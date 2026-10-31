"""objcmp every annotated function of the given sources against the original (the merge check).

	python tools/unitcheck.py [--version PROTOPC_2025] [--all] [--quiet] [FILE.cpp ...]

For each `// FUNCTION: ENGINE 0x...` that is neither EQUIVALENT nor NONMATCHING, the function is looked up in the
object the build made from that source under every name symbols.txt gives the address, and compared like
tools/objcmp.py does (relocations as wildcards, constants and call/data targets checked). Prints each function that
is not 100.0 % (with objcmp's diff unless --quiet) and a summary line; exit status 1 when one does not match.
--all checks every source under src/. A shared header change changes every unit that includes it: check them all.
"""

import argparse
import difflib
import pathlib
import re
import sys

import pefile

ROOT = pathlib.Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import objcmp  # noqa: E402


def annotations(source):
	"""[(address, status)] of a source's annotated functions; status is "match", "equivalent" or "nonmatching"."""
	lines = source.read_text(encoding="utf-8", errors="replace").splitlines()
	result = []
	for i, line in enumerate(lines):
		match = re.search(r"//\s*FUNCTION:\s*ENGINE\s+(0x[0-9A-Fa-f]+)", line)
		if not match:
			continue
		comments = []
		for following in lines[i + 1:i + 4]:
			if not following.strip().startswith("//") or "FUNCTION:" in following:
				break
			comments.append(following)
		status = "match"
		if any("NONMATCHING" in c for c in comments):
			status = "nonmatching"
		elif any("EQUIVALENT" in c for c in comments):
			status = "equivalent"
		result.append((int(match.group(1), 16), status))
	return result


def namesByAddress(version):
	result = {}
	for line in (ROOT / "config" / version / "symbols.txt").read_text(encoding="utf-8").splitlines():
		match = re.match(r"\s*(\S+)\s*=\s*(0x[0-9A-Fa-f]+)\s*;\s*function", line)
		if match:
			result.setdefault(int(match.group(2), 16), []).append(match.group(1))
	return result


def compare(coff, name, address, image, base, known):
	"""(ratio, problems, diff lines) of our function against the original at address."""
	code, mask = coff.function(name)
	original = image[address - base:address - base + len(code)]
	same = sum(1 for k in range(len(code)) if mask[k] or code[k] == original[k])
	ratio = same / len(code)
	problems = []
	if ratio == 1.0:
		problems = objcmp.checkConstants(coff, name, original, image, base, known) \
			+ objcmp.checkTargets(coff, name, original, address, image, base, known)
		if problems:
			ratio = (len(code) - 1) / len(code)
	diff = []
	if ratio < 1.0:
		ours = [t for _, _, t in objcmp.disassemble(code, address)]
		theirs = [t for _, _, t in objcmp.disassemble(bytes(original), address)]
		diff = list(difflib.unified_diff(theirs, ours, "original", "ours", n=3, lineterm=""))
	return ratio, len(code), problems, diff


def engineOperands(image, base, address, size):
	"""The addresses the engine's function names in its operands (the data it reads: literals, constants)."""
	original = bytes(image[address - base:address - base + size])
	operands = set()
	for _, _, text in objcmp.disassemble(original, address):
		operands.update(int(h, 16) for h in re.findall(r"0x([0-9a-f]{6,8})\b", text))
	return {a for a in operands if base <= a < base + len(image)}


def literalProblems(coff, name, image, base, operands):
	"""An EQUIVALENT function's instructions differ, but every string literal it reads must be one the engine's
	function reads too (a literal with an unescaped backslash once broke every audio path). Float constants are left
	out: the engine loads some of them with other instructions (fld1, a table with an index)."""
	defined = {n: (value, section) for n, value, section, storage in coff.symbols if section > 0}
	problems = []
	for offset, target, kind in coff.relocations(name):
		if kind != 0x06:
			continue
		if target.startswith("??_C@") and target in defined:
			value, section = defined[target]
			sec = coff.sections[section - 1]
			wanted = bytes(coff.data[sec["raw"] + value:sec["raw"] + sec["size"]])
			if wanted == b"\0":
				continue  # "": a developer message of the original's that the repository leaves out
		else:
			continue
		if not any(bytes(image[a - base:a - base + len(wanted)]) == wanted for a in operands):
			problems.append(f"+0x{offset:X}: {target} ({wanted[:40]!r}) is read by no operand of the engine's function")
	return problems


PUSH_IMMEDIATE = re.compile(r"^push\s+(0x[0-9a-f]+|\d+)$")


def immediates(code, address, mask=None):
	"""The immediate arguments the function pushes (relocated operands left out): a size passed to operator new, a
	flag, a count. Other immediates are left out: the compiler may pick another instruction and constant for them."""
	values = []
	for at, size, text in objcmp.disassemble(code, address):
		match = PUSH_IMMEDIATE.match(text)
		if not match:
			continue
		if mask is not None and any(mask[at - address + k] for k in range(size)):
			continue  # a relocation: an address, not a value
		value = int(match.group(1), 0)
		if value > 1:
			values.append(value)
	return values


