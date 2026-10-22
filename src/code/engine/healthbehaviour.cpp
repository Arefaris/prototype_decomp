#include "code/engine/healthbehaviour.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/physics/getphysicsobjectmessage.h"
#include "code/ravenphysics/collision/collisionobject.h"
#include "code/ravenphysics/physicsobject.h"

namespace engine
{
#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10847EF0
	content::ClassInfo* HealthBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "HealthBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10847F30
	HealthBehaviour::HealthBehaviour(GameObject* newOwner) : Behaviour(newOwner)
	{
		health = 0.0f;
		maxHealth = -1.0f;
		initialHealth = 0.0f;
		minHealth = 0.0f;
		damageScale = 1.0f;
		undamageable = 0;
		dead = false;
		Listen(0x14, true);
		Listen(2, true);
		Listen(0x16, true);
		Listen(6, true);
	}

	// FUNCTION: ENGINE 0x10847FB0
	void HealthBehaviour::Slot1()
	{
		initialHealth = health;
	}

	// FUNCTION: ENGINE 0x10847FC0
	void HealthBehaviour::GetHealth(GetHealthMessage* message)
	{
		message->health = health;
		message->maxHealth = maxHealth;
	}

	// FUNCTION: ENGINE 0x10847FE0
	void HealthBehaviour::ResetHealth(Message* message)
	{
		health = initialHealth;
		dead = initialHealth <= 0.0f;
	}

	// FUNCTION: ENGINE 0x10848010
	void HealthBehaviour::SetMaxHealth(SetMaxHealthMessage* message)
	{
		maxHealth = message->maxHealth;
	}

	// FUNCTION: ENGINE 0x10848020
	void HealthBehaviour::GetMinHealth(GetMinHealthMessage* message)
	{
		message->minHealth = minHealth;
	}

	// FUNCTION: ENGINE 0x10848030
	void HealthBehaviour::SetMinHealth(SetMinHealthMessage* message)
	{
		minHealth = message->minHealth;
	}

	// FUNCTION: ENGINE 0x10848040
	void HealthBehaviour::GetDamageScale(GetDamageScaleMessage* message)
	{
		message->scale = damageScale;
	}

	// FUNCTION: ENGINE 0x10848050
	void HealthBehaviour::SetDamageScale(SetDamageScaleMessage* message)
	{
		damageScale = message->scale;
	}

	// FUNCTION: ENGINE 0x10848060
	void HealthBehaviour::SetUndamageable(SetUndamageableMessage* message)
	{
		undamageable += message->undamageable ? 1 : -1;
	}

	// FUNCTION: ENGINE 0x10848080
	void HealthBehaviour::OnPostedMessage(Message* message)
	{
		switch (message->type)
		{
		case 0x14:
			switch ((unsigned short)message->id)
			{
			case 1:
				GetHealth((GetHealthMessage*)message);
				break;
			case 6:
				GetDamageScale((GetDamageScaleMessage*)message);
				break;
			case 8:
				((GetUndamageableMessage*)message)->count = undamageable;
				break;
			}
			break;
		case 0x16:
			if (message->id == 0)
			{
				*((SaveHealthMessage*)message)->value = health;
			}
			break;
		}
	}

	// FUNCTION: ENGINE 0x108480D0
	void HealthBehaviour::SetHealth(float newHealth)
	{
		health = newHealth;
		if (newHealth > 0.0f)
		{
			dead = false;
		}
		CheckDeath(0);
	}

	// FUNCTION: ENGINE 0x10848100
	void HealthBehaviour::CheckDeath(Message* cause)
	{
		if (health <= 0.0f)
		{
			health = 0.0f;
			if (!dead)
			{
				dead = true;
				OnDeath(cause);
			}
		}
	}

	// FUNCTION: ENGINE 0x10848130
	void HealthBehaviour::OnDeath(Message* cause)
	{
	}

	// FUNCTION: ENGINE 0x108481C0
	// EQUIVALENT: register allocation only (the health is loaded into xmm0 and its copy goes to xmm1; ours the other way round), 98.8 %
	void HealthBehaviour::ApplyDamage(DamageMessage* message)
	{
		if (undamageable > 0)
		{
			message->applied = 0.0f;
			return;
		}
		float minimum = minHealth;
		float newHealth = health - message->amount * damageScale;
		newHealth = newHealth > minimum ? newHealth : minimum;
		float taken = health - newHealth;
		health = newHealth;
		message->applied = taken;
		DamageAppliedMessage applied(taken, health);
		owner->SendMessage(&applied);
		CheckDeath(message);
	}

