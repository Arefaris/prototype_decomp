"""Check the data objects our units define for the engine (globals and statics mapped in symbols.txt).

    python tools/datacheck.py [--version PROTOPC_2025] [OBJ ...]

A data symbol that one of our objects defines and symbols.txt maps to an address replaces the original's object: the
relink redirects every reference to it (and, for objects with a size, every reference inside it) to our copy. So
our copy must start out exactly like the original's and be as large as symbols.txt says. For each such symbol:
- the initial bytes (.data) or zeros (.bss) must equal the original image's bytes over the object's size;
- symbols.txt must give the size (`; data size:0xN`), else references inside the object are not redirected;
- our object's extent in its section (up to the next symbol) must not be smaller than that size.
Objects with a dynamic initializer (a constructor) start as zeros here; their constructors run at start-up, so a
difference is reported as a note when the original's bytes are not all zero either. Also reported: a `static` engine
global that engine code we do not replace uses (split statics), and an RTTI type descriptor our objects define that
symbols.txt does not map although the original has one (our copy is a second type_info, which code comparing
type_info addresses does not recognise) or that the original only has with the other of struct/class, and a global our
objects define that symbols.txt does not map at all (a second copy of the engine's state). Exit status 1 on any
problem.
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


def splitStatics(image, base, pe):
	"""[(where, declaration, engine functions)] for each `// GLOBAL: ENGINE 0x...` above a `static` variable that a
	function we do not compile (not annotated, or NONMATCHING) also references: a static has internal linkage, so the
	relink cannot map it, and our code and the engine's then keep two copies of the state."""
	import bisect
	import struct
	starts, compiled = [], set()
	for line in (ROOT / "config" / "PROTOPC_2025" / "functions.tsv").read_text(encoding="utf-8").splitlines()[1:]:
		parts = line.split("\t")
		if parts and parts[0].startswith("0x"):
			starts.append(int(parts[0], 16))
	starts.sort()
	statics = []
	for source in (ROOT / "src").rglob("*.c*"):
		lines = source.read_text(encoding="utf-8", errors="replace").splitlines()
		for i, line in enumerate(lines):
			match = re.search(r"//\s*FUNCTION:\s*ENGINE\s+(0x[0-9A-Fa-f]+)", line)
			if match and not any("NONMATCHING" in x for x in lines[i + 1:i + 4] if x.strip().startswith("//")):
				compiled.add(int(match.group(1), 16))
			match = re.search(r"//\s*GLOBAL:\s*ENGINE\s+(0x[0-9A-Fa-f]+)", line)
			if match and i + 1 < len(lines) and lines[i + 1].strip().startswith("static ") \
					and "(" not in lines[i + 1].split("=")[0]:
				statics.append((int(match.group(1), 16), f"{source.relative_to(ROOT)}:{i + 2}", lines[i + 1].strip()))
	text = next(s for s in pe.sections if s.Name.rstrip(b"\0") == b".text")
	code = bytes(image[text.VirtualAddress:text.VirtualAddress + text.Misc_VirtualSize])
	result = []
	for address, where, decl in statics:
		needle = struct.pack("<I", address)
		users = set()
		j = code.find(needle)
		while j != -1:
			k = bisect.bisect_right(starts, base + text.VirtualAddress + j) - 1
			if k >= 0 and starts[k] not in compiled:
				users.add(starts[k])
			j = code.find(needle, j + 1)
		if users:
			result.append((where, decl, sorted(users)))
	return result


def typeDescriptors(image, base, data):
	"""{decorated type name: address} of the original's RTTI type descriptors (a type_info vftable pointer, a spare
	word, then the name `.?AV...` / `.?AU...`), found through the type_info vftable of a mapped descriptor."""
	import struct
	known = next((a for n, (a, s) in data.items() if n.startswith("??_R0?AV")), None)
	if known is None:
		return {}
	vftable = struct.pack("<I", struct.unpack_from("<I", image, known - base)[0])
	result = {}
	j = image.find(vftable)
	while j != -1:
		if image[j + 8:j + 11] in (b".?A", b".PB", b".PA"):
			end = image.find(b"\0", j + 8)
			result[image[j + 9:end].decode("latin-1")] = base + j
		j = image.find(vftable, j + 4)
	return result


def unmappedTypeDescriptors(objectPaths, data, image, base):
	"""[(name, problem)] for each RTTI type descriptor our objects define that symbols.txt does not map: our copy is
	a second type_info, so code that compares type_info addresses (the script wrappers' Function::GetTypeCode) does
	not recognise the type. A name the original only has with the other of struct/class means the declaration uses
	the wrong keyword."""
	engine = typeDescriptors(bytes(image), base, data)
	ours = set()
	for path in objectPaths:
		for name, value, section, storage in objcmp.Coff(path).symbols:
			if name.startswith("??_R0") and section > 0 and name not in data:
				ours.add(name)
	result = []
	for name in sorted(ours):
		typeName = name[5:-2]
		if typeName in engine:
			result.append((name, f"the original's is at 0x{engine[typeName]:08X}; map it in symbols.txt"))
		elif typeName[:3] in ("?AU", "?AV"):
			other = typeName[:2] + ("V" if typeName[2] == "U" else "U") + typeName[3:]
			if other in engine:
				keyword = "class" if other[2] == "V" else "struct"
				result.append((name, f"the original's type is a {keyword} (0x{engine[other]:08X}); declare it {keyword}"))
	return result


def unmappedGlobals(objectPaths, version):
	"""[(name, object)] for each external data symbol our objects define in .data / .bss that symbols.txt does not
	name at all: the engine's code we do not replace keeps using its own object, ours is a second copy of the state
	(a property list our RegisterProperties fills while the engine's stays empty). Left out: COMDAT data (template
	statics, which every user unit carries) and our own `gKeep...` instantiation anchors."""
	import struct
	named = set()
	for line in (ROOT / "config" / version / "symbols.txt").read_text(encoding="utf-8").splitlines():
		match = re.match(r"\s*(\S+)\s*=", line)
		if match:
			named.add(match.group(1))
	result = []
	for path in objectPaths:
		coff = objcmp.Coff(path)
		optSize = struct.unpack_from("<H", coff.data, 16)[0]
		for name, value, section, storage in coff.symbols:
			if section <= 0 or storage != 2 or name in named or name.startswith(("??_", "__", "?gKeep")):
				continue
			sec = coff.sections[section - 1]
			flags = struct.unpack_from("<I", coff.data, 20 + optSize + 40 * (section - 1) + 36)[0]
			if sec["name"].startswith((".data", ".bss")) and not flags & 0x1000:
				result.append((name, path.name))
	return result


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
	for name, problem in unmappedTypeDescriptors([pathlib.Path(o) for o in args.objects] or objects(args.version), data,
			image, base):
		problems += 1
		print(f"  type descriptor: {name}: {problem}")
	for name, where in unmappedGlobals([pathlib.Path(o) for o in args.objects] or objects(args.version), args.version):
		problems += 1
		print(f"  unmapped global: {name} ({where}): our object defines it but symbols.txt does not map it, so the"
			" engine's code keeps its own copy; map it to the engine's address")
	split = splitStatics(image, base, pe)
	for where, decl, users in split:
		problems += 1
		print(f"  split static: {where}: `{decl}` is file-local, so ours is a private copy, while engine code we do not"
			f" replace uses the engine's ({', '.join('0x%08X' % u for u in users[:4])}); drop `static` and map its"
			" decorated name in symbols.txt")
	print(f"{checked} data objects checked, {problems} problems")
	sys.exit(1 if problems else 0)


if __name__ == "__main__":
	main()
