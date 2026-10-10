"""A copy of prototypeenginef.dll that REA's Ghidra provider admits on Windows.

REA's Windows Ghidra provider takes PE applications only and refuses a DLL by the COFF IMAGE_FILE_DLL flag. The copy
clears that one flag; every byte the code and data use is unchanged and the image base stays 0x10000000, so the
addresses REA reports are the ones the project cites. orig/ is only read.

    python tools/re/rea_target.py [--version PROTOPC_2025]   ->  local/re/prototypeenginef_rea.exe
"""

import argparse
import pathlib
import struct
import sys

ROOT = pathlib.Path(__file__).resolve().parents[2]
IMAGE_FILE_DLL = 0x2000


def main():
	parser = argparse.ArgumentParser()
	parser.add_argument("--version", default="PROTOPC_2025")
	args = parser.parse_args()
	source = ROOT / "orig" / args.version / "prototypeenginef.dll"
	target = ROOT / "local" / "re" / "prototypeenginef_rea.exe"
	data = bytearray(source.read_bytes())
	peOffset = struct.unpack_from("<I", data, 0x3C)[0]
	if data[peOffset:peOffset + 4] != b"PE\0\0":
		sys.exit(f"{source}: no PE header")
	# The COFF header's Characteristics field: PE signature + 18
	at = peOffset + 22
	characteristics = struct.unpack_from("<H", data, at)[0]
	struct.pack_into("<H", data, at, characteristics & ~IMAGE_FILE_DLL)
	target.parent.mkdir(parents=True, exist_ok=True)
	target.write_bytes(data)
	print(f"{target} (characteristics 0x{characteristics:04X} -> 0x{characteristics & ~IMAGE_FILE_DLL:04X})")


if __name__ == "__main__":
	main()
