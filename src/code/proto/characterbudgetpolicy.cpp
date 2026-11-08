#include "code/proto/characterbudgetpolicy.h"
#include <math.h>

namespace container
{
	template<> inline void ConstructCopyAt<proto::CharacterBudgetPolicy>(proto::CharacterBudgetPolicy* p,
		const proto::CharacterBudgetPolicy& value)
	{
		if (p != 0)
		{
			new (&p->className) core::Name<core::CaseSensitiveKey>(value.className);
			p->despawnDistanceSquared = value.despawnDistanceSquared;
			p->freezeDistanceSquared = value.freezeDistanceSquared;
			p->priority = value.priority;
			p->weight = value.weight;
			p->weightLOD2 = value.weightLOD2;
			p->weightLOD3 = value.weightLOD3;
			p->needsLoadedCell = value.needsLoadedCell;
		}
	}
}

namespace proto
{
	// The squares of the distances a new policy starts with (data of the engine, names guessed)
	float gDefaultFreezeDistanceSquared = 10000.0f;
	float gDefaultDespawnDistanceSquared = 40000.0f;

#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10385AE0
	content::ClassInfo* CharacterBudgetPolicy::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::CharacterBudgetPolicy";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10385B20
	content::ClassInfo* CharacterBudgetPolicyList::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::CharacterBudgetPolicyList";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10386880
	CharacterBudgetPolicy::CharacterBudgetPolicy() : className("", 1)
	{
		despawnDistanceSquared = gDefaultDespawnDistanceSquared;
		freezeDistanceSquared = gDefaultFreezeDistanceSquared;
		priority = 0;
		weight = 1;
		weightLOD2 = 1;
		weightLOD3 = 1;
		needsLoadedCell = true;
	}

	// FUNCTION: ENGINE 0x10385E20
	float CharacterBudgetPolicy::GetDespawnDistance() const
	{
		return sqrtf(despawnDistanceSquared);
	}

	// FUNCTION: ENGINE 0x103868F0
	void CharacterBudgetPolicy::SetDespawnDistance(float distance)
	{
		despawnDistanceSquared = distance * distance;
	}

	// FUNCTION: ENGINE 0x10385E40
	float CharacterBudgetPolicy::GetFreezeDistance() const
	{
		return sqrtf(freezeDistanceSquared);
	}

	// FUNCTION: ENGINE 0x10386910
	void CharacterBudgetPolicy::SetFreezeDistance(float distance)
	{
		freezeDistanceSquared = distance * distance;
	}

	// FUNCTION: ENGINE 0x10387DB0
	content::MemberList* CharacterBudgetPolicy::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<CharacterBudgetPolicy>(true, true, "p"),
				PROTO_OFFSET(CharacterBudgetPolicy, className), "className" },
			{ content::GetMemberMetaType<CharacterBudgetPolicy, float, 0>(&CharacterBudgetPolicy::GetDespawnDistance,
				&CharacterBudgetPolicy::SetDespawnDistance, "p"), 0, "despawnDistance" },
			{ content::GetMemberMetaType<CharacterBudgetPolicy, float, 1>(&CharacterBudgetPolicy::GetFreezeDistance,
				&CharacterBudgetPolicy::SetFreezeDistance, "p"), 0, "freezeDistance" },
			{ content::GetMemberPrimitiveMetaType<CharacterBudgetPolicy, int, 0>("p"),
				PROTO_OFFSET(CharacterBudgetPolicy, priority), "priority" },
			{ content::GetMemberPrimitiveMetaType<CharacterBudgetPolicy, int, 1>("p"),
				PROTO_OFFSET(CharacterBudgetPolicy, weight), "weight" },
			{ content::GetMemberPrimitiveMetaType<CharacterBudgetPolicy, int, 2>("p"),
				PROTO_OFFSET(CharacterBudgetPolicy, weightLOD2), "weightLOD2" },
			{ content::GetMemberPrimitiveMetaType<CharacterBudgetPolicy, int, 3>("p"),
				PROTO_OFFSET(CharacterBudgetPolicy, weightLOD3), "weightLOD3" },
			{ content::GetMemberPrimitiveMetaType<CharacterBudgetPolicy, bool, 0>("p"),
				PROTO_OFFSET(CharacterBudgetPolicy, needsLoadedCell), "needsLoadedCell" }
		};
		sList.members = sMembers;
		sList.count = 8;
		return &sList;
	}

	// FUNCTION: ENGINE 0x103887B0
	content::MemberList* CharacterBudgetPolicyList::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<CharacterBudgetPolicyList, PolicyArray>(
				content::GetClassMetaType<CharacterBudgetPolicy>(), "p"),
				PROTO_OFFSET(CharacterBudgetPolicyList, policies), "policies" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10389680
	CharacterBudgetPolicyList::CharacterBudgetPolicyList()
	{
	}

	// FUNCTION: ENGINE 0x103896B0
	CharacterBudgetPolicyList::~CharacterBudgetPolicyList()
	{
	}
}

