// The frontend output layer: the mouse cursor, the screen centre and the update flag the `fe_*` Lua natives of this
// unit write (fe_SetUpdateEnable is registered from 0x10864AF0). No assert path names the file, so the directory and
// file name are guesses; the class names are unknown and the accessors are free functions until the binary names
// them.
#include "code/core/language.h"
#include "code/core/strings.h"
#include "code/engine/frontend/frontend.h"

#include "code/engine/luascriptmanager.h"
#include "code/engine/system/enginememory.h"
#include "code/engine/system/skuinfo.h"
#include "code/math/mathutils.h"

namespace engine
{
	// GLOBAL: ENGINE 0x111CEF38
	bool sUpdateEnabled = true;
	// GLOBAL: ENGINE 0x111CEF3C
	float sScreenWidth = 1280.0f;
	// GLOBAL: ENGINE 0x111CEF40
	float sScreenHeight = 720.0f;
	// GLOBAL: ENGINE 0x111CEF44
	float sCursorScale = -1.0f;
	// GLOBAL: ENGINE 0x111CEF48
	float sCursorFade = 0.28f;
	// GLOBAL: ENGINE 0x11315C60
	int sFrontendHeap = 0;
	// GLOBAL: ENGINE 0x11315C65
	bool sScreenCentreSet = false;
	// GLOBAL: ENGINE 0x11315C66
	static bool sHideHUD = false;
	// GLOBAL: ENGINE 0x11315C68
	void* sFrontend = 0;
	// GLOBAL: ENGINE 0x11315C6C
	int sScreenCentreX = 0;
	// GLOBAL: ENGINE 0x11315C70
	int sScreenCentreY = 0;
	// GLOBAL: ENGINE 0x11315C78
	core::Name<core::CaseSensitiveKey> sLanguageName;
	// GLOBAL: ENGINE 0x11315C5C
	int sUnknown5C = 0;
	// GLOBAL: ENGINE 0x11315C64
	bool sUnknown64 = false;

	// FUNCTION: ENGINE 0x108642C0
	void** FrontendObject::GetUnknown5C()
	{
		return &unknown5C;
	}

	// FUNCTION: ENGINE 0x108642E0
	void* CreateFrontend(int a, int b)
	{
		FrontendObject* memory = (FrontendObject*)operator new(0x1238, sFrontendHeap);
		if (memory != 0)
		{
			return memory->Construct(a, b);
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10864540
	// NONMATCHING: the argument is pushed before the frontend is fetched, 57 %
#ifdef NONMATCHING
	void fe_EnableCatchupBehaviour(bool enable)
	{
		FrontendObject* frontend = (FrontendObject*)GetFrontend();
		frontend->handle.SetUnknown9C(enable);
	}
#endif

	// FUNCTION: ENGINE 0x108645A0
	// NONMATCHING: two bytes of the instruction encoding, 98 %
#ifdef NONMATCHING
	void ShutdownFrontend()
	{
		core::Name<core::CaseSensitiveKey> name("", 1);
		sLanguageName = name;
		GetScriptManager()->Unregister(&sUnknown5C);
		ReleaseSubsystemAA6C();
		ReleaseSubsystemAA68();
		ReleaseSubsystem16C90();
		ReleaseScreen();
		SetFrontend(0);
		sUnknown64 = 0;
	}
#endif

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

	// FUNCTION: ENGINE 0x108644F0
	float GetCursorScale()
	{
		return sCursorScale;
	}

	// FUNCTION: ENGINE 0x10864500
	void ResetCursorScale()
	{
		SetCursorScale(-1.0f);
	}

	// GLOBAL: ENGINE 0x11315C58
	bool sScreenFlags[4];

	// GLOBAL: ENGINE 0x10E73254
	const float kScreenClampMin = -120.0f;
	// GLOBAL: ENGINE 0x10DA57E0
	const float kScreenClampMax = 120.0f;

	// FUNCTION: ENGINE 0x10864350
	void SetScreenFlag(int index, bool value, int a, int b)
	{
		if (value || sScreenFlags[index])
		{
			SetScreenValue(index, value, a, b);
		}
		sScreenFlags[index] = value;
	}

	// FUNCTION: ENGINE 0x108643B0
	void SetScreenClampedFloat(int index, int a, float value)
	{
		if (value > 0.0f || value < 0.0f)
		{
			value = math::Clamp(value, kScreenClampMin, kScreenClampMax);
			SetScreenFloat(index, a, value);
		}
	}

	// FUNCTION: ENGINE 0x10864520
	float GetScreenCentreX()
	{
		return (float)sScreenCentreX;
	}

	// FUNCTION: ENGINE 0x10864530
	float GetScreenCentreY()
	{
		return (float)sScreenCentreY;
	}

	// FUNCTION: ENGINE 0x10864560
	int ShouldHideHUD()
	{
		if (sHideHUD || HasCommandLineOption("HideHUD"))
		{
			return 1;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10864590
	void fe_ToggleHideHUDOption()
	{
		sHideHUD ^= 1;
	}

	// FUNCTION: ENGINE 0x10864AE0
	void ResetLanguage()
	{
		SetLanguage('?');
	}

	// FUNCTION: ENGINE 0x108649F0
	void SetLanguageName(const core::Name<core::CaseSensitiveKey>& name)
	{
		sLanguageName = name;
	}

	// FUNCTION: ENGINE 0x10864A00
	core::Name<core::CaseSensitiveKey> GetLanguageName()
	{
		return sLanguageName;
	}

	// FUNCTION: ENGINE 0x10864A20
	void SetLanguage(int language)
	{
		if (language == '?')
		{
			language = core::GetSystemLanguage();
			if (language == '?')
			{
				language = 'E';
			}
		}
		const char* name = core::GetLanguageName(language);
		if (HasCommandLineOption("ForceLanguageSupport"))
		{
			core::LanguageSet(language);
		}
		else
		{
			bool supported = false;
			for (unsigned int index = 0; index < SkuInfo::GetCurrent()->GetLanguageCount(); ++index)
			{
				if (core::StrCmp(name, SkuInfo::GetCurrent()->GetLanguage(index)->language) == 0)
				{
					supported = true;
					break;
				}
			}
			if (supported)
			{
				core::LanguageSet(language);
			}
			else
			{
				core::LanguageSet('E');
			}
		}
		core::Name<core::CaseSensitiveKey> languageName(core::GetLanguageName(core::LanguageGet()), 1);
		SetLanguageName(languageName);
	}
}
