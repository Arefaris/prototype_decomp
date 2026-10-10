"""Copy the original game binaries into orig/<VERSION>/ and check them against config/<VERSION>/config.yml.

    python tools/pin.py fetch [--game DIR] [--version PROTOPC_2025]
    python tools/pin.py verify [--version PROTOPC_2025]

orig/ is the source of truth for every tool: a later Steam update must not move the addresses under our feet.
"""

import argparse
import hashlib
import pathlib
import shutil
import sys

import yaml

ROOT = pathlib.Path(__file__).resolve().parents[1]
DEFAULT_GAME = r"D:\SteamLibrary\steamapps\common\Prototype"
DEFAULT_VERSION = "PROTOPC_2025"


def loadConfig(version):
	with open(ROOT / "config" / version / "config.yml", encoding="utf-8") as f:
		return yaml.safe_load(f)


def sha256(path):
	digest = hashlib.sha256()
	with open(path, "rb") as f:
		for block in iter(lambda: f.read(1 << 20), b""):
			digest.update(block)
	return digest.hexdigest()


def verify(version):
	config = loadConfig(version)
	ok = True
	for name, info in config["files"].items():
		path = ROOT / "orig" / version / name
		if not path.exists():
			print(f"MISSING  {path}")
			ok = False
			continue
		actual = sha256(path)
		if actual != info["sha256"]:
			print(f"MISMATCH {path}\n  expected {info['sha256']}\n  actual   {actual}")
			ok = False
		else:
			print(f"OK       {path}")
	return ok


def fetch(version, gameDir):
	config = loadConfig(version)
	target = ROOT / "orig" / version
	target.mkdir(parents=True, exist_ok=True)
	for name, info in config["files"].items():
		source = pathlib.Path(gameDir) / name
		actual = sha256(source)
		if actual != info["sha256"]:
			sys.exit(f"{source}: sha256 {actual} is not the {version} build ({info['sha256']}); "
				"is the Steam copy updated? Add a new config/<VERSION>/ for it.")
		shutil.copy2(source, target / name)
		print(f"copied   {source} -> {target / name}")
	return verify(version)


def main():
	parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
	parser.add_argument("command", choices=["fetch", "verify"])
	parser.add_argument("--version", default=DEFAULT_VERSION)
	parser.add_argument("--game", default=DEFAULT_GAME)
	args = parser.parse_args()
	ok = fetch(args.version, args.game) if args.command == "fetch" else verify(args.version)
	sys.exit(0 if ok else 1)


if __name__ == "__main__":
	main()
