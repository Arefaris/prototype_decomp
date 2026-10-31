// The actions of the playback and scenario string tracks (unit 0x108A83A0 - 0x108A9100, no assert path; file name guessed). The tracks are in trackfactory.cpp and scenariotracks.cpp.
#include "code/engine/fight/playbackactions.h"
#include "code/engine/camera/director.h"
#include "code/engine/scenariomessage.h"
#include "code/engine/gameobject/messagerouter.h"

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

	// 0x1130D43C: set while the game runs its tutorial (0x1082FDD0 reads it; name guess)
	bool IsTutorialActive();

	// 0x11318188: the listeners the scenario string events are sent to (name guess)
	MessageListeners gScenarioStringListeners("scenario", 0);

	// FUNCTION: ENGINE 0x108A9040
	bool ScenarioStringAction::Slot5(int arg, float value)
	{
		if (link.object != 0)
		{
			if (link.object->tutorialOnly && !IsTutorialActive())
			{
				return false;
			}
			StringMessage message(link.object->string);
			if (target.IsValid())
			{
				message.SetHandle(0, target);
			}
			SendMessage(&message, &gScenarioStringListeners);
		}
		return false;
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

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D77C10
// FUNCTION: ENGINE 0x10D8AD50
