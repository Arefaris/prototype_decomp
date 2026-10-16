"""gamectl: controls the running original through the proxy d3d9.dll.

Every request runs on the game's main thread between two engine frames: Lua in the game's own script state (the
functions its mission scripts use), the chase camera's orbit, keys and mouse fed to the game's DirectInput devices.
Nothing needs the window in front, so no input lock is taken.

	python tools/re/gamectl.py launch [n]                # (re)start this copy and load the newest save (or the n-th older one)
	python tools/re/gamectl.py where                     # feet position and facing yaw
	python tools/re/gamectl.py teleport x y z [yaw]      # the game's own mission teleport (streams the cells there)
	python tools/re/gamectl.py camera yaw pitch [dist]   # chase camera: view yaw (0 = +Z), pitch (> 0 looks down)
	python tools/re/gamectl.py camera behind             # the game's own reset of the camera behind Alex
	python tools/re/gamectl.py hour h [--stop]           # time of day; --stop freezes the clock there
	python tools/re/gamectl.py quiet                     # no traffic, pedestrians, patrols, strike teams
	python tools/re/gamectl.py traffic on|off            # the ambient manager only (cars and pedestrians)
	python tools/re/gamectl.py pause | resume | step     # the game's own pause (gameflow), one step while paused
	python tools/re/gamectl.py keys "shift+w:2,:0.5"     # held keys (names as keys.py, lmb/rmb), waits until done
	python tools/re/gamectl.py mouse dx dy               # a relative mouse move (the game's mouse counts)
	python tools/re/gamectl.py shot out.png              # the next frame (opprobe.py shot)
	python tools/re/gamectl.py lua "return tod_GetTimeOfDay()"
	python tools/re/gamectl.py status                    # threads, Lua state, input hooks
	python tools/re/gamectl.py stop                      # end this copy

The copy is the folder in OP_ORIGINAL_DIR (as for the other tools); `launch` and `stop` end a running game, so they
refuse to run unless OP_ORIGINAL_DIR names the copy explicitly.
"""

import ctypes
import math
import os
import pathlib
import subprocess
import sys
import time

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import probe  # noqa: E402

GAME_DIR = probe.GAME_DIR
REQUEST = GAME_DIR / "opprobe_cmd.request"
RESULT = GAME_DIR / "opprobe_cmd.result"
LOCK = GAME_DIR / "opprobe_cmd.lock"
WAKE_MESSAGE = 0x8000 + 0x4F50  # WM_APP + 0x4F50, as in gamecontrol.hpp
# Engine options read from args.txt at start: no legal screens and movies, no "press a key"
# after loading, no autosave (the copies share the saves), keep running without focus
FAST_OPTIONS = ["SkipMovies", "NoMovie", "NoFELoadingPrompt", "NoAutoSave", "NoSleepOnLostFocus"]

user32 = ctypes.WinDLL("user32", use_last_error=True)


class GameError(Exception):
	pass


def window():
	import keys
	return keys.game_window()


class requestLock:
	"""One request at a time per copy (several tools may talk to the same game); a lock older than 30 s is left over."""

	def __enter__(self):
		deadline = time.time() + 30.0
		while True:
			try:
				os.close(os.open(LOCK, os.O_CREAT | os.O_EXCL | os.O_WRONLY))
				return self
			except FileExistsError:
				try:
					if time.time() - LOCK.stat().st_mtime > 30.0:
						LOCK.unlink(missing_ok=True)
						continue
				except FileNotFoundError:
					continue
				if time.time() > deadline:
					raise GameError("the request lock is held")
				time.sleep(0.01)

	def __exit__(self, *_):
		LOCK.unlink(missing_ok=True)


def request(text, timeout=10.0):
	"""Sends one request to the proxy and returns its output; raises GameError when the game reports an error."""
	with requestLock():
		RESULT.unlink(missing_ok=True)
		temporary = REQUEST.with_suffix(".tmp")
		temporary.write_bytes(text.encode("utf-8"))
		os.replace(temporary, REQUEST)
		hwnd = window()
		if hwnd:
			user32.PostMessageW(hwnd, WAKE_MESSAGE, 0, 0)
		deadline = time.time() + timeout
		while time.time() < deadline:
			if RESULT.exists():
				try:
					answer = RESULT.read_bytes().decode("utf-8", errors="replace")
				except PermissionError:
					time.sleep(0.005)
					continue
				RESULT.unlink(missing_ok=True)
				status, _, output = answer.partition("\n")
				if status != "ok":
					raise GameError(output.strip())
				return output
			time.sleep(0.005)
		REQUEST.unlink(missing_ok=True)
	raise GameError("no answer: is the game running with the proxy d3d9.dll (with the control channel)?")


