#include "code/engine/audio/audiomanager.h"

namespace engine
{
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
}
