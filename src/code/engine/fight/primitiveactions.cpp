// The actions of the primitive visibility, destroy and animation control tracks (unit 0x108EE6B0 - 0x108EF020, no
// assert path; file name guessed). The tracks are in primitivetracks.cpp.
#include "code/engine/fight/primitiveactions.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/primitivemessages.h"

namespace engine
{
	// FUNCTION: ENGINE 0x108EE7F0
	PrimitiveVisibilityAction::PrimitiveVisibilityAction(PrimitiveVisibilityTrack* newTrack, GameObjectHandle newTarget)
		: fight::Action(0xE00), link(newTrack), target(newTarget)
	{
	}

	// FUNCTION: ENGINE 0x108EE880
	PrimitiveVisibilityAction::PrimitiveVisibilityAction(PrimitiveVisibilityTrack* newTrack, fight::Name objectName)
		: fight::Action(0xE00), link(newTrack)
	{
		target = FindGameObject(objectName, *(const content::ObjectName*)"");
	}

	// FUNCTION: ENGINE 0x108EE760
	PrimitiveVisibilityAction::~PrimitiveVisibilityAction()
	{
	}

	// FUNCTION: ENGINE 0x108EE8F0
	// EQUIVALENT: the engine keeps the master table pointer in ebx across both handle lookups, ours loads it again for the second
	// and keeps the name's address in ebx; every other instruction is the engine's
	bool PrimitiveVisibilityAction::Slot5(int arg, float value)
	{
		PrimitiveVisibilityTrack* track = link.object;
		if (track == 0)
		{
			return false;
		}
		if (target.IsValid())
		{
			if (track->primitiveName.IsEmpty())
			{
				SetAllVisibilityMessage message(track->visible);
				target.Get()->SendMessage(&message);
			}
			else
			{
				SetPrimitiveVisibilityMessage message(track->primitiveName, track->visible, true);
				target.Get()->SendMessage(&message);
			}
		}
		return true;
	}

	// FUNCTION: ENGINE 0x108EEA10
	fight::Action* PrimitiveVisibilityTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		GameObjectHandle handle = GetObjectHandle(owner);
		return new PrimitiveVisibilityAction(this, handle);
	}

	// FUNCTION: ENGINE 0x108EEA50
	fight::Action* ExplicitPrimitiveVisibilityTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		return new PrimitiveVisibilityAction(this, object);
	}

	// FUNCTION: ENGINE 0x108EEBC0
	DestroyAction::DestroyAction(DestroyTrack* newTrack, fight::Track* listener, GameObjectHandle newTarget)
		: fight::Action(0xE00), link(newTrack), watch(listener), target(newTarget)
	{
	}

	// FUNCTION: ENGINE 0x108EEB00
	DestroyAction::~DestroyAction()
	{
	}

	// FUNCTION: ENGINE 0x108EEB40
	bool DestroyAction::Slot5(int arg, float value)
	{
		if (target.IsValid())
		{
			target.DeferUpdate(true);
		}
		return false;
	}

	// FUNCTION: ENGINE 0x108EEA90
	bool DestroyAction::Slot7(int arg, float value)
	{
		return false;
	}

	// FUNCTION: ENGINE 0x108EEC60
	fight::Action* DestroyTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		GameObjectHandle handle = GetObjectHandle(owner);
		return new DestroyAction(this, listener, handle);
	}

	// FUNCTION: ENGINE 0x108EEE90
	AnimationControlAction::AnimationControlAction(AnimationControlTrack* newTrack, GameObjectHandle newTarget)
		: fight::Action(0x200), target(newTarget), link(newTrack)
	{
	}

	// FUNCTION: ENGINE 0x108EEE00
	AnimationControlAction::~AnimationControlAction()
	{
	}

	// FUNCTION: ENGINE 0x108EEF10
	// EQUIVALENT: the engine holds the cycle mode in esi (saved around the message) and stores the message fields in order, ours stores
	// it before the message's header; every other instruction is the engine's
	bool AnimationControlAction::Slot5(int arg, float value)
	{
		if (link.object != 0)
		{
			GameObject* object = target.Get();
			if (object != 0)
			{
				int numCycles = link.object->numCycles;
				float relativeSpeed = link.object->relativeSpeed;
				float endFrame = link.object->endFrame;
				float startFrame = link.object->startFrame;
				int cycleMode = link.object->cycleMode;
				AnimationControlMessage message(startFrame, endFrame, relativeSpeed, cycleMode, numCycles);
				object->SendMessage(&message);
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x108EEFB0
	fight::Action* AnimationControlTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		GameObjectHandle handle = GetObjectHandle(owner);
		return new AnimationControlAction(this, handle);
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x108EE860
// FUNCTION: ENGINE 0x108EEC40
// FUNCTION: ENGINE 0x108EECA0
// FUNCTION: ENGINE 0x108EED70
// FUNCTION: ENGINE 0x108EEEF0
// FUNCTION: ENGINE 0x108EE6F0
// FUNCTION: ENGINE 0x108EE710
// FUNCTION: ENGINE 0x108EED90
// FUNCTION: ENGINE 0x108EEDB0
