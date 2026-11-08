// proto::LifetimeManager (RTTI name; vftable 0x10E0BDF0, 4 slots): keeps lists of game objects that are to disappear
// (corpses, props, vehicles) and removes them in turns once a list has grown beyond its limit. The instance is the global
// 0x1126BDF8. Unit 0x10498200 - 0x1049A990 (no assert path; the file name and the member names are guesses). Only what the
// reconstructed members touch is laid out.
#ifndef PROTO_LIFETIMEMANAGER_H
#define PROTO_LIFETIMEMANAGER_H

#include "code/container/arraydynamicnew.h"
#include "code/container/arrayfixed.h"
#include "code/engine/gameobject/gameobjecthandle.h"

namespace proto
{
	// An object and the time it was put on a list
	struct LifetimeEntry
	{
		engine::GameObjectHandle handle;
		int time;
	};

	// A list of entries and the word behind it (the lists are 0x10 bytes apart)
	struct LifetimeList
	{
		container::ArrayDynamicNew<LifetimeEntry> entries;
		int unknown;
	};

	class LifetimeManager
	{
	public:
		// 0x10498E70 / 0x10498EF0
		LifetimeManager();
		virtual ~LifetimeManager();
		// Slot 1 (0x10499E00): allocates the lists; slot 2 (0x1049A950): empties them and ends; slot 3 (0x1049A990): removes
		// what the lists hold beyond their limits (names guessed)
		virtual void Create();
		virtual void Destroy();
		virtual void Update();
		// 0x104988C0: takes an object out of the world, optionally telling the scenario it died (name guess)
		void Unknown104988C0(engine::GameObjectHandle* object, engine::GameObjectHandle* killer, bool unknown, bool sendMessage);

		LifetimeList first[2];  // +0x4, +0x14
		LifetimeList third;  // +0x24
		LifetimeList fourth;  // +0x34
		LifetimeList fifth;  // +0x44
		LifetimeList sixth;  // +0x54
		container::ArrayFixed<engine::GameObjectHandle, 256> pending;  // +0x64
		container::ArrayFixed<engine::GameObjectHandle, 256> removing;  // +0x468
	};

	// The instance (0x1126BDF8)
	extern LifetimeManager* gLifetimeManager;
}

#endif
