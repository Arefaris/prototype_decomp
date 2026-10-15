// The fight tracks the engine registers and the factories that build them (see trackfactory.h). The unit runs
// 0x108078E0 - 0x10809000: the playback track, its properties and factory, then the same for the sound, music and
// scenario tracks.
#include "code/engine/fight/trackfactory.h"

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

	template class fight::PropertyFloatConstRange<PlaybackTrack>;
	template class fight::PropertyBool<PlaybackTrack>;
	template class fight::PropertyName<PlaybackTrack>;
	template class fight::TrackFactoryTemplate<PlaybackTrack>;
	template class fight::TrackFactoryCasterTemplate<PlaybackTrack>;
}
