"""opprobe: puts Alex somewhere in the running original and captures what the game shows.

The player is found without hard-coded heap addresses:
  1. proto::MusicTreeBehaviour exists once, on the player; its vtable is a fixed address in prototypeenginef.dll
  2. behaviour + 0x04 is the owning engine::GameObject
  3. GameObject + 0x08 / + 0x0C delimit its attribute entries {u64 name hash, Attribute*, pad}
  4. the engine::Attribute<math::Matrix> with the transform hash holds the world matrix at + 0x04 (row vectors,
     translation in the last row: the capsule centre, 1 m above the feet). The game rewrites it every frame.
  5. the physics body's world matrix, which the game reads, sits at MusicTreeBehaviour + 0x500 (the player's components
     are one allocation with a fixed layout: same offset in two sessions). Writes are checked against step 4 first.

	python tools/re/opprobe.py where                  # feet position and yaw (opviewer convention)
	python tools/re/opprobe.py teleport x y z [yaw]   # feet position; Alex lands from 0.5 m above
	python tools/re/opprobe.py shot out.png           # the game's next frame, from the proxy d3d9.dll's back buffer
	python tools/re/opprobe.py hour [h]               # the game clock (0..24); with h, sets it

The clock is a float in proto::TimeOfDayManager (one object, found by its vtable): the hour of day at + 0x24. Writing
it moves the time of day at once; the game keeps counting from there.
"""

import ctypes
import math
import pathlib
import struct
import sys
import time

import numpy as np

import probe

MUSIC_TREE_VTABLE = 0x10E0BE9C       # .?AVMusicTreeBehaviour@proto@@
GAME_OBJECT_VTABLE = 0x10E686C0      # .?AVGameObject@engine@@
TRANSFORM_ATTRIBUTE_HASH = (0xBE42C46C, 0x4D9DC39C)
GAME_DIR = probe.GAME_DIR  # the copy of the game (OP_ORIGINAL_DIR), its proxy reads requests from that folder
CAPSULE_CENTRE = 1.0                 # metres above the feet
BODY_MATRIX_OFFSET = 0x500           # from the MusicTreeBehaviour
TIME_OF_DAY_VTABLE = 0x10E1FFB4      # .?AVTimeOfDayManager@proto@@ (first of its two vtables)
HOUR_OFFSET = 0x24


def u32(handle, address):
	raw = probe.read(handle, address, 4)
	return None if raw is None or len(raw) < 4 else struct.unpack("<I", raw)[0]


def findPlayer(handle, body=False):
	"""Address of the player's world matrix (the transform attribute, or with `body` the physics body matrix)."""
	for base, size in probe.regions(handle):
		if size > 64 << 20:
			continue
		raw = probe.read(handle, base, size)
		if raw is None:
			continue
		words = np.frombuffer(raw[:len(raw) - len(raw) % 4], dtype="<u4")
		for index in np.nonzero(words == MUSIC_TREE_VTABLE)[0]:
			gameObject = u32(handle, base + 4 * int(index) + 4)
			if gameObject is None or u32(handle, gameObject) != GAME_OBJECT_VTABLE:
				continue
			begin, end = u32(handle, gameObject + 8), u32(handle, gameObject + 12)
			for entry in range(begin, end, 16):
				if (u32(handle, entry), u32(handle, entry + 4)) == TRANSFORM_ATTRIBUTE_HASH:
					transform = u32(handle, entry + 8) + 4
					if not body:
						return transform
					# The offset moves between builds of the session (0x500 on 2026-10-06, 0x4B0 after a reboot on
					# 2026-10-07): the first matrix near it that sits exactly where the transform is
					# (a few tries: while he moves, the body is a frame ahead of the transform)
					for attempt in range(20):
						expected = readMatrix(handle, transform)[3, :3]
						for offset in [BODY_MATRIX_OFFSET] + list(range(0x400, 0x600, 0x10)):
							matrix = base + 4 * int(index) + offset
							with np.errstate(invalid="ignore"):
								if np.abs(readMatrix(handle, matrix)[3, :3] - expected).max() < 1e-3:
									return matrix
						time.sleep(0.05)
					raise SystemExit("the body matrix is not where it used to be: run tools/re/findsource.py again")
	raise SystemExit("player not found (is a save loaded?)")


def readMatrix(handle, address):
	return np.frombuffer(probe.read(handle, address, 64), dtype="<f4").reshape(4, 4).copy()


def facing(matrix):
	"""Where Alex faces (degrees, 0 = world +Z as in opviewer): the body's local -Z. Checked on 2026-10-08 against his
	motion (running at 272 degrees the matrix's +Z points to 92.8; sprinting at 202, to 22.3)."""
	return (math.degrees(math.atan2(matrix[2, 0], matrix[2, 2])) + 180.0) % 360.0


def feet_and_yaw():
	"""Alex's feet position and yaw (degrees; yaw 0 looks along world +Z like in opviewer)."""
	handle = probe.openProcess()
	matrix = readMatrix(handle, findPlayer(handle))
	x, y, z = matrix[3, :3]
	return (float(x), float(y - CAPSULE_CENTRE), float(z)), facing(matrix)


def where():
	(x, y, z), yaw = feet_and_yaw()
	print(f"feet {x:.2f} {y:.2f} {z:.2f}  yaw {yaw:.1f}")


