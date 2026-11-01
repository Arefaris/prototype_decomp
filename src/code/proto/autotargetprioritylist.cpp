#include "code/proto/autotargetprioritylist.h"
#include "code/core/refptr.h"

namespace content
{
	// The values of proto::TargetClass
	static const EnumValue sTargetClassValues[] =
	{
		{ "none", 0 },
		{ "player", 1 },
		{ "dead", 2 },
		{ "prop", 3 },
		{ "vehicle", 4 },
		{ "pedestrian", 5 },
		{ "firearm", 6 },
		{ "alert", 7 },
		{ "unmannedVehicle", 8 },
		{ "groundSpike", 9 },
		{ "protect", 10 },
		{ "civilianWOI", 11 },
		{ "thrownObject", 12 },
		{ "tank", 13 },
		{ "gunship", 14 },
		{ "transportHeli", 15 },
		{ "cop", 16 },
		{ "copCar", 17 },
		{ "rifleSoldier", 18 },
		{ "missileSoldier", 19 },
		{ "commander", 20 },
		{ "jet", 21 },
		{ "uav", 22 },
		{ "sniffer", 23 },
		{ "supersoldier", 24 },
		{ "gunTurret", 25 },
		{ "militaryBase", 26 },
		{ "militaryBaseHighPriority", 27 },
		{ "militarySpawner", 28 },
		{ "bloodtoxBlower", 29 },
		{ "infectedWaterTowerDormant", 30 },
		{ "infectedWaterTowerActive", 31 },
		{ "brawler", 32 },
		{ "leader", 33 },
		{ "infected1", 34 },
		{ "infected2", 35 },
		{ "hydra", 36 },
		{ "hive", 37 },
		{ "hiveHighPriority", 38 },
		{ "infectedSpawner", 39 },
		{ "boss", 40 },
		{ "diversion", 41 },
		{ "markerDestroy", 42 },
		{ "markerConsume", 43 },
		{ "markerWOI", 44 },
		{ "markerRadio", 45 },
		{ "markerConsumeNow", 46 },
		{ "autoMin", 47 },
		{ "autoMax", 48 },
		{ "autoGrabMin", 49 },
		{ "autoGrabMax", 50 },
		{ "autoGroundRanged", 51 },
		{ "autoAirRanged", 52 },
		{ "autoAirRangedMax", 53 }
	};

	// FUNCTION: ENGINE 0x102B4740
	template<> void EnumInfo<proto::TargetClass>::Get(const char** name, const EnumValue** values, int* count,
		const char** code)
	{
		*name = "proto::TargetClass";
		*code = "p";
		*values = sTargetClassValues;
		*count = proto::TARGET_CLASS_COUNT;
	}
}

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x102B4780
	content::ClassInfo* TargetClassPriority::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::AutoTargetPriorityList::TargetClassPriority";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102B47C0
	content::ClassInfo* AutoTargetPriorityList::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::AutoTargetPriorityList";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102B4800
	TargetClassPriority::TargetClassPriority()
	{
		targetClass = 0;
		targetCategory = 0;
		targetPriority = 0;
		maxTargetableDistance = 0.0f;
		maxLockOnTargetableDistance = 0.0f;
		isThreat = false;
		lockOnForbidden = false;
	}

	// FUNCTION: ENGINE 0x102B4F00
	content::MemberList* TargetClassPriority::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetEnumMetaType<TargetClass>(), 0, "targetClass" },
			{ content::GetMemberPrimitiveMetaType<TargetClassPriority, unsigned int, 0>("p"),
				PROTO_OFFSET(TargetClassPriority, targetCategory), "targetCategory" },
			{ content::GetMemberPrimitiveMetaType<TargetClassPriority, unsigned int, 1>("p"),
				PROTO_OFFSET(TargetClassPriority, targetPriority), "targetPriority" },
			{ content::GetMemberPrimitiveMetaType<TargetClassPriority, float, 0>("p"),
				PROTO_OFFSET(TargetClassPriority, maxTargetableDistance), "maxTargetableDistance" },
			{ content::GetMemberPrimitiveMetaType<TargetClassPriority, float, 1>("p"),
				PROTO_OFFSET(TargetClassPriority, maxLockOnTargetableDistance), "maxLockOnTargetableDistance" },
			{ content::GetMemberPrimitiveMetaType<TargetClassPriority, bool, 0>("p"),
				PROTO_OFFSET(TargetClassPriority, isThreat), "isThreat" },
			{ content::GetMemberPrimitiveMetaType<TargetClassPriority, bool, 1>("p"),
				PROTO_OFFSET(TargetClassPriority, lockOnForbidden), "lockOnForbidden" }
		};
		sList.members = sMembers;
		sList.count = 7;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102B54A0
	content::MemberList* AutoTargetPriorityList::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetReferenceMetaType<AutoTargetPriorityList, AutoTargetPriorityList>("p"),
				PROTO_OFFSET(AutoTargetPriorityList, referenceList), "referenceAutoTargetPriorityList" },
			{ content::GetArrayDynamicMetaType<AutoTargetPriorityList, PriorityArray>(
				content::GetClassMetaType<TargetClassPriority>(), "p"),
				PROTO_OFFSET(AutoTargetPriorityList, priorities), "priorities" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102B5670
	// EQUIVALENT: scheduling; the engine saves esi after the second store of the base class's words, ours before it (93.2 %)
	AutoTargetPriorityList::AutoTargetPriorityList() : referenceList(0)
	{
	}

	// FUNCTION: ENGINE 0x102B56C0
	AutoTargetPriorityList::~AutoTargetPriorityList()
	{
		core::SafeRelease(referenceList);
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102B1770
// FUNCTION: ENGINE 0x102B1860
// FUNCTION: ENGINE 0x102B1950
// FUNCTION: ENGINE 0x102B1F50
// FUNCTION: ENGINE 0x102B3F80
// FUNCTION: ENGINE 0x102B4900
// FUNCTION: ENGINE 0x102B49E0
// FUNCTION: ENGINE 0x102B4A20
// FUNCTION: ENGINE 0x102B4A60
// FUNCTION: ENGINE 0x102B4AA0
// FUNCTION: ENGINE 0x102B4AE0
// FUNCTION: ENGINE 0x102B4B20
// FUNCTION: ENGINE 0x102B4B70
// FUNCTION: ENGINE 0x102B4B80
// FUNCTION: ENGINE 0x102B4BE0
// FUNCTION: ENGINE 0x102B4C00
// FUNCTION: ENGINE 0x102B4C90
// FUNCTION: ENGINE 0x102B4CD0
// FUNCTION: ENGINE 0x102B4D20
// FUNCTION: ENGINE 0x102B4D80
// FUNCTION: ENGINE 0x102B4DB0
// FUNCTION: ENGINE 0x102B4DD0
// FUNCTION: ENGINE 0x102B4DF0
// FUNCTION: ENGINE 0x102B4E20
// FUNCTION: ENGINE 0x102B4E90
// FUNCTION: ENGINE 0x102B51B0
// FUNCTION: ENGINE 0x102B5220
// FUNCTION: ENGINE 0x102B5280
// FUNCTION: ENGINE 0x102B52E0
// FUNCTION: ENGINE 0x102B5320
// FUNCTION: ENGINE 0x102B5450
// FUNCTION: ENGINE 0x102B55A0
// FUNCTION: ENGINE 0x102B57F0
