// More messages the code half of the motion fight items sends to game objects (the second part of motionmessages.h: the grab and
// interrupt state messages and the vehicle, helicopter, variable and transformation messages). RTTI names; the constructors are
// inline in the engine and expanded in every user, the member names and the argument lists are guesses from the users.
#ifndef PROTO_FIGHTITEMS_MOTION_MOTIONMESSAGES2_H
#define PROTO_FIGHTITEMS_MOTION_MOTIONMESSAGES2_H

#include "code/engine/message.h"
#include "code/engine/gameobject/gameobjectmessages.h"
#include "code/core/name.h"
#include "code/proto/fightitems/motion/motionmessages.h"
#include "code/proto/fightitems/ai/aicodemessages.h"

namespace proto
{
	// RTTI: proto::SetUninterruptibleMessage: lets the object's hits interrupt it or not (message type 0x14)
	struct SetUninterruptibleMessage : public engine::IntrusiveMessage
	{
		explicit SetUninterruptibleMessage(bool newUninterruptible) : engine::IntrusiveMessage(0x14, 9), uninterruptible(newUninterruptible)
		{
		}
		virtual ~SetUninterruptibleMessage()
		{
		}

		bool uninterruptible;  // +0xC
	};

	// RTTI: proto::SetSpecificUninterruptibleMessage: the same for the interrupts of the specific kind
	struct SetSpecificUninterruptibleMessage : public engine::IntrusiveMessage
	{
		explicit SetSpecificUninterruptibleMessage(bool newUninterruptible) : engine::IntrusiveMessage(0x14, 0x1a), uninterruptible(newUninterruptible)
		{
		}
		virtual ~SetSpecificUninterruptibleMessage()
		{
		}

		bool uninterruptible;  // +0xC
	};

	// RTTI: proto::GrabbableMessage: the base of the messages about the grabs of an object (message type 0x3C)
	class GrabbableMessage : public engine::IntrusiveMessage
	{
	public:
		explicit GrabbableMessage(short newId) : engine::IntrusiveMessage(0x3c, newId)
		{
		}
		virtual ~GrabbableMessage()
		{
		}
	};

	// RTTI: proto::SetGrabbableUninterruptibleMessage: lets the grabs interrupt the object or not
	class SetGrabbableUninterruptibleMessage : public GrabbableMessage
	{
	public:
		explicit SetGrabbableUninterruptibleMessage(bool newUninterruptible) : GrabbableMessage(4), uninterruptible(newUninterruptible)
		{
		}
		virtual ~SetGrabbableUninterruptibleMessage()
		{
		}

		bool uninterruptible;  // +0xC
	};

	// RTTI: proto::SetDevastatorInterruptAllowedMessage: lets the devastator's grabs interrupt the object or not
	class SetDevastatorInterruptAllowedMessage : public GrabbableMessage
	{
	public:
		explicit SetDevastatorInterruptAllowedMessage(bool newAllowed) : GrabbableMessage(5), allowed(newAllowed)
		{
		}
		virtual ~SetDevastatorInterruptAllowedMessage()
		{
		}

		bool allowed;  // +0xC
	};
}

namespace engine
{
	// RTTI: engine::SetCloudFade: sets the fade of the clouds around an object (message type 7)
	struct SetCloudFade : public IntrusiveMessage
	{
		explicit SetCloudFade(float newFade) : IntrusiveMessage(7, 6), fade(newFade)
		{
		}
		virtual ~SetCloudFade()
		{
		}

		float fade;  // +0xC
	};
}

namespace proto
{
	// The slot of a transformation the object answers (the engine's class is not named; +0x1C answers whether it is active)
	struct TransformationSlot
	{
		int unknown0;
		int unknown4;
		int unknown8;
		int unknownC;
		int unknown10;
		int unknown14;
		int unknown18;
		bool active;  // +0x1C
	};

	// RTTI: proto::CompleteTransformationMessage: the transformation of the object is complete
	class CompleteTransformationMessage : public TransformationMessage
	{
	public:
		CompleteTransformationMessage() : TransformationMessage(5)
		{
		}
		virtual ~CompleteTransformationMessage()
		{
		}
	};

	// RTTI: proto::TransformationAllowedMessage: allows the object to transform or not
	class TransformationAllowedMessage : public TransformationMessage
	{
	public:
		explicit TransformationAllowedMessage(bool newAllowed) : TransformationMessage(0xf), allowed(newAllowed)
		{
		}
		virtual ~TransformationAllowedMessage()
		{
		}

