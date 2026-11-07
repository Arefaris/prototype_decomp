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

		explicit GrabBehaviour(engine::GameObject* newOwner);
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

		explicit GrabAutoSpawnBehaviour(engine::GameObject* newOwner);
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
		explicit GrabSelectionBehaviour(engine::GameObject* newOwner);
		// 0x102CA310
		static content::ClassInfo* GetClassInfo();
		// 0x102CB320
		static content::MemberList* GetMembers();

		engine::HandleBase unknown28;
		float range;  // +0x2C
		int unknown30;
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
