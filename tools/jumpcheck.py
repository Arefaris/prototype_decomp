"""Compares the jump tables of our functions with the engine's.

objcmp treats relocations as wildcards, and the entries of a switch's jump table are relocations to labels of the
function itself: a function whose cases lead to the wrong blocks compares as 100 % identical. For every function our
objects define and symbols.txt maps, this reads each relocation that points to a label of the function's own section,
takes the label's offset from the function's start, and compares it with the engine's table entry at the same place.

	python tools/jumpcheck.py [--version PROTOPC_2025]
"""

import argparse
import pathlib
import re
import struct
import sys

import pefile

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent / "delink"))
from objcmp import Coff  # noqa: E402
from relink import equivalentAddresses, nonmatchingAddresses  # noqa: E402

ROOT = pathlib.Path(__file__).resolve().parents[1]
IMAGE_REL_I386_DIR32 = 6


def loadSymbols(version):
	symbols = {}
	for line in (ROOT / "config" / version / "symbols.txt").read_text(encoding="utf-8").splitlines():
		match = re.match(r"(\S+) = (0x[0-9A-Fa-f]+) ; function", line)
		if match:
			symbols[match.group(1)] = int(match.group(2), 16)
	return symbols


def main():
	parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
	parser.add_argument("--version", default="PROTOPC_2025")
	args = parser.parse_args()

	pe = pefile.PE(str(ROOT / "orig" / args.version / "prototypeenginef.dll"), fast_load=True)
	base = pe.OPTIONAL_HEADER.ImageBase
	image = pe.get_memory_mapped_image()
	symbols = loadSymbols(args.version)
	# only the functions that count as matching: an EQUIVALENT one is laid out differently on purpose
	skipped = equivalentAddresses() | nonmatchingAddresses()

	checked = 0
	problems = 0
	for path in sorted((ROOT / "build" / args.version / "obj").rglob("*.obj")):
		coff = Coff(path)
		bySection = {}
		for name, value, section, storage in coff.symbols:
			if section > 0:
				bySection.setdefault(section, []).append((name, value))
		for name, value, section, storage in coff.symbols:
			address = symbols.get(name)
			if address is None or section <= 0 or address in skipped:
				continue
			sec = coff.sections[section - 1]
			labels = {n: v for n, v in bySection.get(section, [])}
			for offset, symbolIndex, kind in sec["relocs"]:
				if kind != IMAGE_REL_I386_DIR32 or offset < value:
					continue
				target = coff.byIndex.get(symbolIndex)
				if target not in labels or not target.startswith("$"):
					continue
				ours = labels[target] - value
				engineEntry = struct.unpack_from("<I", image, address + offset - value - base)[0]
				theirs = engineEntry - address
				checked += 1
				if ours != theirs:
					problems += 1
					print(f"{path.relative_to(ROOT)}: {name} (0x{address:08X}) +0x{offset - value:X}: our entry leads to "
						f"+0x{ours:X}, the engine's to +0x{theirs:X}")
	print(f"{checked} jump table entries checked, {problems} lead elsewhere than the engine's")
	return 1 if problems else 0


if __name__ == "__main__":
	sys.exit(main())
