"""Reads the frame records of the proxy d3d9.dll (<shot>.frame, docs/re/frame_capture.md).

Every draw of the captured frame: kind, primitive counts, vertex and pixel shader hashes, render target, blend and
depth state, bound textures and the first vertex (c0..c95) and pixel (c0..c63) shader constant registers.

	python tools/re/frame.py passes shot.frame            # draws grouped by render target, in order
	python tools/re/frame.py shaders shot.frame           # pixel shaders: draws, targets, constant registers in use
	python tools/re/frame.py draw shot.frame 120          # everything recorded for one draw
	python tools/re/frame.py ps shot.frame 0xHASH [regs]  # pixel constants of every draw of one shader
	python tools/re/frame.py targets shot.frame           # render targets saved with the frame, as PNG and .npy
"""

import struct
import sys

import numpy as np

STATE_NAMES = ["blend", "src", "dst", "op", "z", "zwrite", "zfunc", "cull", "atest", "aref", "srgbwrite", "colorwrite",
	"sepalpha", "srcalpha", "dstalpha", "stencil"]
BLEND = {1: "0", 2: "1", 3: "srcC", 4: "1-srcC", 5: "srcA", 6: "1-srcA", 7: "dstA", 8: "1-dstA", 9: "dstC", 10: "1-dstC",
	11: "srcAsat", 14: "factor", 15: "1-factor"}
FORMATS = {21: "A8R8G8B8", 22: "X8R8G8B8", 23: "R5G6B5", 28: "A8", 32: "A8B8G8R8", 34: "G16R16", 36: "A16B16G16R16",
	50: "L8", 51: "A8L8", 77: "R32F", 111: "R16F", 112: "G16R16F", 113: "A16B16G16R16F", 114: "R32F", 115: "G32R32F",
	116: "A32B32G32R32F", 75: "D24X8", 77 + 1000: "",
	0x31545844: "DXT1", 0x33545844: "DXT3", 0x35545844: "DXT5", 0x34324E49: "INTZ", 0x5A574152: "RAWZ",
	0x3154454E: "NULL", 0x34324644: "DF24", 0x36314644: "DF16"}


def recordType(stages, states, vsRegisters, psRegisters, version=2):
	texture = np.dtype([("id", "<u4"), ("width", "<u4"), ("height", "<u4"), ("format", "<u4"), ("srgb", "<u4")])
	viewport = [("viewport", "<u4", 4)] if version >= 2 else []
	return np.dtype([("kind", "<u4"), ("primitiveType", "<u4"), ("primitives", "<u4"), ("vertices", "<u4"),
		("vs", "<u4"), ("ps", "<u4"), ("targetWidth", "<u4"), ("targetHeight", "<u4"), ("targetFormat", "<u4"),
		("targetId", "<u4")] + viewport + [("states", "<u4", states), ("textures", texture, stages),
		("vsc", "<f4", (vsRegisters, 4)), ("psc", "<f4", (psRegisters, 4))])


def load(path):
	raw = open(path, "rb").read()
	magic, count, size, vsRegisters, psRegisters, stages, states = struct.unpack("<7I", raw[:28])
	versions = {0x3146504F: 1, 0x3246504F: 2}   # "OPF1" (no viewports), "OPF2"
	if magic not in versions:
		raise SystemExit(f"{path}: not a frame record")
	dtype = recordType(stages, states, vsRegisters, psRegisters, versions[magic])
	if dtype.itemsize != size:
		raise SystemExit(f"{path}: record size {size}, expected {dtype.itemsize}")
	return np.frombuffer(raw, dtype=dtype, count=count, offset=28)


def formatName(value):
	return FORMATS.get(int(value), str(int(value)))


def blendText(states):
	if not states[0]:
		return "opaque"
	return f"{BLEND.get(int(states[1]), states[1])}+{BLEND.get(int(states[2]), states[2])}"


def target(record):
	return f"#{record['targetId']} {record['targetWidth']}x{record['targetHeight']} {formatName(record['targetFormat'])}"


def passes(path):
	draws = load(path)
	start = 0
	for index in range(1, len(draws) + 1):
		if index < len(draws) and draws[index]["targetId"] == draws[start]["targetId"]:
			continue
		group = draws[start:index]
		pixelShaders = len(set(int(value) for value in group["ps"]))
		blends = sorted(set(blendText(record["states"]) for record in group))
		print(f"{start:5d}..{index - 1:5d}  {target(group[0]):30s} {len(group):5d} draws  {pixelShaders:3d} pixel shaders  "
			f"{group['primitives'].sum():8d} primitives  {', '.join(blends)}")
		start = index


def usedRegisters(constants):
	"""Registers that are not zero in any draw, and which of them change between draws."""
	nonzero = np.nonzero(np.abs(constants).max(axis=(0, 2)) > 0)[0]
	varying = [int(r) for r in nonzero if np.ptp(constants[:, r, :], axis=0).max() > 1e-6]
	return [int(r) for r in nonzero], varying


