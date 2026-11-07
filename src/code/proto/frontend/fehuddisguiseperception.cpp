#include "code/proto/frontend/fehuddisguiseperception.h"

#include <string.h>

#include "code/core/strings.h"
#include "code/engine/controller/inputsystem.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/proto/messages/disguisemessages.h"
#include "code/proto/frontend/fehudawareness.h"

namespace core
{
	// 0x1063B990 (the same code as SNPrintf; the callers that use the count)
	int SNPrintfCount(char* buffer, int size, const char* format, ...);
}

namespace engine
{
	class FrontEnd;
	// 0x10864330
	FrontEnd* Unknown10864330();
	// 0x10872840: calls a function of the front end's movie with a format and the arguments it names (name unknown)
	void Unknown10872840(FrontEnd* frontEnd, const char* function, const char* format, ...);

	namespace driving
	{
		// 0x10D94F78
		extern const float gZero;
	}
}

namespace proto
{
	// The popups of the head-up display (another unit)
	class PopupController
	{
	public:
		unsigned char unknown0[0x44];
		FEHudAwareness* awareness;  // +0x44
	};

	class FrontEndHud
	{
	public:
		// 0x104B0CE0
		PopupController* GetPopups();
		// 0x104B1D30: plays the sound of a power selection (name unknown)
		void Unknown104B1D30(int index);
	};
	// 0x104B0A00
	FrontEndHud* GetFrontEndHud();

	// The handles of the players' game objects
	extern engine::GameObjectHandle gPlayerHandles[];
	// 0x11097848: the movie clip the head-up display's elements sit in (name guess)
	extern const char* gHudAnchorName;
	// 0x11099194: the movie clip of the perception indicator
	static const char* sPerceptionClip = "mcAnchor.perceptionHUD";

	// FUNCTION: ENGINE 0x104CBF20
	FEHudDisguisePerception::Slot::Slot() : index(-1)
	{
		disguise = 0;
		blown = false;
		alarm = 0;
		maskVisible = true;
		visible.Set(FlashValue(true));
	}

	// FUNCTION: ENGINE 0x104CBC50
	void FEHudDisguisePerception::Slot::Flush(bool force)
	{
		mask.Flush(force);
		visible.Flush(force);
	}

	// FUNCTION: ENGINE 0x104CBF90
	void FEHudDisguisePerception::Slot::SetIndex(int newIndex)
	{
		index = newIndex;
		char text[0x100] = "";
		core::SNPrintfCount(text, 0x100, "_level0.mcAnchor.perceptionHUD.mcDisguise%d.mcMask._y", newIndex);
		mask.path = text;
		memset(text, 0, 0x100);
		core::SNPrintfCount(text, 0x100, "_level0.mcAnchor.perceptionHUD.mcDisguise%d._visible", index);
		visible.path = text;
	}

	// FUNCTION: ENGINE 0x104CBC80
	void FEHudDisguisePerception::Slot::SetBlown(float amount, bool announce, unsigned char alarmLevel)
	{
		if (amount > engine::driving::gZero)
		{
			mask.Set(FlashValue((double)((1.0f - amount) * 100.0f - 45.0f)));
			if (!blown || alarm != alarmLevel)
			{
				if (announce == true)
				{
					alarm = alarmLevel;
					engine::Unknown10872840(engine::Unknown10864330(), "AS_CallASFunction", "%s%s%d%d", sPerceptionClip, "ActivateAlarm", index, alarmLevel);
				}
			}
			visible.Set(FlashValue(maskVisible));
			blown = true;
		}
		else
		{
			alarm = alarmLevel;
			if (blown)
			{
				engine::Unknown10872840(engine::Unknown10864330(), "AS_CallASFunction", "%s%s%d%d", sPerceptionClip, "ActivateUnblown", index, alarmLevel);
			}
			mask.Set(FlashValue(55.0));
			visible.Set(FlashValue(maskVisible));
			blown = false;
		}
	}

	// FUNCTION: ENGINE 0x104CBE30
	void FEHudDisguisePerception::Slot::SetMaskVisible(bool newVisible)
	{
		maskVisible = newVisible;
		visible.Set(FlashValue(newVisible));
		visible.Flush(true);
	}

	// FUNCTION: ENGINE 0x104CBE80
	void FEHudDisguisePerception::Slot::SetDisguise(int newDisguise)
	{
		if (disguise != newDisguise)
		{
			disguise = newDisguise;
			engine::Unknown10872840(engine::Unknown10864330(), "AS_CallASFunction", "%s%s%d%d", gHudAnchorName, "SetDisguise", index, newDisguise);
		}
	}

