"""Check our calls into engine code against the callee's calling convention.

	python tools/callcheck.py [--version PROTOPC_2025]

A function of ours that calls an engine function we do not compile relies on our declaration of it. When the
declaration is wrong about the convention, the call compiles and links, objcmp sees nothing at an EQUIVALENT
function, and the stack is off after the call: a member declared as a free function (no `this` in ecx) whose
callee pops its own arguments (`ret N`) while our caller pops them again shifted the frame by 12 bytes and the game
closed at start-up. For every call (rel32) in our objects whose target is an engine address symbols.txt maps and our
objects do not define, the callee's `ret N` is read from the original and compared with the convention the
decorated name declares: a name that says __cdecl (the caller pops) for a callee that pops its own arguments
(`ret N`, N > 0) is reported. Exit status 1 on any.
"""

import argparse
import pathlib
import re
import sys

import pefile

ROOT = pathlib.Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import objcmp  # noqa: E402
from difftest import cfg  # noqa: E402

# The convention letter of a decorated name: after the scope, a free or static function has `Y` or `S` and a member
# an access code followed by a const qualifier (`QAE` = public, non-const, __thiscall); `A` is __cdecl
FREE = re.compile(r"@@[YS]([A-Z])")
MEMBER = re.compile(r"@@[A-X][AB]([A-Z])")


def declaredCdecl(name):
	if not name.startswith("?") or name.startswith("??_"):
		return False
	match = FREE.search(name) or MEMBER.search(name)
	return match is not None and match.group(1) == "A"


def main():
	parser = argparse.ArgumentParser()
	parser.add_argument("--version", default="PROTOPC_2025")
	args = parser.parse_args()
	pe = pefile.PE(str(ROOT / "orig" / args.version / "prototypeenginef.dll"), fast_load=True)
	image = pe.get_memory_mapped_image()
	base = pe.OPTIONAL_HEADER.ImageBase
	addresses = {}
	for line in (ROOT / "config" / args.version / "symbols.txt").read_text(encoding="utf-8").splitlines():
		match = re.match(r"\s*(\S+)\s*=\s*(0x[0-9A-Fa-f]+)\s*;\s*function", line)
		if match:
			addresses[match.group(1)] = int(match.group(2), 16)
	coffs = []
	defined = set()
	for path in sorted((ROOT / "build" / args.version / "obj").rglob("*.obj")):
		coff = objcmp.Coff(path)
		coffs.append((path, coff))
		defined.update(n for n, v, s, st in coff.symbols if s > 0 and coff.sections[s - 1]["name"].startswith(".text"))

	def readCode(address, size):
		offset = address - base
		return bytes(image[offset:offset + size]) if 0 <= offset < len(image) else None

	cleanups = {}
	reported = set()
	for path, coff in coffs:
		for index, sec in enumerate(coff.sections):
			if not sec["name"].startswith(".text") or not sec["raw"]:
				continue
			owners = sorted((v, n) for n, v, s, st in coff.symbols if s == index + 1 and st == 2)
			for offset, symbol, kind in sec["relocs"]:
				name = coff.byIndex.get(symbol)
				if kind != 0x14 or name in defined or name not in addresses or not declaredCdecl(name):
					continue
				target = addresses[name]
				if target not in cleanups:
					cleanups[target] = cfg.stackCleanup(readCode, target)
				popped = cleanups[target]
				if not popped:
					continue
				owner = max((o for o in owners if o[0] <= offset), default=(0, "?"))[1]
				if (owner, name) in reported:
					continue
				reported.add((owner, name))
				print(f"{path.name}: {owner} calls {name} (0x{target:08X}) as __cdecl, but the engine's function pops"
					f" {popped} bytes itself (ret {popped}): a member or __stdcall function declared as a free one")
	print(f"{len(reported)} calls whose declared convention does not match the engine's function")
	sys.exit(1 if reported else 0)


if __name__ == "__main__":
	main()
