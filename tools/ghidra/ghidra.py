"""Run Ghidra headless against the project's persistent database in local/ghidra/.

    python tools/ghidra/ghidra.py import               # import orig/<VERSION>/prototypeenginef.dll and auto-analyse (~15 min)
    python tools/ghidra/ghidra.py run Script.java [args...]   # run a script from tools/ghidra/scripts on the saved program
    python tools/ghidra/ghidra.py run Script.java --readonly  # same, without saving changes

Environment: GHIDRA_INSTALL_DIR (default D:/tools/ghidra_12.1.4_PUBLIC), PROTO_JAVA_HOME (default D:/tools/jdk-21.0.12.1+1; replaces JAVA_HOME),
GHIDRA_HEADLESS_MAXMEM (default 12G).
"""

import os
import pathlib
import subprocess
import sys

ROOT = pathlib.Path(__file__).resolve().parents[2]
SCRIPTS = ROOT / "tools" / "ghidra" / "scripts"
PROJECT_DIR = ROOT / "local" / "ghidra"
PROJECT_NAME = "prototype"
VERSION = os.environ.get("PROTO_VERSION", "PROTOPC_2025")
PROGRAM = "prototypeenginef.dll"


def environment():
	env = dict(os.environ)
	env.setdefault("GHIDRA_INSTALL_DIR", r"D:\tools\ghidra_12.1.4_PUBLIC")
	# The system JAVA_HOME may point at an older JDK; Ghidra 12 needs 21+
	env["JAVA_HOME"] = env.get("PROTO_JAVA_HOME", r"D:\tools\jdk-21.0.12.1+1")
	env.setdefault("GHIDRA_HEADLESS_MAXMEM", "12G")
	return env


def headless(args, env):
	launcher = pathlib.Path(env["GHIDRA_INSTALL_DIR"]) / "support" / "analyzeHeadless.bat"
	PROJECT_DIR.mkdir(parents=True, exist_ok=True)
	command = [str(launcher), str(PROJECT_DIR), PROJECT_NAME] + args
	print(" ".join(command), flush=True)
	return subprocess.call(command, env=env)


def main():
	if len(sys.argv) < 2 or sys.argv[1] not in ("import", "run"):
		sys.exit(__doc__)
	env = environment()
	if sys.argv[1] == "import":
		binary = ROOT / "orig" / VERSION / PROGRAM
		code = headless(["-import", str(binary), "-overwrite", "-analysisTimeoutPerFile", "14400",
			"-log", str(PROJECT_DIR / "import.log"), "-scriptlog", str(PROJECT_DIR / "import_script.log")], env)
		sys.exit(code)
	script = sys.argv[2]
	rest = [a for a in sys.argv[3:] if a != "--readonly"]
	args = ["-process", PROGRAM, "-noanalysis", "-scriptPath", str(SCRIPTS), "-postScript", script] + rest
	if "--readonly" in sys.argv:
		args.append("-readOnly")
	args += ["-log", str(PROJECT_DIR / "run.log"), "-scriptlog", str(PROJECT_DIR / "script.log")]
	sys.exit(headless(args, env))


if __name__ == "__main__":
	main()
