"""Compare a function compiled into a COFF object with the original bytes of the engine DLL.

    python tools/objcmp.py OBJ SYMBOL ADDRESS [--version PROTOPC_2025] [--quiet]
    python tools/objcmp.py OBJ --list

The function is the whole COMDAT section of SYMBOL (compile with /Gy). Bytes covered by a relocation in the object
are compared as wildcards (they hold addresses the linker fills in); everything else must be identical. On an identical
function two more checks run: the values behind float-constant and string relocations (checkConstants), and where every
relocation against a symbol that symbols.txt places leads (checkTargets: the original's operand must reach the same
address, incremental-link thunks followed), so a call or global mapped to the wrong address is not a match. Prints the
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
		self.byIndex = {}  # raw symbol table index -> name, as relocations refer to symbols
		i = 0
		while i < nSymbols:
			at = symtab + 18 * i
			name, value, section, _, storage, aux = struct.unpack_from("<8sIhHBB", self.data, at)
			if name[:4] == b"\0\0\0\0":
				offset = struct.unpack_from("<I", name, 4)[0]
				name = self.data[strtab + offset:self.data.index(b"\0", strtab + offset)]
			self.symbols.append((name.rstrip(b"\0").decode("latin-1"), value, section, storage))
			self.byIndex[i] = self.symbols[-1][0]
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

	def relocations(self, symbol):
		"""[(offset in the function, target symbol name, type)] of a function's COMDAT section."""
		for name, value, section, storage in self.symbols:
			if name == symbol and section > 0:
				sec = self.sections[section - 1]
				return [(offset - value, self.byIndex.get(index, "?"), kind) for offset, index, kind in sec["relocs"]]
		raise KeyError(symbol)


def checkConstants(coff, symbol, original, image, base, known=None):
	"""Relocations against the compiler's __real@<hex> constants hide their values from the byte comparison; check
	that the original's operand points at the same value. Returns a list of mismatch descriptions.
	`known` maps symbol names to addresses (symbols.txt): a data word of ours that is itself relocated (a pointer)
	is checked against the address of the symbol it points at, when that symbol is known."""
	problems = []
	defined = {name: (value, section) for name, value, section, storage in coff.symbols if section > 0}
	for offset, name, kind in coff.relocations(symbol):
		if kind != 0x06:
			continue
		if name.startswith("__real@"):
			expected = int(name[7:], 16)
			width = 8 if len(name) - 7 > 8 else 4
		elif name.startswith("??_C@") and name in defined:
			# A string literal: compare the whole literal (its COMDAT section), terminator included
			value, section = defined[name]
			sec = coff.sections[section - 1]
			width = sec["size"] - value
			expected = int.from_bytes(coff.data[sec["raw"] + value:sec["raw"] + value + width], "little")
			if width == 1 and expected == 0:
				continue  # "": a developer message of the original's that the repository leaves out
		elif name in defined and not coff.sections[defined[name][1] - 1]["name"].startswith(".text"):
			# A constant of our own object (e.g. a namespace-scope const float): compare its first four bytes
			value, section = defined[name]
			sec = coff.sections[section - 1]
			if sec["raw"] == 0:
				continue  # uninitialised data
			pointer = [index for at, index, k in sec["relocs"] if at == value and k == 0x06]
			if pointer:
				target = coff.byIndex.get(pointer[0], "?")
				if not known or target not in known:
					continue  # a pointer to something we cannot place
				expected = known[target]
				width = 4
			else:
				# Only up to the next symbol or the end of the section: a static bool is one byte, its neighbours are not ours
				following = [v for n, v, s, st in coff.symbols if s == section and v > value]
				width = min(4, (min(following) if following else sec["size"]) - value)
				expected = int.from_bytes(coff.data[sec["raw"] + value:sec["raw"] + value + width], "little")
		else:
			continue
		target = struct.unpack_from("<I", original, offset)[0]
		at = target - base
		if not 0 <= at < len(image) - width:
			problems.append(f"+0x{offset:X}: {name} but the original points outside the image (0x{target:08X})")
			continue
		actual = int.from_bytes(image[at:at + width], "little")
		if actual != expected:
			problems.append(f"+0x{offset:X}: {name}, the original's 0x{target:08X} holds 0x{actual:0{2 * width}X}")
	return problems


