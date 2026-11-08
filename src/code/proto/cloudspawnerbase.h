// proto::CloudSpawnerBase (RTTI and reflection names; base engine::PropSpawner): the spawner of the things the cloud
// manager keeps around the player (the parked cars, the effects props). It makes its object when the manager asks
// and fades it in and out. Reflected: the priority, the tags, the decay state and whether the spawner is active.
// proto::CloudSpawner (RTTI name) is the plain spawner. Unit 0x104F04B0 - 0x104F3420 (no assert path; the file name
// is a guess). The reflected names are original, the rest is guessed.
#ifndef PROTO_CLOUDSPAWNERBASE_H
#define PROTO_CLOUDSPAWNERBASE_H

#include "code/container/arrayfixed.h"
#include "code/container/arraydynamicallocatornew.h"
#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/nis/nis.h"
#include "code/engine/propspawner.h"
#include "code/engine/gameobject/statepackmessages.h"
#include "code/proto/citymanager.h"

namespace proto
{
	// The parts of the state a spawner holds for its object (CloudSpawnerBase::parts, CloudSpawnState::parts)
	enum
	{
		PART_TREE_NAMES = 1,
		PART_HEALTH = 2,
		PART_GENERIC_BYTE = 4
	};

	// The names of the states of the playback trees of a prop and the flag kept with them (the spawner keeps them while
	// its object is away; copied as a whole)
	struct TreeState
	{
		engine::TreeNameList names;  // +0
		unsigned char broadcast;  // +0x1C
	};

	// A float member that is copied like a word
	struct StoredFloat
	{
		float value;
	};

	// The state of a cloud spawner and of the object it made, as the cloud manager keeps it while the object is away
	// (0x70 bytes; the member names are guesses)
	struct CloudSpawnState
	{
		core::Name<core::CaseSensitiveKey> name;  // +0
		engine::NISTransform transform;  // +8
		TreeState trees;  // +0x48
		StoredFloat health;  // +0x68
		unsigned char genericByte;  // +0x6C
		unsigned char startPriority : 4;  // +0x6D
		unsigned char pending : 1;
		unsigned char parts : 3;  // which parts of the state are held (PART_*)
		unsigned char unknown6E : 1;  // +0x6E
	};

	class CloudSpawnerBase : public engine::PropSpawner
	{
	public:
		// RTTI proto::CloudSpawnerBase::Priority (the values are the reflected ones)
		enum Priority
		{
			PRIORITY_FORCE_ACTIVE = 0,
			PRIORITY_FORCE_ACTIVE_FAR = 1,
			PRIORITY_FORCE_ACTIVE_NEAR = 2,
			PRIORITY_FORCE_ACTIVE_FAR_CAMERA = 3,
			PRIORITY_FORCE_ACTIVE_NEAR_CAMERA = 4,
			PRIORITY_FORCE_ACTIVE_CAMERA = 5,
			PRIORITY_NORMAL = 6,
			PRIORITY_NORMAL_IGNORE_CAMERA = 7,
			PRIORITY_LOW = 8,
			PRIORITY_VERY_LOW = 9,
			PRIORITY_ULTRA_LOW = 10
		};

		// RTTI proto::CloudSpawnerBase::TagWrapper (struct, 8 bytes): one tag name
		struct TagWrapper
		{
			// 0x104F0610 is the class info of the wrapper; its members 0x104F0A30
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			core::Name<core::CaseSensitiveKey> name;  // +0
		};

		typedef container::ArrayDynamic<TagWrapper, container::AllocatorNew> TagArray;

		// 0x104F3310 (the destructor body is 0x104F2F50, the deleting destructor 0x104F33F0)
		CloudSpawnerBase();
		virtual ~CloudSpawnerBase();

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// The four reflected properties (priority and decay state also keep the value the spawner starts with)
		Priority GetPriority() const;
		void SetPriority(Priority newPriority);
		CityManager::DecayState GetDecayState() const;
		void SetDecayState(CityManager::DecayState newState);
		bool GetSpawnActive() const;
		void SetSpawnActive(bool active);

		// 0x104F1DC0 (another unit): decides whether this spawner may make or drop its object. It answers in the three
		// bytes of its last argument (may create, may recycle, may remove) and takes the manager, the two positions,
		// a four-float record, a flag word, the "paused" byte and that answer (`ret 0x28`).
		void Rank(void* context, const float* position, const float* other, float distance, float nearDistance,
			float farDistance, float margin, unsigned int flags, unsigned char pausedByte, unsigned char* answer);

