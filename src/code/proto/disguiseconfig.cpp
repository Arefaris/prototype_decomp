#include "code/proto/disguiseconfig.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x103D1150
	content::ClassInfo* DisguiseConfig::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::DisguiseConfig";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x103D1190
	content::ClassInfo* DisguiseConfig::Incident::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::DisguiseConfig::Incident";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x103D11D0
	content::ClassInfo* DisguiseConfig::SuspicionIncrease::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::DisguiseConfig::SuspicionIncrease";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x103D1210
	content::ClassInfo* DisguiseConfig::SuspicionDecrease::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::DisguiseConfig::SuspicionDecrease";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x103D1250
	content::ClassInfo* DisguiseConfig::AlertIncrease::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::DisguiseConfig::AlertIncrease";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x103D1290
	content::ClassInfo* DisguiseConfig::AlertDecrease::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::DisguiseConfig::AlertDecrease";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x103D12D0
	DisguiseConfig::Incident::Incident() : increase(0.0f), decrease(0.0f), maximum(0.0f), maxFactor(0.0f),
		useDistanceFactor(false), delaysDecrease(false), increaseInSearch(0.0f), maximumInSearch(0.0f)
	{
	}

	// FUNCTION: ENGINE 0x103D2B60
	content::MemberList* DisguiseConfig::Incident::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<Incident, float, 0>("p"), PROTO_OFFSET(Incident, increase),
				"increase" },
			{ content::GetMemberPrimitiveMetaType<Incident, float, 1>("p"), PROTO_OFFSET(Incident, decrease),
				"decrease" },
			{ content::GetMemberPrimitiveMetaType<Incident, float, 2>("p"), PROTO_OFFSET(Incident, maximum),
				"maximum" },
			{ content::GetMemberPrimitiveMetaType<Incident, float, 3>("p"), PROTO_OFFSET(Incident, maxFactor),
				"maxFactor" },
			{ content::GetMemberPrimitiveMetaType<Incident, bool, 4>("p"),
				PROTO_OFFSET(Incident, useDistanceFactor), "useDistanceFactor" },
			{ content::GetMemberPrimitiveMetaType<Incident, bool, 5>("p"),
				PROTO_OFFSET(Incident, delaysDecrease), "delaysDecrease" },
			{ content::GetMemberPrimitiveMetaType<Incident, float, 6>("p"),
				PROTO_OFFSET(Incident, increaseInSearch), "increaseInSearch" },
			{ content::GetMemberPrimitiveMetaType<Incident, float, 7>("p"),
				PROTO_OFFSET(Incident, maximumInSearch), "maximumInSearch" }
		};
		sList.members = sMembers;
		sList.count = 8;
		return &sList;
	}

	// FUNCTION: ENGINE 0x103D2D60
	content::MemberList* DisguiseConfig::SuspicionIncrease::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<SuspicionIncrease, float, 0>("pn"),
				PROTO_OFFSET(SuspicionIncrease, suspicionLow), "suspicionLow" },
			{ content::GetMemberPrimitiveMetaType<SuspicionIncrease, float, 1>("pn"),
				PROTO_OFFSET(SuspicionIncrease, suspicionHigh), "suspicionHigh" },
			{ content::GetMemberPrimitiveMetaType<SuspicionIncrease, float, 2>("pn"),
				PROTO_OFFSET(SuspicionIncrease, minPercent), "minPercent" },
			{ content::GetClassMetaType<Faction>(), PROTO_OFFSET(SuspicionIncrease, disguiseType), "disguiseType" },
			{ content::GetClassMetaType<Faction>(), PROTO_OFFSET(SuspicionIncrease, enemyType), "enemyType" }
		};
		sList.members = sMembers;
		sList.count = 5;
		return &sList;
	}

	// FUNCTION: ENGINE 0x103D2EC0
	content::MemberList* DisguiseConfig::SuspicionDecrease::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<SuspicionDecrease, float, 0>("pn"),
				PROTO_OFFSET(SuspicionDecrease, suspicion), "suspicion" },
			{ content::GetClassMetaType<Faction>(), PROTO_OFFSET(SuspicionDecrease, disguiseType), "disguiseType" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x103D2F90
	content::MemberList* DisguiseConfig::AlertIncrease::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<AlertIncrease, float, 0>("pn"),
				PROTO_OFFSET(AlertIncrease, alert), "alert" },
			{ content::GetMemberPrimitiveMetaType<AlertIncrease, float, 1>("pn"),
				PROTO_OFFSET(AlertIncrease, surroundingFunction), "surroundingFunction" },
			{ content::GetClassMetaType<Faction>(), PROTO_OFFSET(AlertIncrease, disguiseType), "disguiseType" },
			{ content::GetClassMetaType<Faction>(), PROTO_OFFSET(AlertIncrease, enemyType), "enemyType" }
		};
		sList.members = sMembers;
		sList.count = 4;
		return &sList;
	}

	// FUNCTION: ENGINE 0x103D30C0
	content::MemberList* DisguiseConfig::AlertDecrease::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<AlertDecrease, float, 0>("pn"),
				PROTO_OFFSET(AlertDecrease, alert), "alert" },
			{ content::GetMemberPrimitiveMetaType<AlertDecrease, float, 1>("pn"),
				PROTO_OFFSET(AlertDecrease, surroundingFunction), "surroundingFunction" },
			{ content::GetClassMetaType<Faction>(), PROTO_OFFSET(AlertDecrease, disguiseType), "disguiseType" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// FUNCTION: ENGINE 0x103D3EC0
	content::MemberList* DisguiseConfig::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetClassMetaType<Incident>(), PROTO_OFFSET(DisguiseConfig, incidentAttack), "incidentAttack" },
			{ content::GetClassMetaType<Incident>(), PROTO_OFFSET(DisguiseConfig, incidentFaction),
				"incidentFaction" },
			{ content::GetClassMetaType<Incident>(), PROTO_OFFSET(DisguiseConfig, incidentConsume),
				"incidentConsume" },
			{ content::GetClassMetaType<Incident>(), PROTO_OFFSET(DisguiseConfig, incidentShoveSoldier),
				"incidentShoveSoldier" },
			{ content::GetClassMetaType<Incident>(), PROTO_OFFSET(DisguiseConfig, incidentSmallJump),
				"incidentSmallJump" },
			{ content::GetClassMetaType<Incident>(), PROTO_OFFSET(DisguiseConfig, incidentLanding),
				"incidentLanding" },
			{ content::GetClassMetaType<Incident>(), PROTO_OFFSET(DisguiseConfig, incidentShapeshift),
				"incidentShapeshift" },
			{ content::GetClassMetaType<Incident>(), PROTO_OFFSET(DisguiseConfig, incidentHolding),
				"incidentHolding" },
			{ content::GetClassMetaType<Incident>(), PROTO_OFFSET(DisguiseConfig, incidentSprinting),
				"incidentSprinting" },
			{ content::GetClassMetaType<Incident>(), PROTO_OFFSET(DisguiseConfig, incidentWallrunning),
				"incidentWallrunning" },
			{ content::GetClassMetaType<Incident>(), PROTO_OFFSET(DisguiseConfig, incidentClimbing),
				"incidentClimbing" },
			{ content::GetClassMetaType<Incident>(), PROTO_OFFSET(DisguiseConfig, incidentInsideBase),
				"incidentInsideBase" },
			{ content::GetClassMetaType<Incident>(), PROTO_OFFSET(DisguiseConfig, incidentInsidePerimeter),
				"incidentInsidePerimeter" },
			{ content::GetClassMetaType<Incident>(), PROTO_OFFSET(DisguiseConfig, incidentFriendlyFire),
				"incidentFriendlyFire" },
			{ content::GetClassMetaType<Incident>(), PROTO_OFFSET(DisguiseConfig, incidentFriendlyFireDamage),
				"incidentFriendlyFireDamage" },
			{ content::GetClassMetaType<Incident>(), PROTO_OFFSET(DisguiseConfig, incidentCivilianFire),
				"incidentCivilianFire" },
			{ content::GetClassMetaType<Incident>(), PROTO_OFFSET(DisguiseConfig, incidentInfectedAlly),
				"incidentInfectedAlly" },
			{ content::GetClassMetaType<Incident>(), PROTO_OFFSET(DisguiseConfig, incidentMilitaryAlly),
				"incidentMilitaryAlly" },
			{ content::GetClassMetaType<Incident>(), PROTO_OFFSET(DisguiseConfig, incidentLanding2),
				"incidentLanding2" },
			{ content::GetArrayDynamicMetaType<DisguiseConfig, SuspicionIncreaseArray>(
				content::GetClassMetaType<SuspicionIncrease>(), "pn"),
				PROTO_OFFSET(DisguiseConfig, suspicionIncreases), "suspicionIncreases" },
			{ content::GetArrayDynamicMetaType<DisguiseConfig, SuspicionDecreaseArray>(
				content::GetClassMetaType<SuspicionDecrease>(), "pn"),
				PROTO_OFFSET(DisguiseConfig, suspicionDecreases), "suspicionDecreases" },
			{ content::GetArrayDynamicMetaType<DisguiseConfig, AlertIncreaseArray>(
				content::GetClassMetaType<AlertIncrease>(), "pn"),
				PROTO_OFFSET(DisguiseConfig, alertIncreases), "alertIncreases" },
			{ content::GetArrayDynamicMetaType<DisguiseConfig, AlertDecreaseArray>(
				content::GetClassMetaType<AlertDecrease>(), "pn"),
				PROTO_OFFSET(DisguiseConfig, alertDecreases), "alertDecreases" },
			{ content::GetArrayDynamicMetaType<DisguiseConfig, FactionArray>(
				content::GetClassMetaType<Faction>(), "pn"),
				PROTO_OFFSET(DisguiseConfig, allowedInBase), "allowedInBase" },
			{ content::GetMemberPrimitiveMetaType<DisguiseConfig, bool, 0>("p"),
				PROTO_OFFSET(DisguiseConfig, useDistance), "useDistance" },
			{ content::GetMemberPrimitiveMetaType<DisguiseConfig, float, 1>("p"),
				PROTO_OFFSET(DisguiseConfig, decreaseDelay), "decreaseDelay" }
		};
		sList.members = sMembers;
		sList.count = 26;
		return &sList;
	}

	// FUNCTION: ENGINE 0x103D1310
	double DisguiseConfig::AlertIncrease::GetAlert(int unused)
	{
		return alert;
	}

	// FUNCTION: ENGINE 0x103D1320
	double DisguiseConfig::AlertDecrease::GetAlert(int unused)
	{
		return alert;
	}

	// FUNCTION: ENGINE 0x103D1850
	bool DisguiseConfig::IsAllowedInBase(const core::Name<core::CaseSensitiveKey>& name)
	{
		Faction* last = allowedInBase.end;
		for (Faction* faction = allowedInBase.begin; faction != last; faction++)
		{
			if (faction->name == name)
			{
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x103D4F50
	// NONMATCHING: the engine keeps the end of the array in a register for the search and the size test and
	// loads the begin pointer from memory each time (register allocation, about 35 % of the bytes)
#ifdef NONMATCHING
	void DisguiseConfig::SetSuspicionIncrease(Faction disguiseType, Faction enemyType, float low, float high,
		float minPercent)
	{
		SuspicionIncrease* entry = suspicionIncreases.begin;
		SuspicionIncrease* last = suspicionIncreases.end;
		for (; entry != last; entry++)
		{
			if (entry->disguiseType.name == disguiseType.name && entry->enemyType.name == enemyType.name)
			{
				entry->suspicionLow = low;
				entry->suspicionHigh = high;
				entry->minPercent = minPercent;
				return;
			}
		}
		if (suspicionIncreases.Size() < suspicionIncreases.Capacity())
		{
			SuspicionIncrease entry(disguiseType, enemyType, low, high, minPercent);
			suspicionIncreases.PushBack(entry);
		}
	}
#endif

	// FUNCTION: ENGINE 0x103D5130
	// NONMATCHING: the engine keeps the end of the array in a register for the search and the size test and
	// loads the begin pointer from memory each time (register allocation, about 35 % of the bytes)
#ifdef NONMATCHING
	void DisguiseConfig::SetSuspicionDecrease(Faction disguiseType, float suspicion)
	{
		SuspicionDecrease* entry = suspicionDecreases.begin;
		SuspicionDecrease* last = suspicionDecreases.end;
		for (; entry != last; entry++)
		{
			if (entry->disguiseType.name == disguiseType.name)
			{
				entry->suspicion = suspicion;
				return;
			}
		}
		if (suspicionDecreases.Size() < suspicionDecreases.Capacity())
		{
			SuspicionDecrease entry(disguiseType, suspicion);
			suspicionDecreases.PushBack(entry);
		}
	}
#endif

	// FUNCTION: ENGINE 0x103D5260
	// NONMATCHING: the engine keeps the end of the array in a register for the search and the size test and
	// loads the begin pointer from memory each time (register allocation, about 35 % of the bytes)
#ifdef NONMATCHING
	void DisguiseConfig::SetAlertIncrease(Faction disguiseType, Faction enemyType, float alert)
	{
		AlertIncrease* entry = alertIncreases.begin;
		AlertIncrease* last = alertIncreases.end;
		for (; entry != last; entry++)
		{
			if (entry->disguiseType.name == disguiseType.name && entry->enemyType.name == enemyType.name)
			{
				entry->alert = alert;
				return;
			}
		}
		if (alertIncreases.Size() < alertIncreases.Capacity())
		{
			AlertIncrease entry(disguiseType, enemyType, alert);
			alertIncreases.PushBack(entry);
		}
	}
#endif

	// FUNCTION: ENGINE 0x103D5420
	// NONMATCHING: the engine keeps the end of the array in a register for the search and the size test and
	// loads the begin pointer from memory each time (register allocation, about 35 % of the bytes)
#ifdef NONMATCHING
	void DisguiseConfig::SetAlertDecrease(Faction disguiseType, float alert)
	{
		AlertDecrease* entry = alertDecreases.begin;
		AlertDecrease* last = alertDecreases.end;
		for (; entry != last; entry++)
		{
			if (entry->disguiseType.name == disguiseType.name)
			{
				entry->alert = alert;
				return;
			}
		}
		if (alertDecreases.Size() < alertDecreases.Capacity())
		{
			AlertDecrease entry(disguiseType, alert);
			alertDecreases.PushBack(entry);
		}
	}
#endif

	// FUNCTION: ENGINE 0x103D5A90
	// NONMATCHING: the engine stores the reference count before it takes the address of the first incident (98.7 %)
#ifdef NONMATCHING
	DisguiseConfig::DisguiseConfig() : suspicionIncreases(32), suspicionDecreases(32), alertIncreases(32),
		alertDecreases(32), useDistance(true), decreaseDelay(5.0f)
	{
	}
#endif

	// Not the engine's function (neither annotated nor mapped): it only makes the compiler emit the destructor the
	// matching annotation below belongs to, which no vftable of this unit refers to while the constructor is left to
	// the engine
	void MakeDisguiseConfigDestructor()
	{
		DisguiseConfig config;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x103D5CF0
// FUNCTION: ENGINE 0x103D16E0
// FUNCTION: ENGINE 0x103D16F0
// FUNCTION: ENGINE 0x103D1700
// FUNCTION: ENGINE 0x103D1710
// FUNCTION: ENGINE 0x103D1720
// FUNCTION: ENGINE 0x103D1730
// FUNCTION: ENGINE 0x103D1A40
// FUNCTION: ENGINE 0x103D1A80
// FUNCTION: ENGINE 0x103D1AC0
// FUNCTION: ENGINE 0x103D1B00
// FUNCTION: ENGINE 0x103D1B40
// FUNCTION: ENGINE 0x103D1B80
// FUNCTION: ENGINE 0x103D1BC0
// FUNCTION: ENGINE 0x103D1C00
// FUNCTION: ENGINE 0x103D1C40
// FUNCTION: ENGINE 0x103D1C80
// FUNCTION: ENGINE 0x103D1CC0
// FUNCTION: ENGINE 0x103D1D00
// FUNCTION: ENGINE 0x103D1D40
// FUNCTION: ENGINE 0x103D1D80
// FUNCTION: ENGINE 0x103D1DC0
// FUNCTION: ENGINE 0x103D1E00
// FUNCTION: ENGINE 0x103D1E40
// FUNCTION: ENGINE 0x103D1E80
// FUNCTION: ENGINE 0x103D1F60
// FUNCTION: ENGINE 0x103D2050
// FUNCTION: ENGINE 0x103D2170
// FUNCTION: ENGINE 0x103D2260
// FUNCTION: ENGINE 0x103D2330
// FUNCTION: ENGINE 0x103D31C0
// FUNCTION: ENGINE 0x103D3220
// FUNCTION: ENGINE 0x103D3280
// FUNCTION: ENGINE 0x103D32E0
// FUNCTION: ENGINE 0x103D3340
// FUNCTION: ENGINE 0x103D33A0
// FUNCTION: ENGINE 0x103D3400
// FUNCTION: ENGINE 0x103D3460
// FUNCTION: ENGINE 0x103D34C0
// FUNCTION: ENGINE 0x103D3520
// FUNCTION: ENGINE 0x103D3670
// FUNCTION: ENGINE 0x103D36E0
// FUNCTION: ENGINE 0x103D3A10
// FUNCTION: ENGINE 0x103D3A70
// FUNCTION: ENGINE 0x103D3AF0
// FUNCTION: ENGINE 0x103D3B60
// FUNCTION: ENGINE 0x103D4780
// FUNCTION: ENGINE 0x103D4A00
// FUNCTION: ENGINE 0x103D1F20
// FUNCTION: ENGINE 0x103D1F40
// FUNCTION: ENGINE 0x103D2010
// FUNCTION: ENGINE 0x103D2030
// FUNCTION: ENGINE 0x103D2110
// FUNCTION: ENGINE 0x103D2140
// FUNCTION: ENGINE 0x103D2220
// FUNCTION: ENGINE 0x103D2240
// FUNCTION: ENGINE 0x103D24D0
// FUNCTION: ENGINE 0x103D24F0
// FUNCTION: ENGINE 0x103D2510
// FUNCTION: ENGINE 0x103D2530
// FUNCTION: ENGINE 0x103D2550
// FUNCTION: ENGINE 0x103D2570
// FUNCTION: ENGINE 0x103D2590
// FUNCTION: ENGINE 0x103D25B0
// FUNCTION: ENGINE 0x103D25D0
// FUNCTION: ENGINE 0x103D25F0
// FUNCTION: ENGINE 0x103D2610
// FUNCTION: ENGINE 0x103D2630
// FUNCTION: ENGINE 0x103D56C0
// FUNCTION: ENGINE 0x103D5750
// FUNCTION: ENGINE 0x103D57F0
// FUNCTION: ENGINE 0x103D58A0
// FUNCTION: ENGINE 0x103D58F0
// FUNCTION: ENGINE 0x103D5EA0
// FUNCTION: ENGINE 0x103D6120
// FUNCTION: ENGINE 0x103D4740
// FUNCTION: ENGINE 0x103D5670
// FUNCTION: ENGINE 0x103D5710
// FUNCTION: ENGINE 0x103D57A0
// FUNCTION: ENGINE 0x103D5860
// FUNCTION: ENGINE 0x103D5E20
// FUNCTION: ENGINE 0x103D5F60
// FUNCTION: ENGINE 0x103D6050
// FUNCTION: ENGINE 0x103D2650
// FUNCTION: ENGINE 0x103D2890
// FUNCTION: ENGINE 0x103D3810
// FUNCTION: ENGINE 0x103D38C0
// FUNCTION: ENGINE 0x103D3980
// FUNCTION: ENGINE 0x103D3BC0
// FUNCTION: ENGINE 0x103D3C30
// FUNCTION: ENGINE 0x103D3C80
// FUNCTION: ENGINE 0x103D3CE0
// FUNCTION: ENGINE 0x103D3D30
// FUNCTION: ENGINE 0x103D3DF0
// FUNCTION: ENGINE 0x103D3E60
// FUNCTION: ENGINE 0x103D48F0
// FUNCTION: ENGINE 0x103D4BB0
// FUNCTION: ENGINE 0x103D1330
// FUNCTION: ENGINE 0x103D1350
// FUNCTION: ENGINE 0x103D1360
// FUNCTION: ENGINE 0x103D1380
// FUNCTION: ENGINE 0x103D1390
// FUNCTION: ENGINE 0x103D13A0
// FUNCTION: ENGINE 0x103D13B0
// FUNCTION: ENGINE 0x103D13C0
// FUNCTION: ENGINE 0x103D13D0
// FUNCTION: ENGINE 0x103D13F0
// FUNCTION: ENGINE 0x103D1410
// FUNCTION: ENGINE 0x103D1420
// FUNCTION: ENGINE 0x103D1740
// FUNCTION: ENGINE 0x103D1780
// FUNCTION: ENGINE 0x103D17B0
// FUNCTION: ENGINE 0x103D17F0
// FUNCTION: ENGINE 0x103D1820
// FUNCTION: ENGINE 0x103D1EC0
// FUNCTION: ENGINE 0x103D1ED0
// FUNCTION: ENGINE 0x103D1FE0
// FUNCTION: ENGINE 0x103D1FF0
// FUNCTION: ENGINE 0x103D20D0
// FUNCTION: ENGINE 0x103D20E0
// FUNCTION: ENGINE 0x103D2210
// FUNCTION: ENGINE 0x103D22E0
// FUNCTION: ENGINE 0x103D2320
// FUNCTION: ENGINE 0x103D2390
// FUNCTION: ENGINE 0x103D23B0
// FUNCTION: ENGINE 0x103D23E0
// FUNCTION: ENGINE 0x103D2430
// FUNCTION: ENGINE 0x103D2460
// FUNCTION: ENGINE 0x103D24A0
// FUNCTION: ENGINE 0x103D26E0
// FUNCTION: ENGINE 0x103D2730
// FUNCTION: ENGINE 0x103D2790
// FUNCTION: ENGINE 0x103D2800
// FUNCTION: ENGINE 0x103D2820
// FUNCTION: ENGINE 0x103D2830
// FUNCTION: ENGINE 0x103D2850
// FUNCTION: ENGINE 0x103D2860
// FUNCTION: ENGINE 0x103D2870
// FUNCTION: ENGINE 0x103D2920
// FUNCTION: ENGINE 0x103D2970
// FUNCTION: ENGINE 0x103D29A0
// FUNCTION: ENGINE 0x103D29E0
// FUNCTION: ENGINE 0x103D3580
// FUNCTION: ENGINE 0x103D35D0
// FUNCTION: ENGINE 0x103D3600
// FUNCTION: ENGINE 0x103D3640
// FUNCTION: ENGINE 0x103D36B0
// FUNCTION: ENGINE 0x103D3720
// FUNCTION: ENGINE 0x103D3750
// FUNCTION: ENGINE 0x103D3780
// FUNCTION: ENGINE 0x103D37C0
// FUNCTION: ENGINE 0x103D3870
// FUNCTION: ENGINE 0x103D3920
// FUNCTION: ENGINE 0x103D48A0
// FUNCTION: ENGINE 0x103D49C0
// FUNCTION: ENGINE 0x103D4B60
// FUNCTION: ENGINE 0x103D4CA0
// FUNCTION: ENGINE 0x103D4DD0
// FUNCTION: ENGINE 0x103D4E70
// FUNCTION: ENGINE 0x103D4EC0
// FUNCTION: ENGINE 0x103D5980
// FUNCTION: ENGINE 0x103D5A50
