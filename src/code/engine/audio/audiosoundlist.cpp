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

	// The helpers the lists of sounds are walked with (template instances of the unit, not expanded)
	template<class T> bool IsPresent(T* item)
	{
		return item != 0;
	}

	template<class T> inline T* NodeToItem(om::TreeNode* node)
	{
		if (node != 0)
		{
			return (T*)((char*)node - 0x8c);
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x1086F2D0
	// NONMATCHING: the engine walks the tree with an iterator it keeps in a stack word and in registers differently (17 %)
#ifdef NONMATCHING
	AudioSound* AudioSoundList::Find(const AudioName& soundName)
	{
		AudioSound* current = NodeToItem<AudioSound>(tree.First());
		AudioSound* following = 0;
		if (current != 0)
		{
			following = NodeToItem<AudioSound>(tree.Next(&current->node));
		}
		if (IsPresent(current))
		{
			const unsigned int* hash = (const unsigned int*)&soundName.GetHash();
			do
			{
				AudioName& soundData = current->bank->data->name;
				if (soundData.hash == hash[0] && soundData.index == hash[1])
				{
					return current;
				}
				AudioSound* previous = following;
				if (following != 0)
				{
					following = NodeToItem<AudioSound>(tree.Next(&following->node));
				}
				else
				{
					following = 0;
				}
				current = previous;
			}
			while (IsPresent(current));
		}
		return 0;
	}
#endif

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
