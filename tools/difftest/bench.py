"""bench.py: times the difftest replay on the captured states and compares each function's verdict with its
baseline report (local/difftest/reports/*.txt). It runs the same test as difftest.py --replay but does not write
reports, so the baselines stay untouched.

    python tools/difftest/bench.py                  # every function with states under local/difftest/states
    python tools/difftest/bench.py 0x1071B610 ...   # just these functions
    python tools/difftest/bench.py --list           # print the functions with states and their sizes, then stop
    python tools/difftest/bench.py --no-variants    # skip the sentinel variants (faster, fewer blocks covered)
"""

import argparse
import hashlib
import os
import pathlib
import shutil
import struct
import sys
import time

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parents[1]))
from difftest import project, store  # noqa: E402
from difftest.difftest import FunctionTest  # noqa: E402

BASELINE = project.LOCAL.parent / "scratch" / "difftest-speed" / "baseline"


def functionsWithStates():
	"""[address] of every function that has at least one captured state."""
	result = []
	if project.STATES.exists():
		for directory in sorted(project.STATES.iterdir()):
			if not directory.is_dir():
				continue
			if list(directory.glob("*.state")):
				result.append(int(directory.name, 16))
	return result


def stateBytes(paths):
	total = 0
	for path in paths:
		try:
			total += path.stat().st_size
		except OSError:
			pass
	return total


def listMode():
	import unicorn
	import unicorn.x86_const as x86
	print("unicorn %s; UC_HOOK_INSN=%r UC_HOOK_CODE=%r UC_X86_INS_RDTSC=%r" % (getattr(unicorn, "__version__", "?"),
		hasattr(unicorn, "UC_HOOK_INSN"), hasattr(unicorn, "UC_HOOK_CODE"), hasattr(x86, "UC_X86_INS_RDTSC")))
	print("functions with states under %s:" % project.STATES)
	totalStates = 0
	totalStateBytes = 0
	for address in functionsWithStates():
		states = project.listStates(address)
		bytesHere = stateBytes(states)
		totalStates += len(states)
		totalStateBytes += bytesHere
		print("0x%08X  %-60s  %d states, %d bytes" % (address, (project.symbolAt(address) or "")[:60], len(states), bytesHere))
	print("%d states, %d bytes of state files in total" % (totalStates, totalStateBytes))
	for path in (project.STORE / "pages.bin", project.STORE / "pages.idx"):
		if path.exists():
			print("%s: %d bytes" % (path, path.stat().st_size))
	print("baseline reports under %s:" % project.REPORTS)
	if project.REPORTS.exists():
		for path in sorted(project.REPORTS.glob("0x*.txt")):
			print("  %s  %s" % (path.name, verdictKey(baselineVerdict(int(path.stem, 16)))))


def baselineVerdict(address):
	"""The verdict token of the baseline report, or None when there is none. The snapshot copy under BASELINE
	(kept so a difftest run that overwrites local/difftest/reports does not lose the starting point) wins."""
	for directory in (BASELINE, project.REPORTS):
		path = directory / ("0x%08X.txt" % address)
		if not path.exists():
			continue
		verdict = None
		for line in path.read_text(encoding="utf-8").splitlines():
			if line.startswith("verdict: "):
				verdict = line[len("verdict: "):]
		if verdict:
			return verdict
	return None


def verdictKey(verdict):
	"""The leading token: DIFFERENT, VARIANT-DIFFERENT, SAME, NOT REACHED or INCONCLUSIVE."""
	if verdict is None:
		return "?"
	if verdict.startswith("NOT REACHED"):
		return "NOT REACHED"
	return verdict.split(" ", 1)[0]


def diag():
	"""Micro-benchmark of the emulator's fixed costs, to guide the speed work."""
	import time
	from unicorn import Uc, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE, UC_HOOK_MEM_READ, UC_PROT_ALL
	from unicorn.x86_const import UC_X86_REG_EIP, UC_X86_REG_EAX
	uc = Uc(UC_ARCH_X86, UC_MODE_32)
	uc.mem_map(0x1000, 0x1000, UC_PROT_ALL)
	uc.mem_write(0x1000, b"\xEB\xFE")  # jmp $ : one instruction, infinite loop

	def run(count, timeoutMs, withHook):
		uc.reg_write(UC_X86_REG_EIP, 0x1000)
		start = time.perf_counter()
		for _ in range(count):
			uc.emu_start(0x1000, 0, timeout=timeoutMs * 1000, count=1)
		return (time.perf_counter() - start) / count

	for label, count, timeoutMs, withHook in [("t0", 100, 0, False), ("t1ms", 100, 1, False), ("t10ms", 100, 10, False),
		("t50ms", 100, 50, False), ("t100ms", 100, 100, False), ("t1s", 100, 1000, False), ("t20s", 100, 20000, False)]:
		if withHook:
			h = uc.hook_add(UC_HOOK_CODE, lambda uc, a, s, d: None)
		ms = run(count, timeoutMs, withHook) * 1000
		print("emu_start avg %.3f ms (timeout %s)" % (ms, label))
		if withHook:
			uc.hook_del(h)

	from difftest import project
	img = project.image().data
	print("rdtsc (0F 31) occurrences in the engine image: %d" % img.count(b"\x0F\x31"))
	print("cpuid (0F A2) occurrences in the engine image: %d" % img.count(b"\x0F\xA2"))


