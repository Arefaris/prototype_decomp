#include "code/proto/behaviours/fightvariablesbehaviour.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10068C20
	FightVariablesBehaviour::FightVariablesBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner),
		outOfCombatTimer(0.0f)
	{
		Listen(0x23, true);
		Listen(2, true);
		Listen(0x39, true);
		Listen2(8, true);
	}

	// FUNCTION: ENGINE 0x10068CB0
	FightVariablesBehaviour::~FightVariablesBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x10065D60
	content::ClassInfo* FightVariableInt::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::FightVariableInt";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10065DA0
	content::ClassInfo* FightVariableName::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::FightVariableName";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10065DE0
	content::ClassInfo* FightTimer::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::FightTimer";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10065E20
	content::ClassInfo* FightVariablesBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::FightVariablesBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x100662C0
	content::MemberList* FightVariableName::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<FightVariableName>(true, true, "p"), PROTO_NAME_OFFSET(FightVariableName, name),
				"name" },
			{ content::GetNameMetaTypeCopy<FightVariableName>(true, true, "p"),
				PROTO_NAME_OFFSET(FightVariableName, value), "value" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10067A90
	content::MemberList* FightVariableInt::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<FightVariableInt>(true, true, "p"), PROTO_NAME_OFFSET(FightVariableInt, name),
				"name" },
			{ content::GetMemberPrimitiveMetaType<FightVariableInt, int, 0>("p"),
				PROTO_OFFSET(FightVariableInt, value), "value" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10067B60
	content::MemberList* FightTimer::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<FightTimer>(true, true, "p"), PROTO_NAME_OFFSET(FightTimer, name), "name" },
			{ content::GetMemberPrimitiveMetaType<FightTimer, float, 0>("p"), PROTO_OFFSET(FightTimer, time),
				"time" },
			{ content::GetMemberPrimitiveMetaType<FightTimer, bool, 0>("p"),
				PROTO_OFFSET(FightTimer, incrementing), "incrementing" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10068370
	content::MemberList* FightVariablesBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, FightVariablesBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<FightVariablesBehaviour, IntArray>(
				content::GetClassMetaType<FightVariableInt>(), "p"),
				PROTO_OFFSET(FightVariablesBehaviour, varInts), "varInts" },
			{ content::GetArrayDynamicMetaType<FightVariablesBehaviour, NameArray>(
				content::GetClassMetaType<FightVariableName>(), "p"),
				PROTO_OFFSET(FightVariablesBehaviour, varNames), "varNames" },
			{ content::GetArrayDynamicMetaType<FightVariablesBehaviour, TimerArray>(
				content::GetClassMetaType<FightTimer>(), "p"),
				PROTO_OFFSET(FightVariablesBehaviour, timers), "timers" },
			{ content::GetMemberPrimitiveMetaType<FightVariablesBehaviour, float, 0>("p"),
				PROTO_OFFSET(FightVariablesBehaviour, outOfCombatTimer), "outOfCombatTimer" }
		};
		sList.members = sMembers;
		sList.count = 4;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10065E90
