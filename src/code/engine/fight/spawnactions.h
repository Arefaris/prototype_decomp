// The actions of the light, teleport and spawn object tracks (unit 0x108F2C10 - 0x108F4550, no assert path; file name
// guessed). The tracks are in spawntracks.cpp.
#ifndef ENGINE_FIGHT_SPAWNACTIONS_H
#define ENGINE_FIGHT_SPAWNACTIONS_H

#include "code/core/linklist.h"
#include "code/engine/fight/effecttrack.h"
#include "code/engine/fight/spawntracks.h"
#include "code/engine/lightmessages.h"
#include "code/engine/physics/physicsmessages.h"

namespace engine
{
	// RTTI: engine::LightAction (9 vftable slots, size 0xBC): blends the light of an object from the properties it has
	// to the ones of its track
	class LightAction : public fight::Action
	{
	public:
		// 0x108F3060
		explicit LightAction(LightTrack* newTrack);
		// 0x108F2F60 (deleting destructor 0x108F30D0)
		virtual ~LightAction();

		// vftable slot 5 (0x108F30F0), slot 6 (0x108F2F90) and slot 7 (0x108F31D0)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();
		virtual bool Slot7(int arg, float value);

		core::Link<LightTrack> link;  // +0x1C
		GameObjectHandle target;  // +0x28
		GetLightPropertiesMessage start;  // +0x2C: the properties the light had when the action began
		float elapsed;  // +0xB8
	};

	// RTTI: engine::SpawnObjectAction (9 vftable slots, size 0x3C): creates an object and keeps its collision off
	// against the spawner for a while
	class SpawnObjectAction : public fight::Action
	{
	public:
		// 0x108F3F40
		SpawnObjectAction(SpawnObjectTrack* newTrack, GameObjectHandle newOwner);
		// 0x108F3DD0 (deleting destructor 0x108F3FB0)
		virtual ~SpawnObjectAction();

		// vftable slot 5 (0x108F3FD0), slot 6 (0x108F4380) and slot 7 (0x108F4310)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();
		virtual bool Slot7(int arg, float value);

		// 0x108F3E00: gives the spawned object its collision with the spawner back and wakes it up
		void RestoreCollision();

		core::Link<SpawnObjectTrack> link;  // +0x1C
		GameObjectHandle owner;  // +0x28
		GameObjectHandle spawned;  // +0x2C
		unsigned int intersectionMask;  // +0x30
		bool collisionChanged;  // +0x34
		float elapsed;  // +0x38
	};

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
