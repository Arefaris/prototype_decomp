// proto::AutoTargetPriorityList (RTTI and reflection names; a load object) with its element class
// proto::AutoTargetPriorityList::TargetClassPriority and the enumeration proto::TargetClass: how important each class of
// target is to the automatic and the lock-on targeting, and how far it can be targeted. The list keeps one entry per
// target class and the entries of the priorities array replace the ones of their class; a list may take over another one
// (referenceAutoTargetPriorityList). Unit 0x102B4740 - 0x102B5820 (no assert path; the file name is a guess). The reflected
// names are original, the rest is guessed.
#ifndef PROTO_AUTOTARGETPRIORITYLIST_H
#define PROTO_AUTOTARGETPRIORITYLIST_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/engine/gameobject/gameobjecthandle.h"

namespace proto
{
	// RTTI proto::TargetClass; the names are the reflected ones
	enum TargetClass
	{
		TARGET_CLASS_NONE = 0,
		TARGET_CLASS_PLAYER = 1,
		TARGET_CLASS_DEAD = 2,
		TARGET_CLASS_PROP = 3,
		TARGET_CLASS_VEHICLE = 4,
		TARGET_CLASS_PEDESTRIAN = 5,
		TARGET_CLASS_FIREARM = 6,
		TARGET_CLASS_ALERT = 7,
		TARGET_CLASS_UNMANNED_VEHICLE = 8,
		TARGET_CLASS_GROUND_SPIKE = 9,
		TARGET_CLASS_PROTECT = 10,
		TARGET_CLASS_CIVILIAN_WOI = 11,
		TARGET_CLASS_THROWN_OBJECT = 12,
		TARGET_CLASS_TANK = 13,
		TARGET_CLASS_GUNSHIP = 14,
		TARGET_CLASS_TRANSPORT_HELI = 15,
		TARGET_CLASS_COP = 16,
		TARGET_CLASS_COP_CAR = 17,
		TARGET_CLASS_RIFLE_SOLDIER = 18,
		TARGET_CLASS_MISSILE_SOLDIER = 19,
		TARGET_CLASS_COMMANDER = 20,
		TARGET_CLASS_JET = 21,
		TARGET_CLASS_UAV = 22,
		TARGET_CLASS_SNIFFER = 23,
		TARGET_CLASS_SUPERSOLDIER = 24,
		TARGET_CLASS_GUN_TURRET = 25,
		TARGET_CLASS_MILITARY_BASE = 26,
		TARGET_CLASS_MILITARY_BASE_HIGH_PRIORITY = 27,
		TARGET_CLASS_MILITARY_SPAWNER = 28,
		TARGET_CLASS_BLOODTOX_BLOWER = 29,
		TARGET_CLASS_INFECTED_WATER_TOWER_DORMANT = 30,
		TARGET_CLASS_INFECTED_WATER_TOWER_ACTIVE = 31,
		TARGET_CLASS_BRAWLER = 32,
		TARGET_CLASS_LEADER = 33,
		TARGET_CLASS_INFECTED1 = 34,
		TARGET_CLASS_INFECTED2 = 35,
		TARGET_CLASS_HYDRA = 36,
		TARGET_CLASS_HIVE = 37,
		TARGET_CLASS_HIVE_HIGH_PRIORITY = 38,
		TARGET_CLASS_INFECTED_SPAWNER = 39,
		TARGET_CLASS_BOSS = 40,
		TARGET_CLASS_DIVERSION = 41,
		TARGET_CLASS_MARKER_DESTROY = 42,
		TARGET_CLASS_MARKER_CONSUME = 43,
		TARGET_CLASS_MARKER_WOI = 44,
		TARGET_CLASS_MARKER_RADIO = 45,
		TARGET_CLASS_MARKER_CONSUME_NOW = 46,
		TARGET_CLASS_AUTO_MIN = 47,
		TARGET_CLASS_AUTO_MAX = 48,
		TARGET_CLASS_AUTO_GRAB_MIN = 49,
		TARGET_CLASS_AUTO_GRAB_MAX = 50,
		TARGET_CLASS_AUTO_GROUND_RANGED = 51,
		TARGET_CLASS_AUTO_AIR_RANGED = 52,
		TARGET_CLASS_AUTO_AIR_RANGED_MAX = 53
	};

	enum
	{
		TARGET_CLASS_COUNT = 0x36
	};

	// One entry of the list (RTTI proto::AutoTargetPriorityList::TargetClassPriority; 0x18 bytes)
	struct TargetClassPriority
	{
		// 0x102B4800
		TargetClassPriority();

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned int targetClass;  // +0
		unsigned int targetCategory;  // +4
		unsigned int targetPriority;  // +8
		float maxTargetableDistance;  // +0xC
		float maxLockOnTargetableDistance;  // +0x10
		bool isThreat;  // +0x14
		bool lockOnForbidden;  // +0x15
	};
}

namespace container
{
	template<> struct ArrayEraseInline<proto::TargetClassPriority>
	{
		enum
		{
			value = 0
		};
	};
}

namespace content
{
	template<> class ArrayDynamicHelper<container::ArrayDynamic<proto::TargetClassPriority, container::AllocatorNew> >
		: public ArrayDynamicHelperBase
	{
	public:
		typedef container::ArrayDynamic<proto::TargetClassPriority, container::AllocatorNew> A;
		typedef A::Element T;

		virtual int Size(void* array)
		{
			return ((A*)array)->Size();
		}
		virtual void* Get(void* array, int index)
		{
			return ((A*)array)->begin + index;
		}
		virtual void* GetConst(void* array, int index)
		{
			return ((A*)array)->begin + index;
		}
		virtual void Insert(void* array, int index, int unused)
		{
			A* a = (A*)array;
			if (a->Size() >= a->Capacity())
			{
				a->Reserve(a->Size() + 1);
			}
			T* position = a->begin + index;
			static T sDefault;
			a->Insert(position, 1, sDefault);
		}
		virtual void Erase(void* array, int index, int unused)
		{
			A* a = (A*)array;
			a->Erase(a->begin + index);
		}
		virtual int Capacity(void* array)
		{
			return ((A*)array)->Capacity();
		}
		virtual void Expand(void* array, unsigned int count)
		{
			A* a = (A*)array;
			if (a->Capacity() == 0)
			{
				a->Allocate(count);
			}
			else if (count + a->Size() > a->Capacity())
			{
				a->Reserve(count + a->Size());
			}
		}
	};
}

namespace engine
{
	class GameObject;
}

namespace proto
{
	// 0x102B50C0: the target of an object, its automatic target when it has none (name guess)
	engine::GameObjectHandle GetCurrentTarget(engine::GameObject* object);

	class AutoTargetPriorityList : public content::MetaLoadObject
	{
	public:
		typedef container::ArrayDynamic<TargetClassPriority, container::AllocatorNew> PriorityArray;

		// 0x102B5670
		AutoTargetPriorityList();
		// 0x102B56C0 (the deleting destructor is 0x102B57F0)
		virtual ~AutoTargetPriorityList();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// 0x102B4830: the entry of a target class
		TargetClassPriority* GetEntry(int index);

		// vftable slot 5 (0x102B4920): takes over the entries of the referenced list and of the priorities array
		virtual bool Slot5();

		AutoTargetPriorityList* referenceList;  // +8
		PriorityArray priorities;  // +0xC
		int unknown18;  // behind the array: its allocator word
		TargetClassPriority entries[TARGET_CLASS_COUNT];  // +0x1C
	};
}

#endif
