// The actions of the playback and scenario string tracks (unit 0x108A83A0 - 0x108A9100, no assert path; file name guessed). The tracks are in trackfactory.cpp and scenariotracks.cpp.
#ifndef ENGINE_FIGHT_PLAYBACKACTIONS_H
#define ENGINE_FIGHT_PLAYBACKACTIONS_H

#include "code/core/linklist.h"
#include "code/engine/fight/trackfactory.h"
#include "code/engine/scenario/scenariotracks.h"
#include "code/engine/fight/effecttrack.h"

namespace engine
{
	// RTTI: engine::PlaybackAction (9 vftable slots, size 0x30)
	class PlaybackAction : public fight::Action
	{
	public:
		// 0x108A8430
		PlaybackAction(PlaybackTrack* newTrack, core::IRefCount* owner, GameObjectHandle newTarget);
		// 0x108A83A0
		virtual ~PlaybackAction();

		// vftable slot 5 (0x108A84C0)
		virtual bool Slot5(int arg, float value);

		GameObjectHandle target;  // +0x1C
		core::Link<PlaybackTrack> link;  // +0x20
		core::IRefCount* unknown2c;  // +0x2C
	};

	// RTTI: engine::ScenarioStringAction (9 vftable slots, size 0x2C)
	class ScenarioStringAction : public fight::Action
	{
	public:
		// 0x108A8FC0
		ScenarioStringAction(ScenarioStringTrack* newTrack, GameObjectHandle newTarget);
		// 0x108A8F30
		virtual ~ScenarioStringAction();

		// vftable slot 5 (0x108A9040)
		virtual bool Slot5(int arg, float value);

		GameObjectHandle target;  // +0x1C
		core::Link<ScenarioStringTrack> link;  // +0x20
	};

}

#endif
