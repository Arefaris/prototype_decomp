"""Calls that leave the engine image (kernel32, user32, d3d9, the CRT DLL, the executable): they cannot run in the
emulator, so each is logged with its arguments and answered here: the stack is cleaned the way the callee would
(a table, else what the engine's call site pushed for a stdcall callee, else the callee's own `ret N`), eax takes
the answer, ecx and edx are clobbered as a real callee may. The C runtime functions the engine imports from
MSVCR80.dll that the function under test depends on (memcpy, strlen, floor, ...) are performed here, with their
reads and writes traced like the function's own; every other external is a stub whose answer the policy picks,
and the run notes it. Export names come from the modules' own export tables in the snapshot."""

import math
import struct

from unicorn.x86_const import UC_X86_REG_ECX, UC_X86_REG_FPSW, UC_X86_REG_FPTAG, UC_X86_REG_FP0, UC_X86_REG_FP1, \
	UC_X86_REG_FP2, UC_X86_REG_FP3, UC_X86_REG_FP4, UC_X86_REG_FP5, UC_X86_REG_FP6, UC_X86_REG_FP7

from . import cfg

# stdcall byte counts of APIs whose call sites cannot be analysed (called from the CRT or through thunks)
KNOWN_CLEANUP = {
	"GetLastError": 0, "GetCurrentThreadId": 0, "GetCurrentProcessId": 0, "GetTickCount": 0, "GetProcessHeap": 0,
	"QueryPerformanceCounter": 4, "QueryPerformanceFrequency": 4, "Sleep": 4, "SetLastError": 4,
	"EnterCriticalSection": 4, "LeaveCriticalSection": 4, "TryEnterCriticalSection": 4, "InitializeCriticalSection": 4,
	"DeleteCriticalSection": 4, "InterlockedIncrement": 4, "InterlockedDecrement": 4, "InterlockedExchange": 8,
	"InterlockedCompareExchange": 12, "InterlockedExchangeAdd": 8, "OutputDebugStringA": 4, "IsDebuggerPresent": 0,
	"SetEvent": 4, "ResetEvent": 4, "WaitForSingleObject": 8, "ReleaseSemaphore": 12, "CloseHandle": 4,
	"HeapAlloc": 12, "HeapFree": 12, "VirtualAlloc": 16, "VirtualFree": 12, "TlsGetValue": 4, "TlsSetValue": 8,
	"GetModuleHandleA": 4, "GetProcAddress": 8, "DebugBreak": 0, "RaiseException": 16,
	"?before@type_info@@QBEHABV1@@Z": 4,
	"CreateEventA": 16, "CreateEventW": 16, "CreateSemaphoreA": 16, "CreateSemaphoreW": 16, "CreateMutexA": 12,
	"CreateMutexW": 12, "CreateThread": 24, "ExitThread": 4, "SuspendThread": 4, "ResumeThread": 4, "GetCurrentThread": 0,
	"WaitForMultipleObjects": 16, "SwitchToThread": 0, "SetThreadPriority": 8, "SleepEx": 8, "GetCurrentProcess": 0,
	"ReleaseMutex": 4, "GetSystemInfo": 4, "GlobalMemoryStatus": 4, "GetLocalTime": 4, "GetSystemTimeAsFileTime": 4,
	"timeGetTime": 0, "FlushFileBuffers": 4, "GetFileSize": 8, "SetFilePointer": 16, "ReadFile": 20, "WriteFile": 20,
	"CreateFileA": 28, "CreateFileW": 28, "lstrlenA": 4, "lstrcpyA": 8, "MultiByteToWideChar": 24, "WideCharToMultiByte": 32,
}

# what a stub answers: by export name, else 0
RETURNS = {"TryEnterCriticalSection": 1, "InterlockedIncrement": 1, "IsDebuggerPresent": 0, "WaitForSingleObject": 0,
	"QueryPerformanceCounter": 1, "QueryPerformanceFrequency": 1, "TlsGetValue": 0,
	# handle-creating calls succeed, with a handle that is not 0 or -1
	"CreateEventA": 0x1F0, "CreateEventW": 0x1F0, "CreateSemaphoreA": 0x1F4, "CreateSemaphoreW": 0x1F4,
	"CreateMutexA": 0x1F8, "CreateMutexW": 0x1F8, "CreateThread": 0x1FC, "GetCurrentThread": 0xFFFFFFFE,
	"GetCurrentProcess": 0xFFFFFFFF}
