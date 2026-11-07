#include "code/proto/behaviours/squadmemberbehaviour.h"

namespace proto
{
	// FUNCTION: ENGINE 0x103F9DD0
	content::ClassInfo* SquadMemberBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "SquadMemberBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x103F9E10
	SquadMemberBehaviour::SquadMemberBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner)
	{
		Listen(0x27, true);
		Listen(2, true);
		Listen(0x2f, true);
		Listen(0x39, true);
		Listen(0x14, true);
	}

	// FUNCTION: ENGINE 0x103F9E80
	SquadMemberBehaviour::~SquadMemberBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x103F9E90
	void SquadMemberBehaviour::Slot1()
	{
	}

	// FUNCTION: ENGINE 0x103F9EA0
	void SquadMemberBehaviour::Update(float dt, unsigned short mask)
	{
	}

	// FUNCTION: ENGINE 0x103F9FC0
	content::MemberList* SquadMemberBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, SquadMemberBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x103F9F50
// FUNCTION: ENGINE 0x103F9F60
// FUNCTION: ENGINE 0x103F9F90
