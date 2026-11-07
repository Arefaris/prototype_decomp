// proto::EncounterSpawnerBehaviour (RTTI and reflection names; base proto::SpawnerBehaviour) and its derivations
// proto::CloudEncounterSpawnerBehaviour and proto::MobileSpawnerBehaviour: a spawner that makes a group of objects
// (a squad) from its template, between a minimum and a maximum alive at a time, up to a total, with a delay between
// the spawns and locators that expire. Reflected: min, max, total, delay, locatorExpiry, ignoreCamera,
// ignoreCameraCheckDistance, readyToSpawn (the cloud spawner: minGroupSize, maxGroupSize,
// timeSlicedWithDeferredSquadMessages). Units 0x10552860 - 0x10555BA0 (cloud), 0x10556B00 - 0x10559900 (encounter) and
// 0x10559900 - 0x10559CC0 (mobile); no assert path names them, the file names are guesses. The reflected names are
// original, the rest is guessed.
#ifndef PROTO_BEHAVIOURS_ENCOUNTERSPAWNERBEHAVIOUR_H
#define PROTO_BEHAVIOURS_ENCOUNTERSPAWNERBEHAVIOUR_H

#include "code/proto/behaviours/spawnerbehaviour.h"

namespace proto
{
	class EncounterSpawnerBehaviour : public SpawnerBehaviour
	{
	public:
		// 0x105593D0
		explicit EncounterSpawnerBehaviour(engine::GameObject* newOwner);
		// 0x10559550 is the deleting destructor of the derivations' base; this class has none of its own body
		virtual ~EncounterSpawnerBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x10556C80)
		virtual void Slot1();
		// vftable slot 4 (0x10557CE0)
		virtual void Update(float dt, unsigned short mask);
		// vftable slot 6 (0x10558F80)
		virtual void OnMessage(engine::Message* message);
		// vftable slot 8 (0x10558570)
		virtual bool Slot8(engine::GameObjectHandle spawnedObject, engine::GameObjectHandle holder, int index, int value);
		// vftable slots 9 and 10 (0x10557200, 0x10559580)
		virtual void Slot9();
		virtual void Slot10();
		// vftable slot 11 (0x10558920): nothing to do
		virtual void Slot11();
		// vftable slot 12 (0x10558B30): forgets the spawned objects
		virtual void Slot12();
		// vftable slots 13 - 15 (0x10558A70, 0x10558A70, 0x10556CD0)
		virtual engine::GameObjectHandle Slot13();
		virtual bool Slot14(engine::GameObjectHandle squad);
		virtual void Slot15(engine::GameObjectHandle* squad, int value);

		unsigned int min;  // +0x278
		unsigned int max;  // +0x27C
		unsigned int total;  // +0x280
		float delay;  // +0x284
		float locatorExpiry;  // +0x288
		float ignoreCameraCheckDistance;  // +0x28C
		bool unknown290;
		bool ignoreCamera;  // +0x291
		bool unknown292;
		bool unknown293;
		unsigned char unknown294[0x2d4 - 0x294];
		container::ArrayFixed<engine::GameObjectHandle, 30> unknown2D4;  // +0x2D4
		container::ArrayFixed<SpawnedEntry, 30> unknown350;  // +0x350
		container::ArrayFixed<core::Name<core::CaseSensitiveKey>, 5> unknown444;  // +0x444
		bool unknown470;
		bool readyToSpawn;  // +0x471
		bool allZeroHealthSent;  // +0x472
		bool finishedSent;  // +0x473
		int unknown474;
		float unknown478;
		engine::GameObjectHandle unknown47C;  // +0x47C
	};

	// The ObjectSpawnedSpawnMessage (id 9) is declared in proto/fightitems/ai/aicodemessages.h
	struct ObjectSpawnedSpawnMessage;

	class MobileSpawnerBehaviour : public EncounterSpawnerBehaviour
	{
	public:
		// 0x10559AC0
		explicit MobileSpawnerBehaviour(engine::GameObject* newOwner);
		// 0x10559940 is the deleting destructor's body: the vftable store and a jump to the base destructor
		virtual ~MobileSpawnerBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x10559950)
		virtual void Slot1();
		// vftable slot 4 (0x105599A0)
		virtual void Update(float dt, unsigned short mask);
		// vftable slot 6 (0x10559B70)
		virtual void OnMessage(engine::Message* message);
		// vftable slots 9, 10 and 12 (0x10559AA0, 0x10559AB0, 0x10559A90): the encounter spawner's
		virtual void Slot9();
		virtual void Slot10();
		virtual void Slot12();

		// 0x105599F0
		void OnObjectSpawned(ObjectSpawnedSpawnMessage* message);

		int unknown480;  // +0x480
		int unknown484;  // padding: the class is 8-byte aligned in the engine (0x488 bytes)
	};

	class CloudEncounterSpawnerBehaviour : public EncounterSpawnerBehaviour
	{
	public:
		// 0x10555390
		explicit CloudEncounterSpawnerBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown480[0x4f4 - 0x480];
		float unknown4F4;
		bool unknown4F8;
		unsigned int minGroupSize;  // +0x4FC
		unsigned int maxGroupSize;  // +0x500
		bool unknown504;
		bool timeSlicedWithDeferredSquadMessages;  // +0x505
		int unknown508;
		engine::GameObjectHandle unknown50C;
		unsigned char unknown510[0x528 - 0x510];
	};
}

#endif
