#include "code/proto/behaviours/charactermotionbehaviour.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectsystem.h"

namespace engine
{
	namespace driving
	{
		extern const float gTwo;
	}
}

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10063290
	content::ClassInfo* CharacterMotionBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::CharacterMotionBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x100632D0
	// EQUIVALENT: the listen call arguments and the byte store are scheduled differently (29.4 %)
	CharacterMotionBehaviour::CharacterMotionBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner)
	{
		drift.x = 0.0f;
		drift.y = 0.0f;
		drift.z = 0.0f;
		driftTarget.x = 0.0f;
		driftTarget.y = 0.0f;
		driftTarget.z = 0.0f;
		driftAcceleration = 20.0f;
		pushbackAdd.x = 0.0f;
		pushbackAdd.y = 0.0f;
		pushbackAdd.z = 0.0f;
		pushbackTime = 0.0f;
		driftEnabled = false;
		pushbackDirection.x = 0.0f;
		pushbackDirection.y = 0.0f;
		pushbackDirection.z = 0.0f;
		pushbackSpeed = 0.0f;
		pushbackDeceleration = 0.0f;
		lastPosition.x = 0.0f;
		lastPosition.y = 0.0f;
		lastPosition.z = 0.0f;
		noPushbackCount = 0;
		lastVelocity.x = 0.0f;
		lastVelocity.y = 0.0f;
		lastVelocity.z = 0.0f;
		lastSprintVelocity.x = 0.0f;
		lastSprintVelocity.y = 0.0f;
		lastSprintVelocity.z = 0.0f;
		unknown78.x = 0.0f;
		unknown78.y = 0.0f;
		unknown78.z = 0.0f;
		unknown84.x = 0.0f;
		unknown84.y = 0.0f;
		unknown84.z = 0.0f;
		inverseDt = 0.0f;
		sprintVelocity.x = 0.0f;
		sprintVelocity.y = 0.0f;
		sprintVelocity.z = 0.0f;
		Listen(0x21, true);
		Listen2(0x10, true);
	}

	// FUNCTION: ENGINE 0x10063420
	CharacterMotionBehaviour::~CharacterMotionBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x10063430
	void CharacterMotionBehaviour::DriftAdd(DriftAddMessage* message)
	{
		if (message->pushback)
		{
			pushbackAdd.x = message->value.x + pushbackAdd.x;
			pushbackAdd.y = message->value.y + pushbackAdd.y;
			pushbackAdd.z = message->value.z + pushbackAdd.z;
			driftEnabled = true;
			return;
		}
		driftTarget.x = message->value.x + driftTarget.x;
		driftTarget.y = message->value.y + driftTarget.y;
		driftTarget.z = message->value.z + driftTarget.z;
		driftEnabled = true;
	}

	// FUNCTION: ENGINE 0x100634C0
	void CharacterMotionBehaviour::DriftEnable(DriftEnableMessage* message)
	{
		driftEnabled = message->enable;
	}

	// FUNCTION: ENGINE 0x100634D0
	// EQUIVALENT: the flag store is scheduled before the last fstp (93.3 %)
	void CharacterMotionBehaviour::DriftSet(DriftSetMessage* message)
	{
		if (message->pushback)
		{
			pushbackAdd.x = message->value.x + pushbackAdd.x;
			pushbackAdd.y = message->value.y + pushbackAdd.y;
			pushbackAdd.z = message->value.z + pushbackAdd.z;
		}
		else
		{
			drift.x = message->value.x;
			drift.y = message->value.y;
			drift.z = message->value.z;
			driftTarget.x = message->value.x;
			driftTarget.y = message->value.y;
			driftTarget.z = message->value.z;
		}
		driftEnabled = true;
	}

	// FUNCTION: ENGINE 0x10063560
	// EQUIVALENT: the three loads of the first operand are scheduled differently (28.3 %)
	void CharacterMotionBehaviour::DriftGet(DriftGetMessage* message)
	{
		float x = pushbackAdd.x;
		float y = pushbackAdd.y;
		float z = pushbackAdd.z;
		message->value.x = x + drift.x;
		message->value.y = y + drift.y;
		message->value.z = z + drift.z;
	}

	// FUNCTION: ENGINE 0x100635B0
	// EQUIVALENT: the message pointer is loaded after the first fld (77.4 %)
	void CharacterMotionBehaviour::PushbackGet(PushbackGetMessage* message)
	{
		message->direction.x = pushbackDirection.x;
		message->direction.y = pushbackDirection.y;
		message->direction.z = pushbackDirection.z;
		message->time = pushbackSpeed;
	}

	// FUNCTION: ENGINE 0x100635E0
	void CharacterMotionBehaviour::SetNoPushback(bool noPushback)
	{
		if (noPushback)
		{
			noPushbackCount++;
			if (noPushbackCount > 0)
			{
				pushbackTime = 0.0f;
				pushbackDirection.z = 0.0f;
				pushbackDirection.y = 0.0f;
				pushbackDirection.x = 0.0f;
				pushbackSpeed = 0.0f;
				pushbackDeceleration = 0.0f;
			}
		}
		else
		{
			noPushbackCount--;
		}
	}

	// FUNCTION: ENGINE 0x10063630
	void CharacterMotionBehaviour::AccelerationGet(AccelerationGetMessage* message)
	{
		switch (message->index)
		{
		case 0:
			message->acceleration.x = unknown78.x;
			message->acceleration.y = unknown78.y;
			message->acceleration.z = unknown78.z;
			break;
		case 1:
			message->acceleration.x = unknown84.x;
			message->acceleration.y = unknown84.y;
			message->acceleration.z = unknown84.z;
			break;
		}
	}

	// FUNCTION: ENGINE 0x10063690
	// EQUIVALENT: the message pointer is loaded after the first fld (70.6 %)
	void CharacterMotionBehaviour::SprintVelocityGet(SprintVelocityGetMessage* message)
	{
		message->value.x = sprintVelocity.x;
		message->value.y = sprintVelocity.y;
		message->value.z = sprintVelocity.z;
	}

	// FUNCTION: ENGINE 0x100636C0
	void CharacterMotionBehaviour::SprintVelocitySet(SprintVelocitySetMessage* message)
	{
		sprintVelocity.x = message->value.x;
		sprintVelocity.y = message->value.y;
		sprintVelocity.z = message->value.z;
	}

	// FUNCTION: ENGINE 0x100636F0
	void CharacterMotionBehaviour::Reset()
	{
		driftTarget.z = 0.0f;
		driftTarget.y = 0.0f;
		driftTarget.x = 0.0f;
		drift.z = 0.0f;
		drift.y = 0.0f;
		drift.x = 0.0f;
		pushbackAdd.z = 0.0f;
		pushbackAdd.y = 0.0f;
		pushbackAdd.x = 0.0f;
		pushbackTime = 0.0f;
		pushbackSpeed = 0.0f;
		pushbackDeceleration = 0.0f;
		pushbackDirection.z = 0.0f;
		pushbackDirection.y = 0.0f;
		pushbackDirection.x = 0.0f;
		lastVelocity.z = 0.0f;
		lastVelocity.y = 0.0f;
		lastVelocity.x = 0.0f;
		lastSprintVelocity.z = 0.0f;
		lastSprintVelocity.y = 0.0f;
		lastSprintVelocity.x = 0.0f;
		sprintVelocity.z = 0.0f;
		sprintVelocity.y = 0.0f;
		sprintVelocity.x = 0.0f;
		unknown78.z = 0.0f;
		unknown78.y = 0.0f;
		unknown78.x = 0.0f;
		unknown84.z = 0.0f;
		unknown84.y = 0.0f;
		unknown84.x = 0.0f;
		inverseDt = 0.0f;
	}

	// FUNCTION: ENGINE 0x10063AB0
	// EQUIVALENT: the same operations in the same order, the stores and the loads of the constants are scheduled differently (51.9 %)
	void CharacterMotionBehaviour::PushbackAdd(PushbackAddMessage* message)
	{
		if (0.0f < message->time)
		{
			pushbackTime = message->time;
			pushbackDirection.x = message->direction.x;
			pushbackDirection.y = message->direction.y;
			pushbackDirection.z = message->direction.z;
			pushbackDirection.y = 0.0f;
			float length = pushbackDirection.Normalize();
			float duration = pushbackTime;
			pushbackSpeed = length * engine::driving::gTwo;
			pushbackDeceleration = ((duration * length - pushbackSpeed * duration) * engine::driving::gTwo) /
				(duration * duration);
		}
	}

	// FUNCTION: ENGINE 0x10064220
	void CharacterMotionBehaviour::CharacterTeleported(CharacterTeleportedMessage* message)
	{
		if (message->handle.Get() == owner)
		{
			Reset();
		}
	}

	// FUNCTION: ENGINE 0x10064270
	void CharacterMotionBehaviour::OnMessage(engine::Message* message)
	{
		switch (message->type)
		{
		case 2:
			Reset();
			break;
		case 0x21:
			switch ((unsigned short)message->id)
			{
			case 0:
				DriftAdd(static_cast<DriftAddMessage*>(message));
				break;
			case 1:
				DriftEnable(static_cast<DriftEnableMessage*>(message));
				break;
			case 2:
				DriftGet(static_cast<DriftGetMessage*>(message));
				break;
			case 3:
				DriftSet(static_cast<DriftSetMessage*>(message));
				break;
			case 4:
				PushbackAdd(static_cast<PushbackAddMessage*>(message));
				break;
			case 5:
				PushbackGet(static_cast<PushbackGetMessage*>(message));
				break;
			case 6:
				SetNoPushback(static_cast<SetNoPushbackMessage*>(message)->noPushback);
				break;
			case 7:
				AccelerationGet(static_cast<AccelerationGetMessage*>(message));
				break;
			case 8:
				SprintVelocityGet(static_cast<SprintVelocityGetMessage*>(message));
				break;
			case 9:
				SprintVelocitySet(static_cast<SprintVelocitySetMessage*>(message));
				break;
			case 0xd:
				CharacterTeleported(static_cast<CharacterTeleportedMessage*>(message));
				break;
			}
			break;
		}
	}

	// FUNCTION: ENGINE 0x10064150
	content::MemberList* CharacterMotionBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, CharacterMotionBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<CharacterMotionBehaviour, float, 0>("p"),
				PROTO_OFFSET(CharacterMotionBehaviour, driftAcceleration), "driftAcceleration" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10063A40
// FUNCTION: ENGINE 0x10063A50
// FUNCTION: ENGINE 0x10063A80
// FUNCTION: ENGINE 0x10064110
