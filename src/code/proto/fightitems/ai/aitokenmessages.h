// The messages the token actions of the ai fight items send (RTTI names from the engine; type, id and members from the
// engine's constructors, member names are guesses). The constructors are inline, expanded in every user.
#ifndef PROTO_FIGHTITEMS_AI_AITOKENMESSAGES_H
#define PROTO_FIGHTITEMS_AI_AITOKENMESSAGES_H

#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/proto/messages/airequestmessages.h"

namespace proto
{
	// RTTI: proto::RequestTokenMsg: an object asks for a token of a type for a requester and is answered whether it got one
	struct RequestTokenMsg : public TokenMessage
	{
		RequestTokenMsg(int newType, engine::GameObjectHandle newRequester) : TokenMessage(5), type(newType), requester(newRequester)
		{
		}
		virtual ~RequestTokenMsg()
		{
		}

		bool granted;  // +0xC
		int type;  // +0x10
		engine::GameObjectHandle requester;  // +0x14
	};

	// RTTI: proto::ReleaseTokenMsg: an object gives its token of a type back
	struct ReleaseTokenMsg : public TokenMessage
	{
		ReleaseTokenMsg(int newType, engine::GameObjectHandle newRequester) : TokenMessage(6), type(newType), requester(newRequester)
		{
		}
		virtual ~ReleaseTokenMsg()
		{
		}

		int type;  // +0xC
		engine::GameObjectHandle requester;  // +0x10
	};

	// RTTI: proto::SetHunterTokenBoostTokenMsg: an object gets more hunter tokens for a time
	struct SetHunterTokenBoostTokenMsg : public TokenMessage
	{
		SetHunterTokenBoostTokenMsg(int newExtraTokens, float newTime) : TokenMessage(7), extraTokens(newExtraTokens), time(newTime)
		{
		}
		virtual ~SetHunterTokenBoostTokenMsg()
		{
		}

		int extraTokens;  // +0xC
		float time;  // +0x10
	};
}

#endif