		// The vftable slots the spawners of the cloud override: 3, 4 and 7 are the PropSpawner's, left pure here
		virtual void Slot3(int inventory) = 0;
		virtual bool IsReady() = 0;
		// Slot 5 (0x104F06D0)
		virtual bool Slot5();
		virtual engine::GameObject* CreateObject(const content::ObjectName& objectName,
			content::LoadInventory* inventory) = 0;
		// Slot 13 (0x104F2790) / 14 (0x104F1B30): lowers / raises the fade of the object by amount (scaled by the
		// rate); force skips the hysteresis
		virtual bool FadeOut(float amount, bool force, float rate);
		virtual bool FadeIn(float amount, bool force, float rate);
		// 0x104F06E0 / 0x104F0700: the health the spawner hands the object (-1 when none was set)
		float GetHealth() const;
		void SetHealth(float newHealth);
		// 0x104F0B50 / 0x104F0BA0: whether a tag is in the list, and the first tag that differs from the name
		bool HasTag(const core::Name<core::CaseSensitiveKey>& tag) const;
		const core::Name<core::CaseSensitiveKey>* FindOtherTag(const core::Name<core::CaseSensitiveKey>& tag) const;
		// 0x104F1AA0: tells the object (or keeps for it) whether it broadcasts its state changes
		void SetBroadcastStateChanges(bool broadcast);
		// 0x104F2DC0: takes over a state the manager kept
		void Unpack(const CloudSpawnState* state);
		// 0x104F1C90: takes the state of the object (transform, trees, health) back into the spawner
		void SaveState();
		// Slot 15 (0x104F2AE0): makes the object when it is due and sends it its fade
		virtual bool Slot15(bool force);

		TreeState trees;  // +0x68 (the names end at +0x80)
		StoredFloat health;  // +0x88
		TagArray tags;  // +0x8C
		int unknown98;
		float fade;  // +0x9C
		float sentFade;  // +0xA0
		float unknownA4;
		float unknownA8;
		float unknownAC;
		float unknownB0;
		int unknownB4;
		unsigned char unknownB8;  // +0xB8
		unsigned char priority : 4;  // +0xB9
		unsigned char startPriority : 4;
		unsigned char decayState : 3;  // +0xBA
		unsigned char visible : 1;
		unsigned char hysteresis : 3;
		unsigned char pending : 1;
		unsigned char unknownBB0 : 1;  // +0xBB
		unsigned char spawnActive : 1;
		unsigned char parts : 3;  // which parts of the state are held (PART_*)
		unsigned char unknownBB5 : 1;
		unsigned char unknownBB6 : 1;
		unsigned char unknownBB7 : 1;
	};

}

namespace container
{
	// The engine's Erase of the tag array moves the tail down with the copy that answers the end of the destination,
	// and its Reserve stores the begin pointer first
	template<> struct ArrayEraseInline<proto::CloudSpawnerBase::TagWrapper>
	{
		enum
		{
			value = 4
		};
	};
	template<> struct ArrayReserveBeginFirst<proto::CloudSpawnerBase::TagWrapper>
	{
		enum
		{
			value = 1
		};
	};
}

namespace proto
{
	// RTTI proto::CloudSpawner: the plain cloud spawner; its members are the base class's
	class CloudSpawner : public CloudSpawnerBase
	{
	public:
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	};
}

namespace content
{
	// The element access of the tag array for its meta type. The default element the reflection inserts is kept in a
	// function-local static (Default; this unit keeps the engine's out-of-line copy of it as well)
	// (a partial specialization over the allocator, so that the out-of-line copy can be instantiated explicitly)
	template<class Allocator> class ArrayDynamicHelper<container::ArrayDynamic<proto::CloudSpawnerBase::TagWrapper,
		Allocator> > : public ArrayDynamicHelperBase
	{
	public:
		typedef container::ArrayDynamic<proto::CloudSpawnerBase::TagWrapper, Allocator> A;
		typedef proto::CloudSpawnerBase::TagWrapper T;

		static T& Default()
		{
			static T sDefault;
			return sDefault;
		}

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
			a->Insert(position, Default());
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

#endif
