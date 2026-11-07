#include "code/proto/behaviours/basehealthbehaviour.h"
#include "code/engine/driving/carattributes.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x102BA9F0
	content::ClassInfo* BaseHealthBehaviour::BaseAttackTypeConfiguration::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::BaseHealthBehaviour::BaseAttackTypeConfiguration";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102BAA30
	content::ClassInfo* BaseHealthBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::BaseHealthBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102BAA70
	BaseHealthBehaviour::BaseAttackTypeConfiguration::BaseAttackTypeConfiguration()
	{
		float one = engine::driving::gOne;
		damageScale25mm = one;
		damageScale127mm = one;
		damageScale120mm = one;
		damageScale30mm = one;
		damageScale70mm = one;
		damageScaleMissile = one;
		damageScale50cal = one;
	}

	// FUNCTION: ENGINE 0x102BAE50
	content::MemberList* BaseHealthBehaviour::BaseAttackTypeConfiguration::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<BaseAttackTypeConfiguration, float, 0>("p"),
				PROTO_OFFSET(BaseAttackTypeConfiguration, damageScale25mm), "25mmDamageScale" },
			{ content::GetMemberPrimitiveMetaType<BaseAttackTypeConfiguration, float, 1>("p"),
				PROTO_OFFSET(BaseAttackTypeConfiguration, damageScale127mm), "127mmDamageScale" },
			{ content::GetMemberPrimitiveMetaType<BaseAttackTypeConfiguration, float, 2>("p"),
				PROTO_OFFSET(BaseAttackTypeConfiguration, damageScale120mm), "120mmDamageScale" },
			{ content::GetMemberPrimitiveMetaType<BaseAttackTypeConfiguration, float, 3>("p"),
				PROTO_OFFSET(BaseAttackTypeConfiguration, damageScale30mm), "30mmDamageScale" },
			{ content::GetMemberPrimitiveMetaType<BaseAttackTypeConfiguration, float, 4>("p"),
				PROTO_OFFSET(BaseAttackTypeConfiguration, damageScale70mm), "70mmDamageScale" },
			{ content::GetMemberPrimitiveMetaType<BaseAttackTypeConfiguration, float, 5>("p"),
				PROTO_OFFSET(BaseAttackTypeConfiguration, damageScaleMissile), "MissileDamageScale" },
			{ content::GetMemberPrimitiveMetaType<BaseAttackTypeConfiguration, float, 6>("p"),
				PROTO_OFFSET(BaseAttackTypeConfiguration, damageScale50cal), "50calDamageScale" }
		};
		sList.members = sMembers;
		sList.count = 7;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102BB080
	content::MemberList* BaseHealthBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<AdvancedHealthBehaviour>();
		static content::BaseClassCasterImpl<AdvancedHealthBehaviour, BaseHealthBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetClassMetaType<BaseAttackTypeConfiguration>(),
				PROTO_OFFSET(BaseHealthBehaviour, attackTypeDamageScale), "attackTypeDamageScale" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102BAC10
// FUNCTION: ENGINE 0x102BAC20
// FUNCTION: ENGINE 0x102BAC30
// FUNCTION: ENGINE 0x102BAC90
// FUNCTION: ENGINE 0x102BACD0
// FUNCTION: ENGINE 0x102BAD10
// FUNCTION: ENGINE 0x102BAD50
// FUNCTION: ENGINE 0x102BAD90
// FUNCTION: ENGINE 0x102BADD0
// FUNCTION: ENGINE 0x102BAE10
// FUNCTION: ENGINE 0x102BB020
