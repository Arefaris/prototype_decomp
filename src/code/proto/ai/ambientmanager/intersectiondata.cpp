#include "code/proto/ai/ambientmanager/intersectiondata.h"
#include "code/proto/ai/ambientmanager/ambientenums.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10430670
	content::ClassInfo* IntersectionData::Phase::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::IntersectionData::Phase";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x104306F0
	content::ClassInfo* IntersectionSpawner::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::IntersectionSpawner";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x104318E0
	content::MemberList* IntersectionData::Phase::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<Phase, StateArray>(content::GetEnumMetaType<State>(), "p"),
				PROTO_OFFSET(Phase, states), "stateArray" },
			{ content::GetMemberPrimitiveMetaType<Phase, float, 0>("pn"),
				PROTO_OFFSET(Phase, duration), "phaseLength" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10431C20
	content::MemberList* IntersectionData::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<IntersectionData>(true, true, "p"),
				content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((IntersectionData*)0)->name,
					(int)&((IntersectionData*)0)->name), "name" },
			{ content::GetArrayDynamicMetaType<IntersectionData, PhaseArray>(
				content::GetClassMetaType<Phase>(), "p"), PROTO_OFFSET(IntersectionData, phases), "phases" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10431FC0
	content::MemberList* IntersectionSpawner::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<IntersectionSpawner, DataArray>(
				content::GetClassMetaType<IntersectionData>(), "p"),
				PROTO_OFFSET(IntersectionSpawner, intersectionData), "intersectionData" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}
}


// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10430730
// FUNCTION: ENGINE 0x10430740
// FUNCTION: ENGINE 0x104307D0
// FUNCTION: ENGINE 0x104307F0
// FUNCTION: ENGINE 0x10430830
// FUNCTION: ENGINE 0x10430870
// FUNCTION: ENGINE 0x104308F0
// FUNCTION: ENGINE 0x10430900
// FUNCTION: ENGINE 0x10430940
// FUNCTION: ENGINE 0x10430950
// FUNCTION: ENGINE 0x10430C40
// FUNCTION: ENGINE 0x10430C80
// FUNCTION: ENGINE 0x10430C90
// FUNCTION: ENGINE 0x10430CB0
// FUNCTION: ENGINE 0x10430CD0
// FUNCTION: ENGINE 0x10430D10
// FUNCTION: ENGINE 0x10430D30
// FUNCTION: ENGINE 0x10430D90
// FUNCTION: ENGINE 0x10430DA0
// FUNCTION: ENGINE 0x10430DD0
// FUNCTION: ENGINE 0x10430DF0
// FUNCTION: ENGINE 0x10430E60
// FUNCTION: ENGINE 0x10430EA0
// FUNCTION: ENGINE 0x10430EE0
// FUNCTION: ENGINE 0x10430EF0
// FUNCTION: ENGINE 0x10430F20
// FUNCTION: ENGINE 0x10430F40
// FUNCTION: ENGINE 0x10430FB0
// FUNCTION: ENGINE 0x10430FD0
// FUNCTION: ENGINE 0x10430FF0
// FUNCTION: ENGINE 0x10431010
// FUNCTION: ENGINE 0x10431040
// FUNCTION: ENGINE 0x10431060
// FUNCTION: ENGINE 0x10431090
// FUNCTION: ENGINE 0x104310F0
// FUNCTION: ENGINE 0x10431130
// FUNCTION: ENGINE 0x10431190
// FUNCTION: ENGINE 0x104315F0
// FUNCTION: ENGINE 0x10431650
// FUNCTION: ENGINE 0x104316B0
// FUNCTION: ENGINE 0x10431710
// FUNCTION: ENGINE 0x10431760
// FUNCTION: ENGINE 0x10431880
// FUNCTION: ENGINE 0x104318B0
// FUNCTION: ENGINE 0x10431A10
// FUNCTION: ENGINE 0x10431AB0
// FUNCTION: ENGINE 0x10431AE0
// FUNCTION: ENGINE 0x10431B80
// FUNCTION: ENGINE 0x10432070
// FUNCTION: ENGINE 0x10432160
// FUNCTION: ENGINE 0x10432200
// FUNCTION: ENGINE 0x10432250
// FUNCTION: ENGINE 0x10432420
// FUNCTION: ENGINE 0x10432450
// FUNCTION: ENGINE 0x104324C0
// FUNCTION: ENGINE 0x10432510
// FUNCTION: ENGINE 0x10432540
// FUNCTION: ENGINE 0x104325A0
// FUNCTION: ENGINE 0x104327B0
// FUNCTION: ENGINE 0x104328B0
// FUNCTION: ENGINE 0x104329E0
// FUNCTION: ENGINE 0x10432A30
// FUNCTION: ENGINE 0x10432AE0
