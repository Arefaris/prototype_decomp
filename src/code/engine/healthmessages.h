// The messages of the health behaviour and of the hit reaction behaviour (RTTI names where there are any: the
// DamageAppliedMessage and the ApplyDamageMessage; the others are named after the code that handles them).
#ifndef ENGINE_HEALTHMESSAGES_H
#define ENGINE_HEALTHMESSAGES_H

#include "code/engine/message.h"
#include "code/ravenphysics/context.h"

namespace engine
{
	// Asks for the lower limit of the health (answered in the message)
	struct GetMinHealthMessage : public NonintrusiveMessage
	{
		GetMinHealthMessage() : NonintrusiveMessage(0x14, 4)
		{
			minHealth = 0.0f;
		}

		float minHealth;
	};

	// Asks how many times the object was made undamageable and not yet damageable again
	struct GetUndamageableMessage : public NonintrusiveMessage
	{
		GetUndamageableMessage() : NonintrusiveMessage(0x14, 8)
		{
			count = 0;
		}

		int count;
	};

	// Damage to apply: amount is the damage before the scale, applied answers the health that was taken
	struct ApplyDamageMessage : public IntrusiveMessage
	{
		explicit ApplyDamageMessage(float newAmount) : IntrusiveMessage(0x14, 0xb)
		{
			amount = newAmount;
			applied = 0.0f;
		}
		virtual ~ApplyDamageMessage()
		{
		}

		float amount;
		float applied;
	};

	// Sent to the object when its health changed: the health taken and what is left
	struct DamageAppliedMessage : public IntrusiveMessage
	{
		DamageAppliedMessage(float newTaken, float newHealth) : IntrusiveMessage(0x14, 0xc), taken(newTaken),
			health(newHealth)
		{
		}
		virtual ~DamageAppliedMessage()
		{
		}

		float taken;
		float health;
	};

	// Asks the health to be written to a float (type 0x16, names guessed)
	struct SaveHealthMessage : public NonintrusiveMessage
	{
		SaveHealthMessage(float* newValue) : NonintrusiveMessage(0x16, 0)
		{
			value = newValue;
		}

		float* value;
	};

	// Hands the health back from a float (type 0x16, names guessed)
	struct RestoreHealthMessage : public NonintrusiveMessage
	{
		RestoreHealthMessage(float* newValue) : NonintrusiveMessage(0x16, 1)
		{
			value = newValue;
		}

		float* value;
	};

	// Messages of type 6 (names guessed): a flag and a physics object of another object that is switched along
	struct PhysicsFilterMessage : public IntrusiveMessage
	{
		PhysicsFilterMessage(short newId, bool newFlag) : IntrusiveMessage(6, newId)
		{
			flag = newFlag;
			handle.value = 0xffffffff;
		}

		bool flag;
		ravenphysics::ObjectHandle handle;
	};
}

#endif
