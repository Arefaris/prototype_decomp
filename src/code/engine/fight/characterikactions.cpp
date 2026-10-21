// The actions of the character inverse kinematics and jump tracks (the code sits in 0x10930870 - 0x10931980, no assert
// path; file name guessed). The tracks are in characterik.cpp.
#include "code/engine/fight/characterikactions.h"
#include "code/engine/fight/driverrefs.h"
#include "code/engine/physics/supportinglimbmessages.h"

namespace engine
{
	extern content::ObjectName gPuppetAttributeName;
	choreo::Puppet* GetPuppet(GameObject* object);

	// FUNCTION: ENGINE 0x10930E60
	CharacterIKAction::CharacterIKAction(CharacterIKTrack* newTrack, GameObjectHandle newTarget)
		: fight::Action(0xE00), link(newTrack), target(newTarget), driver(0), disabledLimbIK(false)
	{
	}

	// FUNCTION: ENGINE 0x10930CC0
	CharacterIKAction::~CharacterIKAction()
	{
		ReleaseDriverRef(driver);
	}

	// FUNCTION: ENGINE 0x10930970
	bool CharacterIKAction::Slot7(int arg, float value)
	{
		return true;
	}

	// FUNCTION: ENGINE 0x10930CF0
	void CharacterIKAction::SetLimbIKEnabled(bool enabled)
	{
		SetLimbIKEnabledMessage message(enabled);
		target.Get()->SendMessage(&message);
	}

	// FUNCTION: ENGINE 0x10931150
	void CharacterIKAction::Slot6()
	{
		GameObject* object = target.Get();
		if (object != 0)
		{
			if (disabledLimbIK)
			{
				SetLimbIKEnabled(false);
			}
			Attribute<choreo::Puppet*>* attribute = (Attribute<choreo::Puppet*>*)object->FindAttribute(gPuppetAttributeName);
			if (attribute != 0)
			{
				choreo::Puppet** value = &attribute->value;
				if (value != 0 && *value != 0 && driver != 0)
				{
					(*value)->SetEndlessLifetime(driver, false, -1.0f);
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x109313B0
	fight::Action* CharacterIKTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		GameObjectHandle handle = GetObjectHandle(owner);
		return new CharacterIKAction(this, handle);
	}

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

	// FUNCTION: ENGINE 0x10931640
	CharacterJumpAction::CharacterJumpAction(CharacterJumpTrack* newTrack, GameObjectHandle newTarget)
		: fight::Action(0xE00), link(newTrack), target(newTarget), driver(0), velocity(0.0f, 0.0f, 0.0f), landed(false)
	{
	}

	// FUNCTION: ENGINE 0x10931550
	CharacterJumpAction::~CharacterJumpAction()
	{
		ReleaseDriverRef(driver);
	}

	// FUNCTION: ENGINE 0x10931580
	void CharacterJumpAction::Slot6()
	{
		GameObject* object = target.Get();
		if (object != 0)
		{
			choreo::Puppet* puppet = GetPuppet(object);
			if (puppet != 0 && driver != 0)
			{
				puppet->SetEndlessLifetime(driver, false, -1.0f);
				ReleaseDriverRef(driver);
			}
		}
	}

	// FUNCTION: ENGINE 0x10931980
	fight::Action* CharacterJumpTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		GameObjectHandle handle = GetObjectHandle(owner);
		return new CharacterJumpAction(this, handle);
	}
}
