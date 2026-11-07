#include "code/proto/behaviours/powerwheelbehaviour.h"

namespace proto
{
	// FUNCTION: ENGINE 0x104C0100
	content::ClassInfo* PowerWheelBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::PowerWheelBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x104C0140
	PowerWheelBehaviour::PowerWheelBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner)
	{
		active = false;
		Listen(0x36, true);
		Listen2(4, true);
	}

	// FUNCTION: ENGINE 0x104C0180
	PowerWheelBehaviour::~PowerWheelBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x104C0190
	void PowerWheelBehaviour::Slot1()
	{
	}

	// FUNCTION: ENGINE 0x104C01A0
	void PowerWheelBehaviour::SetActive(SetPowerWheelActiveMessage* message)
	{
		active = message->active;
	}

	// FUNCTION: ENGINE 0x104C0220
	void PowerWheelBehaviour::OnMessage(engine::Message* message)
	{
		if (message->type == 0x36 && message->id == 0)
		{
			SetActive((SetPowerWheelActiveMessage*)message);
		}
	}

	// FUNCTION: ENGINE 0x104C0310
	content::MemberList* PowerWheelBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, PowerWheelBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x104C01B0
// FUNCTION: ENGINE 0x104C01C0
// FUNCTION: ENGINE 0x104C01F0
