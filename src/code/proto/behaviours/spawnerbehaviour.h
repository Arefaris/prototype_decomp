// proto::SpawnerBehaviour (RTTI and reflection names; base engine::Behaviour): the base of the spawners that make game
// objects from templates (EncounterSpawnerBehaviour and its derivations). It keeps the name of the template to
// spawn, the radius and offset to spawn at, a branch of the fight tree to play on the spawned objects, the weighted
// list of further templates and the list of the objects it spawned. Reflected: templateName, spawnRadius,
// totalSpawned, spawnOffset, branch. Unit 0x10559CC0 - 0x1055B1E0 (no assert path; the file name is a guess). The
// reflected names are original, the rest is guessed.
#ifndef PROTO_BEHAVIOURS_SPAWNERBEHAVIOUR_H
#define PROTO_BEHAVIOURS_SPAWNERBEHAVIOUR_H

#include "code/container/arrayfixed.h"
#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/fight/branch.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/math/vector.h"

namespace proto
{
	// A spawned object and a number kept with it (8 bytes; names guessed)
	struct SpawnedEntry
	{
		engine::GameObjectHandle handle;
		engine::GameObjectHandle unknown4;
	};

	// A template the spawner chooses from and the weight of the choice (16 bytes; names guessed)
	struct WeightedTemplate
	{
		float weight;
		int unknown4;
		core::Name<core::CaseSensitiveKey> name;
	};

	class SpawnerBehaviour : public engine::Behaviour
	{
	public:
		// 0x1055AF80
		explicit SpawnerBehaviour(engine::GameObject* newOwner);
		// 0x1055B060 (the deleting destructor is 0x1055B0E0)
		virtual ~SpawnerBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x10559D00) and 4 (0x10559D10): nothing to do
		virtual void Slot1();
		virtual void Update(float dt, unsigned short mask);
		// vftable slot 6 (0x1055AA60)
		virtual void OnMessage(engine::Message* message);
		// vftable slot 8 (0x1055A430)
		virtual bool Slot8(engine::GameObjectHandle spawnedObject, engine::GameObjectHandle holder, int index, int value);
		virtual void Slot9() = 0;
		virtual void Slot10() = 0;
		// vftable slot 11 (0x1055A820): nothing to do
		virtual void Slot11();

		// 0x1055A620 / 0x1055A6E0: drops the spawned objects that are gone (or, with the flag, those without health)
		// and answers how many are left
		int PruneSpawned();
		int PruneSpawnedByHealth(bool removeDead);

		// 0x10559ED0 / 0x10559F10: the branch played on the spawned objects (watched, so that it is released
		// with the tree)
		void SetBranch(fight::Branch* newBranch);
		fight::Branch* GetBranch() const;

		int unknownC;  // padding: the names are 8-byte aligned in the engine
		core::Name<core::CaseSensitiveKey> templateName;  // +0x10
		float spawnRadius;  // +0x18
		math::Vector spawnOffset;  // +0x1C
		fight::BranchWatch branch;  // +0x28
		int unknown34;
		container::ArrayFixed<WeightedTemplate, 10> templates;  // +0x38
		unsigned int totalSpawned;  // +0xDC
		int unknownE0;
		container::ArrayFixed<SpawnedEntry, 50> spawned;  // +0xE4
	};
}

#endif
