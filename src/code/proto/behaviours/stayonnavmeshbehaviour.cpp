#include "code/proto/behaviours/stayonnavmeshbehaviour.h"

namespace proto
{
	// FUNCTION: ENGINE 0x103FA8F0
	content::ClassInfo* StayOnNavmeshBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::StayOnNavmeshBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x103FA930
	StayOnNavmeshBehaviour::StayOnNavmeshBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner),
		unknown18(false), enabled(false), unknown1C(1.0f), unknown20(0)
	{
		Listen(0x26, true);
	}

	// FUNCTION: ENGINE 0x103FA980
	StayOnNavmeshBehaviour::~StayOnNavmeshBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x103FA990
	void StayOnNavmeshBehaviour::Slot1()
	{
		Listen2(0x10, true);
		Listen2(0x40, true);
	}

	// FUNCTION: ENGINE 0x103FA9B0
	void StayOnNavmeshBehaviour::OnMessage(engine::Message* message)
	{
		if (message->type == 0x26 && (unsigned short)message->id == 0x59)
		{
			enabled = static_cast<StayOnNavmeshEnableMessage*>(message)->enabled;
		}
	}

	// FUNCTION: ENGINE 0x103FAFA0
	content::MemberList* StayOnNavmeshBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, StayOnNavmeshBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x103FAA80
// FUNCTION: ENGINE 0x103FAA90
// FUNCTION: ENGINE 0x103FAAC0
