// The audio library's mixer strips and the mixer's own properties (0x105C25C0 - 0x105CCBB0): the accessors the
// reflection of audio::Mix and audio::MixStrip registers, and the mixer's constructor.
#include "code/audio/mix.h"

namespace audio
{
	// FUNCTION: ENGINE 0x105C25C0
	const om::ClassName& MixStrip::GetName() const
	{
		return name;
	}

	// FUNCTION: ENGINE 0x105C25D0
	float MixStrip::GetVolume() const
	{
		return volume;
	}

	// FUNCTION: ENGINE 0x105CC070
	void MixStrip::SetVolume(float newVolume)
	{
		volume = newVolume;
	}

	// FUNCTION: ENGINE 0x105C25E0
	float MixStrip::GetPitch() const
	{
		return pitch;
	}

	// FUNCTION: ENGINE 0x105CC080
	void MixStrip::SetPitch(float newPitch)
	{
		pitch = newPitch;
	}

	// FUNCTION: ENGINE 0x105C25F0
	bool MixStrip::GetMuted() const
	{
		return muted;
	}

	// FUNCTION: ENGINE 0x105CC090
	bool MixStrip::GetSolo() const
	{
		return solo;
	}

	// FUNCTION: ENGINE 0x105C2600
	float MixStrip::GetReverb1() const
	{
		return reverb1;
	}

	// FUNCTION: ENGINE 0x105CC0A0
	void MixStrip::SetReverb1(float newReverb1)
	{
		reverb1 = newReverb1;
	}

	// FUNCTION: ENGINE 0x105C2610
	float MixStrip::GetSub() const
	{
		return sub;
	}

	// FUNCTION: ENGINE 0x105CC0B0
	void MixStrip::SetSub(float newSub)
	{
		sub = newSub;
	}

	// FUNCTION: ENGINE 0x105C2620
	bool MixStrip::GetPause() const
	{
		return pause;
	}

	// FUNCTION: ENGINE 0x105CC0C0
	void MixStrip::SetPause(bool newPause)
	{
		pause = newPause;
	}

	// FUNCTION: ENGINE 0x105CC0D0
	unsigned int Mix::GetFadeInTime() const
	{
		return fadeInTime;
	}

	// FUNCTION: ENGINE 0x105CC0E0
	void Mix::SetFadeInTime(unsigned int newFadeInTime)
	{
		fadeInTime = newFadeInTime;
	}

	// FUNCTION: ENGINE 0x105CC0F0
	unsigned int Mix::GetFadeOutTime() const
	{
		return fadeOutTime;
	}

	// FUNCTION: ENGINE 0x105CC100
	void Mix::SetFadeOutTime(unsigned int newFadeOutTime)
	{
		fadeOutTime = newFadeOutTime;
	}

	// FUNCTION: ENGINE 0x105CCB70
	Mix::Mix(const om::ClassName& newName) :
		Entity(newName),
		fadeInTime(1000),
		fadeOutTime(1000)
	{
	}

	// FUNCTION: ENGINE 0x105CDFF0
	om::EntityTypeBase* Mix::GetEntityType()
	{
		return om::FindEntityType(typeid(Mix));
	}
}
