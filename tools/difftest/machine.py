"""The emulator: Unicorn over a captured state. Pages are mapped lazily from the snapshot (plus an optional
overlay of perturbed bytes); only the engine image, our loaded function and the return page may execute, so a call
into another module stops at its first instruction and is answered by externals.Policy. Every read and write, every
call (a block starting at a known function entry), the instructions executed inside the tested functions and the
end registers are recorded in a Trace.

One Machine can run several times (the engine's function, ours, every sentinel variant) on the same state: run()
restores the pages the previous run dirtied (the snapshot is immutable, so their bytes come straight back) and the
entry registers, so the same emulator, its mappings and our loaded function are reused instead of rebuilt."""

import struct
import time

from unicorn import Uc, UcError, UC_ARCH_X86, UC_MODE_32, UC_HOOK_MEM_UNMAPPED, UC_HOOK_MEM_READ, UC_HOOK_MEM_WRITE, \
	UC_HOOK_BLOCK, UC_HOOK_CODE, UC_HOOK_MEM_FETCH_PROT, UC_PROT_ALL, UC_PROT_READ, UC_PROT_WRITE, UC_MEM_FETCH_UNMAPPED, \
	UC_MEM_READ_UNMAPPED, UC_MEM_WRITE_UNMAPPED
try:
	from unicorn import UC_HOOK_INSN
except ImportError:
	UC_HOOK_INSN = None
from unicorn.x86_const import *

from capstone import x86 as csx86
from capstone.x86 import X86_OP_MEM

from . import project, externals, cfg

CS_TO_UC = {csx86.X86_REG_EAX: UC_X86_REG_EAX, csx86.X86_REG_EBX: UC_X86_REG_EBX, csx86.X86_REG_ECX: UC_X86_REG_ECX,
	csx86.X86_REG_EDX: UC_X86_REG_EDX, csx86.X86_REG_ESI: UC_X86_REG_ESI, csx86.X86_REG_EDI: UC_X86_REG_EDI,
	csx86.X86_REG_EBP: UC_X86_REG_EBP, csx86.X86_REG_ESP: UC_X86_REG_ESP}

PAGE = project.PAGE
# SSE instructions whose 16-byte memory operand may be unaligned
UNALIGNED_OK = {"movups", "movupd", "movdqu", "lddqu", "vmovups", "vmovupd", "vmovdqu", "movsd", "movss", "movlps", "movhps",
	"movlpd", "movhpd", "movq", "movd", "fxsave", "fxrstor"}
REGS = {"eax": UC_X86_REG_EAX, "ebx": UC_X86_REG_EBX, "ecx": UC_X86_REG_ECX, "edx": UC_X86_REG_EDX, "esi": UC_X86_REG_ESI,
	"edi": UC_X86_REG_EDI, "ebp": UC_X86_REG_EBP, "esp": UC_X86_REG_ESP}
XMM = [UC_X86_REG_XMM0, UC_X86_REG_XMM1, UC_X86_REG_XMM2, UC_X86_REG_XMM3, UC_X86_REG_XMM4, UC_X86_REG_XMM5, UC_X86_REG_XMM6, UC_X86_REG_XMM7]
EFLAGS_MASK = 0x0CD5
STACK_GROWTH = 0x100000
ACCESS_NAMES = {UC_MEM_FETCH_UNMAPPED: "fetch", UC_MEM_READ_UNMAPPED: "read", UC_MEM_WRITE_UNMAPPED: "write"}

FP = [UC_X86_REG_FP0, UC_X86_REG_FP1, UC_X86_REG_FP2, UC_X86_REG_FP3, UC_X86_REG_FP4, UC_X86_REG_FP5, UC_X86_REG_FP6, UC_X86_REG_FP7]

# instruction counts, hook counts and wall time per hook, when profiling is on (bench.py --profile)
PROFILE = False
# instructions per emu_start: the run checks its deadline between chunks
CHUNK = 100000
# jmp dword ptr [address]: the engine's stub for an imported function
IMPORT_THUNK = bytes([0xFF, 0x25])

_rdtscImage = None


