// proto::WorldTriggers (RTTI and reflection names; a content library object, "water_triggers" in the inventory): the
// list of boxes of the world that act on objects entering them (RTTI struct proto::WorldTrigger, reflected: aabbLow,
// aabbHigh, type) with the enumeration proto::WorldTriggerType. Unit 0x103B4510 - 0x103B6D60 (no assert path; the file
// name is a guess). The reflected names are original, the rest is guessed.
#ifndef PROTO_WORLDTRIGGERS_H
#define PROTO_WORLDTRIGGERS_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/math/vector.h"
#include "code/ravenphysics/context.h"

namespace proto
{
	// proto::WorldTriggerType (reflected values water, exclusion, kill)
	enum WorldTriggerType
	{
		WORLD_TRIGGER_WATER = 0,
		WORLD_TRIGGER_EXCLUSION = 1,
		WORLD_TRIGGER_KILL = 2
	};

	struct WorldTrigger
	{
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// 0x103B6040
		WorldTrigger();
		// 0x103B6260 (the copy that sets the members one after the other)
		WorldTrigger(const WorldTrigger& other)
			: aabbLow(other.aabbLow), aabbHigh(other.aabbHigh), type(other.type), physicsObject(other.physicsObject)
		{
		}
		// 0x103B5FF0
		WorldTrigger& operator=(const WorldTrigger& other)
		{
			aabbHigh.x = other.aabbHigh.x;
			aabbHigh.y = other.aabbHigh.y;
			aabbHigh.z = other.aabbHigh.z;
			aabbLow.x = other.aabbLow.x;
			aabbLow.y = other.aabbLow.y;
			aabbLow.z = other.aabbLow.z;
			type = other.type;
			physicsObject = other.physicsObject;
			return *this;
		}

		math::Vector aabbLow;
		math::Vector aabbHigh;
		WorldTriggerType type;  // +0x18
		ravenphysics::ObjectHandle physicsObject;  // +0x1C (all ones when there is none)
	};

	class WorldTriggers : public content::MetaLoadObject
	{
	public:
		typedef container::ArrayDynamic<WorldTrigger, container::AllocatorNew> TriggerArray;

		// 0x103B6870
		WorldTriggers();
		// 0x103B68A0 (deleting destructor 0x103B6A00): puts the triggers' physics objects to sleep and destroys them
		virtual ~WorldTriggers();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		TriggerArray triggerList;  // +8
		int unknown14;
	};
}

#endif
