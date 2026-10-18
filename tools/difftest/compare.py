"""Compares the engine's run with ours on the same state: faults, return registers, stack cleanup, callee-saved
registers, every byte written outside the function's own stack frame (final value and order), the reads of shared
memory, and the call log with the arguments each callee takes. Findings carry a severity: FAIL (behaves
differently), WARN (a difference that may matter: write order, extra reads), NOTE (informational)."""

import struct

from . import project, cfg

CALLEE_SAVED = ("ebx", "esi", "edi", "ebp")


class Finding:
	def __init__(self, severity, kind, text):
		self.severity = severity
		self.kind = kind
		self.text = text

	def __str__(self):
		return "%s %s: %s" % (self.severity, self.kind, self.text)


class Context:
	"""What the comparison needs to know besides the two traces."""

	def __init__(self, machineEngine, machineOurs, returnKind, argBytes, engineRange, oursRange):
		self.engine = machineEngine
		self.ours = machineOurs
		self.returnKind = returnKind
		self.argBytes = argBytes
		self.engineRange = engineRange
		self.oursRange = oursRange
		self.image = project.image()
		self.layout = machineEngine.layout
		self.entryEsp = machineEngine.entryEsp
		self.argsEnd = self.entryEsp + 4 + max(argBytes, 32)
		self.argCounts = {}
		self.conventions = {}

	def ownObjectSize(self, address):
		"""The bytes from `address` to the end of the data symbol of ours that holds it (to the next symbol or the
		section's end), at most 64; None when `address` is not in the data ours placed."""
		for start, end in getattr(self, "dataSections", ()):
			if start <= address < end:
				following = [a for a in self.dataSymbols if address < a < end]
				return min(64, (min(following) if following else end) - address)
		return None

	def isArgs(self, address):
		return self.entryEsp + 4 <= address < self.argsEnd

	def isOursRegion(self, address):
		return self.layout.code <= address < self.layout.end

	def shared(self, address):
		"""Memory whose contents are state: not the image's read-only sections, not our loaded code and
		constants, not the argument area."""
		if self.isOursRegion(address) or self.isArgs(address):
			return False
		if self.image.contains(address) and self.image.readOnly(address):
			return False
		return True

	def calleeArgCount(self, call):
		"""How many stack dwords the callee takes, from its `ret N`, else from the caller's cleanup after the
		call (cdecl); externals carry their cleanup. Cached per callee."""
		if call.get("external"):
			return min(8, call.get("cleanup", 0) // 4)
		address = call["address"]
		if address in self.argCounts:
			return self.argCounts[address]
		count = None
		if self.image.contains(address):
			cleanup = cfg.stackCleanup(lambda a, n: self.image.read(a, n) if self.image.contains(a) else None, address)
			if cleanup:
				count = cleanup // 4
		if count is None:
			ret = call.get("ret", 0)
			reader = self.engine.readSnapshot if not self.isOursRegion(ret) else self.ours.read
			count = cfg.callerCleanup(reader, ret) // 4
		count = min(count or 0, 8)
		self.argCounts[address] = count
		return count

	def registerArguments(self, call):
		"""Which of ecx, edx, eax the callee takes, from its decorated name, else from the registers it reads
		before writing them."""
		address = call["address"]
		if address in self.conventions:
			return self.conventions[address]
		name = call.get("name", "")
		convention = project.callingConvention(name)
		if convention == "thiscall":
			regs = {"ecx"}
		elif convention == "fastcall":
			regs = {"ecx", "edx"}
		elif convention in ("cdecl", "stdcall"):
			regs = set()
		elif call.get("external"):
			regs = set()
		else:
			code = None
			if self.image.contains(address):
				size = project.functionSizes().get(address, 256)
				code = self.image.read(address, size)
			elif self.isOursRegion(address):
				code = self.ours.read(address, 256)
			regs = cfg.registerInputs(code, address) & {"eax", "ecx", "edx"} if code else set()
		self.conventions[address] = regs
		return regs


def describeFault(fault):
	if not fault:
		return "returned"
	access = fault.get("access")
	where = " (%s)" % fault["where"] if fault.get("where") else ""
	if access and access[0] == "missing-page":
		return "needs a page the state did not save (0x%08X)%s" % (access[1], where)
	if access:
		return "faults at 0x%08X%s: %s of %d bytes at 0x%08X" % (fault["eip"], where, access[0], access[2], access[1])
	return "faults at 0x%08X%s: %s" % (fault["eip"], where, fault["error"])


def compareTraces(engine, ours, context):
	findings = []
	add = findings.append
	# 1. faults and time-outs
	stubbed = sorted(set(engine.stubbed))
	if stubbed:
		add(Finding("NOTE", "externals", "answered by stubs: %s" % ", ".join(stubbed[:8])))
	if engine.fault or engine.timedOut:
		# the engine's own code on its own state cannot fault: the emulation is incomplete here (an external
		# answered wrongly, memory the snapshot lacks); nothing this state shows counts either way
		reason = describeFault(engine.fault) if engine.fault else "runs past the instruction budget (%d)" % engine.instructions
		add(Finding("INCONCLUSIVE", "emulation", "the engine's run %s; ours %s" % (reason,
			describeFault(ours.fault) if ours.fault or not ours.timedOut else "runs past the budget too")))
		compareCalls(engine, ours, context, add)
		return findings
	if ours.fault:
		access = ours.fault.get("access")
		if access and access[0] == "missing-page":
			# a live capture saved only the pages its runs touched; a run (here ours) that needs a page it did
			# not save is inconclusive, never a behavioural difference
			add(Finding("INCONCLUSIVE", "emulation", "ours %s" % describeFault(ours.fault)))
		else:
			add(Finding("FAIL", "fault", "engine returned; ours %s" % describeFault(ours.fault)))
	if ours.timedOut:
		add(Finding("FAIL", "budget", "the engine returned after %d instructions; ours runs past the budget (%d)" % (engine.instructions, ours.instructions)))
	if ours.fault or ours.timedOut:
		compareCalls(engine, ours, context, add)
		return findings
	# 2. registers after return
	e, o = engine.end, ours.end
	if o["esp"] != e["esp"] and not getattr(context, "callersReplaced", False):
		add(Finding("FAIL", "stack", "esp after return: engine 0x%08X, ours 0x%08X (entry 0x%08X): different stack cleanup" % (e["esp"], o["esp"], context.entryEsp)))
	kind = context.returnKind
	mask = {"byte": 0xFF, "word": 0xFFFF}.get(kind, 0xFFFFFFFF)
	if kind in ("int", "int64", "byte", "word", None) and o["eax"] & mask != e["eax"] & mask:
		add(Finding("FAIL", "return", "eax: engine 0x%08X, ours 0x%08X" % (e["eax"], o["eax"])))
	if kind == "int64" and o["edx"] != e["edx"]:
		add(Finding("FAIL", "return", "edx: engine 0x%08X, ours 0x%08X" % (e["edx"], o["edx"])))
	if kind == "float":
		# the value only: the status word's stack top differed in Unicorn on functions whose x87 stack is
		# balanced by their code (each fld popped by its own faddp / fstp), so it is no evidence
		if o["st0"] != e["st0"]:
			add(Finding("FAIL", "return", "st0: engine %r (fpsw 0x%04X), ours %r (fpsw 0x%04X)" % (e["st0"], e["fpsw"], o["st0"], o["fpsw"])))
	for reg in CALLEE_SAVED:
		entry = engine.entry[reg]
		if o[reg] != entry:
			severity = "FAIL" if e[reg] == entry else "WARN"
			add(Finding(severity, "callee-saved", "%s at return: entry 0x%08X, engine 0x%08X, ours 0x%08X" % (reg, entry, e[reg], o[reg])))
		elif e[reg] != entry:
			add(Finding("NOTE", "callee-saved", "the engine itself changes %s (0x%08X -> 0x%08X); ours keeps it" % (reg, entry, e[reg])))
	# 3. memory written
	compareWrites(engine, ours, context, add)
	# 4. memory read
	compareReads(engine, ours, context, add)
	# 5. calls
	compareCalls(engine, ours, context, add)
	add(Finding("NOTE", "count", "instructions: engine %d, ours %d; writes outside the frame: engine %d, ours %d; calls: engine %d, ours %d"
		% (engine.instructions, ours.instructions, len(engine.writes), len(ours.writes), len(engine.calls), len(ours.calls))))
	return findings


def compareWrites(engine, ours, context, add):
	eFinal = engine.finalBytes()
	oFinal = ours.finalBytes()
	shared = [a for a in set(eFinal) | set(oFinal) if context.shared(a)]
	different = sorted(a for a in shared if eFinal.get(a) != oFinal.get(a))
	# a vftable pointer: the engine installs its table, ours the one our object emits (vtcheck compares their
	# slots); the hybrid DLL does the same, so this is not a behaviour difference
	vtables = getattr(context, "placedVtables", {})
	# likewise a pointer to a function ours placed itself (a callback stored in an event): the same function when
	# symbols.txt names the engine's address as the one ours defines
	ownFunctions = getattr(context.ours, "ours", None) or {}
	if (vtables or ownFunctions) and different:
		installed = set()
		functionPointers = set()
		for a in different:
			base = a & ~3
			ev = bytes(eFinal.get(base + k, 0) for k in range(4))
			ov = bytes(oFinal.get(base + k, 0) for k in range(4))
			ourValue = struct.unpack("<I", ov)[0]
			engineValue = struct.unpack("<I", ev)[0]
			if ourValue in vtables and context.image.contains(engineValue) and context.image.readOnly(engineValue):
				installed.update(range(base, base + 4))
			elif ourValue in ownFunctions and context.image.contains(engineValue) and project.symbolAt(engineValue) == ownFunctions[ourValue]:
				functionPointers.update(range(base, base + 4))
		if functionPointers:
			add(Finding("NOTE", "memory", "pointers to functions ours placed itself stored where the engine stores its own (the hybrid DLL links them to one)"))
			different = [a for a in different if a not in functionPointers]
		if installed:
			add(Finding("NOTE", "memory", "vftable pointers installed: ours %s (the engine's own table in the engine's run)"
				% ", ".join(sorted({vtables[struct.unpack('<I', bytes(oFinal.get(b + k, 0) for k in range(4)))[0]] for b in installed if b % 4 == 0}))))
			different = [a for a in different if a not in installed]
	if different:
		samples = []
		for a in different[:8]:
			ev, ov = eFinal.get(a), oFinal.get(a)
			samples.append("0x%08X engine %s ours %s" % (a, "-" if ev is None else "%02X" % ev, "-" if ov is None else "%02X" % ov))
		add(Finding("FAIL", "memory", "%d bytes differ after return: %s" % (len(different), "; ".join(samples))))
	argDiff = sorted(a for a in set(eFinal) | set(oFinal) if context.isArgs(a) and eFinal.get(a) != oFinal.get(a))
	if argDiff:
		add(Finding("NOTE", "memory", "%d bytes of the argument area differ (incoming argument slots reused as temporaries)" % len(argDiff)))
	eSeq = [(a, s, v) for a, s, v in engine.writes if context.shared(a)]
	oSeq = [(a, s, v) for a, s, v in ours.writes if context.shared(a)]
	if eSeq != oSeq and not different:
		k = next((i for i, (x, y) in enumerate(zip(eSeq, oSeq)) if x != y), min(len(eSeq), len(oSeq)))
		detail = "at write %d: engine %s, ours %s" % (k, describeWrite(eSeq, k), describeWrite(oSeq, k))
		add(Finding("WARN", "write-order", "same final memory, different write sequence (%d vs %d writes) %s" % (len(eSeq), len(oSeq), detail)))


def describeWrite(seq, k):
	if k >= len(seq):
		return "(none)"
	a, s, v = seq[k]
	return "0x%08X <- 0x%0*X" % (a, 2 * s, v)


def compareReads(engine, ours, context, add):
	eReads = {a for a, s in engine.reads for a in range(a, a + s) if context.shared(a)}
	oReads = {a for a, s in ours.reads for a in range(a, a + s) if context.shared(a)}
	extra = sorted(oReads - eReads)
	missing = sorted(eReads - oReads)
	if extra:
		add(Finding("WARN", "reads", "ours reads %d bytes the engine does not: %s" % (len(extra), ", ".join("0x%08X" % a for a in extra[:6]))))
	if missing:
		add(Finding("WARN", "reads", "the engine reads %d bytes ours does not: %s" % (len(missing), ", ".join("0x%08X" % a for a in missing[:6]))))
	eArgs = {a for a, s in engine.reads for a in range(a, a + s) if context.isArgs(a)}
	oArgs = {a for a, s in ours.reads for a in range(a, a + s) if context.isArgs(a)}
	if eArgs != oArgs:
		add(Finding("NOTE", "reads", "argument slots read: engine %s, ours %s" % (slots(eArgs, context), slots(oArgs, context))))


def slots(addresses, context):
	return sorted({(a - context.entryEsp - 4) // 4 for a in addresses})


def callText(call, count, regs):
	parts = []
	for reg in ("ecx", "edx", "eax"):
		if reg in regs:
			parts.append("%s=0x%08X" % (reg, call[reg]))
	parts += ["0x%08X" % a for a in call["args"][:count]]
	return "%s(%s)" % (call["name"], ", ".join(parts))


def constantAt(value, machine, context):
	"""The bytes a pointer to a constant designates: the engine's constants live in the image's read-only
	sections, ours beside our function, so such arguments are compared by content (a string, a float table)."""
	layout = context.layout
	if layout.data <= value < layout.ret or (context.image.contains(value) and context.image.readOnly(value)):
		data = machine.read(value, 64)
		if data is not None:
			return data.split(b"\0", 1)[0] if data[0] else data[:16]
	return None


def normalizedArguments(call, machine, count, regs, context):
	"""Argument values with pointers into the function's own frame replaced by a marker (the frame layouts of
	the two builds differ, so such addresses legitimately differ; their contents are compared apart) and
	pointers to constants replaced by the constants themselves."""
	values = []
	masks = project.stackSlotMasks(call["name"][5:] if call["name"].startswith("ours:") else call["name"]) or []
	for key in [r for r in ("ecx", "edx", "eax") if r in regs] + list(range(count)):
		value = call[key] if isinstance(key, str) else (call["args"][key] if key < len(call["args"]) else 0)
		if not isinstance(key, str) and key < len(masks):
			value &= masks[key]
		if machine.isPrivate(value):
			values.append("STK")
			continue
		own = (getattr(machine, "ours", None) or {}).get(value)
		name = own or (project.symbolAt(value) if context.image.contains(value) and value in project.functionSizes() else None)
		if name is not None:
			values.append(("FUNCTION", name))
			continue
		constant = constantAt(value, machine, context)
		values.append(("CONST", constant) if constant is not None else value)
	return values


def rawArguments(call, count, regs):
	return [call[key] if isinstance(key, str) else (call["args"][key] if key < len(call["args"]) else 0)
		for key in [r for r in ("ecx", "edx", "eax") if r in regs] + list(range(count))]


def sameStaticObject(engineValue, oursValue, context):
	"""A pointer to a data object of the engine against one to our own copy of it (a file-level static symbols.txt
	cannot name, which ours keeps in its own data): the same object when the bytes the copy occupies are equal."""
	size = context.ownObjectSize(oursValue)
	if size is None or not context.image.contains(engineValue) or context.image.readOnly(engineValue):
		return False
	engineBytes = context.engine.read(engineValue, size)
	return engineBytes is not None and engineBytes == context.ours.read(oursValue, size)


def sameArguments(ec, oc, count, regs, context):
	engineValues = normalizedArguments(ec, context.engine, count, regs, context)
	oursValues = normalizedArguments(oc, context.ours, count, regs, context)
	if engineValues == oursValues:
		return True
	if len(engineValues) != len(oursValues):
		return False
	engineRaw, oursRaw = rawArguments(ec, count, regs), rawArguments(oc, count, regs)
	return all(e == o or sameStaticObject(er, orw, context) for e, o, er, orw in zip(engineValues, oursValues, engineRaw, oursRaw))


_pureLeaves = {}


def pureLeaf(context, address):
	"""Whether the engine's function at `address` is a small leaf without stores (cfg.isPureLeaf); cached."""
	if address not in _pureLeaves:
		extent = project.functionExtent(address) if address in project.functionSizes() else 0
		code = context.image.read(address, extent) if 0 < extent <= 0x40 else None
		_pureLeaves[address] = code is not None and cfg.isPureLeaf(code, address)
	return _pureLeaves[address]


def compareCalls(engine, ours, context, add):
	eCalls = engine.calls
	# calls of ours to its own copies of helpers the engine does not call at all (it inlined them: a constructor,
	# a copy of a matrix) are skipped as they come; their effects are compared with the memory
	engineNames = {c["name"] for c in eCalls}

	def unmatched(call):
		return call["name"].startswith("ours:") and call["name"][5:] not in engineNames

	def unnamed(call):
		# a local helper symbols.txt does not name: ours' own copies of those pair with them below
		return not call.get("external") and not call["name"].startswith("?")

	anyUnmatched = any(unmatched(c) for c in ours.calls)
	# the same the other way: a call of the engine to a small value-computing function (no store, no call: a test of a
	# member, a comparison) that ours does not make at all is a function ours inlined; what it returned shows in the
	# arguments, calls and stores that follow, which are compared
	oursCallees = {c["address"] for c in ours.calls if not unmatched(c)} | {c["name"][5:] for c in ours.calls if c["name"].startswith("ours:")}

	# and a call to a function ours never calls that stores nothing outside the frame before the next call starts (a
	# copy into a temporary, a constructor of one): ours did the work inline; the temporary's contents show in the
	# arguments of the calls that follow, any store to shared memory in the memory, and a call that leaves the image
	# is never dropped
	def inlined(i, c):
		if c.get("external") or c["address"] in oursCallees or c["name"] in oursCallees:
			return False
		if anyUnmatched and unnamed(c):
			return False
		after = eCalls[i + 1]["writes"] if i + 1 < len(eCalls) else len(engine.writes)
		return pureLeaf(context, c["address"]) or after == c["writes"]

	eCalls = [c for i, c in enumerate(eCalls) if not inlined(i, c)]
	oCalls = ours.calls
	frameNoted = False
	i = j = 0
	while i < len(eCalls) and j < len(oCalls):
		ec, oc = eCalls[i], oCalls[j]
		if unmatched(oc) and not unnamed(ec):
			j += 1
			continue
		index = i
		i += 1
		j += 1
		count = context.calleeArgCount(ec)
		regs = context.registerArguments(ec)
		# a call to our own copy of the same function (the hybrid DLL links ours to it) is the same callee; our
		# copy keeps its own register convention, so only its stack arguments are compared
		ownCopy = oc["name"] == "ours:" + ec["name"]
		if ec["name"].endswith("_chkstk"):
			# the frame size in eax is its only input: it saves ecx and gives it back, so the caller's ecx (a leftover)
			# is no argument, and reading it before writing is only that save
			regs = {"eax"}
		elif ownCopy or ec.get("external"):
			# our own copy keeps its own register convention; an external (an import) takes its arguments on
			# the stack, whatever the caller left in ecx / edx
			regs = set()
		sameName = ec["name"] == oc["name"] or ownCopy or (ec["address"] == oc["address"])
		if not sameName:
			if oc["name"].startswith("ours:") and not ec["name"].startswith("?"):
				add(Finding("WARN", "calls", "call %d: engine calls %s, ours its own copy %s (an unnamed local helper; add it to symbols.txt to pair them)" % (index, ec["name"], oc["name"])))
				continue
			add(Finding("FAIL", "calls", "call %d: engine %s, ours %s" % (index, callText(ec, count, regs), callText(oc, count, regs))))
			return
		if not sameArguments(ec, oc, count, regs, context):
			add(Finding("FAIL", "calls", "call %d: engine %s, ours %s" % (index, callText(ec, count, regs), callText(oc, count, regs))))
			return
		eFrame, oFrame = ec.get("frame", {}), oc.get("frame", {})
		for key in eFrame:
			if key in oFrame and eFrame[key] != oFrame[key] and not frameNoted:
				frameNoted = True
				k = next(n for n in range(64) if eFrame[key][n] != oFrame[key][n])
				add(Finding("WARN", "calls", "call %d %s: the temporary passed as %s differs at byte %d (64 bytes compared; a temporary smaller than that is followed by other frame data)"
					% (index, ec["name"], key, k)))
		if ec.get("external") and ec.get("cleanup") != oc.get("cleanup"):
			add(Finding("FAIL", "calls", "call %d: external %s cleaned %d vs %d bytes" % (index, ec["name"], ec.get("cleanup", 0), oc.get("cleanup", 0))))
			return
	eRest = eCalls[i:]
	oRest = [c for c in oCalls[j:] if not unmatched(c)]
	if eRest or oRest:
		longer, who = (eRest, "engine") if eRest else (oRest, "ours")
		call = longer[0]
		add(Finding("FAIL", "calls", "%s makes %d calls, the other %d; first extra (%s): %s" % (who, i + len(longer), i, who,
			callText(call, context.calleeArgCount(call), context.registerArguments(call)))))
