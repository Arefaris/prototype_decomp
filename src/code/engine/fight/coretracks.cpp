// The tracks and actions of the fight core itself (see coretracks.h).
#include "code/engine/fight/coretracks.h"
#include <new>

namespace fight
{
	// GLOBAL: ENGINE 0x11276134
	Property** gOnEventTrackProperties;
	// GLOBAL: ENGINE 0x11276140
	const EnumEntry* gEventMaskTable;
	// GLOBAL: ENGINE 0x11276144
	int gEventMaskCount;

	// ---- fight::OnEventTrack -------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105A5F20
	bool OnEventTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x105A5F30
	bool OnEventTrack::SetTimeEnd(float newValue)
	{
		timeEnd = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x105A5F40
	bool OnEventTrack::SetTimeHook(float newValue)
	{
		timeHook = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x105A5F50
	bool OnEventTrack::SetEventMask(int newValue)
	{
		eventMask = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x105A5F60
	bool OnEventTrack::SetInitialTest(bool newValue)
	{
		initialTest = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x105A5F70
	BranchHolder* OnEventTrack::GetBranch()
	{
		return &branch;
	}

	// FUNCTION: ENGINE 0x105A5F80
	bool OnEventTrack::SetPriority(int newValue)
	{
		priority = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x105A5F90
	ConditionList* OnEventTrack::GetConditions()
	{
		return &conditions;
	}

	// FUNCTION: ENGINE 0x105A5FA0
	Property* OnEventTrack::GetProperty(int index)
	{
		return gOnEventTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x105A5FB0
	void OnEventTrack::ClearProperties()
	{
		FreePropertyList(&gOnEventTrackProperties);
	}

	// FUNCTION: ENGINE 0x105A5FC0
	OnEventTrack::OnEventTrack() : branch(0), timeBegin(0.0f), timeEnd(-1.0f), timeHook(0.0f), priority(0), eventMask(-1), initialTest(false)
	{
		unknownC = 1;
	}

	// FUNCTION: ENGINE 0x105A6020
	float OnEventTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x105A6030
	float OnEventTrack::Slot10() const
	{
		return -1.0f;
	}

	// FUNCTION: ENGINE 0x105A6040
	OnEventTrack::~OnEventTrack()
	{
	}

	// FUNCTION: ENGINE 0x105A62B0
	TrackFactory* CreateOnEventTrackFactory(const char* name)
	{
		TrackFactoryCasterTemplate<OnEventTrack> caster;
		return FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x105A62D0
	// EQUIVALENT: shrink-wrap
	void OnEventTrack::RegisterProperties()
	{
		if (gOnEventTrackProperties == 0)
		{
			Property* properties[256] = { 0 };
			Property* property = 0;
			property = new PropertyFloatConstRange<OnEventTrack>("timeBegin", &OnEventTrack::SetTimeBegin);
			properties[0] = property;
			property = new PropertyFloatConstRange<OnEventTrack>("timeEnd", &OnEventTrack::SetTimeEnd);
			properties[1] = property;
			property = new PropertyFloatConstRange<OnEventTrack>("timeHook", &OnEventTrack::SetTimeHook);
			properties[2] = property;
			property = new PropertyBitfield<OnEventTrack>("eventMask", &OnEventTrack::GetEventMaskEntry, &OnEventTrack::GetEventMaskCount, &OnEventTrack::SetEventMask);
			properties[3] = property;
			property = new PropertyBool<OnEventTrack>("initialTest", &OnEventTrack::SetInitialTest);
			properties[4] = property;
			property = new PropertyBranch<OnEventTrack>("branch", &OnEventTrack::GetBranch);
			properties[5] = property;
			property = new PropertyIntConstRange<OnEventTrack>("priority", &OnEventTrack::SetPriority);
			properties[6] = property;
			property = new PropertyConditionGroup<OnEventTrack>("conditions", &OnEventTrack::GetConditions);
			properties[7] = property;
			RegisterPropertyList(properties, &gOnEventTrackProperties);
		}
	}

	template class PropertyFloatConstRange<OnEventTrack>;
	template class PropertyBitfield<OnEventTrack>;
	template class PropertyBool<OnEventTrack>;
	template class PropertyBranch<OnEventTrack>;
	template class PropertyIntConstRange<OnEventTrack>;
	template class PropertyConditionGroup<OnEventTrack>;
	template class TrackFactoryTemplate<OnEventTrack>;
	template class TrackFactoryCasterTemplate<OnEventTrack>;

	// FUNCTION: ENGINE 0x105A64B0
	void RegisterEventTrackFactory(TrackRegistry* registry, const char* name)
	{
		TrackFactoryCasterTemplate<OnEventTrack> caster;
		registry->AddFactory(FindTrackFactory(name, &caster));
	}

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
	// FUNCTION: ENGINE 0x105A6E10
	float OnEventTrack::GetTimeEnd() const
	{
		return timeEnd;
	}

	// FUNCTION: ENGINE 0x105A6E20
	float OnEventTrack::GetTimeHook() const
	{
		return timeHook;
	}

	// FUNCTION: ENGINE 0x105A6E30
	int OnEventTrack::GetEventMask() const
	{
		return eventMask;
	}

	// FUNCTION: ENGINE 0x105A6E40
	bool OnEventTrack::GetInitialTest() const
	{
		return initialTest;
	}

	// FUNCTION: ENGINE 0x105A6E50
	BranchHolder* OnEventTrack::GetBranchOf()
	{
		return &branch;
	}

	// FUNCTION: ENGINE 0x105A6E60
	int OnEventTrack::GetPriority() const
	{
		return priority;
	}

	// FUNCTION: ENGINE 0x105A6E70
	ConditionList* OnEventTrack::GetConditionsOf()
	{
		return &conditions;
	}

	// FUNCTION: ENGINE 0x105A6E80
	void SetEventMaskTable(const EnumEntry* table, int count)
	{
		gEventMaskTable = table;
		gEventMaskCount = count;
	}

	// FUNCTION: ENGINE 0x105A6EA0
	const EnumEntry* OnEventTrack::GetEventMaskEntry(int index)
	{
		if (gEventMaskTable != 0 && index >= 0 && index < gEventMaskCount)
		{
			return &gEventMaskTable[index];
		}
		return reinterpret_cast<const EnumEntry*>(core::GetStringHeapCounter1());
	}

	// FUNCTION: ENGINE 0x105A6ED0
	int OnEventTrack::GetEventMaskCount()
	{
		return gEventMaskCount;
	}

}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x105A6090
// FUNCTION: ENGINE 0x105A60A0
// FUNCTION: ENGINE 0x105A60D0
// FUNCTION: ENGINE 0x105A60F0
// FUNCTION: ENGINE 0x105A6110
// FUNCTION: ENGINE 0x105A6120
// FUNCTION: ENGINE 0x105A6150
// FUNCTION: ENGINE 0x105A6170
// FUNCTION: ENGINE 0x105A6180
// FUNCTION: ENGINE 0x105A61A0
// FUNCTION: ENGINE 0x105A61B0
// FUNCTION: ENGINE 0x105A61D0
// FUNCTION: ENGINE 0x105A61F0
// FUNCTION: ENGINE 0x105A6200
// FUNCTION: ENGINE 0x105A6220
// FUNCTION: ENGINE 0x105A6230
// FUNCTION: ENGINE 0x105A6250
// FUNCTION: ENGINE 0x105A6270
// FUNCTION: ENGINE 0x105A6280
// FUNCTION: ENGINE 0x105A62A0
// FUNCTION: ENGINE 0x105A64E0
// FUNCTION: ENGINE 0x105A6510
// FUNCTION: ENGINE 0x105A6530
// FUNCTION: ENGINE 0x105A67B0
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
// FUNCTION: ENGINE 0x105A6B60
// FUNCTION: ENGINE 0x105A6B80
// FUNCTION: ENGINE 0x105A6B90
// FUNCTION: ENGINE 0x105A6BC0
// FUNCTION: ENGINE 0x105A6BE0
// FUNCTION: ENGINE 0x105A6C00
// FUNCTION: ENGINE 0x105A6D40
// FUNCTION: ENGINE 0x105A6D70
// FUNCTION: ENGINE 0x105A6D90
