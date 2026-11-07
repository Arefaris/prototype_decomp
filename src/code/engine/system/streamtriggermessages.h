// engine::StreamTriggerInfoMessage (RTTI name): the query the stream manager sends a game object to learn which stream
// triggers it carries and with which tags (up to four pairs; 0x30 bytes). The members are guesses.
#ifndef ENGINE_SYSTEM_STREAMTRIGGERMESSAGES_H
#define ENGINE_SYSTEM_STREAMTRIGGERMESSAGES_H

#include "code/engine/message.h"

namespace engine
{
	class StreamTrigger;
	class TagSet;

	struct StreamTriggerInfoEntry
	{
		StreamTrigger* trigger;
		TagSet* tags;
	};

	struct StreamTriggerInfoMessage : public IntrusiveMessage
	{
		StreamTriggerInfoMessage() : IntrusiveMessage(0x18, 2)
		{
			count = 0;
		}

		unsigned int count;
		StreamTriggerInfoEntry entries[4];
	};
}

#endif
