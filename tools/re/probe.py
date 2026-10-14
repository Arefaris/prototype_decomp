"""Memory probe for the running original (prototypef.exe), used to find Alex's and the camera's position.

Observation only: snapshots of the game's writable memory are compared while the player moves, the way memory
scanners work. Snapshots stay in the untracked local/probe/ folder.

	python tools/re/probe.py snap s0                  # snapshot of all writable memory
	python tools/re/probe.py scan s0                  # position-like float triples inside Manhattan
	python tools/re/probe.py moved s0 s1              # keep triples that moved horizontally between snapshots
	python tools/re/probe.py same s1 s2               # keep triples that did not change
	python tools/re/probe.py up s2 s3                 # keep triples whose height increased
	python tools/re/probe.py show                     # remaining candidates with their live values
	python tools/re/probe.py nudge 0x0D6236E8 3 0 0   # add to the triple at an address, then show which copies followed
	python tools/re/probe.py pointers s7 0x269C4C10   # pointer chains from module statics to an address (3 levels)
"""

import ctypes
import ctypes.wintypes as wt
import os
import pathlib
import sys

import numpy as np

PROCESS_NAME = "prototypef.exe"
OUT = pathlib.Path(__file__).resolve().parents[2] / "local" / "probe"
CANDIDATES = OUT / "candidates.npy"

# Manhattan in world coordinates (union of the 260 cell triggers), with a margin; streets are 15-25 m high
BOUNDS_X = (-2500.0, 2400.0)
BOUNDS_Y = (-20.0, 700.0)
BOUNDS_Z = (-2200.0, 1900.0)

PROCESS_QUERY_INFORMATION = 0x0400
PROCESS_VM_READ = 0x0010
PROCESS_VM_WRITE = 0x0020
PROCESS_VM_OPERATION = 0x0008
MEM_COMMIT = 0x1000
WRITABLE = {0x04, 0x08, 0x40, 0x80}
PAGE_GUARD = 0x100

kernel32 = ctypes.WinDLL("kernel32", use_last_error=True)


class MemoryInfo(ctypes.Structure):
	_fields_ = [
		("BaseAddress", ctypes.c_ulonglong),
		("AllocationBase", ctypes.c_ulonglong),
		("AllocationProtect", wt.DWORD),
		("PartitionId", wt.WORD),
		("RegionSize", ctypes.c_size_t),
		("State", wt.DWORD),
		("Protect", wt.DWORD),
		("Type", wt.DWORD),
	]


# Which copy of the game: the folder of its prototypef.exe (two copies can run at once, the lead's and the auditor's)
GAME_DIR = pathlib.Path(os.environ.get("OP_ORIGINAL_DIR", r"D:\SteamLibrary\steamapps\common\Prototype"))


def imagePath(pid):
	handle = kernel32.OpenProcess(0x1000, False, pid)  # PROCESS_QUERY_LIMITED_INFORMATION
	if not handle:
		return None
	try:
		size = wt.DWORD(1024)
		buffer = ctypes.create_unicode_buffer(size.value)
		if not kernel32.QueryFullProcessImageNameW(handle, 0, buffer, ctypes.byref(size)):
			return None
		return pathlib.Path(buffer.value)
	finally:
		kernel32.CloseHandle(handle)


def findProcess():
	"""The prototypef.exe started from GAME_DIR."""
	import subprocess
	out = subprocess.run(["tasklist", "/FI", f"IMAGENAME eq {PROCESS_NAME}", "/FO", "CSV", "/NH"], capture_output=True, text=True).stdout
	for line in out.splitlines():
		parts = [p.strip('"') for p in line.split('","')]
		if parts and parts[0].lower() == PROCESS_NAME:
			path = imagePath(int(parts[1]))
			if path is not None and path.parent.resolve() == GAME_DIR.resolve():
				return int(parts[1])
	raise SystemExit(f"{PROCESS_NAME} from {GAME_DIR} is not running")


def openProcess(write=False):
	access = PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | (PROCESS_VM_WRITE | PROCESS_VM_OPERATION if write else 0)
	handle = kernel32.OpenProcess(access, False, findProcess())
	if not handle:
		raise SystemExit(f"OpenProcess failed: {ctypes.get_last_error()}")
	return handle