def copyBaseline():
	"""Snapshots local/difftest/reports/*.txt into BASELINE (never overwrites an existing snapshot)."""
	if not project.REPORTS.exists():
		print("no reports under %s" % project.REPORTS)
		return
	BASELINE.mkdir(parents=True, exist_ok=True)
	count = 0
	for source in sorted(project.REPORTS.glob("0x*.txt")):
		target = BASELINE / source.name
		if target.exists():
			continue
		shutil.copyfile(source, target)
		count += 1
	print("snapshot %d baseline report%s under %s" % (count, "" if count == 1 else "s", BASELINE))


def compareVerdicts(address, verdict):
	base = baselineVerdict(address)
	if base is None:
		return "no baseline", base, verdict
	newKey, baseKey = verdictKey(verdict), verdictKey(base)
	if newKey == baseKey:
		return "same", base, verdict
	if baseKey in ("NOT REACHED", "INCONCLUSIVE") and newKey in ("SAME", "DIFFERENT", "VARIANT-DIFFERENT"):
		return "improved", base, verdict
	return "DIFFER", base, verdict


def allStateFiles():
	"""[state paths] of every .state (and .trim) file under local/difftest/states."""
	result = []
	if project.STATES.exists():
		for directory in sorted(project.STATES.iterdir()):
			if not directory.is_dir():
				continue
			for path in sorted(directory.glob("*")):
				if path.suffix in (".state", ".trim"):
					result.append(path)
	return result


def trimStates(addresses, doVariants, fuzz, maxVariants, margin):
	"""Replays each state to learn which snapshot pages its runs touch, then writes a `NNN.trim` state (same
	header, page table reduced to those pages plus `margin` neighbours) and checks the trimmed state gives the
	same verdict. The original .state is kept; replace it only after the verify line says OK."""
	print("trim: replaying to record the pages each state's runs touch (margin %d)" % margin)
	for address in addresses:
		test = FunctionTest(address)
		states = project.listStates(address)
		if not states:
			continue
		try:
			verdict = test.test(states, doVariants, fuzz, False, maxVariants)
		finally:
			test.pageStore.close()
		trimmedPaths = []
		for path in states:
			pages = test.touched.get(str(path))
			if not pages:
				print("0x%08X %s: no touched pages recorded (skipped)" % (address, path.name))
				continue
			state = store.State.load(path)
			keep = set()
			for page in pages:
				for k in range(-margin, margin + 1):
					candidate = page + k * project.PAGE
					if candidate in state.pages:
						keep.add(candidate)
			trimmed = store.State(state.header, {p: state.pages[p] for p in sorted(keep)})
			out = path.with_suffix(".trim")
			trimmed.save(out)
			trimmedPaths.append(out)
			print("0x%08X %s -> %s: %d -> %d pages (%d -> %d bytes)" % (address, path.name, out.name,
				len(state.pages), len(keep), path.stat().st_size, out.stat().st_size))
		# the trimmed state must reproduce the verdict before the original is replaced
		if trimmedPaths:
			verify = FunctionTest(address)
			try:
				verifyVerdict = verify.test(trimmedPaths, doVariants, fuzz, False, maxVariants)
			finally:
				verify.pageStore.close()
			ok = verdictKey(verdict) == verdictKey(verifyVerdict)
			print("0x%08X trim verify: %s vs %s -> %s" % (address, verdictKey(verdict), verdictKey(verifyVerdict),
				"OK" if ok else "MISMATCH"))


