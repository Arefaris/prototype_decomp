// The ambient messages (message type 0x24) the vehicle fight items send to a vehicle; names from the RTTI, the member names are
// guesses from the requests' use.
#ifndef PROTO_MESSAGES_AMBIENTMESSAGES_H
#define PROTO_MESSAGES_AMBIENTMESSAGES_H

#include "code/engine/message.h"

namespace proto
{
	struct AmbientMessage : public engine::IntrusiveMessage
	{
	public:
		AmbientMessage(short newId) : engine::IntrusiveMessage(0x24, newId)
		{
		}
	};

	struct GetStateMessage : public AmbientMessage
	{
	public:
		GetStateMessage() : AmbientMessage(0xf), state(-1)
		{
		}

		int state;  // +0xC
	};

	struct TerminateMessage : public AmbientMessage
	{
	public:
		TerminateMessage() : AmbientMessage(0xd)
		{
		}
	};

	struct ReturnToNormalMessage : public AmbientMessage
	{
	public:
		ReturnToNormalMessage(float newTime) : AmbientMessage(0xe), time(newTime)
		{
		}

		float time;  // +0xC
	};

	struct SetVehiclePanicStateMessage : public AmbientMessage
	{
	public:
		SetVehiclePanicStateMessage(int newState) : AmbientMessage(0x16), state(newState)
		{
		}

		int state;  // +0xC
	};
}

#endif
