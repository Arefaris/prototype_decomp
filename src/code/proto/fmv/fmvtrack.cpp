#include "code/proto/fmv/fmvtrack.h"
#include <new>

namespace proto
{
	fight::Property** gFMVTrackProperties;  // 0x112738B0

	// FUNCTION: ENGINE 0x105785F0
	bool FMVTrack::SetTimeBegin(float value)
	{
		timeBegin = value;
		return true;
	}

	// FUNCTION: ENGINE 0x10578610
	bool FMVTrack::SetTimeEnd(float value)
	{
		timeEnd = value;
		return true;
	}

	// FUNCTION: ENGINE 0x10578810
	bool FMVTrack::SetFilename(const char* value)
	{
		filename = fight::ReplaceString(filename, value);
		return true;
	}

	// FUNCTION: ENGINE 0x10578630
	bool FMVTrack::SetUseFMVState(bool value)
	{
		useFMVState = value;
		return true;
	}

	// FUNCTION: ENGINE 0x10578640
	bool FMVTrack::SetClearSubtitles(bool value)
	{
		clearSubtitles = value;
		return true;
	}

	// FUNCTION: ENGINE 0x10578650
	bool FMVTrack::SetIsPreLoaded(bool value)
	{
		isPreLoaded = value;
		return true;
	}

	// FUNCTION: ENGINE 0x10578660
	bool FMVTrack::SetUseBlackFades(bool value)
	{
		useBlackFades = value;
		return true;
	}

	// FUNCTION: ENGINE 0x10578670
	bool FMVTrack::SetFadeInOnEnter(bool value)
	{
		fadeInOnEnter = value;
		return true;
	}

	// FUNCTION: ENGINE 0x10578680
	bool FMVTrack::SetStayFadedOnExit(bool value)
	{
		stayFadedOnExit = value;
		return true;
	}

	// FUNCTION: ENGINE 0x10578690
	bool FMVTrack::SetFadeUpOnExit(bool value)
	{
		fadeUpOnExit = value;
		return true;
	}

	// FUNCTION: ENGINE 0x105786A0
	bool FMVTrack::SetDelayUninstall(bool value)
	{
		delayUninstall = value;
		return true;
	}

	// FUNCTION: ENGINE 0x105786B0
	bool FMVTrack::SetUninstallDelayTime(float value)
	{
		uninstallDelayTime = value;
		return true;
	}

	// FUNCTION: ENGINE 0x105786D0
	bool FMVTrack::SetWhiteFadeTime(float value)
	{
		whiteFadeTime = value;
		return true;
	}

	// FUNCTION: ENGINE 0x105786F0
	bool FMVTrack::SetTimer(float value)
	{
		timer = value;
		return true;
	}

