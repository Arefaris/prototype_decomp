// engine::AudioDialogueResolver (RTTI name; vftable 0x10E0C2E0, 11 slots): what the audio system asks the game about the
// dialogue it plays (whether a line may be played, subtitles, the language). The slots 1 - 4 are pure; 5 - 10 do
// nothing, or answer true. proto::SoundDialogueResolver is the game's resolver (soundresolvers.h). Unit 0x1049B110 -
// 0x1049C2D0 (no assert path; the file names are guesses); the slot names and arguments are guesses from the
// overrides.
#ifndef ENGINE_AUDIO_AUDIODIALOGUERESOLVER_H
#define ENGINE_AUDIO_AUDIODIALOGUERESOLVER_H

#include "code/core/name.h"

namespace engine
{
	class AudioDialogueResolver
	{
	public:
		AudioDialogueResolver()
		{
		}
		virtual ~AudioDialogueResolver()
		{
		}
		// Slots 1 - 4 (pure)
		virtual void Update() = 0;
		virtual int Slot2(int first, int second, int third, int fourth) = 0;
		virtual void Slot3(int first) = 0;
		virtual core::Name<core::CaseSensitiveKey> GetLanguageName() = 0;
		// Slots 5 - 10: 0x1049C1E0, 0x1049B130, 0x1049B140, 0x1049B150, 0x1049B160, 0x1049B170
		virtual void Slot5(int first, int second, int third)
		{
		}
		virtual void Slot6(int first, int second)
		{
		}
		virtual void Slot7(int first, int second)
		{
		}
		virtual bool Slot8(int first)
		{
			return true;
		}
		virtual bool Slot9(int first)
		{
			return true;
		}
		virtual void Slot10(int first)
		{
		}
	};
}

#endif
