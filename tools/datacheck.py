"""Check the data objects our units define for the engine (globals and statics mapped in symbols.txt).

    python tools/datacheck.py [--version PROTOPC_2025] [OBJ ...]

A data symbol that one of our objects defines and symbols.txt maps to an address replaces the original's object: the
relink redirects every reference to it (and, for objects with a size, every reference inside it) to our copy. So
our copy must start out exactly like the original's and be as large as symbols.txt says. For each such symbol:
- the initial bytes (.data) or zeros (.bss) must equal the original image's bytes over the object's size;
- symbols.txt must give the size (`; data size:0xN`), else references inside the object are not redirected;
- our object's extent in its section (up to the next symbol) must not be smaller than that size.
Objects with a dynamic initializer (a constructor) start as zeros here; their constructors run at start-up, so a
difference is reported as a note when the original's bytes are not all zero either. Exit status 1 on any problem.
"""

import argparse
import pathlib
import re
import sys

import pefile

ROOT = pathlib.Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import objcmp  # noqa: E402


def loadData(version):
	"""{name: (address, size or None)} for the data lines of symbols.txt."""
	data = {}
	for line in (ROOT / "config" / version / "symbols.txt").read_text(encoding="utf-8").splitlines():
		match = re.match(r"\s*(\S+)\s*=\s*(0x[0-9A-Fa-f]+)\s*;\s*data\b(?:\s+size:(0x[0-9A-Fa-f]+|\d+))?", line)
		if match:
			data[match.group(1)] = (int(match.group(2), 16), int(match.group(3), 0) if match.group(3) else None)
	return data


def objects(version):
	"""The compiled objects of the build (build/<version>/obj/**/*.obj)."""
	return sorted((ROOT / "build" / version / "obj").rglob("*.obj"))


def main():
	parser = argparse.ArgumentParser()
	parser.add_argument("objects", nargs="*")
	parser.add_argument("--version", default="PROTOPC_2025")
	args = parser.parse_args()
	data = loadData(args.version)
	pe = pefile.PE(str(ROOT / "orig" / args.version / "prototypeenginef.dll"), fast_load=True)
	image = pe.get_memory_mapped_image()
	base = pe.OPTIONAL_HEADER.ImageBase
	problems = 0
	checked = 0
	for path in [pathlib.Path(o) for o in args.objects] or objects(args.version):
		coff = objcmp.Coff(path)
		for name, value, section, storage in coff.symbols:
			if section <= 0 or name not in data or storage != 2:
				continue
			sec = coff.sections[section - 1]
			if sec["name"].startswith(".text"):
				continue
			address, size = data[name]
			checked += 1
			where = f"{name} (0x{address:08X}, {path.name})"
			following = [v for n, v, s, st in coff.symbols if s == section and v > value]
			extent = (min(following) if following else sec["size"]) - value
			if size is None:
				# a scalar has no inside to refer to; a struct or array without a size does (RTTI type descriptors are
				# only ever referred to at their start)
				if extent > 4 and not name.startswith("??_R"):
					problems += 1
					print(f"  no size: {where}: our object spans 0x{extent:X} bytes; give `data size:0xN` in symbols.txt"
						" so references inside it reach our copy")
					continue
				size = min(extent, 4)
			if extent < size:
				problems += 1
				print(f"  too small: {where}: our object spans 0x{extent:X} bytes, symbols.txt says 0x{size:X}")
			ours = bytes(coff.data[sec["raw"] + value:sec["raw"] + value + size]) if sec["raw"] else bytes(size)
			ours = ours.ljust(size, b"\0")
			theirs = bytes(image[address - base:address - base + size])
			if ours != theirs:
				# relocated words (pointers to other objects) cannot be compared byte for byte; skip them
				relocated = {o - value for o, _, _ in sec["relocs"] if value <= o < value + size}
				differing = [k for k in range(size) if ours[k] != theirs[k] and not any(r <= k < r + 4 for r in relocated)]
				if differing:
					problems += 1
					k = differing[0]
					print(f"  initial value: {where}: ours {ours[k:k + 8].hex()} vs the original's {theirs[k:k + 8].hex()}"
						f" at +0x{k:X} ({len(differing)} bytes differ)")
	print(f"{checked} data objects checked, {problems} problems")
	sys.exit(1 if problems else 0)


if __name__ == "__main__":
	main()