CLOBBER = 0xCCCCCCCC


class Exports:
	"""Export names of the modules in a snapshot, parsed lazily from their PE headers in the snapshot's memory."""

	def __init__(self, readMemory):
		self.read = readMemory
		self.tables = {}

	def table(self, module):
		base = module["base"]
		if base in self.tables:
			return self.tables[base]
		names = {}
		try:
			dos = self.read(base, 0x40)
			peOffset = struct.unpack_from("<I", dos, 0x3C)[0]
			optional = base + peOffset + 24
			magic = struct.unpack_from("<H", self.read(optional, 2))[0]
			exportDir = optional + (96 if magic == 0x10B else 112)
			rva, size = struct.unpack_from("<II", self.read(exportDir, 8))
			if rva and size:
				header = self.read(base + rva, 40)
				nFunctions, nNames, functionsRva, namesRva, ordinalsRva = struct.unpack_from("<IIIII", header, 20)
				functions = struct.unpack("<%dI" % nFunctions, self.read(base + functionsRva, 4 * nFunctions))
				nameRvas = struct.unpack("<%dI" % nNames, self.read(base + namesRva, 4 * nNames))
				ordinals = struct.unpack("<%dH" % nNames, self.read(base + ordinalsRva, 2 * nNames))
				for nameRva, ordinal in zip(nameRvas, ordinals):
					raw = self.read(base + nameRva, 96)
					name = raw[:raw.index(b"\0")].decode("latin-1") if b"\0" in raw else raw.decode("latin-1")
					if ordinal < nFunctions:
						names.setdefault(base + functions[ordinal], name)
		except Exception:
			pass
		self.tables[base] = names
		return names

	def name(self, module, address):
		table = self.table(module)
		if address in table:
			return "%s!%s" % (module["name"], table[address])
		return "%s+0x%X" % (module["name"], address - module["base"])


# --- C runtime functions performed in the emulator --------------------------------------------------------------

def cString(machine, address, limit=0x10000):
	out = bytearray()
	while len(out) < limit:
		chunk = machine.readTraced(address + len(out), 1)
		if chunk is None or chunk == b"\0":
			break
		out += chunk
	return bytes(out)


# the most bytes a CRT memory function is performed for; beyond it (a sentinel variant's count of -1 or 0x7FFFFFFF)
# the run stops as over its budget instead of filling gigabytes byte by byte in Python
CRT_LIMIT = 16 << 20


def tooLarge(machine, n):
	if n > CRT_LIMIT:
		machine.trace.timedOut = True
		return True
	return False


def crtMemcpy(machine, args):
	dst, src, n = args[0], args[1], args[2]
	if tooLarge(machine, n):
		return dst
	data = machine.readTraced(src, n) if n else b""
	if data is None:
		return None
	machine.writeTraced(dst, data)
	return dst


def crtMemset(machine, args):
	dst, value, n = args[0], args[1], args[2]
	if tooLarge(machine, n):
		return dst
	machine.writeTraced(dst, bytes([value & 0xFF]) * n)
	return dst


def crtMemcmp(machine, args):
	if tooLarge(machine, args[2]):
		return 0
	a = machine.readTraced(args[0], args[2])
	b = machine.readTraced(args[1], args[2])
	if a is None or b is None:
		return None
	return 0 if a == b else (1 if a > b else 0xFFFFFFFF)


def crtStrlen(machine, args):
	return len(cString(machine, args[0]))


def crtStrcmp(machine, args, fold=False, limit=None):
	a = cString(machine, args[0])
	b = cString(machine, args[1])
	if limit is not None:
		a, b = a[:limit], b[:limit]
	if fold:
		a, b = a.lower(), b.lower()
	return 0 if a == b else (1 if a > b else 0xFFFFFFFF)


def crtTypeInfoBefore(machine, args):
	"""type_info::before(const type_info&), a thiscall: the decorated names (at +8 of a type descriptor) in strcmp order,
	as the runtime does. A stub answering 0 for every pair would send a search through a type-keyed tree round in
	circles."""
	this = machine.uc.reg_read(UC_X86_REG_ECX)
	a = cString(machine, this + 8)
	b = cString(machine, args[0] + 8)
	return 1 if a < b else 0


