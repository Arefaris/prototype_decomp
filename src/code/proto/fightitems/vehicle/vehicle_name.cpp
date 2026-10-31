// Fight items of the vehicle group: VehicleNameCondition (unit 0x1027D9F0 - 0x1027DCE0; no assert path, the file name is a guess).
#include "code/proto/fightitems/vehicle/vehicle_name.h"

namespace proto
{
	namespace fightitems
	{
		namespace vehicle
		{
			fight::Property** gVehicleNameConditionProperties;  // 0x112561C8

			// FUNCTION: ENGINE 0x1027DA20
			bool VehicleNameCondition::SetName(const fight::Name& newValue)
			{
				name = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027D9F0
			fight::Property* VehicleNameCondition::GetProperty(int index)
			{
				return gVehicleNameConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1027DA10
			void VehicleNameCondition::ClearProperties()
			{
				fight::FreePropertyList(&gVehicleNameConditionProperties);
			}

			// FUNCTION: ENGINE 0x1027DA40
			VehicleNameCondition::VehicleNameCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x1027DA70
			VehicleNameCondition::~VehicleNameCondition()
			{
			}

			// FUNCTION: ENGINE 0x1027DBA0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void VehicleNameCondition::RegisterProperties()
			{
				if (gVehicleNameConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyName<VehicleNameCondition>("name", &VehicleNameCondition::SetName);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gVehicleNameConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1027DAF0
			fight::ConditionFactory* CreateVehicleNameConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<VehicleNameCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1027DB20
			void RegisterVehicleNameConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<VehicleNameCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			template class fight::PropertyName<VehicleNameCondition>;
			template class fight::ConditionFactoryTemplate<VehicleNameCondition>;
			template class fight::ConditionFactoryCasterTemplate<VehicleNameCondition>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1027DA80
// FUNCTION: ENGINE 0x1027DA90
// FUNCTION: ENGINE 0x1027DAC0
// FUNCTION: ENGINE 0x1027DB50
// FUNCTION: ENGINE 0x1027DB80
// FUNCTION: ENGINE 0x1027DC40
// FUNCTION: ENGINE 0x1027DC70
// FUNCTION: ENGINE 0x1027DC90