		bool allowed;  // +0xC
	};

	// RTTI: proto::GetTransformationAllowedMessage: the object answers whether it may transform
	class GetTransformationAllowedMessage : public TransformationMessage
	{
	public:
		GetTransformationAllowedMessage() : TransformationMessage(0x10), allowed(false)
		{
		}
		virtual ~GetTransformationAllowedMessage()
		{
		}

		bool allowed;  // +0xC
	};

	// RTTI: proto::ConsumeTransformationDescriptionIsValidMessage: the object answers whether its consume transformation description is valid
	class ConsumeTransformationDescriptionIsValidMessage : public TransformationMessage
	{
	public:
		ConsumeTransformationDescriptionIsValidMessage() : TransformationMessage(0xa)
		{
		}
		virtual ~ConsumeTransformationDescriptionIsValidMessage()
		{
		}

		bool valid;  // +0xC
	};

	// RTTI: proto::StartTransformationMessage: starts the transformation in a slot
	class StartTransformationMessage : public TransformationMessage
	{
	public:
		StartTransformationMessage(const core::Name<core::CaseSensitiveKey>& newSlotName, bool newStealthy) : TransformationMessage(4), slotName(newSlotName), stealthy(newStealthy)
		{
		}
		virtual ~StartTransformationMessage()
		{
		}

		int unknownC;
		core::Name<core::CaseSensitiveKey> slotName;  // +0x10
		bool stealthy;  // +0x18
		int unknown1C;
	};

	// RTTI: proto::SetDesiredTransformationMessage: sets the transformation a slot should change to
	class SetDesiredTransformationMessage : public TransformationMessage
	{
	public:
		SetDesiredTransformationMessage(const core::Name<core::CaseSensitiveKey>& newSlotName, const core::Name<core::CaseSensitiveKey>& newDescription, bool newUnknown) : TransformationMessage(3), slotName(newSlotName), description(newDescription), unknown20(newUnknown)
		{
		}
		virtual ~SetDesiredTransformationMessage()
		{
		}

		int unknownC;
		core::Name<core::CaseSensitiveKey> slotName;  // +0x10
		core::Name<core::CaseSensitiveKey> description;  // +0x18
		bool unknown20;  // +0x20
		int unknown24;
	};

	// RTTI: proto::GetTransformationSlotByDescriptionNameMessage: the object answers whether the slot of a transformation description is active
	class GetTransformationSlotByDescriptionNameMessage : public TransformationMessage
	{
	public:
		explicit GetTransformationSlotByDescriptionNameMessage(const core::Name<core::CaseSensitiveKey>& newDescriptionName) : TransformationMessage(1), descriptionName(newDescriptionName), unknown18(0), active(false)
		{
		}
		virtual ~GetTransformationSlotByDescriptionNameMessage()
		{
		}

		int unknownC;
		core::Name<core::CaseSensitiveKey> descriptionName;  // +0x10
		int unknown18;
		bool active;  // +0x1C
	};

	// RTTI: proto::GetTransformationSlotMessage: the object answers the transformation slot of a name
	class GetTransformationSlotMessage : public TransformationMessage
	{
	public:
		explicit GetTransformationSlotMessage(const core::Name<core::CaseSensitiveKey>& newSlotName) : TransformationMessage(2), slot(0), slotName(newSlotName)
		{
		}
		virtual ~GetTransformationSlotMessage()
		{
		}

		TransformationSlot* slot;  // +0xC
		core::Name<core::CaseSensitiveKey> slotName;  // +0x10
	};

	// RTTI: proto::GetDesiredSensesPowerMessage: the object answers the senses power it is changing to
	class GetDesiredSensesPowerMessage : public TransformationMessage
	{
	public:
		GetDesiredSensesPowerMessage() : TransformationMessage(0x24), current(0), desired(0)
		{
		}
		virtual ~GetDesiredSensesPowerMessage()
		{
		}

		int current;  // +0xC
		int desired;  // +0x10
	};
}

namespace engine
{
	// RTTI: engine::EnableAttachedBillboard: switches the billboard attached to an object on or off (message type 7)
	struct EnableAttachedBillboard : public IntrusiveMessage
	{
		explicit EnableAttachedBillboard(bool newEnabled) : IntrusiveMessage(7, 0xd), enabled(newEnabled)
		{
		}
		virtual ~EnableAttachedBillboard()
		{
		}

