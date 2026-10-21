// The actions of the attach and detach tracks (unit 0x108F0370 - 0x108F0C00, no assert path; file name guessed). The
// tracks are in nistracks.cpp.
#include "code/engine/fight/attachactions.h"

namespace engine
{
	namespace animation
	{
		// FUNCTION: ENGINE 0x108F0580
		AttachObjectAction::AttachObjectAction(AttachObjectTrack* newTrack, GameObjectHandle newTarget)
			: fight::Action(0xE00), link(newTrack), target(newTarget)
		{
		}

		// FUNCTION: ENGINE 0x108F0370
		AttachObjectAction::~AttachObjectAction()
		{
		}

		// FUNCTION: ENGINE 0x108F0830
		fight::Action* AttachObjectTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
		{
			GameObjectHandle handle = GetObjectHandle(owner);
			return new AttachObjectAction(this, handle);
		}

		// FUNCTION: ENGINE 0x108F0610
		DetachObjectAction::DetachObjectAction(DetachObjectTrack* newTrack, GameObjectHandle newTarget)
			: fight::Action(0xE00), link(newTrack), target(newTarget)
		{
		}

		// FUNCTION: ENGINE 0x108F0400
		DetachObjectAction::~DetachObjectAction()
		{
		}

		// FUNCTION: ENGINE 0x108F06A0
		// EQUIVALENT: the engine adds the name's offset after pushing the flag, ours before loading the vftable slot (one instruction
		// moved); every other instruction is the engine's
		bool DetachObjectAction::Slot5(int arg, float value)
		{
			if (link.object != 0)
			{
				GameObject* object = content::gRootInventory->Find<GameObject>(link.object->objectToDetach);
				if (object != 0)
				{
					IntrusiveMessage message(0xf, 1);
					object->SendMessage(&message);
				}
			}
			return false;
		}

		// FUNCTION: ENGINE 0x108F0870
		fight::Action* DetachObjectTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
		{
			GameObjectHandle handle = GetObjectHandle(owner);
			return new DetachObjectAction(this, handle);
		}

		// FUNCTION: ENGINE 0x108F0700
		DetachFromParentAction::DetachFromParentAction(DetachFromParentTrack* newTrack, GameObjectHandle newTarget)
			: fight::Action(0xE00), link(newTrack), target(newTarget)
		{
		}

		// FUNCTION: ENGINE 0x108F0440
		DetachFromParentAction::~DetachFromParentAction()
		{
		}

		// FUNCTION: ENGINE 0x108F0790
		bool DetachFromParentAction::Slot5(int arg, float value)
		{
			if (link.object != 0 && target.IsValid())
			{
				IntrusiveMessage message(0xf, 1);
				target.Get()->SendMessage(&message);
			}
			return false;
		}

		// FUNCTION: ENGINE 0x108F08B0
		fight::Action* DetachFromParentTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
		{
			GameObjectHandle handle = GetObjectHandle(owner);
			return new DetachFromParentAction(this, handle);
		}
	}
}
