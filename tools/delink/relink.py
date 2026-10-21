"""Relink prototypeenginef.dll from the original image plus our reconstructed objects.

    python tools/delink/relink.py [OBJ ...] [--version PROTOPC_2025] [--out build/PROTOPC_2025/relink]

The original .text, .rdata and .data become one object ("the image object") whose sections keep their exact sizes and
contents. Every absolute address the original's base relocation table lists becomes a DIR32 relocation against the
section it points into, an import's __imp_ symbol or __ImageBase. The linker then lays the image object out first, at
the original addresses, and appends our objects.

A function is replaced when one of OBJs defines a symbol that config/<VERSION>/symbols.txt maps to an address: every
reference to that address in the image (absolute pointers, and rel32 calls and jumps, which with the original's
incremental link table are mostly the table's own jmp) is redirected to the symbol, so the linker binds it to our
code. The original bytes stay in the image as dead code. Other names of symbols.txt are defined in the image object so
our code can call and read what is not reconstructed yet.

Output: <out>/prototypeenginef.dll (+ .map), and the generated image object, import libraries, .def and .res.
"""

import argparse
import json
import pathlib
import re
import struct
import subprocess
import sys

import pefile

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import coff  # noqa: E402

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import objcmp  # noqa: E402  (its COFF reader)

CL8 = ROOT / "tools" / "toolchain" / "cl8.py"


def runTool(tool, args, cwd):
	# A command line is limited to 32767 characters: a long argument list goes through a response file
	if sum(len(a) + 1 for a in args) > 16000:
		response = pathlib.Path(cwd) / f"{tool}.rsp"
		response.write_text("\n".join('"' + a + '"' for a in args), encoding="ascii")
		args = [f"@{response.name}"]
	code = subprocess.call([sys.executable, str(CL8), tool] + args, cwd=cwd)
	if code != 0:
		sys.exit(f"{tool} failed ({code})")


def loadDataSizes(version):
	"""The sizes symbols.txt gives data symbols ('name = 0x... ; data size:0xN | ...')."""
	path = ROOT / "config" / version / "symbols.txt"
	sizes = {}
	if path.exists():
		for line in path.read_text(encoding="utf-8").splitlines():
			match = re.match(r"\s*(\S+)\s*=\s*0x[0-9A-Fa-f]+\s*;\s*data\s+size:(0x[0-9A-Fa-f]+|\d+)", line)
			if match:
				sizes[match.group(1)] = int(match.group(2), 0)
	return sizes


def loadSymbols(version):
	"""symbols.txt: one 'name = 0xADDRESS  ; comment' per line."""
	path = ROOT / "config" / version / "symbols.txt"
	symbols = {}
	if path.exists():
		for line in path.read_text(encoding="utf-8").splitlines():
			line = line.split(";", 1)[0].strip()
			if not line:
				continue
			name, address = (part.strip() for part in line.rsplit("=", 1))
			symbols[name] = int(address, 16)
	return symbols


def importSymbol(dllName, imp):
	"""The __imp_ symbol lib.exe generates for a .def entry (x86 decorates undecorated names with '_')."""
	if imp.name is None:
		stem = re.sub(r"\W", "_", dllName.rsplit(".", 1)[0])
		return f"__imp__{stem}_ord{imp.ordinal}", f"{stem}_ord{imp.ordinal} @{imp.ordinal} NONAME"
	name = imp.name.decode("latin-1")
	return ("__imp_" + name if name.startswith("?") else "__imp__" + name), name


def buildImportLibraries(pe, out):
	"""One import library per DLL, from the original's import table; returns {IAT slot VA: __imp_ symbol}."""
	base = pe.OPTIONAL_HEADER.ImageBase
	slots = {}
	libraries = []
	for entry in pe.DIRECTORY_ENTRY_IMPORT:
		dllName = entry.dll.decode("latin-1")
		lines = [f"LIBRARY {dllName}", "EXPORTS"]
		for imp in entry.imports:
			symbol, defLine = importSymbol(dllName, imp)
			slots[imp.address] = symbol
			lines.append("\t" + defLine)
		stem = dllName.rsplit(".", 1)[0].lower()
		(out / f"{stem}.def").write_text("\n".join(lines) + "\n", encoding="latin-1")
		runTool("lib", ["/machine:x86", f"/def:{stem}.def", f"/out:{stem}.lib"], out)
		libraries.append(out / f"{stem}.lib")
	return slots, libraries


