"""Captures real entry states from the running game (a 32-bit process, driven from 64-bit Python with ctypes).

No debugger is attached: the game's main thread is hidden from debuggers (an int3 it executes never reaches one
and ends the process instead). Instead the first five bytes of every requested function's entry are replaced by a
jump to its own spin stub in a page allocated in the game (`mov byte [flag], 1; pause; jmp back`): the thread that
enters a function parks there without touching its registers or flags. Every function is armed at once; the tool
polls the flags and, on a hit, suspends the whole process, reads the parked thread's registers
(Wow64GetThreadContext) and takes a state.

By default a state is taken live: while the process is frozen the engine's function and ours are run in the
emulator with pages fetched on demand from the process (ReadProcessMemory per 4 KiB page, cached), plus the
sentinel variants that fit a per-state freeze budget (`--freeze`). Only the pages those runs touched (and their
`--margin` neighbours) are saved. `--full` copies every committed page instead, as before.

The entry is then re-armed after `spacing` seconds until `wanted` hits are taken or `seconds` have passed.
`play` (gamectl commands) can drive the game meanwhile. Attach only to the copy in OP_ORIGINAL_DIR, in free roam.
"""

import ctypes
import ctypes.wintypes as wt
import os
import pathlib
import struct
import subprocess
import sys
import time

from . import project, store, cfg

kernel32 = ctypes.WinDLL("kernel32", use_last_error=True)
psapi = ctypes.WinDLL("psapi", use_last_error=True)
ntdll = ctypes.WinDLL("ntdll", use_last_error=True)

WOW64_CONTEXT_ALL = 0x0001003F
WOW64_CONTEXT_SIZE = 716
MEM_COMMIT = 0x1000
MEM_RESERVE = 0x2000
PAGE_NOACCESS = 0x01
PAGE_GUARD = 0x100
PAGE_EXECUTE_READWRITE = 0x40
LIST_MODULES_32BIT = 0x01
PROCESS_ALL_ACCESS = 0x1FFFFF
THREAD_ALL = 0x001F03FF
TH32CS_SNAPTHREAD = 0x04
JUMP = 5
STUB_STRIDE = 16


def clearStates(addresses):
	"""Removes every .state and .trim file under each address's state directory (used by --clear and --fresh)."""
	for address in addresses:
		removed = 0
		for path in sorted(project.stateDirectory(address).glob("*")):
			if path.suffix in (".state", ".trim"):
				print("0x%08X: removing %s" % (address, path.name))
				path.unlink()
				removed += 1
		if removed == 0:
			print("0x%08X: no states" % address)


def parkingIssues(address):
	"""Why the function at `address` cannot be parked, or None. Parking replaces the first five bytes with a
	jump, so the function must be at least five bytes long and no instruction in those five bytes may jump to a
	target inside them (a jump in from elsewhere could land mid-jump, and the parked thread is always restored to
	the entry)."""
	extent = project.functionExtent(address)
	if extent < JUMP:
		return "function is %d bytes, shorter than the 5-byte jump" % extent
	code = project.image().read(address, JUMP)
	for insn in cfg.disassemble(code, address):
		target = cfg.jumpTarget(insn)
		if target is not None and address <= target < address + JUMP:
			return "jump at 0x%08X lands inside the first 5 bytes (0x%08X)" % (insn.address, target)
	return None


class MemoryBasicInformation(ctypes.Structure):
	_fields_ = [("BaseAddress", ctypes.c_ulonglong), ("AllocationBase", ctypes.c_ulonglong), ("AllocationProtect", wt.DWORD),
		("PartitionId", wt.WORD), ("RegionSize", ctypes.c_size_t), ("State", wt.DWORD), ("Protect", wt.DWORD), ("Type", wt.DWORD)]


class ModuleInfo(ctypes.Structure):
	_fields_ = [("lpBaseOfDll", ctypes.c_void_p), ("SizeOfImage", wt.DWORD), ("EntryPoint", ctypes.c_void_p)]


