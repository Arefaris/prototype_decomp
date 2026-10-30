// The actions of the light, teleport and spawn object tracks (unit 0x108F2C10 - 0x108F4550, no assert path; file name
// guessed). The tracks are in spawntracks.cpp.
#ifndef ENGINE_FIGHT_SPAWNACTIONS_H
#define ENGINE_FIGHT_SPAWNACTIONS_H

#include "code/core/linklist.h"
#include "code/engine/fight/effecttrack.h"
#include "code/engine/fight/spawntracks.h"

namespace engine
{
	// RTTI: engine::TeleportAction (9 vftable slots, size 0x70): puts an object at a place relative to another one
	class TeleportAction : public fight::Action
	{
	public:
		// 0x108F3400
		TeleportAction(TeleportTrack* newTrack, GameObjectHandle newOwner);

		// vftable slot 5 (0x108F34D0), slot 6 (0x108F3740) and slot 7 (0x108F3310)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();
		virtual bool Slot7(int arg, float value);

		core::Link<TeleportTrack> link;  // +0x1C
		GameObjectHandle target;  // +0x28
		GameObjectHandle owner;  // +0x2C
		math::Matrix savedTransform;  // +0x30
	};
}

#endif
