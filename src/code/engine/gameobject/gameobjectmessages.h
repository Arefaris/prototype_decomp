// The messages the game object script functions send (RTTI names; the member names are guesses). Message type 0x14
// is the health family, 0x10 the character queries, 0xb the playback ones.
#ifndef ENGINE_GAMEOBJECT_GAMEOBJECTMESSAGES_H
#define ENGINE_GAMEOBJECT_GAMEOBJECTMESSAGES_H

#include "code/core/name.h"
#include "code/engine/message.h"
#include "code/engine/fight/branch.h"
#include "code/math/vector.h"

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

	// The reset message (type 2)
	struct ResetMessage : public IntrusiveMessage
	{
		ResetMessage() : IntrusiveMessage(2, 0)
		{
		}
	};

	struct SetBroadcastStateChangesMessage : public IntrusiveMessage
	{
		explicit SetBroadcastStateChangesMessage(bool newBroadcast) : IntrusiveMessage(0xb, 7)
		{
			broadcast = newBroadcast;
		}

		bool broadcast;
	};

	// The physics messages (type 3)
	struct PhysicsSetEnabledMessage : public IntrusiveMessage
	{
		explicit PhysicsSetEnabledMessage(bool newEnabled) : IntrusiveMessage(3, 0x11)
		{
			enabled = newEnabled;
		}

		bool enabled;
	};

	struct PhysicsWakeUpMessage : public IntrusiveMessage
	{
		PhysicsWakeUpMessage() : IntrusiveMessage(3, 0x14)
		{
			unknownC = false;
		}

		bool unknownC;
	};

	struct PhysicsSetLinearVelocityMessage : public IntrusiveMessage
	{
		PhysicsSetLinearVelocityMessage(const math::Vector& newVelocity, int newMode) :
			IntrusiveMessage(3, 5),
			mode(newMode),
			velocity(newVelocity)
		{
		}

		int mode;
		math::Vector velocity;
	};

	struct PhysicsSetAngularVelocityMessage : public IntrusiveMessage
	{
		PhysicsSetAngularVelocityMessage(const math::Vector& newVelocity, int newMode) :
			IntrusiveMessage(3, 7),
			mode(newMode),
			velocity(newVelocity)
		{
		}

		int mode;
		math::Vector velocity;
	};

	// engine::CharacterQueryMessage (RTTI): the questions a character's behaviours answer (message type 0x10)
	struct CharacterQueryMessage : public IntrusiveMessage
	{
		explicit CharacterQueryMessage(short newId) : IntrusiveMessage(0x10, newId)
		{
		}
	};

	struct CharacterIntentionLockMessage : public CharacterQueryMessage
	{
		explicit CharacterIntentionLockMessage(bool newLocked) : CharacterQueryMessage(3)
		{
			locked = newLocked;
		}

		bool locked;
	};

	struct CharacterIntentionClearMessage : public CharacterQueryMessage
	{
		CharacterIntentionClearMessage() : CharacterQueryMessage(4)
		{
		}
	};

	// Plays a branch of the fight tree (type 0xb); the members are guesses
	struct PlayBranchMessage : public IntrusiveMessage
	{
		PlayBranchMessage(fight::Branch* newBranch, int newMode, bool newFlag) : IntrusiveMessage(0xb, 2)
		{
			branch = newBranch;
			unknown10 = 0;
			mode = newMode;
			unknown18 = true;
			unknown1C = 0;
			flag = newFlag;
		}

		fight::Branch* branch;
		int unknown10;
		int mode;
		bool unknown18;
		int unknown1C;
		bool flag;
	};

	// Asks whether a branch is being played (answered in the message)
	struct IsPlayingBranchMessage : public NonintrusiveMessage
	{
		IsPlayingBranchMessage(fight::Branch* newBranch, bool newExact) :
			NonintrusiveMessage(0xb, 8),
			branch(newBranch)
		{
			exact = newExact;
			playing = false;
		}

		fight::Branch* branch;
		bool exact;
		bool playing;
	};

	// A supporting limb of a character (0x11 / 3 asks for the active one); the layout is a guess
	struct SupportingLimbInfo
	{
		int unknown0;
		int unknown4;
		core::Name<core::CaseSensitiveKey> name;
	};

	// Asks which supporting limb is active (answered through a pointer in the message)
	struct SupportingLimbGetActiveMessage : public IntrusiveMessage
	{
		SupportingLimbGetActiveMessage() : IntrusiveMessage(0x11, 3)
		{
			limb = 0;
		}

		SupportingLimbInfo** limb;
	};

	// Asks whether the character stands on a supporting surface (answered through a pointer in the message)
	struct CharacterQueryCollisionStateMessage : public CharacterQueryMessage
	{
		CharacterQueryCollisionStateMessage() : CharacterQueryMessage(2)
		{
			state = 0;
		}

		bool* state;
	};

	// Asks for the name of the playback state of a fight branch (type 0xb): two names go in, the third comes out
	struct GetPlaybackStateMessage : public NonintrusiveMessage
	{
		GetPlaybackStateMessage(const core::Name<core::CaseSensitiveKey>& newFirst,
			const core::Name<core::CaseSensitiveKey>& newSecond) :
			NonintrusiveMessage(0xb, 4),
			first(newFirst),
			second(newSecond)
		{
		}

		int unknownC;
		core::Name<core::CaseSensitiveKey> first;
		core::Name<core::CaseSensitiveKey> second;
		core::Name<core::CaseSensitiveKey> state;
	};

	// Asks the fight tree to print its diagnostics (type 0xb)
	struct FightPrintDiagnosticsMessage : public IntrusiveMessage
	{
		FightPrintDiagnosticsMessage() : IntrusiveMessage(0xb, 0xe)
		{
			enabled = true;
		}

		bool enabled;
	};

	// Asks the logic tree of a prop to go to a state (type 0xb); the constructor is in another unit (0x10259040)
	struct SetPropLogicStateMessage : public IntrusiveMessage
	{
		SetPropLogicStateMessage(core::Name<core::CaseSensitiveKey> newPrefix, const char* newState, bool newFlag,
			bool newOther, float newTime);

		int unknownC;
		core::Name<core::CaseSensitiveKey> prefix;
		core::Name<core::CaseSensitiveKey> stateName;
		const char* state;
		bool flag;
		bool other;
		float time;
		int unknown2C;
		bool succeeded;
	};
}

#endif