def buildExportDef(pe, out, dllName):
	base = pe.OPTIONAL_HEADER.ImageBase
	textStart = base + pe.sections[0].VirtualAddress
	textEnd = textStart + pe.sections[0].Misc_VirtualSize
	lines = [f"LIBRARY {dllName}", "EXPORTS"]
	exports = []
	for exp in pe.DIRECTORY_ENTRY_EXPORT.symbols:
		name = exp.name.decode("latin-1")
		va = base + exp.address
		symbol = name if name.startswith("?") else "_" + name
		data = "" if textStart <= va < textEnd else " DATA"
		# link.exe decorates an undecorated .def name with '_' itself, so no "name=internal" alias
		lines.append(f"\t{name} @{exp.ordinal}{data}")
		exports.append((symbol, va))
	(out / "exports.def").write_text("\n".join(lines) + "\n", encoding="latin-1")
	return exports


def buildResources(pe, out):
	"""Write the original's resources (version info, manifest) as a .res file for link.exe."""
	entries = []
	for typeEntry in pe.DIRECTORY_ENTRY_RESOURCE.entries:
		for nameEntry in typeEntry.directory.entries:
			for langEntry in nameEntry.directory.entries:
				data = pe.get_data(langEntry.data.struct.OffsetToData, langEntry.data.struct.Size)
				entries.append((typeEntry, nameEntry, langEntry.id, data))

	def idField(entry):
		if entry.name is not None:
			return (str(entry.name) + "\0").encode("utf-16-le")
		return struct.pack("<HH", 0xFFFF, entry.id)

	res = bytearray(struct.pack("<II", 0, 32) + struct.pack("<HHHH", 0xFFFF, 0, 0xFFFF, 0) + bytes(16))
	for typeEntry, nameEntry, language, data in entries:
		header = idField(typeEntry) + idField(nameEntry)
		header += b"\0" * (-(8 + len(header)) % 4)
		header += struct.pack("<IHHII", 0, 0x1030, language, 0, 0)
		res += struct.pack("<II", len(data), 8 + len(header)) + header + data + b"\0" * (-len(data) % 4)
	(out / "resources.res").write_bytes(res)


def scanRel32(text, textVa, targets):
	"""Sites of rel32 calls / jumps (E8, E9, 0F 8x) in .text whose destination is one of targets."""
	sites = []
	if not targets:
		return sites
	for m in re.finditer(rb"[\xE8\xE9]|\x0F[\x80-\x8F]", text):
		at = m.end()
		if at + 4 > len(text):
			continue
		destination = (textVa + at + 4 + struct.unpack_from("<i", text, at)[0]) & 0xFFFFFFFF
		if destination in targets:
			sites.append((at, destination))
	return sites


def nonmatchingAddresses():
	"""Addresses whose `// FUNCTION: ENGINE` annotation is followed by `// NONMATCHING` in its comment block."""
	addresses = set()
	for path in (ROOT / "src").rglob("*.c*"):
		lines = path.read_text(encoding="utf-8", errors="replace").splitlines()
		for i, line in enumerate(lines):
			match = re.match(r"\s*//\s*FUNCTION:\s*ENGINE\s+(0x[0-9A-Fa-f]+)", line)
			if not match:
				continue
			for following in lines[i + 1:i + 12]:
				if not following.strip().startswith("//"):
					break
				if re.match(r"\s*//\s*NONMATCHING", following):
					addresses.add(int(match.group(1), 16))
					break
	return addresses


def definedSymbols(objects):
	names = set()
	for path in objects:
		obj = objcmp.Coff(path)
		for name, value, section, storage in obj.symbols:
			if section > 0 and storage == coff.IMAGE_SYM_CLASS_EXTERNAL:
				names.add(name)
	return names


