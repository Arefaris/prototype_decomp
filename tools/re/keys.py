"""keys: holds keys in the running original (DirectInput reads SendInput scan codes while its window is in front).

	python tools/re/keys.py hold space 1.5                  # hold Space for 1.5 s
	python tools/re/keys.py hold space 1.5 shot out.png     # ... and take a frame (opprobe shot) near the end
	python tools/re/keys.py tap e                           # press and release
	python tools/re/keys.py click 128 646                   # left click at a point of the game's 1280x720 frame

Brings the game's window to the front first (docs/re/running_original.md).
"""

import ctypes
import ctypes.wintypes as wt
import subprocess
import sys
import time

SCAN_CODES = {"space": 0x39, "e": 0x12, "f": 0x21, "q": 0x10, "w": 0x11, "a": 0x1E, "s": 0x1F, "d": 0x20,
	"shift": 0x2A, "enter": 0x1C, "escape": 0x01, "1": 0x02, "2": 0x03, "3": 0x04, "4": 0x05, "5": 0x06,
	# the power hot keys F1 - F11 (docs/re/input.md 2), R the power wheel, Tab lock-on, X camera reset, Ctrl walk
	"f1": 0x3B, "f2": 0x3C, "f3": 0x3D, "f4": 0x3E, "f5": 0x3F, "f6": 0x40, "f7": 0x41, "f8": 0x42, "f9": 0x43, "f10": 0x44,
	"f11": 0x57, "r": 0x13, "tab": 0x0F, "x": 0x2D, "ctrl": 0x1D}

user32 = ctypes.WinDLL("user32", use_last_error=True)
INPUT_KEYBOARD = 1
KEYEVENTF_SCANCODE = 0x0008
KEYEVENTF_KEYUP = 0x0002


class KEYBDINPUT(ctypes.Structure):
	_fields_ = [("wVk", wt.WORD), ("wScan", wt.WORD), ("dwFlags", wt.DWORD), ("time", wt.DWORD), ("dwExtraInfo", ctypes.c_size_t)]


class INPUT(ctypes.Structure):
	class _U(ctypes.Union):
		_fields_ = [("ki", KEYBDINPUT), ("padding", ctypes.c_byte * 32)]
	_anonymous_ = ("u",)
	_fields_ = [("type", wt.DWORD), ("u", _U)]


LOCK = __import__("pathlib").Path(__file__).resolve().parents[2] / "local" / "original_input.lock"


class inputLock:
	"""Keys and mouse reach only the window in front, and two copies of the game run (the lead's and the auditor's):
	whoever sends input holds this lock file; the other waits. A lock older than 3 minutes is taken as left over."""

	def __init__(self, owner="", wait=600.0):
		self.owner, self.wait, self.held = owner, wait, False

	def __enter__(self):
		import os
		LOCK.parent.mkdir(parents=True, exist_ok=True)
		deadline = time.time() + self.wait
		while True:
			try:
				fd = os.open(LOCK, os.O_CREAT | os.O_EXCL | os.O_WRONLY)
				os.write(fd, f"{os.getpid()} {self.owner} {time.ctime()}".encode())
				os.close(fd)
				self.held = True
				return self
			except FileExistsError:
				try:
					if time.time() - LOCK.stat().st_mtime > 180.0:
						LOCK.unlink(missing_ok=True)
						continue
				except FileNotFoundError:
					continue
				if time.time() > deadline:
					raise SystemExit(f"the input lock is held: {LOCK.read_text(errors='replace')}")
				time.sleep(0.5)

	def __exit__(self, *_):
		if self.held:
			LOCK.unlink(missing_ok=True)


def send(scan, up):
	flags = KEYEVENTF_SCANCODE | (KEYEVENTF_KEYUP if up else 0)
	event = INPUT(type=INPUT_KEYBOARD, ki=KEYBDINPUT(0, scan, flags, 0, 0))
	user32.SendInput(1, ctypes.byref(event), ctypes.sizeof(INPUT))


def game_window():
	"""The window of the copy of the game that probe.GAME_DIR names (OP_ORIGINAL_DIR)."""
	import probe
	found = []
	process = ctypes.c_ulong()
	pid = probe.findProcess()

	@ctypes.WINFUNCTYPE(wt.BOOL, wt.HWND, wt.LPARAM)
	def visit(hwnd, _):
		if not user32.IsWindowVisible(hwnd):
			return True
		user32.GetWindowThreadProcessId(hwnd, ctypes.byref(process))
		if process.value != pid:
			return True
		length = user32.GetWindowTextLengthW(hwnd)
		title = ctypes.create_unicode_buffer(length + 1)
		user32.GetWindowTextW(hwnd, title, length + 1)
		if "Prototype" in title.value or "PROTOTYPE" in title.value:
			found.append(hwnd)
		return True

	user32.EnumWindows(visit, 0)
	return found[0] if found else None


def bring_to_front():
	hwnd = game_window()
	if hwnd is None:
		raise SystemExit("the game's window was not found")
	# An Alt tap lets this process move another window to the front
	send(0x38, False)
	send(0x38, True)
	user32.ShowWindow(hwnd, 9 if user32.IsIconic(hwnd) else 5)  # restore a minimised window
	user32.SetForegroundWindow(hwnd)
	time.sleep(0.4)


def click(x, y):
	"""Left click at (x, y) of the game's client area (the frame's pixels)."""
	hwnd = game_window()
	if hwnd is None:
		raise SystemExit("the game's window was not found")
	bring_to_front()
	point = wt.POINT(int(x), int(y))
	user32.ClientToScreen(hwnd, ctypes.byref(point))
	user32.SetCursorPos(point.x, point.y)
	time.sleep(0.1)
	user32.mouse_event(0x0002, 0, 0, 0, 0)  # left down
	time.sleep(0.08)
	user32.mouse_event(0x0004, 0, 0, 0, 0)  # left up


def main(args):
	if len(args) >= 3 and args[0] == "hold":
		scans = [SCAN_CODES[name] for name in args[1].split("+")]
		seconds = float(args[2])
		shot = args[4] if len(args) >= 5 and args[3] == "shot" else None
		bring_to_front()
		for scan in scans:
			send(scan, False)
		if shot:
			time.sleep(max(seconds - 0.3, 0.0))
			subprocess.run([sys.executable, __file__.replace("keys.py", "opprobe.py"), "shot", shot], check=False)
			time.sleep(0.1)
		else:
			time.sleep(seconds)
		for scan in scans:
			send(scan, True)
	elif len(args) == 2 and args[0] == "tap":
		bring_to_front()
		send(SCAN_CODES[args[1]], False)
		time.sleep(0.08)
		send(SCAN_CODES[args[1]], True)
	elif len(args) == 3 and args[0] == "click":
		click(float(args[1]), float(args[2]))
	else:
		print(__doc__)


if __name__ == "__main__":
	with inputLock("keys.py " + " ".join(sys.argv[1:3])):
		main(sys.argv[1:])
