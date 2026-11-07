#include "code/proto/behaviours/missilespawnerbehaviour.h"
#include "code/core/refptr.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x1046D330
	content::ClassInfo* MissileSpawnProfile::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::MissileSpawnProfile";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1046D370
	content::ClassInfo* MissileSpawnDrawSwap::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::MissileSpawnDrawSwap";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1046D3B0
	content::ClassInfo* MissileSpawnerBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::MissileSpawnerBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1046D3F0
	void MissileSpawnerBehaviour::Slot1()
	{
		WeaponBehaviour::Slot1();
		Slot9(0);
	}

	// FUNCTION: ENGINE 0x1046D410
	void MissileSpawnerBehaviour::OnMessage(engine::Message* message)
	{
		WeaponBehaviour::OnMessage(message);
	}

	// FUNCTION: ENGINE 0x1046D420
	AmmoProfileBase* MissileSpawnerBehaviour::GetAmmoProfile()
	{
		return ammoProfile;
	}

	// FUNCTION: ENGINE 0x1046D780
	content::MemberList* MissileSpawnProfile::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<MissileSpawnProfile, 0>("p"), 8, "spawnPositionOffset" },
			{ content::GetMemberVectorMetaType<MissileSpawnProfile, 1>("p"), 0x14, "spawnRotationOffset" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1046D840
	content::MemberList* MissileSpawnDrawSwap::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<MissileSpawnDrawSwap>(true, true, "p"),
				PROTO_NAME_OFFSET(MissileSpawnDrawSwap, drawable), "drawable" },
			{ content::GetNameMetaTypeCopy<MissileSpawnDrawSwap>(true, true, "p"),
				PROTO_NAME_OFFSET(MissileSpawnDrawSwap, spawnJoint), "spawnJoint" },
			{ content::GetMemberVectorMetaType<MissileSpawnDrawSwap, 0>("p"), 0x10, "spawnPositionOffset" },
			{ content::GetMemberVectorMetaType<MissileSpawnDrawSwap, 1>("p"), 0x1c, "spawnRotationOffset" }
		};
		sList.members = sMembers;
		sList.count = 4;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1046D9C0
	MissileSpawnDrawSwap::MissileSpawnDrawSwap() : spawnPositionOffset(math::kZeroVector),
		spawnRotationOffset(math::kZeroVector)
	{
	}

	// FUNCTION: ENGINE 0x1046DA40
	MissileSpawnProfile::MissileSpawnProfile() : spawnPositionOffset(math::kZeroVector),
		spawnRotationOffset(math::kZeroVector)
	{
	}

	// FUNCTION: ENGINE 0x1046DB00
	void MissileSpawnerBehaviour::SetAmmoProfile(AmmoProfileBase* profile)
	{
		core::RefAssign(ammoProfile, static_cast<MissileProfile*>(profile));
	}

	// FUNCTION: ENGINE 0x1046EAC0
	content::MemberList* MissileSpawnerBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<WeaponBehaviour>();
		static content::BaseClassCasterImpl<WeaponBehaviour, MissileSpawnerBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetReferenceMetaType<MissileSpawnerBehaviour, content::MetaObjectTemplate>("p"),
				PROTO_OFFSET(MissileSpawnerBehaviour, missileTemplate), "missileTemplate" },
			{ content::GetReferenceMetaType<MissileSpawnerBehaviour, MissileProfile>("p"),
				PROTO_OFFSET(MissileSpawnerBehaviour, ammoProfile), "ammoProfile" },
			{ content::GetReferenceMetaType<MissileSpawnerBehaviour, MissileSpawnProfile>("p"),
				PROTO_OFFSET(MissileSpawnerBehaviour, missileSpawnProfile), "missileSpawnProfile" },
			{ content::GetArrayDynamicMetaType<MissileSpawnerBehaviour, DrawSwapArray>(
				content::GetClassMetaType<MissileSpawnDrawSwap>(), "p"),
				PROTO_OFFSET(MissileSpawnerBehaviour, drawSwapList), "drawSwapList" }
		};
		sList.members = sMembers;
		sList.count = 4;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1046F9F0
	MissileSpawnerBehaviour::MissileSpawnerBehaviour(engine::GameObject* newOwner) : WeaponBehaviour(newOwner),
		unknown78(0), missileTemplate(0), ammoProfile(0), missileSpawnProfile(0)
	{
		Listen(0x22, true);
	}

	// FUNCTION: ENGINE 0x1046FA50
	MissileSpawnerBehaviour::~MissileSpawnerBehaviour()
	{
		core::SafeRelease(missileTemplate);
		core::SafeRelease(missileSpawnProfile);
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1046D430
// FUNCTION: ENGINE 0x1046D510
// FUNCTION: ENGINE 0x1046D520
// FUNCTION: ENGINE 0x1046D560
// FUNCTION: ENGINE 0x1046D5A0
// FUNCTION: ENGINE 0x1046D5E0
// FUNCTION: ENGINE 0x1046D620
// FUNCTION: ENGINE 0x1046D660
// FUNCTION: ENGINE 0x1046D6A0
// FUNCTION: ENGINE 0x1046D6B0
// FUNCTION: ENGINE 0x1046D6C0
// FUNCTION: ENGINE 0x1046D6D0
// FUNCTION: ENGINE 0x1046D6F0
// FUNCTION: ENGINE 0x1046D700
// FUNCTION: ENGINE 0x1046D980
// FUNCTION: ENGINE 0x1046D990
// FUNCTION: ENGINE 0x1046DAC0
// FUNCTION: ENGINE 0x1046DAD0
// FUNCTION: ENGINE 0x1046DE30
// FUNCTION: ENGINE 0x1046DE40
// FUNCTION: ENGINE 0x1046DE50
// FUNCTION: ENGINE 0x1046DE80
// FUNCTION: ENGINE 0x1046DE90
// FUNCTION: ENGINE 0x1046DEC0
// FUNCTION: ENGINE 0x1046DED0
// FUNCTION: ENGINE 0x1046DF00
// FUNCTION: ENGINE 0x1046DF20
// FUNCTION: ENGINE 0x1046DF40
// FUNCTION: ENGINE 0x1046DFA0
// FUNCTION: ENGINE 0x1046DFD0
// FUNCTION: ENGINE 0x1046E090
// FUNCTION: ENGINE 0x1046E0C0
// FUNCTION: ENGINE 0x1046E1C0
// FUNCTION: ENGINE 0x1046E7F0
// FUNCTION: ENGINE 0x1046E850
// FUNCTION: ENGINE 0x1046E8B0
// FUNCTION: ENGINE 0x1046E910
// FUNCTION: ENGINE 0x1046E980
// FUNCTION: ENGINE 0x1046EA30
// FUNCTION: ENGINE 0x1046EE70
// FUNCTION: ENGINE 0x1046F010
// FUNCTION: ENGINE 0x1046F920
// FUNCTION: ENGINE 0x1046F940
// FUNCTION: ENGINE 0x1046FAA0
// FUNCTION: ENGINE 0x1046FB70
