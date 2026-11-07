#include "code/proto/behaviours/prototypehealthbehaviour.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x102C28B0
	PrototypeHealthBehaviour::HealthBehaviourUnlockable::HealthBehaviourUnlockable() : unlockable(UNLOCKABLE_NONE),
		healthAdded(0.0f), criticalMassHealthAdded(0.0f)
	{
	}

	// FUNCTION: ENGINE 0x102C2830
	content::ClassInfo* PrototypeHealthBehaviour::HealthBehaviourUnlockable::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::PrototypeHealthBehaviour::HealthBehaviourUnlockable";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102C2870
	content::ClassInfo* PrototypeHealthBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::PrototypeHealthBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102C3AA0
	content::MemberList* PrototypeHealthBehaviour::HealthBehaviourUnlockable::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetEnumMetaType<Unlockable>(), 0, "unlockable" },
			{ content::GetMemberPrimitiveMetaType<HealthBehaviourUnlockable, float, 0>("p"),
				PROTO_OFFSET(HealthBehaviourUnlockable, healthAdded), "healthAdded" },
			{ content::GetMemberPrimitiveMetaType<HealthBehaviourUnlockable, float, 1>("p"),
				PROTO_OFFSET(HealthBehaviourUnlockable, criticalMassHealthAdded), "criticalMassHealthAdded" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102C4030
	content::MemberList* PrototypeHealthBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<AdvancedHealthBehaviour>();
		static content::BaseClassCasterImpl<AdvancedHealthBehaviour, PrototypeHealthBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<PrototypeHealthBehaviour, UnlockableArray>(
				content::GetClassMetaType<HealthBehaviourUnlockable>(), "p"),
				PROTO_OFFSET(PrototypeHealthBehaviour, unlockables), "unlockables" },
			{ content::GetMemberPrimitiveMetaType<PrototypeHealthBehaviour, float, 0>("p"),
				PROTO_OFFSET(PrototypeHealthBehaviour, devastatorHealthCost), "devastatorHealthCost" },
			{ content::GetMemberPrimitiveMetaType<PrototypeHealthBehaviour, float, 1>("p"),
				PROTO_OFFSET(PrototypeHealthBehaviour, defaultHealthPercentage), "defaultHealthPercentage" },
			{ content::GetMemberPrimitiveMetaType<PrototypeHealthBehaviour, float, 2>("p"),
				PROTO_OFFSET(PrototypeHealthBehaviour, criticalMassHealthGainFactor), "criticalMassHealthGainFactor" },
			{ content::GetMemberPrimitiveMetaType<PrototypeHealthBehaviour, float, 3>("p"),
				PROTO_OFFSET(PrototypeHealthBehaviour, criticalMassExitHealthLoss), "criticalMassExitHealthLoss" },
			{ content::GetMemberPrimitiveMetaType<PrototypeHealthBehaviour, float, 4>("p"),
				PROTO_OFFSET(PrototypeHealthBehaviour, regenRateMax), "regenRateMax" },
			{ content::GetEnumMetaType<Unlockable>(), 0x1D0, "regenRateUnlockableFirst" },
			{ content::GetEnumMetaType<Unlockable>(), 0x1D4, "regenRateUnlockableLast" },
			{ content::GetMemberPrimitiveMetaType<PrototypeHealthBehaviour, float, 5>("p"),
				PROTO_OFFSET(PrototypeHealthBehaviour, regenTimeWithNoDamageMax), "regenTimeWithNoDamageMax" },
			{ content::GetEnumMetaType<Unlockable>(), 0x1DC, "regenTimeWithNoDamageUnlockableFirst" },
			{ content::GetEnumMetaType<Unlockable>(), 0x1E0, "regenTimeWithNoDamageUnlockableLast" },
			{ content::GetMemberPrimitiveMetaType<PrototypeHealthBehaviour, float, 6>("p"),
				PROTO_OFFSET(PrototypeHealthBehaviour, consumeHealthMultiplier), "consumeHealthMultiplier" },
			{ content::GetEnumMetaType<Unlockable>(), 0x1E8, "consumeHealthMultiplierUnlockableFirst" },
			{ content::GetEnumMetaType<Unlockable>(), 0x1EC, "consumeHealthMultiplierUnlockableLast" },
			{ content::GetMemberPrimitiveMetaType<PrototypeHealthBehaviour, float, 7>("p"),
				PROTO_OFFSET(PrototypeHealthBehaviour, adrenalineSurgeThresholdHealth),
				"adrenalineSurgeThresholdHealth" },
			{ content::GetMemberPrimitiveMetaType<PrototypeHealthBehaviour, float, 8>("p"),
				PROTO_OFFSET(PrototypeHealthBehaviour, adrenalineSurgeHealthOnEntry), "adrenalineSurgeHealthOnEntry" },
			{ content::GetMemberPrimitiveMetaType<PrototypeHealthBehaviour, float, 9>("p"),
				PROTO_OFFSET(PrototypeHealthBehaviour, adrenalineSurgeUndamageableTime),
				"adrenalineSurgeUndamageableTime" },
			{ content::GetMemberPrimitiveMetaType<PrototypeHealthBehaviour, float, 10>("p"),
				PROTO_OFFSET(PrototypeHealthBehaviour, minTimeBetweenAdrenalineDevastators),
				"minTimeBetweenAdrenalineDevastators" },
			{ content::GetMemberPrimitiveMetaType<PrototypeHealthBehaviour, float, 11>("p"),
				PROTO_OFFSET(PrototypeHealthBehaviour, lowHealthThreshold), "lowHealthThreshold" },
			{ content::GetEnumMetaType<Unlockable>(), 0x210, "adrenalineSurgeUnlockable" }
		};
		sList.members = sMembers;
		sList.count = 20;
		return &sList;
	}
}
