"""Recover the MSVC RTTI of the engine DLL: every polymorphic class, its base classes and its vftables.

    python tools/rtti.py [--version PROTOPC_2025]

Writes config/<VERSION>/rtti.tsv (one row per vftable: address, slot count, offset in the object, class, bases)
and config/<VERSION>/classes.tsv (one row per type descriptor: address, mangled and demangled name, bases).
Reads only orig/<VERSION>/prototypeenginef.dll; names are demangled with undname.exe from any installed MSVC.

MSVC x86 RTTI layout (VS 2005):
  TypeDescriptor            { void* pVFTable; void* spare; char name[]; }       name ".?AV<class>@@"
  CompleteObjectLocator     { u32 signature(0); u32 offset; u32 cdOffset; TypeDescriptor*; ClassHierarchyDescriptor*; }
  ClassHierarchyDescriptor  { u32 signature; u32 attributes; u32 numBaseClasses; BaseClassDescriptor** array; }
  BaseClassDescriptor       { TypeDescriptor*; u32 numContainedBases; i32 mdisp, pdisp, vdisp; u32 attributes; }
  vftable[-1] = CompleteObjectLocator*
"""

import argparse
import glob
import pathlib
import re
import struct
import subprocess

import pefile

ROOT = pathlib.Path(__file__).resolve().parents[1]


class Image:
	def __init__(self, path):
		self.pe = pefile.PE(str(path), fast_load=True)
		self.base = self.pe.OPTIONAL_HEADER.ImageBase
		self.data = self.pe.get_memory_mapped_image()
		self.sections = {s.Name.rstrip(b"\0").decode(): (self.base + s.VirtualAddress, self.base + s.VirtualAddress + s.Misc_VirtualSize) for s in self.pe.sections}

	def u32(self, va):
		return struct.unpack_from("<I", self.data, va - self.base)[0]

	def i32(self, va):
		return struct.unpack_from("<i", self.data, va - self.base)[0]

	def inSection(self, va, name):
		start, end = self.sections[name]
		return start <= va < end

	def cstring(self, va):
		offset = va - self.base
		end = self.data.index(b"\0", offset)
		return self.data[offset:end].decode("latin-1")


def findUndname():
	pattern = r"C:\Program Files*\Microsoft Visual Studio\*\*\VC\Tools\MSVC\*\bin\Host*\x86\undname.exe"
	found = sorted(glob.glob(pattern))
	return found[-1] if found else None


def demangleAll(names):
	"""Demangle RTTI type names in batches through undname.exe; falls back to the raw name."""
	undname = findUndname()
	result = {}
	if not undname:
		return {n: n for n in names}
	names = list(names)
	for i in range(0, len(names), 300):
		batch = names[i:i + 300]
		args = [undname] + ["??_R0" + n[1:] + "@8" for n in batch]
		out = subprocess.run(args, capture_output=True, text=True, errors="replace").stdout
		decoded = re.findall(r'is :- "(.*)"', out)
		for name, text in zip(batch, decoded):
			text = re.sub(r"^(class|struct|union) ", "", text)
			result[name] = text.replace(" `RTTI Type Descriptor'", "")
	for n in names:
		result.setdefault(n, n)
	return result


def main():
	parser = argparse.ArgumentParser()
	parser.add_argument("--version", default="PROTOPC_2025")
	args = parser.parse_args()
	image = Image(ROOT / "orig" / args.version / "prototypeenginef.dll")
	raw = image.data

	# Type descriptors: ".?AV"/".?AU" names preceded by the type_info vftable pointer and a null spare
	typeDescriptors = {}
	for m in re.finditer(rb"\.\?A[VU][^\0]+\0", raw):
		va = image.base + m.start() - 8
		if image.inSection(va, ".data") and image.u32(va + 4) == 0:
			typeDescriptors[va] = m.group()[:-1].decode("latin-1")

	def baseClasses(chd):
		count = image.u32(chd + 8)
		array = image.u32(chd + 12)
		bases = []
		for k in range(1, count):  # entry 0 is the class itself
			bcd = image.u32(array + 4 * k)
			bases.append((typeDescriptors.get(image.u32(bcd), "?"), image.i32(bcd + 8), image.u32(bcd + 4)))
		return bases

	# Complete object locators in .rdata, then the vftables that point at them
	rdataStart, rdataEnd = image.sections[".rdata"]
	locators = {}
	for va in range(rdataStart, rdataEnd - 20, 4):
		if image.u32(va) != 0:
			continue
		td = image.u32(va + 12)
		chd = image.u32(va + 16)
		if td in typeDescriptors and image.inSection(chd, ".rdata"):
			locators[va] = (td, image.u32(va + 4), chd)
	textStart, textEnd = image.sections[".text"]
	vftables = []
	for va in range(rdataStart, rdataEnd - 4, 4):
		col = image.u32(va)
		if col in locators:
			vft = va + 4
			slots = 0
			while vft + 4 * slots < rdataEnd and textStart <= image.u32(vft + 4 * slots) < textEnd:
				slots += 1
				if slots > 1 and image.u32(vft + 4 * slots) in locators:
					break
			td, offset, chd = locators[col]
			vftables.append((vft, slots, offset, td, chd))

	names = demangleAll(set(typeDescriptors.values()))
	out = ROOT / "config" / args.version
	with open(out / "rtti.tsv", "w", encoding="utf-8", newline="\n") as f:
		f.write("vftable\tslots\toffset\tclass\tbases\n")
		for vft, slots, offset, td, chd in sorted(vftables):
			bases = "; ".join(names.get(b, b) for b, _, _ in baseClasses(chd))
			f.write(f"0x{vft:08X}\t{slots}\t{offset}\t{names[typeDescriptors[td]]}\t{bases}\n")
	hierarchy = {}
	for _, _, _, td, chd in vftables:
		hierarchy.setdefault(td, chd)
	with open(out / "classes.tsv", "w", encoding="utf-8", newline="\n") as f:
		f.write("type_descriptor\tmangled\tclass\tbases\n")
		for td, mangled in sorted(typeDescriptors.items()):
			bases = "; ".join(f"{names.get(b, b)}@{mdisp}" for b, mdisp, _ in baseClasses(hierarchy[td])) if td in hierarchy else ""
			f.write(f"0x{td:08X}\t{mangled}\t{names[mangled]}\t{bases}\n")
	polymorphic = len(hierarchy)
	print(f"type descriptors {len(typeDescriptors)}, object locators {len(locators)}, vftables {len(vftables)}, "
		f"polymorphic classes {polymorphic}, virtual slots {sum(v[1] for v in vftables)}")


if __name__ == "__main__":
	main()