def buildImageObject(pe, slots, exports, symbols, replaced, path, dataSizes=None):
	base = pe.OPTIONAL_HEADER.ImageBase
	image = pe.get_memory_mapped_image()
	writer = coff.CoffWriter()
	layout = []  # (start VA, end VA, Section or None)
	# The image's sections must stay apart from our objects' .text/.rdata/.data (and from the import tables link.exe
	# merges into .rdata), first and contiguous, at the original addresses whatever we add. link.exe's own section
	# ordering depends on section flags, so they use its documented grouping instead: ".o$1", ".o$2", ".o$3" become
	# one output section ".o", ordered by the suffix, each part page-aligned like the original sections.
	# The output section is read/write/execute; tools/delink/relink.py does not split it again.
	flagsByName = {".text": (".o$1", coff.CODE | coff.IMAGE_SCN_MEM_WRITE | coff.IMAGE_SCN_CNT_INITIALIZED_DATA),
		".rdata": (".o$2", coff.DATA | coff.IMAGE_SCN_MEM_EXECUTE | coff.IMAGE_SCN_CNT_CODE),
		".data": (".o$3", coff.DATA | coff.IMAGE_SCN_MEM_EXECUTE | coff.IMAGE_SCN_CNT_CODE)}
	for s in pe.sections:
		name = s.Name.rstrip(b"\0").decode()
		start = base + s.VirtualAddress
		end = start + s.Misc_VirtualSize
		if name in flagsByName:
			data = image[s.VirtualAddress:s.VirtualAddress + s.Misc_VirtualSize]
			section = writer.addSection(flagsByName[name][0], data, flagsByName[name][1])
			layout.append((start, end, section))
		else:
			layout.append((start, end, None))

	def place(va):
		for start, end, section in layout:
			if start <= va < end and section is not None:
				return section, va - start
		for start, end, section in layout:  # one-past-the-end pointers
			if va == end and section is not None:
				return section, va - start
		return None, None

	byAddress = {address: name for name, address in replaced.items()}
	# A replaced data object larger than a word is referenced inside too (a struct's members, an array's elements):
	# those references must reach our copy at the same offset, or the object is split between ours and the original's
	interiors = sorted((address, address + dataSizes[name], name) for name, address in replaced.items()
		if dataSizes and dataSizes.get(name, 0) > 1)

	def interior(value):
		for start, end, name in interiors:
			if start < value < end:
				return name, value - start
		return None, None

	stats = {"section": 0, "import": 0, "imagebase": 0, "replaced": 0, "interior": 0, "unresolved": 0}
	redirects = []  # image sites now pointing at our code, for verify.py
	for block in pe.DIRECTORY_ENTRY_BASERELOC:
		for entry in block.entries:
			if entry.type != pefile.RELOCATION_TYPE["IMAGE_REL_BASED_HIGHLOW"]:
				continue
			siteVa = base + entry.rva
			site, siteOffset = place(siteVa)
			if site is None:
				stats["unresolved"] += 1
				continue
			value = struct.unpack_from("<I", site.data, siteOffset)[0]
			if value in byAddress:
				struct.pack_into("<I", site.data, siteOffset, 0)
				site.relocations.append((siteOffset, writer.external(byAddress[value]), coff.IMAGE_REL_I386_DIR32))
				stats["replaced"] += 1
				redirects.append({"site": siteVa, "kind": "dir32", "symbol": byAddress[value]})
			elif interior(value)[0] is not None:
				name, offset = interior(value)
				struct.pack_into("<I", site.data, siteOffset, offset)  # x86 COFF DIR32: the addend is in place
				site.relocations.append((siteOffset, writer.external(name), coff.IMAGE_REL_I386_DIR32))
				stats["interior"] += 1
				redirects.append({"site": siteVa, "kind": "dir32", "symbol": name, "offset": offset})
			elif value in slots:
				struct.pack_into("<I", site.data, siteOffset, 0)
				site.relocations.append((siteOffset, writer.external(slots[value]), coff.IMAGE_REL_I386_DIR32))
				stats["import"] += 1
			else:
				target, targetOffset = place(value)
				if target is not None:
					struct.pack_into("<I", site.data, siteOffset, targetOffset)
					site.relocations.append((siteOffset, writer.sectionSymbol(target), coff.IMAGE_REL_I386_DIR32))
					stats["section"] += 1
				elif base <= value < base + 0x1000:
					struct.pack_into("<I", site.data, siteOffset, value - base)
					site.relocations.append((siteOffset, writer.external("___ImageBase"), coff.IMAGE_REL_I386_DIR32))
					stats["imagebase"] += 1
				else:
					stats["unresolved"] += 1
					print(f"  unresolved absolute value 0x{value:08X} at 0x{siteVa:08X}")

	text = layout[0][2]
	textVa = layout[0][0]
	for at, destination in scanRel32(bytes(text.data), textVa, set(byAddress)):
		struct.pack_into("<i", text.data, at, 0)
		text.relocations.append((at, writer.external(byAddress[destination]), coff.IMAGE_REL_I386_REL32))
		stats["replaced"] += 1
		redirects.append({"site": textVa + at, "kind": "rel32", "symbol": byAddress[destination]})

	entry = base + pe.OPTIONAL_HEADER.AddressOfEntryPoint
	section, offset = place(entry)
	writer.define("_DllEntry@12", section, offset, function=True)
	for symbol, va in exports:
		if symbol in replaced:
			# an exported function of the engine that one of our objects defines: the object provides the export
			continue
		section, offset = place(va)
		writer.define(symbol, section, offset, function=section is text)
	exported = {symbol for symbol, _ in exports}
	if hasattr(pe, "DIRECTORY_ENTRY_LOAD_CONFIG"):
		section, offset = place(base + pe.OPTIONAL_HEADER.DATA_DIRECTORY[10].VirtualAddress)
		writer.define("__load_config_used", section, offset)
	# __fltused: every object with floating point references it so the CRT's float support is linked; the CRT is
	# already inside the image and the symbol's value is never read, so any address in the data does
	if "__fltused" not in symbols:
		section, offset = place(layout[2][0])
		writer.define("__fltused", section, offset)
	for name, va in symbols.items():
		if name in replaced or name in exported:
			continue
		section, offset = place(va)
		if section is not None:
			writer.define(name, section, offset, function=section is text)
	writer.write(path)
	return stats, redirects