	// FUNCTION: ENGINE 0x10848270
	// EQUIVALENT: the engine keeps the maximum in xmm0 and spills it into the dead argument slot, ours keeps it in xmm1 and spills it into a new stack slot, 14.1 %
	void HealthBehaviour::SetHealthFromMessage(SetHealthMessage* message)
	{
		if (maxHealth < 0.0f)
		{
			SetHealth(message->health);
		}
		else if (message->health > maxHealth)
		{
			SetHealth(maxHealth);
		}
		else
		{
			SetHealth(message->health);
		}
	}

	// FUNCTION: ENGINE 0x108482D0
	void HealthBehaviour::OnPhysicsFilterOn(PhysicsFilterMessage* message)
	{
		if (message->flag)
		{
			if (message->handle.IsValid())
			{
				message->handle.GetObject()->SetFilterBits(0x10, true);
				message->handle.GetObject()->SetFilterBits2(0x100, true);
			}
		}
	}

	// FUNCTION: ENGINE 0x10848330
	void HealthBehaviour::OnPhysicsFilterSwitch(PhysicsFilterMessage* message)
	{
		if (message->handle.IsValid())
		{
			bool flag = message->flag;
			bool inverse = !flag;
			GetPhysicsObjectMessage query;
			owner->PostMessage(&query);
			query.handle.GetObject()->SetFilterBits(0x10, inverse);
			query.handle.GetObject()->SetFilterBits2(0x100, inverse);
			message->handle.GetObject()->SetFilterBits(0x10, flag);
			message->handle.GetObject()->SetFilterBits2(0x100, flag);
		}
	}

	// FUNCTION: ENGINE 0x10848410
	void HealthBehaviour::OnMessage(Message* message)
	{
		switch (message->type)
		{
		case 0x14:
			switch ((unsigned short)message->id)
			{
			case 0xb:
				ApplyDamage((DamageMessage*)message);
				break;
			case 0:
				SetHealthFromMessage((SetHealthMessage*)message);
				break;
			case 2:
				SetMaxHealth((SetMaxHealthMessage*)message);
				break;
			case 4:
				GetMinHealth((GetMinHealthMessage*)message);
				break;
			case 3:
				SetMinHealth((SetMinHealthMessage*)message);
				break;
			case 5:
				SetDamageScale((SetDamageScaleMessage*)message);
				break;
			case 7:
				SetUndamageable((SetUndamageableMessage*)message);
				break;
			}
			break;
		case 0x16:
			switch ((unsigned short)message->id)
			{
			case 1:
				health = *((RestoreHealthMessage*)message)->value;
				break;
			}
			break;
		case 2:
			ResetHealth(message);
			break;
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
		}
	}

	// FUNCTION: ENGINE 0x108486A0
	content::MemberList* HealthBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Behaviour>();
		static content::BaseClassCasterImpl<Behaviour, HealthBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<HealthBehaviour, float, 0>("pn"),
				ENGINE_OFFSET(HealthBehaviour, health), "health" },
			{ content::GetMemberPrimitiveMetaType<HealthBehaviour, float, 1>("p"),
				ENGINE_OFFSET(HealthBehaviour, initialHealth), "initialHealth" },
			{ content::GetMemberPrimitiveMetaType<HealthBehaviour, float, 2>("p"),
				ENGINE_OFFSET(HealthBehaviour, maxHealth), "maxHealth" },
			{ content::GetMemberPrimitiveMetaType<HealthBehaviour, float, 3>("p"),
				ENGINE_OFFSET(HealthBehaviour, minHealth), "minHealth" },
			{ content::GetMemberPrimitiveMetaType<HealthBehaviour, float, 4>("p"),
				ENGINE_OFFSET(HealthBehaviour, damageScale), "damageScale" },
			{ content::GetMemberPrimitiveMetaType<HealthBehaviour, int, 0>("p"),
				ENGINE_OFFSET(HealthBehaviour, undamageable), "undamageable" }
		};
		sList.members = sMembers;
		sList.count = 6;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10847EA0
// FUNCTION: ENGINE 0x10847EE0
// FUNCTION: ENGINE 0x10848140
// FUNCTION: ENGINE 0x10848160
// FUNCTION: ENGINE 0x10848170
// FUNCTION: ENGINE 0x108481A0
// FUNCTION: ENGINE 0x10848520
// FUNCTION: ENGINE 0x10848560
// FUNCTION: ENGINE 0x108485A0
// FUNCTION: ENGINE 0x108485E0
// FUNCTION: ENGINE 0x10848620
// FUNCTION: ENGINE 0x10848660
