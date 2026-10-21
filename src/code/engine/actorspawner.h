// engine::ActorSpawner and engine::ActorCrowdSpawner (RTTI and reflection names): game object spawners that place
// one actor of a player (the controller table decides when it may spawn) or a grid of actors named after a base name.
// Both derive from engine::GameObjectSpawner. Unit 0x10905BC0 - 0x109067F0 (no assert path; the file name is a
// guess). The reflected member names are original; the rest is guessed.
#ifndef ENGINE_ACTORSPAWNER_H
#define ENGINE_ACTORSPAWNER_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/container/arraydynamicstatic.h"
#include "code/container/string.h"
#include "code/content/metatype.h"
#include "code/content/stringmetatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/engine/gameobject/gameobjectspawner.h"
#include "code/engine/surfacedefinition.h"
#include "code/math/matrix.h"

namespace engine
{
	class ActorSpawner : public GameObjectSpawner
	{
	public:
		// 0x10905DE0
		ActorSpawner();
		// 0x10906270 (deleting destructor 0x109066B0)
		virtual ~ActorSpawner();

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 3 (0x10905C60): once loaded, spawns the actor and keeps its handle
		virtual void Slot3(int unused);
		// vftable slot 4 (0x109062B0): while the actor's object lives it is switched off and its handle dropped
		virtual bool IsReady();
		// vftable slot 5 (0x10905C40): false while the player's controller slot is taken by nobody
		virtual bool Slot5();
		// vftable slot 10 (0x10906330): spawns the actor under the object name in inventory and makes it the point of
		// interest of its player
		virtual GameObjectHandle SpawnActor(content::LoadInventory* inventory);

		int unknown4C;
		core::Name<core::CaseSensitiveKey> objectName;  // +0x50
		int playerIndex;  // +0x58
		GameObjectHandle handle;  // +0x5C
	};

	class ActorCrowdSpawner : public GameObjectSpawner
	{
	public:
		typedef container::ArrayDynamic<GameObjectHandle, container::AllocatorNew> HandleArray;

		// 0x109066D0
		ActorCrowdSpawner();
		// 0x10906740 (deleting destructor 0x109067C0)
		virtual ~ActorCrowdSpawner();

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 3 (0x10905C80): spawns the grid
		virtual void Slot3(int unused);
		// vftable slot 4 (0x109063C0): while the crowd's objects live they are switched off and their handles dropped
		virtual bool IsReady();
		// vftable slot 10 (0x10906450): makes numAlongX times numAlongZ objects named "<baseName>_<x>_<z>", a grid
		// spacing apart from baseTransform, and keeps their handles
		virtual void SpawnGrid(content::LoadInventory* inventory);

		// 0x10905C90: both counts are below 100
		bool IsGridSizeValid() const;

		container::StringC<32> baseName;  // +0x4C
		math::Matrix baseTransform;  // +0x70
		unsigned int numAlongX;  // +0xB0
		unsigned int numAlongZ;  // +0xB4
		float gridSpacingX;  // +0xB8
		float gridSpacingZ;  // +0xBC
		HandleArray handles;  // +0xC0
		int unknownCC;  // the object is 0xD0 bytes (nothing reads or writes the word)
	};
}

#endif
