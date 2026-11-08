// engine::AudioPlayerSimple: see the header.
#include "code/engine/audio/audiomessage.h"
#include "code/engine/audio/audioplayersimple.h"
#include "code/om/dynamicobject.h"

#include "code/engine/driving/carattributes.h"

namespace engine
{
	// FUNCTION: ENGINE 0x1087F5E0
	// NONMATCHING: the base's vftable store and the remote player table's arguments come out in another form (42 %)
#ifdef NONMATCHING
	AudioPlayerSimple::AudioPlayerSimple(const AudioPlayerDescription* description) :
		AudioPlayer(Expanded()),
		name(description->name, 1)
	{
		player.word = audio::gRemotePlayers->Create(*reinterpret_cast<const audio::RemotePlayerParams*>(description->unknown10),
			description->unknown4 == 0, description->unknown8 == 0, description->unknownC == 0,
			reinterpret_cast<const type_info*>(description->unknown58), 1);
	}
#endif

	// FUNCTION: ENGINE 0x1087F7D0
	// NONMATCHING: the engine stores the vftable behind the three words and in front of the last float (64.5 %)
#ifdef NONMATCHING
	AudioPlayerPhysics::AudioPlayerPhysics(const AudioPlayerDescription* description) :
		AudioPlayerSimple(description),
		unknown24(0.0f),
		unknown28(0.0f),
		unknown2C(driving::gOne)
	{
		unknown20 = 0;
		unknown1C = 0;
		unknown18 = 0;
	}
#endif

	// FUNCTION: ENGINE 0x1087F660
	AudioPlayerSimple::~AudioPlayerSimple()
	{
		audio::gRemotePlayers->Destroy(player);
	}

	// FUNCTION: ENGINE 0x1087F640
	// The class's operator delete (inline in the header)

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

	// FUNCTION: ENGINE 0x1087F230
	void AudioPlayerSimple::Slot2(om::DynamicObject* properties)
	{
		for (om::DynamicPropertyBase* property = properties->GetFirstProperty(); property != 0; property = properties->GetNextProperty(property))
		{
			Slot9(property);
		}
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
