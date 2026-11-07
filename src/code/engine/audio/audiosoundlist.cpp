// engine::AudioSoundList and engine::AudioSound: the lists of sounds the audio emitters keep (see audiomessage.h). Unit
// 0x1086E6A0 - 0x10871870 (no assert path; the file name is a guess).
#include "code/engine/audio/audiomessage.h"

namespace engine
{
	// The audio system's singleton (0x113164B0; made by the engine's start-up)
	extern AudioSystem* gAudioSystem;

	// FUNCTION: ENGINE 0x1086E060
	AudioSystem* AudioSystem::Get()
	{
		return gAudioSystem;
	}

	// FUNCTION: ENGINE 0x1086E000
	void AudioSound::MarkReleased()
	{
		released = true;
	}

	// FUNCTION: ENGINE 0x10870AF0
	AudioSoundList::AudioSoundList(const AudioName& newName) :
		name(newName),
		slots(0),
		usedSlots(0),
		slotCount(0)
	{
	}

	// FUNCTION: ENGINE 0x10871620
	AudioSoundList::~AudioSoundList()
	{
		RemoveAll(true);
		om::Release(slots, slotCount * 8, 4);
	}

	// FUNCTION: ENGINE 0x10871500
	void AudioSoundList::Remove(AudioSound* sound, int unknown)
	{
		sound->Release(unknown);
	}

	// FUNCTION: ENGINE 0x108714D0
	void AudioSound::Release(int force)
	{
		if (!force || bank->unknownC)
		{
			MarkReleased();
		}
		AudioSoundList* system = (AudioSoundList*)AudioSystem::Get();
		if (system != list)
		{
			system->Adopt(this);
		}
	}
}
