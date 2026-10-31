#include "code/engine/audio/audiomanager.h"

namespace engine
{
	// The singleton (0x1130E74C; created by the engine's start-up)
	extern AudioManager* gAudioManager;

	// FUNCTION: ENGINE 0x10844DA0
	AudioManager* AudioManager::Get()
	{
		return gAudioManager;
	}

	inline float Abs(float value)
	{
		return value >= 0.0f ? value : -value;
	}

	inline bool IsZeroTime(float dt)
	{
		return Abs(dt) <= 1e-5f;
	}

	// FUNCTION: ENGINE 0x108451C0
	// EQUIVALENT: same calls and loop; the engine turns the zero test into a 0 / 1 value and compares it (`setne` /
	// `test` / `ja`) and keeps the join of each null-checked node adjustment before testing the object again (no
	// jump threading); every bool and cast form tried branches directly
	void AudioManager::Update(UpdateContext context)
	{
		AudioMixer::Get()->Update(context);
		AudioSystem::Get()->Update(context);
		if (!IsZeroTime(context.dt))
		{
			for (AudioUpdatable* item = AudioUpdatable::FromLink(sFirst); item != 0;
				item = AudioUpdatable::FromLink(item->link.next))
			{
				item->Update(context.dt);
			}
		}
		AudioClock::Get()->Update();
		gAudioEmitterSystem->Update(context);
	}

	// FUNCTION: ENGINE 0x108452B0
	void AudioManager::AddUpdatable(AudioUpdatable* updatable)
	{
		AudioUpdatableLink* link = updatable != 0 ? &updatable->link : 0;
		if (sFirst == 0)
		{
			sFirst = link;
			link->previous = 0;
			sLast = link;
			link->next = 0;
			return;
		}
		sLast->next = link;
		link->previous = sLast;
		sLast = link;
		link->next = 0;
	}

	// FUNCTION: ENGINE 0x10845310
	void AudioManager::RemoveUpdatable(AudioUpdatable* updatable)
	{
		AudioUpdatableLink* link = updatable != 0 ? &updatable->link : 0;
		if (link->previous == 0)
		{
			sFirst = link->next;
		}
		else
		{
			link->previous->next = link->next;
		}
		if (link->next == 0)
		{
			sLast = link->previous;
			return;
		}
		link->next->previous = link->previous;
	}
}
