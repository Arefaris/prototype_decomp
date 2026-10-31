#include "code/proto/behaviours/fightvariablesbehaviour.h"

namespace container
{
	template class ArrayDynamic<proto::FightVariableInt, AllocatorNew>;
	template class ArrayDynamic<proto::FightVariableName, AllocatorNew>;
	template class ArrayDynamic<proto::FightTimer, AllocatorNew>;
}

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

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