		bool enabled;  // +0xC
	};
}

namespace proto
{
	// RTTI: proto::VehiclePlayAnimationMessage: starts or stops the vehicle's animation
	struct VehiclePlayAnimationMessage : public VehicleMessage
	{
		explicit VehiclePlayAnimationMessage(bool newPlay) : VehicleMessage(5), play(newPlay)
		{
		}
		virtual ~VehiclePlayAnimationMessage()
		{
		}

		bool play;  // +0xC
	};

	// RTTI: proto::GetRotorCollisionTimeMessage: the helicopter answers how long its rotor has been colliding
	struct GetRotorCollisionTimeMessage : public VehicleMessage
	{
		GetRotorCollisionTimeMessage() : VehicleMessage(10), time(0.0f)
		{
		}
		virtual ~GetRotorCollisionTimeMessage()
		{
		}

		float time;  // +0xC
	};

	// RTTI: proto::VehiclePowerOnOffMessage: switches the vehicle's power on or off
	struct VehiclePowerOnOffMessage : public VehicleMessage
	{
		VehiclePowerOnOffMessage(bool newPowerOn, bool newUseSpinup) : VehicleMessage(0xb), powerOn(newPowerOn), useSpinup(newUseSpinup)
		{
		}
		virtual ~VehiclePowerOnOffMessage()
		{
		}

		bool powerOn;  // +0xC
		bool useSpinup;  // +0xD
	};

	// RTTI: proto::SetHelicopterWashTypeMessage: switches the helicopter's wash effect
	struct SetHelicopterWashTypeMessage : public VehicleMessage
	{
		explicit SetHelicopterWashTypeMessage(bool newWash) : VehicleMessage(0xc), wash(newWash)
		{
		}
		virtual ~SetHelicopterWashTypeMessage()
		{
		}

		bool wash;  // +0xC
	};

	// RTTI: proto::GetSecondaryWeaponTypeMessage: the vehicle answers the type of its secondary weapon
	struct GetSecondaryWeaponTypeMessage : public VehicleMessage
	{
		GetSecondaryWeaponTypeMessage() : VehicleMessage(0xd)
		{
		}
		virtual ~GetSecondaryWeaponTypeMessage()
		{
		}

		int type;  // +0xC
	};

	// RTTI: proto::SetSecondaryWeaponTypeMessage: sets the type of the vehicle's secondary weapon
	struct SetSecondaryWeaponTypeMessage : public VehicleMessage
	{
		explicit SetSecondaryWeaponTypeMessage(int newType) : VehicleMessage(0xe), type(newType)
		{
		}
		virtual ~SetSecondaryWeaponTypeMessage()
		{
		}

		int type;  // +0xC
	};

	// RTTI: proto::GetHelicopterOnGroundMessage: the helicopter answers how long it has been on the ground
	struct GetHelicopterOnGroundMessage : public VehicleMessage
	{
		GetHelicopterOnGroundMessage() : VehicleMessage(0x10)
		{
		}
		virtual ~GetHelicopterOnGroundMessage()
		{
		}

		float time;  // +0xC
	};

	// RTTI: proto::GetHelicopterHeightAboveGroundMessage: the helicopter answers its height above the ground
	struct GetHelicopterHeightAboveGroundMessage : public VehicleMessage
	{
		GetHelicopterHeightAboveGroundMessage() : VehicleMessage(0x11)
		{
		}
		virtual ~GetHelicopterHeightAboveGroundMessage()
		{
		}

		float height;  // +0xC
	};

	// RTTI: proto::GetVehiclePowerOnOffMessage: the vehicle answers whether its power is on
	struct GetVehiclePowerOnOffMessage : public VehicleMessage
	{
		GetVehiclePowerOnOffMessage() : VehicleMessage(0x12)
		{
		}
		virtual ~GetVehiclePowerOnOffMessage()
		{
		}

		bool powerOn;  // +0xC
	};

	// RTTI: proto::SetSolverEnabledMessage: enables or disables the vehicle's solver
	struct SetSolverEnabledMessage : public VehicleMessage
	{
		explicit SetSolverEnabledMessage(bool newEnabled) : VehicleMessage(0x13), enabled(newEnabled)
		{
		}
		virtual ~SetSolverEnabledMessage()
		{
		}