def followThunks(image, base, address):
	"""The incremental link table holds `jmp rel32` thunks; follow up to two of them to the code they lead to."""
	for _ in range(2):
		at = address - base
		if not 0 <= at < len(image) - 5 or image[at] != 0xE9:
			break
		address = address + 5 + struct.unpack_from("<i", image, at + 1)[0]
	return address


def checkTargets(coff, symbol, original, address, image, base, known):
	"""Relocations are wildcards in the byte comparison; check where they lead. For every relocation against a symbol
	that symbols.txt places, the original's operand must lead to the same address (thunks followed on both sides).
	Symbols we cannot place (our own literals, statics, emitted vftables, unknown names) are skipped. Returns a list
	of mismatch descriptions."""
	problems = []
	defined = {name for name, value, section, storage in coff.symbols if section > 0}
	code, _ = coff.function(symbol)
	for offset, name, kind in coff.relocations(symbol):
		if kind not in (0x06, 0x14) or name not in known or offset < 0 or offset + 4 > len(original):
			continue
		if name.startswith(("__real@", "??_C@")):
			continue  # values, not places: checkConstants compares them
		inplace = struct.unpack_from("<i", code, offset)[0]
		expected = known[name] + inplace
		value = struct.unpack_from("<I", original, offset)[0]
		actual = value if kind == 0x06 else (address + offset + 4 + struct.unpack_from("<i", original, offset)[0]) & 0xFFFFFFFF
		if followThunks(image, base, expected) == followThunks(image, base, actual):
			continue
		if name in defined and followThunks(image, base, actual) == followThunks(image, base, known[name]):
			continue
		problems.append(f"+0x{offset:X}: {name} is 0x{expected:08X} in symbols.txt, the original's operand leads to "
			f"0x{actual:08X}")
	return problems


def loadSymbols(version):
	"""symbols.txt: one 'name = 0xADDRESS  ; comment' per line (as tools/delink/relink.py reads it)."""
	path = ROOT / "config" / version / "symbols.txt"
	symbols = {}
	if path.exists():
		for line in path.read_text(encoding="utf-8").splitlines():
			line = line.split(";", 1)[0].strip()
			if line:
				name, address = (part.strip() for part in line.rsplit("=", 1))
				symbols[name] = int(address, 16)
	return symbols


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
	known = loadSymbols(args.version) if ratio == 1.0 else None
	base = pe.OPTIONAL_HEADER.ImageBase
	problems = checkConstants(coff, args.symbol, original, image, base, known) if ratio == 1.0 else []
	targets = checkTargets(coff, args.symbol, original, address, image, base, known) if ratio == 1.0 else []
	if problems or targets:
		ratio = (len(code) - 1) / len(code)  # identical instructions, wrong constant or target: not a match
	print(f"{args.symbol} vs 0x{address:08X}: {len(code)} bytes, {ratio:.1%} identical (relocations as wildcards)"
		+ (f", {len(problems)} constant(s) differ" if problems else "")
		+ (f", {len(targets)} target(s) differ" if targets else ""))
	for problem in problems:
		print("  constant " + problem)
	for problem in targets:
		print("  target " + problem)
	if not args.quiet and ratio < 1.0:
		ours = [t for _, _, t in disassemble(code, address)]
		theirs = [t for _, _, t in disassemble(original, address)]
		for line in difflib.unified_diff(theirs, ours, "original", "ours", n=3, lineterm=""):
			print(line)
	sys.exit(0 if ratio == 1.0 else 1)


if __name__ == "__main__":
	main()
