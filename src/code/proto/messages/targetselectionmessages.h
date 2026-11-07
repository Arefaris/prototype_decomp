// The messages the target selection sends to the objects it rates (RTTI names): how much of the object's alliance is dynamic and
// the token score. The members behind the ids are guesses from the constructors and the handlers.
#ifndef PROTO_MESSAGES_TARGETSELECTIONMESSAGES_H
#define PROTO_MESSAGES_TARGETSELECTIONMESSAGES_H

#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/proto/messages/airequestmessages.h"

namespace proto
{
	// Disguise message 0x43: asks how much of the alliance of the object is dynamic (the answer starts at one half)
	struct GetDynamicAllianceRatioMsg : public DisguiseMessage
	{
		explicit GetDynamicAllianceRatioMsg(engine::GameObjectHandle newOther) : DisguiseMessage(0x43), ratio(0.5f),
			other(newOther)
		{
		}
		virtual ~GetDynamicAllianceRatioMsg()
		{
		}

		float ratio;  // +0xC
		engine::GameObjectHandle other;  // +0x10
	};

	// Token message 9: the score of an object for the tokens
	struct GetTokenScoreMsg : public TokenMessage
	{
		explicit GetTokenScoreMsg(engine::GameObjectHandle newHandle) : TokenMessage(9), handle(newHandle)
		{
		}
		virtual ~GetTokenScoreMsg()
		{
		}

		engine::GameObjectHandle handle;  // +0xC
		float normalized;  // +0x10
		float score;  // +0x14
	};
}

#endif
