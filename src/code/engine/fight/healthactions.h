// The action of the health track (unit 0x108BA600 - 0x108BA930, no assert path; file name guessed). The track is in healthtrack.cpp.
#ifndef ENGINE_FIGHT_HEALTHACTIONS_H
#define ENGINE_FIGHT_HEALTHACTIONS_H

#include "code/core/linklist.h"
#include "code/engine/fight/healthtrack.h"
#include "code/engine/fight/effecttrack.h"

namespace engine
{
	// RTTI: engine::HealthAction (9 vftable slots, size 0x2C)
	class HealthAction : public fight::Action
	{
	public:
		// 0x108BA690
		HealthAction(HealthTrack* newTrack, GameObjectHandle newTarget);
		// 0x108BA600
		virtual ~HealthAction();

		// vftable slot 5 (0x108BA710)
		virtual bool Slot5(int arg, float value);

		GameObjectHandle target;  // +0x1C
		core::Link<HealthTrack> link;  // +0x20
	};

}

#endif