def lua(code, timeout=10.0):
	"""Runs a Lua chunk in the game; returns the values it returned, as strings."""
	return request("lua " + code, timeout).splitlines()


def luaValue(code, timeout=10.0):
	values = lua(code, timeout)
	return values[0] if values else None


# --- Process ---------------------------------------------------------------------------------------------------------

def requireExplicitCopy():
	if not os.environ.get("OP_ORIGINAL_DIR"):
		raise SystemExit("launch and stop end a running game: set OP_ORIGINAL_DIR to the copy they are meant for")


def running():
	try:
		return probe.findProcess()
	except SystemExit:
		return None


def stop():
	"""Ends the copy of the game in GAME_DIR (only that one: the process whose image is in that folder)."""
	requireExplicitCopy()
	pid = running()
	if pid is None:
		return
	subprocess.run(["taskkill", "/PID", str(pid), "/F"], capture_output=True)
	for _ in range(100):
		if running() is None:
			break
		time.sleep(0.1)
	else:
		raise SystemExit(f"process {pid} did not end")
	for leftover in (REQUEST, RESULT, LOCK):
		leftover.unlink(missing_ok=True)


def writeOptions():
	"""args.txt in the game folder holds the engine options; the fast ones are added, others are kept."""
	path = GAME_DIR / "args.txt"
	lines = path.read_text().split() if path.exists() else []
	missing = [option for option in FAST_OPTIONS if option not in lines]
	if missing:
		path.write_text("\n".join(lines + missing) + "\n")


def start():
	"""Starts the game and waits until the control channel answers (the title screen)."""
	requireExplicitCopy()
	writeOptions()
	subprocess.Popen([str(GAME_DIR / "prototypef.exe")], cwd=str(GAME_DIR), creationflags=0x00000008 | 0x00000200)
	deadline = time.time() + 90.0
	while time.time() < deadline:
		if running() is not None and window():
			try:
				request("status", timeout=1.0)
				return
			except GameError:
				pass
		time.sleep(0.25)
	raise SystemExit("the game did not answer within 90 s")


# --- Game state ------------------------------------------------------------------------------------------------------

def press(script, wait=True):
	"""Holds keys in the game (proxy key script); waits until the script has run."""
	output = request("keys " + script)
	if wait:
		seconds = sum(float(step.rpartition(":")[2]) for step in script.split(","))
		time.sleep(seconds + 0.05)
	return output


def inFreeRoam():
	"""The HUD is up, Alex exists and the save system is idle (flags only: no game object is touched while loading)."""
	try:
		return luaValue("return fe_GetHudLoaded() and PLAYER_1 ~= nil and not sgm_IsActive()") == "true"
	except GameError:
		return False


def waitFreeRoam(timeout=120.0):
	deadline = time.time() + timeout
	while time.time() < deadline:
		if inFreeRoam():
			time.sleep(1.0)
			return
		time.sleep(0.5)
	raise SystemExit("not in free roam after loading (see gamectl.py shot)")


def storageActive():
	return luaValue("return sgm_IsActive()") == "true"


def openLoadDialog():
	"""sgm_LoadGame opens the save list (newest save highlighted) at the main menu; sgm_IsActive tells that it did.
	The list takes about a second to take the keyboard: an Enter before that goes to the menu behind it, which then
	keeps the focus, so confirmLoad waits first. (In the game the same dialog loads too, but the engine then crashes
	while it restarts the world; a clean state is a new launch.)"""
	if not storageActive():
		lua("sgm_LoadGame()")
	return storageActive()


def confirmLoad(older=0):
	"""Enter on the highlighted save (the newest, or `older` entries further down the list), then Enter on Yes until
	the save system starts loading."""
	time.sleep(2.0)
	for _ in range(older):
		press("s:0.2,:0.3")
	press("enter:0.2")
	for _ in range(8):
		time.sleep(1.5)
		if not storageActive():
			break
		press("enter:0.2")
	else:
		raise SystemExit("the load was not confirmed (see gamectl.py shot)")
	waitFreeRoam()


def launch(older=0):
	"""Restarts this copy and loads the newest save (or the `older`-th older one): the title, two notices, then the load dialog, all without the
	window in front. The front end has no state Lua can read, so the menus are timed; the load dialog is checked."""
	began = time.time()
	stop()
	start()
	time.sleep(1.5)
	press("enter:0.2,:2.0")  # title
	press("enter:0.2,:2.0")  # notice: input device
	press("enter:0.2,:2.5")  # notice: autosave; then the main menu
	for _ in range(4):
		if openLoadDialog():
			break
		press("enter:0.2,:2.5")  # a notice that came late
	else:
		raise SystemExit("the main menu did not come up (see gamectl.py shot)")
	confirmLoad(older)
	print(f"free roam after {time.time() - began:.1f} s")
	where()


