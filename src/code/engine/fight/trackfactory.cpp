// The fight tracks the engine registers and the factories that build them (see trackfactory.h). The unit runs
// 0x108078E0 - 0x10809000: the playback track, its properties and factory, then the same for the sound, music and
// scenario tracks.
#include "code/engine/fight/trackfactory.h"
#include "code/engine/audio/audiotracks.h"

namespace fight
{
	// FUNCTION: ENGINE 0x108079C0
	template<class T> TrackFactoryCasterTemplate<T>::TrackFactoryCasterTemplate()
	{
	}
}

namespace engine
{
	// The properties of the playback track, built by RegisterProperties and freed by ClearProperties
	fight::Property** gPlaybackTrackProperties;

	// ---- the members the properties write ------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x108078E0
	bool PlaybackTrack::SetTimeBegin(float value)
	{
		timeBegin = value;
		return true;
	}

	// FUNCTION: ENGINE 0x108078F0
	bool PlaybackTrack::SetNotifyOnPlaybackFinished(bool value)
	{
		notifyOnPlaybackFinished = value;
		return true;
	}

	// FUNCTION: ENGINE 0x10807920
	bool PlaybackTrack::SetState(const fight::Name& value)
	{
		state = value;
		return true;
	}

	// FUNCTION: ENGINE 0x10807940
	bool PlaybackTrack::SetSpecificPlaybackSet(const fight::Name& value)
	{
		specificPlaybackSet = value;
		return true;
	}

	// FUNCTION: ENGINE 0x10807900
	fight::Property* PlaybackTrack::GetProperty(int index)
	{
		return gPlaybackTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x10807910
	void PlaybackTrack::ClearProperties()
	{
		fight::FreePropertyList(&gPlaybackTrackProperties);
	}

	// FUNCTION: ENGINE 0x10807990
	float PlaybackTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108079A0
	float PlaybackTrack::Slot10() const
	{
		return 0.0f;
	}

	// ---- the track itself ----------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x10807960
	PlaybackTrack::PlaybackTrack()
		: timeBegin(0.0f), notifyOnPlaybackFinished(false)
	{
	}

	// FUNCTION: ENGINE 0x108079B0
	PlaybackTrack::~PlaybackTrack()
	{
	}

	// ---- the property list ---------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x10807B50
	// NONMATCHING: the engine's prologue saves esi before the guard test (sub esp, cmp, push esi, jne), ours schedules
	// the push after the branch, which shifts the jump displacements; every instruction and operand is otherwise the
	// engine's, including the array's 0x3fc memset and the four property constructions (98.1 %)
#ifdef NONMATCHING
	void PlaybackTrack::RegisterProperties()
	{
		if (gPlaybackTrackProperties != 0)
		{
			return;
		}

		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = new fight::PropertyFloatConstRange<PlaybackTrack>("timeBegin", &PlaybackTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyName<PlaybackTrack>("state", &PlaybackTrack::SetState);
			properties[1] = property;
			property = new fight::PropertyName<PlaybackTrack>("specificPlaybackSet", &PlaybackTrack::SetSpecificPlaybackSet);
			properties[2] = property;
			property = new fight::PropertyBool<PlaybackTrack>("notifyOnPlaybackFinished", &PlaybackTrack::SetNotifyOnPlaybackFinished);
			properties[3] = property;
			fight::RegisterPropertyList(properties, &gPlaybackTrackProperties);
		}
	}
#endif

	// ---- the factory ---------------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x10807AC0
	fight::TrackFactory* CreatePlaybackTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<PlaybackTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x10807AE0
	void RegisterPlaybackTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<PlaybackTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	// FUNCTION: ENGINE 0x108082A0
	fight::TrackFactory* CreateDialogueTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<DialogueTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108082C0
	fight::TrackFactory* CreateSoundTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<SoundTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108082E0
	fight::TrackFactory* CreateSoundBoolValueTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<SoundBoolValueTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x10808300
	fight::TrackFactory* CreateMixerTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<MixerTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x10808320
	fight::TrackFactory* CreateMusicTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<MusicTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x10808340
	fight::TrackFactory* CreateReverbTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<ReverbTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x10808360
	fight::TrackFactory* CreateSoundZoneTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<SoundZoneTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x10808380
	void RegisterAudioTrackFactories(fight::TrackRegistry* registry)
	{
		{
			fight::TrackFactoryCasterTemplate<DialogueTrack> caster;
			registry->AddFactory(fight::FindTrackFactory("dialogue", &caster));
		}
		{
			fight::TrackFactoryCasterTemplate<SoundTrack> caster;
			registry->AddFactory(fight::FindTrackFactory("sound", &caster));
		}
		{
			fight::TrackFactoryCasterTemplate<SoundBoolValueTrack> caster;
			registry->AddFactory(fight::FindTrackFactory("soundBoolValue", &caster));
		}
		{
			fight::TrackFactoryCasterTemplate<MixerTrack> caster;
			registry->AddFactory(fight::FindTrackFactory("mixer", &caster));
		}
		{
			fight::TrackFactoryCasterTemplate<MusicTrack> caster;
			registry->AddFactory(fight::FindTrackFactory("music", &caster));
		}
		{
			fight::TrackFactoryCasterTemplate<ReverbTrack> caster;
			registry->AddFactory(fight::FindTrackFactory("reverb", &caster));
		}
		{
			fight::TrackFactoryCasterTemplate<SoundZoneTrack> caster;
			registry->AddFactory(fight::FindTrackFactory("soundZone", &caster));
		}
	}

	template class fight::PropertyFloatConstRange<PlaybackTrack>;
	template class fight::PropertyBool<PlaybackTrack>;
	template class fight::PropertyName<PlaybackTrack>;
	template class fight::TrackFactoryTemplate<PlaybackTrack>;
	template class fight::TrackFactoryCasterTemplate<PlaybackTrack>;
	template class fight::TrackFactoryTemplate<DialogueTrack>;
	template class fight::TrackFactoryCasterTemplate<DialogueTrack>;
	template class fight::TrackFactoryTemplate<SoundTrack>;
	template class fight::TrackFactoryCasterTemplate<SoundTrack>;
	template class fight::TrackFactoryTemplate<SoundBoolValueTrack>;
	template class fight::TrackFactoryCasterTemplate<SoundBoolValueTrack>;
	template class fight::TrackFactoryTemplate<MixerTrack>;
	template class fight::TrackFactoryCasterTemplate<MixerTrack>;
	template class fight::TrackFactoryTemplate<MusicTrack>;
	template class fight::TrackFactoryCasterTemplate<MusicTrack>;
	template class fight::TrackFactoryTemplate<ReverbTrack>;
	template class fight::TrackFactoryCasterTemplate<ReverbTrack>;
	template class fight::TrackFactoryTemplate<SoundZoneTrack>;
	template class fight::TrackFactoryCasterTemplate<SoundZoneTrack>;
}
