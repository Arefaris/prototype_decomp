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
# /we4129: an unknown escape in a literal ("audio\english") is an error; it changes the string, not the code
CFLAGS = ["/c", "/O2", "/Ob1", "/arch:SSE", "/fp:fast", "/GS-", "/GR", "/MD", "/Gy", "/W3", "/we4129", "/D", "NDEBUG", "/D", "WIN32"]
# A source whose unit the engine compiled with other options says so in a comment among its first lines:
# "// CFLAGS: /arch:SSE2". An option replaces the default of the same name (the part before the colon); "!/arch"
# removes it.
SOURCE_FLAGS = re.compile(r"^//\s*CFLAGS:\s*(.+?)\s*$", re.MULTILINE)
ANNOTATION = re.compile(r"//\s*FUNCTION:\s*ENGINE\s+(0x[0-9A-Fa-f]+)[^\n]*\n(?:\s*//\s*(NONMATCHING|EQUIVALENT))?")


def cflagsFor(source):
	"""CFLAGS of one source file: the defaults, with the options its "// CFLAGS:" comment names substituted."""
	text = pathlib.Path(source).read_text(encoding="utf-8")[:2000]
	flags = list(CFLAGS)
	for match in SOURCE_FLAGS.finditer(text):
		for option in match.group(1).split():
			if option.startswith("!"):
				# "!/arch" drops the option of that name (the unit was compiled without it)
				flags = [f for f in flags if f.split(":")[0] != option[1:]]
				continue
			stem = option.split(":")[0]
			flags = [f for f in flags if f.split(":")[0] != stem]
			flags.append(option)
	return flags


def annotations(text):
	"""[(address, status)] of a source file; status is "match", "nonmatching" or "equivalent".

	The line after a FUNCTION annotation may say why a function does not match yet:
	- "// NONMATCHING: reason": the function sits inside #ifdef NONMATCHING, so it is neither compiled into the hybrid
	  DLL nor checked;
	- "// EQUIVALENT: reason": the function computes the same as the original but is not byte-identical (register or
	  scheduling choices). It is compiled and replaces the original in the hybrid DLL, which keeps the register
	  knowledge its callers in the same unit rely on, but it does not count as matched."""
	return [(int(m.group(1), 16), (m.group(2) or "match").lower()) for m in ANNOTATION.finditer(text)]


def compileAll(version):
	objDir = ROOT / "build" / version / "obj"
	objects = []
	for source in sorted((ROOT / "src").rglob("*.cpp")):
		relative = source.relative_to(ROOT / "src")
		obj = objDir / relative.with_suffix(".obj")
		obj.parent.mkdir(parents=True, exist_ok=True)
		code = subprocess.call([sys.executable, str(ROOT / "tools" / "toolchain" / "cl8.py"), "cl"] + cflagsFor(source) +
			[f"/Fo{obj}", str(source)], stdout=subprocess.DEVNULL)
		if code != 0:
			sys.exit(f"compile failed: {relative}")
		objects.append((source, obj))
	return objects


def checkFunctions(objects, version):
	symbols = relink.loadSymbols(version)
	byAddress = {address: name for name, address in symbols.items()}
	matched = total = nonmatching = equivalent = 0
	for source, obj in objects:
		for address, status in annotations(source.read_text(encoding="utf-8")):
			name = byAddress.get(address)
			if status == "nonmatching":
				nonmatching += 1
				print(f"  nonm. 0x{address:08X} {name}")
				continue
			if status == "equivalent":
				equivalent += 1
				print(f"  equiv 0x{address:08X} {name}")
				continue
			total += 1
			if name is None:
				print(f"  {source.name}: 0x{address:08X} has no entry in symbols.txt")
				continue
			result = subprocess.run([sys.executable, str(ROOT / "tools" / "objcmp.py"), str(obj), name, hex(address),
				"--quiet", "--version", version], capture_output=True, text=True)
			status = "match" if result.returncode == 0 else "DIFF "
			matched += result.returncode == 0
			print(f"  {status} 0x{address:08X} {name}: {result.stdout.strip().split(': ', 1)[-1]}")
	print(f"{matched}/{total} annotated functions match ({nonmatching} NONMATCHING, {equivalent} EQUIVALENT)")
	return matched == total


def main():
	parser = argparse.ArgumentParser()
	parser.add_argument("--version", default="PROTOPC_2025")
	parser.add_argument("--no-link", action="store_true")
	parser.add_argument("--no-compile", action="store_true", help="use the objects ninja already built")
	parser.add_argument("--stamp", help="file to touch when everything matches (for ninja)")
	args = parser.parse_args()
	if args.no_compile:
		objDir = ROOT / "build" / args.version / "obj"
		objects = [(s, objDir / s.relative_to(ROOT / "src").with_suffix(".obj")) for s in sorted((ROOT / "src").rglob("*.cpp"))]
	else:
		objects = compileAll(args.version)
		print(f"compiled {len(objects)} sources")
	allMatch = checkFunctions(objects, args.version)
	if args.no_link:
		if allMatch and args.stamp:
			pathlib.Path(args.stamp).touch()
		sys.exit(0 if allMatch else 1)
	code = subprocess.call([sys.executable, str(ROOT / "tools" / "delink" / "relink.py"), "--version", args.version] +
		[str(obj) for _, obj in objects])
	if code != 0:
		sys.exit("relink failed")
	code = subprocess.call([sys.executable, str(ROOT / "tools" / "delink" / "verify.py"), "--version", args.version])
	sys.exit(code or (0 if allMatch else 1))


if __name__ == "__main__":
	main()
