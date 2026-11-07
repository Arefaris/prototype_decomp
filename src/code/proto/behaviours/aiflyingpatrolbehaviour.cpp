#include "code/proto/behaviours/aiflyingpatrolbehaviour.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x1042D3B0
	content::ClassInfo* AIFlyingPatrolBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::AIFlyingPatrolBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1042D3F0
	// NONMATCHING: the engine interleaves the constant loads with the stores differently (47 %)
#ifdef NONMATCHING
	AIFlyingPatrolBehaviour::AIFlyingPatrolBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner),
		unknown10(0.0f), unknown14(false), radius(12.0f), brakeAtGoal(true), unknown2C(0.0f), unknown30(250.0f),
		unknown34(0.0f), unknown38(0), unknown3C(false)
	{
		Listen(0x26, true);
	}
#endif

	// FUNCTION: ENGINE 0x1042D470
	AIFlyingPatrolBehaviour::~AIFlyingPatrolBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x1042DAF0
	content::MemberList* AIFlyingPatrolBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, AIFlyingPatrolBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<AIFlyingPatrolBehaviour, float, 0>("pn"),
				PROTO_OFFSET(AIFlyingPatrolBehaviour, radius), "radius" },
			{ content::GetMemberPrimitiveMetaType<AIFlyingPatrolBehaviour, float, 1>("pn"),
				PROTO_OFFSET(AIFlyingPatrolBehaviour, startVelocity), "startVelocity" },
			{ content::GetMemberPrimitiveMetaType<AIFlyingPatrolBehaviour, bool, 0>("pn"),
				PROTO_OFFSET(AIFlyingPatrolBehaviour, brakeAtGoal), "brakeAtGoal" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}
}


// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1042D600
// FUNCTION: ENGINE 0x1042D610
// FUNCTION: ENGINE 0x1042D640
// FUNCTION: ENGINE 0x1042DA30
// FUNCTION: ENGINE 0x1042DA70
// FUNCTION: ENGINE 0x1042DAB0