def shaders(path):
	draws = load(path)
	for hash in sorted(set(int(value) for value in draws["ps"]), key=lambda h: -np.count_nonzero(draws["ps"] == h)):
		group = draws[draws["ps"] == hash]
		targets = sorted(set(target(record) for record in group))
		used, varying = usedRegisters(group["psc"])
		textures = [stage for stage in range(group["textures"].shape[1]) if group["textures"][:, stage]["id"].any()]
		print(f"ps 0x{hash:08X}  {len(group):5d} draws  first {int(np.nonzero(draws['ps'] == hash)[0][0]):5d}  "
			f"textures {textures}  c{used} varying c{varying}  -> {'; '.join(targets)}")


def draw(path, index):
	record = load(path)[index]
	print(f"draw {index}: kind {record['kind']} primitives {record['primitives']} vertices {record['vertices']}")
	print(f"  vs 0x{record['vs']:08X}  ps 0x{record['ps']:08X}  target {target(record)}")
	print("  " + "  ".join(f"{name}={int(value)}" for name, value in zip(STATE_NAMES, record["states"])))
	for stage, texture in enumerate(record["textures"]):
		if texture["id"]:
			kind = "cube" if texture["height"] == 0 else f"{texture['width']}x{texture['height']}"
			print(f"  s{stage}: #{texture['id']} {kind} {formatName(texture['format'])} srgb={texture['srgb']}")
	for name, constants in (("vs", record["vsc"]), ("ps", record["psc"])):
		for register, value in enumerate(constants):
			if np.abs(value).max() > 0:
				print(f"  {name} c{register:<3d} {value[0]:12.6f} {value[1]:12.6f} {value[2]:12.6f} {value[3]:12.6f}")


def pixelConstants(path, hash, registers=None):
	draws = load(path)
	indices = np.nonzero(draws["ps"] == hash)[0]
	group = draws[indices]
	if registers is None:
		registers = usedRegisters(group["psc"])[0]
	for index, record in zip(indices, group):
		values = "  ".join(f"c{r}=({' '.join(f'{v:.4f}' for v in record['psc'][r])})" for r in registers)
		print(f"{index:5d} p{record['primitives']:<6d} {values}")


def loadTarget(path):
	"""A render target saved by the proxy (<shot>.rt<id>.bin) as a float array (height, width, channels)."""
	raw = open(path, "rb").read()
	magic, width, height, fmt, pitch = struct.unpack("<5I", raw[:20])
	rows = np.frombuffer(raw, dtype=np.uint8, offset=20).reshape(height, pitch)
	if fmt in (21, 22):        # A8R8G8B8 / X8R8G8B8: BGRA bytes
		pixels = rows[:, :width * 4].reshape(height, width, 4)[:, :, [2, 1, 0, 3]].astype(np.float32) / 255.0
	elif fmt == 113:           # A16B16G16R16F: RGBA halves
		pixels = rows[:, :width * 8].copy().view("<f2").reshape(height, width, 4).astype(np.float32)
	elif fmt == 114:           # R32F
		pixels = rows[:, :width * 4].copy().view("<f4").reshape(height, width, 1)
	else:
		raise SystemExit(f"{path}: format {fmt} not handled")
	return pixels, fmt


def targets(path):
	import glob
	from PIL import Image
	base = path[:-len(".frame")] if path.endswith(".frame") else path
	for file in sorted(glob.glob(glob.escape(base) + ".rt*.bin")):
		pixels, fmt = loadTarget(file)
		stem = file[:-len(".bin")]
		np.save(stem + ".npy", pixels)
		shown = np.clip(pixels[:, :, :3] if pixels.shape[2] >= 3 else np.repeat(pixels, 3, axis=2), 0.0, 1.0)
		Image.fromarray((shown * 255.0 + 0.5).astype(np.uint8)).save(stem + ".png")
		print(f"{file}: {pixels.shape[1]}x{pixels.shape[0]} {formatName(fmt)}  min {pixels.min(axis=(0, 1)).round(3)}  max {pixels.max(axis=(0, 1)).round(3)}")


if __name__ == "__main__":
	args = sys.argv[1:]
	if len(args) == 2 and args[0] == "passes":
		passes(args[1])
	elif len(args) == 2 and args[0] == "shaders":
		shaders(args[1])
	elif len(args) == 3 and args[0] == "draw":
		draw(args[1], int(args[2]))
	elif len(args) == 2 and args[0] == "targets":
		targets(args[1])
	elif len(args) >= 3 and args[0] == "ps":
		pixelConstants(args[1], int(args[2], 16), [int(r) for r in args[3].split(",")] if len(args) > 3 else None)
	else:
		print(__doc__)
