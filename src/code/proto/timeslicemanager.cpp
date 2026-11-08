#include "code/proto/timeslicemanager.h"
#include "code/proto/fightitems/motion/motionattachmentmessage.h"
#include "code/proto/fightitems/motion/motionmessages4.h"

namespace proto
{
	// FUNCTION: ENGINE 0x103B1FC0
#pragma auto_inline(off)
	TimeSliceManager::Entry::Entry() : object(0), time(0.0f)
	{
	}
#pragma auto_inline(on)

	// FUNCTION: ENGINE 0x103B2510
	TimeSliceManager::TimeSliceManager() : enabled(true), attached(0)
	{
	}

	// FUNCTION: ENGINE 0x103B2540
	TimeSliceManager::~TimeSliceManager()
	{
	}

	// FUNCTION: ENGINE 0x103B20D0
	bool TimeSliceManager::CanSkipFrames(engine::GameObject* object)
	{
		if (!enabled)
		{
			return false;
		}
		if (object == attached)
		{
			return false;
		}
		for (engine::GameObject** it = held.Begin(); it != held.End(); it++)
		{
			if (object == *it)
			{
				return false;
			}
		}
		for (Entry* it = active.Begin(); it != active.End(); it++)
		{
			if (object == it->object)
			{
				return false;
			}
		}
		return true;
	}

	// FUNCTION: ENGINE 0x103B2210
	// NONMATCHING: the engine tests the element count with sar and enters the loop through a jump (73.3 %)
#ifdef NONMATCHING
	void TimeSliceManager::Update(float timeStep)
	{
		if (active.Size() != 0)
		{
			Entry* it = active.End() - 1;
			while (it != active.Begin())
			{
				float left = it->time - timeStep;
				it->time = left;
				if (left <= 0.0f)
				{
					active.EraseFast(it);
				}
				it--;
			}
		}
	}

#endif

	// FUNCTION: ENGINE 0x103B22A0
	// NONMATCHING: the engine builds the entry in a stack slot through its out-of-line constructor, we drop it (10.3 %)
#ifdef NONMATCHING
	void TimeSliceManager::KeepActive(engine::GameObject* object)
	{
		object->behaviours.SetTimeSliceFrameSkip(0);
		for (Entry* it = active.Begin(); it != active.End(); it++)
		{
			if (it->object == object)
			{
				it->time = 1.0f;
				return;
			}
		}
		if (active.Size() < 256)
		{
			Entry entry;
			entry.time = 1.0f;
			Entry* place = active.AllocateBack();
			if (place != 0)
			{
				place->object = object;
				place->time = entry.time;
			}
		}
	}

#endif

	// FUNCTION: ENGINE 0x103B2390
	void TimeSliceManager::Refresh(engine::GameObject* object)
	{
		attached = 0;
		engine::AttachmentGetAttachmentStateMessage attachment;
		object->PostMessage(&attachment);
		if (attachment.parent != 0)
		{
			engine::GameObject* parent = attachment.parent->Get();
			attached = parent;
			if (parent != 0)
			{
				parent->behaviours.SetTimeSliceFrameSkip(0);
			}
		}
		held.Reset();
		GetGrabSlotsMessage message;
		object->SendMessage(&message);
		if (message.slots != 0)
		{
			for (GrabSlot* slot = message.slots->begin; slot != message.slots->end; slot++)
			{
				engine::GameObject* heldObject = static_cast<engine::GameObjectHandle&>(slot->held).Get();
				if (heldObject != 0)
				{
					engine::GameObject** place = held.AllocateBack();
					if (place != 0)
					{
						*place = heldObject;
					}
					heldObject->behaviours.SetTimeSliceFrameSkip(0);
				}
			}
		}
	}
}
