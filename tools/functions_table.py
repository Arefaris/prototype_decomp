"""Write config/<VERSION>/functions.tsv, the denominator of progress: every function of the original except the
incremental link thunks, from a Ghidra export (tools/ghidra/scripts/ExportFunctions.java).

    python tools/functions_table.py local/ghidra/functions.tsv [--version PROTOPC_2025]

Columns: address, size (bytes of the function body as Ghidra sees it), Ghidra's name when it is not a default one.
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
	args = parser.parse_args()
	original = split.Original(args.version)
	rows = list(csv.DictReader(open(args.export, encoding="utf-8"), delimiter="\t"))
	functions = []
	covered = bytearray(original.textEnd - original.textStart)
	for row in rows:
		address = int(row["entry"], 16)
		if address in original.thunks or not original.textStart <= address < original.textEnd:
			continue
		name = row["name"]
		if name.split("::")[-1].startswith(("FUN_", "thunk_FUN_")):
			name = ""
		functions.append((address, int(row["size"]), name))
		for span in row["ranges"].split(","):
			start, end = (int(x, 16) for x in span.split("-"))
			covered[start - original.textStart:end - original.textStart] = b"\x01" * (end - start)
	functions.sort()
	out = ROOT / "config" / args.version / "functions.tsv"
	with open(out, "w", encoding="utf-8", newline="\n") as f:
		f.write("address\tsize\tname\n")
		for address, size, name in functions:
			f.write(f"0x{address:08X}\t{size}\t{name}\n")
	iltEnd = max(original.thunks) + 5
	image, base = original.image, original.base
	uncovered = sum(1 for i in range(iltEnd - original.textStart, len(covered))
		if not covered[i] and image[original.textStart - base + i] != 0xCC)
	print(f"{len(functions)} functions, {sum(s for _, s, _ in functions)} bytes -> {out}")
	print(f"{uncovered} bytes of .text after the link table are in no function and are not padding")


if __name__ == "__main__":
	main()
