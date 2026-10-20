// The action of the health track (unit 0x108BA600 - 0x108BA930, no assert path; file name guessed). The track is in healthtrack.cpp.
#include "code/engine/fight/healthactions.h"

namespace engine
{
	// FUNCTION: ENGINE 0x108BA690
	HealthAction::HealthAction(HealthTrack* newTrack, GameObjectHandle newTarget)
		: fight::Action(0x200), target(newTarget), link(newTrack)
	{
	}

	// FUNCTION: ENGINE 0x108BA600
	HealthAction::~HealthAction()
	{
	}

	// FUNCTION: ENGINE 0x108BA900
	fight::Action* HealthTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		GameObjectHandle handle = GetObjectHandle(owner);
		return new HealthAction(this, handle);
	}

}