class LdtEntry(ctypes.Structure):
	_fields_ = [("LimitLow", wt.WORD), ("BaseLow", wt.WORD), ("BaseMid", ctypes.c_ubyte), ("Flags1", ctypes.c_ubyte),
		("Flags2", ctypes.c_ubyte), ("BaseHi", ctypes.c_ubyte)]


class ThreadEntry(ctypes.Structure):
	_fields_ = [("dwSize", wt.DWORD), ("cntUsage", wt.DWORD), ("th32ThreadID", wt.DWORD), ("th32OwnerProcessID", wt.DWORD),
		("tpBasePri", wt.LONG), ("tpDeltaPri", wt.LONG), ("dwFlags", wt.DWORD)]


kernel32.ReadProcessMemory.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_void_p, ctypes.c_size_t, ctypes.POINTER(ctypes.c_size_t)]
kernel32.WriteProcessMemory.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_void_p, ctypes.c_size_t, ctypes.POINTER(ctypes.c_size_t)]
kernel32.VirtualQueryEx.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.POINTER(MemoryBasicInformation), ctypes.c_size_t]
kernel32.VirtualQueryEx.restype = ctypes.c_size_t
kernel32.VirtualAllocEx.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_size_t, wt.DWORD, wt.DWORD]
kernel32.VirtualAllocEx.restype = ctypes.c_void_p
kernel32.FlushInstructionCache.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_size_t]
kernel32.Wow64GetThreadContext.argtypes = [ctypes.c_void_p, ctypes.c_void_p]
kernel32.Wow64SetThreadContext.argtypes = [ctypes.c_void_p, ctypes.c_void_p]
kernel32.Wow64GetThreadSelectorEntry.argtypes = [ctypes.c_void_p, wt.DWORD, ctypes.POINTER(LdtEntry)]
kernel32.OpenProcess.restype = ctypes.c_void_p
kernel32.OpenProcess.argtypes = [wt.DWORD, wt.BOOL, wt.DWORD]
kernel32.OpenThread.restype = ctypes.c_void_p
kernel32.OpenThread.argtypes = [wt.DWORD, wt.BOOL, wt.DWORD]
kernel32.CreateToolhelp32Snapshot.restype = ctypes.c_void_p
kernel32.CloseHandle.argtypes = [ctypes.c_void_p]
kernel32.WaitForSingleObject.argtypes = [ctypes.c_void_p, wt.DWORD]
ntdll.NtSuspendProcess.argtypes = [ctypes.c_void_p]
ntdll.NtResumeProcess.argtypes = [ctypes.c_void_p]
psapi.EnumProcessModulesEx.argtypes = [ctypes.c_void_p, ctypes.c_void_p, wt.DWORD, ctypes.POINTER(wt.DWORD), wt.DWORD]
psapi.GetModuleFileNameExW.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_wchar_p, wt.DWORD]
psapi.GetModuleInformation.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.POINTER(ModuleInfo), wt.DWORD]

CONTEXT_FIELDS = {"edi": 156, "esi": 160, "ebx": 164, "edx": 168, "ecx": 172, "eax": 176, "ebp": 180, "eip": 184,
	"eflags": 192, "esp": 196}


def parseContext(raw):
	regs = {name: struct.unpack_from("<I", raw, offset)[0] for name, offset in CONTEXT_FIELDS.items()}
	regs["segfs"] = struct.unpack_from("<I", raw, 144)[0]
	regs["fpcw"] = struct.unpack_from("<I", raw, 28)[0] & 0xFFFF
	regs["fpsw"] = struct.unpack_from("<I", raw, 32)[0] & 0xFFFF
	ext = raw[204:204 + 512]
	regs["mxcsr"] = struct.unpack_from("<I", ext, 24)[0]
	regs["xmm"] = [ext[160 + 16 * i:176 + 16 * i].hex() for i in range(8)]
	return regs


def gamePid():
	sys.path.insert(0, str(project.ROOT / "tools" / "re"))
	import probe
	if not os.environ.get("OP_ORIGINAL_DIR"):
		raise SystemExit("set OP_ORIGINAL_DIR to the test copy the states are captured from (never the Steam folder)")
	return probe.findProcess(), probe.GAME_DIR


