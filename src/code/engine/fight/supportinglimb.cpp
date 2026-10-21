// The fight tracks of the supporting limb (unit 0x108F99F0 - 0x108FA380; no assert path, file name guessed).
#include "code/engine/fight/supportinglimb.h"

namespace engine
{
	fight::Property** gSupportingLimbTrackProperties;  // 0x1131B2FC

	// FUNCTION: ENGINE 0x108F99F0
	bool SupportingLimbTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F9A00
	bool SupportingLimbTrack::SetDirection(const math::Vector& newValue)
	{
		direction.x = newValue.x;
		direction.y = newValue.y;
		direction.z = newValue.z;
		return true;
	}

	// FUNCTION: ENGINE 0x108F9AB0
	fight::Property* SupportingLimbTrack::GetProperty(int index)
	{
		return gSupportingLimbTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108F9AC0
	void SupportingLimbTrack::ClearProperties()
	{
		fight::FreePropertyList(&gSupportingLimbTrackProperties);
	}

	// FUNCTION: ENGINE 0x108F9B80
	bool SupportingLimbTrack::SetSupportingLimb(const fight::Name& newValue)
	{
		supportingLimb = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F9BC0
	SupportingLimbTrack::SupportingLimbTrack() : direction(0.0f, 0.0f, 0.0f), timeBegin(0.0f)
	{
		unknownC = 1;
	}

	// FUNCTION: ENGINE 0x108F9C00
	float SupportingLimbTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108F9C10
	float SupportingLimbTrack::Slot10() const
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x108F9C20
	SupportingLimbTrack::~SupportingLimbTrack()
	{
	}

	// FUNCTION: ENGINE 0x108F9F50
	fight::TrackFactory* CreateSupportingLimbTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<SupportingLimbTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108FA120
	void RegisterSupportingLimbTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<SupportingLimbTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	// FUNCTION: ENGINE 0x108FA2A0
	// EQUIVALENT: the engine saves the registers it uses in the entry block, before the guard's branch; ours sinks the pushes behind the branch and leaves the early exit without the pops; every other instruction is the engine's
	void SupportingLimbTrack::RegisterProperties()
	{
		if (gSupportingLimbTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<SupportingLimbTrack>("timeBegin", &SupportingLimbTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyNameList<SupportingLimbTrack>("supportingLimb", &SupportingLimbTrack::SetSupportingLimb);
			properties[1] = property;
			property = new fight::PropertyVector<SupportingLimbTrack>("direction", &SupportingLimbTrack::SetDirection);
			properties[2] = property;
			fight::RegisterPropertyList(properties, &gSupportingLimbTrackProperties);
		}
	}

	template class fight::PropertyFloatConstRange<SupportingLimbTrack>;
	template class fight::PropertyNameList<SupportingLimbTrack>;
	template class fight::PropertyVector<SupportingLimbTrack>;
	template class fight::TrackFactoryTemplate<SupportingLimbTrack>;
	template class fight::TrackFactoryCasterTemplate<SupportingLimbTrack>;


	fight::Property** gSupportingLimbExtraLengthTrackProperties;  // 0x1131B300

	// FUNCTION: ENGINE 0x108F9A20
	bool SupportingLimbExtraLengthTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F9A30
	bool SupportingLimbExtraLengthTrack::SetTimeEnd(float newValue)
	{
		timeEnd = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F9A40
	bool SupportingLimbExtraLengthTrack::SetExtraLength(float newValue)
	{
		extraLength = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F9AD0
	fight::Property* SupportingLimbExtraLengthTrack::GetProperty(int index)
	{
		return gSupportingLimbExtraLengthTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108F9AE0
	void SupportingLimbExtraLengthTrack::ClearProperties()
	{
		fight::FreePropertyList(&gSupportingLimbExtraLengthTrackProperties);
	}

	// FUNCTION: ENGINE 0x108F9BA0
	bool SupportingLimbExtraLengthTrack::SetSupportingLimb(const fight::Name& newValue)
	{
		supportingLimb = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F9C30
	SupportingLimbExtraLengthTrack::SupportingLimbExtraLengthTrack() : extraLength(0.0f), timeBegin(0.0f), timeEnd(-1.0f)
	{
		unknownC = 1;
	}

	// FUNCTION: ENGINE 0x108F9C70
	float SupportingLimbExtraLengthTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108F9C80
	float SupportingLimbExtraLengthTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x108F9C90
	SupportingLimbExtraLengthTrack::~SupportingLimbExtraLengthTrack()
	{
	}

	// FUNCTION: ENGINE 0x108F9F70
	fight::TrackFactory* CreateSupportingLimbExtraLengthTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<SupportingLimbExtraLengthTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108FA150
	void RegisterSupportingLimbExtraLengthTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<SupportingLimbExtraLengthTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	// FUNCTION: ENGINE 0x108FA380
	// EQUIVALENT: the engine saves the registers it uses in the entry block, before the guard's branch; ours sinks the pushes behind the branch and leaves the early exit without the pops; every other instruction is the engine's
	void SupportingLimbExtraLengthTrack::RegisterProperties()
	{
		if (gSupportingLimbExtraLengthTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<SupportingLimbExtraLengthTrack>("timeBegin", &SupportingLimbExtraLengthTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<SupportingLimbExtraLengthTrack>("timeEnd", &SupportingLimbExtraLengthTrack::SetTimeEnd);
			properties[1] = property;
			property = new fight::PropertyNameList<SupportingLimbExtraLengthTrack>("supportingLimb", &SupportingLimbExtraLengthTrack::SetSupportingLimb);
			properties[2] = property;
			property = new fight::PropertyFloatConstRange<SupportingLimbExtraLengthTrack>("extraLength", &SupportingLimbExtraLengthTrack::SetExtraLength);
			properties[3] = property;
			fight::RegisterPropertyList(properties, &gSupportingLimbExtraLengthTrackProperties);
		}
	}

	template class fight::PropertyFloatConstRange<SupportingLimbExtraLengthTrack>;
	template class fight::PropertyNameList<SupportingLimbExtraLengthTrack>;
	template class fight::TrackFactoryTemplate<SupportingLimbExtraLengthTrack>;
	template class fight::TrackFactoryCasterTemplate<SupportingLimbExtraLengthTrack>;

	// FUNCTION: ENGINE 0x1092FDC0
	const fight::Name* SupportingLimbTrack::GetSupportingLimb() const
	{
		return &supportingLimb;
	}

	// FUNCTION: ENGINE 0x1092FDD0
	math::Vector SupportingLimbTrack::GetDirection() const
	{
		return direction;
	}

	// FUNCTION: ENGINE 0x1092FDF0
	const fight::Name* SupportingLimbExtraLengthTrack::GetSupportingLimb() const
	{
		return &supportingLimb;
	}

	// FUNCTION: ENGINE 0x1092FE00
	float SupportingLimbExtraLengthTrack::GetExtraLength() const
	{
		return extraLength;
	}
}
