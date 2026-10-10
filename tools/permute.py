"""Try orderings of statements, sum terms and operands until a function matches the original.

    python tools/permute.py SOURCE.cpp SYMBOL ADDRESS [--limit 400] [--out best.cpp] [--seed 1]

Mark what may be reordered in a copy of the source:
- lines between "// PERMUTE_LINES_BEGIN" and "// PERMUTE_LINES_END" may be put in any order (any number of lines);
- PERMUTE_SUM(a, b, c) becomes "(a + b + c)" in any order of its terms (terms may contain parentheses);
- PERMUTE_MUL(a, b) becomes "(a * b)" or "(b * a)".
Sums and products may sit inside a lines block and inside each other.
Local search: a state is one ordering per spot; a move swaps two elements of one spot (or moves one element to
another position). Each candidate is compiled with the project's options (tools/build.py) and scored with
tools/objcmp.py; hill climbing with random restarts runs for at most --limit compilations and the best variant is
written to --out. Scores are cached per rendered source.
"""

import argparse
import hashlib
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


class Spot:
	"""A reorderable place in the source: its elements and how an ordering renders. Lines blocks are located by
	their markers; sum and mul spots carry a unique tag (PERMUTE_SUM_3(...)) so they can sit inside lines blocks."""

	def __init__(self, kind, elements, tag=None):
		self.kind, self.elements, self.tag = kind, elements, tag

	def render(self, order):
		parts = [self.elements[i] for i in order]
		if self.kind == "lines":
			return "".join(parts)
		if self.kind == "sum":
			return "(" + " + ".join(parts) + ")"
		return "(" + " * ".join(parts) + ")"


def tagMarkers(text):
	"""Give every PERMUTE_SUM / PERMUTE_MUL occurrence a unique tag: PERMUTE_SUM_<n>( ... )."""
	counter = [0]

	def tag(m):
		counter[0] += 1
		return f"{m.group(1)}_{counter[0]}("
	return re.sub(r"(PERMUTE_(?:SUM|MUL))\(", tag, text)


def spots(text):
	"""text must be tagged. Lines blocks first (outermost), then the tagged sums and products in document order."""
	result = []
	for b in re.finditer(r"([ \t]*// PERMUTE_LINES_BEGIN\n)(.*?)([ \t]*// PERMUTE_LINES_END\n)", text, re.S):
		result.append(Spot("lines", b.group(2).splitlines(keepends=True), tag=("block", b.start(), b.end())))
	for m in re.finditer(r"PERMUTE_(SUM|MUL)_(\d+)\(", text):
		depth, i = 1, m.end()
		while depth:
			depth += text[i] == "("
			depth -= text[i] == ")"
			i += 1
		result.append(Spot(m.group(1).lower(), splitTerms(text[m.end():i - 1]), tag=m.group(0)))
	return result


def render(text, allSpots, state):
	"""Lines blocks are replaced by position (from the end, so earlier offsets stay valid), then every tagged sum or
	product is found by its tag wherever the line reordering put it."""
	source = text
	blocks = [(spot, order) for spot, order in zip(allSpots, state) if spot.kind == "lines"]
	for spot, order in sorted(blocks, key=lambda item: -item[0].tag[1]):
		_, start, end = spot.tag
		source = source[:start] + spot.render(order) + source[end:]
	for spot, order in zip(allSpots, state):
		if spot.kind == "lines":
			continue
		start = source.index(spot.tag)
		depth, i = 1, start + len(spot.tag)
		while depth:
			depth += source[i] == "("
			depth -= source[i] == ")"
			i += 1
		source = source[:start] + spot.render(order) + source[i:]
	return source


def neighbours(state, rng):
	"""Yield states one move away, in random order: swaps and single-element moves within one spot."""
	moves = []
	for k, order in enumerate(state):
		n = len(order)
		for i in range(n):
			for j in range(i + 1, n):
				moves.append((k, "swap", i, j))
				if j != i + 1:
					moves.append((k, "move", i, j))
					moves.append((k, "move", j, i))
	rng.shuffle(moves)
	for k, kind, i, j in moves:
		order = list(state[k])
		if kind == "swap":
			order[i], order[j] = order[j], order[i]
		else:
			order.insert(j, order.pop(i))
		trial = list(state)
		trial[k] = tuple(order)
		yield trial


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
	parser.add_argument("--limit", type=int, default=400)
	parser.add_argument("--out")
	parser.add_argument("--seed", type=int, default=1)
	args = parser.parse_args()
	source = pathlib.Path(args.source)
	text = tagMarkers(source.read_text(encoding="utf-8"))
	allSpots = spots(text)
	rng = random.Random(args.seed)
	print(f"{len(allSpots)} reorderable spots: " + ", ".join(f"{s.kind}[{len(s.elements)}]" for s in allSpots), flush=True)
	cache = {}
	evaluations = 0
	with tempfile.TemporaryDirectory(dir=source.parent) as directory:
		def evaluate(state):
			nonlocal evaluations
			rendered = render(text, allSpots, state)
			key = hashlib.sha1(rendered.encode("utf-8")).hexdigest()
			if key not in cache:
				cache[key] = score(rendered, pathlib.Path(directory), args.symbol, args.address)
				evaluations += 1
			return cache[key]

		initial = [tuple(range(len(s.elements))) for s in allSpots]
		best = (initial, evaluate(initial))
		print(f"  start {best[1]:.1f} %", flush=True)
		state, current = best
		while evaluations < args.limit and best[1] < 100.0:
			improved = False
			for trial in neighbours(state, rng):
				value = evaluate(trial)
				if value > current:
					state, current, improved = trial, value, True
					if current > best[1]:
						best = (state, current)
						print(f"  [{evaluations}] {current:.1f} %", flush=True)
					break
				if evaluations >= args.limit or current >= 100.0:
					break
			if not improved and current < 100.0:
				# Local optimum: restart from a shuffled copy of the best state
				state = [tuple(rng.sample(order, len(order))) for order in best[0]]
				current = evaluate(state)
	out = pathlib.Path(args.out or source.with_suffix(".best.cpp"))
	out.write_text(render(text, allSpots, best[0]), encoding="utf-8")
	print(f"best {best[1]:.1f} % after {evaluations} compilations -> {out}")


if __name__ == "__main__":
	main()
