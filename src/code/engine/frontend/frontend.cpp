// The frontend output layer: the mouse cursor, the screen centre and the update flag the `fe_*` Lua natives of this
// unit write (fe_SetUpdateEnable is registered from 0x10864AF0). No assert path names the file, so the directory and
// file name are guesses; the class names are unknown and the accessors are free functions until the binary names
// them.
#include "code/engine/frontend/frontend.h"

namespace engine
{
	// GLOBAL: ENGINE 0x111CEF38
	static bool sUpdateEnabled = true;
	// GLOBAL: ENGINE 0x111CEF3C
	static float sScreenWidth = 1280.0f;
	// GLOBAL: ENGINE 0x111CEF40
	static float sScreenHeight = 720.0f;
	// GLOBAL: ENGINE 0x111CEF44
	static float sCursorScale = -1.0f;
	// GLOBAL: ENGINE 0x111CEF48
	static float sCursorFade = 0.28f;
	// GLOBAL: ENGINE 0x11315C60
	int sFrontendHeap = 0;
	// GLOBAL: ENGINE 0x11315C65
	static bool sScreenCentreSet = false;
	// GLOBAL: ENGINE 0x11315C68
	void* sFrontend = 0;
	// GLOBAL: ENGINE 0x11315C6C
	static int sScreenCentreX = 0;
	// GLOBAL: ENGINE 0x11315C70
	static int sScreenCentreY = 0;

	// FUNCTION: ENGINE 0x108642D0
	bool fe_SetUpdateEnable(bool enable)
	{
		bool previous = sUpdateEnabled;
		sUpdateEnabled = enable;
		return previous;
	}

	// FUNCTION: ENGINE 0x10864310
	void SetFrontend(void* frontend)
	{
		sFrontend = frontend;
		SetFrontendOutput(frontend);
	}

	// FUNCTION: ENGINE 0x10864330
	void* GetFrontend()
	{
		return sFrontend;
	}

	// FUNCTION: ENGINE 0x10864340
	int GetFrontendHeap()
	{
		return sFrontendHeap;
	}

	// FUNCTION: ENGINE 0x10864390
	void SetScreenCentre(int x, int y)
	{
		sScreenCentreX = x;
		sScreenCentreY = y;
		UpdateCursorPosition(x, y);
	}

	// FUNCTION: ENGINE 0x10864420
	float GetScreenWidth()
	{
		return sScreenWidth;
	}

	// FUNCTION: ENGINE 0x10864430
	float GetScreenHeight()
	{
		return sScreenHeight;
	}

	// FUNCTION: ENGINE 0x10864440
	void UpdateScreenCentre()
	{
		if (!sScreenCentreSet)
		{
			sScreenCentreX = gDisplay->GetWidth() / 2;
			sScreenCentreY = gDisplay->GetUnknown8() / 2;
			SetScreenCentre(sScreenCentreX, sScreenCentreY);
		}
	}

	// FUNCTION: ENGINE 0x10864490
	void SetCursorFade(float fade)
	{
		sCursorFade = fade;
	}

	// FUNCTION: ENGINE 0x108644A0
	float GetCursorFade()
	{
		return sCursorFade;
	}

	// FUNCTION: ENGINE 0x108644E0
	void SetCursorScale(float scale)
	{
		sCursorScale = scale;
	}
}