def regions(handle):
	address = 0
	info = MemoryInfo()
	while address < 0x100000000:
		if not kernel32.VirtualQueryEx(ctypes.c_void_p(handle), ctypes.c_void_p(address), ctypes.byref(info), ctypes.sizeof(info)):
			break
		if info.State == MEM_COMMIT and (info.Protect & 0xFF) in WRITABLE and not info.Protect & PAGE_GUARD:
			yield info.BaseAddress, info.RegionSize
		address = info.BaseAddress + info.RegionSize


def read(handle, address, size):
	buffer = ctypes.create_string_buffer(size)
	done = ctypes.c_size_t()
	if not kernel32.ReadProcessMemory(ctypes.c_void_p(handle), ctypes.c_void_p(address), buffer, size, ctypes.byref(done)):
		return None
	return buffer.raw[:done.value]


def snap(name):
	OUT.mkdir(parents=True, exist_ok=True)
	handle = openProcess()
	table = []
	total = 0
	with open(OUT / f"{name}.bin", "wb") as data:
		for base, size in regions(handle):
			chunk = read(handle, base, size)
			if chunk is None:
				continue
			table.append((base, len(chunk), total))
			data.write(chunk)
			total += len(chunk)
	np.save(OUT / f"{name}.regions.npy", np.array(table, dtype=np.int64))
	print(f"{name}: {len(table)} regions, {total / 2**20:.0f} MiB")


class Snapshot:
	def __init__(self, name):
		self.table = np.load(OUT / f"{name}.regions.npy")
		self.data = np.memmap(OUT / f"{name}.bin", dtype=np.uint8, mode="r")

	def floats(self, addresses, count=3):
		"""Values of `count` floats at each address (NaN where the address is not in the snapshot)."""
		result = np.full((len(addresses), count), np.nan, dtype=np.float32)
		index = np.searchsorted(self.table[:, 0], addresses, side="right") - 1
		valid = index >= 0
		base = self.table[np.maximum(index, 0)]
		valid &= addresses + 4 * count <= base[:, 0] + base[:, 1]
		offsets = base[:, 2] + (addresses - base[:, 0])
		for k in range(count):
			raw = np.zeros(len(addresses), dtype=np.uint32)
			for b in range(4):
				raw |= self.data[np.where(valid, offsets + 4 * k + b, 0)].astype(np.uint32) << (8 * b)
			result[:, k] = np.where(valid, raw.view(np.float32), np.nan)
		return result


def inBounds(x, y, z):
	return (x > BOUNDS_X[0]) & (x < BOUNDS_X[1]) & (y > BOUNDS_Y[0]) & (y < BOUNDS_Y[1]) & (z > BOUNDS_Z[0]) & (z < BOUNDS_Z[1]) \
		& (np.abs(x) > 1.0) & (np.abs(z) > 1.0)


def scan(name):
	snapshot = Snapshot(name)
	found = []
	for base, size, offset in snapshot.table:
		values = np.frombuffer(snapshot.data[offset:offset + size - size % 4], dtype="<f4")
		if len(values) < 3:
			continue
		x, y, z = values[:-2], values[1:-1], values[2:]
		with np.errstate(invalid="ignore"):
			hits = np.nonzero(inBounds(x, y, z))[0]
		found.append(base + 4 * hits.astype(np.int64))
	candidates = np.concatenate(found) if found else np.zeros(0, dtype=np.int64)
	np.save(CANDIDATES, candidates)
	print(f"{len(candidates)} candidates")


def keep(before, after, rule):
	candidates = np.load(CANDIDATES)
	a = Snapshot(before).floats(candidates)
	b = Snapshot(after).floats(candidates)
	with np.errstate(invalid="ignore"):
		horizontal = np.hypot(b[:, 0] - a[:, 0], b[:, 2] - a[:, 2])
		rise = b[:, 1] - a[:, 1]
		mask = {
			"moved": (horizontal > 0.3) & (horizontal < 200.0) & (np.abs(rise) < 5.0),
			"same": (np.abs(b - a) < 1e-4).all(axis=1),
			"up": rise > 1.0,
			"down": rise < -1.0,
		}[rule] & inBounds(b[:, 0], b[:, 1], b[:, 2])
	np.save(CANDIDATES, candidates[mask])
	print(f"{rule}: {len(candidates)} -> {int(mask.sum())} candidates")


