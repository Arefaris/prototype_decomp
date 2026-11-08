// proto::GrabBehaviour (RTTI name; reflected as "GrabBehaviour"; base engine::Behaviour), its slots (proto::GrabSlot), the
// automatic spawning of the objects held in them (proto::GrabAutoSpawnBehaviour with the entries proto::GrabSpawnListEntry)
// and proto::GrabSelectionBehaviour (base GrabBehaviour), which picks the object a grab reaches for. Unit 0x102C6800 -
// 0x102CBF50 (no assert path; the file name is a guess). The reflected names are original, the rest is guessed; only the
// reflection is reconstructed.
#ifndef PROTO_BEHAVIOURS_GRABBEHAVIOUR_H
#define PROTO_BEHAVIOURS_GRABBEHAVIOUR_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/arrayhelpercount.h"
#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/engine/message.h"
#include "code/math/vector.h"

namespace content
{
	class MetaObjectTemplate;
}

namespace ravenphysics
{
	class IntersectionPropertiesLoader;
}

namespace proto
{
	// 0x10D977EC
	extern const float gTen;

	// A place on the grabber that holds an object (RTTI proto::GrabSlot; reflected: name, temporary, wakeUpPhysics)
	struct GrabSlot
	{
		// 0x102CA0F0
		static content::ClassInfo* GetClassInfo();
		// 0x102CA1F0
		static content::MemberList* GetMembers();

		GrabSlot()
		{
		}

		core::Name<core::CaseSensitiveKey> name;  // +0
		engine::HandleBase held;  // +8
		bool temporary;  // +0xC
		bool wakeUpPhysics;  // +0xD
	};

	// An object spawned into a slot (RTTI proto::GrabSpawnListEntry; 0x60 bytes)
	struct __declspec(align(8)) GrabSpawnListEntry
	{
		// 0x102C68D0
		static content::ClassInfo* GetClassInfo();
		// 0x102C84D0
		static content::MemberList* GetMembers();

		// 0x102C7000
		GrabSpawnListEntry();
		// 0x102C7880
		GrabSpawnListEntry(const GrabSpawnListEntry& other);
		// 0x102C7040 (deleting destructor 0x102C77F0)
		~GrabSpawnListEntry();
		// 0x102C7050
		GrabSpawnListEntry& operator=(const GrabSpawnListEntry& other);

		core::Name<core::CaseSensitiveKey> grabSlot;  // +0
		content::MetaObjectTemplate* spawnTemplate;  // +8
		int unknownC;
		core::Name<core::CaseSensitiveKey> parentJoint;  // +0x10
		math::Vector parentPositionOffset;  // +0x18
		math::Vector parentRotationOffset;  // +0x24
		core::Name<core::CaseSensitiveKey> childJoint;  // +0x30
		math::Vector childPositionOffset;  // +0x38
		math::Vector childRotationOffset;  // +0x44
		core::Name<core::CaseSensitiveKey> initialPlaybackNode;  // +0x50
		bool aICharacter;  // +0x58
		unsigned char unknown59[7];
	};

	class GrabBehaviour : public engine::Behaviour
	{
	public:
		typedef container::ArrayDynamic<GrabSlot, container::AllocatorNew> SlotArray;

		// 0x102C9BB0
		explicit GrabBehaviour(engine::GameObject* newOwner);
		// 0x102C9C40 (the engine's: it lets the held objects go; the deleting destructor is 0x102C9E30)
		virtual ~GrabBehaviour();
		// 0x102C7120: the index of the slot of that name, -1 when there is none
		int FindSlot(const core::Name<core::CaseSensitiveKey>& name);
		// 0x102C7180: what the slot of that name holds (an empty handle when there is none)
		engine::HandleBase GetSlotHandle(const core::Name<core::CaseSensitiveKey>& name);
		// 0x102C80D0: hands a message to every object the slots hold
		void SendToHeld(engine::Message* message);
		// vftable slot 1 (0x102C7110): nothing
		virtual void Slot1()
		{
		}
		// vftable slot 6 (0x102C8840): the messages
		virtual void OnMessage(engine::Message* message);
		// 0x102C6910
		static content::ClassInfo* GetClassInfo();
		// 0x102C8730
		static content::MemberList* GetMembers();

		SlotArray grabSlots;  // +0xC
		int unknown18;
		int unknown1C;
		core::Name<core::CaseSensitiveKey> mountableSlot;  // +0x20
	};

	class GrabAutoSpawnBehaviour : public engine::Behaviour
	{
	public:
		typedef container::ArrayDynamic<GrabSpawnListEntry, container::AllocatorNew> SpawnArray;

		// 0x102C9E60 (the destructor 0x102C9EB0, the deleting destructor 0x102CA0C0)
		explicit GrabAutoSpawnBehaviour(engine::GameObject* newOwner);
		virtual ~GrabAutoSpawnBehaviour();
		// vftable slots 0 (0x102C7350): nothing; 1 (0x102C98E0, a jump to 0x102C8A50): spawns the objects of the list;
		// 6 (0x102C92F0): the messages
		virtual void Slot0()
		{
		}
		virtual void Slot1();
		virtual void OnMessage(engine::Message* message);
		// 0x102C6950
		static content::ClassInfo* GetClassInfo();
		// 0x102C9800
		static content::MemberList* GetMembers();

		SpawnArray autoSpawnList;  // +0xC
		int unknown18;
	};

	class GrabSelectionBehaviour : public GrabBehaviour
	{
	public:
		// 0x102CA4F0
		explicit GrabSelectionBehaviour(engine::GameObject* newOwner);
		// 0x102CA590 (the deleting destructor is 0x102CAA40)
		virtual ~GrabSelectionBehaviour();
		// vftable slot 4 (0x102CA360): the timer runs out, then the behaviour stops being updated
		virtual void Update(float dt, unsigned short mask);
		// 0x102CA3B0: forgets the object picked
		void ClearTarget();
		// 0x102CA310
		static content::ClassInfo* GetClassInfo();
		// 0x102CB320
		static content::MemberList* GetMembers();

		engine::HandleBase unknown28;
		float range;  // +0x2C
		float timer;  // +0x30
		bool unknown34;
		ravenphysics::IntersectionPropertiesLoader* grabbableIntersectionProperties;  // +0x38
		unsigned int allowedNavmeshAreas;  // +0x3C
		math::Vector closeRangeOffset;  // +0x40
		math::Vector longRangeOffset;  // +0x4C
		float minimumMassToGrab;  // +0x58
		int unknown5C;
	};
}

namespace container
{
	template<> struct ArrayEraseInline<proto::GrabSlot>
	{
		enum
		{
			value = 4
		};
	};
	template<> struct ArrayEraseInline<proto::GrabSpawnListEntry>
	{
		enum
		{
			value = 4
		};
	};
}

namespace content
{
	CONTENT_ARRAY_HELPER_COUNT_INSERT(proto::GrabBehaviour::SlotArray);
}

#endif
