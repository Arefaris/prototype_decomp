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

namespace engine
{
	core::Name<core::CaseSensitiveKey> gAudioMin("min", 0);
	core::Name<core::CaseSensitiveKey> gAudioMax("max", 0);
	core::Name<core::CaseSensitiveKey> gMinEnvelope("min_envelope", 0);
	core::Name<core::CaseSensitiveKey> gMaxEnvelope("max_envelope", 0);
	core::Name<core::CaseSensitiveKey> gCurEnvelope("cur_envelope", 0);
	core::Name<core::CaseSensitiveKey> gImpulse("impulse", 0);
	core::Name<core::CaseSensitiveKey> gAudioMaxPitch("max_pitch", 0);
	core::Name<core::CaseSensitiveKey> gAudioMinPitch("min_pitch", 0);
	core::Name<core::CaseSensitiveKey> gAudioStop("stop", 0);
	core::Name<core::CaseSensitiveKey> gVel("vel", 0);
	core::Name<core::CaseSensitiveKey> gAudioVolume("volume", 0);
}

namespace engine
{
	core::Name<core::CaseSensitiveKey> gEvent("event", 0);
	core::Name<core::CaseSensitiveKey> gFile("file", 0);
	core::Name<core::CaseSensitiveKey> gAudioPlay("play", 0);
	core::Name<core::CaseSensitiveKey> gUserMixName("user_mix", 0);
}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D74290
// FUNCTION: ENGINE 0x10D742B0
// FUNCTION: ENGINE 0x10D743F0
// FUNCTION: ENGINE 0x10D74470
// FUNCTION: ENGINE 0x10D89E50
// FUNCTION: ENGINE 0x10D89E60
// FUNCTION: ENGINE 0x10D89F00
// FUNCTION: ENGINE 0x10D89F40


// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D742D0
// FUNCTION: ENGINE 0x10D742F0
// FUNCTION: ENGINE 0x10D74310
// FUNCTION: ENGINE 0x10D74330
// FUNCTION: ENGINE 0x10D74350
// FUNCTION: ENGINE 0x10D74370
// FUNCTION: ENGINE 0x10D74390
// FUNCTION: ENGINE 0x10D743B0
// FUNCTION: ENGINE 0x10D74450
// FUNCTION: ENGINE 0x10D74490
// FUNCTION: ENGINE 0x10D744B0
// FUNCTION: ENGINE 0x10D89E70
// FUNCTION: ENGINE 0x10D89E80
// FUNCTION: ENGINE 0x10D89E90
// FUNCTION: ENGINE 0x10D89EA0
// FUNCTION: ENGINE 0x10D89EB0
// FUNCTION: ENGINE 0x10D89EC0
// FUNCTION: ENGINE 0x10D89ED0
// FUNCTION: ENGINE 0x10D89EE0
// FUNCTION: ENGINE 0x10D89F30
// FUNCTION: ENGINE 0x10D89F50
// FUNCTION: ENGINE 0x10D89F60


// Kept copies: the audio sound and audio system accessors Apply inlines
// FUNCTION: ENGINE 0x107FE2C0
// FUNCTION: ENGINE 0x107FE2D0
// FUNCTION: ENGINE 0x107FE2F0
