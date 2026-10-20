// The actions of the playback and scenario string tracks (unit 0x108A83A0 - 0x108A9100, no assert path; file name guessed). The tracks are in trackfactory.cpp and scenariotracks.cpp.
#include "code/engine/fight/playbackactions.h"

namespace engine
{
	// FUNCTION: ENGINE 0x108A8430
	PlaybackAction::PlaybackAction(PlaybackTrack* newTrack, core::IRefCount* owner, GameObjectHandle newTarget)
		: fight::Action(0x200), target(newTarget), link(newTrack), unknown2c(0)
	{
		AssignEffectRef(unknown2c, owner);
	}

	// FUNCTION: ENGINE 0x108A83A0
	PlaybackAction::~PlaybackAction()
	{
		ReleaseEffectRef(unknown2c);
	}

	// FUNCTION: ENGINE 0x108A8560
	fight::Action* PlaybackTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		GameObjectHandle handle = GetObjectHandle(owner);
		return new PlaybackAction(this, owner, handle);
	}

	// FUNCTION: ENGINE 0x108A8FC0
	ScenarioStringAction::ScenarioStringAction(ScenarioStringTrack* newTrack, GameObjectHandle newTarget)
		: fight::Action(0x200), target(newTarget), link(newTrack)
	{
	}

	// FUNCTION: ENGINE 0x108A8F30
	ScenarioStringAction::~ScenarioStringAction()
	{
	}

	// FUNCTION: ENGINE 0x108A90C0
	fight::Action* ScenarioStringTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		GameObjectHandle handle = GetObjectHandle(owner);
		return new ScenarioStringAction(this, handle);
	}

}
