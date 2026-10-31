#include "code/proto/behaviours/chargebehaviour.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/fight/fighteventmessage.h"
#include "code/proto/fightitems/motion/motionmessages.h"
#include "code/proto/smarthint/smarthintmanager.h"

namespace engine
{
	namespace driving
	{
		extern const float gOne;
	}
}

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x100643E0
	content::ClassInfo* ChargeBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::ChargeBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10064420
	ChargeBehaviour::ChargeBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner)
	{
		charge = 0.0f;
		chargeType = 1;
		Listen(2, true);
		Listen(0x1c, true);
	}

	// FUNCTION: ENGINE 0x10064470
	ChargeBehaviour::~ChargeBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x10064480
	void ChargeBehaviour::Add(ChargeMessage* message)
	{
		if (message->chargeType != 0 && message->chargeType != chargeType)
		{
			chargeType = message->chargeType;
			charge = 0.0f;
		}
		float old = charge;
		float value = message->value;
		float sum = value + old;
		float one = engine::driving::gOne;
		charge = sum;
		if (one > old && sum >= one)
		{
			switch (chargeType)
			{
			case 1:
				gSmartHintManager->SetTimer(10, 0.0f);
				break;
			case 2:
				gSmartHintManager->SetTimer(9, 0.0f);
				break;
			}
			engine::FightEventMessage event(0x10000);
			owner->SendMessage(&event);
		}
		else if (old > 0.0f && sum <= 0.0f)
		{
			engine::FightEventMessage event(0x10000);
			owner->SendMessage(&event);
		}
	}

	// FUNCTION: ENGINE 0x10064580
	void ChargeBehaviour::Get(ChargeMessage* message)
	{
		if (message->chargeType != 0 && chargeType != message->chargeType)
		{
			message->value = 0.0f;
			return;
		}
		message->value = charge;
	}

	// FUNCTION: ENGINE 0x100645B0
	void ChargeBehaviour::Set(ChargeMessage* message)
	{
		if (charge != message->value)
		{
			engine::FightEventMessage event(0x10000);
			owner->SendMessage(&event);
		}
		charge = message->value;
		if (message->chargeType != 0)
		{
			chargeType = message->chargeType;
		}
	}

	// FUNCTION: ENGINE 0x10064630
	void ChargeBehaviour::Reset()
	{
		charge = 0.0f;
		chargeType = 1;
	}

	// FUNCTION: ENGINE 0x100646F0
	void ChargeBehaviour::Eat(ChargeMessage* message)
	{
		Get(message);
		if (charge != 0.0f)
		{
			engine::FightEventMessage event(0x10000);
			owner->SendMessage(&event);
		}
		charge = 0.0f;
	}

	// FUNCTION: ENGINE 0x10064770
	void ChargeBehaviour::OnMessage(engine::Message* message)
	{
		switch (message->type)
		{
		case 2:
			Reset();
			break;
		case 0x1c:
			switch ((unsigned short)message->id)
			{
			case 0:
				Add(static_cast<ChargeMessage*>(message));
				break;
			case 1:
				Eat(static_cast<ChargeMessage*>(message));
				break;
			case 2:
				Get(static_cast<ChargeMessage*>(message));
				break;
			case 3:
				Set(static_cast<ChargeMessage*>(message));
				break;
			}
			break;
		}
	}

	// FUNCTION: ENGINE 0x10064830
	content::MemberList* ChargeBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, ChargeBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<ChargeBehaviour, float, 0>("pn"),
				PROTO_OFFSET(ChargeBehaviour, charge), "charge" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10064380
// FUNCTION: ENGINE 0x100643B0
// FUNCTION: ENGINE 0x10064650
// FUNCTION: ENGINE 0x10064680
// FUNCTION: ENGINE 0x10064690
// FUNCTION: ENGINE 0x100646C0
// FUNCTION: ENGINE 0x100647F0
