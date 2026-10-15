"""Check the vftables our objects define against the original's: slot count and the function of every slot.

    python tools/vtcheck.py [--version PROTOPC_2025] [--all]

A constructor that matches byte for byte still installs our vftable (its address is a relocation), so a missing
override or a slot in the wrong place passes the function comparison and breaks only the running game. The same
goes for the class key (struct / class): it is part of the RTTI type name that dynamic_cast compares. For every
`??_7<class>6B@` an object defines, the original vftable comes from the RTTI tables (config/<VERSION>/classes.tsv
and rtti.tsv); each slot's symbol must be mapped in symbols.txt to the original slot's function (or to the
incremental link thunk the original slot holds). An unmapped slot function is a problem too: the slot then leads to
our compiled copy, which nothing compared with the original. Exempt are `__purecall` where the original slot is pure
as well, and the compiler-generated deleting destructors (`??_E`, `??_G`); --all lists those as well.
"""

import argparse
import pathlib
import sys

import pefile

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
from objcmp import Coff

ROOT = pathlib.Path(__file__).resolve().parents[1]


def loadSymbols(version):
	symbols = {}
	for line in (ROOT / "config" / version / "symbols.txt").read_text(encoding="utf-8").splitlines():
		line = line.split(";", 1)[0].strip()
		if "=" in line:
			name, address = (part.strip() for part in line.split("=", 1))
			symbols[name] = int(address, 16)
	return symbols


def loadVftables(version):
	"""(decorated type name ".?AV...", offset of the vftable in the object) -> (vftable address, slot count)."""
	descriptors = {}
	for line in (ROOT / "config" / version / "classes.tsv").read_text(encoding="utf-8").splitlines()[1:]:
		fields = line.split("\t")
		descriptors[fields[2]] = fields[1]
	vftables = {}
	for line in (ROOT / "config" / version / "rtti.tsv").read_text(encoding="utf-8").splitlines()[1:]:
		address, slots, offset, name = line.split("\t")[:4]
		if name in descriptors:
			vftables[(descriptors[name], int(offset))] = (int(address, 16), int(slots))
	return vftables


def ourVftables(coff):
	"""[(vftable name, class part of the mangled name, offset in the object, [slot target symbol])] of the vftables
	an object defines; the offset is read from the vftable's complete object locator (??_R4...)."""
	defined = {name: (value, section) for name, value, section, storage in coff.symbols if section > 0}
	result = []
	for name, (value, section) in defined.items():
		if not name.startswith("??_7") or "@@6B" not in name:
			continue
		locator = defined.get("??_R4" + name[4:])
		if locator is None:
			continue
		sec = coff.sections[locator[1] - 1]
		offset = int.from_bytes(coff.data[sec["raw"] + locator[0] + 4:sec["raw"] + locator[0] + 8], "little")
		relocs = sorted((at, target) for at, target, kind in coff.relocations(name))
		slots = [target for at, target in relocs if at >= 0]
		result.append((name, name[4:name.index("@@6B") + 2], offset, slots))
	return result


def main():
	parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
	parser.add_argument("--version", default="PROTOPC_2025")
	parser.add_argument("--all", action="store_true", help="also report slots whose function is not mapped")
	args = parser.parse_args()

	pe = pefile.PE(str(ROOT / "orig" / args.version / "prototypeenginef.dll"), fast_load=True)
	base = pe.OPTIONAL_HEADER.ImageBase
	image = pe.get_memory_mapped_image()

	def u32(va):
		return int.from_bytes(image[va - base:va - base + 4], "little")

	def follow(va):
		"""The target of an incremental link thunk (jmp rel32), else va."""
		if image[va - base] == 0xE9:
			return (va + 5 + int.from_bytes(image[va - base + 1:va - base + 5], "little", signed=True)) & 0xFFFFFFFF
		return va

	symbols = loadSymbols(args.version)
	vftables = loadVftables(args.version)
	# the original's pure slots lead to its import stub of the CRT's _purecall (jmp dword ptr [import])
	pe.parse_data_directories(directories=[pefile.DIRECTORY_ENTRY["IMAGE_DIRECTORY_ENTRY_IMPORT"]])
	iat = next(imp.address for entry in pe.DIRECTORY_ENTRY_IMPORT for imp in entry.imports if imp.name == b"_purecall")
	purecall = base + bytes(image).find(b"\xff\x25" + iat.to_bytes(4, "little"))
	problems = 0
	seen = set()
	for path in sorted((ROOT / "build" / args.version / "obj").rglob("*.obj")):
		coff = Coff(path)
		names = set(name for name, value, section, storage in coff.symbols)
		for vftable, mangled, offset, slots in ourVftables(coff):
			if vftable in seen:
				continue
			seen.add(vftable)
			original = vftables.get((".?AV" + mangled, offset)) or vftables.get((".?AU" + mangled, offset))
			if original is None:
				continue
			address, count = original
			lines = []
			# The class key is part of the RTTI type name, and dynamic_cast compares type names: a class the
			# original declares as a struct (or the other way round) fails every cast from the game's code
			originalKey = "U" if (".?AU" + mangled, offset) in vftables else "V"
			ourKey = "U" if "??_R0?AU" + mangled + "@8" in names else "V"
			if ourKey != originalKey:
				kinds = {"U": "struct", "V": "class"}
				lines.append(f"  declared {kinds[ourKey]}, the original's RTTI says {kinds[originalKey]}")
			if len(slots) != count:
				lines.append(f"  {len(slots)} slots, the original has {count}")
			for i, target in enumerate(slots[:count]):
				slot = u32(address + 4 * i)
				mapped = symbols.get(target)
				if mapped is None:
					if target == "__purecall" and follow(slot) != purecall:
						lines.append(f"  [{i}] pure in ours, the original slot holds 0x{follow(slot):08X}")
					elif target == "__purecall" or target.startswith(("??_E", "??_G")):
						if args.all:
							lines.append(f"  [{i}] {target} is not mapped (original 0x{follow(slot):08X})")
					else:
						lines.append(f"  [{i}] {target} is not mapped: the slot leads to our copy, not to the original"
							f" 0x{follow(slot):08X}")
				elif mapped not in (slot, follow(slot)) and follow(mapped) != follow(slot):
					lines.append(f"  [{i}] {target} = 0x{mapped:08X}, the original slot holds 0x{follow(slot):08X}")
			if lines:
				problems += 1
				print(f"{vftable} (0x{address:08X}, {path.relative_to(ROOT)})")
				print("\n".join(lines))
	print(f"{len(seen)} vftables checked, {problems} with problems")
	sys.exit(1 if problems else 0)


if __name__ == "__main__":
	main()