def show(limit=60):
	candidates = np.load(CANDIDATES)
	handle = openProcess()
	print(f"{len(candidates)} candidates")
	for address in candidates[:limit]:
		raw = read(handle, int(address), 12)
		values = np.frombuffer(raw, dtype="<f4") if raw and len(raw) == 12 else [np.nan] * 3
		print(f"  0x{int(address):08X}  {values[0]:10.3f} {values[1]:9.3f} {values[2]:10.3f}")


def nudge(address, delta):
	import time
	handle = openProcess(write=True)
	current = np.frombuffer(read(handle, address, 12), dtype="<f4")
	moved = (current + np.array(delta, dtype=np.float32)).astype("<f4").tobytes()
	written = ctypes.c_size_t()
	if not kernel32.WriteProcessMemory(ctypes.c_void_p(handle), ctypes.c_void_p(address), moved, 12, ctypes.byref(written)):
		raise SystemExit(f"WriteProcessMemory failed: {ctypes.get_last_error()}")
	print(f"0x{address:08X}: {current} -> {np.frombuffer(moved, dtype='<f4')}")
	time.sleep(1.0)
	show()


class ModuleEntry(ctypes.Structure):
	_fields_ = [
		("dwSize", wt.DWORD), ("th32ModuleID", wt.DWORD), ("th32ProcessID", wt.DWORD), ("GlblcntUsage", wt.DWORD),
		("ProccntUsage", wt.DWORD), ("modBaseAddr", ctypes.c_void_p), ("modBaseSize", wt.DWORD), ("hModule", wt.HMODULE),
		("szModule", ctypes.c_wchar * 256), ("szExePath", ctypes.c_wchar * 260),
	]


def modules():
	"""(name, base, size) of the 32-bit modules of the game"""
	snapshot = kernel32.CreateToolhelp32Snapshot(0x8 | 0x10, findProcess())
	entry = ModuleEntry()
	entry.dwSize = ctypes.sizeof(entry)
	result = []
	ok = kernel32.Module32FirstW(snapshot, ctypes.byref(entry))
	while ok:
		result.append((entry.szModule, entry.modBaseAddr or 0, entry.modBaseSize))
		ok = kernel32.Module32NextW(snapshot, ctypes.byref(entry))
	kernel32.CloseHandle(snapshot)
	return result


def pointers(name, target, maxOffset=0x1000, levels=3):
	"""Breadth-first search for dwords that point at most maxOffset below the target, up to module statics."""
	snapshot = Snapshot(name)
	words = []
	for base, size, offset in snapshot.table:
		values = np.frombuffer(snapshot.data[offset:offset + size - size % 4], dtype="<u4")
		words.append((base, values))
	images = [(n, b, b + s) for n, b, s in modules()]

	def module(address):
		for n, b, e in images:
			if b <= address < e:
				return f"{n}+0x{address - b:X}"
		return None

	frontier = {target: []}
	for level in range(levels):
		found = {}
		for wanted, chain in frontier.items():
			for base, values in words:
				hits = np.nonzero((values <= wanted) & (values >= wanted - maxOffset))[0]
				for hit in hits[:200]:
					where = base + 4 * int(hit)
					step = chain + [wanted - int(values[hit])]
					label = module(where)
					if label:
						print(f"level {level + 1}: [{label}] -> " + " -> ".join(f"+0x{o:X}" for o in reversed(step)))
					elif len(found) < 5000:
						found[where] = step
		frontier = found
		print(f"level {level + 1}: {len(frontier)} heap pointers")


def main(args):
	if not args:
		print(__doc__)
		return
	command = args[0]
	if command == "snap":
		snap(args[1])
	elif command == "scan":
		scan(args[1])
	elif command in ("moved", "same", "up", "down"):
		keep(args[1], args[2], command)
	elif command == "nudge":
		nudge(int(args[1], 16), [float(v) for v in args[2:5]])
	elif command == "pointers":
		pointers(args[1], int(args[2], 16))
	elif command == "show":
		show(int(args[1]) if len(args) > 1 else 60)
	else:
		print(__doc__)


if __name__ == "__main__":
	main(sys.argv[1:])
