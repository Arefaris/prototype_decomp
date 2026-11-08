#include "code/proto/frontend/fehudscreen.h"

#include "code/core/heap.h"
#include "code/engine/camera/cinematographer.h"
#include "code/engine/camera/director.h"
#include "code/engine/frontend/frontend.h"
#include "code/engine/function.h"
#include "code/engine/luascriptmanager.h"
#include <math.h>

namespace engine
{
	class FrontEnd;
	// 0x10864330
	FrontEnd* Unknown10864330();
	// 0x10872840: calls a function of the front end's movie with a format and the arguments it names (name unknown)
	void Unknown10872840(FrontEnd* frontEnd, const char* function, const char* format, ...);
}

namespace engine
{
	namespace driving
	{
		// 0x10D94CC4
		extern const float gHalf;
	}
}

namespace proto
{
	int GetLocalPlayerIndex();

	// 0x11097834 - 0x11097844: how the movie's 1280 by 720 area maps onto the screen (the factors and offsets of both axes
	// and the aspect they were made for); all minus one until the first update
	static float sScaleY = -1.0f;
	static float sScaleX = -1.0f;
	static float sOffsetX = -1.0f;
	static float sOffsetY = -1.0f;
	static float sAspect = -1.0f;

	// FUNCTION: ENGINE 0x104C0D00
	void ScaleFEHudX(float* x, bool shift)
	{
		float scaled = *x * sScaleX;
		*x = scaled;
		if (shift)
		{
			scaled = scaled - sOffsetX;
		}
		*x = scaled;
	}

	// FUNCTION: ENGINE 0x104C0D40
	void ScaleFEHudY(float* y, bool shift)
	{
		float scaled = *y * sScaleY;
		*y = scaled;
		if (shift)
		{
			scaled = scaled - sOffsetY;
		}
		*y = scaled;
	}

