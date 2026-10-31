#include "code/proto/nis/nisexcludevolume.h"

namespace proto
{
	// The entries of the action on props property and how many there are (data of the start-up code)
	fight::EnumEntry gNISExcludeActionTable[5] =
		{
			{ fight::Name("DoNothing", 0) },
			{ fight::Name("Hide", 0) },
			{ fight::Name("HideOnlyDisplacedOrGenerated", 0) },
			{ fight::Name("Delete", 0) },
			{ fight::Name("DeleteOnlyDisplacedOrGenerated", 0) }
		};
	extern const int gNISExcludeActionCount;

	fight::Property** gNISExcludeVolumeTrackProperties;  // 0x112738AC

	// FUNCTION: ENGINE 0x10577D10
	bool NISExcludeVolumeTrack::SetTimeBegin(float value)
	{
		timeBegin = value;
		return true;
	}

	// FUNCTION: ENGINE 0x10577D30
	bool NISExcludeVolumeTrack::SetTimeEnd(float value)
	{
		timeEnd = value;
		return true;
	}

	// FUNCTION: ENGINE 0x10577DF0
	bool NISExcludeVolumeTrack::SetVolumeName1(const fight::Name& value)
	{
		volumeName1 = value;
		return true;
	}

	// FUNCTION: ENGINE 0x10577E10
	bool NISExcludeVolumeTrack::SetVolumeName2(const fight::Name& value)
	{
		volumeName2 = value;
		return true;
	}

	// FUNCTION: ENGINE 0x10577E30
	bool NISExcludeVolumeTrack::SetVolumeName3(const fight::Name& value)
	{
		volumeName3 = value;
		return true;
	}

	// FUNCTION: ENGINE 0x10577D50
	bool NISExcludeVolumeTrack::SetActionOnProps(int value)
	{
		actionOnProps = value;
		return true;
	}

	// FUNCTION: ENGINE 0x10577D60
	bool NISExcludeVolumeTrack::SetHideAndBlockAmbients(bool value)
	{
		hideAndBlockAmbients = value;
		return true;
	}

	// FUNCTION: ENGINE 0x10577D70
	bool NISExcludeVolumeTrack::SetHideAndBlockDrivables(bool value)
	{
		hideAndBlockDrivables = value;
		return true;
	}

	// FUNCTION: ENGINE 0x10577D80
	bool NISExcludeVolumeTrack::SetHideAndBlockWalkers(bool value)
	{
		hideAndBlockWalkers = value;
		return true;
	}

	// FUNCTION: ENGINE 0x10577D90
	bool NISExcludeVolumeTrack::SetHideAndBlockHunters(bool value)
	{
		hideAndBlockHunters = value;
		return true;
	}

	// FUNCTION: ENGINE 0x10577DA0
	bool NISExcludeVolumeTrack::SetDeleteDeadBodies(bool value)
	{
		deleteDeadBodies = value;
		return true;
	}

	// FUNCTION: ENGINE 0x10577DB0
	bool NISExcludeVolumeTrack::SetMaxHiddenObjects(int value)
	{
		maxHiddenObjects = value;
		return true;
	}

