"""Extract the Visual Studio 2005 SP1 x86 compiler (cl 14.00.50727.762) from Microsoft's Windows SDK Update for
Windows Vista ISO, without installing anything.

    python tools/toolchain/setup_vc8.py ISO [--out D:/tools/vc8]

Get the ISO from the Microsoft Download Center (1 237 436 416 bytes):
  https://download.microsoft.com/download/4/2/6/42684501-9ec5-43dd-9dfe-c8c9dfa6a66f/6.1.6000.16384.10.WindowsSDK_Vista_Feb2007Update_rtm.DVD.Rel.iso

Steps: check the ISO's SHA-256, pull the compiler MSI and its cabinets out with 7-Zip, require a valid Microsoft
Authenticode signature on each of them, run an administrative install (msiexec /a: unpacks files, writes nothing to
the system), then check that cl.exe reports 14.00.50727.762. The extracted binaries themselves are unsigned, as all
of Microsoft's 2005 binaries were; their integrity comes from the signed cabinets.
"""

import argparse
import hashlib
import pathlib
import shutil
import subprocess
import sys
import tempfile

ISO_SHA256 = "f544c8ec782921a64ffed4b41206aa3d6e16d0cf47c78a5bc26308ae0c2251ea"
SEVEN_ZIP = r"C:\Program Files\7-Zip\7z.exe"
EXPECTED_VERSION = "14.00.50727.762"


def sha256(path):
	digest = hashlib.sha256()
	with open(path, "rb") as f:
		for block in iter(lambda: f.read(1 << 20), b""):
			digest.update(block)
	return digest.hexdigest()


def signatureStatus(path):
	command = f"(Get-AuthenticodeSignature -LiteralPath '{path}').Status"
	return subprocess.run(["powershell", "-NoProfile", "-Command", command], capture_output=True, text=True).stdout.strip()


def main():
	parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
	parser.add_argument("iso")
	parser.add_argument("--out", default=r"D:\tools\vc8")
	args = parser.parse_args()
	out = pathlib.Path(args.out)

	print("checking ISO hash...", flush=True)
	if sha256(args.iso) != ISO_SHA256:
		sys.exit(f"{args.iso}: unexpected SHA-256; expected {ISO_SHA256}")

	stage = pathlib.Path(tempfile.mkdtemp(prefix="vc8_stage_"))
	try:
		subprocess.run([SEVEN_ZIP, "x", "-y", f"-o{stage}", args.iso, "Setup/WinSDKCompiler-*"], check=True, stdout=subprocess.DEVNULL)
		packages = sorted((stage / "Setup").iterdir())
		for package in packages:
			status = signatureStatus(package)
			if status != "Valid":
				sys.exit(f"{package.name}: Authenticode status {status}; refusing to unpack")
		print(f"{len(packages)} packages, all signed by Microsoft", flush=True)
		msi = stage / "Setup" / "WinSDKCompiler-x86.msi"
		log = stage / "admin.log"
		code = subprocess.call(["msiexec", "/a", str(msi), f"TARGETDIR={out}", "/qn", "/L*v", str(log)])
		if code != 0:
			sys.exit(f"msiexec /a failed with {code}; see {log}")
	finally:
		shutil.rmtree(stage, ignore_errors=True)

	cl = out / "VC" / "Bin" / "cl.exe"
	banner = subprocess.run([str(cl)], capture_output=True, text=True, env={"PATH": str(cl.parent)}).stderr
	if EXPECTED_VERSION not in banner:
		sys.exit(f"{cl}: unexpected version banner:\n{banner}")
	print(f"{cl}: {EXPECTED_VERSION}")
	for name in ("cl.exe", "c1.dll", "c1xx.dll", "c2.dll", "link.exe", "lib.exe", "mspdb80.dll"):
		print(f"  {sha256(cl.parent / name)}  {name}")


if __name__ == "__main__":
	main()
