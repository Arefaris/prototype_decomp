// The message a puppet behaviour sends to its object when the puppet is made or taken away so that the render
// behaviour re-evaluates the pose (RTTI name engine::RenderEvaluatePoseMessage; type 7, id 8; the member name is a
// guess). The deleting destructor is the compiler's (0x1091B300).
#ifndef ENGINE_RENDERMESSAGES_H
#define ENGINE_RENDERMESSAGES_H

#include "code/engine/message.h"

namespace engine
{
	struct RenderEvaluatePoseMessage : public Message
	{
		explicit RenderEvaluatePoseMessage(bool newRemoved) : Message(7, 8)
		{
			removed = newRemoved;
		}
		virtual ~RenderEvaluatePoseMessage()
		{
		}

		bool removed;  // +0xC
	};
}

#endif
