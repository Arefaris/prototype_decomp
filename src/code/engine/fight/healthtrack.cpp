// The fight track that changes an object's health (unit 0x10815010 - 0x10815900).
#include "code/engine/fight/healthtrack.h"

namespace engine
{
	fight::EnumEntry gHealthTrackOperationTable[3] =
		{
			{ fight::Name("Set", 0) },
			{ fight::Name("Add", 0) },
			{ fight::Name("Multiply", 0) }
		};
	fight::EnumEntry gHealthTrackApplyToTable[3] =
		{
			{ fight::Name("Current health (absolute value)", 0) },
			{ fight::Name("Percentage of current health", 0) },
			{ fight::Name("Percentage of maximum health", 0) }
		};

	fight::Property** gHealthTrackProperties;  // 0x11284C00

	// FUNCTION: ENGINE 0x10814FF0
	bool HealthTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10815000
	bool HealthTrack::SetOperation(int newValue)
	{
		operation = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10815010
	bool HealthTrack::SetApplyTo(int newValue)
	{
		applyTo = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10815020
	bool HealthTrack::SetHealth(float newValue)
	{
		health = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10815030
	bool HealthTrack::SetChangeMaxHealth(bool newValue)
	{
		changeMaxHealth = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10815040
	bool HealthTrack::SetChangeMinHealth(bool newValue)
	{
		changeMinHealth = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10815050
	fight::Property* HealthTrack::GetProperty(int index)
	{
		return gHealthTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x10815060
	void HealthTrack::ClearProperties()
	{
		fight::FreePropertyList(&gHealthTrackProperties);
	}

	// FUNCTION: ENGINE 0x10815070
	// ctor stores: [('mov', 'dword', 24, '0'), ('mov', 'dword', 28, '0'), ('mov', 'byte', 32, '0'), ('mov', 'byte', 33, '0'), ('mov', 'dword', 0, '0x10e6d364'), ('movss', 'dword', 16, '0.0f'), ('movss', 'dword', 20, '0.0f')]
	HealthTrack::HealthTrack() : health(0.0f), timeBegin(0.0f), applyTo(0), operation(0), changeMaxHealth(false), changeMinHealth(false)
	{
	}

	// FUNCTION: ENGINE 0x108150A0
	float HealthTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108150B0
	float HealthTrack::Slot10() const
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x108150C0
	HealthTrack::~HealthTrack()
	{
	}

	// FUNCTION: ENGINE 0x10815280
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void HealthTrack::RegisterProperties()
	{
		if (gHealthTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<HealthTrack>("timeBegin", &HealthTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyEnumConstList<HealthTrack>("operation", gHealthTrackOperationTable, 3, &HealthTrack::SetOperation);
			properties[1] = property;
			property = new fight::PropertyEnumConstList<HealthTrack>("applyTo", gHealthTrackApplyToTable, 3, &HealthTrack::SetApplyTo);
			properties[2] = property;
			property = new fight::PropertyFloatConstRange<HealthTrack>("health", &HealthTrack::SetHealth);
			properties[3] = property;
			property = new fight::PropertyBool<HealthTrack>("changeMaxHealth", &HealthTrack::SetChangeMaxHealth);
			properties[4] = property;
			property = new fight::PropertyBool<HealthTrack>("changeMinHealth", &HealthTrack::SetChangeMinHealth);
			properties[5] = property;
			fight::RegisterPropertyList(properties, &gHealthTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x10815260
	fight::TrackFactory* CreateHealthTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<HealthTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x10815410
	void RegisterHealthTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<HealthTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyBool<HealthTrack>;
	template class fight::PropertyEnumConstList<HealthTrack>;
	template class fight::PropertyFloatConstRange<HealthTrack>;
	template class fight::TrackFactoryTemplate<HealthTrack>;
	template class fight::TrackFactoryCasterTemplate<HealthTrack>;

}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D74BE0
// FUNCTION: ENGINE 0x10D74C20
// FUNCTION: ENGINE 0x10D8A020
// FUNCTION: ENGINE 0x10D8A030
