// Fight items of the scenario group: StateChangeCondition, CurrentStateCondition (unit 0x101DA5C0 - 0x101DABA0; no assert path, the file name is a guess).
#include "code/proto/fightitems/scenario/scenario_statecondition.h"

namespace proto
{
	namespace fightitems
	{
		namespace scenario
		{
			fight::Property** gStateChangeConditionProperties;  // 0x11254DC4

			// FUNCTION: ENGINE 0x101DA5C0
			fight::BranchHolder* StateChangeCondition::SetState()
			{
				return &state;
			}

			// FUNCTION: ENGINE 0x101DA5E0
			fight::Property* StateChangeCondition::GetProperty(int index)
			{
				return gStateChangeConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101DA600
			void StateChangeCondition::ClearProperties()
			{
				fight::FreePropertyList(&gStateChangeConditionProperties);
			}

			// FUNCTION: ENGINE 0x101DA610
			StateChangeCondition::StateChangeCondition() : fight::Condition(0), state(0)
			{
			}

			// FUNCTION: ENGINE 0x101DA640
			StateChangeCondition::~StateChangeCondition()
			{
			}

			// FUNCTION: ENGINE 0x101DA8C0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void StateChangeCondition::RegisterProperties()
			{
				if (gStateChangeConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBranch<StateChangeCondition>("state", &StateChangeCondition::SetState);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gStateChangeConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101DA860
			fight::ConditionFactory* CreateStateChangeConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<StateChangeCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101DAA00
			void RegisterStateChangeConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<StateChangeCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gCurrentStateConditionProperties;  // 0x11254DC8

			// FUNCTION: ENGINE 0x101DA5D0
			fight::BranchHolder* CurrentStateCondition::SetState()
			{
				return &state;
			}

			// FUNCTION: ENGINE 0x101DA660
			fight::Property* CurrentStateCondition::GetProperty(int index)
			{
				return gCurrentStateConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101DA680
			void CurrentStateCondition::ClearProperties()
			{
				fight::FreePropertyList(&gCurrentStateConditionProperties);
			}

			// FUNCTION: ENGINE 0x101DA690
			CurrentStateCondition::CurrentStateCondition() : fight::Condition(0), state(0)
			{
			}

			// FUNCTION: ENGINE 0x101DA6C0
			CurrentStateCondition::~CurrentStateCondition()
			{
			}

			// FUNCTION: ENGINE 0x101DA960
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void CurrentStateCondition::RegisterProperties()
			{
				if (gCurrentStateConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBranch<CurrentStateCondition>("state", &CurrentStateCondition::SetState);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gCurrentStateConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101DA890
			fight::ConditionFactory* CreateCurrentStateConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<CurrentStateCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101DAA30
			void RegisterCurrentStateConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<CurrentStateCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			template class fight::PropertyBranch<StateChangeCondition>;
			template class fight::ConditionFactoryTemplate<StateChangeCondition>;
			template class fight::ConditionFactoryCasterTemplate<StateChangeCondition>;
			template class fight::PropertyBranch<CurrentStateCondition>;
			template class fight::ConditionFactoryTemplate<CurrentStateCondition>;
			template class fight::ConditionFactoryCasterTemplate<CurrentStateCondition>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101DA6E0
// FUNCTION: ENGINE 0x101DA710
// FUNCTION: ENGINE 0x101DA740
// FUNCTION: ENGINE 0x101DA750
// FUNCTION: ENGINE 0x101DA780
// FUNCTION: ENGINE 0x101DA790
// FUNCTION: ENGINE 0x101DA7C0
// FUNCTION: ENGINE 0x101DA7F0
// FUNCTION: ENGINE 0x101DA810
// FUNCTION: ENGINE 0x101DA840
// FUNCTION: ENGINE 0x101DAA60
// FUNCTION: ENGINE 0x101DAA90
// FUNCTION: ENGINE 0x101DAAB0
// FUNCTION: ENGINE 0x101DAAE0
// FUNCTION: ENGINE 0x101DAB00
// FUNCTION: ENGINE 0x101DAB50
