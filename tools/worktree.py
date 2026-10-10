"""Git worktrees for parallel agents: each agent works in its own tree and branch, the main session merges.

    python tools/worktree.py new NAME       # ../<repo>_wt/NAME on branch NAME (created from main if missing)
    python tools/worktree.py remove NAME    # removes the worktree (the branch stays)
    python tools/worktree.py list

The ignored directories the tools need (orig/ with the pinned original, local/ with the Ghidra database and the
REA target) are linked into the worktree as junctions, so pin.py verify, objcmp, ninja and the REA tools work there
unchanged; build/ is per worktree. configure.py is run so ninja is ready.
"""

import argparse
import os
import pathlib
import stat
import subprocess
import sys

ROOT = pathlib.Path(__file__).resolve().parents[1]
BASE = ROOT.parent / (ROOT.name + "_wt")
SHARED = ["orig", "local"]


def link(linkPath, target):
	if os.name == "nt":
		subprocess.check_call(["cmd", "/c", "mklink", "/J", str(linkPath), str(target)], stdout=subprocess.DEVNULL)
	else:
		os.symlink(target, linkPath, target_is_directory=True)


def linkShared(path, source):
	"""Junction source into the worktree; when git tracks files inside it (orig/README.md) the directory already
	exists there, so each untracked subdirectory is linked instead."""
	if not source.is_dir():
		return
	target = path / source.name
	if not target.exists():
		link(target, source)
		return
	for entry in source.iterdir():
		if entry.is_dir() and not (target / entry.name).exists():
			link(target / entry.name, entry)


def isJunction(path):
	if os.name != "nt":
		return path.is_symlink()
	return bool(os.lstat(path).st_file_attributes & stat.FILE_ATTRIBUTE_REPARSE_POINT)


def junctions(path):
	for shared in SHARED:
		directory = path / shared
		if not directory.exists():
			continue
		if isJunction(directory):
			yield directory
			continue
		for entry in directory.iterdir():
			if isJunction(entry):
				yield entry


def new(name):
	path = BASE / name
	if path.exists():
		sys.exit(f"{path} already exists")
	BASE.mkdir(exist_ok=True)
	branches = subprocess.run(["git", "branch", "--list", name], cwd=ROOT, capture_output=True, text=True).stdout
	if branches.strip():
		subprocess.check_call(["git", "worktree", "add", str(path), name], cwd=ROOT)
	else:
		subprocess.check_call(["git", "worktree", "add", "-b", name, str(path), "main"], cwd=ROOT)
	for shared in SHARED:
		linkShared(path, ROOT / shared)
	subprocess.check_call([sys.executable, str(path / "tools" / "configure.py")], cwd=path)
	print(f"worktree {path} on branch {name}")


def remove(name):
	path = BASE / name
	# A junction is removed like an empty directory; its target is untouched
	for junction in list(junctions(path)):
		os.rmdir(junction)
	subprocess.check_call(["git", "worktree", "remove", "--force", str(path)], cwd=ROOT)
	print(f"removed {path}")


def main():
	parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
	parser.add_argument("command", choices=["new", "remove", "list"])
	parser.add_argument("name", nargs="?")
	args = parser.parse_args()
	if args.command == "list":
		subprocess.call(["git", "worktree", "list"], cwd=ROOT)
		return
	if not args.name:
		sys.exit("NAME is required")
	(new if args.command == "new" else remove)(args.name)


if __name__ == "__main__":
	main()
