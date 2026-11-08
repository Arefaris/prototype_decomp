// The message that asks a ragdoll object for the physics objects of its two halves (declared by another unit of the engine; RTTI name, the constructor is inline there).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTIONRAGDOLLMESSAGE_H
#define PROTO_FIGHTITEMS_MOTION_MOTIONRAGDOLLMESSAGE_H

#include "code/engine/message.h"
#include "code/ravenphysics/context.h"

namespace engine
{
	// RTTI: engine::RagdollGetPhysicsObjectMessage: the object answers the handles of its two physics objects (an invalid handle is all ones)
	struct RagdollGetPhysicsObjectMessage : public IntrusiveMessage
	{
		RagdollGetPhysicsObjectMessage() : IntrusiveMessage(0x12, 9)
		{
			first.value = 0xFFFFFFFF;
			second.value = 0xFFFFFFFF;
		}
		virtual ~RagdollGetPhysicsObjectMessage()
		{
		}

		ravenphysics::ObjectHandle first;  // +0xC
		ravenphysics::ObjectHandle second;  // +0x10
	};
}

#endif
