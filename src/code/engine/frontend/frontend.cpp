// The frontend output layer: the mouse cursor, the screen centre and the update flag the `fe_*` Lua natives of this
// unit write (fe_SetUpdateEnable is registered from 0x10864AF0). No assert path names the file, so the directory and
// file name are guesses; the class names are unknown and the accessors are free functions until the binary names
// them.
#include "code/core/heap.h"
#include "code/core/language.h"
#include "code/core/strings.h"
#include "code/engine/controller/inputsystem.h"
#include "code/engine/controller/physicalcontroller.h"
#include "code/engine/controller/physicalcontrollermapmanager.h"
#include "code/engine/display.h"
#include "code/engine/frontend/fesubtitle.h"
#include "code/engine/frontend/feinputhandler.h"
#include "code/engine/frontend/frontend.h"

#include "code/engine/function.h"
#include "code/engine/luascriptmanager.h"
#include "code/engine/system/enginememory.h"
#include "code/engine/system/skuinfo.h"
#include "code/math/mathutils.h"
#include <math.h>
#include <string.h>

extern "C" __declspec(dllimport) int __stdcall GetSystemMetrics(int index);
#pragma comment(linker, "/alternatename:__imp__GetSystemMetrics@4=__imp__GetSystemMetrics")

namespace engine
{
	namespace driving
	{
		extern const float gOne;
	}

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
	core::Name<core::CaseSensitiveKey> sLanguageName("english", 0);
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
	bool fe_EnableCatchupBehaviour(bool enable)
	{
		GameObjectHandle* handle = &((FrontendObject*)GetFrontend())->handle;
		return handle->SetUnknown9C(enable);
	}

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

	// The functions of the other front end units this one calls (names guessed; 0x1088A590 updates the next layer)
	void UpdateFEInput();
	// The front end's movie as this unit uses it (the object GetFrontend answers): 0x10872AD0 advances it by the
	// frame's time (a member: the object comes in ecx and the function pops its argument)
	class FrontendUpdater
	{
	public:
		void Unknown10872AD0(UpdateContext context);
	};
	void Unknown1088A590();
	void Unknown108740E0(int heap, int a, int b);
	void Unknown108E20B0(int heap);
	void Unknown108E1B80(int value);
	void SetMouseVisible(bool visible, bool option);
	bool GetMouseVisible();
	bool GetMouseVisibleOption();

