"""What difftest knows about the repository: symbols.txt, functions.tsv, the units and their objects, the original
image (read from orig/, never written anywhere), and the places captured states live (local/difftest/, ignored)."""

import json
import pathlib
import re
import struct
import sys

ROOT = pathlib.Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402
import objcmp  # noqa: E402

VERSION = "PROTOPC_2025"
LOCAL = ROOT / "local" / "difftest"
STATES = LOCAL / "states"
STORE = LOCAL / "store"
REPORTS = LOCAL / "reports"
DLL = ROOT / "orig" / VERSION / "prototypeenginef.dll"
PAGE = 0x1000

_symbols = None
_byAddress = None
_functions = None
_image = None


def symbols():
	global _symbols, _byAddress
	if _symbols is None:
		_symbols = objcmp.loadSymbols(VERSION)
		_byAddress = {}
		for name, address in _symbols.items():
			_byAddress.setdefault(address, name)
	return _symbols


def symbolAt(address):
	symbols()
	return _byAddress.get(address)


def functionSizes():
	"""{address: size} from functions.tsv."""
	global _functions
	if _functions is None:
		_functions = {}
		for line in (ROOT / "config" / VERSION / "functions.tsv").read_text(encoding="utf-8").splitlines():
			parts = line.split("\t")
			if len(parts) >= 2 and parts[0].startswith("0x"):
				_functions[int(parts[0], 16)] = int(parts[1])
	return _functions


_starts = None


def sortedStarts():
	global _starts
	if _starts is None:
		_starts = sorted(functionSizes())
	return _starts


def containingFunction(address):
	"""The start of the function (functions.tsv) that holds `address`, or None."""
	import bisect
	starts = sortedStarts()
	i = bisect.bisect_right(starts, address) - 1
	if i < 0:
		return None
	start = starts[i]
	return start if address < start + functionSizes()[start] + 16 else None


def functionExtent(address):
	"""The bytes a function may occupy: up to the next function start (functions.tsv), at most 16 bytes past the
	table's size (the table's sizes can stop short of the final ret), trailing int3 padding removed."""
	sizes = functionSizes()
	size = sizes.get(address, 0x100)
	starts = sortedStarts()
	import bisect
	i = bisect.bisect_right(starts, address)
	nextStart = starts[i] if i < len(starts) else address + size
	extent = min(nextStart - address, size + 16) if nextStart > address else size
	code = image().read(address, extent)
	while extent > size and code[extent - 1] == 0xCC:
		extent -= 1
	return extent


class Image:
	"""The original DLL as mapped: bytes, sections and incremental-link thunks."""

	def __init__(self):
		import pefile
		pe = pefile.PE(str(DLL), fast_load=True)
		self.base = pe.OPTIONAL_HEADER.ImageBase
		self.data = bytes(pe.get_memory_mapped_image())
		self.end = self.base + len(self.data)
		self.sections = []
		for s in pe.sections:
			name = s.Name.rstrip(b"\0").decode()
			start = self.base + s.VirtualAddress
			writable = bool(s.Characteristics & 0x80000000)
			executable = bool(s.Characteristics & 0x20000000)
			self.sections.append((name, start, start + s.Misc_VirtualSize, writable, executable))

	def read(self, address, size):
		return self.data[address - self.base:address - self.base + size]

	def u32(self, address):
		return struct.unpack_from("<I", self.data, address - self.base)[0]

	def contains(self, address):
		return self.base <= address < self.end

	def section(self, address):
		for section in self.sections:
			if section[1] <= address < section[2]:
				return section
		return None

	def readOnly(self, address):
		"""Inside a read-only section of the image (code, constants, vtables): reads there carry no state."""
		section = self.section(address)
		return section is not None and not section[3]

	def followThunks(self, address):
		for _ in range(4):
			if not self.contains(address) or self.data[address - self.base] != 0xE9:
				break
			address = (address + 5 + struct.unpack_from("<i", self.data, address - self.base + 1)[0]) & 0xFFFFFFFF
		return address

	def imports(self):
		"""{import name: IAT slot address} of the engine DLL (the slot holds the resolved address at run time)."""
		if not hasattr(self, "_imports"):
			import pefile
			pe = pefile.PE(str(DLL), fast_load=True)
			pe.parse_data_directories(directories=[pefile.DIRECTORY_ENTRY["IMAGE_DIRECTORY_ENTRY_IMPORT"]])
			table = {}
			for entry in getattr(pe, "DIRECTORY_ENTRY_IMPORT", []):
				for imp in entry.imports:
					if imp.name:
						table.setdefault(imp.name.decode("latin-1"), imp.address)
			self._imports = table
		return self._imports

	def textRange(self):
		for name, start, end, writable, executable in self.sections:
			if name == ".text":
				return start, end
		raise KeyError(".text")


def image():
	global _image
	if _image is None:
		_image = Image()
	return _image


