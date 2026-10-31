// The messages the code half of the motion fight items (conditions' Evaluate and the actions) sends to game objects. The messages
// are declared by other units of the engine (RTTI names; the constructors are inline there and expanded in every user), the
// member names and the argument lists are guesses from the users.
#ifndef PROTO_FIGHTITEMS_MOTION_MOTIONMESSAGES2_H
#define PROTO_FIGHTITEMS_MOTION_MOTIONMESSAGES2_H

#include "code/engine/message.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/core/name.h"
#include "code/proto/fightitems/ai/aicodemessages.h"
#include "code/proto/fightitems/motion/motioncommon2.h"

namespace proto
{
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
