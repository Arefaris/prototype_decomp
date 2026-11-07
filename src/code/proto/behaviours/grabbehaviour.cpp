#include "code/proto/behaviours/grabbehaviour.h"
#include "code/engine/gameobject/gameobjectspawner.h"
#include "code/core/refptr.h"
#include "code/ravenphysics/context.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// This unit's own copy of core::RefAssign for the spawn template (the engine keeps one per unit)
	struct SpawnTemplateRef
	{
		static void Assign(content::MetaObjectTemplate*& pointer, content::MetaObjectTemplate* object);
	};

	// FUNCTION: ENGINE 0x102C6DE0
	void SpawnTemplateRef::Assign(content::MetaObjectTemplate*& pointer, content::MetaObjectTemplate* object)
	{
		if (object != 0)
		{
			object->AddRef();
		}
		if (pointer != 0)
		{
			pointer->Release();
		}
		pointer = object;
	}

	// FUNCTION: ENGINE 0x102C7000
	GrabSpawnListEntry::GrabSpawnListEntry() : spawnTemplate(0)
	{
	}

	// FUNCTION: ENGINE 0x102C7880
	GrabSpawnListEntry::GrabSpawnListEntry(const GrabSpawnListEntry& other) : spawnTemplate(0)
	{
		*this = other;
	}

	// FUNCTION: ENGINE 0x102C7040
	GrabSpawnListEntry::~GrabSpawnListEntry()
	{
		core::SafeRelease(spawnTemplate);
	}

	// FUNCTION: ENGINE 0x102C7050
	GrabSpawnListEntry& GrabSpawnListEntry::operator=(const GrabSpawnListEntry& other)
	{
		grabSlot = other.grabSlot;
		SpawnTemplateRef::Assign(spawnTemplate, other.spawnTemplate);
		parentJoint = other.parentJoint;
		parentPositionOffset.x = other.parentPositionOffset.x;
		parentPositionOffset.y = other.parentPositionOffset.y;
		parentPositionOffset.z = other.parentPositionOffset.z;
		parentRotationOffset.x = other.parentRotationOffset.x;
		parentRotationOffset.y = other.parentRotationOffset.y;
		parentRotationOffset.z = other.parentRotationOffset.z;
		childJoint = other.childJoint;
		childPositionOffset.x = other.childPositionOffset.x;
		childPositionOffset.y = other.childPositionOffset.y;
		childPositionOffset.z = other.childPositionOffset.z;
		childRotationOffset.x = other.childRotationOffset.x;
		childRotationOffset.y = other.childRotationOffset.y;
		childRotationOffset.z = other.childRotationOffset.z;
		initialPlaybackNode = other.initialPlaybackNode;
		aICharacter = other.aICharacter;
		return *this;
	}

	// FUNCTION: ENGINE 0x102C68D0
	content::ClassInfo* GrabSpawnListEntry::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::GrabSpawnListEntry";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102C6910
	content::ClassInfo* GrabBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "GrabBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102C6950
	content::ClassInfo* GrabAutoSpawnBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::GrabAutoSpawnBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102CA0F0
	content::ClassInfo* GrabSlot::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::GrabSlot";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102CA310
	content::ClassInfo* GrabSelectionBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::GrabSelectionBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102C84D0
	content::MemberList* GrabSpawnListEntry::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<GrabSpawnListEntry>(true, true, "p"),
				PROTO_NAME_OFFSET(GrabSpawnListEntry, grabSlot), "grabSlot" },
			{ content::GetReferenceMetaType<GrabSpawnListEntry, content::MetaObjectTemplate>("p"),
				PROTO_OFFSET(GrabSpawnListEntry, spawnTemplate), "spawnTemplate" },
			{ content::GetMemberNameMetaType<GrabSpawnListEntry, 1>(true, true, "p"),
				PROTO_NAME_OFFSET(GrabSpawnListEntry, parentJoint), "parentJoint" },
			{ content::GetMemberVectorMetaType<GrabSpawnListEntry, 0>("p"), 0x18, "parentPositionOffset" },
			{ content::GetMemberVectorMetaType<GrabSpawnListEntry, 1>("p"), 0x24, "parentRotationOffset" },
			{ content::GetMemberNameMetaType<GrabSpawnListEntry, 2>(true, true, "p"),
				PROTO_NAME_OFFSET(GrabSpawnListEntry, childJoint), "childJoint" },
			{ content::GetMemberVectorMetaType<GrabSpawnListEntry, 2>("p"), 0x38, "childPositionOffset" },
			{ content::GetMemberVectorMetaType<GrabSpawnListEntry, 3>("p"), 0x44, "childRotationOffset" },
			{ content::GetMemberPrimitiveMetaType<GrabSpawnListEntry, bool, 0>("p"),
				PROTO_OFFSET(GrabSpawnListEntry, aICharacter), "aICharacter" },
			{ content::GetMemberNameMetaType<GrabSpawnListEntry, 3>(true, true, "p"),
				PROTO_NAME_OFFSET(GrabSpawnListEntry, initialPlaybackNode), "initialPlaybackNode" }
		};
		sList.members = sMembers;
		sList.count = 10;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102C8730
	content::MemberList* GrabBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, GrabBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<GrabBehaviour, SlotArray>(content::GetClassMetaType<GrabSlot>(), "pn"),
				PROTO_OFFSET(GrabBehaviour, grabSlots), "grabSlots" },
			{ content::GetNameMetaType<GrabBehaviour>(true, true, "p"),
				PROTO_NAME_OFFSET(GrabBehaviour, mountableSlot), "mountableSlot" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102C9800
	content::MemberList* GrabAutoSpawnBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, GrabAutoSpawnBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<GrabAutoSpawnBehaviour, SpawnArray>(
				content::GetClassMetaType<GrabSpawnListEntry>(), "p"),
				PROTO_OFFSET(GrabAutoSpawnBehaviour, autoSpawnList), "autoSpawnList" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102CA1F0
	content::MemberList* GrabSlot::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<GrabSlot>(true, true, "pn"), PROTO_NAME_OFFSET(GrabSlot, name), "name" },
			{ content::GetMemberPrimitiveMetaType<GrabSlot, bool, 0>("pn"), PROTO_OFFSET(GrabSlot, temporary),
				"temporary" },
			{ content::GetMemberPrimitiveMetaType<GrabSlot, bool, 1>("pn"), PROTO_OFFSET(GrabSlot, wakeUpPhysics),
				"wakeUpPhysics" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102CB320
	content::MemberList* GrabSelectionBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<GrabBehaviour>();
		static content::BaseClassCasterImpl<GrabBehaviour, GrabSelectionBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<GrabSelectionBehaviour, float, 0>("p"),
				PROTO_OFFSET(GrabSelectionBehaviour, range), "range" },
			{ content::GetMemberPrimitiveMetaType<GrabSelectionBehaviour, unsigned int, 0>("p"),
				PROTO_OFFSET(GrabSelectionBehaviour, allowedNavmeshAreas), "allowedNavmeshAreas" },
			{ content::GetReferenceMetaType<GrabSelectionBehaviour, ravenphysics::IntersectionPropertiesLoader>("p"),
				PROTO_OFFSET(GrabSelectionBehaviour, grabbableIntersectionProperties),
				"grabbableIntersectionProperties" },
			{ content::GetMemberVectorMetaType<GrabSelectionBehaviour, 0>("p"), 0x40, "closeRangeOffset" },
			{ content::GetMemberVectorMetaType<GrabSelectionBehaviour, 1>("p"), 0x4C, "longRangeOffset" },
			{ content::GetMemberPrimitiveMetaType<GrabSelectionBehaviour, float, 1>("p"),
				PROTO_OFFSET(GrabSelectionBehaviour, minimumMassToGrab), "minimumMassToGrab" }
		};
		sList.members = sMembers;
		sList.count = 6;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102C69E0
