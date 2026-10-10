"""Pointer chains from the game's modules to a heap address (pointer scan), validated against the live process.

A chain [module+static] -> +a -> +b -> +c means: p = [module + static]; p = [p + a]; p = [p + b]; target = p + c.
Only chains that start in prototypeenginef.dll or prototypef.exe and still resolve to the target in the running
game are printed. Re-run `check` after reloading a save: chains through temporary objects break.

	python tools/re/pointers.py find s7 0x269C4C10 [levels] [maxOffset]
	python tools/re/pointers.py check                  # re-validate the saved chains, print their values
"""

import json
import struct
import sys

import numpy as np

import probe

ROOTS = ("prototypeenginef.dll", "prototypef.exe")
SAVED = probe.OUT / "chains.json"


def index(snapshot):
	"""All aligned dwords of the snapshot as (value, location), sorted by value."""
	values = []
	locations = []
	for base, size, offset in snapshot.table:
		words = np.frombuffer(snapshot.data[offset:offset + size - size % 4], dtype="<u4")
		values.append(words)
		locations.append(base + 4 * np.arange(len(words), dtype=np.int64))
	values = np.concatenate(values)
	locations = np.concatenate(locations)
	order = np.argsort(values, kind="stable")
	return values[order], locations[order]


def resolve(handle, root, offsets):
	address = root
	for offset in offsets[:-1]:
		raw = probe.read(handle, address, 4)
		if raw is None:
			return None
		address = struct.unpack("<I", raw)[0] + offset
	raw = probe.read(handle, address, 4)
	if raw is None:
		return None
	return struct.unpack("<I", raw)[0] + offsets[-1]


def find(name, target, levels=4, maxOffset=0x2000):
	snapshot = probe.Snapshot(name)
	values, locations = index(snapshot)
	images = {n.lower(): (b, b + s) for n, b, s in probe.modules()}
	roots = [images[r] for r in ROOTS if r in images]
	handle = probe.openProcess()

	# frontier: location -> offsets from that location's pointee down to the target
	frontier = {target: []}
	chains = []
	for level in range(levels):
		found = {}
		for wanted, offsets in frontier.items():
			low = np.searchsorted(values, max(wanted - maxOffset, 0), side="left")
			high = np.searchsorted(values, wanted, side="right")
			for value, where in zip(values[low:high], locations[low:high]):
				offset = wanted - int(value)
				if offset % 4:
					continue
				chain = [offset] + offsets
				if any(b <= where < e for b, e in roots):
					if resolve(handle, int(where), chain) == target:
						chains.append((int(where), chain))
				elif len(found) < 20000:
					found.setdefault(int(where), chain)
		frontier = found
		print(f"level {level + 1}: {len(frontier)} heap pointers, {len(chains)} valid chains")
	chains.sort(key=lambda c: (len(c[1]), c[1]))
	SAVED.write_text(json.dumps([{"root": r, "offsets": o} for r, o in chains], indent=1))
	for root, chain in chains[:40]:
		print(describe(root, chain, images))


def describe(root, chain, images):
	for name, (b, e) in images.items():
		if b <= root < e:
			return f"[{name}+0x{root - b:X}] " + " ".join(f"+0x{o:X}" for o in chain)
	return f"[0x{root:08X}] " + " ".join(f"+0x{o:X}" for o in chain)


def check():
	handle = probe.openProcess()
	images = {n.lower(): (b, b + s) for n, b, s in probe.modules()}
	chains = json.loads(SAVED.read_text())
	for entry in chains[:60]:
		address = resolve(handle, entry["root"], entry["offsets"])
		raw = probe.read(handle, address, 12) if address else None
		values = np.frombuffer(raw, dtype="<f4") if raw and len(raw) == 12 else None
		print(f"{describe(entry['root'], entry['offsets'], images):70} -> {values}")


if __name__ == "__main__":
	if len(sys.argv) > 2 and sys.argv[1] == "find":
		find(sys.argv[2], int(sys.argv[3], 16), *(int(v, 0) for v in sys.argv[4:6]))
	elif len(sys.argv) > 1 and sys.argv[1] == "check":
		check()
	else:
		print(__doc__)
