#include "code/proto/behaviours/randomdeadpedbehaviour.h"

namespace proto
{
	// FUNCTION: ENGINE 0x10432ED0
	content::ClassInfo* RandomDeadPedBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::RandomDeadPedBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10433150
	RandomDeadPedBehaviour::RandomDeadPedBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner)
	{
	}

	// FUNCTION: ENGINE 0x10433170
	RandomDeadPedBehaviour::~RandomDeadPedBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x10438940
	content::MemberList* RandomDeadPedBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, RandomDeadPedBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102C0B20
