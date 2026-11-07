// proto::AmbientSpawner (RTTI and reflection names; a load object) with the spawners the ambient manager keeps:
// proto::VehicleSpawner and proto::PedestrianSpawner. A spawner holds the template of the objects it makes
// (reflected as templateName) and a name; the pedestrian spawner also names the kind of pedestrian (reflected as
// type). Unit 0x10420710 - 0x10421200 (no assert path; the file name is a guess). The reflected names are original,
// the rest is guessed; only the construction, the reflection and the slots that do not reach the ambient manager
// are reconstructed.
#ifndef PROTO_AI_AMBIENTMANAGER_AMBIENTSPAWNERS_H
#define PROTO_AI_AMBIENTMANAGER_AMBIENTSPAWNERS_H

#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/engine/gameobject/gameobjectspawner.h"
#include "code/proto/ai/ambientmanager/parkedcarcloudmanager.h"

namespace proto
{
	class NPCType;

	class AmbientSpawner : public content::MetaLoadObject
	{
	public:
		// 0x10420940
		AmbientSpawner();
		// 0x10420A60 (the deleting destructor of the base is 0x10420C10)
		virtual ~AmbientSpawner();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 3 (0x10420970): nothing to do
		virtual void Slot3(int unused);
		// vftable slot 4 (0x10420980)
		virtual bool IsReady();
		// vftable slot 6 (0x10420A90): keeps the name
		virtual void SetName(const content::ObjectName& newName);
		// vftable slot 7 (0x10420990)
		virtual bool Slot7(void* argument);
		// vftable slot 8: makes an object of the template (an argument the implementations read as a position)
		virtual void Slot8(void* argument) = 0;

		content::MetaObjectTemplate* templateName;  // +8
		int unknownC;  // +0xC
		content::ObjectName name;  // +0x10
	};

	class VehicleSpawner : public AmbientSpawner
	{
	public:
		// 0x10420AA0
		VehicleSpawner();
		// 0x10420B50 (the deleting destructor is 0x10420B60)
		virtual ~VehicleSpawner() {}
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 3 (0x10420810) and 4 (0x10420830): hand the spawner to the ambient manager
		virtual void Slot3(int unused);
		virtual bool IsReady();
		// vftable slot 7 (0x10420850)
		virtual bool Slot7(void* argument);
		// vftable slot 8 (0x10420DD0)
		virtual void Slot8(void* argument);
	};

	// proto::ParkedCarSpawner (RTTI name): makes the parked cars of the cloud of cars around the player; only the class
	// info is reconstructed (its bases are not)
	class ParkedCarSpawner : public CloudSpawnerBase
	{
	public:
		static content::ClassInfo* GetClassInfo();
	};

	class PedestrianSpawner : public AmbientSpawner
	{
	public:
		// 0x10420AC0
		PedestrianSpawner();
		// 0x10420AE0 (the deleting destructor is 0x10420C40)
		virtual ~PedestrianSpawner();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 3 (0x10420860) and 4 (0x10420880): hand the spawner to the ambient manager
		virtual void Slot3(int unused);
		virtual bool IsReady();
		// vftable slot 7 (0x104208A0)
		virtual bool Slot7(void* argument);
		// vftable slot 8 (0x10420EA0)
		virtual void Slot8(void* argument);

		NPCType* type;  // +0x18
		int unknown1C;  // +0x1C
	};
}

#endif
