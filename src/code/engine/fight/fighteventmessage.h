// engine::FightEventMessage (RTTI: base engine::IntrusiveMessage; message type 0xB, id 0xD): tells the fight system
// of its owner that something happened to a fight value. The word at +0xC is the event (0x10000 is the one the
// behaviours of the open world send); the names are guesses.
#ifndef ENGINE_FIGHT_FIGHTEVENTMESSAGE_H
#define ENGINE_FIGHT_FIGHTEVENTMESSAGE_H

#include "code/engine/message.h"

namespace engine
{
	struct FightEventMessage : public IntrusiveMessage
	{
		explicit FightEventMessage(int newEvent) : IntrusiveMessage(0xb, 0xd), event(newEvent)
		{
		}
		virtual ~FightEventMessage()
		{
		}

		int event;  // +0xC
	};
}

#endif