	// FUNCTION: ENGINE 0x104CBEE0
	void FEHudDisguisePerception::Slot::ResendDisguise()
	{
		engine::Unknown10872840(engine::Unknown10864330(), "AS_CallASFunction", "%s%s%d%d", gHudAnchorName, "SetDisguise", index, disguise);
	}

	// FUNCTION: ENGINE 0x104CBB20
	FEHudDisguisePerception::FEHudDisguisePerception() : hintVisible("_level0.mcAnchor.perceptionHUD.mcHint._visible"),
		visible("_level0.mcAnchor.perceptionHUD._visible"), disguiseHidden(false)
	{
		for (int i = 0; i < 2; i++)
		{
			slots[i].SetIndex(i);
		}
		hintVisible.Set(FlashValue(false));
		visible.Set(FlashValue(true));
	}

	// FUNCTION: ENGINE 0x104CB790
	void FEHudDisguisePerception::Update(bool force)
	{
		for (int i = 0; i < 2; i++)
		{
			slots[i].Flush(force);
		}
		hintVisible.Flush(force);
		visible.Flush(force);
	}

	// FUNCTION: ENGINE 0x104CB900
	void FEHudDisguisePerception::OnShow(bool shown)
	{
		SetVisible(shown);
	}

	// FUNCTION: ENGINE 0x104CB7F0
	void FEHudDisguisePerception::SetVisible(bool newVisible)
	{
		visible.Set(FlashValue(newVisible));
		visible.Flush(true);
	}

	// FUNCTION: ENGINE 0x104CB840
	void FEHudDisguisePerception::ResendDisguises()
	{
		for (int i = 0; i < 2; i++)
		{
			slots[i].ResendDisguise();
		}
	}

	// FUNCTION: ENGINE 0x104CB870
	bool FEHudDisguisePerception::CanShowHint()
	{
		if (slots[0].blown && slots[1].blown != true && slots[1].disguise != 0 && disguiseHidden != true)
		{
			return GetFrontEndHud()->GetPopups()->awareness->IsWatched() ? false : true;
		}
		return false;
	}

	// The handle of a player's game object, the empty handle when there is no such player
	inline engine::GameObjectHandle GetPlayerHandle(int index)
	{
		if (index >= engine::controller::InputSystem::Get()->GetPlayerCount())
		{
			return engine::GameObjectHandle();
		}
		return gPlayerHandles[index];
	}

	// FUNCTION: ENGINE 0x104CB910
	// NONMATCHING: the registers of the master table lookup and of the copy of the hint's value, 97.5 %
#ifdef NONMATCHING
	void FEHudDisguisePerception::SetHint(bool shown)
	{
		bool send = false;
		if (shown == true)
		{
			FlashValue current(hintVisible.value);
			if (!current.value.boolean)
			{
				if (IsShown() == shown)
				{
					GetFrontEndHud()->Unknown104B1D30(8);
					GetFrontEndHud()->Unknown104B1D30(9);
					GetFrontEndHud()->Unknown104B1D30(10);
				}
				send = true;
			}
		}
		else if (shown == false)
		{
			FlashValue current(hintVisible.value);
			if (current.value.boolean == true)
			{
				send = true;
			}
		}
		if (send)
		{
			StartGraceSwitchDisguisesMsg message;
			engine::GameObjectHandle handle = GetPlayerHandle(0);
			engine::GameObject* object = handle.Get();
			if (object != 0)
			{
				object->SendMessage(&message);
			}
		}
		hintVisible.Set(FlashValue(shown));
	}
#endif

	// FUNCTION: ENGINE 0x104CBA70
	void FEHudDisguisePerception::SetLane(int mode, int newDisguise, float amount, bool lane, unsigned char alarmLevel)
	{
		int laneIndex = lane == false;
		if (mode == 0)
		{
			bool hidden = newDisguise == 4 || newDisguise == 5;
			if (hidden != disguiseHidden)
			{
				slots[1].SetMaskVisible(!hidden);
			}
			disguiseHidden = hidden;
		}
		Slot& slot = slots[laneIndex];
		slot.SetBlown(amount, lane, alarmLevel);
		slot.SetDisguise(newDisguise);
		SetHint(CanShowHint());
	}
}
