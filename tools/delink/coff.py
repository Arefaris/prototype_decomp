"""A minimal writer for i386 COFF object files, enough to hand a delinked image to link.exe."""

import struct

IMAGE_FILE_MACHINE_I386 = 0x14C
IMAGE_REL_I386_DIR32 = 0x06
IMAGE_REL_I386_REL32 = 0x14
IMAGE_SCN_CNT_CODE = 0x00000020
IMAGE_SCN_CNT_INITIALIZED_DATA = 0x00000040
IMAGE_SCN_ALIGN_4096BYTES = 0x00D00000
IMAGE_SCN_LNK_NRELOC_OVFL = 0x01000000
IMAGE_SCN_MEM_EXECUTE = 0x20000000
IMAGE_SCN_MEM_READ = 0x40000000
IMAGE_SCN_MEM_WRITE = 0x80000000
IMAGE_SYM_CLASS_EXTERNAL = 2
IMAGE_SYM_CLASS_STATIC = 3
IMAGE_SYM_DTYPE_FUNCTION = 0x20

CODE = IMAGE_SCN_CNT_CODE | IMAGE_SCN_MEM_EXECUTE | IMAGE_SCN_MEM_READ | IMAGE_SCN_ALIGN_4096BYTES
RDATA = IMAGE_SCN_CNT_INITIALIZED_DATA | IMAGE_SCN_MEM_READ | IMAGE_SCN_ALIGN_4096BYTES
DATA = IMAGE_SCN_CNT_INITIALIZED_DATA | IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_WRITE | IMAGE_SCN_ALIGN_4096BYTES


class Section:
	def __init__(self, name, data, flags):
		self.name = name
		self.data = bytearray(data)
		self.flags = flags
		self.relocations = []  # (offset, symbol index, type)
		self.number = 0


class CoffWriter:
	def __init__(self):
		self.sections = []
		self.symbols = []  # (name, value, section number, type, storage class, aux bytes)
		self.symbolIndex = {}
		self.symbolCount = 0

	def addSection(self, name, data, flags):
		section = Section(name, data, flags)
		self.sections.append(section)
		section.number = len(self.sections)
		return section

	def _addSymbol(self, name, value, section, symType, storage, aux=b""):
		index = self.symbolCount
		self.symbolCount += 1 + len(aux) // 18
		self.symbols.append((name, value, section, symType, storage, aux))
		self.symbolIndex[name] = index
		return index

	def sectionSymbol(self, section):
		key = "$section:" + section.name
		if key not in self.symbolIndex:
			index = self._addSymbol(section.name, 0, section.number, 0, IMAGE_SYM_CLASS_STATIC, bytes(18))
			self.symbolIndex[key] = index
		return self.symbolIndex[key]

	def external(self, name):
		if name not in self.symbolIndex:
			self._addSymbol(name, 0, 0, IMAGE_SYM_DTYPE_FUNCTION, IMAGE_SYM_CLASS_EXTERNAL)
		return self.symbolIndex[name]

	def define(self, name, section, offset, function=False):
		if name in self.symbolIndex:
			raise ValueError(f"symbol {name} defined twice")
		return self._addSymbol(name, offset, section.number, IMAGE_SYM_DTYPE_FUNCTION if function else 0, IMAGE_SYM_CLASS_EXTERNAL)

	def write(self, path):
		for section in self.sections:
			self.sectionSymbol(section)
		headerSize = 20 + 40 * len(self.sections)
		blobs = []
		offset = headerSize
		layout = []
		for section in self.sections:
			raw = bytes(section.data)
			relocs = sorted(section.relocations)
			count = len(relocs)
			flags = section.flags
			relocBytes = bytearray()
			if count > 0xFFFF:
				flags |= IMAGE_SCN_LNK_NRELOC_OVFL
				relocBytes += struct.pack("<IIH", count + 1, 0, 0)
			for at, symbol, kind in relocs:
				relocBytes += struct.pack("<IIH", at, symbol, kind)
			rawOffset = offset
			relocOffset = rawOffset + len(raw) if relocs else 0
			offset += len(raw) + len(relocBytes)
			layout.append((section, rawOffset, relocOffset, min(count, 0xFFFF), flags, len(raw)))
			blobs += [raw, bytes(relocBytes)]
		symtabOffset = offset
		strings = bytearray(4)
		symbolBytes = bytearray()
		for name, value, number, symType, storage, aux in self.symbols:
			encoded = name.encode("latin-1")
			if len(encoded) <= 8:
				nameField = encoded.ljust(8, b"\0")
			else:
				nameField = struct.pack("<II", 0, len(strings))
				strings += encoded + b"\0"
			if aux:
				section = self.sections[number - 1]
				count = len(section.relocations)
				aux = struct.pack("<IHHIHB", len(section.data), min(count, 0xFFFF), 0, 0, 0, 0).ljust(18, b"\0")
			symbolBytes += nameField + struct.pack("<IhHBB", value, number, symType, storage, len(aux) // 18) + aux
		struct.pack_into("<I", strings, 0, len(strings))
		numberOfSymbols = len(symbolBytes) // 18
		with open(path, "wb") as f:
			f.write(struct.pack("<HHIIIHH", IMAGE_FILE_MACHINE_I386, len(self.sections), 0, symtabOffset, numberOfSymbols, 0, 0))
			for section, rawOffset, relocOffset, count, flags, size in layout:
				f.write(struct.pack("<8sIIIIIIHHI", section.name.encode("latin-1").ljust(8, b"\0"), 0, 0, size, rawOffset, relocOffset, 0, count, 0, flags))
			for blob in blobs:
				f.write(blob)
			f.write(symbolBytes)
			f.write(strings)