def typeName(read, descriptor):
	"""The decorated name at +8 of an RTTI type descriptor (descriptors of one type can be duplicated, so types are compared by name)."""
	out = bytearray()
	while len(out) < 512:
		byte = read(descriptor + 8 + len(out), 1)
		if byte is None:
			return None
		if byte == b"\0":
			break
		out += byte
	return bytes(out)


def dynamicCast(read, pointer, vfDelta, targetType):
	"""The address __RTDynamicCast gives for a pointer to a polymorphic object: the unique base of the complete object
	that has the target type, found through the object's complete object locator (vftable[-1]) and its class hierarchy
	descriptor, with the member displacements of the base class descriptors (and the virtual base table for a virtual
	base). None when the walk reads something the snapshot lacks or the cast needs a case this does not cover; 0 when
	the target is not a base (a null result)."""
	def u32(address, signed=False):
		data = read(address, 4)
		return None if data is None else struct.unpack("<i" if signed else "<I", data)[0]

	vftable = u32(pointer)
	locator = u32(vftable - 4) if vftable else None
	if not locator or vfDelta:
		return None
	offset, cdOffset, hierarchy = u32(locator + 4), u32(locator + 8), u32(locator + 16)
	if None in (offset, cdOffset, hierarchy):
		return None
	complete = pointer - offset
	if cdOffset:
		adjust = u32(pointer - cdOffset, True)
		if adjust is None:
			return None
		complete += adjust
	count, array = u32(hierarchy + 8), u32(hierarchy + 12)
	wanted = typeName(read, targetType)
	if count is None or array is None or wanted is None or count > 256:
		return None
	found = set()
	for i in range(count):
		base = u32(array + 4 * i)
		descriptor = u32(base) if base else None
		name = typeName(read, descriptor) if descriptor else None
		if name is None:
			return None
		if name != wanted:
			continue
		mdisp, pdisp, vdisp = u32(base + 8, True), u32(base + 12, True), u32(base + 16, True)
		if None in (mdisp, pdisp, vdisp):
			return None
		displacement = mdisp
		if pdisp >= 0:
			table = u32(complete + pdisp)
			virtualOffset = u32(table + vdisp, True) if table else None
			if virtualOffset is None:
				return None
			displacement = mdisp + pdisp + virtualOffset
		found.add(complete + displacement)
	return found.pop() if len(found) == 1 else 0


def crtDynamicCast(machine, args):
	"""__RTDynamicCast(pointer, vfDelta, sourceType, targetType, isReference): performed from the object's RTTI. A
	null pointer stays null; a case it cannot walk is answered 0 like any stub."""
	if args[0] == 0:
		return 0
	result = dynamicCast(lambda address, size: machine.readTraced(address, size), args[0], args[1], args[3])
	return result or 0


def crtStrcpy(machine, args):
	machine.writeTraced(args[0], cString(machine, args[1]) + b"\0")
	return args[0]


def teb(machine):
	return machine.state.header.get("fsBase", 0)


def apiTlsGetValue(machine, args):
	"""The thread's TLS slot, from its TEB in the snapshot (the engine's heap finds its per-thread state there)."""
	index = args[0]
	if index < 64:
		data = machine.readTraced(teb(machine) + 0xE10 + 4 * index, 4)
	else:
		expansion = machine.readTraced(teb(machine) + 0xF94, 4)
		pointer = struct.unpack("<I", expansion)[0] if expansion else 0
		data = machine.readTraced(pointer + 4 * (index - 64), 4) if pointer else None
	return struct.unpack("<I", data)[0] if data else 0


def apiTebDword(offset):
	def handler(machine, args):
		data = machine.readTraced(teb(machine) + offset, 4)
		return struct.unpack("<I", data)[0] if data else 0
	return handler


def apiSetLastError(machine, args):
	machine.writeTraced(teb(machine) + 0x34, struct.pack("<I", args[0]))
	return 0


def apiQueryPerformanceCounter(machine, args):
	"""Writes a counter that depends only on how many times the run has asked (the engine's run and ours get the same
	values): the real call fills the caller's 64-bit slot, and a stub that left it alone would hand each run the
	garbage of its own stack frame."""
	index = sum(1 for call in machine.trace.calls if call["name"].endswith("QueryPerformanceCounter"))
	machine.writeTraced(args[0], struct.pack("<Q", 0x100000000 + 0x1000 * index))
	return 1