def imageRdtsc():
	"""The addresses of `rdtsc` in the engine image (scanned once; the original's fixed clock value must be
	substituted in both runs or a real TSC would differ between them)."""
	global _rdtscImage
	if _rdtscImage is None:
		data = project.image().data
		base = project.image().base
		addresses = set()
		i = data.find(b"\x0F\x31")
		while i != -1:
			addresses.add(base + i)
			i = data.find(b"\x0F\x31", i + 1)
		_rdtscImage = addresses
	return _rdtscImage


def extended(value):
	"""A double as Unicorn's 80-bit x87 register value: (mantissa, sign and exponent)."""
	import math
	if value != value:
		return (3 << 62, 0x7FFF)
	sign = 0x8000 if math.copysign(1.0, value) < 0 else 0
	value = abs(value)
	if value == 0.0:
		return (0, sign)
	if math.isinf(value):
		return (1 << 63, sign | 0x7FFF)
	m, e = math.frexp(value)
	return (int(m * (1 << 64)) & 0xFFFFFFFFFFFFFFFF, sign | (e - 1 + 16383))


def gdtEntry(base, limit, access, flags):
	entry = limit & 0xFFFF
	entry |= (base & 0xFFFFFF) << 16
	entry |= (access & 0xFF) << 40
	entry |= ((limit >> 16) & 0xF) << 48
	entry |= (flags & 0xF) << 52
	entry |= ((base >> 24) & 0xFF) << 56
	return struct.pack("<Q", entry)


class Trace:
	def __init__(self):
		self.reads = set()  # (address, size) outside the private stack
		self.readOrder = []  # the addresses above in the order they were first read
		self.writes = []  # (address, size, value) outside the private stack, in order
		self.privateWrites = 0
		self.calls = []  # dicts: name/address, esp, ret, ecx, edx, eax, args
		self.externals = 0
		self.stubbed = []  # names of the external calls answered by a stub (not performed)
		self.executed = set()  # instruction addresses inside the watched ranges
		self.instructions = 0
		self.fault = None
		self.end = {}
		self.timedOut = False
		self.last = []  # the last instructions before a fault

	def finalBytes(self):
		"""{address: byte} the run left in memory outside its private stack."""
		result = {}
		for address, size, value in self.writes:
			for k in range(size):
				result[address + k] = (value >> (8 * k)) & 0xFF
		return result


class Layout:
	"""Addresses free in a snapshot for our code, the data beside it, the return page and the GDT.

	A live-captured state saves the addresses it used (its page table does not span the whole process, so a
	replay would otherwise pick a different base); `state.header["layout"]` wins when present."""

	def __init__(self, state):
		saved = state.header.get("layout")
		if saved:
			self.code = saved["code"]
			self.data = saved["data"]
			self.ret = saved["ret"]
			self.gdt = saved["gdt"]
			self.scratch = saved["scratch"]
			self.end = saved["end"]
			return
		pages = state.mappedPages
		start = 0x60000000
		while True:
			if all((start + k) not in pages for k in range(0, 0x300000, PAGE)):
				break
			start += 0x100000
		self.code = start
		self.data = start + 0x100000
		self.ret = start + 0x200000
		self.gdt = start + 0x201000
		self.scratch = start + 0x202000
		self.end = start + 0x300000

	def asDict(self):
		return {"code": self.code, "data": self.data, "ret": self.ret, "gdt": self.gdt,
			"scratch": self.scratch, "end": self.end}


