"""difftest: does an EQUIVALENT function behave like the engine's? Replays real entry states captured from the
game on both and compares everything they do (docs/workflow.md, "Checking an EQUIVALENT function").

    python tools/difftest/difftest.py 0x1071B610 --capture 3 [--seconds 30] [--play "keys w:2.5,:2"]
        attach to the test copy in OP_ORIGINAL_DIR (the original DLL in it), break at every function's entry in
        one game session and save up to 3 states under local/difftest/states/<address>/. By default the states are
        taken live (the emulator runs the engine and ours against the frozen process, saving only the pages the
        runs touch); --full copies the whole memory instead. 'all' arms every EQUIVALENT function; extra addresses
        (e.g. the crash case 0x1071B610) can be added: difftest.py all 0x1071B610 --capture 3
    python tools/difftest/difftest.py 0x1071B610 [--fuzz 200] [--no-variants] [--obj X.obj] [--symbol NAME]
        replay every captured state on the engine's function and on ours (from the build's object unless --obj),
        then sentinel variants of the inputs for the blocks the real states miss, then random mutations
    python tools/difftest/difftest.py all [--capture 3 --seconds 120]
        every function annotated EQUIVALENT

The report (printed, and local/difftest/reports/<address>.txt) ends in one verdict per function: DIFFERENT (a real
state behaves differently: the function is not equivalent), VARIANT-DIFFERENT (only a perturbed state differs: look
at it), SAME with the coverage of the engine's basic blocks, NOT REACHED (no state captured), INCONCLUSIVE.
"""

import argparse
import bisect
import pathlib
import struct
import sys
import time

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parents[1]))
from difftest import project, store, machine, loader, compare, variants, cfg, externals  # noqa: E402


class Result:
	def __init__(self, label, findings, engine=None, ours=None, context=None, error=None):
		self.label = label
		self.findings = findings
		self.engine = engine
		self.ours = ours
		self.context = context
		self.error = error

	def worst(self):
		if self.error:
			return "ERROR"
		for severity in ("INCONCLUSIVE", "FAIL", "WARN"):
			if any(f.severity == severity for f in self.findings):
				return severity
		return "OK"


# wall-clock budget for the sentinel variants of one function (each variant may run up to --timeout)
VARIANT_SECONDS = 60.0

