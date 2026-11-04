#include "code/proto/behaviours/weaponconfigurationbehaviour.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10474AE0
	content::ClassInfo* WeaponEntry::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::WeaponEntry";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10474B20
	content::ClassInfo* WeaponConfiguration::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::WeaponConfiguration";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10474B60
	content::ClassInfo* WeaponConfigurationBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::WeaponConfigurationBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10474F50
	WeaponEntry::WeaponEntry()
	{
	}

	// FUNCTION: ENGINE 0x10476220
	WeaponConfiguration::WeaponConfiguration()
	{
	}

	// FUNCTION: ENGINE 0x10474E70
	content::MemberList* WeaponEntry::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<WeaponEntry>(true, true, "p"),
				PROTO_NAME_OFFSET(WeaponEntry, weapon), "weapon" },
			{ content::GetNameMetaTypeCopy<WeaponEntry>(true, true, "p"),
				PROTO_NAME_OFFSET(WeaponEntry, grabSlot), "grabSlot" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10474FB0
	void WeaponConfigurationBehaviour::Slot1()
	{
		if (configurations.begin != configurations.end)
		{
			currentConfiguration = 0;
		}
	}

	// FUNCTION: ENGINE 0x10475CB0
	content::MemberList* WeaponConfiguration::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<WeaponConfiguration>(true, true, "p"),
				PROTO_NAME_OFFSET(WeaponConfiguration, name), "name" },
			{ content::GetArrayDynamicMetaType<WeaponConfiguration, WeaponArray>(
				content::GetClassMetaType<WeaponEntry>(), "p"), PROTO_OFFSET(WeaponConfiguration, weapons), "weapons" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10475FB0
	content::MemberList* WeaponConfigurationBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, WeaponConfigurationBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<WeaponConfigurationBehaviour, ConfigurationArray>(
				content::GetClassMetaType<WeaponConfiguration>(), "p"),
				PROTO_OFFSET(WeaponConfigurationBehaviour, configurations), "configurations" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10476800
	WeaponConfigurationBehaviour::WeaponConfigurationBehaviour(engine::GameObject* newOwner) :
		engine::Behaviour(newOwner), currentConfiguration(-1)
	{
		Listen(0x22, true);
	}

	// FUNCTION: ENGINE 0x10476850
	WeaponConfigurationBehaviour::~WeaponConfigurationBehaviour()
	{
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10474BF0
// FUNCTION: ENGINE 0x10474C10
// FUNCTION: ENGINE 0x10474C50
// FUNCTION: ENGINE 0x10474CC0
// FUNCTION: ENGINE 0x10474D50
// FUNCTION: ENGINE 0x10474D60
// FUNCTION: ENGINE 0x10474DA0
// FUNCTION: ENGINE 0x10474DE0
// FUNCTION: ENGINE 0x10474E20
// FUNCTION: ENGINE 0x10474E30
// FUNCTION: ENGINE 0x10474E40
// FUNCTION: ENGINE 0x10474E50
// FUNCTION: ENGINE 0x10474F70
// FUNCTION: ENGINE 0x10474F80
// FUNCTION: ENGINE 0x104753A0
// FUNCTION: ENGINE 0x104753B0
// FUNCTION: ENGINE 0x104753C0
// FUNCTION: ENGINE 0x10475420
// FUNCTION: ENGINE 0x10475430
// FUNCTION: ENGINE 0x10475450
// FUNCTION: ENGINE 0x10475470
// FUNCTION: ENGINE 0x104754D0
// FUNCTION: ENGINE 0x10475500
// FUNCTION: ENGINE 0x10475530
// FUNCTION: ENGINE 0x10475560
// FUNCTION: ENGINE 0x10475570
// FUNCTION: ENGINE 0x104755A0
// FUNCTION: ENGINE 0x104755C0
// FUNCTION: ENGINE 0x10475620
// FUNCTION: ENGINE 0x10475660
// FUNCTION: ENGINE 0x10475680
// FUNCTION: ENGINE 0x104756A0
// FUNCTION: ENGINE 0x104756C0
// FUNCTION: ENGINE 0x10475700
// FUNCTION: ENGINE 0x10475730
// FUNCTION: ENGINE 0x10475780
// FUNCTION: ENGINE 0x104757E0
// FUNCTION: ENGINE 0x10475840
// FUNCTION: ENGINE 0x10475940
// FUNCTION: ENGINE 0x104759A0
// FUNCTION: ENGINE 0x10475A10
// FUNCTION: ENGINE 0x10475AC0
// FUNCTION: ENGINE 0x10475B20
// FUNCTION: ENGINE 0x10475BB0
// FUNCTION: ENGINE 0x10475D90
// FUNCTION: ENGINE 0x10475E00
// FUNCTION: ENGINE 0x10475E30
// FUNCTION: ENGINE 0x10475F30
// FUNCTION: ENGINE 0x10476090
// FUNCTION: ENGINE 0x104760B0
// FUNCTION: ENGINE 0x10476140
// FUNCTION: ENGINE 0x104761B0
// FUNCTION: ENGINE 0x10476240
// FUNCTION: ENGINE 0x104762F0
// FUNCTION: ENGINE 0x104763A0
// FUNCTION: ENGINE 0x104763E0
// FUNCTION: ENGINE 0x10476550
// FUNCTION: ENGINE 0x104766D0
// FUNCTION: ENGINE 0x10476720
// FUNCTION: ENGINE 0x10476750
// FUNCTION: ENGINE 0x104768A0
// FUNCTION: ENGINE 0x10476970
