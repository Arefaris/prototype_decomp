// proto::SoundDialogueResolver (RTTI name; vftable 0x10E0C31C, base engine::AudioDialogueResolver): the game's answers to
// the audio system's dialogue questions. Unit 0x1049B310 - 0x1049E3F0 (no assert path; the file names are guesses).
#ifndef PROTO_SOUNDRESOLVERS_H
#define PROTO_SOUNDRESOLVERS_H

#include "code/engine/audio/audiodialogueresolver.h"

namespace proto
{
	class SoundDialogueResolver : public engine::AudioDialogueResolver
	{
	public:
		// 0x1049B310
		SoundDialogueResolver();
		virtual ~SoundDialogueResolver()
		{
		}
		// The overrides of the engine's copies (left to the engine): 0x1049E0C0, 0x1049BB30, 0x1049BB70, 0x1049CD70,
		// 0x1049CD90, 0x1049E2C0, 0x1049E3F0, 0x104A0950
		virtual void Update();
		virtual int Slot2(int first, int second, int third, int fourth);
		virtual void Slot3(int first);
		virtual core::Name<core::CaseSensitiveKey> GetLanguageName();
		virtual void Slot7(int first, int second);
		virtual bool Slot8(int first);
		virtual bool Slot9(int first);
		virtual void Slot10(int first);
	};
}

#endif
