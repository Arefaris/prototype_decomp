#include "code/engine/gameobject/gameobject.h"
#include "code/engine/primitivemessages.h"
#include "code/proto/fightitems/motion/motionmessages4.h"
#include "code/proto/messages/statemessages.h"

namespace proto
{
	// Helpers that tell an object and the objects it holds the same thing (unit 0x103C0040 - 0x103C5D60, no assert
	// path; the file name is a guess)

	// FUNCTION: ENGINE 0x103C0FC0
	void ActivateRenderingWithHeld(engine::GameObject* object, bool active)
	{
		engine::ActivateRenderingMessage message(active);
		object->SendMessage(&message);
		GetGrabSlotsMessage slotsMessage;
		object->SendMessage(&slotsMessage);
		GrabBehaviour::SlotArray* slots = slotsMessage.slots;
		if (slots != 0)
		{
			for (GrabSlot* slot = slots->Begin(); slot != slots->End(); slot++)
			{
				engine::GameObject* held = ((engine::GameObjectHandle*)&slot->held)->Get();
				if (held != 0)
				{
					held->SendMessage(&message);
					slots = slotsMessage.slots;
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x103C10C0
	void SetAllVisibilityWithHeld(engine::GameObject* object, bool visible)
	{
		engine::SetAllVisibilityMessage message(visible);
		object->SendMessage(&message);
		GetGrabSlotsMessage slotsMessage;
		object->SendMessage(&slotsMessage);
		GrabBehaviour::SlotArray* slots = slotsMessage.slots;
		if (slots != 0)
		{
			for (GrabSlot* slot = slots->Begin(); slot != slots->End(); slot++)
			{
				engine::GameObject* held = ((engine::GameObjectHandle*)&slot->held)->Get();
				if (held != 0)
				{
					held->SendMessage(&message);
					slots = slotsMessage.slots;
				}
			}
		}
	}
}
