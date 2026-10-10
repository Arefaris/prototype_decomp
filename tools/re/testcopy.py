"""Make (or refresh) a test copy of the game that runs a relinked prototypeenginef.dll, without touching the Steam one.

    python tools/re/testcopy.py [--dll build/PROTOPC_2025/relink/prototypeenginef.dll] [--copy D:/PrototypeRecomp]
                                [--game D:/SteamLibrary/steamapps/common/Prototype] [--proxy D:/PrototypeAudit]
    python tools/re/testcopy.py --original     # put the original DLL back into the copy

Large files are hard links and folders are junctions into the Steam installation (same volume, no admin rights
needed, no extra space). prototypeenginef.dll is a real copy. From --proxy, if given, the copy takes the d3d9 proxy
(windowed mode, shots, control channel), args.txt (skip movies and prompts) and steam_appid.txt.
"""

import argparse
import os
import pathlib
import shutil
import subprocess
import sys

ROOT = pathlib.Path(__file__).resolve().parents[2]
EXTRAS = ("d3d9.dll", "args.txt", "steam_appid.txt")


def main():
	parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
	parser.add_argument("--dll", default=str(ROOT / "build" / "PROTOPC_2025" / "relink" / "prototypeenginef.dll"))
	parser.add_argument("--copy", default=r"D:\PrototypeRecomp")
	parser.add_argument("--game", default=r"D:\SteamLibrary\steamapps\common\Prototype")
	parser.add_argument("--proxy", default=r"D:\PrototypeAudit")
	parser.add_argument("--original", action="store_true")
	args = parser.parse_args()
	game, copy = pathlib.Path(args.game), pathlib.Path(args.copy)
	copy.mkdir(parents=True, exist_ok=True)
	for item in game.iterdir():
		target = copy / item.name
		# opprobe_* are the proxy's request and log files: per copy, never shared
		if item.name in EXTRAS or item.name == "prototypeenginef.dll" or item.name.startswith("opprobe_") or target.exists():
			continue
		if item.is_dir():
			subprocess.run(["cmd", "/c", "mklink", "/J", str(target), str(item)], check=True, stdout=subprocess.DEVNULL)
		else:
			os.link(item, target)
	if args.proxy:
		for name in EXTRAS:
			source = pathlib.Path(args.proxy) / name
			if source.exists():
				shutil.copy2(source, copy / name)
	dll = ROOT / "orig" / "PROTOPC_2025" / "prototypeenginef.dll" if args.original else pathlib.Path(args.dll)
	if not dll.exists():
		sys.exit(f"{dll} does not exist")
	shutil.copy2(dll, copy / "prototypeenginef.dll")
	print(f"{copy}: prototypeenginef.dll <- {dll}")


if __name__ == "__main__":
	main()
