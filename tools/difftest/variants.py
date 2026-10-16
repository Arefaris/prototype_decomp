"""Variants of a real state: the dwords the engine's run read from shared memory are its inputs, so each one is
set to a sentinel (0, -1, 1, a large count) in turn to reach the blocks the captured states leave out; the fuzzer
mutates a few of them at random. A variant can be an impossible state, so a difference found on one is reported
apart from the real states' verdict, and a variant that reaches no new engine block is not evidence of anything."""

import random
import struct

SENTINELS = (0, 0xFFFFFFFF, 1, 0x7FFFFFFF)


def inputDwords(trace, context, limit):
	"""Dword addresses the engine read in shared memory and in its argument area, nearest the entry stack first
	(arguments, then the objects they point at by address)."""
	seen = set()
	ordered = []
	for address in trace.readOrder:
		dword = address & ~3
		if dword in seen or not (context.isArgs(dword) or context.shared(dword)):
			continue
		seen.add(dword)
		ordered.append(dword)
	# the arguments first, then the rest in the order the run first read them (early reads decide early branches)
	args = [a for a in ordered if context.isArgs(a)]
	rest = [a for a in ordered if not context.isArgs(a)]
	return (args + rest)[:limit]


def perturbations(trace, context, machine, limit=160):
	"""[(label, overlay)] sentinel variants of the inputs."""
	result = []
	for address in inputDwords(trace, context, limit):
		original = machine.readSnapshot(address, 4)
		if original is None:
			continue
		current = struct.unpack("<I", original)[0]
		for value in SENTINELS:
			if value == current:
				continue
			overlay = {address + k: (value >> (8 * k)) & 0xFF for k in range(4)}
			result.append(("[0x%08X] 0x%08X -> 0x%08X" % (address, current, value), overlay))
	return result


def mutate(value, rnd):
	choice = rnd.random()
	if choice < 0.3:
		return rnd.choice(SENTINELS + (2, 3, 0x10000, 0x80000000))
	if choice < 0.6:
		return value ^ (1 << rnd.randrange(32))
	if choice < 0.8:
		return (value + rnd.choice((-16, -4, -1, 1, 4, 16))) & 0xFFFFFFFF
	return rnd.getrandbits(32)


def fuzzVariants(trace, context, machine, count, seed=1, limit=400):
	"""[(label, overlay)] random mutations of one to three inputs each."""
	rnd = random.Random(seed)
	inputs = inputDwords(trace, context, limit)
	result = []
	if not inputs:
		return result
	for i in range(count):
		overlay = {}
		labels = []
		for address in rnd.sample(inputs, min(len(inputs), rnd.choice((1, 1, 2, 3)))):
			original = machine.readSnapshot(address, 4)
			if original is None:
				continue
			current = struct.unpack("<I", original)[0]
			value = mutate(current, rnd)
			for k in range(4):
				overlay[address + k] = (value >> (8 * k)) & 0xFF
			labels.append("[0x%08X] 0x%08X -> 0x%08X" % (address, current, value))
		if overlay:
			result.append(("fuzz %d: %s" % (i, ", ".join(labels)), overlay))
	return result
