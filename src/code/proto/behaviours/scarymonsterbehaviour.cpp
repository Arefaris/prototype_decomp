#include "code/proto/behaviours/scarymonsterbehaviour.h"

namespace proto
{
	extern const float gTen;

#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x103F7F80
	content::ClassInfo* ScaryMonsterBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::ScaryMonsterBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x103F7FC0
	ScaryMonsterBehaviour::ScaryMonsterBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner),
		intensity(10.0f), unknown10(0.0f)
	{
		Listen(0x26, true);
	}

	// FUNCTION: ENGINE 0x103F8010
	ScaryMonsterBehaviour::~ScaryMonsterBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x103F8020
	void ScaryMonsterBehaviour::Slot1()
	{
		Listen2(4, true);
		Remove(10);
	}

	// FUNCTION: ENGINE 0x103F8040
	void ScaryMonsterBehaviour::OnMessage(engine::Message* message)
	{
		if (message->type == 0x26)
		{
			switch ((unsigned short)message->id)
			{
			case 0x40:
				OnActiveChanged(static_cast<ScaryMonsterActiveMessage*>(message)->active);
				break;
			case 0x41:
				Remove(static_cast<ScaryMonsterParamsMessage*>(message)->frameSkip);
				intensity = static_cast<ScaryMonsterParamsMessage*>(message)->intensity;
				unknown10 = static_cast<ScaryMonsterParamsMessage*>(message)->unknown10;
				break;
			}
		}
	}

	// FUNCTION: ENGINE 0x103F82E0
	content::MemberList* ScaryMonsterBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, ScaryMonsterBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<ScaryMonsterBehaviour, float, 0>("p"),
				PROTO_OFFSET(ScaryMonsterBehaviour, intensity), "intensity" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x103F80A0
// FUNCTION: ENGINE 0x103F80B0
// FUNCTION: ENGINE 0x103F80E0
// FUNCTION: ENGINE 0x103F82A0
