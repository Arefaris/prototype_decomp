"""Cut the original functions of each unit out of the DLL as COFF objects: the "target" side of objdiff.

    python tools/delink/split.py UNITS.json [--version PROTOPC_2025] [--out build/PROTOPC_2025/target]

UNITS.json (written by configure.py): {"units": [{"name": "code/math/src/vector", "functions": [address, ...]}]}.
Each function becomes its own COMDAT .text section, as /Gy compiles it, holding the original bytes. Relocations:
- absolute values at the original's base relocation sites: against the function itself (jump tables), the __imp_
  symbol of an import, the symbols.txt name whose extent contains the value (with the offset in place), or a
  synthetic dat_XXXXXXXX / sub_XXXXXXXX name;
- rel32 calls and jumps that leave the function: against the callee's name; a call through the original's
  incremental link table is followed to the function the thunk jumps to, as our objects call it directly.
"""

import argparse
import bisect
import json
import pathlib
import struct
import sys

import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import coff  # noqa: E402
import relink  # noqa: E402

ROOT = pathlib.Path(__file__).resolve().parents[2]
BRANCHES = {"call", "jmp", "ja", "jae", "jb", "jbe", "je", "jne", "jg", "jge", "jl", "jle", "jo", "jno", "jp",
	"jnp", "js", "jns"}


def loadSymbolTable(version):
	"""symbols.txt with sizes: [(address, size, name)] sorted by address."""
	path = ROOT / "config" / version / "symbols.txt"
	table = []
	for line in path.read_text(encoding="utf-8").splitlines():
		body, _, comment = line.partition(";")
		body = body.strip()
		if not body:
			continue
		name, address = (part.strip() for part in body.rsplit("=", 1))
		size = 0
		for word in comment.split("|", 1)[0].split():
			if word.startswith("size:"):
				size = int(word[5:], 16)
		table.append((int(address, 16), size, name))
	table.sort()
	return table


class Original:
	def __init__(self, version):
		self.pe = pefile.PE(str(ROOT / "orig" / version / "prototypeenginef.dll"))
		self.base = self.pe.OPTIONAL_HEADER.ImageBase
		self.image = self.pe.get_memory_mapped_image()
		text = self.pe.sections[0]
		self.textStart = self.base + text.VirtualAddress
		self.textEnd = self.textStart + text.Misc_VirtualSize
		self.sites = sorted(self.base + e.rva for b in self.pe.DIRECTORY_ENTRY_BASERELOC for e in b.entries if e.type == 3)
		self.slots = {}
		for entry in self.pe.DIRECTORY_ENTRY_IMPORT:
			dllName = entry.dll.decode("latin-1")
			for imp in entry.imports:
				self.slots[imp.address] = relink.importSymbol(dllName, imp)[0]
		# The incremental link table: consecutive 5-byte "jmp rel32" thunks from the start of .text
		self.thunks = {}
		at = self.textStart
		while self.image[at - self.base] == 0xCC:
			at += 1
		while self.image[at - self.base] == 0xE9:
			self.thunks[at] = (at + 5 + struct.unpack_from("<i", self.image, at - self.base + 1)[0]) & 0xFFFFFFFF
			at += 5

	def u32(self, va):
		return struct.unpack_from("<I", self.image, va - self.base)[0]

	def bytes(self, va, size):
		return self.image[va - self.base:va - self.base + size]


class Namer:
	def __init__(self, original, table):
		self.original = original
		self.table = table
		self.starts = [entry[0] for entry in table]

	def resolve(self, va):
		"""(name, offset) for an address: a known symbol containing it, else a synthetic name."""
		va = self.original.thunks.get(va, va)
		i = bisect.bisect_right(self.starts, va) - 1
		if i >= 0:
			start, size, name = self.table[i]
			if va == start or start <= va < start + size:
				return name, va - start
		prefix = "sub" if self.original.textStart <= va < self.original.textEnd else "dat"
		return f"{prefix}_{va:08X}", 0


def buildUnit(original, namer, addresses, path):
	writer = coff.CoffWriter()
	byAddress = {entry[0]: entry for entry in namer.table}
	functions = []
	for address in addresses:
		if address not in byAddress or byAddress[address][1] == 0:
			raise SystemExit(f"0x{address:08X}: needs a symbols.txt entry with size:")
		_, size, name = byAddress[address]
		section = writer.addSection(".text", original.bytes(address, size),
			coff.IMAGE_SCN_CNT_CODE | coff.IMAGE_SCN_MEM_EXECUTE | coff.IMAGE_SCN_MEM_READ | coff.IMAGE_SCN_ALIGN_16BYTES | coff.IMAGE_SCN_LNK_COMDAT)
		section.selection = coff.IMAGE_COMDAT_SELECT_NODUPLICATES
		writer.sectionSymbol(section)
		symbol = writer.define(name, section, 0, function=True)
		functions.append((address, size, name, section, symbol))
	md = Cs(CS_ARCH_X86, CS_MODE_32)
	for address, size, name, section, symbol in functions:
		end = address + size
		first = bisect.bisect_left(original.sites, address)
		for site in original.sites[first:bisect.bisect_left(original.sites, end - 3)]:
			at = site - address
			value = original.u32(site)
			if address <= value < end:
				struct.pack_into("<I", section.data, at, value - address)
				section.relocations.append((at, symbol, coff.IMAGE_REL_I386_DIR32))
			elif value in original.slots:
				struct.pack_into("<I", section.data, at, 0)
				section.relocations.append((at, writer.external(original.slots[value]), coff.IMAGE_REL_I386_DIR32))
			else:
				target, offset = namer.resolve(value)
				struct.pack_into("<I", section.data, at, offset)
				section.relocations.append((at, writer.external(target), coff.IMAGE_REL_I386_DIR32))
		for insn in md.disasm(original.bytes(address, size), address):
			if insn.mnemonic not in BRANCHES or insn.size not in (5, 6) or not insn.op_str.startswith("0x"):
				continue
			destination = int(insn.op_str, 16)
			if address <= destination < end:
				continue
			at = insn.address + insn.size - 4 - address
			target, offset = namer.resolve(destination)
			struct.pack_into("<i", section.data, at, offset)
			section.relocations.append((at, writer.external(target), coff.IMAGE_REL_I386_REL32))
	path.parent.mkdir(parents=True, exist_ok=True)
	writer.write(path)


def main():
	parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
	parser.add_argument("units")
	parser.add_argument("--version", default="PROTOPC_2025")
	parser.add_argument("--out")
	args = parser.parse_args()
	out = pathlib.Path(args.out or ROOT / "build" / args.version / "target")
	units = json.loads(pathlib.Path(args.units).read_text(encoding="utf-8"))["units"]
	original = Original(args.version)
	namer = Namer(original, loadSymbolTable(args.version))
	for unit in units:
		buildUnit(original, namer, unit["functions"], out / (unit["name"] + ".obj"))
	print(f"{len(units)} target objects in {out} ({len(original.thunks)} incremental link thunks)")


if __name__ == "__main__":
	main()
