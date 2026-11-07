// The messages the action halves of the motion fight items in 0x10100000 - 0x10120000 send, whose classes no other unit of this source tree declares (RTTI names; the
// constructors are inline in the engine and expanded in every user, so the argument lists and member names are guesses from the users).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTIONMESSAGES4_H
#define PROTO_FIGHTITEMS_MOTION_MOTIONMESSAGES4_H

#include "code/engine/message.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/core/name.h"
#include "code/proto/fightitems/ai/aimessages.h"
#include "code/proto/fightitems/motion/motionmessages.h"
#include "code/proto/messages/airequestmessages.h"
#include "code/proto/fightitems/ai/aicodemessages.h"

namespace proto
{
	// RTTI: proto::SetPatsyDisguiseMsg: gives the object its patsy
	struct SetPatsyDisguiseMsg : public DisguiseMessage
	{
		explicit SetPatsyDisguiseMsg(engine::GameObjectHandle newPatsy) : DisguiseMessage(0x2c), patsy(newPatsy)
		{
		}
		virtual ~SetPatsyDisguiseMsg()
		{
		}

		engine::GameObjectHandle patsy;  // +0xC
	};

	// RTTI: proto::GetPatsyDisguiseMsg: the object answers its patsy
	struct GetPatsyDisguiseMsg : public DisguiseMessage
	{
		GetPatsyDisguiseMsg() : DisguiseMessage(0x2d), patsy()
		{
		}
		virtual ~GetPatsyDisguiseMsg()
		{
		}

		engine::GameObjectHandle patsy;  // +0xC
	};

	// RTTI: proto::GetFailedPatsyDisguiseMsg: the object answers its failed patsy
	struct GetFailedPatsyDisguiseMsg : public DisguiseMessage
	{
		GetFailedPatsyDisguiseMsg() : DisguiseMessage(0x2e), patsy()
		{
		}
		virtual ~GetFailedPatsyDisguiseMsg()
		{
		}

		engine::GameObjectHandle patsy;  // +0xC
	};

	// RTTI: proto::SetFailedPatsyDisguiseMsg: gives the object its failed patsy
	struct SetFailedPatsyDisguiseMsg : public DisguiseMessage
	{
		explicit SetFailedPatsyDisguiseMsg(engine::GameObjectHandle newPatsy) : DisguiseMessage(0x2f), patsy(newPatsy)
		{
		}
		virtual ~SetFailedPatsyDisguiseMsg()
		{
		}

		engine::GameObjectHandle patsy;  // +0xC
	};

	// RTTI: proto::SetStunnedMovementMessage: stuns the movement of the object or lets it move again
	struct SetStunnedMovementMessage : public MovementMessage
	{
		explicit SetStunnedMovementMessage(bool newStunned) : MovementMessage(0x45), stunned(newStunned)
		{
		}
		virtual ~SetStunnedMovementMessage()
		{
		}

		bool stunned;  // +0xC
	};

	// RTTI: proto::SetFloatDelayTokenMsg: sets the delay of the object's token
	struct SetFloatDelayTokenMsg : public TokenMessage
	{
		explicit SetFloatDelayTokenMsg(float newDelay) : TokenMessage(2), delay(newDelay)
		{
		}
		virtual ~SetFloatDelayTokenMsg()
		{
		}

		float delay;  // +0xC
	};
}

#endif
