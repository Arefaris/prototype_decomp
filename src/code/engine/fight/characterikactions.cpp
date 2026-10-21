// The actions of the character inverse kinematics and jump tracks (the code sits in 0x10930870 - 0x10931980, no assert
// path; file name guessed). The tracks are in characterik.cpp.
#include "code/engine/fight/characterikactions.h"
#include "code/engine/physics/supportinglimbmessages.h"

namespace engine
{
	// FUNCTION: ENGINE 0x109311D0
	CharacterEnableLimbIKAction::CharacterEnableLimbIKAction(CharacterEnableLimbIKTrack* newTrack, GameObjectHandle newTarget)
		: fight::Action(0xE00), link(newTrack), target(newTarget), previousEnabled(false)
	{
	}

	// FUNCTION: ENGINE 0x10930D70
	CharacterEnableLimbIKAction::~CharacterEnableLimbIKAction()
	{
	}

	// FUNCTION: ENGINE 0x10930980
	bool CharacterEnableLimbIKAction::Slot7(int arg, float value)
	{
		return true;
	}

	// FUNCTION: ENGINE 0x10931240
	bool CharacterEnableLimbIKAction::Slot5(int arg, float value)
	{
		if (link.object == 0)
		{
			return false;
		}
		GameObject* object = target.Get();
		if (object == 0)
		{
			return false;
		}
		GetLimbIKEnabledMessage query;
		object->PostMessage(&query);
		previousEnabled = query.enabled;
		switch (link.object->actionOnBegin)
		{
		case 1:
		{
			SetLimbIKEnabledMessage message(true);
			object->SendMessage(&message);
			break;
		}
		case 2:
		{
			SetLimbIKEnabledMessage message(false);
			object->SendMessage(&message);
			break;
		}
		}
		return true;
	}

	// FUNCTION: ENGINE 0x10931320
	void CharacterEnableLimbIKAction::Slot6()
	{
		CharacterEnableLimbIKTrack* track = link.object;
		if (track != 0)
		{
			GameObject* object = target.Get();
			if (object != 0)
			{
				switch (track->actionOnEnd)
				{
				case 0:
				{
					SetLimbIKEnabledMessage message(previousEnabled);
					object->SendMessage(&message);
					break;
				}
				case 1:
				{
					SetLimbIKEnabledMessage message(true);
					object->SendMessage(&message);
					break;
				}
				case 2:
				{
					SetLimbIKEnabledMessage message(false);
					object->SendMessage(&message);
					break;
				}
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x109313F0
	fight::Action* CharacterEnableLimbIKTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		GameObjectHandle handle = GetObjectHandle(owner);
		return new CharacterEnableLimbIKAction(this, handle);
	}
}
