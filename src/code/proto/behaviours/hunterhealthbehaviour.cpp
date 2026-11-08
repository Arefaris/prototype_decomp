#include "code/proto/behaviours/hunterhealthbehaviour.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x102BF870
	content::ClassInfo* HunterHealthBehaviour::MinHealthOverride::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::HunterHealthBehaviour::MinHealthOverride";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102BF8B0
	content::ClassInfo* HunterHealthBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::HunterHealthBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102BF8F0
	HunterHealthBehaviour::MinHealthOverride::MinHealthOverride()
	{
		for (int i = 0; i < ATTACK_TYPE_COUNT; i++)
		{
			minHealth[i] = -1.0f;
		}
	}

	// FUNCTION: ENGINE 0x102BFC60
	content::MemberList* HunterHealthBehaviour::MinHealthOverride::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<MinHealthOverride, float, 0>("p"),
				PROTO_OFFSET(MinHealthOverride, minHealth[11]), "minHealthMissile" },
			{ content::GetMemberPrimitiveMetaType<MinHealthOverride, float, 1>("p"),
				PROTO_OFFSET(MinHealthOverride, minHealth[12]), "minHealthMissileExplosion" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102BFD90
	content::MemberList* HunterHealthBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<AdvancedHealthBehaviour>();
		static content::BaseClassCasterImpl<AdvancedHealthBehaviour, HunterHealthBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetClassMetaType<MinHealthOverride>(),
				PROTO_OFFSET(HunterHealthBehaviour, minHealthOverride), "minHealthOverride" },
			{ content::GetMemberPrimitiveMetaType<HunterHealthBehaviour, float, 0>("p"),
				PROTO_OFFSET(HunterHealthBehaviour, damageOverrideThreshold), "damageOverrideThreshold" },
			{ content::GetMemberPrimitiveMetaType<HunterHealthBehaviour, float, 1>("p"),
				PROTO_OFFSET(HunterHealthBehaviour, damageOverrideMinHealth), "damageOverrideMinHealth" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102BFA20
// FUNCTION: ENGINE 0x102BFA30
// FUNCTION: ENGINE 0x102BFA40
// FUNCTION: ENGINE 0x102BFB60
// FUNCTION: ENGINE 0x102BFBA0
// FUNCTION: ENGINE 0x102BFBE0
// FUNCTION: ENGINE 0x102BFC20
// FUNCTION: ENGINE 0x102BFD30
