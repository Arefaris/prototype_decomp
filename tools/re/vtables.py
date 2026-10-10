"""Identifies the C++ objects around an address by their virtual function tables and MSVC RTTI names.

Every polymorphic object starts with a pointer to its vtable in prototypeenginef.dll's .rdata; the dword before the
vtable points to the RTTI complete object locator, whose type descriptor holds the decorated class name
(".?AVName@namespace@@"). Reading these names is observation of data, like reading strings.

	python tools/re/vtables.py near 0x269C4C10 [bytes]   # objects starting before an address, with the offset to it
	python tools/re/vtables.py find s8 ".?AVName@@"       # every live object of a class (scans a snapshot)
	python tools/re/vtables.py refs s8 0x26984130 [span]  # who points into [address, address + span): owners, statics
"""

import struct
import sys

import numpy as np

import probe

# prototypeenginef.dll loads at its preferred base; section ranges from its PE header
RDATA = (0x10D90000, 0x10D90000 + 0x25A15A)
DATA = (0x10FEB000, 0x10FEB000 + 0x267000)


def u32(handle, address):
	raw = probe.read(handle, address, 4)
	return None if raw is None or len(raw) < 4 else struct.unpack("<I", raw)[0]


def className(handle, vtable):
	"""Decorated RTTI name of the class whose vtable is at `vtable`, or None."""
	if not RDATA[0] <= vtable < RDATA[1]:
		return None
	locator = u32(handle, vtable - 4)
	if locator is None or not RDATA[0] <= locator < RDATA[1]:
		return None
	descriptor = u32(handle, locator + 12)
	if descriptor is None:
		return None
	raw = probe.read(handle, descriptor + 8, 128)
	if not raw or not raw.startswith(b".?A"):
		return None
	return raw.split(b"\0")[0].decode("ascii", "replace")


def near(target, span=0x4000):
	handle = probe.openProcess()
	start = target - span
	raw = probe.read(handle, start, span + 4)
	if raw is None:
		raise SystemExit("cannot read the memory before the target")
	words = np.frombuffer(raw[:len(raw) - len(raw) % 4], dtype="<u4")
	for index in range(len(words) - 1, -1, -1):
		name = className(handle, int(words[index]))
		if name:
			address = start + 4 * index
			print(f"0x{address:08X}  target at +0x{target - address:X}  vtable 0x{int(words[index]):08X}  {name}")


def find(snapshotName, wanted):
	"""Objects whose first dword is a vtable of the wanted class (any vtable with that RTTI name)."""
	handle = probe.openProcess()
	snapshot = probe.Snapshot(snapshotName)
	names = {}
	for base, size, offset in snapshot.table:
		words = np.frombuffer(snapshot.data[offset:offset + size - size % 4], dtype="<u4")
		candidates = np.nonzero((words >= RDATA[0]) & (words < RDATA[1]))[0]
		for index in candidates:
			vtable = int(words[index])
			if vtable not in names:
				names[vtable] = className(handle, vtable)
			if names[vtable] == wanted:
				print(f"0x{base + 4 * int(index):08X}  vtable 0x{vtable:08X}")


def owner(handle, address, reach=0x800):
	"""(object start, offset, class) of the nearest preceding object with an RTTI vtable."""
	for back in range(0, reach, 4):
		name = className(handle, u32(handle, address - back) or 0)
		if name:
			return address - back, back, name
	return None


def refs(snapshotName, target, span=0x40):
	handle = probe.openProcess()
	snapshot = probe.Snapshot(snapshotName)
	for base, size, offset in snapshot.table:
		words = np.frombuffer(snapshot.data[offset:offset + size - size % 4], dtype="<u4")
		for index in np.nonzero((words >= target) & (words < target + span))[0]:
			where = int(base) + 4 * int(index)
			value = int(words[index])
			static = f"engine .data +0x{where - 0x10000000:X}" if DATA[0] <= where < DATA[1] else ""
			found = owner(handle, where)
			label = f"{found[2]} +0x{found[1]:X} (object 0x{found[0]:08X})" if found else ""
			print(f"0x{where:08X} -> 0x{value:08X} (+0x{value - target:X})  {static} {label}")


if __name__ == "__main__":
	if len(sys.argv) > 2 and sys.argv[1] == "near":
		near(int(sys.argv[2], 16), int(sys.argv[3], 0) if len(sys.argv) > 3 else 0x4000)
	elif len(sys.argv) > 3 and sys.argv[1] == "find":
		find(sys.argv[2], sys.argv[3])
	elif len(sys.argv) > 3 and sys.argv[1] == "refs":
		refs(sys.argv[2], int(sys.argv[3], 16), int(sys.argv[4], 0) if len(sys.argv) > 4 else 0x40)
	else:
		print(__doc__)
