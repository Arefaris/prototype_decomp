// Fight items of the proplogic group: ShootingEventCondition (unit 0x1025E0E0 - 0x1025EFA0; no assert path, the file name is a guess).
#include "code/proto/fightitems/proplogic/proplogic_shootingevent.h"

namespace proto
{
	namespace fightitems
	{
		namespace proplogic
		{
			fight::Property** gShootingEventConditionProperties;  // 0x11255D08

			// FUNCTION: ENGINE 0x1025EC50
			bool ShootingEventCondition::SetEvent(int newValue)
			{
				event = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025EC60
			fight::Property* ShootingEventCondition::GetProperty(int index)
			{
				return gShootingEventConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1025EC80
			void ShootingEventCondition::ClearProperties()
			{
				fight::FreePropertyList(&gShootingEventConditionProperties);
			}

			// FUNCTION: ENGINE 0x1025EC90
			ShootingEventCondition::ShootingEventCondition() : fight::Condition(0), event(0)
			{
			}

			// FUNCTION: ENGINE 0x1025ECC0
			ShootingEventCondition::~ShootingEventCondition()
			{
			}

			// FUNCTION: ENGINE 0x1025EE20
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ShootingEventCondition::RegisterProperties()
			{
				if (gShootingEventConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<ShootingEventCondition>("event", gShootingEventConditionEventTable, 4, &ShootingEventCondition::SetEvent);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gShootingEventConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1025EDF0
			fight::ConditionFactory* CreateShootingEventConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ShootingEventCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1025EED0
			void RegisterShootingEventConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ShootingEventCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			template class fight::PropertyEnumConstList<ShootingEventCondition>;
			template class fight::ConditionFactoryTemplate<ShootingEventCondition>;
			template class fight::ConditionFactoryCasterTemplate<ShootingEventCondition>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1025ECD0
// FUNCTION: ENGINE 0x1025ED00
// FUNCTION: ENGINE 0x1025ED10
// FUNCTION: ENGINE 0x1025ED40
// FUNCTION: ENGINE 0x1025ED80
// FUNCTION: ENGINE 0x1025ED90
// FUNCTION: ENGINE 0x1025EDC0
// FUNCTION: ENGINE 0x1025EDE0
// FUNCTION: ENGINE 0x1025EF00
// FUNCTION: ENGINE 0x1025EF30
// FUNCTION: ENGINE 0x1025EF50
