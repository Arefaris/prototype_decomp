"""Check the functions the relink puts in place of the engine's without an annotation ("kept copies").

	python tools/keptcheck.py [--version PROTOPC_2025] [--all]

A function our objects define (an inline member, a template instance, a compiler-generated destructor) that
symbols.txt maps replaces the engine's code at that address, exactly like an annotated one, but nothing compared
it: objcmp only sees annotated functions. A mapping by name alone can name the wrong address (a template instance
the engine inlined everywhere, its address taken by another function), and a definition of ours can differ from the
engine's under the same name (a constructor that hashes differently): either replaces engine code with something
else for every caller. Each such function is compared like objcmp does (relocations as wildcards, constants and
call/data targets checked); an incremental-link thunk at the mapped address is followed. A copy that differs but
was read and found to do the same is listed in config/<version>/keptcopies.txt with the reason. Exit status 1 when
an unlisted one differs. Needs build/<version>/relink/relink.json (`ninja dll`).
"""

import argparse
import json
import pathlib
import re
import struct
import sys

import pefile

ROOT = pathlib.Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import objcmp  # noqa: E402


def annotatedAddresses():
	"""Every address a `// FUNCTION: ENGINE` annotation names (objcmp checks those, or they are EQUIVALENT)."""
	result = set()
	for source in (ROOT / "src").rglob("*.c*"):
		for match in re.finditer(r"//\s*FUNCTION:\s*ENGINE\s+(0x[0-9A-Fa-f]+)", source.read_text(encoding="utf-8", errors="replace")):
			result.add(int(match.group(1), 16))
	return result


def definitions(version, names):
	"""{name: Coff} of the first object that defines each name in a code section."""
	result = {}
	for path in sorted((ROOT / "build" / version / "obj").rglob("*.obj")):
		coff = objcmp.Coff(path)
		for name, value, section, storage in coff.symbols:
			if section > 0 and name in names and name not in result \
					and coff.sections[section - 1]["name"].startswith(".text"):
				result[name] = (coff, path)
	return result


def main():
	parser = argparse.ArgumentParser()
	parser.add_argument("--version", default="PROTOPC_2025")
	parser.add_argument("--all", action="store_true", help="also list the matching ones")
	args = parser.parse_args()
	replaced = json.loads((ROOT / "build" / args.version / "relink" / "relink.json").read_text())["replaced"]
	annotated = annotatedAddresses()
	kept = {name: address for name, address in replaced.items() if address not in annotated}
	defs = definitions(args.version, set(kept))
	pe = pefile.PE(str(ROOT / "orig" / args.version / "prototypeenginef.dll"), fast_load=True)
	image = pe.get_memory_mapped_image()
	base = pe.OPTIONAL_HEADER.ImageBase
	known = objcmp.loadSymbols(args.version)
	listed = set()
	listing = ROOT / "config" / args.version / "keptcopies.txt"
	if listing.exists():
		for line in listing.read_text(encoding="utf-8").splitlines():
			if line.strip() and not line.startswith("#"):
				listed.add(line.split(";")[0].strip())
	checked = 0
	differing = 0
	for name, address in sorted(kept.items(), key=lambda item: item[1]):
		if name not in defs:
			continue
		coff, path = defs[name]
		try:
			code, mask = coff.function(name)
		except KeyError:
			continue
		target = address
		# the mapped address can be the incremental-link thunk (jmp rel32) in front of the function
		if image[target - base] == 0xE9 and code[:1] != b"\xe9":
			target = (target + 5 + struct.unpack_from("<i", image, target - base + 1)[0]) & 0xFFFFFFFF
		original = image[target - base:target - base + len(code)]
		same = sum(1 for k in range(len(code)) if mask[k] or code[k] == original[k])
		problems = []
		if same == len(code):
			problems = objcmp.checkConstants(coff, name, original, image, base, known) \
				+ objcmp.checkTargets(coff, name, original, target, image, base, known)
		checked += 1
		if (same < len(code) or problems) and name in listed:
			if args.all:
				print(f"  0x{address:08X} {same / len(code):6.1%} {len(code):5d}  {name}  (listed)")
		elif same < len(code) or problems:
			differing += 1
			print(f"  0x{address:08X} {same / len(code):6.1%} {len(code):5d}  {name}  ({path.name})")
			for problem in problems[:3]:
				print("      " + problem)
		elif args.all:
			print(f"  0x{address:08X} 100.0% {len(code):5d}  {name}")
	print(f"{checked} kept copies checked, {differing} differ from the engine's code at their address (not counting {len(listed)} listed)")
	sys.exit(1 if differing else 0)


if __name__ == "__main__":
	main()