def immediateProblems(coff, name, image, base, address, size):
	"""The pushed immediates of an EQUIVALENT function must be the engine's: register allocation and scheduling do
	not change them, a wrong struct size (operator new of a class four bytes short) does."""
	code, mask = coff.function(name)
	ours = immediates(code, address, mask)
	original = bytes(image[address - base:address - base + size])
	theirs = immediates(original, address)
	# the engine may build the same value in a register first (mov eax, 0xFF000000 / push eax)
	anywhere = {int(m.group(1), 0) for _, _, text in objcmp.disassemble(original, address)
		for m in [re.search(r"(?:,\s*|^push\s+)(0x[0-9a-f]+|\d+)$", text)] if m}
	extra = sorted(set(ours) - anywhere)
	if not extra:
		return []
	missing = sorted(set(theirs) - set(ours))
	return [f"pushed values only ours has: {', '.join(hex(v) for v in extra)}; the engine pushes instead: "
		f"{', '.join(hex(v) for v in missing) or 'none'}"]


def main():
	parser = argparse.ArgumentParser()
	parser.add_argument("files", nargs="*")
	parser.add_argument("--version", default="PROTOPC_2025")
	parser.add_argument("--all", action="store_true")
	parser.add_argument("--quiet", action="store_true")
	args = parser.parse_args()
	sources = sorted((ROOT / "src").rglob("*.cpp")) if args.all else [pathlib.Path(f).resolve() for f in args.files]
	names = namesByAddress(args.version)
	known = objcmp.loadSymbols(args.version)
	pe = pefile.PE(str(ROOT / "orig" / args.version / "prototypeenginef.dll"), fast_load=True)
	image = pe.get_memory_mapped_image()
	base = pe.OPTIONAL_HEADER.ImageBase
	sizes = {}
	for line in (ROOT / "config" / args.version / "functions.tsv").read_text(encoding="utf-8").splitlines()[1:]:
		fields = line.split("\t")
		sizes[int(fields[0], 16)] = int(fields[1])
	# a function split into chunks has only its first chunk's size in functions.tsv; symbols.txt gives the whole
	for line in (ROOT / "config" / args.version / "symbols.txt").read_text(encoding="utf-8").splitlines():
		match = re.match(r"\s*\S+\s*=\s*(0x[0-9A-Fa-f]+)\s*;\s*function\s+size:(0x[0-9A-Fa-f]+)", line)
		if match:
			address = int(match.group(1), 16)
			sizes[address] = max(sizes.get(address, 0), int(match.group(2), 16))
	checked = 0
	failed = 0
	literalsChecked = 0
	literalsFailed = 0
	for source in sources:
		relative = source.relative_to(ROOT / "src").with_suffix(".obj")
		objectPath = ROOT / "build" / args.version / "obj" / relative
		wanted = [(a, s) for a, s in annotations(source) if s in ("match", "equivalent")]
		if not wanted:
			continue
		if not objectPath.exists():
			print(f"{source.relative_to(ROOT)}: no object {objectPath.relative_to(ROOT)} (build it first)")
			failed += len(wanted)
			continue
		coff = objcmp.Coff(objectPath)
		defined = {n for n, v, s, st in coff.symbols if s > 0 and coff.sections[s - 1]["name"].startswith(".text")}
		for address, status in wanted:
			candidates = [n for n in names.get(address, []) if n in defined]
			if status == "equivalent":
				if not candidates or address not in sizes:
					continue
				literalsChecked += 1
				problems = literalProblems(coff, candidates[0], image, base,
					engineOperands(image, base, address, sizes[address])) \
					+ immediateProblems(coff, candidates[0], image, base, address, sizes[address])
				if problems:
					literalsFailed += 1
					print(f"{candidates[0]} vs 0x{address:08X} (EQUIVALENT): {len(problems)} literal(s) or pushed value(s) the engine's"
						f" function does not read  [{source.relative_to(ROOT)}]")
					for problem in problems:
						print("  " + problem)
				continue
			checked += 1
			if not candidates:
				failed += 1
				print(f"0x{address:08X} ({source.relative_to(ROOT)}): no symbol of this address in symbols.txt is"
					" defined in the object")
				continue
			best = None
			for name in candidates:
				result = compare(coff, name, address, image, base, known)
				if best is None or result[0] > best[1][0]:
					best = (name, result)
				if result[0] == 1.0:
					break
			name, (ratio, size, problems, diff) = best
			if ratio == 1.0:
				continue
			failed += 1
			print(f"{name} vs 0x{address:08X}: {size} bytes, {ratio:.1%} identical (relocations as wildcards)"
				+ (f", {len(problems)} constant(s)/target(s) differ" if problems else "")
				+ f"  [{source.relative_to(ROOT)}]")
			for problem in problems:
				print("  " + problem)
			if not args.quiet:
				for line in diff[:60]:
					print("  " + line)
	print(f"{checked} checked, {failed} not matching; {literalsChecked} EQUIVALENT checked for their literals,"
		f" {literalsFailed} reading a literal the engine's function does not")
	sys.exit(1 if failed or literalsFailed else 0)


if __name__ == "__main__":
	main()
