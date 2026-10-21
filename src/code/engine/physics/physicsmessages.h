// The physics messages the game objects exchange (RTTI names, namespace engine; type 3 for all of them). The
// constructors are inline: the fields are stored one by one and the object's own vftable (a single slot, the deleting
// destructor) last. The ids and the member names are read from the code that builds them on its stack; the names are
// guesses.
#ifndef ENGINE_PHYSICS_PHYSICSMESSAGES_H
#define ENGINE_PHYSICS_PHYSICSMESSAGES_H

#include "code/engine/message.h"
#include "code/math/vector.h"
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

	// Asks whether the physics simulation of the object is on (id 0x10); the answer comes back in the message
	struct PhysicsGetEnabledMessage : public NonintrusiveMessage
	{
		PhysicsGetEnabledMessage() : NonintrusiveMessage(3, 0x10)
		{
			enabled = false;
		}
		virtual ~PhysicsGetEnabledMessage()
		{
		}

		bool enabled;
	};

	// Lets the physics object fall asleep or not (id 0x15); the second flag is the track's own
	struct PhysicsSetSleepingAllowedMessage : public IntrusiveMessage
	{
		PhysicsSetSleepingAllowedMessage(bool newAllowed, bool newKeepAwake) : IntrusiveMessage(3, 0x15)
		{
			allowed = newAllowed;
			keepAwake = newKeepAwake;
		}
		virtual ~PhysicsSetSleepingAllowedMessage()
		{
		}

		bool allowed;
		bool keepAwake;
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

	// Asks for the object's linear velocity (id 6); the velocity comes back in the message
	struct PhysicsGetLinearVelocityMessage : public NonintrusiveMessage
	{
		PhysicsGetLinearVelocityMessage() : NonintrusiveMessage(3, 6)
		{
			unknownC = -1;
			velocity.x = 0.0f;
			velocity.y = 0.0f;
			velocity.z = 0.0f;
		}
		virtual ~PhysicsGetLinearVelocityMessage()
		{
		}

		int unknownC;
		math::Vector velocity;
	};

	// Sets the object's linear velocity (id 5)
	struct PhysicsSetLinearVelocityMessage : public IntrusiveMessage
	{
		PhysicsSetLinearVelocityMessage(float newX, float newY, float newZ) : IntrusiveMessage(3, 5)
		{
			unknownC = -1;
			velocity.x = newX;
			velocity.y = newY;
			velocity.z = newZ;
		}
		virtual ~PhysicsSetLinearVelocityMessage()
		{
		}

		int unknownC;
		math::Vector velocity;
	};

	// Asks for the object's angular velocity (id 8)
	struct PhysicsGetAngularVelocityMessage : public NonintrusiveMessage
	{
		PhysicsGetAngularVelocityMessage() : NonintrusiveMessage(3, 8)
		{
			unknownC = -1;
			velocity.x = 0.0f;
			velocity.y = 0.0f;
			velocity.z = 0.0f;
		}
		virtual ~PhysicsGetAngularVelocityMessage()
		{
		}

		int unknownC;
		math::Vector velocity;
	};

	// Sets the object's angular velocity (id 7)
	struct PhysicsSetAngularVelocityMessage : public IntrusiveMessage
	{
		PhysicsSetAngularVelocityMessage(float newX, float newY, float newZ) : IntrusiveMessage(3, 7)
		{
			unknownC = -1;
			velocity.x = newX;
			velocity.y = newY;
			velocity.z = newZ;
		}
		virtual ~PhysicsSetAngularVelocityMessage()
		{
		}

		int unknownC;
		math::Vector velocity;
	};
}

#endif
