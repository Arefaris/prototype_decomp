"""Index the engine addresses that docs/reference mentions: which note talks about which address.

    python tools/reference_index.py      -> docs/reference/address_index.tsv

Each row: address, the notes naming it, and the first line that does (trimmed). Ghidra gets them as bookmarks
(tools/ghidra/scripts/ImportReferenceIndex.java), so a function's notes are one click away.
"""

import collections
import pathlib
import re

ROOT = pathlib.Path(__file__).resolve().parents[1]
ADDRESS = re.compile(r"0x(1[0-1][0-9A-Fa-f]{6})\b")


def main():
	notes = collections.defaultdict(list)
	context = {}
	for path in sorted((ROOT / "docs" / "reference").rglob("*.md")):
		relative = path.relative_to(ROOT / "docs" / "reference").as_posix()
		for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
			for m in ADDRESS.finditer(line):
				address = int(m.group(1), 16)
				if not 0x10001000 <= address < 0x11335000:
					continue
				if relative not in notes[address]:
					notes[address].append(relative)
				if address not in context:
					text = re.sub(r"\s+", " ", line.strip().lstrip("-*| "))
					context[address] = text[:160]
	out = ROOT / "docs" / "reference" / "address_index.tsv"
	with open(out, "w", encoding="utf-8", newline="\n") as f:
		f.write("address\tnotes\tcontext\n")
		for address in sorted(notes):
			f.write(f"0x{address:08X}\t{','.join(notes[address])}\t{context[address].replace(chr(9), ' ')}\n")
	print(f"{len(notes)} addresses in {len({n for v in notes.values() for n in v})} notes -> {out}")


if __name__ == "__main__":
	main()