namespace
{
	typedef container::ArrayDynamic<proto::CharacterBudgetPolicy, container::AllocatorNew> PolicyArrayInstance;
}

template PolicyArrayInstance::ArrayDynamic(unsigned int);
template PolicyArrayInstance::ArrayDynamic(unsigned int, const container::AllocatorNew&);
template PolicyArrayInstance::ArrayDynamic(const PolicyArrayInstance&);
template PolicyArrayInstance& PolicyArrayInstance::operator=(const PolicyArrayInstance&);
template proto::CharacterBudgetPolicy* PolicyArrayInstance::Begin();
template proto::CharacterBudgetPolicy* PolicyArrayInstance::End();
template proto::CharacterBudgetPolicy& PolicyArrayInstance::operator[](int);
template const proto::CharacterBudgetPolicy& PolicyArrayInstance::operator[](int) const;
template bool PolicyArrayInstance::Create(unsigned int);
template void PolicyArrayInstance::Clear();
template bool PolicyArrayInstance::PushBack(const proto::CharacterBudgetPolicy&);
template void PolicyArrayInstance::Free();
template proto::CharacterBudgetPolicy* PolicyArrayInstance::Grow();
template void PolicyArrayInstance::Erase(proto::CharacterBudgetPolicy*, proto::CharacterBudgetPolicy*);
template void PolicyArrayInstance::Resize(unsigned int, const proto::CharacterBudgetPolicy&);


// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10385F90
// FUNCTION: ENGINE 0x10385FB0
// FUNCTION: ENGINE 0x10386000
// FUNCTION: ENGINE 0x10386020
// FUNCTION: ENGINE 0x103860A0
// FUNCTION: ENGINE 0x10386120
// FUNCTION: ENGINE 0x103861A0
// FUNCTION: ENGINE 0x103861B0
// FUNCTION: ENGINE 0x103861F0
// FUNCTION: ENGINE 0x10386260
// FUNCTION: ENGINE 0x10386330
// FUNCTION: ENGINE 0x10386400
// FUNCTION: ENGINE 0x10386990
// FUNCTION: ENGINE 0x10386AC0
// FUNCTION: ENGINE 0x10386B00
// FUNCTION: ENGINE 0x10386B40
// FUNCTION: ENGINE 0x10386B80
// FUNCTION: ENGINE 0x10386BC0
// FUNCTION: ENGINE 0x10386CC0
// FUNCTION: ENGINE 0x10386CD0
// FUNCTION: ENGINE 0x10386D00
// FUNCTION: ENGINE 0x10386D20
// FUNCTION: ENGINE 0x10386D80
// FUNCTION: ENGINE 0x10386DB0
// FUNCTION: ENGINE 0x10386DD0
// FUNCTION: ENGINE 0x10386E30
// FUNCTION: ENGINE 0x10386FB0
// FUNCTION: ENGINE 0x10386FD0
// FUNCTION: ENGINE 0x10386FF0
// FUNCTION: ENGINE 0x10387010
// FUNCTION: ENGINE 0x10387030
// FUNCTION: ENGINE 0x10387060
// FUNCTION: ENGINE 0x103870E0
// FUNCTION: ENGINE 0x10387B70
// FUNCTION: ENGINE 0x10387BF0
// FUNCTION: ENGINE 0x10387C70
// FUNCTION: ENGINE 0x103886C0
// FUNCTION: ENGINE 0x10388730
// FUNCTION: ENGINE 0x10388B50
// FUNCTION: ENGINE 0x10388B60
// FUNCTION: ENGINE 0x10388BA0
// FUNCTION: ENGINE 0x10388D00
// FUNCTION: ENGINE 0x10389080
// FUNCTION: ENGINE 0x103890C0
// FUNCTION: ENGINE 0x103896E0
// FUNCTION: ENGINE 0x10389820
