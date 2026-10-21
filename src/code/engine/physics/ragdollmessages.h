// The messages the ragdoll behaviour listens to (RTTI names, namespace engine; type 0x12 unless noted). The constructors
// are inline: the fields are stored one by one and the object's own vftable last; the ids and the member names are
// read from the code that builds them on its stack, the names are guesses.
#ifndef ENGINE_PHYSICS_RAGDOLLMESSAGES_H
#define ENGINE_PHYSICS_RAGDOLLMESSAGES_H

#include "code/core/memory/imemoryallocator.h"
#include "code/engine/message.h"

namespace engine
{
	// Asks whether the ragdoll is enabled (id 0); the answer comes back in the message
	struct RagdollGetEnabledMessage : public NonintrusiveMessage
	{
		RagdollGetEnabledMessage() : NonintrusiveMessage(0x12, 0)
		{
			enabled = false;
		}
		virtual ~RagdollGetEnabledMessage()
		{
		}

		bool enabled;  // +0xC
	};

	// Turns the ragdoll on or off (id 1); the fields from rootJoint on are assigned after the construction. The engine
	// has one out-of-line copy of the four-argument constructor (0x1007A060, another unit's) and the callers that inline
	// it store all six fields, which the second constructor stands for
	struct RagdollSetEnabledMessage : public IntrusiveMessage
	{
		RagdollSetEnabledMessage(bool newEnabled, bool newDisableSupportingLimb, bool newInheritJointVelocities, int newPhysicsObject);
		RagdollSetEnabledMessage(bool newEnabled, bool newDisableSupportingLimb, bool newInheritJointVelocities, int newPhysicsObject,
			int newRootJoint, bool newIncludeRootJoint)
			: IntrusiveMessage(0x12, 1)
		{
			enabled = newEnabled;
			disableSupportingLimb = newDisableSupportingLimb;
			inheritJointVelocities = newInheritJointVelocities;
			physicsObject = newPhysicsObject;
			rootJoint = newRootJoint;
			includeRootJoint = newIncludeRootJoint;
		}
		virtual ~RagdollSetEnabledMessage()
		{
		}

		bool enabled;  // +0xC
		bool disableSupportingLimb;  // +0xD
		bool inheritJointVelocities;  // +0xE
		int physicsObject;  // +0x10
		int rootJoint;  // +0x14
		bool includeRootJoint;  // +0x18
	};

	// Powers the ragdoll by a pose (id 2); holds a reference on the source while it lives
	struct RagdollSetPoweredByPoseMessage : public IntrusiveMessage
	{
		RagdollSetPoweredByPoseMessage(core::IRefCount* newSource, int newConstraintProperties, bool newFlag)
			: IntrusiveMessage(0x12, 2)
		{
			source = newSource;
			constraintProperties = newConstraintProperties;
			flag = newFlag;
			if (source != 0)
			{
				source->AddRef();
			}
		}
		virtual ~RagdollSetPoweredByPoseMessage()
		{
			if (source != 0)
			{
				source->Release();
			}
		}

		core::IRefCount* source;  // +0xC
		int constraintProperties;  // +0x10
		bool flag;  // +0x14
	};

	// Starts or stops storing the velocities of the joints (id 3)
	struct RagdollStoreJointVelocitiesMessage : public IntrusiveMessage
	{
		explicit RagdollStoreJointVelocitiesMessage(bool newStore) : IntrusiveMessage(0x12, 3)
		{
			store = newStore;
		}
		virtual ~RagdollStoreJointVelocitiesMessage()
		{
		}

		bool store;  // +0xC
	};

	// Switches the ragdoll behaviour on or off (id 6)
	struct RagdollSetBehaviourActiveMessage : public IntrusiveMessage
	{
		explicit RagdollSetBehaviourActiveMessage(bool newActive) : IntrusiveMessage(0x12, 6)
		{
			active = newActive;
		}
		virtual ~RagdollSetBehaviourActiveMessage()
		{
		}

		bool active;  // +0xC
	};

	// Tells the ragdoll whether its keyframes were updated (id 7); the answer comes back in the second flag
	struct RagdollSetKeyframeUpdatedMessage : public IntrusiveMessage
	{
		explicit RagdollSetKeyframeUpdatedMessage(bool newKeyframeUpdated) : IntrusiveMessage(0x12, 7)
		{
			keyframeUpdated = newKeyframeUpdated;
			handled = false;
		}
		virtual ~RagdollSetKeyframeUpdatedMessage()
		{
		}

		bool keyframeUpdated;  // +0xC
		bool handled;  // +0xD
	};

	// Keeps the animation of the joints while the physics runs (type 3, id 0x1B)
	struct SetPhysicsPreserveJointAnimationMessage : public IntrusiveMessage
	{
		explicit SetPhysicsPreserveJointAnimationMessage(bool newPreserve) : IntrusiveMessage(3, 0x1b)
		{
			preserve = newPreserve;
			preserveAgain = newPreserve;
		}
		virtual ~SetPhysicsPreserveJointAnimationMessage()
		{
		}

		bool preserve;  // +0xC
		bool preserveAgain;  // +0xD
	};
}

#endif
