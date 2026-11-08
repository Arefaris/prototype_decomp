// The setters of audio::RemotePlayer that the audio thread runs for the events of the game (unit 0x1087F100 - 0x1087F200;
// no assert path, the file name is a guess). See audio/remoteplayerevent.h for the class.
#include "code/audio/remoteplayerevent.h"

namespace audio
{
	// FUNCTION: ENGINE 0x1087F100
	void RemotePlayer::SetUnknown444(float value)
	{
		unknown444 = value;
	}

	// FUNCTION: ENGINE 0x1087F120
	void RemotePlayer::SetUnknown528(float value)
	{
		unknown528 = value;
	}

	// FUNCTION: ENGINE 0x1087F140
	void RemotePlayer::SetUnknown52C(float value)
	{
		unknown52C = value;
	}

	// FUNCTION: ENGINE 0x1087F160
	void RemotePlayer::SetUnknown520(float value)
	{
		unknown520 = value;
	}

	// FUNCTION: ENGINE 0x1087F180
	void RemotePlayer::SetUnknown524(float value)
	{
		unknown524 = value;
	}

	// FUNCTION: ENGINE 0x1087F1A0
	void RemotePlayer::SetUnknown544(float value)
	{
		unknown544 = value;
	}

	// FUNCTION: ENGINE 0x1087F1C0
	void RemotePlayer::SetBinVolume(MixBin bin, float value)
	{
		binVolumes[bin] = value;
	}

	// FUNCTION: ENGINE 0x1087F1E0
	void RemotePlayer::SetChannelVolume(unsigned int channel, float value)
	{
		channelVolumes[channel] = value;
	}
}

template class audio::RemotePlayerEvent_Param2<audio::MixBin, float>;

// Kept copies of the instance's members (the unit keeps its own set; the other members, the allocation and the
// execution, are in the neighbouring units):
// FUNCTION: ENGINE 0x1087F2B0
// FUNCTION: ENGINE 0x1087F2E0
// FUNCTION: ENGINE 0x1087F2F0
