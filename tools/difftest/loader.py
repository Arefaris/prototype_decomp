"""Loads one compiled function (the COMDAT section of a symbol in a build object) into a machine's memory, with
its relocations applied: symbols that symbols.txt places go to the engine's addresses (the callees run as the
engine's own code), symbols the object defines (constants, strings, local helpers, vtables) are placed beside the
function, anything else is an error (the relink would fail on it too)."""

import struct

import objcmp

from . import project

DIR32 = 0x06
REL32 = 0x14


class LoadError(Exception):
	pass


class Loaded:
	def __init__(self):
		self.entry = None
		self.size = 0
		self.sections = {}  # section number -> (base, size, name)
		self.placed = {}  # symbol -> address (symbols placed in ours)
		self.engineRefs = {}  # symbol -> engine address used


def load(coffPath, symbol, writer, codeBase, dataBase, unitMode=False, fallback=None):
	"""Places `symbol`'s section (and transitively what it references) through writer(address, bytes).
	Code sections go from codeBase upward, data sections from dataBase. `fallback(name)` may resolve what
	neither symbols.txt nor the object defines (the C runtime imports). Returns a Loaded."""
	coff = objcmp.Coff(coffPath)
	symbols = project.symbols()
	defined = {}
	for name, value, section, storage in coff.symbols:
		if section > 0 and name not in defined:
			defined[name] = (value, section)
	rawSyms = {}
	for k, rawIndex in enumerate(sorted(coff.byIndex)):
		rawSyms[rawIndex] = coff.symbols[k]
	loaded = Loaded()
	cursors = {"code": codeBase, "data": dataBase}
	bases = {}

	def writableData(section):
		return coff.sections[section - 1]["name"].startswith((".data", ".bss"))

	def resolve(target, section, value):
		# in unit mode our own functions and read-only tables (vftables) shadow the engine's; a writable data object
		# symbols.txt maps (a function-local static) stays at the engine's address, as the relink makes the image's
		# references reach one copy, and both runs then read and write the same state
		if target in symbols and not (unitMode and target in defined and not writableData(defined[target][1])):
			loaded.engineRefs[target] = symbols[target]
			return symbols[target]
		if section > 0:
			return placeSection(section) + value
		if target in defined:
			value, section = defined[target]
			return placeSection(section) + value
		if target.startswith("??_E"):
			# the vector deleting destructor is an alias of the scalar one (??_G) in these objects
			alias = "??_G" + target[4:]
			if alias in defined or alias in symbols:
				return resolve(alias, 0, 0)
		found = fallback(target) if fallback else None
		if found is not None:
			loaded.engineRefs[target] = found
			return found
		raise LoadError("unresolved symbol %s (not in symbols.txt, not defined in %s)" % (target, coffPath))

	def placeSection(section):
		if section in bases:
			return bases[section]
		sec = coff.sections[section - 1]
		kind = "code" if sec["name"].startswith(".text") else "data"
		base = cursors[kind]
		cursors[kind] += (sec["size"] + 15) & ~15
		bases[section] = base
		loaded.sections[section] = (base, sec["size"], sec["name"])
		data = bytearray(coff.data[sec["raw"]:sec["raw"] + sec["size"]]) if sec["raw"] else bytearray(sec["size"])
		for offset, index, kind in sec["relocs"]:
			name, value, symSection, storage = rawSyms[index]
			target = resolve(name, symSection, value)
			inplace = struct.unpack_from("<i", data, offset)[0]
			if kind == DIR32:
				struct.pack_into("<I", data, offset, (target + inplace) & 0xFFFFFFFF)
			elif kind == REL32:
				struct.pack_into("<I", data, offset, (target + inplace - (base + offset + 4)) & 0xFFFFFFFF)
			else:
				raise LoadError("relocation type 0x%02X in %s" % (kind, sec["name"]))
		writer(base, bytes(data))
		return base

	if symbol not in defined:
		raise LoadError("%s is not defined in %s" % (symbol, coffPath))
	value, section = defined[symbol]
	loaded.entry = placeSection(section) + value
	loaded.size = coff.sections[section - 1]["size"] - value
	for name, (value, sectionNumber) in defined.items():
		if sectionNumber in bases:
			loaded.placed[name] = bases[sectionNumber] + value
	loaded.coff = coff
	return loaded
