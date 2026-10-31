// proto::CharacterMotionBehaviour (RTTI and reflection names; base engine::Behaviour): the motion a character gets
// on top of its animation. It listens for the character motion messages (type 0x21) that add drift and pushback
// to it, hands the sprint velocity and the accelerations of the last frames out, and moves the character's puppet
// in its update. Reflected: the drift acceleration. Unit 0x10063250 - 0x10064370 (no assert path; the file name is a
// guess). The reflected name and the message names are original, the rest is guessed; the update is not reconstructed.
#ifndef PROTO_BEHAVIOURS_CHARACTERMOTIONBEHAVIOUR_H
#define PROTO_BEHAVIOURS_CHARACTERMOTIONBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/message.h"
#include "code/math/vector.h"
#include "code/proto/fightitems/motion/motionmessages.h"

namespace proto
{
	// Drift (vector, flag +0x18: into the pushback instead) added to the drift (id 0)
	class DriftAddMessage : public CharacterMotionMessage
	{
	public:
		DriftAddMessage(const math::Vector& newValue) : CharacterMotionMessage(0)
		{
			value.x = newValue.x;
			value.y = newValue.y;
			value.z = newValue.z;
			pushback = false;
		}
		virtual ~DriftAddMessage()
		{
		}

		math::Vector value;  // +0xC
		bool pushback;  // +0x18
	};

	// The sum of the drift and the pushback is read (id 2)
	class DriftGetMessage : public CharacterMotionMessage
	{
	public:
		DriftGetMessage() : CharacterMotionMessage(2), value(0.0f, 0.0f, 0.0f)
		{
		}
		virtual ~DriftGetMessage()
		{
		}

		math::Vector value;  // +0xC
	};

	// Drift set (id 3; flag +0x18: added to the pushback)
	class DriftSetMessage : public CharacterMotionMessage
	{
	public:
		DriftSetMessage(const math::Vector& newValue) : CharacterMotionMessage(3)
		{
			value.x = newValue.x;
			value.y = newValue.y;
			value.z = newValue.z;
			pushback = false;
		}
		virtual ~DriftSetMessage()
		{
		}

		math::Vector value;  // +0xC
		bool pushback;  // +0x18
	};

	// A pushback with a duration (id 4)
	class PushbackAddMessage : public CharacterMotionMessage
	{
	public:
		PushbackAddMessage(const math::Vector& newDirection, float newTime) : CharacterMotionMessage(4),
			time(newTime)
		{
			direction.x = newDirection.x;
			direction.y = newDirection.y;
			direction.z = newDirection.z;
		}
		virtual ~PushbackAddMessage()
		{
		}

		math::Vector direction;  // +0xC
		float time;  // +0x18
	};

	// The pushback is read (id 5)
	class PushbackGetMessage : public CharacterMotionMessage
	{
	public:
		PushbackGetMessage() : CharacterMotionMessage(5), time(0.0f)
		{
			direction.x = math::kZeroVector.x;
			direction.y = math::kZeroVector.y;
			direction.z = math::kZeroVector.z;
		}
		virtual ~PushbackGetMessage()
		{
		}

		math::Vector direction;  // +0xC
		float time;  // +0x18
	};

	// Counts the requests for no pushback (id 6)
	class SetNoPushbackMessage : public CharacterMotionMessage
	{
	public:
		explicit SetNoPushbackMessage(bool newNoPushback) : CharacterMotionMessage(6), noPushback(newNoPushback)
		{
		}
		virtual ~SetNoPushbackMessage()
		{
		}

		bool noPushback;  // +0xC
	};

	// The acceleration of one of the two last frames is read (id 7)
	class AccelerationGetMessage : public CharacterMotionMessage
	{
	public:
		AccelerationGetMessage(int newIndex) : CharacterMotionMessage(7), index(newIndex), acceleration(0.0f, 0.0f, 0.0f)
		{
		}
		virtual ~AccelerationGetMessage()
		{
		}

		int index;  // +0xC
		math::Vector acceleration;  // +0x10
	};

	// The sprint velocity is read (id 8) / set (id 9)
	class SprintVelocityGetMessage : public CharacterMotionMessage
	{
	public:
		SprintVelocityGetMessage() : CharacterMotionMessage(8), value(0.0f, 0.0f, 0.0f)
		{
		}
		virtual ~SprintVelocityGetMessage()
		{
		}

		math::Vector value;  // +0xC
	};

	class SprintVelocitySetMessage : public CharacterMotionMessage
	{
	public:
		SprintVelocitySetMessage(const math::Vector& newValue) : CharacterMotionMessage(9)
		{
			value.x = newValue.x;
			value.y = newValue.y;
			value.z = newValue.z;
		}
		virtual ~SprintVelocitySetMessage()
		{
		}

		math::Vector value;  // +0xC
	};

	// The character was teleported (id 0xD; the handle is at +0xC)
	class CharacterTeleportedMessage : public CharacterMotionMessage
	{
	public:
		virtual ~CharacterTeleportedMessage()
		{
		}

		engine::GameObjectHandle handle;  // +0xC
	};

	class CharacterMotionBehaviour : public engine::Behaviour
	{
	public:
		// 0x100632D0
		explicit CharacterMotionBehaviour(engine::GameObject* newOwner);
		// 0x10063420 (deleting destructor 0x1006xxxx)
		virtual ~CharacterMotionBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 4 (0x10063B50) and 6 (0x10064270)
		virtual void Update(float dt, unsigned short mask);
		virtual void OnMessage(engine::Message* message);

		// 0x10063430 / 0x100634C0 / 0x10063560 / 0x100634D0 / 0x10063AB0 / 0x100635B0 / 0x100635E0 / 0x10063630 /
		// 0x10063690 / 0x100636C0 / 0x10064220: the handlers of the messages, in the order of their ids
		void DriftAdd(DriftAddMessage* message);
		void DriftEnable(DriftEnableMessage* message);
		void DriftGet(DriftGetMessage* message);
		void DriftSet(DriftSetMessage* message);
		void PushbackAdd(PushbackAddMessage* message);
		void PushbackGet(PushbackGetMessage* message);
		void SetNoPushback(bool noPushback);
		void AccelerationGet(AccelerationGetMessage* message);
		void SprintVelocityGet(SprintVelocityGetMessage* message);
		void SprintVelocitySet(SprintVelocitySetMessage* message);
		void CharacterTeleported(CharacterTeleportedMessage* message);
		// 0x100636F0: forgets the state of the motion
		void Reset();

		math::Vector drift;  // +0xC
		math::Vector driftTarget;  // +0x18
		float driftAcceleration;  // +0x24
		math::Vector pushbackAdd;  // +0x28
		bool driftEnabled;  // +0x34
		float pushbackTime;  // +0x38
		math::Vector pushbackDirection;  // +0x3C
		float pushbackSpeed;  // +0x48
		float pushbackDeceleration;  // +0x4C
		math::Vector lastPosition;  // +0x50
		int noPushbackCount;  // +0x5C
		math::Vector lastVelocity;  // +0x60
		math::Vector lastSprintVelocity;  // +0x6C
		math::Vector unknown78;  // +0x78
		math::Vector unknown84;  // +0x84
		float inverseDt;  // +0x90
		math::Vector sprintVelocity;  // +0x94
	};
}

#endif
