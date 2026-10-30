"""Resolve the merge conflicts of line lists: config/<version>/symbols.txt and docs/engine_worklist.md.

	python tools/mergesym.py [--version PROTOPC_2025] [FILE ...]

Two branches that each add symbols.txt lines (or worklist lines) at the same place conflict although both sides are
wanted. In each conflicted file every `<<<<<<< / ======= / >>>>>>>` block is replaced by the lines of both sides
(ours first, then those of theirs not already in ours). Afterwards symbols.txt is checked for an address given to
two different function names and for a name given twice: both are printed for a decision by hand (an address can
legitimately carry a scalar and a vector deleting destructor, or two functions folded into one). Exit status 1 when
a conflict block is malformed or such duplicates are new.
"""

import argparse
import pathlib
import re
import subprocess
import sys
import time

ROOT = pathlib.Path(__file__).resolve().parents[1]


def resolve(path):
	"""Replaces the conflict blocks of path with the union of both sides; returns the number of blocks."""
	lines = path.read_bytes().decode("utf-8").split("\n")
	out = []
	blocks = 0
	i = 0
	while i < len(lines):
		if not lines[i].startswith("<<<<<<< "):
			out.append(lines[i])
			i += 1
			continue
		ours, theirs = [], []
		i += 1
		while not lines[i].startswith("======="):
			if lines[i].startswith(("<<<<<<< ", ">>>>>>> ")):
				sys.exit(f"{path}: malformed conflict block at line {i + 1}")
			ours.append(lines[i])
			i += 1
		i += 1
		while not lines[i].startswith(">>>>>>> "):
			theirs.append(lines[i])
			i += 1
		i += 1
		out.extend(ours)
		out.extend(line for line in theirs if line not in ours)
		blocks += 1
	# right after `git merge` the file is sometimes still held open (a scanner): opening it fails with EINVAL
	for attempt in range(10):
		try:
			path.write_bytes("\n".join(out).encode("utf-8"))
			break
		except OSError:
			if attempt == 9:
				raise
			time.sleep(1)
	return blocks


def duplicates(path):
	"""({address: [names]} given to several function names, {name: count} given more than once)."""
	byAddress = {}
	byName = {}
	for line in path.read_text(encoding="utf-8").splitlines():
		match = re.match(r"\s*(\S+)\s*=\s*(0x[0-9A-Fa-f]+)\s*;\s*(\w+)", line)
		if not match:
			continue
		name, address, kind = match.group(1), int(match.group(2), 16), match.group(3)
		byName[name] = byName.get(name, 0) + 1
		if kind == "function" and not name.startswith(("??_E", "??_G")):
			byAddress.setdefault(address, set()).add(name)
	return {a: sorted(n) for a, n in byAddress.items() if len(n) > 1}, {n: c for n, c in byName.items() if c > 1}


def main():
	parser = argparse.ArgumentParser()
	parser.add_argument("files", nargs="*")
	parser.add_argument("--version", default="PROTOPC_2025")
	args = parser.parse_args()
	symbols = ROOT / "config" / args.version / "symbols.txt"
	before = ({}, {})
	if symbols.exists():
		head = subprocess.run(["git", "show", f"HEAD:config/{args.version}/symbols.txt"], cwd=ROOT,
			capture_output=True).stdout.decode("utf-8", errors="replace")
		temporary = ROOT / "build" / "symbols.head.txt"
		temporary.parent.mkdir(exist_ok=True)
		temporary.write_text(head, encoding="utf-8")
		before = duplicates(temporary)
	files = [pathlib.Path(f) for f in args.files] or [symbols, ROOT / "docs" / "engine_worklist.md"]
	for path in files:
		if path.exists():
			print(f"{path.relative_to(ROOT) if path.is_absolute() else path}: {resolve(path)} conflict blocks resolved")
	addresses, names = duplicates(symbols)
	newAddresses = {a: n for a, n in addresses.items() if a not in before[0] or before[0][a] != n}
	newNames = {n: c for n, c in names.items() if n not in before[1]}
	for address, nameList in sorted(newAddresses.items()):
		print(f"  new address with two names: 0x{address:08X} {', '.join(nameList)}")
	for name, count in sorted(newNames.items()):
		print(f"  new name given {count} times: {name}")
	sys.exit(1 if newAddresses or newNames else 0)


if __name__ == "__main__":
	main()
