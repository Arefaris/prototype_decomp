"""Try orderings of statements and of sum terms until a function matches the original.

    python tools/permute.py SOURCE.cpp SYMBOL ADDRESS [--limit 3000] [--out best.cpp]

Mark what may be reordered in a copy of the source:
- lines between "// PERMUTE_LINES_BEGIN" and "// PERMUTE_LINES_END" are tried in every order;
- PERMUTE_SUM(a, b, c) is replaced by "a + b + c" in every order of its terms (terms may contain parentheses);
- PERMUTE_MUL(a, b) becomes "(a * b)" or "(b * a)".
Variants are compiled with the project's options (tools/build.py) and scored with tools/objcmp.py by hill climbing
(one spot changed at a time, random restarts) for at most --limit compilations; the best is written to --out.
"""

import argparse
import itertools
import pathlib
import random
import re
import subprocess
import sys
import tempfile

ROOT = pathlib.Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402


def splitTerms(text):
	terms, depth, current = [], 0, ""
	for ch in text:
		if ch == "," and depth == 0:
			terms.append(current.strip())
			current = ""
			continue
		depth += ch == "("
		depth -= ch == ")"
		current += ch
	terms.append(current.strip())
	return terms




def findMarked(text, marker):
	"""[(start, end, terms)] of MARKER(...) occurrences."""
	found = []
	for m in re.finditer(marker + r"\(", text):
		depth, i = 1, m.end()
		while depth:
			depth += text[i] == "("
			depth -= text[i] == ")"
			i += 1
		found.append((m.start(), i, splitTerms(text[m.end():i - 1])))
	return found


def groups(text):
	"""Every reorderable spot as (start, end, [replacement texts]). PERMUTE_MUL(a, b) gives "a * b" or "b * a"."""
	result = []
	for b in re.finditer(r"([ \t]*// PERMUTE_LINES_BEGIN\n)(.*?)([ \t]*// PERMUTE_LINES_END\n)", text, re.S):
		lines = b.group(2).splitlines(keepends=True)
		result.append((b.start(), b.end(), ["".join(p) for p in itertools.permutations(lines)]))
	for start, end, terms in findMarked(text, "PERMUTE_SUM"):
		result.append((start, end, [" + ".join(p) for p in itertools.permutations(terms)]))
	for start, end, terms in findMarked(text, "PERMUTE_MUL"):
		result.append((start, end, ["(" + " * ".join(p) + ")" for p in itertools.permutations(terms)]))
	# Nested markers are not supported: the spots must not overlap
	return sorted(result)


def render(text, spots, state):
	source = text
	for (start, end, options), choice in sorted(zip(spots, state), key=lambda item: -item[0][0]):
		source = source[:start] + options[choice] + source[end:]
	return source


def score(source, directory, symbol, address):
	cpp = directory / "permute_candidate.cpp"
	obj = directory / "permute_candidate.obj"
	cpp.write_text(source, encoding="utf-8")
	compiled = subprocess.run([sys.executable, str(ROOT / "tools" / "toolchain" / "cl8.py"), "cl"] + build.CFLAGS +
		[f"/Fo{obj}", str(cpp)], capture_output=True, text=True)
	if compiled.returncode != 0:
		return -1.0
	result = subprocess.run([sys.executable, str(ROOT / "tools" / "objcmp.py"), str(obj), symbol, address, "--quiet"],
		capture_output=True, text=True)
	m = re.search(r"([\d.]+)% identical", result.stdout)
	return float(m.group(1)) if m else -1.0


def main():
	parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
	parser.add_argument("source")
	parser.add_argument("symbol")
	parser.add_argument("address")
	parser.add_argument("--limit", type=int, default=3000)
	parser.add_argument("--out")
	args = parser.parse_args()
	source = pathlib.Path(args.source)
	text = source.read_text(encoding="utf-8")
	spots = groups(text)
	total = 1
	for _, _, options in spots:
		total *= len(options)
	print(f"{len(spots)} reorderable spots, {total} combinations", flush=True)
	random.seed(1)
	cache = {}
	evaluations = 0
	with tempfile.TemporaryDirectory(dir=source.parent) as directory:
		def evaluate(state):
			nonlocal evaluations
			key = tuple(state)
			if key not in cache:
				cache[key] = score(render(text, spots, state), pathlib.Path(directory), args.symbol, args.address)
				evaluations += 1
			return cache[key]

		best = ([0] * len(spots), evaluate([0] * len(spots)))
		print(f"  start {best[1]:.1f} %", flush=True)
		# Hill climbing over one spot at a time, with random restarts, until --limit compilations
		while evaluations < args.limit and best[1] < 100.0:
			state = list(best[0]) if random.random() < 0.7 else [random.randrange(len(o)) for _, _, o in spots]
			current = evaluate(state)
			improved = True
			while improved and evaluations < args.limit and current < 100.0:
				improved = False
				for k in random.sample(range(len(spots)), len(spots)):
					for choice in random.sample(range(len(spots[k][2])), len(spots[k][2])):
						if choice == state[k]:
							continue
						trial = list(state)
						trial[k] = choice
						value = evaluate(trial)
						if value > current:
							state, current, improved = trial, value, True
							break
					if evaluations >= args.limit or current >= 100.0:
						break
			if current > best[1]:
				best = (state, current)
				print(f"  [{evaluations}] {current:.1f} %", flush=True)
			if total <= len(cache):
				break
	out = pathlib.Path(args.out or source.with_suffix(".best.cpp"))
	out.write_text(render(text, spots, best[0]), encoding="utf-8")
	print(f"best {best[1]:.1f} % after {evaluations} compilations -> {out}")


if __name__ == "__main__":
	main()
