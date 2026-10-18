// The physics messages the game objects exchange (RTTI names, namespace engine; type 3 for all of them). The
// constructors are inline: the fields are stored one by one and the object's own vftable (a single slot, the deleting
// destructor) last. The ids and the member names are read from the code that builds them on its stack; the names are
// guesses.
#ifndef ENGINE_PHYSICS_PHYSICSMESSAGES_H
#define ENGINE_PHYSICS_PHYSICSMESSAGES_H

#include "code/engine/message.h"
#include "code/ravenphysics/context.h"

namespace engine
{
	// Sets what the object's collision tests include (id 10)
	struct SetIntersectionPropertiesMessage : public IntrusiveMessage
	{
		SetIntersectionPropertiesMessage(unsigned int newMask, bool newEnable, int newValue, bool newFlag)
			: IntrusiveMessage(3, 10)
		{
			mask = newMask;
			enable = newEnable;
			value = newValue;
			flag = newFlag;
		}
		virtual ~SetIntersectionPropertiesMessage()
		{
		}

		unsigned int mask;
		bool enable;
		int value;
		bool flag;
	};

	// Asks for the intersection properties of the object (id 9)
	struct GetIntersectionPropertiesMessage : public NonintrusiveMessage
	{
		GetIntersectionPropertiesMessage() : NonintrusiveMessage(3, 9)
		{
			properties = 0;
		}
		virtual ~GetIntersectionPropertiesMessage()
		{
		}

		int properties;
	};

	// Asks for the object's physics object (id 0xB); the handle comes back in the message
	struct GetPhysicsObjectMessage : public NonintrusiveMessage
	{
		GetPhysicsObjectMessage() : NonintrusiveMessage(3, 0xb)
		{
			handle.value = 0xffffffff;
		}
		virtual ~GetPhysicsObjectMessage()
		{
		}

		ravenphysics::ObjectHandle handle;
	};

	// Switches the physics object between simulated and keyframed (id 0x1A)
	struct SetPhysicsObjectKeyframedMessage : public IntrusiveMessage
	{
		explicit SetPhysicsObjectKeyframedMessage(bool newKeyframed) : IntrusiveMessage(3, 0x1a)
		{
			keyframed = newKeyframed;
		}
		virtual ~SetPhysicsObjectKeyframedMessage()
		{
		}

		bool keyframed;
	};

	// Lets a keyframed physics object update (id 0x19)
	struct SetKeyframedPhysicsUpdateEnabledMessage : public IntrusiveMessage
	{
		explicit SetKeyframedPhysicsUpdateEnabledMessage(bool newEnabled) : IntrusiveMessage(3, 0x19)
		{
			enabled = newEnabled;
		}
		virtual ~SetKeyframedPhysicsUpdateEnabledMessage()
		{
		}

		bool enabled;
	};

	// Wakes the physics object up (engine::PhysicsWakeUpMessage, id 0x14); the flag at +0xC is false when it is sent
	// by the ambient cars
	struct PhysicsWakeUpMessage : public IntrusiveMessage
	{
		explicit PhysicsWakeUpMessage(bool newFlag) : IntrusiveMessage(3, 0x14)
		{
			flag = newFlag;
		}
		virtual ~PhysicsWakeUpMessage()
		{
		}

		bool flag;
	};

	// Switches the physics simulation of the object on or off (id 0x11)
	struct PhysicsSetEnabledMessage : public IntrusiveMessage
	{
		explicit PhysicsSetEnabledMessage(bool newEnabled) : IntrusiveMessage(3, 0x11)
		{
			enabled = newEnabled;
		}
		virtual ~PhysicsSetEnabledMessage()
		{
		}

		bool enabled;
	};
}

#endif