class FunctionTest:
	def __init__(self, address, objPath=None, symbol=None, unitMode=False, budget=5000000, timeout=20.0, pageStore=None):
		self.address = address
		self.symbol = symbol or project.symbolAt(address)
		self.unit, self.status, located = project.locate(address)
		self.obj = pathlib.Path(objPath) if objPath else located
		self.unitMode = unitMode
		self.budget = budget
		self.timeout = timeout
		self.image = project.image()
		sizes = project.functionSizes()
		self.size = project.functionExtent(address)
		self.code = self.image.read(address, self.size)
		self.blocks, self.insns = cfg.basicBlocks(self.code, address)
		self.rets = cfg.retImmediates(self.code, address)
		self.argBytes = max(self.rets) if self.rets else 0
		self.returnKind = project.returnKind(self.symbol)
		self.functionStarts = set(sizes)
		self.starts = sorted(sizes)
		self.pageStore = pageStore or store.PageStore()
		self.lines = []
		self.noted = False
		self.touched = {}  # state path -> set of snapshot pages the runs on it read or wrote

	def say(self, text=""):
		self.lines.append(text)
		print(text, flush=True)

	def containingFunction(self, address):
		i = bisect.bisect_right(self.starts, address) - 1
		return self.starts[i] if i >= 0 else None

	# --- static: calling convention ---------------------------------------------------------------------------

	def conventionCheck(self):
		findings = []
		coff = loader.objcmp.Coff(self.obj)
		try:
			oursCode, mask = coff.function(self.symbol)
		except KeyError:
			return [compare.Finding("FAIL", "object", "%s is not in %s" % (self.symbol, self.obj))]
		oursRets = cfg.retImmediates(oursCode, 0)
		engineInputs = cfg.registerInputs(self.code, self.address)
		oursInputs = cfg.registerInputs(oursCode, 0)
		self.say("convention: engine ret %s, ours ret %s; register inputs engine %s, ours %s; %s per the name"
			% (sorted(self.rets), sorted(oursRets), sorted(engineInputs) or "-", sorted(oursInputs) or "-", project.callingConvention(self.symbol)))
		if oursRets and self.rets and oursRets != self.rets:
			findings.append(compare.Finding("FAIL", "convention", "stack cleanup differs: engine ret %s, ours ret %s" % (sorted(self.rets), sorted(oursRets))))
		extra = oursInputs - engineInputs - {"ebp"}
		if extra:
			findings.append(compare.Finding("FAIL", "convention", "ours reads %s before writing them; the engine's function does not take them" % sorted(extra)))
		missing = engineInputs - oursInputs - {"ebp"}
		if missing:
			findings.append(compare.Finding("WARN", "convention", "the engine's function takes %s; ours never reads them" % sorted(missing)))
		sites, words = cfg.directCallSites(self.image, self.address)
		pushes = {}
		regsSet = {}
		cleanups = {}
		for site, viaThunk in sites[:40]:
			info = cfg.callSiteArguments(self.image, site, self.containingFunction(site))
			pushes[info["pushes"]] = pushes.get(info["pushes"], 0) + 1
			for reg in info["regs"]:
				regsSet[reg] = regsSet.get(reg, 0) + 1
			cleanups[info["callerCleanup"]] = cleanups.get(info["callerCleanup"], 0) + 1
		self.say("call sites: %d direct (%d through thunks), %d data words hold the address; pushes before the call %s; registers set %s; caller cleanup %s"
			% (len(sites), sum(1 for s in sites if s[1]), words, dict(sorted(pushes.items())), dict(sorted(regsSet.items())), dict(sorted(cleanups.items()))))
		if sites and self.rets and max(self.rets) == 0 and all(c == 0 for c in cleanups) and max(pushes, default=0) > 0:
			findings.append(compare.Finding("WARN", "convention", "callers push arguments and clean nothing while the function returns with a plain ret"))
		if sites and self.rets and max(self.rets) > 0 and any(c > 0 for c in cleanups):
			findings.append(compare.Finding("WARN", "convention", "some callers clean the stack although the function pops %d bytes itself" % max(self.rets)))
		for f in findings:
			self.say("  " + str(f))
		return findings

	# --- dynamic: one state ------------------------------------------------------------------------------------

	def runState(self, state, label, overlay=None, policyVariant=0, emulator=None, deadline=None):
		policy = externals.Policy(policyVariant)
		engineRange = (self.address, self.address + self.size)
		if emulator is None:
			emulator = machine.Machine(state, self.pageStore, overlay, policy, self.functionStarts)
		else:
			emulator.policy = policy
			emulator.setOverlay(overlay)
		engineTimeout = self.timeout
		if deadline is not None:
			engineTimeout = min(engineTimeout, max(0.001, deadline - time.time()))
		engineTrace = emulator.run(self.address, self.argBytes, self.budget, engineTimeout, watch=[engineRange])
		loaded = emulator.loaded
		if loaded is None:
			def importFallback(name):
				"""A C runtime import (`_memcpy`, `__imp__memset`): the engine's IAT slot, or what it holds."""
				viaSlot = name.startswith("__imp_")
				base = (name[6:] if viaSlot else name).split("@")[0]
				imports = self.image.imports()
				# a C symbol carries one leading underscore (`__purecall` is the import `_purecall`)
				slot = imports.get(base[1:] if base.startswith("_") else base) or imports.get(base.lstrip("_"))
				if slot is None:
					return None
				if viaSlot:
					return slot
				data = emulator.readSnapshot(slot, 4)
				return struct.unpack("<I", data)[0] if data is not None else None

			try:
				loaded = loader.load(self.obj, self.symbol, emulator.write, emulator.layout.code, emulator.layout.data, self.unitMode, importFallback)
			except loader.LoadError as e:
				result = Result(label, [], engineTrace, None, None, error=str(e))
				result.machine = emulator
				return result
			# functions placed beside ours (local helpers), not the compiler's labels inside them ($LN8)
			emulator.ours = {a: n for n, a in loaded.placed.items() if emulator.layout.code <= a < emulator.layout.data and not n.startswith("$")}
			emulator.resetToClean()  # the engine run's writes are not part of our clean memory
			emulator.seal()
			emulator.loaded = loaded
		oursRange = (loaded.entry, loaded.entry + loaded.size)
		oursTimeout = self.timeout
		if deadline is not None:
			oursTimeout = min(oursTimeout, max(0.001, deadline - time.time()))
		oursTrace = emulator.run(loaded.entry, self.argBytes, self.budget, oursTimeout, watch=[oursRange])
		context = compare.Context(emulator, emulator, self.returnKind, self.argBytes, engineRange, oursRange)
		context.placedVtables = {a: n for n, a in loaded.placed.items() if n.startswith("??_7")}
		findings = compare.compareTraces(engineTrace, oursTrace, context)
		result = Result(label, findings, engineTrace, oursTrace, context)
		result.loaded = loaded
		result.machine = emulator
		return result

	def blocksHit(self, traces):
		hit = set()
		for trace in traces:
			for start, end in self.blocks:
				if any(start <= a < end for a in trace.executed):
					hit.add((start, end))
		return hit

	def oursBlocks(self, result):
		mo = result.context.ours
		start, end = result.context.oursRange
		code = mo.read(start, end - start)
		blocks, insns = cfg.basicBlocks(code, start)
		hit = {b for b in blocks if any(b[0] <= a < b[1] for a in result.ours.executed)}
		return hit, blocks

	# --- the whole test ------------------------------------------------------------------------------------------

	def test(self, states, doVariants=True, fuzz=0, verbose=False, maxVariants=240):
		self.say("=" * 100)
		self.say("%s 0x%08X  %s" % (self.symbol, self.address, self.status or "unannotated"))
		self.say("object %s; engine %d bytes, %d blocks, %d instructions" % (self.obj, self.size, len(self.blocks), len(self.insns)))
		if self.obj is None or not self.obj.exists():
			self.say("verdict: INCONCLUSIVE (no object: run ninja, or pass --obj)")
			return "INCONCLUSIVE"
		conventionFindings = self.conventionCheck()
		if not states:
			self.say("no captured states: capture some with --capture N while the game runs the path")
			self.say("verdict: NOT REACHED")
			return "NOT REACHED"
		realResults = []
		for path in states:
			state = store.State.load(path)
			t0 = time.time()
			result = self.runState(state, path.name)
			realResults.append(result)
			self.report(result, verbose, time.time() - t0)
		errors = [r for r in realResults if r.error]
		if errors:
			self.say("verdict: INCONCLUSIVE (%s)" % errors[0].error)
			return "INCONCLUSIVE"
		realHit = self.blocksHit([r.engine for r in realResults])
		self.say("coverage on real states: %d/%d engine blocks" % (len(realHit), len(self.blocks)))
		variantResults = []
		variantHit = set(realHit)
		if doVariants and realResults:
			variantResults = self.runVariants(realResults, states, variantHit, verbose, maxVariants,
				time.time() + VARIANT_SECONDS)
		fuzzResults = []
		if fuzz and realResults and not any(r.worst() == "FAIL" for r in variantResults):
			fuzzResults = self.runFuzz(realResults, states, variantHit, verbose, fuzz)
		unreached = [b for b in self.blocks if b not in variantHit]
		self.say("coverage with variants: %d/%d engine blocks%s" % (len(variantHit), len(self.blocks),
			"; unreached: " + ", ".join("0x%08X" % b[0] for b in unreached) if unreached else ""))
		oursHit, oursBlocks = self.oursBlocks(realResults[0]) if realResults[0].ours else (set(), [])
		for r in realResults[1:] + variantResults + fuzzResults:
			if r.ours and r.context:
				h, _ = self.oursBlocks(r)
				oursHit |= h
		self.say("coverage of ours: %d/%d blocks" % (len(oursHit), len(oursBlocks)))
		self.touched = {}
		for r, path in zip(realResults, states):
			machine = getattr(r, "machine", None)
			if machine is not None:
				self.touched[str(path)] = set(machine.touched)
		verdict = self.verdict(conventionFindings, realResults, variantResults + fuzzResults, realHit, variantHit)
		self.say("verdict: %s" % verdict)
		return verdict

	def runVariants(self, realResults, states, variantHit, verbose, maxVariants, deadline=None):
		results = []
		perState = max(1, maxVariants // len(realResults))
		for result, path in zip(realResults, states):
			if result.worst() in ("INCONCLUSIVE", "FAIL"):
				# INCONCLUSIVE: the engine's own run does not complete, so perturbing it cannot add evidence.
				# FAIL: the real state already differs, so the verdict is DIFFERENT and variants add no verdict.
				continue
			budget = perState
			machine = result.machine
			state = machine.state
			candidates = variants.perturbations(result.engine, result.context, result.context.engine)
			# external answers that fail, as a variant class of its own
			candidates.insert(0, ("externals fail (variant policy 1)", None))
			tried = 0
			for label, overlay in candidates:
				if budget <= 0:
					break
				if deadline is not None and time.time() >= deadline:
					break
				variant = self.runState(state, "%s %s" % (path.name, label), overlay, 1 if overlay is None else 0, machine, deadline)
				budget -= 1
				tried += 1
				if variant.error:
					continue
				newBlocks = self.blocksHit([variant.engine]) - variantHit
				variantHit |= newBlocks
				# the report needs a variant's findings and coverage, not its memory logs (up to ACCESS_LIMIT
				# entries per run, kept for every variant of the function otherwise)
				for trace in (variant.engine, variant.ours):
					if trace is not None:
						trace.reads, trace.readOrder, trace.writes, trace.calls = set(), [], [], []
				if variant.worst() == "FAIL" or newBlocks or verbose:
					self.say("variant %s: %s%s" % (variant.label, variant.worst(), " (+%d new engine blocks)" % len(newBlocks) if newBlocks else ""))
					for f in variant.findings:
						if f.severity == "FAIL" or verbose:
							self.say("    " + str(f))
				results.append(variant)
				if variant.worst() == "FAIL":
					# a perturbed state differs: the verdict is already VARIANT-DIFFERENT
					break
			self.say("%s: %d sentinel variants tried" % (path.name, tried))
		return results

	def runFuzz(self, realResults, states, variantHit, verbose, count):
		results = []
		per = max(1, count // len(realResults))
		for seed, (result, path) in enumerate(zip(realResults, states)):
			if result.worst() in ("INCONCLUSIVE", "FAIL"):
				continue
			machine = result.machine
			state = machine.state
			fails = 0
			newTotal = 0
			for label, overlay in variants.fuzzVariants(result.engine, result.context, result.context.engine, per, seed=seed + 1):
				variant = self.runState(state, "%s %s" % (path.name, label), overlay, 0, machine)
				if variant.error:
					continue
				newBlocks = self.blocksHit([variant.engine]) - variantHit
				variantHit |= newBlocks
				newTotal += len(newBlocks)
				if variant.worst() == "FAIL":
					fails += 1
					if fails <= 5 or verbose:
						self.say("fuzz %s: FAIL" % variant.label)
						for f in variant.findings:
							if f.severity == "FAIL":
								self.say("    " + str(f))
				results.append(variant)
			self.say("%s: %d fuzz runs, %d differ, %d new engine blocks" % (path.name, per, fails, newTotal))
		return results

	def report(self, result, verbose, seconds):
		if result.error:
			self.say("%s: ERROR %s" % (result.label, result.error))
			return
		e, o = result.engine, result.ours
		hit = self.blocksHit([e])
		self.say("%s: %s  (engine %d insns, ours %d insns, %d/%d engine blocks, %.1f s)" % (result.label, result.worst(), e.instructions, o.instructions, len(hit), len(self.blocks), seconds))
		for f in result.findings:
			if f.severity != "NOTE" or verbose:
				self.say("    " + str(f))
		loaded = getattr(result, "loaded", None)
		if loaded is not None and not self.noted:
			self.noted = True
			layout = result.context.layout
			statics = sorted(n for n, a in loaded.placed.items() if layout.data <= a < layout.ret and not n.startswith(("__real@", "??_C@", "__xmm@", "$")))
			if statics:
				self.say("    NOTE statics: our object defines %s itself; symbols.txt does not map them, so ours (and the hybrid DLL) use their own copies, not the engine's" % ", ".join(statics[:6]))
		if verbose:
			for c in e.calls[:20]:
				self.say("    engine call %s ecx=0x%08X %s" % (c["name"], c["ecx"], " ".join("0x%08X" % a for a in c["args"][:4])))

	def verdict(self, conventionFindings, realResults, synthetic, realHit, variantHit):
		if any(f.severity == "FAIL" for f in conventionFindings):
			return "DIFFERENT (calling convention)"
		conclusive = [r for r in realResults if r.worst() != "INCONCLUSIVE"]
		if any(r.worst() == "FAIL" for r in conclusive):
			return "DIFFERENT"
		if not conclusive:
			first = next((f for f in realResults[0].findings if f.severity == "INCONCLUSIVE"), None)
			return "INCONCLUSIVE (%s)" % (first.text if first else "the engine's run does not complete in the emulator")
		if any(r.worst() == "FAIL" for r in synthetic):
			return "VARIANT-DIFFERENT (real states agree, %d/%d blocks; a perturbed state differs)" % (len(realHit), len(self.blocks))
		warn = any(r.worst() == "WARN" for r in conclusive)
		skipped = len(realResults) - len(conclusive)
		return "SAME (%d states, %d/%d engine blocks on real states, %d/%d with variants%s%s)" % (len(conclusive), len(realHit), len(self.blocks),
			len(variantHit), len(self.blocks), ", with warnings" if warn else "", ", %d inconclusive states" % skipped if skipped else "")

	def save(self):
		project.REPORTS.mkdir(parents=True, exist_ok=True)
		(project.REPORTS / ("0x%08X.txt" % self.address)).write_text("\n".join(self.lines) + "\n", encoding="utf-8")


def parseAddresses(items):
	result = []
	for item in items:
		if item == "all":
			result.extend(address for address, status, unit in project.annotated(("equivalent",)))
		else:
			result.append(int(item, 16))
	seen = set()
	unique = []
	for address in result:
		if address not in seen:
			seen.add(address)
			unique.append(address)
	return unique


def main():
	parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
	parser.add_argument("addresses", nargs="+", help="function addresses, or 'all' for every EQUIVALENT function")
	parser.add_argument("--capture", type=int, metavar="N", help="capture N states per function from the running test copy")
	parser.add_argument("--seconds", type=float, default=30.0, help="how long to wait for hits (default 30)")
	parser.add_argument("--spacing", type=float, default=1.0, help="seconds between two captures of one function")
	parser.add_argument("--full", action="store_true", help="capture every committed page (the old full-copy capture) instead of the live one")
	parser.add_argument("--freeze", type=float, default=3.0, help="per-state freeze budget for the live capture in seconds (default 3)")
	parser.add_argument("--margin", type=int, default=1, help="neighbour pages saved around each touched page in the live capture (default 1)")
	parser.add_argument("--fresh", action="store_true", help="remove each address's existing states before capturing (re-capture from 000)")
	parser.add_argument("--clear", action="store_true", help="remove each address's existing states, then stop")
	parser.add_argument("--play", action="append", metavar="CMD",
		help="a gamectl command to run once the breakpoints are in, e.g. \"keys w:2.5,:2\" or \"teleport 1000 20 -500\" (repeatable, run in order)")
	parser.add_argument("--replay", action="store_true", help="replay captured states (the default without --capture)")
	parser.add_argument("--no-variants", action="store_true", help="skip the sentinel variants")
	parser.add_argument("--fuzz", type=int, default=0, metavar="N", help="N random mutations of the inputs per function")
	parser.add_argument("--max-variants", type=int, default=240)
	parser.add_argument("--states", type=int, default=0, help="replay at most this many states per function (0 = all)")
	parser.add_argument("--obj", help="object holding our function (default: the build's object of its unit)")
	parser.add_argument("--symbol", help="decorated name of our function (default: symbols.txt at the address)")
	parser.add_argument("--unit", action="store_true", help="resolve calls to functions our object defines to our copies, as the hybrid DLL does")
	parser.add_argument("--budget", type=int, default=5000000, help="instruction budget per run")
	parser.add_argument("--timeout", type=float, default=20.0, help="wall-clock budget per emulated run (default 20 s)")
	parser.add_argument("-v", "--verbose", action="store_true")
	args = parser.parse_args()
	addresses = parseAddresses(args.addresses)
	if args.clear:
		from difftest import capture
		capture.clearStates(addresses)
		return
	if args.capture:
		from difftest import capture
		capture.capture(addresses, args.capture, args.seconds, args.spacing, args.play, full=args.full,
			obj=args.obj, symbol=args.symbol, unit=args.unit, budget=args.budget, timeout=args.timeout,
			freeze=args.freeze, margin=args.margin, fresh=args.fresh)
		if not args.replay:
			return
	verdicts = {}
	for address in addresses:
		test = FunctionTest(address, args.obj, args.symbol, args.unit, args.budget, args.timeout)
		states = project.listStates(address)
		if args.states:
			states = states[:args.states]
		try:
			verdicts[address] = test.test(states, not args.no_variants, args.fuzz, args.verbose, args.max_variants)
		finally:
			test.save()
			test.pageStore.close()
	if len(addresses) > 1:
		print("=" * 100)
		for address, verdict in verdicts.items():
			print("0x%08X %-60s %s" % (address, (project.symbolAt(address) or "")[:60], verdict))


if __name__ == "__main__":
	main()
