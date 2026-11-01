#include "code/proto/behaviours/targetingbehaviour.h"
#include "code/proto/fightitems/ai/aimessages.h"

namespace proto
{
	// The message that names the target to take (type 0x20, id 2)
	class SetTargetMessage : public TargetMessage
	{
	public:
		explicit SetTargetMessage(engine::GameObjectHandle newTarget) : TargetMessage(2), target(newTarget)
		{
		}
		virtual ~SetTargetMessage()
		{
		}

		engine::GameObjectHandle target;  // +0xC
	};

	// FUNCTION: ENGINE 0x102B4500
	content::ClassInfo* TargetingBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::TargetingBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102B4540
	TargetingBehaviour::TargetingBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner)
	{
		Listen(0x20, true);
		Listen(2, true);
	}

	// FUNCTION: ENGINE 0x102B4590
	TargetingBehaviour::~TargetingBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x102B45A0
	void TargetingBehaviour::ClearTarget()
	{
		target = engine::GameObjectHandle();
	}

	// FUNCTION: ENGINE 0x102B45C0
	void TargetingBehaviour::SetTarget(const engine::GameObjectHandle* newTarget)
	{
		target = *newTarget;
	}

	// FUNCTION: ENGINE 0x102B45D0
	void TargetingBehaviour::GetTarget(GetTargetMessage* message)
	{
		message->target = target;
	}

	// FUNCTION: ENGINE 0x102B45E0
	void TargetingBehaviour::OnSetTarget(SetTargetMessage* message)
	{
		SetTarget(&message->target);
	}

	// FUNCTION: ENGINE 0x102B4670
	void TargetingBehaviour::OnMessage(engine::Message* message)
	{
		switch (message->type)
		{
		case 2:
			ClearTarget();
			break;
		case 0x20:
			switch ((unsigned short)message->id)
			{
			case 0:
				GetTarget((GetTargetMessage*)message);
				return;
			case 2:
				OnSetTarget((SetTargetMessage*)message);
				return;
			}
		}
	}

	// FUNCTION: ENGINE 0x102B46C0
	content::MemberList* TargetingBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, TargetingBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102B4600
// FUNCTION: ENGINE 0x102B4610
// FUNCTION: ENGINE 0x102B4640

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102A83D0
// FUNCTION: ENGINE 0x102A8410
