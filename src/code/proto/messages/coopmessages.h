// The co-op messages (message type 0x30) the online fight items send to a player; names from the RTTI, the member names are
// guesses from the requests' use.
#ifndef PROTO_MESSAGES_COOPMESSAGES_H
#define PROTO_MESSAGES_COOPMESSAGES_H

#include "code/engine/message.h"

namespace proto
{
	class CoOpMessage : public engine::IntrusiveMessage
	{
	public:
		CoOpMessage(short newId) : engine::IntrusiveMessage(0x30, newId)
		{
		}
	};

	class CoOpMessageGetPlayerDeathState : public CoOpMessage
	{
	public:
		CoOpMessageGetPlayerDeathState(int newPlayer) : CoOpMessage(1), player(newPlayer), dead(false)
		{
		}

		int player;  // +0xC
		bool dead;  // +0x10
	};

	class CoOpMessageGetRespawnState : public CoOpMessage
	{
	public:
		CoOpMessageGetRespawnState() : CoOpMessage(2), state(-1)
		{
		}

		int state;  // +0xC
	};
}

#endif
