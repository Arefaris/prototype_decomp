"""Find what breaks the hybrid DLL in the game: relink without some units (or with some functions left to the engine),
launch the test copy, teleport and fight, and tell whether the game survived.

	python tools/gamebisect.py try [--exclude LIST] [--keep-game]   # relink without the units in LIST (one .cpp per line)
	python tools/gamebisect.py units LIST                           # exclude each half of LIST in turn, then narrow down
	python tools/gamebisect.py wrap FILE.cpp [0xADDRESS ...]        # put these definitions (default: every EQUIVALENT)
	                                                            # under #ifdef NONMATCHING, so the engine's code runs

`try` needs OP_ORIGINAL_DIR naming the test copy (as gamectl.py); it prints `RESULT OK`, `RESULT CRASH` (and the
fault the proxy logged) or `RESULT FROZEN` (the game runs but Alex stays where the teleport put him: the
simulation does not update). `units` assumes the full list crashes and that leaving all of LIST out does not; it reports
the unit whose absence alone makes the game survive (or the smallest set it found). Only one bisect may run at a
time: they share the relinked DLL and the game.
"""

import argparse
import os
import pathlib
import re
import subprocess
import sys
import time

ROOT = pathlib.Path(__file__).resolve().parents[1]
VERSION = "PROTOPC_2025"
OUT = ROOT / "build" / VERSION / "bisect"
TELEPORT_HEIGHT = 30
PLAY = [f"teleport 300 {TELEPORT_HEIGHT} -400","keys e:0.3,:0.8,lmb:0.3,:0.8,rmb:0.6,:1,space:0.3,lmb:0.4,:1"]


def relinkObjects():
	"""The objects the relink rule of build.ninja takes, in order."""
	for line in (ROOT / "build.ninja").read_text(encoding="utf-8").splitlines():
		if line.startswith("build ") and ": relink " in line:
			return line.split(": relink ", 1)[1].split(" |")[0].split()
	sys.exit("no relink rule in build.ninja (run tools/configure.py)")


def sourceOf(objectPath):
	return re.sub(r"\.obj$", ".cpp", objectPath.replace(f"build/{VERSION}/obj/", "src/"))


def gamectl(*command, timeout=300):
	result = subprocess.run([sys.executable, str(ROOT / "tools" / "re" / "gamectl.py"), *command], cwd=ROOT,
		capture_output=True, text=True, timeout=timeout)
	return result.returncode, (result.stdout + result.stderr).strip()


def lastFault():
	log = pathlib.Path(os.environ["OP_ORIGINAL_DIR"]) / "opprobe_d3d9.log"
	if not log.exists():
		return ""
	faults = [line for line in log.read_text(encoding="utf-8", errors="replace").splitlines() if line.startswith("fault")]
	return "\n".join(faults[-2:])


def tryBuild(excluded, keepGame=False):
	"""Relinks without the excluded sources, plays the test; True when the game survived."""
	if "OP_ORIGINAL_DIR" not in os.environ:
		sys.exit("set OP_ORIGINAL_DIR to the test copy")
	keep = [o for o in relinkObjects() if sourceOf(o) not in excluded]
	OUT.mkdir(parents=True, exist_ok=True)
	objectList = OUT / "objects.rsp"
	objectList.write_text("\n".join(keep) + "\n", encoding="utf-8")
	relink = subprocess.run([sys.executable, str(ROOT / "tools" / "delink" / "relink.py"), "--version", VERSION, "--out",
		str(OUT), f"@{objectList}"], cwd=ROOT, capture_output=True, text=True)
	if relink.returncode != 0:
		sys.exit("relink failed: " + (relink.stdout + relink.stderr)[-2000:])
	gamectl("stop")
	time.sleep(3)
	subprocess.run([sys.executable, str(ROOT / "tools" / "re" / "testcopy.py"), "--dll", str(OUT / "prototypeenginef.dll")],
		cwd=ROOT, check=True, capture_output=True)
	before = lastFault()
	code, text = gamectl("launch", "1", timeout=420)
	ok = code == 0
	for command in PLAY:
		if not ok:
			break
		gamectl(*command.split())
	frozen = False
	if ok:
		code, text = gamectl("where")
		ok = code == 0
		# Alex is teleported 12 m above the ground: a game whose simulation does not run leaves him in the air
		feet = re.search(r"feet\s+(\S+)\s+(\S+)\s+(\S+)", text)
		frozen = ok and (feet is None or float(feet.group(2)) > TELEPORT_HEIGHT - 1)
	fault = lastFault()
	if not keepGame:
		gamectl("stop")
	print(f"RESULT {'FROZEN' if frozen else 'OK' if ok else 'CRASH'}"
		+ (f"\n{fault}" if fault and fault != before else ""))
	return ok and not frozen


def readList(path):
	return [line.strip().replace("\\", "/") for line in pathlib.Path(path).read_text(encoding="utf-8").splitlines() if line.strip()]


def units(listPath):
	candidates = readList(listPath)
	while len(candidates) > 1:
		half = candidates[:len(candidates) // 2]
		rest = candidates[len(candidates) // 2:]
		print(f"excluding {len(half)} of {len(candidates)}: ", end="", flush=True)
		if tryBuild(set(half)):
			candidates = half
			continue
		print(f"excluding the other {len(rest)}: ", end="", flush=True)
		if tryBuild(set(rest)):
			candidates = rest
			continue
		print("neither half alone helps: more than one unit is involved; the candidates are", " ".join(candidates))
		return
	print("culprit:", candidates[0] if candidates else "none")


def wrap(path, addresses):
	"""Puts the definitions of the given annotated functions (default: every EQUIVALENT) inside #ifdef NONMATCHING."""
	lines = pathlib.Path(path).read_text(encoding="utf-8").split("\n")
	out = []
	wrapped = 0
	i = 0
	while i < len(lines):
		match = re.search(r"// FUNCTION: ENGINE (0x[0-9A-Fa-f]+)", lines[i])
		if match:
			address = int(match.group(1), 16)
			equivalent = any("EQUIVALENT" in x for x in lines[i + 1:i + 3])
			if (address in addresses) or (not addresses and equivalent):
				out.append(lines[i])
				i += 1
				while lines[i].strip().startswith("//"):
					out.append(lines[i])
					i += 1
				out.append("#ifdef NONMATCHING")
				depth = 0
				started = False
				while True:
					out.append(lines[i])
					depth += lines[i].count("{") - lines[i].count("}")
					started = started or "{" in lines[i]
					i += 1
					if started and depth == 0:
						break
				out.append("#endif")
				wrapped += 1
				continue
		out.append(lines[i])
		i += 1
	pathlib.Path(path).write_text("\n".join(out), encoding="utf-8", newline="\n")
	print(f"{wrapped} definitions wrapped (restore the file from git afterwards)")


def main():
	parser = argparse.ArgumentParser()
	sub = parser.add_subparsers(dest="command", required=True)
	t = sub.add_parser("try")
	t.add_argument("--exclude")
	t.add_argument("--keep-game", action="store_true")
	u = sub.add_parser("units")
	u.add_argument("list")
	w = sub.add_parser("wrap")
	w.add_argument("file")
	w.add_argument("addresses", nargs="*")
	args = parser.parse_args()
	if args.command == "try":
		sys.exit(0 if tryBuild(set(readList(args.exclude)) if args.exclude else set(), args.keep_game) else 1)
	elif args.command == "units":
		units(args.list)
	else:
		wrap(args.file, {int(a, 16) for a in args.addresses})


if __name__ == "__main__":
	main()
