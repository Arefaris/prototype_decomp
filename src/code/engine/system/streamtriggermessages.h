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

	// A message to the stream system (RTTI name; 0x10 bytes): an id and a word
	struct StreamMessage : public IntrusiveMessage
	{
		// 0x10854080
		StreamMessage(short newId, int newValue);

		int value;
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