	// FUNCTION: ENGINE 0x10577DC0
	fight::Property* NISExcludeVolumeTrack::GetProperty(int index)
	{
		return gNISExcludeVolumeTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x10577DE0
	void NISExcludeVolumeTrack::ClearProperties()
	{
		fight::FreePropertyList(&gNISExcludeVolumeTrackProperties);
	}

	// FUNCTION: ENGINE 0x10577E50
	NISExcludeVolumeTrack::NISExcludeVolumeTrack() : timeBegin(0.0f), timeEnd(-1.0f), actionOnProps(0),
		maxHiddenObjects(0x100), deleteDeadBodies(false), hideAndBlockAmbients(false), hideAndBlockDrivables(false),
		hideAndBlockHunters(false), hideAndBlockWalkers(false)
	{
		unknownC = 1;
	}

	// FUNCTION: ENGINE 0x10577ED0
	float NISExcludeVolumeTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x10577EE0
	float NISExcludeVolumeTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x10577EF0
	NISExcludeVolumeTrack::~NISExcludeVolumeTrack()
	{
	}

	// FUNCTION: ENGINE 0x10578200
	// EQUIVALENT: shrink-wrap (the engine saves esi in the entry block, before the guard's branch; ours sinks the push
	// behind it)
	void NISExcludeVolumeTrack::RegisterProperties()
	{
		if (gNISExcludeVolumeTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<NISExcludeVolumeTrack>("timeBegin",
				&NISExcludeVolumeTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<NISExcludeVolumeTrack>("timeEnd",
				&NISExcludeVolumeTrack::SetTimeEnd);
			properties[1] = property;
			property = new fight::PropertyName<NISExcludeVolumeTrack>("volumeName1", &NISExcludeVolumeTrack::SetVolumeName1);
			properties[2] = property;
			property = new fight::PropertyName<NISExcludeVolumeTrack>("volumeName2", &NISExcludeVolumeTrack::SetVolumeName2);
			properties[3] = property;
			property = new fight::PropertyName<NISExcludeVolumeTrack>("volumeName3", &NISExcludeVolumeTrack::SetVolumeName3);
			properties[4] = property;
			property = new fight::PropertyEnumConstList<NISExcludeVolumeTrack>("actionOnProps", gNISExcludeActionTable,
				gNISExcludeActionCount, &NISExcludeVolumeTrack::SetActionOnProps);
			properties[5] = property;
			property = new fight::PropertyBool<NISExcludeVolumeTrack>("hideAndBlockAmbients",
				&NISExcludeVolumeTrack::SetHideAndBlockAmbients);
			properties[6] = property;
			property = new fight::PropertyBool<NISExcludeVolumeTrack>("hideAndBlockDrivables",
				&NISExcludeVolumeTrack::SetHideAndBlockDrivables);
			properties[7] = property;
			property = new fight::PropertyBool<NISExcludeVolumeTrack>("hideAndBlockWalkers",
				&NISExcludeVolumeTrack::SetHideAndBlockWalkers);
			properties[8] = property;
			property = new fight::PropertyBool<NISExcludeVolumeTrack>("hideAndBlockHunters",
				&NISExcludeVolumeTrack::SetHideAndBlockHunters);
			properties[9] = property;
			property = new fight::PropertyBool<NISExcludeVolumeTrack>("deleteDeadBodies",
				&NISExcludeVolumeTrack::SetDeleteDeadBodies);
			properties[10] = property;
			property = new fight::PropertyIntConstRange<NISExcludeVolumeTrack>("maxHiddenObjects",
				&NISExcludeVolumeTrack::SetMaxHiddenObjects);
			properties[11] = property;
			fight::RegisterPropertyList(properties, &gNISExcludeVolumeTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x10578150
	fight::TrackFactory* CreateNISExcludeVolumeTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<NISExcludeVolumeTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x10578180
	void RegisterNISExcludeVolumeTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<NISExcludeVolumeTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyBool<NISExcludeVolumeTrack>;
	template class fight::PropertyEnumConstList<NISExcludeVolumeTrack>;
	template class fight::PropertyFloatConstRange<NISExcludeVolumeTrack>;
	template class fight::PropertyIntConstRange<NISExcludeVolumeTrack>;
	template class fight::PropertyName<NISExcludeVolumeTrack>;
	template class fight::TrackFactoryTemplate<NISExcludeVolumeTrack>;
	template class fight::TrackFactoryCasterTemplate<NISExcludeVolumeTrack>;
}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D62630
// FUNCTION: ENGINE 0x10D86110


// Kept copies (template instances and wrappers of this unit):
// FUNCTION: ENGINE 0x10577F00
// FUNCTION: ENGINE 0x10577F10
// FUNCTION: ENGINE 0x10577F40
// FUNCTION: ENGINE 0x10577F70
// FUNCTION: ENGINE 0x10577FA0
// FUNCTION: ENGINE 0x10577FD0
// FUNCTION: ENGINE 0x10577FE0
// FUNCTION: ENGINE 0x10578020
// FUNCTION: ENGINE 0x10578030
// FUNCTION: ENGINE 0x10578060
// FUNCTION: ENGINE 0x10578080
// FUNCTION: ENGINE 0x10578090
// FUNCTION: ENGINE 0x105780C0
// FUNCTION: ENGINE 0x105780E0
// FUNCTION: ENGINE 0x105780F0
// FUNCTION: ENGINE 0x10578120
// FUNCTION: ENGINE 0x10578140
// FUNCTION: ENGINE 0x105781B0
// FUNCTION: ENGINE 0x105781E0
// FUNCTION: ENGINE 0x10578550
// FUNCTION: ENGINE 0x10578580
// FUNCTION: ENGINE 0x105785A0