def main():
	parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
	parser.add_argument("objects", nargs="*")
	parser.add_argument("--version", default="PROTOPC_2025")
	parser.add_argument("--out")
	args = parser.parse_args()
	out = pathlib.Path(args.out or ROOT / "build" / args.version / "relink").resolve()
	out.mkdir(parents=True, exist_ok=True)
	objects = [pathlib.Path(o).resolve() for o in args.objects]

	dllName = "prototypeenginef.dll"
	pe = pefile.PE(str(ROOT / "orig" / args.version / dllName))
	symbols = loadSymbols(args.version)
	ours = definedSymbols(objects)
	replaced = {name: symbols[name] for name in ours if name in symbols}
	print(f"{len(symbols)} known symbols, {len(replaced)} replaced by {len(objects)} objects")
	# a NONMATCHING function keeps the original; a definition left outside its #ifdef (an empty body) would replace it
	nonmatching = nonmatchingAddresses()
	leaked = sorted((address, name) for name, address in replaced.items() if address in nonmatching)
	if leaked:
		for address, name in leaked:
			print(f"error: 0x{address:08X} {name} is NONMATCHING but our objects define it; put the whole definition"
				" inside #ifdef NONMATCHING")
		sys.exit(1)

	slots, libraries = buildImportLibraries(pe, out)
	exports = buildExportDef(pe, out, dllName)
	buildResources(pe, out)
	stats, redirects = buildImageObject(pe, slots, exports, symbols, replaced, out / "image.obj",
		loadDataSizes(args.version))
	print("relocations:", ", ".join(f"{k} {v}" for k, v in stats.items()))
	report = {"replaced": {name: address for name, address in sorted(replaced.items())}, "redirects": redirects}
	(out / "relink.json").write_text(json.dumps(report, indent=1), encoding="utf-8")

	linkArgs = ["/DLL", "/NODEFAULTLIB", "/SAFESEH:NO", "/INCREMENTAL:NO", "/OPT:NOREF", "/OPT:NOICF",
		f"/BASE:0x{pe.OPTIONAL_HEADER.ImageBase:08X}", "/ENTRY:DllEntry", "/DEF:exports.def", "/MANIFEST:NO",
		f"/OUT:{dllName}", "/MAP:prototypeenginef.map", "/SUBSYSTEM:WINDOWS", "image.obj"]
	linkArgs += [str(o) for o in objects] + [str(lib) for lib in libraries] + ["resources.res"]
	runTool("link", linkArgs, out)
	stampLikeOriginal(pe, out / dllName)
	print(f"wrote {out / dllName}")


def stampLikeOriginal(original, path):
	"""Give the relinked DLL the original's COFF time stamp: tools (the d3d9 proxy's control channel among them)
	recognise the engine build by it, and our DLL is meant to stand in for that build."""
	stamp = original.FILE_HEADER.TimeDateStamp
	data = bytearray(path.read_bytes())
	peOffset = struct.unpack_from("<I", data, 0x3C)[0]
	struct.pack_into("<I", data, peOffset + 8, stamp)
	ours = pefile.PE(data=bytes(data), fast_load=True)
	ours.parse_data_directories(directories=[pefile.DIRECTORY_ENTRY["IMAGE_DIRECTORY_ENTRY_EXPORT"]])
	exportDirectory = ours.DIRECTORY_ENTRY_EXPORT.struct.get_file_offset()
	struct.pack_into("<I", data, exportDirectory + 4, original.DIRECTORY_ENTRY_EXPORT.struct.TimeDateStamp)
	path.write_bytes(data)


if __name__ == "__main__":
	main()