def where():
	x, y, z, dx, dz = (float(v) for v in lua("local p, d = go_GetPosition(PLAYER_1), go_GetOrientation(PLAYER_1) "
		"return p.x, p.y, p.z, d.x, d.z"))
	yaw = math.degrees(math.atan2(dx, dz)) % 360.0
	print(f"feet {x:.2f} {y - 1.0:.2f} {z:.2f}  yaw {yaw:.1f}")
	return (x, y - 1.0, z), yaw


def teleport(x, y, z, yaw=None):
	"""go_ProtoTeleport, the mission scripts' teleport: it flushes the player's stream driver, so the cells at the
	destination load first, puts Alex there (go_PlayerTeleport) and finally onto the supporting surface under the
	point. Without fades. (x, y, z) are the feet."""
	if yaw is None:
		_, yaw = where()
	angle = math.radians(yaw)
	lua(f"go_ProtoTeleport(PLAYER_1, Vector({x}, {y}, {z}), Vector({math.sin(angle)}, 0, {math.cos(angle)}), true, true)")
	deadline = time.time() + 30.0
	time.sleep(0.2)
	while time.time() < deadline and luaValue("return go_IsPlayerTeleporting()") == "true":
		time.sleep(0.1)
	time.sleep(0.3)
	(fx, fy, fz), facing = where()
	if math.hypot(fx - x, fz - z) > 1.0 or abs(fy - y) > 3.0:
		print(f"warning: Alex is {math.hypot(fx - x, fz - z):.1f} m from the target, {fy - y:+.1f} m in height")


def camera(args):
	if args and args[0] == "behind":
		lua("cm_ResetChaseCamBehind(0)")
		print("camera behind Alex")
	else:
		print(request("camera " + " ".join(args)).strip())


def hour(value, freeze=False):
	lua(f"tod_SetTimeOfDay({value % 24.0})" + (" tod_SetSpeed(0)" if freeze else " tod_SetSpeed(1)"))
	print(f"hour {float(luaValue('return tod_GetTimeOfDay()')):.3f}, speed {luaValue('return tod_GetSpeed()')}")


def quiet():
	"""The ambient manager off (it removes its pedestrians and cars), the military patrols destroyed and disabled,
	no strike teams."""
	lua("amb_EnableManager(false) ai_patrol_DisableAndDestroy() ai_EnableStrikeTeams(false) ai_ClearAllStrikeTeams()")
	print("quiet: no ambient pedestrians and cars, no patrols, no strike teams")


def traffic(on):
	lua(f"amb_EnableManager({'true' if on else 'false'})")
	print(f"ambient manager {'on' if on else 'off'}")


def main(args):
	if not args:
		print(__doc__)
		return
	command, rest = args[0], args[1:]
	try:
		if command == "launch" and len(rest) <= 1:
			launch(int(rest[0]) if rest else 0)
		elif command == "stop":
			stop()
		elif command == "start":
			stop()
			start()
		elif command == "status":
			print(request("status"), end="")
		elif command == "lua":
			print("\n".join(lua(" ".join(rest))))
		elif command == "where":
			where()
		elif command == "teleport" and len(rest) in (3, 4):
			teleport(*map(float, rest))
		elif command == "camera" and rest:
			camera(rest)
		elif command == "hour" and rest:
			hour(float(rest[0]), "--stop" in rest)
		elif command == "quiet":
			quiet()
		elif command == "traffic" and rest and rest[0] in ("on", "off"):
			traffic(rest[0] == "on")
		elif command == "pause":
			lua("gameflow_Pause()")
		elif command == "resume":
			lua("gameflow_Unpause()")
		elif command == "step":
			lua("gameflow_SingleStep()")
		elif command == "keys" and rest:
			print(press(rest[0]).strip())
		elif command == "mouse" and len(rest) == 2:
			print(request(f"mouse {int(rest[0])} {int(rest[1])}").strip())
		elif command == "release":
			print(request("release").strip())
		elif command == "shot" and rest:
			import opprobe
			opprobe.shot(rest[0])
		else:
			print(__doc__)
	except GameError as error:
		raise SystemExit(f"error: {error}")


if __name__ == "__main__":
	main(sys.argv[1:])
