// The messages the code half of the motion fight items (conditions' Evaluate and the actions) sends to game objects. The messages
// are declared by other units of the engine (RTTI names; the constructors are inline there and expanded in every user), the
// member names and the argument lists are guesses from the users.
#ifndef PROTO_FIGHTITEMS_MOTION_MOTIONMESSAGES_H
#define PROTO_FIGHTITEMS_MOTION_MOTIONMESSAGES_H

#include "code/engine/message.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/core/name.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/ai/aicodemessages.h"
#include "code/proto/fightitems/motion/motioncommon.h"

namespace proto
{
	// RTTI: proto::ChargeMessage: the base of the messages about the charge of an object (message type 0x1C), which carry an
	// amount and the type of the charge
	class ChargeMessage : public engine::IntrusiveMessage
	{
	public:
		ChargeMessage(short newId, float newValue, int newChargeType) : engine::IntrusiveMessage(0x1c, newId), value(newValue), chargeType(newChargeType)
		{
		}
		virtual ~ChargeMessage()
		{
		}

		float value;  // +0xC
		int chargeType;  // +0x10
	};

	// RTTI: proto::ChargeAddMessage: adds an amount to the charge of a type
	class ChargeAddMessage : public ChargeMessage
	{
	public:
		ChargeAddMessage(float newAmount, int newChargeType) : ChargeMessage(0, newAmount, newChargeType)
		{
		}
		virtual ~ChargeAddMessage()
		{
		}
	};

	// RTTI: proto::ChargeGetMessage: the object answers the charge of a type (in value)
	class ChargeGetMessage : public ChargeMessage
	{
	public:
		explicit ChargeGetMessage(int newChargeType) : ChargeMessage(2, 0.0f, newChargeType)
		{
		}
		virtual ~ChargeGetMessage()
		{
		}
	};

	// RTTI: proto::ChargeSetMessage: sets the charge of a type
	class ChargeSetMessage : public ChargeMessage
	{
	public:
		ChargeSetMessage(float newValue, int newChargeType) : ChargeMessage(3, newValue, newChargeType)
		{
		}
		virtual ~ChargeSetMessage()
		{
		}
	};

	// RTTI: proto::ButtonHintMessage: the base of the messages about the button hints (message type 0x37)
	struct ButtonHintMessage : public engine::IntrusiveMessage
	{
		explicit ButtonHintMessage(short newId) : engine::IntrusiveMessage(0x37, newId)
		{
		}
		virtual ~ButtonHintMessage()
		{
		}
	};

	// RTTI: proto::EnableButtonHintsMessage: turns the button hints of the object on or off
	struct EnableButtonHintsMessage : public ButtonHintMessage
	{
		explicit EnableButtonHintsMessage(bool newEnable) : ButtonHintMessage(2), enable(newEnable)
		{
		}
		virtual ~EnableButtonHintsMessage()
		{
		}

		bool enable;  // +0xC
	};

	// RTTI: proto::IsButtonHintShowingMessasge (sic): the object answers whether a button hint is showing, and its name
	struct IsButtonHintShowingMessasge : public ButtonHintMessage
	{
		IsButtonHintShowingMessasge() : ButtonHintMessage(3), showing(false), name(proto::fightitems::motion::gNoButtonHint)
		{
		}
		virtual ~IsButtonHintShowingMessasge()
		{
		}

		bool showing;  // +0xC
		core::Name<core::CaseSensitiveKey> name;  // +0x10
	};

	// RTTI: proto::CollisionMessage: the base of the messages about the collisions of an object (message type 0x1D)
	class CollisionMessage : public engine::IntrusiveMessage
	{
	public:
		explicit CollisionMessage(short newId) : engine::IntrusiveMessage(0x1d, newId)
		{
		}
		virtual ~CollisionMessage()
		{
		}
	};

	// RTTI: proto::ClearCollisionRecordMessage: the object forgets the collisions it has recorded
	class ClearCollisionRecordMessage : public CollisionMessage
	{
	public:
		ClearCollisionRecordMessage() : CollisionMessage(0)
		{
		}
		virtual ~ClearCollisionRecordMessage()
		{
		}
	};

	// RTTI: proto::CharacterMotionMessage: the base of the messages about the motion of a character (message type 0x21)
	class CharacterMotionMessage : public engine::IntrusiveMessage
	{
	public:
		explicit CharacterMotionMessage(short newId) : engine::IntrusiveMessage(0x21, newId)
		{
		}
		virtual ~CharacterMotionMessage()
		{
		}
	};

	// RTTI: proto::DriftEnableMessage: turns the drift of the character on or off
	class DriftEnableMessage : public CharacterMotionMessage
	{
	public:
		explicit DriftEnableMessage(bool newEnable) : CharacterMotionMessage(1), enable(newEnable)
		{
		}
		virtual ~DriftEnableMessage()
		{
		}

		bool enable;  // +0xC
	};

	// RTTI: proto::DevastatorAvailableMessage: the object answers whether its devastator is available (message type 0x14)
	struct DevastatorAvailableMessage : public engine::IntrusiveMessage
	{
		DevastatorAvailableMessage() : engine::IntrusiveMessage(0x14, 0x22), available(false)
		{
		}
		virtual ~DevastatorAvailableMessage()
		{
		}