def apiQueryPerformanceFrequency(machine, args):
	"""A non-zero frequency (10 MHz) in the caller's 64-bit slot, for the same reason."""
	machine.writeTraced(args[0], struct.pack("<Q", 10000000))
	return 1


def interlocked(operation):
	def handler(machine, args):
		data = machine.readTraced(args[0], 4)
		if data is None:
			return None
		old = struct.unpack("<I", data)[0]
		new, result = operation(old, args)
		machine.writeTraced(args[0], struct.pack("<I", new & 0xFFFFFFFF))
		return result & 0xFFFFFFFF
	return handler


def crtFloat(function):
	def handler(machine, args):
		value = struct.unpack("<d", struct.pack("<II", args[0], args[1]))[0]
		try:
			machine.setSt0(function(value))
		except (ValueError, OverflowError):
			machine.setSt0(float("nan"))
		return 0
	return handler


FP = [UC_X86_REG_FP0, UC_X86_REG_FP1, UC_X86_REG_FP2, UC_X86_REG_FP3, UC_X86_REG_FP4, UC_X86_REG_FP5, UC_X86_REG_FP6, UC_X86_REG_FP7]


def fpuTop(uc):
	return (uc.reg_read(UC_X86_REG_FPSW) >> 11) & 7


def fpuRead(uc, depth):
	"""st(depth) of the x87 stack as a float."""
	mantissa, exponent = uc.reg_read(FP[(fpuTop(uc) + depth) & 7])
	sign = -1.0 if exponent & 0x8000 else 1.0
	exponent &= 0x7FFF
	if exponent == 0x7FFF:
		return sign * math.inf if mantissa & ((1 << 63) - 1) == 0 else math.nan
	if exponent == 0 and mantissa == 0:
		return sign * 0.0
	return sign * math.ldexp(mantissa / (1 << 63), exponent - 16383)


def fpuWrite(uc, depth, value):
	from .machine import extended
	uc.reg_write(FP[(fpuTop(uc) + depth) & 7], extended(value))


def fpuPop(uc):
	top = fpuTop(uc)
	uc.reg_write(UC_X86_REG_FPTAG, uc.reg_read(UC_X86_REG_FPTAG) | (3 << (2 * top)))
	uc.reg_write(UC_X86_REG_FPSW, (uc.reg_read(UC_X86_REG_FPSW) & ~(7 << 11)) | (((top + 1) & 7) << 11))


def crtIntrinsic1(function):
	"""A `_CI` function of the C runtime: the argument in st0 (no stack arguments), the result left in st0 in its place."""
	def handler(machine, args):
		uc = machine.uc
		try:
			result = function(fpuRead(uc, 0))
		except (ValueError, OverflowError):
			result = math.nan
		fpuWrite(uc, 0, result)
		return 0
	return handler


def crtIntrinsic2(function):
	"""A two-argument `_CI` function: the first argument in st1, the second in st0; both are replaced by the result."""
	def handler(machine, args):
		uc = machine.uc
		try:
			result = function(fpuRead(uc, 1), fpuRead(uc, 0))
		except (ValueError, OverflowError, ZeroDivisionError):
			result = math.nan
		fpuWrite(uc, 1, result)
		fpuPop(uc)
		return 0
	return handler


def crtFloat2(function):
	def handler(machine, args):
		a = struct.unpack("<d", struct.pack("<II", args[0], args[1]))[0]
		b = struct.unpack("<d", struct.pack("<II", args[2], args[3]))[0]
		try:
			machine.setSt0(function(a, b))
		except (ValueError, OverflowError, ZeroDivisionError):
			machine.setSt0(float("nan"))
		return 0
	return handler


