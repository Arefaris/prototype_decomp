"""Read the EQUIVALENT functions statically: does ours do the engine's instructions, only placed differently?

	python tools/shrinkcheck.py [--all] [--version PROTOPC_2025]

For every EQUIVALENT whose reason names shrink-wrap (--all: every EQUIVALENT) ours and the engine's instructions are
compared as multisets, with the pushes and pops of callee-saved registers left out, esp offsets, absolute addresses
and call/jump targets normalised. A shrink-wrap difference (the engine saves registers in the entry block, ours
behind the early exit) leaves the same multiset; anything else shows as instructions only one side has: a literal
where the engine loads a constant, a store ours lacks, a field read at another offset. Each such function is printed
for reading; many are harmless (a duplicated epilogue, other registers), some are not (an enum list registered with
zero entries hid behind "shrink-wrap" this way).
"""

import argparse
import collections
import pathlib
import re
import sys

import pefile

ROOT = pathlib.Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import objcmp  # noqa: E402

SAVED = re.compile(r"^(push|pop)\s+(esi|edi|ebx|ebp)$")


def normalise(text):
	text = re.sub(r"0x1[0-9a-f]{7}", "A", text)
	text = re.sub(r"(dword|word|byte) ptr \[0x[0-9a-f]+\]", lambda m: m.group(1) + " ptr [A]", text)
	text = re.sub(r"\[esp \+ (0x)?[0-9a-f]+\]|\[esp\]", "[esp+N]", text)
	text = re.sub(r"^(j\w+|call)\s+.*", r"\1 T", text)
	return text


def instructions(code, address):
	out = []
	for _, _, text in objcmp.disassemble(code, address):
		text = " ".join(text.split())
		if SAVED.match(text) or text.startswith("int3") or text == "nop":
			continue
		out.append(normalise(text))
	return out


def main():
	parser = argparse.ArgumentParser()
	parser.add_argument("--all", action="store_true")
	parser.add_argument("--version", default="PROTOPC_2025")
	args = parser.parse_args()
	pe = pefile.PE(str(ROOT / "orig" / args.version / "prototypeenginef.dll"), fast_load=True)
	image = pe.get_memory_mapped_image()
	base = pe.OPTIONAL_HEADER.ImageBase
	sizes = {}
	for line in (ROOT / "config" / args.version / "functions.tsv").read_text(encoding="utf-8").splitlines()[1:]:
		parts = line.split("\t")
		sizes[int(parts[0], 16)] = int(parts[1])
	names = {}
	for line in (ROOT / "config" / args.version / "symbols.txt").read_text(encoding="utf-8").splitlines():
		match = re.match(r"\s*(\S+)\s*=\s*(0x[0-9A-Fa-f]+)\s*;\s*function", line)
		if match:
			names.setdefault(int(match.group(2), 16), []).append(match.group(1))
	checked = flagged = 0
	for source in sorted((ROOT / "src").rglob("*.cpp")):
		lines = source.read_text(encoding="utf-8", errors="replace").splitlines()
		objectPath = ROOT / "build" / args.version / "obj" / source.relative_to(ROOT / "src").with_suffix(".obj")
		coff = None
		for i, line in enumerate(lines):
			match = re.search(r"//\s*FUNCTION:\s*ENGINE\s+(0x[0-9A-Fa-f]+)", line)
			if not match:
				continue
			reason = " ".join(x for x in lines[i + 1:i + 3] if "EQUIVALENT" in x)
			if not reason or (not args.all and "shrink" not in reason.lower()):
				continue
			if coff is None:
				if not objectPath.exists():
					break
				coff = objcmp.Coff(objectPath)
			address = int(match.group(1), 16)
			code = mask = None
			for name in names.get(address, []):
				try:
					code, mask = coff.function(name)
					break
				except KeyError:
					continue
			if code is None:
				continue
			# relocated fields hold zeros in the object: an address-like marker normalises like the engine's
			code = bytes(0x11 if mask[k] else code[k] for k in range(len(code)))
			original = bytes(image[address - base:address - base + sizes.get(address, len(code))])
			ours = collections.Counter(instructions(code, address))
			theirs = collections.Counter(instructions(original, address))
			checked += 1
			extra = ours - theirs
			if extra:
				flagged += 1
				print(f"{source.relative_to(ROOT)}:{i + 1} 0x{address:08X} {name[:70]}")
				print("   ours only:   ", list(extra.elements())[:6])
				print("   engine only: ", list((theirs - ours).elements())[:6])
	print(f"{checked} checked, {flagged} with instructions beyond shrink-wrap")


if __name__ == "__main__":
	main()
