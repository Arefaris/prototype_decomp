// Fight items of the ai group: DriverStateCondition, VehicleStateCondition, SetVehicleStateTrack (unit 0x10255E00 - 0x10256A40; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_vehiclestate.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gDriverStateConditionProperties;  // 0x11255C50

			// FUNCTION: ENGINE 0x10255E00
			bool DriverStateCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10255EF0
			bool DriverStateCondition::SetValue(const fight::Name& newValue)
			{
				value = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10255E60
			fight::Property* DriverStateCondition::GetProperty(int index)
			{
				return gDriverStateConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10255E80
			void DriverStateCondition::ClearProperties()
			{
				fight::FreePropertyList(&gDriverStateConditionProperties);
			}

			// FUNCTION: ENGINE 0x10255F50
			DriverStateCondition::DriverStateCondition() : fight::Condition(0), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x10255F80
			DriverStateCondition::~DriverStateCondition()
			{
			}

			// FUNCTION: ENGINE 0x10256570
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DriverStateCondition::RegisterProperties()
			{
				if (gDriverStateConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<DriverStateCondition>("compare", motion::gClassNameConditionCompareTable, motion::gClassNameConditionCompareCount, &DriverStateCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyName<DriverStateCondition>("value", &DriverStateCondition::SetValue);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gDriverStateConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10256360
			fight::ConditionFactory* CreateDriverStateConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DriverStateCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102563F0
			void RegisterDriverStateConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DriverStateCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gVehicleStateConditionProperties;  // 0x11255C54

			// FUNCTION: ENGINE 0x10255E10
			bool VehicleStateCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10255F10
			bool VehicleStateCondition::SetValue(const fight::Name& newValue)
			{
				value = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10255E90
			fight::Property* VehicleStateCondition::GetProperty(int index)
			{
				return gVehicleStateConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10255EB0
			void VehicleStateCondition::ClearProperties()
			{
				fight::FreePropertyList(&gVehicleStateConditionProperties);
			}

			// FUNCTION: ENGINE 0x10255F90
			VehicleStateCondition::VehicleStateCondition() : fight::Condition(0), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x10255FC0
			VehicleStateCondition::~VehicleStateCondition()
			{
			}

			// FUNCTION: ENGINE 0x10256660
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void VehicleStateCondition::RegisterProperties()
			{
				if (gVehicleStateConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<VehicleStateCondition>("compare", motion::gClassNameConditionCompareTable, motion::gClassNameConditionCompareCount, &VehicleStateCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyName<VehicleStateCondition>("value", &VehicleStateCondition::SetValue);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gVehicleStateConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10256390
			fight::ConditionFactory* CreateVehicleStateConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<VehicleStateCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10256420
			void RegisterVehicleStateConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<VehicleStateCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gSetVehicleStateTrackProperties;  // 0x11255C58

			// FUNCTION: ENGINE 0x10255E20
			bool SetVehicleStateTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10255E40
			bool SetVehicleStateTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10255F30
			bool SetVehicleStateTrack::SetValue(const fight::Name& newValue)
			{
				value = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10255EC0
			fight::Property* SetVehicleStateTrack::GetProperty(int index)
			{
				return gSetVehicleStateTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10255EE0
			void SetVehicleStateTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSetVehicleStateTrackProperties);
			}

			// FUNCTION: ENGINE 0x10255FD0
			SetVehicleStateTrack::SetVehicleStateTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x10256010
			float SetVehicleStateTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10256020
			float SetVehicleStateTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10256030
			SetVehicleStateTrack::~SetVehicleStateTrack()
			{
			}

			// FUNCTION: ENGINE 0x10256750
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SetVehicleStateTrack::RegisterProperties()
			{
				if (gSetVehicleStateTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<SetVehicleStateTrack>("timeBegin", &SetVehicleStateTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<SetVehicleStateTrack>("timeEnd", &SetVehicleStateTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyName<SetVehicleStateTrack>("value", &SetVehicleStateTrack::SetValue);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gSetVehicleStateTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x102563C0
			fight::TrackFactory* CreateSetVehicleStateTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SetVehicleStateTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10256450
			void RegisterSetVehicleStateTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SetVehicleStateTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyEnumConstList<DriverStateCondition>;
			template class fight::PropertyName<DriverStateCondition>;
			template class fight::ConditionFactoryTemplate<DriverStateCondition>;
			template class fight::ConditionFactoryCasterTemplate<DriverStateCondition>;
			template class fight::PropertyEnumConstList<VehicleStateCondition>;
			template class fight::PropertyName<VehicleStateCondition>;
			template class fight::ConditionFactoryTemplate<VehicleStateCondition>;
			template class fight::ConditionFactoryCasterTemplate<VehicleStateCondition>;
			template class fight::PropertyFloatConstRange<SetVehicleStateTrack>;
			template class fight::PropertyName<SetVehicleStateTrack>;
			template class fight::TrackFactoryTemplate<SetVehicleStateTrack>;
			template class fight::TrackFactoryCasterTemplate<SetVehicleStateTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10256040
// FUNCTION: ENGINE 0x10256050
// FUNCTION: ENGINE 0x10256080
// FUNCTION: ENGINE 0x10256090
// FUNCTION: ENGINE 0x102560C0
// FUNCTION: ENGINE 0x102560D0
// FUNCTION: ENGINE 0x10256100
// FUNCTION: ENGINE 0x10256130
// FUNCTION: ENGINE 0x10256160
// FUNCTION: ENGINE 0x10256190
// FUNCTION: ENGINE 0x102561D0
// FUNCTION: ENGINE 0x102561E0
// FUNCTION: ENGINE 0x10256210
// FUNCTION: ENGINE 0x10256230
// FUNCTION: ENGINE 0x10256240
// FUNCTION: ENGINE 0x10256280
// FUNCTION: ENGINE 0x10256290
// FUNCTION: ENGINE 0x102562C0
// FUNCTION: ENGINE 0x102562E0
// FUNCTION: ENGINE 0x102562F0
// FUNCTION: ENGINE 0x10256320
// FUNCTION: ENGINE 0x10256350
// FUNCTION: ENGINE 0x10256480
// FUNCTION: ENGINE 0x102564B0
// FUNCTION: ENGINE 0x102564D0
// FUNCTION: ENGINE 0x10256500
// FUNCTION: ENGINE 0x10256520
// FUNCTION: ENGINE 0x10256550
// FUNCTION: ENGINE 0x10256860
// FUNCTION: ENGINE 0x10256890
// FUNCTION: ENGINE 0x102568B0
// FUNCTION: ENGINE 0x102568E0
// FUNCTION: ENGINE 0x10256900
// FUNCTION: ENGINE 0x10256930
// FUNCTION: ENGINE 0x10256950
// FUNCTION: ENGINE 0x102569A0
// FUNCTION: ENGINE 0x102569F0
