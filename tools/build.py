"""Build the hybrid prototypeenginef.dll: compile src/ with the original's compiler and options, check every annotated
function against the original, relink, verify.

    python tools/build.py [--version PROTOPC_2025] [--no-link]

Each "// FUNCTION: ENGINE 0xADDRESS" annotation must sit directly above a function definition; the function is the
symbol config/<VERSION>/symbols.txt maps to that address. A temporary pipeline until configure.py and ninja (phase 1).
"""

import argparse
import pathlib
import re
import subprocess
import sys

ROOT = pathlib.Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools" / "delink"))
import objcmp  # noqa: E402
import relink  # noqa: E402

# Options measured from the binary and confirmed by matching (docs/toolchain.md)
CFLAGS = ["/c", "/O2", "/arch:SSE", "/fp:fast", "/GS-", "/GR", "/MD", "/Gy", "/W3", "/D", "NDEBUG", "/D", "WIN32"]
ANNOTATION = re.compile(r"//\s*FUNCTION:\s*ENGINE\s+(0x[0-9A-Fa-f]+)")


def compileAll(version):
	objDir = ROOT / "build" / version / "obj"
	objects = []
	for source in sorted((ROOT / "src").rglob("*.cpp")):
		relative = source.relative_to(ROOT / "src")
		obj = objDir / relative.with_suffix(".obj")
		obj.parent.mkdir(parents=True, exist_ok=True)
		code = subprocess.call([sys.executable, str(ROOT / "tools" / "toolchain" / "cl8.py"), "cl"] + CFLAGS +
			[f"/Fo{obj}", str(source)], stdout=subprocess.DEVNULL)
		if code != 0:
			sys.exit(f"compile failed: {relative}")
		objects.append((source, obj))
	return objects


def checkFunctions(objects, version):
	symbols = relink.loadSymbols(version)
	byAddress = {address: name for name, address in symbols.items()}
	matched = total = 0
	for source, obj in objects:
		for m in ANNOTATION.finditer(source.read_text(encoding="utf-8")):
			address = int(m.group(1), 16)
			total += 1
			name = byAddress.get(address)
			if name is None:
				print(f"  {source.name}: 0x{address:08X} has no entry in symbols.txt")
				continue
			result = subprocess.run([sys.executable, str(ROOT / "tools" / "objcmp.py"), str(obj), name, hex(address),
				"--quiet", "--version", version], capture_output=True, text=True)
			status = "match" if result.returncode == 0 else "DIFF "
			matched += result.returncode == 0
			print(f"  {status} 0x{address:08X} {name}: {result.stdout.strip().split(': ', 1)[-1]}")
	print(f"{matched}/{total} annotated functions match")
	return matched == total


def main():
	parser = argparse.ArgumentParser()
	parser.add_argument("--version", default="PROTOPC_2025")
	parser.add_argument("--no-link", action="store_true")
	args = parser.parse_args()
	objects = compileAll(args.version)
	print(f"compiled {len(objects)} sources")
	allMatch = checkFunctions(objects, args.version)
	if args.no_link:
		sys.exit(0 if allMatch else 1)
	code = subprocess.call([sys.executable, str(ROOT / "tools" / "delink" / "relink.py"), "--version", args.version] +
		[str(obj) for _, obj in objects])
	if code != 0:
		sys.exit("relink failed")
	code = subprocess.call([sys.executable, str(ROOT / "tools" / "delink" / "verify.py"), "--version", args.version])
	sys.exit(code or (0 if allMatch else 1))


if __name__ == "__main__":
	main()
