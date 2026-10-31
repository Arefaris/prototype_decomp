// Fight items of the motion group: UnlockableCondition (unit 0x101C4FB0 - 0x101C5300; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_unlockable.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gUnlockableConditionProperties;  // 0x11254C20

			// FUNCTION: ENGINE 0x101C4FB0
			bool UnlockableCondition::SetUnlockable(int newValue)
			{
				unlockable = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C4FC0
			fight::Property* UnlockableCondition::GetProperty(int index)
			{
				return gUnlockableConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101C4FE0
			void UnlockableCondition::ClearProperties()
			{
				fight::FreePropertyList(&gUnlockableConditionProperties);
			}

			// FUNCTION: ENGINE 0x101C4FF0
			UnlockableCondition::UnlockableCondition() : fight::Condition(0), unlockable(0)
			{
			}

			// FUNCTION: ENGINE 0x101C5020
			UnlockableCondition::~UnlockableCondition()
			{
			}

			// FUNCTION: ENGINE 0x101C5180
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void UnlockableCondition::RegisterProperties()
			{
				if (gUnlockableConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<UnlockableCondition>("unlockable", gJumpTrackUnlockableFirstTable, gJumpTrackUnlockableFirstCount, &UnlockableCondition::SetUnlockable);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gUnlockableConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C5150
			fight::ConditionFactory* CreateUnlockableConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<UnlockableCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101C5230
			void RegisterUnlockableConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<UnlockableCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			template class fight::PropertyEnumConstList<UnlockableCondition>;
			template class fight::ConditionFactoryTemplate<UnlockableCondition>;
			template class fight::ConditionFactoryCasterTemplate<UnlockableCondition>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101C5030
// FUNCTION: ENGINE 0x101C5060
// FUNCTION: ENGINE 0x101C5070
// FUNCTION: ENGINE 0x101C50A0
// FUNCTION: ENGINE 0x101C50E0
// FUNCTION: ENGINE 0x101C50F0
// FUNCTION: ENGINE 0x101C5120
// FUNCTION: ENGINE 0x101C5140
// FUNCTION: ENGINE 0x101C5260
// FUNCTION: ENGINE 0x101C5290
// FUNCTION: ENGINE 0x101C52B0
