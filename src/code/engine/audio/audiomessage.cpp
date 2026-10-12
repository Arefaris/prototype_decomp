#include "code/engine/audio/audiomessage.h"
#include <float.h>

namespace engine
{
	// FUNCTION: ENGINE 0x107FE300
	// EQUIVALENT: register choice for the volume parameter table (the engine computes it in eax, ours in ecx)
	void AudioEmitterTriggerMessage::Apply(AudioEmitter* emitter)
	{
		AudioSound* instance = emitter->sounds.Find(sound);
		AudioSoundList* sounds = &emitter->sounds;
		bool created = false;
		if (instance != 0)
		{
			if (event == gAudioPlay && mode == MODE_ONCE)
			{
				return;
			}
			if (event == gAudioPlay && mode == MODE_RESTART)
			{
				do
				{
					instance->Trigger(gAudioStop);
					instance->Release(true);
					instance = sounds->Find(sound);
				}
				while (instance != 0);
			}
			else if (!(event == gAudioPlay && mode == MODE_KEEP))
			{
				goto play;
			}
		}
		if (event == gAudioStop)
		{
			return;
		}
		instance = sounds->Create(sound, FLT_MAX, gAudioNoCategory);
		if (instance == 0)
		{
			return;
		}
		created = true;
	play:
		instance->SetUnknown21(unknown34);
		if (unknown34 == true)
		{
			instance->UpdateUnknown24();
		}
		if (gAudioStop == event)
		{
			sounds->Remove(instance, true);
			return;
		}
		if (created || unknown34 == false)
		{
			instance->Trigger(event);
		}
		if (0.0f != maxDistance)
		{
			instance->SetParameter(gAudioMin, &minDistance);
			instance->SetParameter(gAudioMax, &maxDistance);
		}
		if (1.0f != minPitch)
		{
			instance->SetParameter(gAudioMinPitch, &minPitch);
		}
		if (1.0f != maxPitch)
		{
			instance->SetParameter(gAudioMaxPitch, &maxPitch);
		}
		if (volume < 1.0f)
		{
			AudioParameterSource* source = instance->bank->data->parameters.Find(gAudioVolume);
			if (source != 0)
			{
				float value = source->GetValue() * volume;
				instance->SetParameter(gAudioVolume, &value);
			}
		}
		emitter->Update(0.0f);
	}
}

// Kept copies: the audio sound and audio system accessors Apply inlines
// FUNCTION: ENGINE 0x107FE2C0
// FUNCTION: ENGINE 0x107FE2D0
// FUNCTION: ENGINE 0x107FE2F0
