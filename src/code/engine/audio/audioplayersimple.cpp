// engine::AudioPlayerSimple: see the header.
#include "code/engine/audio/audiomessage.h"
#include "code/engine/audio/audioplayersimple.h"

namespace engine
{

	// FUNCTION: ENGINE 0x1087F680
	bool AudioPlayerSimple::Slot1(core::Name<core::CaseSensitiveKey>* name)
	{
		if (*name == gAudioPlay)
		{
			Slot10();
			return true;
		}
		if (*name == gAudioStop)
		{
			new audio::RemotePlayerEvent_Param1<unsigned int>(player, &audio::RemotePlayer::Stop, 0);
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1087FF80
	bool AudioPlayerSimple::Slot3()
	{
		return 0 < audio::gRemotePlayers->entries[player.index].unknown2C;
	}

	// FUNCTION: ENGINE 0x1087F740
	void AudioPlayerSimple::Slot4()
	{
		new audio::RemotePlayerEvent_Param1<unsigned int>(player, &audio::RemotePlayer::Stop, 0);
	}

	// FUNCTION: ENGINE 0x1087FFA0
	bool AudioPlayerSimple::Slot5()
	{
		return audio::gRemotePlayers->entries[player.index].unknown28;
	}

	// FUNCTION: ENGINE 0x1087F980
	// NONMATCHING: the engine keeps the index in eax and the table in edx, ours the other way round (14 %)
#ifdef NONMATCHING
	float AudioPlayerSimple::Slot6(int* unknown)
	{
		audio::RemotePlayerTable* table = audio::gRemotePlayers;
		*unknown = table->entries[player.index].unknown34;
		return table->entries[player.index].unknown38;
	}
#endif

	// FUNCTION: ENGINE 0x1087F920
	bool AudioPlayerSimple::Slot8(const core::Name<core::CaseSensitiveKey>& name, float* value)
	{
		if (core::Name<core::CaseSensitiveKey>("amplitude", 0) == name)
		{
			*value = audio::gRemotePlayers->entries[player.index].amplitude;
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1087F700
	void AudioPlayerSimple::Slot10()
	{
		new audio::RemotePlayerEvent_Param1<unsigned int>(player, &audio::RemotePlayer::Play, 0);
	}
}
