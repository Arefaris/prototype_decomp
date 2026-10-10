"""List likely function entry points Ghidra's auto-analysis missed, for tools/ghidra/scripts/CreateFunctions.java.

    python tools/ghidra/ghidra.py run ExportFunctions.java local/ghidra/functions.tsv --readonly
    python tools/function_candidates.py local/ghidra/functions.tsv [--version PROTOPC_2025]   -> local/ghidra/candidates.txt

The original was linked incrementally and without /OPT:REF, so it keeps unreferenced functions, and every function
has an incremental link thunk. Candidates: targets of those thunks, vftable slots (config/<VERSION>/rtti.tsv), and the
first byte after each run of int3 padding that no known function covers.
"""

import argparse
import csv
import pathlib
import sys

ROOT = pathlib.Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools" / "delink"))
import split  # noqa: E402


def main():
	parser = argparse.ArgumentParser()
	parser.add_argument("export")
	parser.add_argument("--version", default="PROTOPC_2025")
	parser.add_argument("--out", default=str(ROOT / "local" / "ghidra" / "candidates.txt"))
	args = parser.parse_args()
	original = split.Original(args.version)
	image, base = original.image, original.base
	start, end = original.textStart, original.textEnd
	covered = bytearray(end - start)
	starts = set()
	with open(args.export, encoding="utf-8") as f:
		for row in csv.DictReader(f, delimiter="\t"):
			starts.add(int(row["entry"], 16))
			for span in row["ranges"].split(","):
				a, b = (int(x, 16) for x in span.split("-"))
				covered[a - start:b - start] = b"\x01" * (b - a)
	candidates = set(original.thunks.values())
	with open(ROOT / "config" / args.version / "rtti.tsv", encoding="utf-8") as f:
		for row in csv.DictReader(f, delimiter="\t"):
			vftable = int(row["vftable"], 16)
			for slot in range(int(row["slots"])):
				target = original.u32(vftable + 4 * slot)
				candidates.add(original.thunks.get(target, target))
	i = max(original.thunks) + 5 - start
	while i < len(covered):
		if image[start - base + i] == 0xCC:
			j = i
			while j < len(covered) and image[start - base + j] == 0xCC:
				j += 1
			if j < len(covered) and not covered[j]:
				candidates.add(start + j)
			i = j
		else:
			i += 1
	candidates = sorted(c for c in candidates if start <= c < end and c not in starts and c not in original.thunks)
	pathlib.Path(args.out).write_text("".join(f"0x{c:08X}\n" for c in candidates), encoding="utf-8")
	print(f"{len(candidates)} candidates -> {args.out}")


if __name__ == "__main__":
	main()
