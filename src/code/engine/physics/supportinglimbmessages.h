// The messages a character's supporting limbs answer (RTTI names, namespace engine; type 0x11). The constructors are
// inline: the fields are stored one by one and the object's own vftable last. The ids and the member names are read
// from the code that builds them on its stack; the names are guesses.
#ifndef ENGINE_PHYSICS_SUPPORTINGLIMBMESSAGES_H
#define ENGINE_PHYSICS_SUPPORTINGLIMBMESSAGES_H

#include "code/core/name.h"
#include "code/engine/message.h"

namespace engine
{
	class SupportingLimb;

	// Looks a limb up by name (id 1); the limb comes back in the message
	struct FindSupportingLimbMessage : public IntrusiveMessage
	{
		explicit FindSupportingLimbMessage(const core::Name<core::CaseSensitiveKey>& newName) : IntrusiveMessage(0x11, 1), name(newName)
		{
			limb = 0;
		}
		virtual ~FindSupportingLimbMessage()
		{
		}

		int unknownC;
		core::Name<core::CaseSensitiveKey> name;  // +0x10
		SupportingLimb* limb;  // +0x18
		int unknown1C;
	};

	// Makes a limb the active one (id 5)
	struct SupportingLimbSetActiveMessage : public IntrusiveMessage
	{
		explicit SupportingLimbSetActiveMessage(SupportingLimb* newLimb) : IntrusiveMessage(0x11, 5)
		{
			limb = newLimb;
		}
		virtual ~SupportingLimbSetActiveMessage()
		{
		}

		SupportingLimb* limb;  // +0xC
	};

	// Sticks the character to its supporting surface or lets it go (id 7); the previous setting comes back in the message
	struct StickToSupportingSurfaceMessage : public IntrusiveMessage
	{
		explicit StickToSupportingSurfaceMessage(bool newStick) : IntrusiveMessage(0x11, 7)
		{
			stick = newStick;
			previous = false;
		}
		virtual ~StickToSupportingSurfaceMessage()
		{
		}

		bool stick;  // +0xC
		bool previous;  // +0xD
	};

	// Turns the inverse kinematics of the character's limbs on or off (id 9)
	struct SetLimbIKEnabledMessage : public IntrusiveMessage
	{
		explicit SetLimbIKEnabledMessage(bool newEnabled) : IntrusiveMessage(0x11, 9)
		{
			enabled = newEnabled;
		}
		virtual ~SetLimbIKEnabledMessage()
		{
		}

		bool enabled;  // +0xC
	};

	// Asks whether the inverse kinematics of the character's limbs is on (id 8); the answer comes back in the message
	struct GetLimbIKEnabledMessage : public NonintrusiveMessage
	{
		GetLimbIKEnabledMessage() : NonintrusiveMessage(0x11, 8)
		{
			enabled = false;
		}
		virtual ~GetLimbIKEnabledMessage()
		{
		}

		bool enabled;  // +0xC
	};
}

#endif
