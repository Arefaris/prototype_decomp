// The fight track that sticks a character to the supporting surface (unit 0x108F9A50 - 0x108FA180; no assert path, file name guessed).
#include "code/engine/fight/supportingstick.h"

namespace engine
{
	fight::Property** gSupportingSurfaceStickTrackProperties;  // 0x1131B304

	// FUNCTION: ENGINE 0x108F9A50
	bool SupportingSurfaceStickTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F9A60
	bool SupportingSurfaceStickTrack::SetTimeEnd(float newValue)
	{
		timeEnd = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F9A70
	bool SupportingSurfaceStickTrack::SetStickToSupportingSurface(bool newValue)
	{
		stickToSupportingSurface = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F9A80
	bool SupportingSurfaceStickTrack::SetResetOrientationDelta(bool newValue)
	{
		resetOrientationDelta = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F9A90
	bool SupportingSurfaceStickTrack::SetResetLimbSmoothing(bool newValue)
	{
		resetLimbSmoothing = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F9AA0
	bool SupportingSurfaceStickTrack::SetRestoreOnEnd(bool newValue)
	{
		restoreOnEnd = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F9AF0
	fight::Property* SupportingSurfaceStickTrack::GetProperty(int index)
	{
		return gSupportingSurfaceStickTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108F9B00
	void SupportingSurfaceStickTrack::ClearProperties()
	{
		fight::FreePropertyList(&gSupportingSurfaceStickTrackProperties);
	}

	// FUNCTION: ENGINE 0x108F9B10
	SupportingSurfaceStickTrack::SupportingSurfaceStickTrack() : timeBegin(0.0f), timeEnd(-1.0f), resetLimbSmoothing(false), resetOrientationDelta(true), restoreOnEnd(false), stickToSupportingSurface(true)
	{
		unknownC = 1;
	}

	// FUNCTION: ENGINE 0x108F9B50
	float SupportingSurfaceStickTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108F9B60
	float SupportingSurfaceStickTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x108F9B70
	SupportingSurfaceStickTrack::~SupportingSurfaceStickTrack()
	{
	}

	// FUNCTION: ENGINE 0x108F9F90
	fight::TrackFactory* CreateSupportingSurfaceStickTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<SupportingSurfaceStickTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108F9FB0
	// EQUIVALENT: the engine saves the registers it uses in the entry block, before the guard's branch; ours sinks the pushes behind the branch and leaves the early exit without the pops; every other instruction is the engine's
	void SupportingSurfaceStickTrack::RegisterProperties()
	{
		if (gSupportingSurfaceStickTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<SupportingSurfaceStickTrack>("timeBegin", &SupportingSurfaceStickTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<SupportingSurfaceStickTrack>("timeEnd", &SupportingSurfaceStickTrack::SetTimeEnd);
			properties[1] = property;
			property = new fight::PropertyBool<SupportingSurfaceStickTrack>("stickToSupportingSurface", &SupportingSurfaceStickTrack::SetStickToSupportingSurface);
			properties[2] = property;
			property = new fight::PropertyBool<SupportingSurfaceStickTrack>("resetOrientationDelta", &SupportingSurfaceStickTrack::SetResetOrientationDelta);
			properties[3] = property;
			property = new fight::PropertyBool<SupportingSurfaceStickTrack>("resetLimbSmoothing", &SupportingSurfaceStickTrack::SetResetLimbSmoothing);
			properties[4] = property;
			property = new fight::PropertyBool<SupportingSurfaceStickTrack>("restoreOnEnd", &SupportingSurfaceStickTrack::SetRestoreOnEnd);
			properties[5] = property;
			fight::RegisterPropertyList(properties, &gSupportingSurfaceStickTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x108FA180
	void RegisterSupportingSurfaceStickTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<SupportingSurfaceStickTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyBool<SupportingSurfaceStickTrack>;
	template class fight::PropertyFloatConstRange<SupportingSurfaceStickTrack>;
	template class fight::TrackFactoryTemplate<SupportingSurfaceStickTrack>;
	template class fight::TrackFactoryCasterTemplate<SupportingSurfaceStickTrack>;

	// FUNCTION: ENGINE 0x1092FE10
	bool SupportingSurfaceStickTrack::GetStickToSupportingSurface() const
	{
		return stickToSupportingSurface;
	}

	// FUNCTION: ENGINE 0x1092FE20
	bool SupportingSurfaceStickTrack::GetResetOrientationDelta() const
	{
		return resetOrientationDelta;
	}

	// FUNCTION: ENGINE 0x1092FE30
	bool SupportingSurfaceStickTrack::GetResetLimbSmoothing() const
	{
		return resetLimbSmoothing;
	}

	// FUNCTION: ENGINE 0x1092FE40
	bool SupportingSurfaceStickTrack::GetRestoreOnEnd() const
	{
		return restoreOnEnd;
	}
}
