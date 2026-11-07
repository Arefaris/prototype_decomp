// engine::AudioPlayer and the constant answers of the game's sound players: see audioplayer.h. Unit 0x104A2E40 - 0x104A3530
// (no assert path; the file name is a guess).
#include "code/engine/audio/audioplayer.h"

namespace engine
{
	// FUNCTION: ENGINE 0x104A3440
	AudioPlayer::AudioPlayer()
	{
	}

	// FUNCTION: ENGINE 0x104A2E50
	float AudioPlayer::Slot6(int a)
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x104A2E60
	void AudioPlayer::Slot7(int a)
	{
	}

	// FUNCTION: ENGINE 0x104A2E70
	bool AudioPlayer::Slot8(int a, int b)
	{
		return false;
	}
}

namespace proto
{
	// FUNCTION: ENGINE 0x104A3450
	bool SoundPlayerAmbience::Slot1(core::Name<core::CaseSensitiveKey>* name)
	{
		return true;
	}

	// FUNCTION: ENGINE 0x104A3520
	bool SoundPlayerAmbience::Slot3()
	{
		return false;
	}

	// FUNCTION: ENGINE 0x104A3460
	void SoundPlayerAmbience::Slot4()
	{
	}

	// FUNCTION: ENGINE 0x104A3470
	bool SoundPlayerAmbience::Slot5()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x104A6140
	bool SoundPlayerHelicopter::Slot3()
	{
		return false;
	}

	// FUNCTION: ENGINE 0x104A89D0
	bool SoundPlayerVehicle::Slot3()
	{
		return false;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x104A2E40
// FUNCTION: ENGINE 0x104A2E80