// FUNCTION: ENGINE 0x10065EC0
// FUNCTION: ENGINE 0x10065F20
// FUNCTION: ENGINE 0x10065FC0
// FUNCTION: ENGINE 0x10066050
// FUNCTION: ENGINE 0x100660D0
// FUNCTION: ENGINE 0x100660E0
// FUNCTION: ENGINE 0x10066120
// FUNCTION: ENGINE 0x10066130
// FUNCTION: ENGINE 0x10066170
// FUNCTION: ENGINE 0x100661B0
// FUNCTION: ENGINE 0x100661F0
// FUNCTION: ENGINE 0x10066200
// FUNCTION: ENGINE 0x10066210
// FUNCTION: ENGINE 0x10066220
// FUNCTION: ENGINE 0x10066230
// FUNCTION: ENGINE 0x10066240
// FUNCTION: ENGINE 0x10066250
// FUNCTION: ENGINE 0x10066260
// FUNCTION: ENGINE 0x10066280
// FUNCTION: ENGINE 0x100662A0
// FUNCTION: ENGINE 0x100663A0
// FUNCTION: ENGINE 0x100663B0
// FUNCTION: ENGINE 0x10067130
// FUNCTION: ENGINE 0x10067190
// FUNCTION: ENGINE 0x100671D0
// FUNCTION: ENGINE 0x10067210
// FUNCTION: ENGINE 0x10067250
// FUNCTION: ENGINE 0x10067290
// FUNCTION: ENGINE 0x100672A0
// FUNCTION: ENGINE 0x100672C0
// FUNCTION: ENGINE 0x100672E0
// FUNCTION: ENGINE 0x10067300
// FUNCTION: ENGINE 0x10067360
// FUNCTION: ENGINE 0x10067380
// FUNCTION: ENGINE 0x100673B0
// FUNCTION: ENGINE 0x100673E0
// FUNCTION: ENGINE 0x10067410
// FUNCTION: ENGINE 0x10067420
// FUNCTION: ENGINE 0x10067450
// FUNCTION: ENGINE 0x10067470
// FUNCTION: ENGINE 0x10067490
// FUNCTION: ENGINE 0x100674F0
// FUNCTION: ENGINE 0x10067520
// FUNCTION: ENGINE 0x10067550
// FUNCTION: ENGINE 0x10067580
// FUNCTION: ENGINE 0x100675B0
// FUNCTION: ENGINE 0x100675C0
// FUNCTION: ENGINE 0x100675E0
// FUNCTION: ENGINE 0x10067600
// FUNCTION: ENGINE 0x10067620
// FUNCTION: ENGINE 0x10067680
// FUNCTION: ENGINE 0x100676A0
// FUNCTION: ENGINE 0x100676D0
// FUNCTION: ENGINE 0x10067700
// FUNCTION: ENGINE 0x10067730
// FUNCTION: ENGINE 0x10067750
// FUNCTION: ENGINE 0x10067780
// FUNCTION: ENGINE 0x100677A0
// FUNCTION: ENGINE 0x100677B0
// FUNCTION: ENGINE 0x100677C0
// FUNCTION: ENGINE 0x100677D0
// FUNCTION: ENGINE 0x10067800
// FUNCTION: ENGINE 0x10067850
// FUNCTION: ENGINE 0x10067890
// FUNCTION: ENGINE 0x100678F0
// FUNCTION: ENGINE 0x10067920
// FUNCTION: ENGINE 0x100679D0
// FUNCTION: ENGINE 0x10067DD0
// FUNCTION: ENGINE 0x10067E30
// FUNCTION: ENGINE 0x10067E90
// FUNCTION: ENGINE 0x10067EF0
// FUNCTION: ENGINE 0x10067F50
// FUNCTION: ENGINE 0x10067FE0
// FUNCTION: ENGINE 0x10068010
// FUNCTION: ENGINE 0x10068040
// FUNCTION: ENGINE 0x10068530
// FUNCTION: ENGINE 0x10068560
// FUNCTION: ENGINE 0x100685A0
// FUNCTION: ENGINE 0x100685D0
// FUNCTION: ENGINE 0x100686D0
// FUNCTION: ENGINE 0x10068800
// FUNCTION: ENGINE 0x10068950
// FUNCTION: ENGINE 0x10068A50
// FUNCTION: ENGINE 0x10068AA0
// FUNCTION: ENGINE 0x10068B10
// FUNCTION: ENGINE 0x10068D10
// FUNCTION: ENGINE 0x10068DF0
// FUNCTION: ENGINE 0x10068EE0

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10067100
// FUNCTION: ENGINE 0x10067110
// FUNCTION: ENGINE 0x10067120
// FUNCTION: ENGINE 0x10068250
// FUNCTION: ENGINE 0x100682B0
// FUNCTION: ENGINE 0x10068310
// FUNCTION: ENGINE 0x100689F0
// FUNCTION: ENGINE 0x10068A10
// FUNCTION: ENGINE 0x10068A30
// FUNCTION: ENGINE 0x10068FC0
