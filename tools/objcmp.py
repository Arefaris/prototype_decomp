"""Compare a function compiled into a COFF object with the original bytes of the engine DLL.

    python tools/objcmp.py OBJ SYMBOL ADDRESS [--version PROTOPC_2025] [--quiet]
    python tools/objcmp.py OBJ --list

The function is the whole COMDAT section of SYMBOL (compile with /Gy). Bytes covered by a relocation in the object
are compared as wildcards (they hold addresses the linker fills in); everything else must be identical. Prints the
match ratio and, unless --quiet, both disassemblies side by side with the differing lines marked.
A quick check for spikes; objdiff is the project's real diff tool.
"""

import argparse
import difflib
import pathlib
import struct
import sys

import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = pathlib.Path(__file__).resolve().parents[1]


class Coff:
	def __init__(self, path):
		self.data = pathlib.Path(path).read_bytes()
		(self.machine, nSections, _, symtab, nSymbols, optSize, _) = struct.unpack_from("<HHIIIHH", self.data, 0)
		self.sections = []
		for i in range(nSections):
			at = 20 + optSize + 40 * i
			name, _, _, size, raw, relocs, _, nRelocs, _, flags = struct.unpack_from("<8sIIIIIIHHI", self.data, at)
			self.sections.append({"name": name.rstrip(b"\0").decode("latin-1"), "size": size, "raw": raw,
				"relocs": [struct.unpack_from("<IIH", self.data, relocs + 10 * r) for r in range(nRelocs)]})
		strtab = symtab + 18 * nSymbols
		self.symbols = []
		i = 0
		while i < nSymbols:
			at = symtab + 18 * i
			name, value, section, _, storage, aux = struct.unpack_from("<8sIhHBB", self.data, at)
			if name[:4] == b"\0\0\0\0":
				offset = struct.unpack_from("<I", name, 4)[0]
				name = self.data[strtab + offset:self.data.index(b"\0", strtab + offset)]
			self.symbols.append((name.rstrip(b"\0").decode("latin-1"), value, section, storage))
			i += 1 + aux

	def function(self, symbol):
		for name, value, section, storage in self.symbols:
			if name == symbol and section > 0:
				sec = self.sections[section - 1]
				code = self.data[sec["raw"] + value:sec["raw"] + sec["size"]]
				mask = bytearray(len(code))
				for offset, _, kind in sec["relocs"]:
					for k in range(4):
						if 0 <= offset - value + k < len(mask):
							mask[offset - value + k] = 1
				return code, mask
		raise KeyError(symbol)


def disassemble(code, address):
	md = Cs(CS_ARCH_X86, CS_MODE_32)
	return [(i.address, i.size, f"{i.mnemonic} {i.op_str}") for i in md.disasm(code, address)]


def main():
	parser = argparse.ArgumentParser()
	parser.add_argument("obj")
	parser.add_argument("symbol", nargs="?")
	parser.add_argument("address", nargs="?")
	parser.add_argument("--version", default="PROTOPC_2025")
	parser.add_argument("--list", action="store_true")
	parser.add_argument("--quiet", action="store_true")
	args = parser.parse_args()
	coff = Coff(args.obj)
	if args.list:
		for name, value, section, storage in coff.symbols:
			if section > 0 and storage == 2 and coff.sections[section - 1]["name"].startswith(".text"):
				print(f"{coff.sections[section - 1]['size'] - value:6d}  {name}")
		return
	code, mask = coff.function(args.symbol)
	address = int(args.address, 16)
	pe = pefile.PE(str(ROOT / "orig" / args.version / "prototypeenginef.dll"), fast_load=True)
	image = pe.get_memory_mapped_image()
	start = address - pe.OPTIONAL_HEADER.ImageBase
	original = image[start:start + len(code)]
	same = sum(1 for k in range(len(code)) if mask[k] or code[k] == original[k])
	ratio = same / len(code)
	print(f"{args.symbol} vs 0x{address:08X}: {len(code)} bytes, {ratio:.1%} identical (relocations as wildcards)")
	if not args.quiet and ratio < 1.0:
		ours = [t for _, _, t in disassemble(code, address)]
		theirs = [t for _, _, t in disassemble(original, address)]
		for line in difflib.unified_diff(theirs, ours, "original", "ours", n=3, lineterm=""):
			print(line)
	sys.exit(0 if ratio == 1.0 else 1)


if __name__ == "__main__":
	main()
