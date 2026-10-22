#include "code/engine/hitreactionbehaviour.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/physics/applyimpulsemessage.h"
#include "code/engine/physics/getphysicsobjectmessage.h"
#include "code/ravenphysics/collision/collisionobject.h"
#include "code/ravenphysics/physicsobject.h"

namespace engine
{
#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10848820
	content::ClassInfo* HitReactionBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::HitReactionBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10848860
	HitReactionBehaviour::HitReactionBehaviour(GameObject* newOwner) : Behaviour(newOwner)
	{
		impulseScale = 1.0f;
		Listen(0x14, true);
		Listen(6, true);
	}

	// FUNCTION: ENGINE 0x108488A0
	void HitReactionBehaviour::Slot1()
	{
	}

	// FUNCTION: ENGINE 0x108488B0
	// EQUIVALENT: the same products and stores, the engine computes the impulse's y first and the x as scale * x, ours x, y, z each as the component times the scale (a commutative product), 51.4 %
	void HitReactionBehaviour::OnHit(HitMessage* message)
	{
		if (message->applyDamage)
		{
			ApplyDamageMessage damage(message->damage);
			owner->SendMessage(&damage);
		}
		float scale = impulseScale;
		math::Vector impulse(message->direction->x * scale, message->direction->y * scale,
			message->direction->z * scale);
		ApplyImpulseMessage push(impulse, *message->position);
		owner->SendMessage(&push);
	}

	// FUNCTION: ENGINE 0x108489F0
	void HitReactionBehaviour::OnPhysicsFilterOn(PhysicsFilterMessage* message)
	{
		if (message->flag)
		{
			if (message->handle.IsValid())
			{
				message->handle.GetObject()->SetFilterBits(0x20, true);
				message->handle.GetObject()->SetFilterBits2(0x200, true);
			}
		}
	}

	// FUNCTION: ENGINE 0x10848A50
	void HitReactionBehaviour::OnPhysicsFilterSwitch(PhysicsFilterMessage* message)
	{
		if (message->handle.IsValid() && message->flag)
		{
			bool flag = message->flag;
			GetPhysicsObjectMessage query;
			owner->PostMessage(&query);
			query.handle.GetObject()->SetFilterBits(0x20, false);
			query.handle.GetObject()->SetFilterBits2(0x200, false);
			message->handle.GetObject()->SetFilterBits(0x20, flag);
			message->handle.GetObject()->SetFilterBits2(0x200, flag);
		}
	}

	// FUNCTION: ENGINE 0x10848B70
	content::MemberList* HitReactionBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Behaviour>();
		static content::BaseClassCasterImpl<Behaviour, HitReactionBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<HitReactionBehaviour, float, 0>("pn"),
				ENGINE_OFFSET(HitReactionBehaviour, impulseScale), "impulseScale" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10848C20
	void HitReactionBehaviour::HandleMessage(Message* message)
	{
		switch (message->type)
		{
		case 6:
			switch ((unsigned short)message->id)
			{
			case 0:
				OnPhysicsFilterOn((PhysicsFilterMessage*)message);
				break;
			case 1:
				OnPhysicsFilterSwitch((PhysicsFilterMessage*)message);
				break;
			}
			break;
		case 0x14:
			if (message->id == 10)
			{
				OnHit((HitMessage*)message);
			}
			break;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10848990
// FUNCTION: ENGINE 0x108489A0
// FUNCTION: ENGINE 0x108489D0
// FUNCTION: ENGINE 0x10848B30
