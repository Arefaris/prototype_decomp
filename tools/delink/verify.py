"""Check that a relinked prototypeenginef.dll is the original with only the intended differences.

    python tools/delink/verify.py [DLL] [--version PROTOPC_2025]

For .text, .rdata and .data: every byte outside the original's base relocation sites must be identical at the same
RVA, except inside replaced functions (listed by the relink .map's symbols that config symbols.txt maps). Each
relocation site must point at the same thing in both images: the same section offset, or the same import.
"""

import argparse
import json
import pathlib
import re
import struct
import sys

import pefile

ROOT = pathlib.Path(__file__).resolve().parents[2]


def imports(pe):
	slots = {}
	for entry in pe.DIRECTORY_ENTRY_IMPORT:
		dll = entry.dll.decode("latin-1").lower()
		for imp in entry.imports:
			slots[imp.address] = (dll, imp.name or imp.ordinal)
	return slots


def sections(pe):
	base = pe.OPTIONAL_HEADER.ImageBase
	return {s.Name.rstrip(b"\0").decode(): (base + s.VirtualAddress, s.Misc_VirtualSize) for s in pe.sections}


def classify(value, secs, slots, imageSecs):
	"""What an absolute value points at. imageSecs: the original's sections, used for the relinked ".o" section,
	which holds the original .text/.rdata/.data at their original addresses."""
	if value in slots:
		return ("import",) + slots[value]
	for name, (start, size) in secs.items():
		if start <= value <= start + size:
			if name == ".o":
				for origName, (origStart, origSize) in imageSecs.items():
					if origStart <= value <= origStart + origSize:
						return (origName, value - origStart)
			return (name, value - start)
	return ("absolute", value)


def mapAddresses(path):
	"""Public symbol -> address from a link.exe /MAP file ("Publics by Value" lines)."""
	addresses = {}
	if path.exists():
		for line in path.read_text(encoding="latin-1").splitlines():
			m = re.match(r"\s*[0-9a-fA-F]{4}:[0-9a-fA-F]{8}\s+(\S+)\s+([0-9a-fA-F]{8})\s", line)
			if m:
				addresses[m.group(1)] = int(m.group(2), 16)
	return addresses


def main():
	parser = argparse.ArgumentParser()
	parser.add_argument("dll", nargs="?")
	parser.add_argument("--version", default="PROTOPC_2025")
	parser.add_argument("--stamp", help="file to touch when the DLL verifies (for ninja)")
	args = parser.parse_args()
	ours = pefile.PE(args.dll or str(ROOT / "build" / args.version / "relink" / "prototypeenginef.dll"))
	orig = pefile.PE(str(ROOT / "orig" / args.version / "prototypeenginef.dll"))
	origSecs, ourSecs = sections(orig), sections(ours)
	origSlots, ourSlots = imports(orig), imports(ours)
	origImage, ourImage = orig.get_memory_mapped_image(), ours.get_memory_mapped_image()
	base = orig.OPTIONAL_HEADER.ImageBase
	ok = True
	sites = set()
	for block in orig.DIRECTORY_ENTRY_BASERELOC:
		for e in block.entries:
			if e.type == 3:
				sites.add(e.rva)
	imageSecs = {name: origSecs[name] for name in (".text", ".rdata", ".data")}
	if ".o" not in ourSecs or ourSecs[".o"][0] != origSecs[".text"][0]:
		sys.exit(f"the image section .o is not at 0x{origSecs['.text'][0]:08X}: {ourSecs.get('.o')}")
	# Replaced functions: the original address and our symbol's address in the relinked DLL
	relinkDir = pathlib.Path(args.dll).parent if args.dll else ROOT / "build" / args.version / "relink"
	report = json.loads((relinkDir / "relink.json").read_text(encoding="utf-8")) if (relinkDir / "relink.json").exists() else {"replaced": {}, "redirects": []}
	mapped = mapAddresses(relinkDir / "prototypeenginef.map")
	origReplaced = {address: name for name, address in report["replaced"].items()}
	ourReplaced = {mapped[name]: name for name in report["replaced"]}
	rel32 = {r["site"] - base: r["symbol"] for r in report["redirects"] if r["kind"] == "rel32"}
	badRedirects = 0
	for name in (".text", ".rdata", ".data"):
		start, size = origSecs[name]
		rva = start - base
		a = origImage[rva:rva + size]
		b = ourImage[rva:rva + size]
		masked = bytearray(len(a))
		badRelocs = 0
		for siteRva, symbol in rel32.items():
			at = siteRva - rva
			if 0 <= at < size:
				for k in range(4):
					masked[at + k] = 1
				destination = (base + siteRva + 4 + struct.unpack_from("<i", b, at)[0]) & 0xFFFFFFFF
				if destination != mapped[symbol]:
					badRedirects += 1
					print(f"  rel32 at 0x{base + siteRva:08X} goes to 0x{destination:08X}, not {symbol}")
		for site in sites:
			at = site - rva
			if 0 <= at < size:
				for k in range(4):
					masked[at + k] = 1
				va = struct.unpack_from("<I", a, at)[0]
				vb = struct.unpack_from("<I", b, at)[0]
				ca = ("replaced", origReplaced[va]) if va in origReplaced else classify(va, origSecs, origSlots, imageSecs)
				cb = ("replaced", ourReplaced[vb]) if vb in ourReplaced else classify(vb, ourSecs, ourSlots, imageSecs)
				if ca != cb:
					badRelocs += 1
					if badRelocs <= 10:
						print(f"  {name} reloc at 0x{site + base:08X}: {ca} -> {cb}")
		diffs = [k for k in range(size) if not masked[k] and a[k] != b[k]]
		print(f"{name}: {size} bytes, {len(diffs)} differing bytes outside relocations, {badRelocs} relocations pointing elsewhere")
		for k in diffs[:10]:
			print(f"  0x{start + k:08X}: {a[k]:02X} -> {b[k]:02X}")
		ok = ok and not diffs and not badRelocs
	ok = ok and not badRedirects
	print(f"{len(report['replaced'])} replaced functions, {len(report['redirects'])} references redirected to them")
	print("IDENTICAL (modulo relocation targets and replaced functions)" if ok else "DIFFERENT")
	if ok and args.stamp:
		pathlib.Path(args.stamp).touch()
	sys.exit(0 if ok else 1)


if __name__ == "__main__":
	main()
