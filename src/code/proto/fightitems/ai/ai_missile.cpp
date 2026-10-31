// Fight items of the ai group: IsMissileTargetingPlayerCondition (unit 0x1021C6F0 - 0x1021C920; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_missile.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gIsMissileTargetingPlayerConditionProperties;  // 0x11255828

			// FUNCTION: ENGINE 0x1021C750
			fight::Property* IsMissileTargetingPlayerCondition::GetProperty(int index)
			{
				return gIsMissileTargetingPlayerConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1021C770
			void IsMissileTargetingPlayerCondition::ClearProperties()
			{
				fight::FreePropertyList(&gIsMissileTargetingPlayerConditionProperties);
			}

			// FUNCTION: ENGINE 0x1021C780
			IsMissileTargetingPlayerCondition::IsMissileTargetingPlayerCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x1021C7A0
			IsMissileTargetingPlayerCondition::~IsMissileTargetingPlayerCondition()
			{
			}

			// FUNCTION: ENGINE 0x1021C6F0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void IsMissileTargetingPlayerCondition::RegisterProperties()
			{
				if (gIsMissileTargetingPlayerConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					fight::RegisterPropertyList(properties, &gIsMissileTargetingPlayerConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1021C8C0
			fight::ConditionFactory* CreateIsMissileTargetingPlayerConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<IsMissileTargetingPlayerCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1021C8F0
			void RegisterIsMissileTargetingPlayerConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<IsMissileTargetingPlayerCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			// ---- actions begin

			// ---- actions end
			template class fight::ConditionFactoryTemplate<IsMissileTargetingPlayerCondition>;
			template class fight::ConditionFactoryCasterTemplate<IsMissileTargetingPlayerCondition>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1021C7B0
// FUNCTION: ENGINE 0x1021C7E0
// FUNCTION: ENGINE 0x1021C7F0
// FUNCTION: ENGINE 0x1021C820
// FUNCTION: ENGINE 0x1021C850
// FUNCTION: ENGINE 0x1021C870