CRT = {
	"memcpy": crtMemcpy, "memmove": crtMemcpy, "memset": crtMemset, "memcmp": crtMemcmp, "strlen": crtStrlen,
	"strcmp": crtStrcmp, "_stricmp": lambda m, a: crtStrcmp(m, a, fold=True), "strncmp": lambda m, a: crtStrcmp(m, a, limit=a[2]),
	"_strnicmp": lambda m, a: crtStrcmp(m, a, fold=True, limit=a[2]), "strcpy": crtStrcpy,
	"?before@type_info@@QBEHABV1@@Z": crtTypeInfoBefore, "__RTDynamicCast": crtDynamicCast,
	"_CIacos": crtIntrinsic1(math.acos), "_CIasin": crtIntrinsic1(math.asin), "_CIatan": crtIntrinsic1(math.atan),
	"_CIcos": crtIntrinsic1(math.cos), "_CIsin": crtIntrinsic1(math.sin), "_CItan": crtIntrinsic1(math.tan),
	"_CIexp": crtIntrinsic1(math.exp), "_CIlog": crtIntrinsic1(math.log), "_CIlog10": crtIntrinsic1(math.log10),
	"_CIsqrt": crtIntrinsic1(math.sqrt), "_CIcosh": crtIntrinsic1(math.cosh), "_CIsinh": crtIntrinsic1(math.sinh),
	"_CItanh": crtIntrinsic1(math.tanh), "_CIatan2": crtIntrinsic2(math.atan2), "_CIpow": crtIntrinsic2(math.pow),
	"_CIfmod": crtIntrinsic2(math.fmod),
	"floor": crtFloat(math.floor), "ceil": crtFloat(math.ceil), "sqrt": crtFloat(math.sqrt), "sin": crtFloat(math.sin),
	"cos": crtFloat(math.cos), "tan": crtFloat(math.tan), "exp": crtFloat(math.exp), "log": crtFloat(math.log),
	"fabs": crtFloat(abs), "atan": crtFloat(math.atan), "asin": crtFloat(math.asin), "acos": crtFloat(math.acos),
	"atan2": crtFloat2(math.atan2), "pow": crtFloat2(math.pow), "fmod": crtFloat2(math.fmod),
	"abs": lambda m, a: abs(a[0] - 0x100000000 if a[0] & 0x80000000 else a[0]) & 0xFFFFFFFF,
	# Win32 calls whose effect is in the thread's own memory: performed exactly from the snapshot
	"TlsGetValue": apiTlsGetValue, "GetCurrentThreadId": apiTebDword(0x24), "GetCurrentProcessId": apiTebDword(0x20),
	"GetLastError": apiTebDword(0x34), "SetLastError": apiSetLastError,
	"QueryPerformanceCounter": apiQueryPerformanceCounter, "QueryPerformanceFrequency": apiQueryPerformanceFrequency,
	"InterlockedIncrement": interlocked(lambda old, a: (old + 1, old + 1)),
	"InterlockedDecrement": interlocked(lambda old, a: (old - 1, old - 1)),
	"InterlockedExchange": interlocked(lambda old, a: (a[1], old)),
	"InterlockedExchangeAdd": interlocked(lambda old, a: (old + a[1], old)),
	"InterlockedCompareExchange": interlocked(lambda old, a: (a[1] if old == a[2] else old, old)),
}


class Policy:
	"""Answers for external calls. `variant` selects an alternative answer set for runs that probe other paths."""

	def __init__(self, variant=0):
		self.variant = variant

	@staticmethod
	def short(name):
		return name.split("!", 1)[1] if "!" in name else None

	def cleanup(self, name, target, readMemory, pushes=None, callerCleans=False):
		"""Bytes the callee pops: the table, nothing for a cdecl callee (its caller adds to esp after the call),
		else what the engine's call site pushed (the APIs and COM methods are stdcall), else the callee's `ret N`."""
		short = self.short(name)
		if short in KNOWN_CLEANUP:
			return KNOWN_CLEANUP[short]
		if short in CRT or callerCleans:
			return 0
		if pushes is not None:
			return 4 * pushes
		found = cfg.stackCleanup(readMemory, target)
		return 0 if found is None else found

	def answer(self, name, machine, args):
		"""(eax, performed): a CRT function is performed; anything else is a stub with the variant's value."""
		short = self.short(name)
		handler = CRT.get(short)
		if handler is not None:
			value = handler(machine, args)
			return (0 if value is None else value & 0xFFFFFFFF), True
		if self.variant == 0:
			return RETURNS.get(short, 0), False
		# other variants: fail every call (HRESULT E_FAIL / FALSE) or answer non-zero
		return (0x80004005 if self.variant == 1 else 1), False