	// FUNCTION: ENGINE 0x10578710
	fight::Property* FMVTrack::GetProperty(int index)
	{
		return gFMVTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x10578730
	void FMVTrack::ClearProperties()
	{
		fight::FreePropertyList(&gFMVTrackProperties);
	}

	// FUNCTION: ENGINE 0x10578740
	FMVTrack::FMVTrack() : filename(0), timeBegin(0.0f), timeEnd(-1.0f), timer(-1.0f), uninstallDelayTime(-1.0f),
		whiteFadeTime(0.25f), clearSubtitles(true), delayUninstall(false), fadeInOnEnter(false), fadeUpOnExit(true),
		isPreLoaded(false), stayFadedOnExit(false), useBlackFades(true), useFMVState(true)
	{
	}

	// FUNCTION: ENGINE 0x105787C0
	float FMVTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x105787D0
	float FMVTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x105787E0
	FMVTrack::~FMVTrack()
	{
		delete[] filename;
	}

	// FUNCTION: ENGINE 0x10578A10
	// EQUIVALENT: shrink-wrap (the engine saves esi in the entry block, before the guard's branch; ours sinks the push
	// behind it)
	void FMVTrack::RegisterProperties()
	{
		if (gFMVTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<FMVTrack>("timeBegin", &FMVTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<FMVTrack>("timeEnd", &FMVTrack::SetTimeEnd);
			properties[1] = property;
			property = new fight::PropertyString<FMVTrack>("filename", &FMVTrack::SetFilename);
			properties[2] = property;
			property = new fight::PropertyBool<FMVTrack>("useFMVState", &FMVTrack::SetUseFMVState);
			properties[3] = property;
			property = new fight::PropertyBool<FMVTrack>("clearSubtitles", &FMVTrack::SetClearSubtitles);
			properties[4] = property;
			property = new fight::PropertyBool<FMVTrack>("isPreLoaded", &FMVTrack::SetIsPreLoaded);
			properties[5] = property;
			property = new fight::PropertyBool<FMVTrack>("useBlackFades", &FMVTrack::SetUseBlackFades);
			properties[6] = property;
			property = new fight::PropertyBool<FMVTrack>("fadeInOnEnter", &FMVTrack::SetFadeInOnEnter);
			properties[7] = property;
			property = new fight::PropertyBool<FMVTrack>("stayFadedOnExit", &FMVTrack::SetStayFadedOnExit);
			properties[8] = property;
			property = new fight::PropertyBool<FMVTrack>("fadeUpOnExit", &FMVTrack::SetFadeUpOnExit);
			properties[9] = property;
			property = new fight::PropertyBool<FMVTrack>("delayUninstall", &FMVTrack::SetDelayUninstall);
			properties[10] = property;
			property = new fight::PropertyFloatConstRange<FMVTrack>("uninstallDelayTime", &FMVTrack::SetUninstallDelayTime);
			properties[11] = property;
			property = new fight::PropertyFloatConstRange<FMVTrack>("whiteFadeTime", &FMVTrack::SetWhiteFadeTime);
			properties[12] = property;
			property = new fight::PropertyFloatConstRange<FMVTrack>("timer", &FMVTrack::SetTimer);
			properties[13] = property;
			fight::RegisterPropertyList(properties, &gFMVTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x105789E0
	fight::TrackFactory* CreateFMVTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<FMVTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x10578DD0
	void RegisterFMVTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<FMVTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyBool<FMVTrack>;
	template class fight::PropertyFloatConstRange<FMVTrack>;
	template class fight::PropertyString<FMVTrack>;
	template class fight::TrackFactoryTemplate<FMVTrack>;
	template class fight::TrackFactoryCasterTemplate<FMVTrack>;

	// FUNCTION: ENGINE 0x10577830
	FMVAction::FMVAction(FMVTrack* newTrack, core::IRefCount* newOwner) : fight::Action(0xE00), link(newTrack),
		owner(newOwner), unknown30(0), unknown34(false), unknown35(false), unknown38(0), unknown3C(0.0f)
	{
	}

	// FUNCTION: ENGINE 0x10577790
	FMVAction::~FMVAction()
	{
	}
}

// Kept copies (template instances and wrappers of this unit):
// FUNCTION: ENGINE 0x10577770
// FUNCTION: ENGINE 0x105777C0
// FUNCTION: ENGINE 0x105778B0
// FUNCTION: ENGINE 0x10578840
// FUNCTION: ENGINE 0x10578870
// FUNCTION: ENGINE 0x10578880
// FUNCTION: ENGINE 0x105788B0
// FUNCTION: ENGINE 0x105788E0
// FUNCTION: ENGINE 0x10578910
// FUNCTION: ENGINE 0x10578920
// FUNCTION: ENGINE 0x10578950
// FUNCTION: ENGINE 0x10578970
// FUNCTION: ENGINE 0x10578980
// FUNCTION: ENGINE 0x105789B0
// FUNCTION: ENGINE 0x105789D0
// FUNCTION: ENGINE 0x10578E00
// FUNCTION: ENGINE 0x10578E30
// FUNCTION: ENGINE 0x10578E50