	// The mouse as a game pad: the swap of the buttons is the system's, the wheel and the move are axes of the pad
	// (0x10864600)
	// FUNCTION: ENGINE 0x10864600
	// EQUIVALENT: the compiler keeps the constant 1 in a register for the static's guard and the three flags where the
	// engine uses immediates, loads the slot's low byte, and schedules the float part of the cursor limit differently,
	// 36 %
	void UpdateFrontend(UpdateContext context)
	{
		if ((GetMouseVisible() || (!GetMouseVisible() && GetMouseVisibleOption())) && !sScreenCentreSet)
		{
			static unsigned int sSlot = controller::InputSystem::LocalId(1);
			controller::PhysicalControllerMapManager* maps =
				(controller::PhysicalControllerMapManager*)controller::InputSystem::Get()->override;
			controller::PhysicalController* pad = maps->GetConnected(sSlot);
			if (pad != 0)
			{
				float moveX = 0.0f;
				float moveY = 0.0f;
				float wheel = 0.0f;
				controller::PhysicalController::AxisBinding* axis = pad->FindAxis(6);
				if (axis != 0)
				{
					moveX = axis->raw;
				}
				axis = pad->FindAxis(7);
				if (axis != 0)
				{
					moveY = axis->raw;
				}
				axis = pad->FindAxis(8);
				if (axis != 0)
				{
					axis->point->SetRange(0.0f, 1.0f);
					wheel = axis->point->Read(0);
				}
				int width = gDisplay->GetWidth();
				sScreenCentreX += (int)moveX;
				int height = gDisplay->GetUnknown8();
				sScreenCentreY += (int)moveY;
				int newY;
				if (sCursorScale == -1.0f)
				{
					if (sScreenCentreX > width)
					{
						sScreenCentreX = width;
					}
					else if (sScreenCentreX < 0)
					{
						sScreenCentreX = 0;
					}
					newY = height;
					if (sScreenCentreY <= height)
					{
						newY = sScreenCentreY;
						if (sScreenCentreY < 0)
						{
							sScreenCentreY = 0;
							newY = sScreenCentreY;
						}
					}
				}
				else
				{
					float halfWidth = (float)(gDisplay->GetWidth() / 2);
					float halfHeight = (float)(gDisplay->GetUnknown8() / 2);
					float offsetX = (float)sScreenCentreX - halfWidth;
					float offsetY = (float)sScreenCentreY - halfHeight;
					float distance = sqrtf(offsetY * offsetY + offsetX * offsetX);
					newY = sScreenCentreY;
					if (sCursorScale < distance)
					{
						float factor = driving::gOne / distance;
						sScreenCentreX = (int)(factor * offsetX * sCursorScale + halfWidth);
						newY = (int)(factor * offsetY * sCursorScale + halfHeight);
					}
				}
				sScreenCentreY = newY;
				float right = 0.0f;
				float left = 0.0f;
				float middle = 0.0f;
				int swapped = GetSystemMetrics(0x17);
				controller::PhysicalController::ButtonBinding* button = pad->FindButton(0x27);
				if (swapped != 0)
				{
					button = pad->FindButton(0x29);
				}
				if (button != 0)
				{
					right = button->point->Read(0);
				}
				button = pad->FindButton(0x29);
				if (swapped != 0)
				{
					button = pad->FindButton(0x27);
				}
				if (button != 0)
				{
					left = button->point->Read(0);
				}
				button = pad->FindButton(0x28);
				if (button != 0)
				{
					middle = button->point->Read(0);
				}
				SetScreenFlag(0, right == driving::gOne, sScreenCentreX, sScreenCentreY);
				SetScreenFlag(1, left == driving::gOne, sScreenCentreX, sScreenCentreY);
				SetScreenFlag(2, middle == driving::gOne, sScreenCentreX, sScreenCentreY);
				SetScreenClampedFloat(sScreenCentreX, sScreenCentreY, wheel);
				SetScreenCentre(sScreenCentreX, sScreenCentreY);
			}
		}
		FrontendUpdater* frontend;
		if (sUpdateEnabled && (frontend = (FrontendUpdater*)GetFrontend()) != 0)
		{
			frontend->Unknown10872AD0(context);
		}
		UpdateFEInput();
		if (gSubtitleOptions != 0)
		{
			gSubtitleOptions->Update(context);
		}
		Unknown1088A590();
	}

	// What the game hands the front end when it starts it (heap, two numbers for the movie layer, the reference
	// resolution and the cursor's fade time; names guessed)
	struct FrontendParams
	{
		int heap;
		int unknown4;
		int unknown8;
		float width;
		float height;
		float fade;
	};

	// FUNCTION: ENGINE 0x10864AF0
	void StartFrontend(const FrontendParams* params)
	{
		sFrontendHeap = params->heap;
		sScreenWidth = params->width;
		sScreenHeight = params->height;
		sScreenCentreSet = !(((unsigned int)controller::InputSystem::Get()->config.unknown8 >> 3) & 1);
		Unknown108740E0(sFrontendHeap, params->unknown4, params->unknown8);
		CreateFEInputHandler(sFrontendHeap);
		Unknown108E20B0(sFrontendHeap);
		LuaScriptManager* script = GetScriptManager();
		script->SetOwner(&sUnknown5C);
		script->Register("fe_SetUpdateEnable", fe_SetUpdateEnable);
		script->Register("fe_SetMouseVisibility", SetMouseVisible);
		script->Register("fe_EnableCatchupBehaviour", fe_EnableCatchupBehaviour);
		script->Register("fe_ToggleHideHUDOption", fe_ToggleHideHUDOption);
		script->ClearOwner();
		{
			core::HeapScope scope(sFrontendHeap);
			Unknown108E1B80(0x32);
		}
		sCursorFade = params->fade;
		memset(sScreenFlags, 0, 3);
		UpdateScreenCentre();
		sUnknown64 = true;
	}
}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D75A40
// FUNCTION: ENGINE 0x10D8A670


// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1036BA70
// FUNCTION: ENGINE 0x1036BAE0
// FUNCTION: ENGINE 0x1036BB00
