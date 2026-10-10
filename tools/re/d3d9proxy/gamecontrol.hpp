// Control of the running original from outside (docs/re/game_control.md): a command channel served on the game's main
// thread, Lua run in the game's own script state, the chase camera's orbit, and keys and mouse fed to the game's
// DirectInput devices without the window in front.
#pragma once

#include <windows.h>

namespace gamecontrol
{
	// Posted to the game's window to run a pending request on the thread that owns it (the game's main thread)
	constexpr UINT WAKE_MESSAGE = WM_APP + 0x4F50;

	// The window whose procedure runs on the game's main thread
	void attach(HWND window);
	// Present, every frame: notices a request file and wakes the window's thread
	void onPresent();
	// Window procedure: runs a pending request; true if the message was ours
	bool onMessage(HWND window, UINT message);
	// Patches the DirectInput device vtables (keyboard and mouse, ANSI and wide) so injected input reaches the game
	void hookInput();
}
