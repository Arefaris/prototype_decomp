// The tracks and actions of the fight core itself (see coretracks.h).
#include "code/engine/fight/coretracks.h"
#include <new>

namespace fight
{
	// GLOBAL: ENGINE 0x11276138
	Property** gSpawnTrackProperties;

	// ---- fight::SpawnTrack ---------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105A66C0
	bool SpawnTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x105A66D0
	bool SpawnTrack::SetTimeEnd(float newValue)
	{
		timeEnd = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x105A66E0
	BranchHolder* SpawnTrack::GetBranch()
	{
		return &branch;
	}

	// FUNCTION: ENGINE 0x105A66F0
	ConditionList* SpawnTrack::GetConditions()
	{
		return &conditions;
	}

	// FUNCTION: ENGINE 0x105A6700
	Property* SpawnTrack::GetProperty(int index)
	{
		return gSpawnTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x105A6710
	void SpawnTrack::ClearProperties()
	{
		FreePropertyList(&gSpawnTrackProperties);
	}

	// FUNCTION: ENGINE 0x105A6720
	SpawnTrack::SpawnTrack() : branch(0), timeBegin(0.0f), timeEnd(-1.0f)
	{
		unknownC = 1;
	}

	// FUNCTION: ENGINE 0x105A6760
	float SpawnTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x105A6770
	float SpawnTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x105A6780
	SpawnTrack::~SpawnTrack()
	{
	}

	// FUNCTION: ENGINE 0x105A68E0
	// EQUIVALENT: shrink-wrap
	void SpawnTrack::RegisterProperties()
	{
		if (gSpawnTrackProperties == 0)
		{
			Property* properties[256] = { 0 };
			Property* property = 0;
			property = new PropertyFloatConstRange<SpawnTrack>("timeBegin", &SpawnTrack::SetTimeBegin);
			properties[0] = property;
			property = new PropertyFloatConstRange<SpawnTrack>("timeEnd", &SpawnTrack::SetTimeEnd);
			properties[1] = property;
			property = new PropertyBranch<SpawnTrack>("branch", &SpawnTrack::GetBranch);
			properties[2] = property;
			property = new PropertyConditionGroup<SpawnTrack>("conditions", &SpawnTrack::GetConditions);
			properties[3] = property;
			RegisterPropertyList(properties, &gSpawnTrackProperties);
		}
	}

	template class PropertyFloatConstRange<SpawnTrack>;
	template class PropertyBranch<SpawnTrack>;
	template class PropertyConditionGroup<SpawnTrack>;
	template class TrackFactoryTemplate<SpawnTrack>;
	template class TrackFactoryCasterTemplate<SpawnTrack>;

	// FUNCTION: ENGINE 0x105A68C0
	TrackFactory* CreateSpawnTrackFactory(const char* name)
	{
		TrackFactoryCasterTemplate<SpawnTrack> caster;
		return FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x105A69F0
	void RegisterSpawnTrackFactory(TrackRegistry* registry, const char* name)
	{
		TrackFactoryCasterTemplate<SpawnTrack> caster;
		registry->AddFactory(FindTrackFactory(name, &caster));
	}

	// GLOBAL: ENGINE 0x1127613C
	Property** gWaitTrackProperties;

	// ---- fight::WaitTrack ----------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105A6AB0
	bool WaitTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x105A6AC0
	bool WaitTrack::SetTimeEndMin(float newValue)
	{
		timeEndMin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x105A6AD0
	bool WaitTrack::SetTimeEndMax(float newValue)
	{
		timeEndMax = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x105A6AE0
	Property* WaitTrack::GetProperty(int index)
	{
		return gWaitTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x105A6AF0
	void WaitTrack::ClearProperties()
	{
		FreePropertyList(&gWaitTrackProperties);
	}

	// FUNCTION: ENGINE 0x105A6B00
	WaitTrack::WaitTrack() : timeBegin(0.0f), timeEndMax(0.0f), timeEndMin(0.0f)
	{
	}

	// FUNCTION: ENGINE 0x105A6B30
	float WaitTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x105A6B40
	float WaitTrack::Slot10() const
	{
		return -1.0f;
	}

	// FUNCTION: ENGINE 0x105A6B50
	WaitTrack::~WaitTrack()
	{
	}

	// FUNCTION: ENGINE 0x105A6C30
	// EQUIVALENT: shrink-wrap (97.7 %)
	void WaitTrack::RegisterProperties()
	{
		if (gWaitTrackProperties == 0)
		{
			Property* properties[256] = { 0 };
			Property* property = 0;
			property = new PropertyFloatConstRange<WaitTrack>("timeBegin", &WaitTrack::SetTimeBegin);
			properties[0] = property;
			property = new PropertyFloatConstRange<WaitTrack>("timeEndMin", &WaitTrack::SetTimeEndMin);
			properties[1] = property;
			property = new PropertyFloatConstRange<WaitTrack>("timeEndMax", &WaitTrack::SetTimeEndMax);
			properties[2] = property;
			RegisterPropertyList(properties, &gWaitTrackProperties);
		}
	}

	template class PropertyFloatConstRange<WaitTrack>;
	template class TrackFactoryTemplate<WaitTrack>;
	template class TrackFactoryCasterTemplate<WaitTrack>;

	// FUNCTION: ENGINE 0x105A6C10
	TrackFactory* CreateWaitTrackFactory(const char* name)
	{
		TrackFactoryCasterTemplate<WaitTrack> caster;
		return FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x105A6D10
	void RegisterWaitTrackFactory(TrackRegistry* registry, const char* name)
	{
		TrackFactoryCasterTemplate<WaitTrack> caster;
		registry->AddFactory(FindTrackFactory(name, &caster));
	}
}


// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x105A67D0
// FUNCTION: ENGINE 0x105A67E0
// FUNCTION: ENGINE 0x105A6810
// FUNCTION: ENGINE 0x105A6830
// FUNCTION: ENGINE 0x105A6850
// FUNCTION: ENGINE 0x105A6860
// FUNCTION: ENGINE 0x105A6880
// FUNCTION: ENGINE 0x105A6890
// FUNCTION: ENGINE 0x105A68B0
// FUNCTION: ENGINE 0x105A6A20
// FUNCTION: ENGINE 0x105A6A50
// FUNCTION: ENGINE 0x105A6A70
// FUNCTION: ENGINE 0x105A6B80
// FUNCTION: ENGINE 0x105A6B90
// FUNCTION: ENGINE 0x105A6BC0
// FUNCTION: ENGINE 0x105A6BE0
// FUNCTION: ENGINE 0x105A6C00
// FUNCTION: ENGINE 0x105A6D40
// FUNCTION: ENGINE 0x105A6D70
// FUNCTION: ENGINE 0x105A6D90