def teleportFar(x, y, z, yaw=None, lift=0.0, hop=3.0):
	"""Feet to (x, y, z) from anywhere: the game takes only short moves of the physics body (a 170 m write is undone,
	3 m is kept), so the move goes in hops of `hop` metres along the straight line, 50 m above both ends' height
	(over the roofs), then down onto the target."""
	handle = probe.openProcess(write=True)
	address = findPlayer(handle, body=True)
	written = ctypes.c_size_t()

	def here():
		p = readMatrix(handle, address)[3, :3].astype(float)
		p[1] -= CAPSULE_CENTRE
		return p

	def put(p):
		matrix = readMatrix(handle, address)
		matrix[3, :3] = [p[0], p[1] + CAPSULE_CENTRE, p[2]]
		data = matrix.astype("<f4").tobytes()
		probe.kernel32.WriteProcessMemory(ctypes.c_void_p(handle), ctypes.c_void_p(address), data, len(data), ctypes.byref(written))

	start = here()
	high = max(start[1], y) + 50.0
	for goal in (np.array([start[0], high, start[2]]), np.array([x, high, z]), np.array([x, y + lift, z])):
		# Each hop is kept by the game before the next: from where he is now toward the goal, at most `hop` metres
		for _ in range(2000):
			now = here()
			gap = goal - now
			distance = float(np.linalg.norm(gap))
			if distance < 0.2:
				break
			put(now + gap * min(1.0, hop / distance))
			time.sleep(0.05)
	if yaw is not None:
		teleport(x, y, z, yaw, lift)
	else:
		time.sleep(1.0)
		where()


def teleport(x, y, z, yaw=None, lift=0.5):
	"""Feet to (x, y, z), lift metres above it (the original then keeps him there until he moves: 0 for a start)"""
	handle = probe.openProcess(write=True)
	address = findPlayer(handle, body=True)
	matrix = readMatrix(handle, address)
	matrix[3, :3] = [x, y + CAPSULE_CENTRE + lift, z]
	if yaw is not None:
		angle = math.radians(yaw + 180.0)  # the body's -Z faces `yaw`
		matrix[0, :3] = [math.cos(angle), 0.0, -math.sin(angle)]
		matrix[1, :3] = [0.0, 1.0, 0.0]
		matrix[2, :3] = [math.sin(angle), 0.0, math.cos(angle)]
	written = ctypes.c_size_t()
	data = matrix.astype("<f4").tobytes()
	if not probe.kernel32.WriteProcessMemory(ctypes.c_void_p(handle), ctypes.c_void_p(address), data, len(data), ctypes.byref(written)):
		raise SystemExit(f"WriteProcessMemory failed: {ctypes.get_last_error()}")
	time.sleep(1.0)
	where()


def findTimeOfDay(handle):
	"""Address of the TimeOfDayManager: the object whose first two dwords are its two vtables."""
	for base, size in probe.regions(handle):
		if size > 64 << 20:
			continue
		raw = probe.read(handle, base, size)
		if raw is None:
			continue
		words = np.frombuffer(raw[:len(raw) - len(raw) % 4], dtype="<u4")
		for index in np.nonzero(words[:-1] == TIME_OF_DAY_VTABLE)[0]:
			if words[index + 1] == TIME_OF_DAY_VTABLE - 0x18:
				return base + 4 * int(index)
	raise SystemExit("TimeOfDayManager not found (is a save loaded?)")


def hour(value=None):
	handle = probe.openProcess(write=value is not None)
	address = findTimeOfDay(handle) + HOUR_OFFSET
	if value is not None:
		data = struct.pack("<f", value % 24.0)
		written = ctypes.c_size_t()
		if not probe.kernel32.WriteProcessMemory(ctypes.c_void_p(handle), ctypes.c_void_p(address), data, 4, ctypes.byref(written)):
			raise SystemExit(f"WriteProcessMemory failed: {ctypes.get_last_error()}")
		time.sleep(0.5)
	current = struct.unpack("<f", probe.read(handle, address, 4))[0]
	print(f"hour {current:.3f} ({int(current):02d}:{int(current % 1 * 60):02d})")


def shot(path, timeout=10.0):
	"""Asks the proxy d3d9.dll for the next frame (a BMP) and converts it to the requested format."""
	from PIL import Image
	target = pathlib.Path(path).resolve()
	bmp = target.with_suffix(".bmp")
	bmp.unlink(missing_ok=True)
	(GAME_DIR / "opprobe_shot.request").write_text(str(bmp))
	deadline = time.time() + timeout
	while time.time() < deadline:
		time.sleep(0.2)
		if bmp.exists() and not (GAME_DIR / "opprobe_shot.request").exists():
			time.sleep(0.2)
			Image.open(bmp).save(target)
			if target != bmp:
				bmp.unlink()
				# The draws of the frame, recorded by the proxy (tools/re/frame.py)
				frame = pathlib.Path(str(bmp) + ".frame")
				if frame.exists():
					frame.replace(target.with_suffix(".frame"))
				# Render targets and small textures of the frame: <shot>.bmp.rt<id>.bin -> <shot>.rt<id>.bin
				for saved in list(bmp.parent.glob(bmp.name + ".rt*.bin")) + list(bmp.parent.glob(bmp.name + ".tex*.dds")):
					saved.replace(target.parent / (target.stem + saved.name[len(bmp.name):]))
			print(f"saved {target}")
			return
	raise SystemExit("no frame: is the game running with the proxy d3d9.dll?")


if __name__ == "__main__":
	args = sys.argv[1:]
	if args and args[0] == "where":
		where()
	elif len(args) in (4, 5) and args[0] == "teleport":
		teleport(*map(float, args[1:]))
	elif len(args) >= 2 and args[0] == "shot":
		shot(args[1])
	elif len(args) in (1, 2) and args[0] == "hour":
		hour(float(args[1]) if len(args) == 2 else None)
	else:
		print(__doc__)
