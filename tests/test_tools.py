"""Tests of the delinking tools on synthetic data (no original binary needed).

    python -m unittest discover tests
"""

import pathlib
import struct
import sys
import tempfile
import unittest

ROOT = pathlib.Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools" / "delink"))

import coff  # noqa: E402
import objcmp  # noqa: E402
import relink  # noqa: E402


class CoffWriterTest(unittest.TestCase):
	def writeAndRead(self, writer):
		with tempfile.TemporaryDirectory() as directory:
			path = pathlib.Path(directory) / "t.obj"
			writer.write(path)
			return objcmp.Coff(path)

	def testFunctionWithRelocations(self):
		writer = coff.CoffWriter()
		code = bytes.fromhex("e800000000c3")  # call rel32; ret
		text = writer.addSection(".text", code, coff.CODE)
		writer.sectionSymbol(text)
		writer.define("?f@@YAXXZ", text, 0, function=True)
		text.relocations.append((1, writer.external("?g@@YAXXZ"), coff.IMAGE_REL_I386_REL32))
		read = self.writeAndRead(writer)
		body, mask = read.function("?f@@YAXXZ")
		self.assertEqual(body, code)
		self.assertEqual(bytes(mask), bytes([0, 1, 1, 1, 1, 0]))
		names = [s[0] for s in read.symbols]
		self.assertIn("?g@@YAXXZ", names)

	def testRelocationOverflow(self):
		writer = coff.CoffWriter()
		data = writer.addSection(".data", bytes(4 * 70000), coff.DATA)
		symbol = writer.sectionSymbol(data)
		for k in range(70000):
			data.relocations.append((4 * k, symbol, coff.IMAGE_REL_I386_DIR32))
		with tempfile.TemporaryDirectory() as directory:
			path = pathlib.Path(directory) / "t.obj"
			writer.write(path)
			raw = path.read_bytes()
		_, _, _, _, _, relocs, _, count, _, flags = struct.unpack_from("<8sIIIIIIHHI", raw, 20)
		self.assertEqual(count, 0xFFFF)
		self.assertTrue(flags & coff.IMAGE_SCN_LNK_NRELOC_OVFL)
		self.assertEqual(struct.unpack_from("<I", raw, relocs)[0], 70001)

	def testComdatSymbolFollowsSectionSymbol(self):
		writer = coff.CoffWriter()
		text = writer.addSection(".text", b"\xc3", coff.CODE | coff.IMAGE_SCN_LNK_COMDAT)
		text.selection = coff.IMAGE_COMDAT_SELECT_NODUPLICATES
		sectionIndex = writer.sectionSymbol(text)
		functionIndex = writer.define("_f", text, 0, function=True)
		self.assertEqual(functionIndex, sectionIndex + 2)


class ImportNamingTest(unittest.TestCase):
	class Imp:
		def __init__(self, name, ordinal=None):
			self.name = name
			self.ordinal = ordinal

	def testNames(self):
		self.assertEqual(relink.importSymbol("KERNEL32.dll", self.Imp(b"Sleep"))[0], "__imp__Sleep")
		self.assertEqual(relink.importSymbol("MSVCR80.dll", self.Imp(b"_stricmp"))[0], "__imp___stricmp")
		self.assertEqual(relink.importSymbol("MSVCR80.dll", self.Imp(b"??2@YAPAXI@Z"))[0], "__imp_??2@YAPAXI@Z")
		symbol, line = relink.importSymbol("XINPUT1_3.dll", self.Imp(None, 2))
		self.assertEqual(symbol, "__imp__XINPUT1_3_ord2")
		self.assertTrue(line.endswith("@2 NONAME"))


if __name__ == "__main__":
	unittest.main()