		bool enabled;  // +0xC
	};

	// RTTI: proto::SetAnimatedMessage: sets whether the vehicle is animated
	struct SetAnimatedMessage : public VehicleMessage
	{
		explicit SetAnimatedMessage(bool newAnimated) : VehicleMessage(0x14), animated(newAnimated)
		{
		}
		virtual ~SetAnimatedMessage()
		{
		}

		bool animated;  // +0xC
	};
}

namespace proto
{
	// RTTI: proto::ReleaseWhipFistPowerMessage: releases the whip fist (power message id 0x15)
	class ReleaseWhipFistPowerMessage : public TransformationMessage
	{
	public:
		ReleaseWhipFistPowerMessage() : TransformationMessage(0x15)
		{
		}
		virtual ~ReleaseWhipFistPowerMessage()
		{
		}
	};

	// RTTI: proto::AnimatedWhipFistPowerMessage: switches the whip fist's animation on or off
	class AnimatedWhipFistPowerMessage : public TransformationMessage
	{
	public:
		explicit AnimatedWhipFistPowerMessage(bool newAnimated) : TransformationMessage(0x14), animated(newAnimated)
		{
		}
		virtual ~AnimatedWhipFistPowerMessage()
		{
		}

		bool animated;  // +0xC
	};

	// RTTI: proto::WhipFistResetTargetMessage: resets the target of the whip fist
	class WhipFistResetTargetMessage : public TransformationMessage
	{
	public:
		WhipFistResetTargetMessage() : TransformationMessage(0x1c)
		{
		}
		virtual ~WhipFistResetTargetMessage()
		{
		}
	};

	// RTTI: proto::WhipFistCheckExtendBlockedMessage: the object answers whether the whip fist's extension is blocked
	class WhipFistCheckExtendBlockedMessage : public TransformationMessage
	{
	public:
		WhipFistCheckExtendBlockedMessage() : TransformationMessage(0x1a), blocked(false)
		{
		}
		virtual ~WhipFistCheckExtendBlockedMessage()
		{
		}

		bool blocked;  // +0xC
	};

	// RTTI: proto::GetWhipFistStateMessage: the object answers the state of its whip fist
	class GetWhipFistStateMessage : public TransformationMessage
	{
	public:
		GetWhipFistStateMessage() : TransformationMessage(0x16), state(0)
		{
		}
		virtual ~GetWhipFistStateMessage()
		{
		}

		int state;  // +0xC
	};

	// RTTI: proto::GetWhipFistSegmentCountMessage: the object answers the number of segments of its whip fist
	class GetWhipFistSegmentCountMessage : public TransformationMessage
	{
	public:
		GetWhipFistSegmentCountMessage() : TransformationMessage(0x17), count(-1)
		{
		}
		virtual ~GetWhipFistSegmentCountMessage()
		{
		}

		int count;  // +0xC
	};

	// RTTI: proto::RetractWhipFistPowerMessage: retracts the whip fist
	class RetractWhipFistPowerMessage : public TransformationMessage
	{
	public:
		RetractWhipFistPowerMessage(float newVelocity, float newSoundLeadTime) : TransformationMessage(0x12), velocity(newVelocity), unknown10(0.0f), soundLeadTime(newSoundLeadTime)
		{
		}
		virtual ~RetractWhipFistPowerMessage()
		{
		}

		float velocity;  // +0xC
		float unknown10;  // +0x10
		float soundLeadTime;  // +0x14
	};

	// RTTI: proto::MakeTautWhipFistPowerMessage: makes the whip fist taut
	class MakeTautWhipFistPowerMessage : public TransformationMessage
	{
	public:
		explicit MakeTautWhipFistPowerMessage(float newTautTime) : TransformationMessage(0x13), tautTime(newTautTime)
		{
		}
		virtual ~MakeTautWhipFistPowerMessage()
		{
		}

		float tautTime;  // +0xC
	};

	// RTTI: proto::WhipFistFreezeSegmentsMessage: freezes the first segments of the whip fist
	class WhipFistFreezeSegmentsMessage : public TransformationMessage
	{
	public:
		explicit WhipFistFreezeSegmentsMessage(int newNumSegments) : TransformationMessage(0x19), numSegments(newNumSegments)
		{
		}
		virtual ~WhipFistFreezeSegmentsMessage()
		{
		}