	// FUNCTION: ENGINE 0x104C0D80
	void UpdateFEHudScale()
	{
		engine::camera::CameraTarget* target = engine::camera::Director::Get()->GetCameraTarget(GetLocalPlayerIndex(), 0);
		if (target != 0)
		{
			float aspect = target->width / target->height;
			if (!(fabsf(sAspect - aspect) <= 0.00001f))
			{
				sAspect = aspect;
				if (aspect <= 16.0f / 9.0f)
				{
					sScaleX = 1280.0f;
					sScaleY = 1280.0f / aspect;
					sOffsetX = 0.0f;
					sOffsetY = (sScaleY - 720.0f) * engine::driving::gHalf;
				}
				else
				{
					sScaleX = aspect * 720.0f;
					sOffsetX = (sScaleX - 1280.0f) * engine::driving::gHalf;
					sScaleY = 720.0f;
					sOffsetY = 0.0f;
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x104C1000
	void ScaleFEHud(float* x, float* y, bool shift)
	{
		ScaleFEHudX(x, shift);
		ScaleFEHudY(y, shift);
	}

	// FUNCTION: ENGINE 0x104C1C40
	FEHudScreen::FEHudScreen()
	{
		created = false;
		miniMap = 0;
		health = 0;
		powers = 0;
		popup = 0;
		disguisePerception = 0;
		buttonHint = 0;
		targeting = 0;
		evolutionPoints = 0;
		disguiseActions = 0;
		meter = 0;
		textLog = 0;
		vehicleHealth = 0;
		eventPopup = 0;
		missionPopup = 0;
		opportunityEventPopup = 0;
		typewriter = 0;
		keyCard = 0;
		awareness = 0;
		combatConclusion = 0;
		engine::LuaScriptManager* manager = engine::GetScriptManager();
		manager->SetOwner(this);
		manager->RegisterMethod("fe_GetEnabledHudElements", this, &FEHudScreen::GetEnabledElements);
		manager->RegisterMethod("fe_ForceShowPopups", this, &FEHudScreen::ForceShowPopups);
		manager->RegisterMethod("fe_GetHideHudElementRefCount", this, &FEHudScreen::GetHideCount);
		manager->RegisterMethod("fe_SetHideHudElementRefCount", this, &FEHudScreen::SetHideCount);
		manager->ClearOwner();
	}

	// FUNCTION: ENGINE 0x104C1400
	void FEHudScreen::Create()
	{
		core::HeapScope scope(0x72);
		if (miniMap == 0)
		{
			miniMap = new FEHudMiniMap;
		}
		if (health == 0)
		{
			health = new FEHudHealth;
		}
		if (powers == 0)
		{
			powers = new FEHudPowers;
		}
		if (popup == 0)
		{
			popup = new FEHudPopup;
		}
		if (disguisePerception == 0)
		{
			disguisePerception = new FEHudDisguisePerception;
		}
		if (buttonHint == 0)
		{
			buttonHint = new FEHudButtonHint;
		}
		if (targeting == 0)
		{
			targeting = new FEHudTargeting;
		}
		if (evolutionPoints == 0)
		{
			evolutionPoints = new FEHudEvolutionPoints;
		}
		if (disguiseActions == 0)
		{
			disguiseActions = new FEHudDisguiseActions;
		}
		if (meter == 0)
		{
			meter = new FEHudMeter;
		}
		if (textLog == 0)
		{
			textLog = new FEHudTextLog;
		}
		if (vehicleHealth == 0)
		{
			vehicleHealth = new FEHudVehicleHealth;
		}
		if (eventPopup == 0)
		{
			eventPopup = new FEHudEventPopup;
		}
		if (missionPopup == 0)
		{
			missionPopup = new FEHudMissionPopup;
		}
		if (opportunityEventPopup == 0)
		{
			opportunityEventPopup = new FEHudOpportunityEventPopup;
		}
		if (typewriter == 0)
		{
			typewriter = new FEHUDTypewriter;
		}
		if (keyCard == 0)
		{
			keyCard = new FEHudKeyCard;
		}
		if (awareness == 0)
		{
			awareness = new FEHudAwareness;
		}
		if (combatConclusion == 0)
		{
			combatConclusion = new FEHudCombatConclusion;
		}
		created = true;
		if ((char)engine::ShouldHideHUD() != 0)
		{
			ShowAll(false);
		}
	}

	// FUNCTION: ENGINE 0x104C1EA0
	void FEHudScreen::Destroy(bool keepMiniMap)
	{
		engine::Unknown10872840(engine::Unknown10864330(), "AS_ClearHUDData", "");
		if (miniMap != 0 && !keepMiniMap)
		{
			delete miniMap;
			miniMap = 0;
		}
		delete health;
		delete powers;
		delete popup;
		delete disguisePerception;
		delete buttonHint;
		delete targeting;
		delete evolutionPoints;
		delete disguiseActions;
		delete meter;
		delete textLog;
		delete vehicleHealth;
		delete eventPopup;
		delete missionPopup;
		delete opportunityEventPopup;
		delete typewriter;
		delete keyCard;
		delete awareness;
		delete combatConclusion;
		health = 0;
		powers = 0;
		popup = 0;
		disguisePerception = 0;
		buttonHint = 0;
		targeting = 0;
		evolutionPoints = 0;
		disguiseActions = 0;
		meter = 0;
		textLog = 0;
		vehicleHealth = 0;
		eventPopup = 0;
		missionPopup = 0;
		opportunityEventPopup = 0;
		typewriter = 0;
		keyCard = 0;
		awareness = 0;
		combatConclusion = 0;
		created = false;
	}

	// FUNCTION: ENGINE 0x104C04D0
	void FEHudScreen::Update(bool force)
	{
		if (created)
		{
			popup->Update(force);
			health->Update(force);
			miniMap->Update(force);
			powers->Update(force);
			disguisePerception->Update(force);
			buttonHint->Update(force);
			targeting->Update(force);
			evolutionPoints->Update(force);
			disguiseActions->Update(force);
			meter->Update(force);
			textLog->Update(force);
			vehicleHealth->Update(force);
			typewriter->Update(force);
			keyCard->Update(force);
			awareness->Update(force);
			combatConclusion->Update(force);
		}
	}

	// FUNCTION: ENGINE 0x104C0920
	void FEHudScreen::Show(bool show, unsigned int mask)
	{
		if (created)
		{
			if (mask & 1)
			{
				miniMap->Show(show);
			}
			if (mask & 2)
			{
				health->Show(show);
			}
			if (mask & 4)
			{
				powers->Show(show);
			}
			if (mask & 8)
			{
				popup->Show(show);
			}
			if (mask & 0x10)
			{
				disguisePerception->Show(show);
			}
			if (mask & 0x20)
			{
				buttonHint->Show(show);
			}
			if (mask & 0x40)
			{
				targeting->Show(show);
			}
			if (mask & 0x80)
			{
				evolutionPoints->Show(show);
			}
			if (mask & 0x100)
			{
				meter->Show(show);
			}
			if (mask & 0x200)
			{
				textLog->Show(show);
			}
			if (mask & 0x400)
			{
				vehicleHealth->Show(show);
			}
			if (mask & 0x1000)
			{
				keyCard->Show(show);
			}
			if (mask & 0x2000)
			{
				disguiseActions->FEHudElement::Show(show);
			}
			if (mask & 0x4000)
			{
				awareness->Show(show);
			}
			if (mask & 0x8000)
			{
				combatConclusion->FEHudElement::Show(show);
			}
		}
	}

	// FUNCTION: ENGINE 0x104C0F90
	void FEHudScreen::ShowAll(bool show)
	{
		Show(show, 0xFFFFFFFF);
	}

	// FUNCTION: ENGINE 0x104C0A70
	void FEHudScreen::ForceShowPopups()
	{
		while (!popup->IsShown())
		{
			popup->Show(true);
		}
	}

	// FUNCTION: ENGINE 0x104C0AB0
	int FEHudScreen::GetEnabledElements()
	{
		if (!created)
		{
			return 0xFFFFFFFF;
		}
		unsigned int mask = 0;
		if (miniMap->IsShown())
		{
			mask = 1;
		}
		if (health->IsShown())
		{
			mask |= 2;
		}
		if (powers->IsShown())
		{
			mask |= 4;
		}
		if (popup->IsShown())
		{
			mask |= 8;
		}
		if (disguisePerception->IsShown())
		{
			mask |= 0x10;
		}
		if (buttonHint->IsShown())
		{
			mask |= 0x20;
		}
		if (targeting->IsShown())
		{
			mask |= 0x40;
		}
		if (evolutionPoints->IsShown())
		{
			mask |= 0x80;
		}
		if (meter->IsShown())
		{
			mask |= 0x100;
		}
		if (textLog->IsShown())
		{
			mask |= 0x200;
		}
		if (vehicleHealth->IsShown())
		{
			mask |= 0x400;
		}
		if (keyCard->IsShown())
		{
			mask |= 0x1000;
		}
		if (disguiseActions->IsShown())
		{
			mask |= 0x2000;
		}
		if (awareness->IsShown())
		{
			mask |= 0x4000;
		}
		if (combatConclusion->IsShown())
		{
			mask |= 0x8000;
		}
		return mask;
	}

	// FUNCTION: ENGINE 0x104C0C10
	FEHudElement* FEHudScreen::GetElement(unsigned int mask)
	{
		if (mask & 1)
		{
			if (miniMap != 0)
			{
				return miniMap;
			}
		}
		else if (mask & 2)
		{
			return health;
		}
		else if (mask & 4)
		{
			return powers;
		}
		else if (mask & 8)
		{
			return popup;
		}
		else if (mask & 0x10)
		{
			return disguisePerception;
		}
		else if (mask & 0x20)
		{
			return buttonHint;
		}
		else if (mask & 0x40)
		{
			return targeting;
		}
		else if (mask & 0x80)
		{
			return evolutionPoints;
		}
		else if (mask & 0x100)
		{
			return meter;
		}
		else if (mask & 0x200)
		{
			return textLog;
		}
		else if (mask & 0x400)
		{
			return vehicleHealth;
		}
		else if (mask & 0x1000)
		{
			return keyCard;
		}
		else if (mask & 0x2000)
		{
			return disguiseActions;
		}
		else if (mask & 0x4000)
		{
			return awareness;
		}
		else if (mask & 0x8000)
		{
			return combatConclusion;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x104C0FB0
	int FEHudScreen::GetHideCount(unsigned int mask)
	{
		FEHudElement* element = GetElement(mask);
		if (element != 0)
		{
			return element->hideCount;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x104C0FD0
	void FEHudScreen::SetHideCount(unsigned int count, unsigned int mask)
	{
		FEHudElement* element = GetElement(mask);
		if (element != 0)
		{
			int newCount = count;
			element->SetHideCount(newCount);
		}
	}

	// FUNCTION: ENGINE 0x104C05C0
	void FEHudScreen::Unknown104C05C0()
	{
		if (created)
		{
			typewriter->Unknown104D9A90(false);
			powers->Unknown104C6420();
		}
	}

	// FUNCTION: ENGINE 0x104C05F0
	void FEHudScreen::Unknown104C05F0()
	{
		if (created)
		{
			powers->Unknown104C58C0();
			evolutionPoints->Unknown104D0A90();
			disguisePerception->ResendDisguises();
			health->Unknown104D4EE0();
			typewriter->Unknown104D9A90(true);
			combatConclusion->Reset();
			Update(true);
		}
	}

	// FUNCTION: ENGINE 0x104C0F00
	void FEHudScreen::Unknown104C0F00(FEHudPoint position)
	{
		if (created)
		{
			UpdateFEHudScale();
			health->Unknown104D3ED0();
			miniMap->Unknown104C4630(position);
			powers->Unknown104C5870();
			buttonHint->Unknown104CE490();
			targeting->Unknown104CAEA0();
			evolutionPoints->Unknown104CFED0();
			vehicleHealth->UpdateHealth();
			eventPopup->Unknown104CFB90();
			missionPopup->Unknown104D0F70();
		}
	}
}
