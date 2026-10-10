"""Finds which copy of a position the game reads from: each candidate is nudged in turn, and a derived copy that the
game rewrites every frame (the witness) shows whether the nudge propagated. Every nudge is undone afterwards.

	python tools/re/findsource.py 0x0BD2B2B0 [delta]
"""

import ctypes
import sys
import time

import numpy as np

import probe


def readTriple(handle, address):
	raw = probe.read(handle, address, 12)
	return np.frombuffer(raw, dtype="<f4").copy() if raw and len(raw) == 12 else None


def write(handle, address, values):
	data = np.asarray(values, dtype="<f4").tobytes()
	written = ctypes.c_size_t()
	return probe.kernel32.WriteProcessMemory(ctypes.c_void_p(handle), ctypes.c_void_p(address), data, 12, ctypes.byref(written))


def main(witness, delta=3.0):
	handle = probe.openProcess(write=True)
	candidates = np.load(probe.CANDIDATES)
	reference = readTriple(handle, witness)
	print(f"witness 0x{witness:08X} at {reference}")
	for address in map(int, candidates):
		if address == witness:
			continue
		value = readTriple(handle, address)
		# Only exact copies of the witness's horizontal position are worth testing
		if value is None or abs(value[0] - reference[0]) > 0.01 or abs(value[2] - reference[2]) > 0.01:
			continue
		write(handle, address, value + np.array([delta, 0.0, 0.0], dtype=np.float32))
		time.sleep(0.5)
		after = readTriple(handle, witness)
		followed = after is not None and abs(after[0] - reference[0] - delta) < 0.5
		current = readTriple(handle, address)
		# Undo: put the candidate back where it was, relative to wherever the game has it now
		if current is not None and abs(current[0] - value[0] - delta) < 0.01:
			write(handle, address, value)
		print(f"0x{address:08X} {'SOURCE' if followed else '-'}  witness now {after}")
		if followed:
			break
		reference = readTriple(handle, witness)


if __name__ == "__main__":
	main(int(sys.argv[1], 16), float(sys.argv[2]) if len(sys.argv) > 2 else 3.0)