// FUNCTION: ENGINE 0x102C6A20
// FUNCTION: ENGINE 0x102C6AF0
// FUNCTION: ENGINE 0x102C6B80
// FUNCTION: ENGINE 0x102C6BC0
// FUNCTION: ENGINE 0x102C6C00
// FUNCTION: ENGINE 0x102C6C40
// FUNCTION: ENGINE 0x102C6C80
// FUNCTION: ENGINE 0x102C6CC0
// FUNCTION: ENGINE 0x102C6D00
// FUNCTION: ENGINE 0x102C6D40
// FUNCTION: ENGINE 0x102C6D80
// FUNCTION: ENGINE 0x102C6D90
// FUNCTION: ENGINE 0x102C6DD0
// FUNCTION: ENGINE 0x102C6E20
// FUNCTION: ENGINE 0x102C6E30
// FUNCTION: ENGINE 0x102C6F80
// FUNCTION: ENGINE 0x102C6F90
// FUNCTION: ENGINE 0x102C6FC0
// FUNCTION: ENGINE 0x102C6FD0
// FUNCTION: ENGINE 0x102C7110
// FUNCTION: ENGINE 0x102C7380
// FUNCTION: ENGINE 0x102C73C0
// FUNCTION: ENGINE 0x102C73D0
// FUNCTION: ENGINE 0x102C73F0
// FUNCTION: ENGINE 0x102C7410
// FUNCTION: ENGINE 0x102C7430
// FUNCTION: ENGINE 0x102C7490
// FUNCTION: ENGINE 0x102C74A0
// FUNCTION: ENGINE 0x102C74D0
// FUNCTION: ENGINE 0x102C7500
// FUNCTION: ENGINE 0x102C7520
// FUNCTION: ENGINE 0x102C7530
// FUNCTION: ENGINE 0x102C7560
// FUNCTION: ENGINE 0x102C7580
// FUNCTION: ENGINE 0x102C75E0
// FUNCTION: ENGINE 0x102C7630
// FUNCTION: ENGINE 0x102C7650
// FUNCTION: ENGINE 0x102C7670
// FUNCTION: ENGINE 0x102C76B0
// FUNCTION: ENGINE 0x102C76F0
// FUNCTION: ENGINE 0x102C7750
// FUNCTION: ENGINE 0x102C7790
// FUNCTION: ENGINE 0x102C81C0
// FUNCTION: ENGINE 0x102C8220
// FUNCTION: ENGINE 0x102C8280
// FUNCTION: ENGINE 0x102C82F0
// FUNCTION: ENGINE 0x102C83F0
// FUNCTION: ENGINE 0x102C8460
// FUNCTION: ENGINE 0x102C94E0
// FUNCTION: ENGINE 0x102C9580
// FUNCTION: ENGINE 0x102C95B0
// FUNCTION: ENGINE 0x102C96F0
// FUNCTION: ENGINE 0x102C9950
// FUNCTION: ENGINE 0x102C99A0
// FUNCTION: ENGINE 0x102C9CD0
// FUNCTION: ENGINE 0x102C9D80
// FUNCTION: ENGINE 0x102C9DF0
// FUNCTION: ENGINE 0x102C9FF0
// FUNCTION: ENGINE 0x102CA130
// FUNCTION: ENGINE 0x102CA170
// FUNCTION: ENGINE 0x102CA1B0
// FUNCTION: ENGINE 0x102CA3F0
// FUNCTION: ENGINE 0x102CA430
// FUNCTION: ENGINE 0x102CA4B0
// FUNCTION: ENGINE 0x102CA4C0
// FUNCTION: ENGINE 0x102CA980
// FUNCTION: ENGINE 0x102CA9C0
// FUNCTION: ENGINE 0x102CAA00
// FUNCTION: ENGINE 0x102CB2C0