		bool available;  // +0xC
	};

	// RTTI: proto::DevastatorUsedMessage: the devastator of the object has been used (message type 0x14)
	struct DevastatorUsedMessage : public engine::IntrusiveMessage
	{
		DevastatorUsedMessage() : engine::IntrusiveMessage(0x14, 0x21)
		{
		}
		virtual ~DevastatorUsedMessage()
		{
		}
	};

	// RTTI: proto::SetTargetableTargetMessage: makes the object targetable or not
	struct SetTargetableTargetMessage : public TargetableMessage
	{
		explicit SetTargetableTargetMessage(bool newTarget) : TargetableMessage(5), target(newTarget)
		{
		}
		virtual ~SetTargetableTargetMessage()
		{
		}

		bool target;  // +0xC
	};

	// RTTI: proto::SetTargetClassMessage: sets the class the object is targeted as
	struct SetTargetClassMessage : public TargetableMessage
	{
		explicit SetTargetClassMessage(int newTargetClass) : TargetableMessage(3), targetClass(newTargetClass)
		{
		}
		virtual ~SetTargetClassMessage()
		{
		}

		int targetClass;  // +0xC
	};

	// RTTI: proto::TransformationMessage: the base of the messages about the transformations and powers of an object (message type 0x1E)
	class TransformationMessage : public engine::IntrusiveMessage
	{
	public:
		explicit TransformationMessage(short newId) : engine::IntrusiveMessage(0x1e, newId)
		{
		}
		virtual ~TransformationMessage()
		{
		}
	};

	// RTTI: proto::ShieldSetStateMessage: sets the state of the object's shield
	class ShieldSetStateMessage : public TransformationMessage
	{
	public:
		explicit ShieldSetStateMessage(int newState) : TransformationMessage(0x1e), state(newState)
		{
		}
		virtual ~ShieldSetStateMessage()
		{
		}

		int state;  // +0xC
	};

	// RTTI: proto::ShieldReflectStartMessage: the shield starts to reflect bullets and missiles
	class ShieldReflectStartMessage : public TransformationMessage
	{
	public:
		ShieldReflectStartMessage(bool newReflectBullets, bool newReflectMissiles) : TransformationMessage(0x20), reflectBullets(newReflectBullets), reflectMissiles(newReflectMissiles)
		{
		}
		virtual ~ShieldReflectStartMessage()
		{
		}

		bool reflectBullets;  // +0xC
		bool reflectMissiles;  // +0xD
	};

	// RTTI: proto::ShieldReflectStopMessage: the shield stops reflecting
	class ShieldReflectStopMessage : public TransformationMessage
	{
	public:
		ShieldReflectStopMessage(bool newReflectBullets, bool newReflectMissiles) : TransformationMessage(0x21), reflectBullets(newReflectBullets), reflectMissiles(newReflectMissiles)
		{
		}
		virtual ~ShieldReflectStopMessage()
		{
		}

		bool reflectBullets;  // +0xC
		bool reflectMissiles;  // +0xD
	};

	// RTTI: proto::SetMotionStateMsg: sets a motion state of the object
	struct SetMotionStateMsg : public CharacterMotionMessage
	{
		SetMotionStateMsg(int newKind, const core::Name<core::CaseSensitiveKey>& newName) : CharacterMotionMessage(10), kind(newKind), name(newName)
		{
		}
		virtual ~SetMotionStateMsg()
		{
		}

		int kind;  // +0xC
		core::Name<core::CaseSensitiveKey> name;  // +0x10
	};

	// RTTI: proto::ShieldGetStateMessage: the object answers the state of its shield
	class ShieldGetStateMessage : public TransformationMessage
	{
	public:
		explicit ShieldGetStateMessage(int newState) : TransformationMessage(0x1f), state(newState)
		{
		}
		virtual ~ShieldGetStateMessage()
		{
		}

		int state;  // +0xC
	};

	// RTTI: proto::ShieldGetHealthMessage: the object answers the health of its shield and the most it can have
	class ShieldGetHealthMessage : public TransformationMessage
	{
	public:
		ShieldGetHealthMessage() : TransformationMessage(0x1d), health(choreo::gMinusOne), maxHealth(choreo::gMinusOne)
		{
		}
		virtual ~ShieldGetHealthMessage()
		{
		}

		float health;  // +0xC
		float maxHealth;  // +0x10
	};

	// RTTI: proto::GetStunnedMovementMessage: the object answers whether its movement is stunned
	struct GetStunnedMovementMessage : public MovementMessage
	{
		GetStunnedMovementMessage() : MovementMessage(0x45), stunned(false)
		{
		}
		virtual ~GetStunnedMovementMessage()
		{
		}

		bool stunned;  // +0xC
	};

	// RTTI: proto::GetMotionStateMsg: the object answers its motion state and the name of it
	struct GetMotionStateMsg : public CharacterMotionMessage
	{
		GetMotionStateMsg() : CharacterMotionMessage(0xb), state(-1)
		{
		}
		virtual ~GetMotionStateMsg()
		{
		}

		int state;  // +0xC
		core::Name<core::CaseSensitiveKey> name;  // +0x10
	};
}

#endif
