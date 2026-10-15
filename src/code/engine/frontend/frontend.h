// The frontend output layer: see the source file. The unit registers the `fe_*` Lua natives; no assert path names
// it, so the class, member and method names are guesses.
#ifndef ENGINE_FRONTEND_FRONTEND_H
#define ENGINE_FRONTEND_FRONTEND_H

#include "code/core/name.h"
#include "code/engine/display.h"

namespace engine
{
	// 0x108642D0: the Lua native fe_SetUpdateEnable; answers the value the flag had
	bool fe_SetUpdateEnable(bool enable);

	// 0x10864310 / 0x10864330: the frontend object the cursor code works on
	void SetFrontend(void* frontend);
	void* GetFrontend();
	// 0x10864340: the heap the frontend allocates from (0x108642E0)
	int GetFrontendHeap();
	// 0x10864390: the centre of the screen, and the game script that follows it
	void SetScreenCentre(int x, int y);
	// 0x10864420 / 0x10864430: the reference resolution
	float GetScreenWidth();
	float GetScreenHeight();
	// 0x10864440: the centre of the display, once
	void UpdateScreenCentre();
	// 0x10864490 / 0x108644A0 / 0x108644E0 / 0x108644F0 / 0x10864500: the cursor's fade time and scale
	void SetCursorFade(float fade);
	float GetCursorFade();
	void SetCursorScale(float scale);
	float GetCursorScale();
	void ResetCursorScale();
	// 0x10864520 / 0x10864530: the centre of the screen as floats
	float GetScreenCentreX();
	float GetScreenCentreY();
	// 0x10864560 / 0x10864590: the HideHUD option (its Lua native toggles it)
	int ShouldHideHUD();
	void fe_ToggleHideHUDOption();
	// 0x10864AE0: back to the language the system asks for ('?')
	void ResetLanguage();
	// 0x10864A20 (another function of this unit): selects the language of the frontend
	void SetLanguage(int language);
	// 0x108649F0 / 0x10864A00: the language the frontend is set to now
	void SetLanguageName(const core::Name<core::CaseSensitiveKey>& name);
	core::Name<core::CaseSensitiveKey> GetLanguageName();

	// 0x10848E70 (another unit): whether the game's command line has the option
	bool HasCommandLineOption(const char* option);

	// The cursor's position (another function of this unit)
	void UpdateCursorPosition(int x, int y);
	// Another function of this unit: passes the frontend on to the output layer
	void SetFrontendOutput(void* frontend);

	extern int sFrontendHeap;
	extern void* sFrontend;
}

#endif
