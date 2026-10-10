"""Disassemble original functions by address (bounds from config/<VERSION>/functions.tsv), annotating constants.

    python tools/disasm.py 0x107CE3D0 [0x107CE460 ...] [--version PROTOPC_2025] [--bytes]

Absolute operands that point at data show the float / dword / string stored there; call targets show their
symbols.txt name, following incremental link thunks.
"""

import argparse
import bisect
import csv
import pathlib
import re
import struct
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = pathlib.Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools" / "delink"))
import split  # noqa: E402


def describe(original, namer, value):
	if original.textStart <= value < original.textEnd:
		name, offset = namer.resolve(value)
		return name + (f"+{offset:#x}" if offset else "")
	offset = value - original.base
	if not 0 <= offset < len(original.image) - 8:
		return None
	raw = original.image[offset:offset + 64]
	text = raw.split(b"\0", 1)[0]
	if len(text) >= 4 and all(32 <= c < 127 for c in text):
		return repr(text.decode())
	f = struct.unpack_from("<f", raw)[0]
	d = struct.unpack_from("<d", raw)[0]
	name, delta = namer.resolve(value)
	label = "" if name.startswith("dat_") else f"{name}{f'+{delta:#x}' if delta else ''} "
	return f"{label}[{struct.unpack_from('<I', raw)[0]:#010x} f={f:.9g} d={d:.6g}]"


def main():
	parser = argparse.ArgumentParser()
	parser.add_argument("addresses", nargs="+")
	parser.add_argument("--version", default="PROTOPC_2025")
	parser.add_argument("--bytes", action="store_true")
	args = parser.parse_args()
	original = split.Original(args.version)
	namer = split.Namer(original, split.loadSymbolTable(args.version))
	sizes = {}
	with open(ROOT / "config" / args.version / "functions.tsv", encoding="utf-8") as f:
		for row in csv.DictReader(f, delimiter="\t"):
			sizes[int(row["address"], 16)] = int(row["size"])
	md = Cs(CS_ARCH_X86, CS_MODE_32)
	for text in args.addresses:
		address = int(text, 16)
		size = sizes.get(address, 64)
		name, _ = namer.resolve(address)
		print(f"; {address:#010x} {name} ({size} bytes)")
		for insn in md.disasm(original.bytes(address, size), address):
			notes = []
			for m in re.finditer(r"0x([0-9a-f]{8})", insn.op_str):
				note = describe(original, namer, int(m.group(1), 16))
				if note:
					notes.append(note)
			raw = f"{insn.bytes.hex():24s} " if args.bytes else ""
			comment = f"  ; {', '.join(notes)}" if notes else ""
			print(f"  {insn.address:08x}  {raw}{insn.mnemonic:8s} {insn.op_str}{comment}")
		print()


if __name__ == "__main__":
	main()
