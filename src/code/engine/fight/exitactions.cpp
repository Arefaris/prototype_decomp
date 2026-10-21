// The action of the exit track (unit 0x108F44B0 - 0x108F4630, no assert path; file name guessed). The track is in
// exittracks.cpp.
#include "code/engine/fight/exitactions.h"

namespace engine
{
	// FUNCTION: ENGINE 0x108F4550
	ExitAction::ExitAction(fight::Track* listener, ExitTrack* newTrack, int newEffect, core::IRefCount* newOwner)
		: fight::Action(0xE00), watch(listener), link(newTrack), effect(newEffect), owner(0)
	{
		AssignEffectRef(owner, newOwner);
	}

	// FUNCTION: ENGINE 0x108F44B0
	ExitAction::~ExitAction()
	{
		ReleaseEffectRef(owner);
	}

	// FUNCTION: ENGINE 0x108F45F0
	bool ExitAction::Slot7(int arg, float value)
	{
		if (link.object != 0)
		{
			int listener = (int)watch.track;
			int object = (int)owner;
			if (!link.object->conditions.Evaluate(listener, effect, object, 0))
			{
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x108B6CE0
	fight::Action* ExitTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		return new ExitAction(listener, this, (int)effect, owner);
	}
}