		int numSegments;  // +0xC
	};
}

namespace proto
{
	// RTTI: proto::FightVariablesMessage: the base of the messages to the fight variables of an object (message type 0x23)
	class FightVariablesMessage : public engine::IntrusiveMessage
	{
	public:
		explicit FightVariablesMessage(short newId) : engine::IntrusiveMessage(0x23, newId)
		{
		}
		virtual ~FightVariablesMessage()
		{
		}
	};

	// RTTI: proto::VariableIntMessage: the base of the messages about an integer variable
	class VariableIntMessage : public FightVariablesMessage
	{
	public:
		VariableIntMessage(short newId, const core::Name<core::CaseSensitiveKey>& newVariable, int newValue) : FightVariablesMessage(newId), variable(newVariable), value(newValue)
		{
		}
		virtual ~VariableIntMessage()
		{
		}

		int unknownC;
		core::Name<core::CaseSensitiveKey> variable;  // +0x10
		int value;  // +0x18
	};

	// RTTI: proto::VariableIntGetMessage: the object answers the value of an integer variable
	class VariableIntGetMessage : public VariableIntMessage
	{
	public:
		explicit VariableIntGetMessage(const core::Name<core::CaseSensitiveKey>& newVariable) : VariableIntMessage(0, newVariable, 0)
		{
		}
		virtual ~VariableIntGetMessage()
		{
		}
	};

	// RTTI: proto::VariableNameMessage: the base of the messages about a name variable
	class VariableNameMessage : public FightVariablesMessage
	{
	public:
		VariableNameMessage(short newId, const core::Name<core::CaseSensitiveKey>& newVariable, const core::Name<core::CaseSensitiveKey>& newValue) : FightVariablesMessage(newId), variable(newVariable), value(newValue)
		{
		}
		virtual ~VariableNameMessage()
		{
		}

		int unknownC;
		core::Name<core::CaseSensitiveKey> variable;  // +0x10
		core::Name<core::CaseSensitiveKey> value;  // +0x18
	};

	// RTTI: proto::VariableNameGetMessage: the object answers the value of a name variable
	class VariableNameGetMessage : public VariableNameMessage
	{
	public:
		explicit VariableNameGetMessage(const core::Name<core::CaseSensitiveKey>& newVariable) : VariableNameMessage(2, newVariable, core::Name<core::CaseSensitiveKey>((const char*)0, 1))
		{
		}
		virtual ~VariableNameGetMessage()
		{
		}
	};

	// RTTI: proto::TimerMessage: the base of the messages about a timer
	class TimerMessage : public FightVariablesMessage
	{
	public:
		TimerMessage(short newId, const core::Name<core::CaseSensitiveKey>& newTimer, float newTime, bool newIncrementing) : FightVariablesMessage(newId), timer(newTimer), time(newTime), incrementing(newIncrementing)
		{
		}
		virtual ~TimerMessage()
		{
		}

		int unknownC;
		core::Name<core::CaseSensitiveKey> timer;  // +0x10
		float time;  // +0x18
		bool incrementing;  // +0x1C
	};

	// RTTI: proto::TimerGetMessage: the object answers the time of a timer
	class TimerGetMessage : public TimerMessage
	{
	public:
		explicit TimerGetMessage(const core::Name<core::CaseSensitiveKey>& newTimer) : TimerMessage(4, newTimer, 0.0f, false)
		{
		}
		virtual ~TimerGetMessage()
		{
		}
	};

	// RTTI: proto::OutOfCombatTimerMessage: the base of the messages about the out of combat timer
	class OutOfCombatTimerMessage : public FightVariablesMessage
	{
	public:
		OutOfCombatTimerMessage(short newId, float newTime) : FightVariablesMessage(newId), time(newTime)
		{
		}
		virtual ~OutOfCombatTimerMessage()
		{
		}

		float time;  // +0xC
	};

	// RTTI: proto::OutOfCombatTimerGetMessage: the object answers the out of combat time
	class OutOfCombatTimerGetMessage : public OutOfCombatTimerMessage
	{
	public:
		OutOfCombatTimerGetMessage() : OutOfCombatTimerMessage(6, 0.0f)
		{
		}
		virtual ~OutOfCombatTimerGetMessage()
		{
		}
	};
}

#endif
