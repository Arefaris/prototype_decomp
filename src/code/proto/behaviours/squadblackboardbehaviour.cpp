#include "code/proto/behaviours/squadblackboardbehaviour.h"

namespace proto
{
	// FUNCTION: ENGINE 0x103F83B0
	content::ClassInfo* SquadBlackboardBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "SquadBlackboardBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x103F86E0
	SquadBlackboardBehaviour::SquadBlackboardBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner),
		unknown13C(math::kZeroVector), unknown14C(0.0f), unknown150(0)
	{
		Listen(0x27, true);
		Listen(2, true);
	}

	// FUNCTION: ENGINE 0x103F8790
	SquadBlackboardBehaviour::~SquadBlackboardBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x103F85D0
	void SquadBlackboardBehaviour::Reset()
	{
		points.Clear();
		unknown148.index = 0xFFFF;
		unknown148.serial = 0;
	}

	// FUNCTION: ENGINE 0x103F87B0
	void SquadBlackboardBehaviour::Slot1()
	{
		Reset();
	}

	// FUNCTION: ENGINE 0x103F83F0
	void SquadBlackboardBehaviour::Update(float dt, unsigned short mask)
	{
	}

	// FUNCTION: ENGINE 0x103F8550
	content::MemberList* SquadBlackboardBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, SquadBlackboardBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x103F8400
// FUNCTION: ENGINE 0x103F8460
// FUNCTION: ENGINE 0x103F8470
// FUNCTION: ENGINE 0x103F8540
// FUNCTION: ENGINE 0x103F8920

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x103F86D0
