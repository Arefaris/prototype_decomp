"""Run a Visual Studio 2005 SP1 tool (cl, link, lib, dumpbin) with its environment set.

    python tools/toolchain/cl8.py cl /c /O2 file.cpp
    python tools/toolchain/cl8.py link /DLL ...

VC8_DIR (default D:/tools/vc8) is the directory tools/toolchain/setup_vc8.py extracted into.
"""

import os
import pathlib
import subprocess
import sys

ROOT = pathlib.Path(__file__).resolve().parents[2]


def environment():
	vc = pathlib.Path(os.environ.get("VC8_DIR", r"D:\tools\vc8")) / "VC"
	env = dict(os.environ)
	env["PATH"] = str(vc / "Bin") + os.pathsep + env.get("PATH", "")
	includes = [vc / "INCLUDE", ROOT / "include", ROOT / "src"]
	env["INCLUDE"] = os.pathsep.join(str(p) for p in includes)
	env["LIB"] = str(vc / "LIB")
	return env, vc / "Bin"


def main():
	if len(sys.argv) < 2:
		sys.exit(__doc__)
	env, binDir = environment()
	tool = binDir / (sys.argv[1] + ".exe")
	sys.exit(subprocess.call([str(tool), "/nologo"] + sys.argv[2:], env=env))


if __name__ == "__main__":
	main()