def units():
	path = ROOT / "build" / VERSION / "units.json"
	if not path.exists():
		raise SystemExit("build/%s/units.json is missing: run python tools/configure.py" % VERSION)
	return json.loads(path.read_text(encoding="utf-8"))["units"]


def annotated(statuses=("equivalent",)):
	"""[(address, status, unit)] of every annotated function whose status is in `statuses`."""
	result = []
	for unit in units():
		text = (ROOT / unit["source"]).read_text(encoding="utf-8")
		for address, status in build.annotations(text):
			if status in statuses:
				result.append((address, status, unit))
	return result


_replaced = None


def replacedFunctions():
	"""Addresses of the functions the build compiles (match and equivalent): the hybrid DLL runs ours in their place."""
	global _replaced
	if _replaced is None:
		_replaced = {address for address, status, unit in annotated(("match", "equivalent"))}
	return _replaced


def locate(address):
	"""The unit, annotation status and compiled object of the function annotated at `address`."""
	for unit in units():
		text = (ROOT / unit["source"]).read_text(encoding="utf-8")
		for found, status in build.annotations(text):
			if found == address:
				obj = ROOT / "build" / VERSION / "obj" / (unit["name"] + ".obj")
				return unit, status, obj
	return None, None, None


def returnKind(mangled):
	"""What a function returns, from its decorated name: "void", "float" (x87 st0), "int64" (edx:eax) or "int"
	(eax, pointers and bools included); None when the name is not a decorated C++ name."""
	if not mangled or not mangled.startswith("?"):
		return None
	# the function code: Y/Z (global) and S/K/C (static member) are followed by the convention alone, a non-static
	# member by its this-qualifier (A, B, ...) and then the convention; the return type comes next
	m = re.search(r"@@([YZSKC])([AEGI])(.+)$", mangled) or re.search(r"@@([A-Z$])([ABCD])([AEGI])(.+)$", mangled)
	if not m:
		return None
	rest = m.group(m.lastindex)
	code = rest[:2] if rest.startswith("_") else rest[:1]
	if code == "@":  # constructors return this in eax, destructors nothing
		return "void" if mangled.startswith("??1") else "int"
	if code == "X":
		return "void"
	if code in ("M", "N", "O"):
		return "float"
	if code in ("_J", "_K"):
		return "int64"
	if code in ("_N", "C", "D", "E"):
		return "byte"  # bool and the chars come back in al; the rest of eax is whatever was there
	if code in ("F", "G"):
		return "word"
	return "int"


_slotMasks = {}


def stackSlotMasks(mangled):
	"""For each stack dword of a function's arguments, the mask of the bytes that carry the value (a bool or
	char argument uses one byte of its dword, a short two; the rest is whatever the caller had in the register it
	pushed), from the declaration dbghelp undecorates the name to; None when the name cannot be read."""
	if mangled in _slotMasks:
		return _slotMasks[mangled]
	masks = None
	if mangled and mangled.startswith("?"):
		import ctypes
		buffer = ctypes.create_string_buffer(2048)
		if ctypes.windll.dbghelp.UnDecorateSymbolName(mangled.encode("latin-1"), buffer, len(buffer), 0):
			text = buffer.value.decode("latin-1")
			inside = text[text.rfind("(") + 1:text.rfind(")")] if "(" in text else ""
			depth, parts, current = 0, [], ""
			for ch in inside:
				depth += ch == "<"
				depth -= ch == ">"
				if ch == "," and depth == 0:
					parts.append(current.strip())
					current = ""
				else:
					current += ch
			if current.strip():
				parts.append(current.strip())
			masks = []
			for part in parts:
				if part in ("void", "...") or "*" in part or "&" in part:
					if part != "void":
						masks.append(0xFFFFFFFF)
					continue
				words = part.replace("const", "").replace("volatile", "").split()
				if "double" in words or "__int64" in words:
					masks += [0xFFFFFFFF, 0xFFFFFFFF]
				elif "char" in words or "bool" in words:
					masks.append(0xFF)
				elif "short" in words or "wchar_t" in words:
					masks.append(0xFFFF)
				else:
					masks.append(0xFFFFFFFF)
	_slotMasks[mangled] = masks
	return masks


def callingConvention(mangled):
	"""'thiscall', 'cdecl', 'stdcall', 'fastcall' or None from a decorated name."""
	if not mangled or not mangled.startswith("?"):
		return None
	m = re.search(r"@@([YZSKC])([AEGI])", mangled) or re.search(r"@@([A-Z$])([ABCD])([AEGI])", mangled)
	if not m:
		return None
	return {"A": "cdecl", "E": "thiscall", "G": "stdcall", "I": "fastcall"}[m.group(m.lastindex)]


def stateDirectory(address):
	return STATES / ("0x%08X" % address)


def listStates(address):
	directory = stateDirectory(address)
	if not directory.exists():
		return []
	return sorted(directory.glob("*.state"))
