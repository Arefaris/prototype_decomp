// The message the motion tracked expression tracks send to an object (RTTI name, namespace engine). The constructor is
// inline; the member names are guesses.
#ifndef ENGINE_EXPRESSIONMESSAGES_H
#define ENGINE_EXPRESSIONMESSAGES_H

#include "code/engine/message.h"

namespace engine
{
	// Switches the blending of the motion tracked expressions on or off over a duration (type 0xA, id 9)
	struct SetExpressionBlendingEnabledMessage : public IntrusiveMessage
	{
		SetExpressionBlendingEnabledMessage(bool newEnabled, float newBlendDuration) : IntrusiveMessage(0xa, 9)
		{
			enabled = newEnabled;
			blendDuration = newBlendDuration;
		}
		virtual ~SetExpressionBlendingEnabledMessage()
		{
		}

		bool enabled;  // +0xC
		float blendDuration;  // +0x10
	};
}

#endif
