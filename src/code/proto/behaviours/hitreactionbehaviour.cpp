#include "code/proto/behaviours/hitreactionbehaviour.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x102BEAE0
	content::ClassInfo* HitReactionBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::HitReactionBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102BEBD0
	HitReactionBehaviour::HitReactionBehaviour(engine::GameObject* newOwner)
		: engine::HitReactionBehaviour(newOwner), uninterruptible(0), applyImpulse(true)
	{
		Listen(0x14, true);
	}

	// FUNCTION: ENGINE 0x102BF350
	content::MemberList* HitReactionBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::HitReactionBehaviour>();
		static content::BaseClassCasterImpl<engine::HitReactionBehaviour, HitReactionBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<HitReactionBehaviour, bool, 0>("pn"),
				PROTO_OFFSET(HitReactionBehaviour, applyImpulse), "applyImpulse" },
			{ content::GetMemberPrimitiveMetaType<HitReactionBehaviour, int, 0>("pn"),
				PROTO_OFFSET(HitReactionBehaviour, uninterruptible), "uninterruptible" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102BEB70
// FUNCTION: ENGINE 0x102BEC10
// FUNCTION: ENGINE 0x102BEC20
// FUNCTION: ENGINE 0x102BEC50
// FUNCTION: ENGINE 0x102BF2D0
// FUNCTION: ENGINE 0x102BF310
