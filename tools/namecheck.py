"""Check that symbols.txt spells our symbols the way the compiler decorates them.

    python tools/namecheck.py [--version PROTOPC_2025]

relink and the checks match symbols.txt names to our objects' symbols by their exact decorated spelling. A name that
is written slightly differently (a type spelled out where the compiler uses a back reference such as `@1@` or `0`,
a different return type, const) matches nothing: the function or global we compiled then does not replace the
engine's, while our own code keeps using its private copy; for a global that splits the state between our code and
the engine's (a buffer the engine fills and our code reads). A symbols.txt name is reported when no object defines
it but an object defines a symbol with the same qualified name (the part before the type) that symbols.txt does not
list and both undecorate to the same declaration (dbghelp). Exit status 1 when anything is reported.
"""

import argparse
import collections
import ctypes
import pathlib
import re
import sys

ROOT = pathlib.Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import objcmp  # noqa: E402


def undecorate(name):
	"""The full C++ declaration dbghelp makes of a decorated name (the name itself when it cannot)."""
	buffer = ctypes.create_string_buffer(2048)
	if ctypes.windll.dbghelp.UnDecorateSymbolName(name.encode("latin-1"), buffer, len(buffer), 0):
		return buffer.value.decode("latin-1")
	return name


def qualified(name):
	"""The decorated qualified name without the type part: "?gBuffer@engine@@3U..." -> "?gBuffer@engine"."""
	match = re.match(r"(\?[^@]+(?:@[^@?$]+)*)@@", name)
	return match.group(1) if match else None


def main():
	parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
	parser.add_argument("--version", default="PROTOPC_2025")
	args = parser.parse_args()
	listed = {}
	for line in (ROOT / "config" / args.version / "symbols.txt").read_text(encoding="utf-8").splitlines():
		match = re.match(r"\s*(\S+)\s*=\s*(0x[0-9A-Fa-f]+)", line)
		if match:
			listed[match.group(1)] = int(match.group(2), 16)
	defined = collections.defaultdict(set)
	for path in sorted((ROOT / "build" / args.version / "obj").rglob("*.obj")):
		for name, value, section, storage in objcmp.Coff(path).symbols:
			if section > 0 and storage == 2:
				defined[name].add(path.name)
	byQualified = collections.defaultdict(list)
	for name in defined:
		key = qualified(name)
		if key and name not in listed:
			byQualified[key].append(name)
	problems = 0
	for name, address in sorted(listed.items(), key=lambda item: item[1]):
		if name in defined:
			continue
		key = qualified(name)
		# the same declaration spelled differently (overloads undecorate differently and are left alone)
		# or cut short (a data name without its final storage letter, `2PAD` for `2PADA`, does not undecorate)
		same = [ours for ours in byQualified.get(key, []) if undecorate(ours) == undecorate(name)
			or ours.startswith(name)] if key else []
		if same:
			problems += 1
			print(f"0x{address:08X} {name}")
			for ours in same:
				print(f"    ours: {ours} ({', '.join(sorted(defined[ours]))})")
	print(f"{len(listed)} symbols.txt names, {problems} spelled differently from a symbol our objects define")
	sys.exit(1 if problems else 0)


if __name__ == "__main__":
	main()