class Machine:
	def __init__(self, state, pageStore, overlay=None, policy=None, functionStarts=None, watch=(), codeHook=True):
		self.state = state
		self.store = pageStore
		self.policy = policy or externals.Policy()
		self.entryAddress = None
		self.functionStarts = functionStarts or set()
		self.watch = list(watch)  # [(start, end)] ranges whose instructions are recorded
		self.image = project.image()
		self.layout = Layout(state)
		self.executable = [(self.image.base, self.image.end), (self.layout.code, self.layout.data), (self.layout.ret, self.layout.ret + PAGE)]
		self.exports = externals.Exports(self.readSnapshot)
		self.trace = Trace()
		self.alignCache = {}
		self.blockCache = {}  # block address -> (instruction count, [instruction addresses])
		self.mapped = set()
		self.invalid = None
		self.entryEsp = 0
		self.stackLow = 0
		self.privateLimit = 0
		self.ours = None
		self.loaded = None
		self.rdtsc = set(imageRdtsc())  # instruction addresses whose rdtsc gets a fixed value
		self.touched = set()  # snapshot pages any run read or wrote (for --trim)
		self.missing = set()  # pages a run needed but the snapshot lacks (a live capture's offline replay)
		self.dirty = set()  # mapped pages the last run modified
		self.clean = {}  # page -> bytes for mapped pages the snapshot does not hold (our code, grown stack)
		self.overlay = {}
		self.overlayPages = {}
		self.stats = {"emu": 0.0, "block": 0.0, "read": 0.0, "write": 0.0, "code": 0.0, "external": 0.0,
			"blocks": 0, "reads": 0, "writes": 0, "codes": 0, "externals": 0, "maps": 0, "emuCalls": 0}
		self.lastBlock = None  # (instruction count, [instruction addresses]) of the block being executed
		uc = self.uc = Uc(UC_ARCH_X86, UC_MODE_32)
		for address in (self.layout.code, self.layout.data):
			uc.mem_map(address, 0x100000, UC_PROT_ALL)
			self.mapped.update(range(address, address + 0x100000, PAGE))
		for address in (self.layout.ret, self.layout.gdt, self.layout.scratch):
			uc.mem_map(address, PAGE, UC_PROT_ALL)
			self.mapped.add(address)
		uc.mem_write(self.layout.ret, b"\x90" * 16)
		self.setupSegments(state.header.get("fsBase", 0))
		self.setOverlay(overlay)
		uc.hook_add(UC_HOOK_MEM_UNMAPPED, self.onUnmapped)
		uc.hook_add(UC_HOOK_MEM_FETCH_PROT, self.onFetchProt)
		uc.hook_add(UC_HOOK_MEM_READ, self.onRead)
		uc.hook_add(UC_HOOK_MEM_WRITE, self.onWrite)
		uc.hook_add(UC_HOOK_BLOCK, self.onBlock)
		# rdtsc: a fixed value in both runs, so the two runs cannot see different clocks
		if UC_HOOK_INSN is not None:
			try:
				uc.hook_add(UC_HOOK_INSN, self.onRdtsc, None, 1, 0, UC_X86_INS_RDTSC)
			except Exception as e:
				if PROFILE:
					print("    UC_HOOK_INSN failed (%s); falling back to UC_HOOK_CODE" % e, flush=True)
				uc.hook_add(UC_HOOK_CODE, self.onCode)
		elif codeHook:
			uc.hook_add(UC_HOOK_CODE, self.onCode)

	# --- memory ---------------------------------------------------------------------------------------------------

	def setupSegments(self, fsBase):
		uc = self.uc
		gdt = self.layout.gdt
		uc.mem_write(gdt + 8 * 1, gdtEntry(0, 0xFFFFF, 0x9B, 0xC))  # cs
		uc.mem_write(gdt + 8 * 2, gdtEntry(0, 0xFFFFF, 0x93, 0xC))  # ds, es, ss, gs
		uc.mem_write(gdt + 8 * 3, gdtEntry(fsBase, 0xFFFFF, 0x93, 0xC))  # fs: the thread's TEB
		uc.reg_write(UC_X86_REG_GDTR, (0, gdt, 0x1000, 0))
		uc.reg_write(UC_X86_REG_CS, 0x08)
		for reg in (UC_X86_REG_DS, UC_X86_REG_ES, UC_X86_REG_SS, UC_X86_REG_GS):
			uc.reg_write(reg, 0x10)
		uc.reg_write(UC_X86_REG_FS, 0x18)

	def pageData(self, page):
		"""The raw bytes of a page: the snapshot's store, or the live process during a live capture."""
		offset = self.state.pages.get(page)
		if offset is not None:
			return self.store.get(offset)
		if self.state.live is not None:
			return self.state.live(page)
		return None

	def pageBytes(self, page):
		"""A page's bytes with the overlay applied, or None. Any page read from the snapshot or the live
		process is recorded in `touched` so a live capture can save exactly the pages its runs used."""
		data = self.pageData(page)
		if data is None:
			return None
		self.touched.add(page)
		patches = self.overlayPages.get(page)
		if patches:
			data = bytearray(data)
			for address, value in patches.items():
				data[address - page] = value
			data = bytes(data)
		return data

	def isExecutable(self, address):
		return any(start <= address < end for start, end in self.executable)

	def mapPage(self, page):
		if page in self.mapped:
			return True
		data = self.pageBytes(page)
		if data is None:
			if self.stackLow <= page < self.entryEsp:
				data = bytes(PAGE)  # stack growth below the committed pages: the system would commit zeros
			else:
				self.missing.add(page)
				return False
		prot = UC_PROT_ALL if self.isExecutable(page) else UC_PROT_READ | UC_PROT_WRITE
		self.uc.mem_map(page, PAGE, prot)
		self.uc.mem_write(page, data)
		self.mapped.add(page)
		if page not in self.state.pages and page not in self.clean:
			self.clean[page] = data
		if PROFILE:
			self.stats["maps"] += 1
		return True

	def setOverlay(self, overlay):
		"""Applies a new overlay of perturbed bytes to the clean snapshot, re-writing the pages it touches."""
		overlay = overlay or {}
		if overlay == self.overlay:
			return
		old = set(self.overlayPages)
		self.overlay = overlay
		self.overlayPages = {}
		for address, value in overlay.items():
			self.overlayPages.setdefault(address & ~(PAGE - 1), {})[address] = value
		for page in old | set(self.overlayPages):
			if page in self.mapped:
				data = self.pageBytes(page)
				if data is not None:
					self.uc.mem_write(page, data)
			self.dirty.discard(page)

	def seal(self):
		"""Captures the clean content of every mapped page the snapshot does not hold (our loaded code and data,
		the GDT), so run() can restore the pages later runs modify."""
		self.clean = {}
		for page in self.mapped:
			if page not in self.state.pages:
				data = bytes(self.uc.mem_read(page, PAGE))
				self.clean[page] = data
				if self.layout.code <= page < self.layout.data:
					self.noteRdtsc(data, page)
		self.dirty.clear()

	def noteRdtsc(self, data, base):
		"""Adds the addresses of `rdtsc` in freshly loaded code to the fixed-clock set."""
		i = data.find(b"\x0F\x31")
		while i != -1:
			self.rdtsc.add(base + i)
			i = data.find(b"\x0F\x31", i + 1)

	def resetToClean(self):
		"""Undoes the previous run's writes: dirty pages get their clean bytes back (snapshot store or live
		process, with the current overlay re-applied); pages neither source holds (our loaded code, grown stack)
		get their sealed content."""
		if self.dirty:
			for page in self.dirty:
				data = self.pageBytes(page)
				if data is None:
					data = self.clean.get(page)
				if data is not None:
					self.uc.mem_write(page, data)
			self.dirty.clear()

	def onFetchProt(self, uc, access, address, size, value, data):
		"""A fetch from a page that may not execute: a call into another module. The hook's address is exact
		(eip read after the exception is not); run() answers the call."""
		self.invalid = ("fetchprot", address, size)
		return False

	def onUnmapped(self, uc, access, address, size, value, data):
		page = address & ~(PAGE - 1)
		ok = True
		for p in range(page, address + max(size, 1), PAGE):
			ok = self.mapPage(p) and ok
		if not ok:
			# a page the snapshot does not hold (a live capture saved only what its runs touched): report it as
			# a missing page, never guess its bytes
			kind = "missing-page" if self.missing else ACCESS_NAMES.get(access, str(access))
			self.invalid = (kind, address, size)
		return ok

	def readSnapshot(self, address, size):
		"""Bytes straight from the snapshot (overlay applied) without touching the emulator."""
		out = bytearray()
		while size > 0:
			page = address & ~(PAGE - 1)
			if page in self.mapped and page not in self.state.pages:
				data = bytes(self.uc.mem_read(page, PAGE))
			else:
				data = self.pageBytes(page)
			if data is None:
				return None if not out else bytes(out)
			take = min(size, page + PAGE - address)
			out += data[address - page:address - page + take]
			address += take
			size -= take
		return bytes(out)

	def read(self, address, size):
		"""Bytes as the emulator sees them now (mapping on demand)."""
		for page in range(address & ~(PAGE - 1), address + size, PAGE):
			if not self.mapPage(page):
				return None
		return bytes(self.uc.mem_read(address, size))

	def write(self, address, data):
		for page in range(address & ~(PAGE - 1), address + len(data), PAGE):
			if not self.mapPage(page):
				self.uc.mem_map(page, PAGE, UC_PROT_ALL)
				self.mapped.add(page)
		self.uc.mem_write(address, bytes(data))

	def u32(self, address):
		data = self.read(address, 4)
		return None if data is None else struct.unpack("<I", data)[0]

	def readTraced(self, address, size):
		"""A read made on the function's behalf (a CRT function performed here): recorded like its own."""
		data = self.read(address, size)
		if data is not None and size:
			self.onRead(self.uc, 0, address, size, 0, None)
		return data

	def writeTraced(self, address, data):
		if not data:
			return
		self.write(address, data)
		for page in range(address & ~(PAGE - 1), address + len(data), PAGE):
			self.dirty.add(page)
		stackLow = self.stackLow
		stackHigh = self.entryEsp + 4
		writes = self.trace.writes
		private = 0
		view = memoryview(data)
		n = len(data)
		i = 0
		while i + 4 <= n:
			a = address + i
			if stackLow <= a < stackHigh:
				private += 1
			else:
				writes.append((a, 4, int.from_bytes(view[i:i + 4], "little")))
			i += 4
		while i < n:
			a = address + i
			if stackLow <= a < stackHigh:
				private += 1
			else:
				writes.append((a, 1, data[i]))
			i += 1
		self.trace.privateWrites += private

	def setSt0(self, value):
		"""Leaves `value` in st0 as a function returning a double does (one entry on the x87 stack)."""
		uc = self.uc
		uc.reg_write(UC_X86_REG_FPSW, 7 << 11)
		uc.reg_write(UC_X86_REG_FPTAG, 0x3FFF)
		uc.reg_write(UC_X86_REG_FP7, extended(value))

	# --- hooks ----------------------------------------------------------------------------------------------------

	def onRead(self, uc, access, address, size, value, data):
		t0 = time.perf_counter() if PROFILE else 0.0
		if size == 8 and address & 15:
			self.checkAlignment(uc, address)
		if self.stackLow <= address < self.entryEsp + 4:
			if PROFILE:
				self.stats["read"] += time.perf_counter() - t0
				self.stats["reads"] += 1
			return
		key = (address, size)
		if key not in self.trace.reads:
			self.trace.reads.add(key)
			self.trace.readOrder.append(address)
		if PROFILE:
			self.stats["read"] += time.perf_counter() - t0
			self.stats["reads"] += 1

	def onWrite(self, uc, access, address, size, value, data):
		t0 = time.perf_counter() if PROFILE else 0.0
		if size == 8 and address & 15:
			self.checkAlignment(uc, address)
		self.dirty.add(address & ~(PAGE - 1))
		if self.stackLow <= address < self.entryEsp + 4:
			self.trace.privateWrites += 1
			if PROFILE:
				self.stats["write"] += time.perf_counter() - t0
				self.stats["writes"] += 1
			return
		self.trace.writes.append((address, size, value))
		if PROFILE:
			self.stats["write"] += time.perf_counter() - t0
			self.stats["writes"] += 1

	def checkAlignment(self, uc, address):
		"""QEMU does not fault on a misaligned 16-byte SSE access (movaps, addps, ... need a 16-byte aligned
		operand; the real processor raises #GP, Windows reports an access violation at 0xFFFFFFFF). Unicorn
		reports such an access as two 8-byte halves, so an 8-byte access off a 16-byte boundary is checked
		against its instruction."""
		if self.trace.fault:
			return
		eip = uc.reg_read(UC_X86_REG_EIP)
		operand = self.alignCache.get(eip)
		if operand is None:
			operand = False
			code = self.read(eip, 16)
			if code:
				insns = cfg.disassemble(code, eip)
				if insns and insns[0].mnemonic not in UNALIGNED_OK:
					for op in insns[0].operands:
						if op.type == X86_OP_MEM and op.size == 16:
							operand = (CS_TO_UC.get(op.mem.base), CS_TO_UC.get(op.mem.index), op.mem.scale, op.mem.disp)
			self.alignCache[eip] = operand
		if not operand:
			return
		base, index, scale, disp = operand
		effective = disp
		if base:
			effective += uc.reg_read(base)
		if index:
			effective += scale * uc.reg_read(index)
		if effective & 15:
			self.trace.fault = {"error": "misaligned 16-byte SSE access (#GP on the processor, an access violation at 0xFFFFFFFF in Windows)",
				"eip": eip, "access": ("aligned-access", effective & 0xFFFFFFFF, 16), "where": self.where(eip)}
			uc.emu_stop()

	def decodeBlock(self, address, size):
		"""(instruction count, [instruction addresses]) of one basic block, decoded once per address."""
		code = self.read(address, size)
		if not code:
			return 0, []
		count = 0
		addresses = []
		for insn in cfg.disassemble(code, address):
			if insn.address >= address + size:
				break
			count += 1
			addresses.append(insn.address)
		return count, addresses

	def onBlock(self, uc, address, size, data):
		t0 = time.perf_counter() if PROFILE else 0.0
		info = self.blockCache.get(address)
		if info is None:
			info = self.decodeBlock(address, size)
			self.blockCache[address] = info
		self.lastBlock = info
		self.trace.instructions += info[0]
		for insnAddress in info[1]:
			for start, end in self.watch:
				if start <= insnAddress < end:
					self.trace.executed.add(insnAddress)
					break
		# an import thunk (jmp dword ptr [import]) is not logged: the external call it leads to is
		if address != self.entryAddress and (address in self.functionStarts or (self.ours is not None and address in self.ours)) \
				and self.read(address, 2) != IMPORT_THUNK:
			esp = uc.reg_read(UC_X86_REG_ESP)
			frame = self.read(esp, 36)
			words = struct.unpack("<9I", frame) if frame is not None and len(frame) == 36 else (0,) * 9
			call = {"address": address, "name": self.calleeName(address), "esp": esp, "ret": words[0],
				"args": words[1:], "ecx": uc.reg_read(UC_X86_REG_ECX), "edx": uc.reg_read(UC_X86_REG_EDX),
				"eax": uc.reg_read(UC_X86_REG_EAX), "external": False}
			self.frameArguments(call)
			self.trace.calls.append(call)
		if PROFILE:
			self.stats["block"] += time.perf_counter() - t0
			self.stats["blocks"] += 1

	def onCode(self, uc, address, size, data):
		"""Fallback per-instruction hook (only when UC_HOOK_INSN is unavailable): rdtsc gets a fixed value."""
		t0 = time.perf_counter() if PROFILE else 0.0
		if address in self.rdtsc:
			uc.reg_write(UC_X86_REG_EAX, 0x12345678)
			uc.reg_write(UC_X86_REG_EDX, 0x1)
			uc.reg_write(UC_X86_REG_EIP, address + 2)
		if PROFILE:
			self.stats["code"] += time.perf_counter() - t0
			self.stats["codes"] += 1

	def onRdtsc(self, uc, user_data):
		eip = uc.reg_read(UC_X86_REG_EIP)
		uc.reg_write(UC_X86_REG_EAX, 0x12345678)
		uc.reg_write(UC_X86_REG_EDX, 0x1)
		uc.reg_write(UC_X86_REG_EIP, eip + 2)

	def isPrivate(self, value):
		return self.stackLow <= value < self.entryEsp + 4

	def frameArguments(self, call):
		"""Arguments that point into the function's own frame (temporaries) differ in address between the two
		builds; what they point at is recorded (64 bytes) so the comparison can look at the contents instead."""
		frame = {}
		for key, value in [("ecx", call["ecx"]), ("edx", call["edx"])] + list(enumerate(call["args"])):
			if self.isPrivate(value):
				data = self.read(value, 64)
				if data is not None:
					frame[key] = data
		if frame:
			call["frame"] = frame

	def adjustPartialBlock(self, eip, started):
		"""The block hook counts a whole block at entry; when a run stops mid-block, the instructions after `eip`
		(and `eip` itself when it did not start, as on the instruction limit) never executed."""
		info = self.lastBlock
		if not info:
			return
		unexecuted = 0
		for address in info[1]:
			if (address > eip) if started else (address >= eip):
				unexecuted += 1
				self.trace.executed.discard(address)
		self.trace.instructions -= unexecuted
		self.lastBlock = None

	def calleeName(self, address):
		name = project.symbolAt(address)
		if name:
			return name
		if self.ours and address in self.ours:
			return "ours:" + self.ours[address]
		return "0x%08X" % address

	# --- registers ------------------------------------------------------------------------------------------------

	def loadRegisters(self, regs):
		uc = self.uc
		for name, reg in REGS.items():
			uc.reg_write(reg, regs[name])
		uc.reg_write(UC_X86_REG_EFLAGS, (regs["eflags"] & EFLAGS_MASK) | 0x202)
		uc.reg_write(UC_X86_REG_FPCW, regs.get("fpcw", 0x27F))
		uc.reg_write(UC_X86_REG_MXCSR, regs.get("mxcsr", 0x1F80))
		for i, value in enumerate(regs.get("xmm", [])[:8]):
			uc.reg_write(XMM[i], int.from_bytes(bytes.fromhex(value), "little"))

	def registers(self):
		uc = self.uc
		result = {name: uc.reg_read(reg) for name, reg in REGS.items()}
		result["eip"] = uc.reg_read(UC_X86_REG_EIP)
		result["fpsw"] = uc.reg_read(UC_X86_REG_FPSW)
		top = (result["fpsw"] >> 11) & 7
		try:
			result["st0"] = tuple(uc.reg_read(FP[top]))
		except Exception:
			result["st0"] = None
		return result

	# --- running --------------------------------------------------------------------------------------------------

	def external(self, target):
		"""Answers a call that reached code outside the engine image: logs it and returns to the caller."""
		t0 = time.perf_counter() if PROFILE else 0.0
		uc = self.uc
		esp = uc.reg_read(UC_X86_REG_ESP)
		frame = self.read(esp, 36)
		words = struct.unpack("<9I", frame) if frame is not None and len(frame) == 36 else (0,) * 9
		module = self.state.module(target)
		name = self.exports.name(module, target) if module else "0x%08X" % target
		pushes = None
		callerCleans = False
		returnAddress = words[0]
		if self.image.contains(returnAddress):
			pushes = cfg.callerPushes(self.image.read, returnAddress, project.containingFunction(returnAddress))
			callerCleans = cfg.callerCleanup(self.image.read, returnAddress) > 0
		elif self.ours and self.layout.code <= returnAddress < self.layout.data:
			pushes = cfg.callerPushes(self.read, returnAddress, max((a for a in self.ours if a <= returnAddress), default=None))
			callerCleans = cfg.callerCleanup(self.read, returnAddress) > 0
		cleanup = self.policy.cleanup(name, target, self.readSnapshot, pushes, callerCleans)
		count = min(8, cleanup // 4) if cleanup else (pushes if pushes else 4)
		self.trace.externals += 1
		value, performed = self.policy.answer(name, self, words[1:9])
		if not performed:
			self.trace.stubbed.append(name)
		call = {"address": target, "name": name, "esp": esp, "ret": returnAddress, "args": words[1:1 + count],
			"ecx": uc.reg_read(UC_X86_REG_ECX), "edx": uc.reg_read(UC_X86_REG_EDX), "eax": uc.reg_read(UC_X86_REG_EAX),
			"external": True, "cleanup": cleanup, "returned": value, "performed": performed}
		self.frameArguments(call)
		self.trace.calls.append(call)
		uc.reg_write(UC_X86_REG_EAX, value)
		uc.reg_write(UC_X86_REG_ECX, externals.CLOBBER)
		uc.reg_write(UC_X86_REG_EDX, externals.CLOBBER)
		uc.reg_write(UC_X86_REG_ESP, esp + 4 + cleanup)
		if PROFILE:
			self.stats["external"] += time.perf_counter() - t0
			self.stats["externals"] += 1
		return words[0]

	def run(self, entry, argBytes=0, budget=20000000, timeout=60.0, watch=None):
		"""Runs from `entry` with the state's registers until the function returns to the return page."""
		uc = self.uc
		if watch is not None:
			self.watch = watch
		self.resetToClean()
		regs = self.state.regs
		self.loadRegisters(regs)
		self.trace = Trace()
		self.entryEsp = regs["esp"]
		self.stackLow = self.entryEsp - STACK_GROWTH
		self.privateLimit = self.entryEsp + 4 + max(argBytes, 32)
		self.write(self.entryEsp, struct.pack("<I", self.layout.ret))
		self.trace.entry = dict(regs)
		self.entryAddress = entry
		self.invalid = None
		self.trace.timedOut = False
		self.lastBlock = None
		pc = entry
		deadline = time.time() + timeout
		while True:
			# hard limits across the segments between external calls: instructions, wall clock, externals
			# (a loop spinning on a stub's answer would otherwise never end)
			remaining = budget - self.trace.instructions
			if remaining <= 0 or time.time() >= deadline or self.trace.externals > 20000:
				self.trace.timedOut = True
				break
			self.invalid = None
			t0 = time.perf_counter() if PROFILE else 0.0
			if PROFILE:
				self.stats["emuCalls"] += 1
			try:
				# no `timeout` here: Unicorn 2.1.4 spends ~15 ms per emu_start call whenever a timeout is
				# given (Windows timer resolution), which dominates functions that call out often. The
				# instruction `count` bounds a single segment; the deadline at the top of the loop bounds
				# the wall clock across segments.
				# the count is also cut into chunks, so the deadline is checked every CHUNK instructions even in a
				# function that never calls out (a variant spinning in a loop kept the game frozen for minutes)
				uc.emu_start(pc, self.layout.ret, count=min(remaining, CHUNK))
			except UcError as e:
				if PROFILE:
					self.stats["emu"] += time.perf_counter() - t0
				eip = uc.reg_read(UC_X86_REG_EIP)
				if self.invalid and self.invalid[0] == "fetchprot":
					pc = self.external(self.invalid[1])
					continue
				if self.invalid and self.invalid[0] == "fetch":
					eip = self.invalid[1]
				self.trace.fault = {"error": str(e), "eip": eip, "access": self.invalid, "where": self.where(eip)}
				self.adjustPartialBlock(eip, True)
				break
			if PROFILE:
				self.stats["emu"] += time.perf_counter() - t0
			eip = uc.reg_read(UC_X86_REG_EIP)
			if self.trace.fault:  # stopped by a hook (alignment)
				self.adjustPartialBlock(eip, True)
				break
			if eip == self.layout.ret:
				self.lastBlock = None
				break
			if self.trace.instructions < budget and remaining > CHUNK:
				# stopped at a chunk boundary: go on from here after the deadline check at the top
				self.adjustPartialBlock(eip, False)
				self.lastBlock = None
				pc = eip
				continue
			self.trace.timedOut = True
			self.adjustPartialBlock(eip, False)
			break
		self.trace.end = self.registers()
		if PROFILE:
			s = self.stats
			print("    profile: emu %.2fs (%d calls, avg %.2f ms) block %.2fs read %.2fs write %.2fs code %.2fs ext %.2fs; blocks %d reads %d writes %d codes %d ext %d maps %d insns %d"
				% (s["emu"], s["emuCalls"], 1000.0 * s["emu"] / max(1, s["emuCalls"]), s["block"], s["read"], s["write"], s["code"], s["external"],
					s["blocks"], s["reads"], s["writes"], s["codes"], s["externals"], s["maps"], self.trace.instructions), flush=True)
		return self.trace

	def where(self, eip):
		if self.ours and self.layout.code <= eip < self.layout.data:
			base = min(self.ours)
			return "ours+0x%X" % (eip - base)
		name = project.symbolAt(eip)
		if name:
			return name
		if self.image.contains(eip):
			sizes = project.functionSizes()
			best = max((a for a in sizes if a <= eip), default=None)
			if best is not None and eip < best + sizes[best]:
				return "%s+0x%X" % (project.symbolAt(best) or ("0x%08X" % best), eip - best)
			return "image+0x%X" % (eip - self.image.base)
		module = self.state.module(eip)
		return self.exports.name(module, eip) if module else "0x%08X" % eip