def compactStore():
	"""Rewrites pages.bin/pages.idx to hold only the pages the state files still reference, and remaps every
	state's page table to the new offsets. The store is content-addressed, so the page data is unchanged. A
	`NNN.trim` state wins over its `NNN.state` original, so compaction after --trim drops the rest."""
	files = allStateFiles()
	if not files:
		print("no state files under %s" % project.STATES)
		return
	byState = {}
	for path in files:
		key = (path.parent, path.stem)
		existing = byState.get(key)
		if existing is None or (path.suffix == ".trim" and existing.suffix == ".state"):
			byState[key] = path
	files = list(byState.values())
	referenced = set()
	states = []
	for path in files:
		try:
			state = store.State.load(path)
		except Exception:
			continue
		states.append((path, state))
		referenced.update(state.pages.values())
	old = store.PageStore()
	newBin = project.STORE / "pages.bin.new"
	newIdx = project.STORE / "pages.idx.new"
	offsetMap = {}
	newOffset = 0
	with open(newBin, "wb") as binFile, open(newIdx, "wb") as idxFile:
		for offset in sorted(referenced):
			page = old.get(offset)
			digest = hashlib.blake2b(page, digest_size=16).digest()
			offsetMap[offset] = newOffset
			binFile.write(page)
			idxFile.write(digest + struct.pack("<Q", newOffset))
			newOffset += store.PAGE
	old.close()
	for path, state in states:
		state.pages = {address: offsetMap[offset] for address, offset in state.pages.items()}
		state.save(path)
	os.replace(newBin, project.STORE / "pages.bin")
	os.replace(newIdx, project.STORE / "pages.idx")
	print("compacted store: %d unique pages referenced by %d states -> %d bytes" % (len(referenced), len(states), newOffset))


def main():
	parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
	parser.add_argument("addresses", nargs="*", help="function addresses (default: every function with states)")
	parser.add_argument("--list", action="store_true", help="print the functions with states and their sizes, then stop")
	parser.add_argument("--copy-baseline", action="store_true", help="snapshot local/difftest/reports into the scratch baseline directory, then stop")
	parser.add_argument("--diag", action="store_true", help="micro-benchmark the emulator and then stop")
	parser.add_argument("--trim", action="store_true", help="rewrite each state to reference only the pages its runs touch (writes NNN.trim)")
	parser.add_argument("--trim-margin", type=int, default=1, help="neighbour pages kept around each touched page when trimming (default 1)")
	parser.add_argument("--compact", action="store_true", help="rewrite the page store to drop pages no state references, then stop")
	parser.add_argument("--no-variants", action="store_true", help="skip the sentinel variants")
	parser.add_argument("--fuzz", type=int, default=0, metavar="N", help="N random mutations of the inputs per function")
	parser.add_argument("--max-variants", type=int, default=240)
	parser.add_argument("--states", type=int, default=0, help="replay at most this many states per function (0 = all)")
	parser.add_argument("--budget", type=int, default=5000000, help="instruction budget per run")
	parser.add_argument("--obj", help="object holding our function (default: the build's object of its unit)")
	parser.add_argument("--symbol", help="decorated name of our function (default: symbols.txt at the address)")
	parser.add_argument("--unit", action="store_true", help="resolve calls to functions our object defines to our copies")
	parser.add_argument("--profile", action="store_true", help="print per-hook timing for each run")
	args = parser.parse_args()
	if args.profile:
		import difftest.machine
		difftest.machine.PROFILE = True

	if args.list:
		listMode()
		return
	if args.copy_baseline:
		copyBaseline()
		return
	if args.diag:
		diag()
		return
	if args.compact:
		compactStore()
		return
	if args.trim:
		addresses = [int(item, 16) for item in args.addresses] if args.addresses else functionsWithStates()
		if not addresses:
			print("no functions with states under %s" % project.STATES)
			return
		trimStates(addresses, not args.no_variants, args.fuzz, args.max_variants, args.trim_margin)
		return

	addresses = [int(item, 16) for item in args.addresses] if args.addresses else functionsWithStates()
	if not addresses:
		print("no functions with states under %s" % project.STATES)
		return

	totalStart = time.time()
	rows = []
	for address in addresses:
		test = FunctionTest(address, args.obj, args.symbol, args.unit, args.budget)
		states = project.listStates(address)
		if args.states:
			states = states[:args.states]
		start = time.time()
		try:
			verdict = test.test(states, not args.no_variants, args.fuzz, False, args.max_variants)
		finally:
			test.pageStore.close()
		elapsed = time.time() - start
		comparison, base, new = compareVerdicts(address, verdict)
		rows.append((address, verdict, comparison, base, elapsed, len(states)))
		print("0x%08X  %-6.1f s  %s  [%s]  %s" % (address, elapsed, verdict, comparison, base or "no baseline"), flush=True)

	total = time.time() - totalStart
	print("=" * 100)
	for address, verdict, comparison, base, elapsed, count in rows:
		print("0x%08X  %d states  %6.1f s  %-50s  %s" % (address, count, elapsed, verdict[:50], comparison))
	print("total: %.1f s over %d functions" % (total, len(rows)))


if __name__ == "__main__":
	main()
