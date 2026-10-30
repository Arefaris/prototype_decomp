// engine::PlaybackMessage (RTTI name; derives engine::IntrusiveMessage): asks an object to play a named animation or
// sound (type 0xB, id 3). Its only virtual member is the destructor. The field names are guesses; the layout is
// read from the constructor the users inline (0x24 bytes after the 12 of the message header; the word at +0xC is
// not written).
#ifndef ENGINE_PLAYBACKMESSAGE_H
#define ENGINE_PLAYBACKMESSAGE_H

#include "code/core/name.h"
#include "code/engine/message.h"

namespace engine
{
	struct PlaybackMessage : public IntrusiveMessage
	{
		PlaybackMessage(const core::Name<core::CaseSensitiveKey>& newName, const core::Name<core::CaseSensitiveKey>& newOther,
			bool newFlagA, bool newFlagB, float newValue) : IntrusiveMessage(0xb, 3), name(newName), other(newOther),
			flagA(newFlagA), flagB(newFlagB), value(newValue)
		{
		}
		virtual ~PlaybackMessage()
		{
		}

		int unknownC;
		core::Name<core::CaseSensitiveKey> name;  // +0x10
		core::Name<core::CaseSensitiveKey> other;  // +0x18
		bool flagA;  // +0x20
		bool flagB;  // +0x21
		float value;  // +0x24
	};
}

#endif
