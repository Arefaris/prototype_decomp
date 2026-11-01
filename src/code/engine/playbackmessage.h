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

	// engine::GetPlaybackStateMessage (RTTI name; derives engine::NonintrusiveMessage; type 0xB, id 4): asks an object for
	// the state of a playback; the answer is written to the last name. The constructor takes both names by value and the
	// engine keeps one out of line copy (0x102C5320). The field names are guesses.
	struct GetPlaybackStateMessage : public NonintrusiveMessage
	{
		// 0x102C5320 (another unit)
		GetPlaybackStateMessage(core::Name<core::CaseSensitiveKey> newPlaybackSet, core::Name<core::CaseSensitiveKey> newState);
		virtual ~GetPlaybackStateMessage()
		{
		}

		int unknownC;
		core::Name<core::CaseSensitiveKey> playbackSet;  // +0x10
		core::Name<core::CaseSensitiveKey> requestedState;  // +0x18
		core::Name<core::CaseSensitiveKey> state;  // +0x20: the answer
	};
}

#endif
