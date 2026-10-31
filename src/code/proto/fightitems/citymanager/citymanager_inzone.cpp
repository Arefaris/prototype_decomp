// Fight items of the citymanager group: InZoneCondition (unit 0x1027DCE0 - 0x1027E100; no assert path, the file name is a guess).
#include "code/proto/fightitems/citymanager/citymanager_inzone.h"

namespace proto
{
	namespace fightitems
	{
		namespace citymanager
		{
			fight::Property** gInZoneConditionProperties;  // 0x11256200

			// FUNCTION: ENGINE 0x1027DDB0
			bool InZoneCondition::SetZoneType(int newValue)
			{
				zoneType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027DDC0
			fight::Property* InZoneCondition::GetProperty(int index)
			{
				return gInZoneConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1027DDE0
			void InZoneCondition::ClearProperties()
			{
				fight::FreePropertyList(&gInZoneConditionProperties);
			}

			// FUNCTION: ENGINE 0x1027DDF0
			InZoneCondition::InZoneCondition() : fight::Condition(0), zoneType(0)
			{
			}

			// FUNCTION: ENGINE 0x1027DE20
			InZoneCondition::~InZoneCondition()
			{
			}

			// FUNCTION: ENGINE 0x1027DF80
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void InZoneCondition::RegisterProperties()
			{
				if (gInZoneConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<InZoneCondition>("zoneType", gInZoneConditionZoneTypeTable, gInZoneConditionZoneTypeCount, &InZoneCondition::SetZoneType);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gInZoneConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1027DF50
			fight::ConditionFactory* CreateInZoneConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<InZoneCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1027E030
			void RegisterInZoneConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<InZoneCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			template class fight::PropertyEnumConstList<InZoneCondition>;
			template class fight::ConditionFactoryTemplate<InZoneCondition>;
			template class fight::ConditionFactoryCasterTemplate<InZoneCondition>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1027DE30
// FUNCTION: ENGINE 0x1027DE60
// FUNCTION: ENGINE 0x1027DE70
// FUNCTION: ENGINE 0x1027DEA0
// FUNCTION: ENGINE 0x1027DEE0
// FUNCTION: ENGINE 0x1027DEF0
// FUNCTION: ENGINE 0x1027DF20
// FUNCTION: ENGINE 0x1027DF40
// FUNCTION: ENGINE 0x1027E060
// FUNCTION: ENGINE 0x1027E090
// FUNCTION: ENGINE 0x1027E0B0
