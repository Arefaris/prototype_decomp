// The fight tracks that clear decals and set the effect timers (unit 0x10810E00 - 0x10811750).
#include "code/engine/fight/effecttimertracks.h"

namespace engine
{
	fight::Property** gDeleteAllDecalsTrackProperties;  // 0x11284BA0

	// FUNCTION: ENGINE 0x10810E00
	bool DeleteAllDecalsTrack::SetTimeBegin(float value)
	{
		timeBegin = value;
		return true;
	}

	// FUNCTION: ENGINE 0x10810E10
	fight::Property* DeleteAllDecalsTrack::GetProperty(int index)
	{
		return gDeleteAllDecalsTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x10810E20
	void DeleteAllDecalsTrack::ClearProperties()
	{
		fight::FreePropertyList(&gDeleteAllDecalsTrackProperties);
	}

	// FUNCTION: ENGINE 0x10810E30
	// ctor stores: [('mov', 'dword', 0, '0x10e6c8d4'), ('movss', 'dword', 16, 'xmm0')]
	DeleteAllDecalsTrack::DeleteAllDecalsTrack() : timeBegin(0.0f)
	{
	}

	// FUNCTION: ENGINE 0x10810E50  // fld dword ptr [ecx + 0x10]; ret 
	float DeleteAllDecalsTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x10810E60  // fldz ; ret 
	float DeleteAllDecalsTrack::Slot10() const
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x10810E70
	DeleteAllDecalsTrack::~DeleteAllDecalsTrack()
	{
	}

	// FUNCTION: ENGINE 0x10810F50
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void DeleteAllDecalsTrack::RegisterProperties()
	{
		if (gDeleteAllDecalsTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<DeleteAllDecalsTrack>("timeBegin", &DeleteAllDecalsTrack::SetTimeBegin);
			properties[0] = property;
			fight::RegisterPropertyList(properties, &gDeleteAllDecalsTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x10810F30
	fight::TrackFactory* CreateDeleteAllDecalsTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<DeleteAllDecalsTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x10810FD0
	void RegisterDeleteAllDecalsTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<DeleteAllDecalsTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyFloatConstRange<DeleteAllDecalsTrack>;
	template class fight::TrackFactoryTemplate<DeleteAllDecalsTrack>;
	template class fight::TrackFactoryCasterTemplate<DeleteAllDecalsTrack>;

}