class Process:
	"""The game: memory, threads, modules; suspend and resume."""

	def __init__(self, pid):
		self.pid = pid
		self.handle = kernel32.OpenProcess(PROCESS_ALL_ACCESS, False, pid)
		if not self.handle:
			raise SystemExit("OpenProcess failed: %d" % ctypes.get_last_error())

	def alive(self):
		return kernel32.WaitForSingleObject(self.handle, 0) == 0x102

	def read(self, address, size):
		buffer = ctypes.create_string_buffer(size)
		got = ctypes.c_size_t(0)
		if not kernel32.ReadProcessMemory(self.handle, address, buffer, size, ctypes.byref(got)) or got.value != size:
			return None
		return buffer.raw

	def write(self, address, data):
		done = ctypes.c_size_t(0)
		ok = kernel32.WriteProcessMemory(self.handle, address, data, len(data), ctypes.byref(done))
		kernel32.FlushInstructionCache(self.handle, address, len(data))
		return bool(ok)

	def allocate(self, size):
		address = kernel32.VirtualAllocEx(self.handle, None, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE)
		if not address or address >= 0x100000000:
			raise SystemExit("VirtualAllocEx in the game failed: %d" % ctypes.get_last_error())
		return address

	def suspend(self):
		ntdll.NtSuspendProcess(self.handle)

	def resume(self):
		ntdll.NtResumeProcess(self.handle)

	def threads(self):
		"""{tid: handle} of the process's threads now (handles are closed by closeThreads)."""
		result = {}
		snapshot = kernel32.CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0)
		entry = ThreadEntry()
		entry.dwSize = ctypes.sizeof(entry)
		ok = kernel32.Thread32First(snapshot, ctypes.byref(entry))
		while ok:
			if entry.th32OwnerProcessID == self.pid:
				handle = kernel32.OpenThread(THREAD_ALL, False, entry.th32ThreadID)
				if handle:
					result[entry.th32ThreadID] = handle
			ok = kernel32.Thread32Next(snapshot, ctypes.byref(entry))
		kernel32.CloseHandle(snapshot)
		return result

	@staticmethod
	def closeThreads(threads):
		for handle in threads.values():
			kernel32.CloseHandle(handle)

	def context(self, thread):
		raw = ctypes.create_string_buffer(WOW64_CONTEXT_SIZE)
		struct.pack_into("<I", raw, 0, WOW64_CONTEXT_ALL)
		if not kernel32.Wow64GetThreadContext(thread, raw):
			return None
		return raw

	def setEip(self, thread, raw, eip):
		struct.pack_into("<I", raw, 184, eip)
		struct.pack_into("<I", raw, 0, WOW64_CONTEXT_ALL)
		if not kernel32.Wow64SetThreadContext(thread, raw):
			raise OSError("Wow64SetThreadContext failed: %d" % ctypes.get_last_error())

	def selectorBase(self, thread, selector):
		entry = LdtEntry()
		if not kernel32.Wow64GetThreadSelectorEntry(thread, selector, ctypes.byref(entry)):
			return 0
		return entry.BaseLow | (entry.BaseMid << 16) | (entry.BaseHi << 24)

	def modules(self):
		handles = (ctypes.c_void_p * 1024)()
		needed = wt.DWORD(0)
		if not psapi.EnumProcessModulesEx(self.handle, handles, ctypes.sizeof(handles), ctypes.byref(needed), LIST_MODULES_32BIT):
			return []
		result = []
		name = ctypes.create_unicode_buffer(1024)
		info = ModuleInfo()
		for i in range(min(needed.value // ctypes.sizeof(ctypes.c_void_p), 1024)):
			psapi.GetModuleFileNameExW(self.handle, handles[i], name, 1024)
			psapi.GetModuleInformation(self.handle, handles[i], ctypes.byref(info), ctypes.sizeof(info))
			result.append({"name": pathlib.Path(name.value).name, "path": name.value, "base": info.lpBaseOfDll or 0, "size": info.SizeOfImage})
		return sorted(result, key=lambda m: m["base"])

	def regions(self):
		"""Committed, readable regions below 4 GB: [(address, size)]."""
		result = []
		address = 0
		info = MemoryBasicInformation()
		while address < 0x100000000:
			if not kernel32.VirtualQueryEx(self.handle, address, ctypes.byref(info), ctypes.sizeof(info)):
				break
			size = info.RegionSize
			if info.State == MEM_COMMIT and not (info.Protect & PAGE_GUARD) and (info.Protect & 0xFF) != PAGE_NOACCESS:
				end = min(info.BaseAddress + size, 0x100000000)
				result.append((info.BaseAddress, end - info.BaseAddress))
			address = info.BaseAddress + size
		return result

	def snapshot(self, pageStore, address, thread, tid, patches):
		"""The parked thread's registers and the whole memory; `patches` {address: original bytes} hides the
		jumps still armed at other entries."""
		raw = self.context(thread)
		regs = parseContext(raw)
		regs["eip"] = address  # the thread is parked in the stub; its registers are the entry's
		fsBase = self.selectorBase(thread, regs["segfs"])
		header = store.newHeader(address, regs, tid, fsBase, self.modules(), bytes(raw))

		def reader(start, size):
			data = self.read(start, size)
			if data is None:
				return None
			touched = [a for a in patches if start < a + len(patches[a]) and a < start + size]
			if touched:
				data = bytearray(data)
				for a in touched:
					for k, byte in enumerate(patches[a]):
						if start <= a + k < start + size:
							data[a + k - start] = byte
			return data

		pages = store.snapshotRegions(pageStore, self.regions(), reader)
		pageStore.flush()
		return store.State(header, pages)


def captureLiveState(process, pageStore, address, handle, tid, patches, test, freeze, margin, verbose):
	"""Takes one state live: the process is suspended and the thread parked, so the engine's function and ours run
	in the emulator with pages fetched on demand from the frozen process; the pages they (and the sentinel variants
	that fit) touch are then the state, plus `margin` neighbours. The game stays frozen for at most `freeze`
	seconds; whatever ran up to then is saved and the rest replays offline (a page it needs and lacks is
	INCONCLUSIVE, never guessed)."""
	raw = process.context(handle)
	regs = parseContext(raw)
	regs["eip"] = address  # the thread is parked in the stub; its registers are the entry's
	fsBase = process.selectorBase(handle, regs["segfs"])
	header = store.newHeader(address, regs, tid, fsBase, process.modules(), bytes(raw))

	committed = set()
	for start, size in process.regions():
		for page in range(start & ~(project.PAGE - 1), (start + size + project.PAGE - 1) & ~(project.PAGE - 1), project.PAGE):
			committed.add(page)

	cache = {}

	def live(page):
		"""A page straight from the frozen process, with the still-armed jumps hidden, or None."""
		if page in cache:
			return cache[page]
		data = process.read(page, project.PAGE)
		if data is None or len(data) != project.PAGE:
			cache[page] = None
			return None
		touched = [a for a in patches if page < a + len(patches[a]) and a < page + project.PAGE]
		if touched:
			data = bytearray(data)
			for a in touched:
				for k, byte in enumerate(patches[a]):
					if page <= a + k < page + project.PAGE:
						data[a + k - page] = byte
			data = bytes(data)
		cache[page] = data
		return data

	liveState = store.State(header, {}, live=live, mappedPages=committed)
	deadline = time.time() + freeze
	result = test.runState(liveState, "live", deadline=deadline)
	machine = result.machine
	header["layout"] = machine.layout.asDict()
	if result.error is None:
		test.runVariants([result], [pathlib.Path("live")], set(), False, 240, deadline)
	pages = {}
	for page in sorted(machine.touched):
		for k in range(-margin, margin + 1):
			candidate = page + k * project.PAGE
			if candidate in pages:
				continue
			data = live(candidate)
			if data is not None:
				pages[candidate] = pageStore.put(bytes(data))
	pageStore.flush()
	if verbose:
		print("    live: %d touched pages -> %d saved pages (margin %d)" % (len(machine.touched), len(pages), margin))
	state = store.State(header, pages)
	state.liveInfo = {"touched": len(machine.touched), "saved": len(pages)}
	return state


class Breakpoints:
	"""Entry jumps to spin stubs in memory allocated in the game. One stub per function (16 bytes, `STUB_STRIDE`),
	then a page-aligned block of flag bytes the stubs set, so any number of functions fits."""

	def __init__(self, process, addresses):
		self.process = process
		self.addresses = list(addresses)
		stubBytes = len(self.addresses) * STUB_STRIDE
		self.flagsOffset = (stubBytes + 0xFFF) & ~0xFFF
		self.page = process.allocate(self.flagsOffset + len(self.addresses))
		self.originals = {}
		self.armed = set()
		code = bytearray()
		for i, address in enumerate(self.addresses):
			stub = self.page + STUB_STRIDE * i
			flag = self.page + self.flagsOffset + i
			# mov byte ptr [flag], 1 ; pause ; jmp pause
			piece = b"\xC6\x05" + struct.pack("<I", flag) + b"\x01" + b"\xF3\x90" + b"\xEB\xFC"
			code += piece + b"\xCC" * (STUB_STRIDE - len(piece))
			original = process.read(address, JUMP)
			if original is None:
				raise SystemExit("cannot read 0x%08X in the game" % address)
			self.originals[address] = original
		process.write(self.page, bytes(code))
		process.write(self.page + self.flagsOffset, bytes(len(self.addresses)))

	def stub(self, address):
		return self.page + STUB_STRIDE * self.addresses.index(address)

	def inStub(self, eip, address):
		stub = self.stub(address)
		return stub <= eip < stub + STUB_STRIDE

	def arm(self, address):
		"""Writes the jump while no thread is inside the bytes it replaces; False when one is (try again later)."""
		if address in self.armed:
			return True
		self.process.suspend()
		try:
			threads = self.process.threads()
			try:
				for handle in threads.values():
					raw = self.process.context(handle)
					if raw is not None and address <= struct.unpack_from("<I", raw, 184)[0] < address + JUMP:
						return False
			finally:
				self.process.closeThreads(threads)
			jump = b"\xE9" + struct.pack("<i", self.stub(address) - (address + JUMP))
			self.process.write(address, jump)
			self.armed.add(address)
			return True
		finally:
			self.process.resume()

	def disarm(self, address):
		if address in self.armed:
			self.process.write(address, self.originals[address])
			self.armed.discard(address)

	def flags(self):
		data = self.process.read(self.page + self.flagsOffset, len(self.addresses))
		return [self.addresses[i] for i, byte in enumerate(data or b"") if byte]

	def clearFlag(self, address):
		self.process.write(self.page + self.flagsOffset + self.addresses.index(address), b"\x00")

	def parked(self, address, threads):
		"""[(tid, handle, context)] of the threads spinning in this entry's stub (the process is suspended)."""
		result = []
		for tid, handle in threads.items():
			raw = self.process.context(handle)
			if raw is not None and self.inStub(struct.unpack_from("<I", raw, 184)[0], address):
				result.append((tid, handle, raw))
		return result

	def release(self, address, threads):
		"""Restores the entry and sends every thread parked at it back to the function's first instruction."""
		self.disarm(address)
		for tid, handle, raw in self.parked(address, threads):
			self.process.setEip(handle, raw, address)
		self.clearFlag(address)

	def disarmAll(self):
		self.process.suspend()
		try:
			threads = self.process.threads()
			try:
				for address in list(self.addresses):
					self.release(address, threads)
			finally:
				self.process.closeThreads(threads)
		finally:
			self.process.resume()


def capture(addresses, wanted=3, seconds=30.0, spacing=1.0, play=None, verbose=True, full=False, obj=None,
		symbol=None, unit=False, budget=5000000, timeout=20.0, freeze=3.0, margin=1, fresh=False):
	"""Captures up to `wanted` states for each address; returns {address: [state paths]}. Every address is armed
	at once and a state is taken live (the emulator fetches pages from the frozen process on demand and saves only
	the pages its runs touched) unless `full` copies the whole memory. `fresh` removes each address's existing
	states first, so the capture is indexed from 000 again. `play` is a list of gamectl commands
	("keys w:2.5,:2", "teleport 1000 20 -500") run one after another once the entries are armed, to drive the game
	onto the paths wanted."""
	deadline = time.time() + seconds
	parkable = []
	for address in addresses:
		issue = parkingIssues(address)
		if issue:
			print("0x%08X: cannot park (%s); skipped" % (address, issue))
		else:
			parkable.append(address)
	if not parkable:
		raise SystemExit("none of the requested functions can be parked")
	pageStore = store.PageStore()
	# the tests (our objects, the engine's blocks) before the game: the start-up runs the loaders within seconds
	# of the DLL being mapped, and every entry has to be armed by then
	tests = {}
	if not full:
		from difftest.difftest import FunctionTest
		for address in parkable:
			tests[address] = FunctionTest(address, obj, symbol, unit, budget, timeout, pageStore)
	# the game may still be starting (to capture its start-up, run this first and launch the game meanwhile): wait
	# for the process, then for the engine DLL to be mapped
	while True:
		try:
			pid, gameDir = gamePid()
			break
		except SystemExit:
			if time.time() > deadline:
				raise
			time.sleep(0.05)
	process = Process(pid)
	while process.read(parkable[0], JUMP) is None:
		if time.time() > deadline or not process.alive():
			pageStore.close()
			raise SystemExit("the engine DLL is not mapped in the game")
		time.sleep(0.01)
	if fresh:
		clearStates(parkable)
	breakpoints = Breakpoints(process, parkable)
	hits = {a: 0 for a in parkable}
	armAt = {a: 0.0 for a in parkable}
	saved = {a: [] for a in parkable}
	existing = {a: len(project.listStates(a)) for a in parkable}
	player = None
	try:
		for address in parkable:
			if not breakpoints.arm(address):
				armAt[address] = time.time() + 0.05
		if play:
			script = " & ".join("%s %s %s" % (sys.executable, project.ROOT / "tools" / "re" / "gamectl.py", command) for command in play)
			player = subprocess.Popen(["cmd", "/c", script], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
		while time.time() < deadline:
			if all(hits[a] >= wanted for a in parkable):
				break
			if not process.alive():
				print("the game ended")
				break
			now = time.time()
			for address, when in armAt.items():
				if when and now >= when and hits[address] < wanted:
					armAt[address] = 0.0 if breakpoints.arm(address) else now + 0.05
			flagged = breakpoints.flags()
			if not flagged:
				time.sleep(0.002)
				continue
			process.suspend()
			try:
				threads = process.threads()
				try:
					for address in flagged:
						parked = breakpoints.parked(address, threads)
						if parked and hits[address] < wanted:
							tid, handle, raw = parked[0]
							t0 = time.time()
							patches = {a: breakpoints.originals[a] for a in breakpoints.armed}
							if full:
								state = process.snapshot(pageStore, address, handle, tid, patches)
							else:
								state = captureLiveState(process, pageStore, address, handle, tid, patches,
									tests[address], freeze, margin, verbose)
							index = existing[address] + hits[address]
							path = project.stateDirectory(address) / ("%03d.state" % index)
							state.save(path)
							saved[address].append(path)
							hits[address] += 1
							if verbose:
								live = getattr(state, "liveInfo", None)
								print("0x%08X hit %d: %s (%d pages, %.2f s%s)" % (address, hits[address],
									state.describe(), len(state.pages), time.time() - t0,
									", live %d touched" % live["touched"] if live else ""))
							if hits[address] < wanted:
								armAt[address] = time.time() + spacing
						breakpoints.release(address, threads)
				finally:
					process.closeThreads(threads)
			finally:
				process.resume()
	finally:
		if process.alive():
			breakpoints.disarmAll()
		pageStore.close()
		if player is not None:
			player.wait()
	for address in parkable:
		if hits[address] == 0 and verbose:
			print("0x%08X: not reached in %.0f s" % (address, seconds))
	return saved
