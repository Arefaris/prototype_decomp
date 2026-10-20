// The messages the game object script functions send (RTTI names; the member names are guesses). Message type 0x14
// is the health family, 0x10 the character queries, 0xb the playback ones.
#ifndef ENGINE_GAMEOBJECT_GAMEOBJECTMESSAGES_H
#define ENGINE_GAMEOBJECT_GAMEOBJECTMESSAGES_H

#include "code/engine/message.h"

namespace engine
{
	// Sets the health of the object
	struct SetHealthMessage : public IntrusiveMessage
	{
		explicit SetHealthMessage(float newHealth) : IntrusiveMessage(0x14, 0)
		{
			health = newHealth;
		}

		float health;
	};

	// Asks for the health (answered in the message): the current one and the maximum
	struct GetHealthMessage : public NonintrusiveMessage
	{
		GetHealthMessage() : NonintrusiveMessage(0x14, 1)
		{
			health = 0.0f;
			maxHealth = 0.0f;
		}

		float health;
		float maxHealth;
	};

	struct SetMaxHealthMessage : public IntrusiveMessage
	{
		explicit SetMaxHealthMessage(float newMaxHealth) : IntrusiveMessage(0x14, 2)
		{
			maxHealth = newMaxHealth;
		}

		float maxHealth;
	};

	struct SetMinHealthMessage : public IntrusiveMessage
	{
		explicit SetMinHealthMessage(float newMinHealth) : IntrusiveMessage(0x14, 3)
		{
			minHealth = newMinHealth;
		}

		float minHealth;
	};

	struct SetDamageScaleMessage : public IntrusiveMessage
	{
		explicit SetDamageScaleMessage(float newScale) : IntrusiveMessage(0x14, 5)
		{
			scale = newScale;
		}

		float scale;
	};

	// Asks for the damage scale (starts at one)
	struct GetDamageScaleMessage : public NonintrusiveMessage
	{
		GetDamageScaleMessage() : NonintrusiveMessage(0x14, 6)
		{
			scale = 1.0f;
		}

		float scale;
	};

	struct SetUndamageableMessage : public IntrusiveMessage
	{
		explicit SetUndamageableMessage(bool newUndamageable) : IntrusiveMessage(0x14, 7)
		{
			undamageable = newUndamageable;
		}

		bool undamageable;
	};
}

#endif
