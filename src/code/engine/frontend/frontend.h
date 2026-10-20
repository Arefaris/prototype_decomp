// The frontend output layer: see the source file. The unit registers the `fe_*` Lua natives; no assert path names
// it, so the class, member and method names are guesses.
#ifndef ENGINE_FRONTEND_FRONTEND_H
#define ENGINE_FRONTEND_FRONTEND_H

#include "code/core/name.h"
#include "code/engine/display.h"
#include "code/engine/gameobject/gameobjecthandle.h"

namespace engine
{
	struct Message;

	// The frontend object the unit builds (0x1238 bytes, 0x108642E0) and works on: a handle at +0x2C, the object
	// the screen follows. Only the members this unit touches are spelled out.
	struct FrontendObject
	{
		// 0x10872D70 (the Scaleform unit): builds the object in the memory given and answers it
		FrontendObject* Construct(int a, int b);
		// 0x108642C0: the member at +0x5C
		void** GetUnknown5C();

		unsigned char unknown0[0x2C];
		GameObjectHandle handle;
		unsigned char unknown30[0x5C - 0x30];
		void* unknown5C;
		unsigned char unknown60[0x1238 - 0x60];
	};

	// 0x108642D0: the Lua native fe_SetUpdateEnable; answers the value the flag had
	bool fe_SetUpdateEnable(bool enable);

	// 0x108642E0: builds the frontend object in the frontend heap (0x1238 bytes)
	void* CreateFrontend(int a, int b);
	// 0x10881340 / 0x108814F0 (the Scaleform unit): writes a value into the frontend's screen object, while the
	// screen is up (its static at 0x11316C95)
	void SetScreenValue(int index, bool value, int a, int b);
	void SetScreenFloat(int index, int a, float value);
	// 0x10864350: one of the screen's boolean options, kept in the flag array at 0x11315C58
	void SetScreenFlag(int index, bool value, int a, int b);
	// 0x108643B0: one of the screen's floats, held between -120 and 120
	void SetScreenClampedFloat(int index, int a, float value);
	// 0x10864540: hands the flag on to the object the frontend follows (the Lua native fe_EnableCatchupBehaviour)
	void fe_EnableCatchupBehaviour(bool enable);
	// 0x108645A0: shuts the frontend down and forgets it
	void ShutdownFrontend();

	// The subsystems the frontend owns, each released out of line by its own unit (the globals at 0x1131AA68,
	// 0x1131AA6C and 0x11316C90; the Screenform screen's is 0x10873220)
	void ReleaseSubsystemAA68();
	void ReleaseSubsystemAA6C();
	void ReleaseSubsystem16C90();
	void ReleaseScreen();

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
	// The languages the game supports (0x113176C8 holds the table; entries of 32 bytes, each starting with the name)
	class LanguageTable
	{
	public:
		// 0x108928C0 / 0x108928D0 (kept copies of the unit that owns the table)
		unsigned int GetCount();
		const char* GetName(unsigned int index);
	};
	// 0x10892690
	LanguageTable* GetLanguageTable();

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
