"""Calls that leave the engine image (kernel32, user32, d3d9, the CRT DLL, the executable): they cannot run in the
emulator, so each is logged with its arguments and answered here: the stack is cleaned the way the callee would
(a table, else what the engine's call site pushed for a stdcall callee, else the callee's own `ret N`), eax takes
the answer, ecx and edx are clobbered as a real callee may. The C runtime functions the engine imports from
MSVCR80.dll that the function under test depends on (memcpy, strlen, floor, ...) are performed here, with their
reads and writes traced like the function's own; every other external is a stub whose answer the policy picks,
and the run notes it. Export names come from the modules' own export tables in the snapshot."""

import math
import struct

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
}

# what a stub answers: by export name, else 0
RETURNS = {"TryEnterCriticalSection": 1, "InterlockedIncrement": 1, "IsDebuggerPresent": 0, "WaitForSingleObject": 0,
	"QueryPerformanceCounter": 1, "QueryPerformanceFrequency": 1, "TlsGetValue": 0}
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
	"floor": crtFloat(math.floor), "ceil": crtFloat(math.ceil), "sqrt": crtFloat(math.sqrt), "sin": crtFloat(math.sin),
	"cos": crtFloat(math.cos), "tan": crtFloat(math.tan), "exp": crtFloat(math.exp), "log": crtFloat(math.log),
	"fabs": crtFloat(abs), "atan": crtFloat(math.atan), "asin": crtFloat(math.asin), "acos": crtFloat(math.acos),
	"atan2": crtFloat2(math.atan2), "pow": crtFloat2(math.pow), "fmod": crtFloat2(math.fmod),
	"abs": lambda m, a: abs(a[0] - 0x100000000 if a[0] & 0x80000000 else a[0]) & 0xFFFFFFFF,
	# Win32 calls whose effect is in the thread's own memory: performed exactly from the snapshot
	"TlsGetValue": apiTlsGetValue, "GetCurrentThreadId": apiTebDword(0x24), "GetCurrentProcessId": apiTebDword(0x20),
	"GetLastError": apiTebDword(0x34), "SetLastError": apiSetLastError,
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
