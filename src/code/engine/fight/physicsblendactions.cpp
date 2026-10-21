// The actions of the physics blend tracks (the code sits in 0x1092D040 - 0x1092D810, no assert path; file name guessed).
// The tracks are in physicsblend.cpp.
#include "code/engine/fight/physicsblendactions.h"
#include "code/engine/physics/physicsmessages.h"

namespace engine
{
	// FUNCTION: ENGINE 0x1092D420
	PhysicsPoseBlendFactorAction::PhysicsPoseBlendFactorAction(PhysicsPoseBlendFactorTrack* newTrack, GameObjectHandle newTarget)
		: fight::Action(0xE00), link(newTrack), target(newTarget)
	{
	}

	// FUNCTION: ENGINE 0x1092D320
	PhysicsPoseBlendFactorAction::~PhysicsPoseBlendFactorAction()
	{
	}

	// FUNCTION: ENGINE 0x1092D4B0
	// EQUIVALENT: shrink-wrap; the engine saves edi before the handle's table lookup, ours after it (and repeats the epilogue); every other instruction is the engine's
	bool PhysicsPoseBlendFactorAction::Slot5(int arg, float value)
	{
		PhysicsPoseBlendFactorTrack* track = link.object;
		if (track != 0)
		{
			GameObject* object = target.Get();
			if (object != 0)
			{
				float duration = track->Slot10();
				SetPhysicsToPoseBlendFactorMessage message(link.object->targetBlendFactor, duration);
				object->SendMessage(&message);
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1092D6A0
	fight::Action* PhysicsPoseBlendFactorTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		GameObjectHandle handle = GetObjectHandle(owner);
		return new PhysicsPoseBlendFactorAction(this, handle);
	}

	// FUNCTION: ENGINE 0x1092D540
	PhysicsJointBlendFactorAction::PhysicsJointBlendFactorAction(PhysicsJointBlendFactorTrack* newTrack, GameObjectHandle newTarget)
		: fight::Action(0xE00), link(newTrack), target(newTarget)
	{
	}

	// FUNCTION: ENGINE 0x1092D610
	// EQUIVALENT: shrink-wrap; the engine saves edi before the handle's table lookup, ours after it (and repeats the epilogue); every other instruction is the engine's
	bool PhysicsJointBlendFactorAction::Slot5(int arg, float value)
	{
		PhysicsJointBlendFactorTrack* track = link.object;
		if (track != 0)
		{
			GameObject* object = target.Get();
			if (object != 0)
			{
				float duration = track->Slot10();
				SetPhysicsToJointBlendFactorMessage message(link.object->targetBlendFactor, duration, &link.object->jointName);
				object->SendMessage(&message);
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1092D6E0
	fight::Action* PhysicsJointBlendFactorTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		GameObjectHandle handle = GetObjectHandle(owner);
		return new PhysicsJointBlendFactorAction(this, handle);
	}
}
