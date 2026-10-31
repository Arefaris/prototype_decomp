// Fight items of the freeroamevents group: FREventTriggerTestCondition (unit 0x1027E100 - 0x1027E580; no assert path, the file name is a guess).
#include "code/proto/fightitems/freeroamevents/freeroamevents_triggertest.h"
#include <new>

namespace proto
{
	namespace fightitems
	{
		namespace freeroamevents
		{
			fight::Property** gFREventTriggerTestConditionProperties;  // 0x11256214

			// FUNCTION: ENGINE 0x1027E2E0
			bool FREventTriggerTestCondition::SetName(const char* newValue)
			{
				name = fight::ReplaceString(name, newValue);
				return true;
			}

			// FUNCTION: ENGINE 0x1027E250
			fight::Property* FREventTriggerTestCondition::GetProperty(int index)
			{
				return gFREventTriggerTestConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1027E270
			void FREventTriggerTestCondition::ClearProperties()
			{
				fight::FreePropertyList(&gFREventTriggerTestConditionProperties);
			}

			// FUNCTION: ENGINE 0x1027E280
			FREventTriggerTestCondition::FREventTriggerTestCondition() : fight::Condition(0), name(0)
			{
			}

			// FUNCTION: ENGINE 0x1027E2B0
			FREventTriggerTestCondition::~FREventTriggerTestCondition()
			{
				delete[] name;
			}

			// FUNCTION: ENGINE 0x1027E410
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void FREventTriggerTestCondition::RegisterProperties()
			{
				if (gFREventTriggerTestConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyString<FREventTriggerTestCondition>("name", &FREventTriggerTestCondition::SetName);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gFREventTriggerTestConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1027E3E0
			fight::ConditionFactory* CreateFREventTriggerTestConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<FREventTriggerTestCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1027E4B0
			void RegisterFREventTriggerTestConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<FREventTriggerTestCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			template class fight::PropertyString<FREventTriggerTestCondition>;
			template class fight::ConditionFactoryTemplate<FREventTriggerTestCondition>;
			template class fight::ConditionFactoryCasterTemplate<FREventTriggerTestCondition>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1027E310
// FUNCTION: ENGINE 0x1027E340
// FUNCTION: ENGINE 0x1027E350
// FUNCTION: ENGINE 0x1027E380
// FUNCTION: ENGINE 0x1027E3B0
// FUNCTION: ENGINE 0x1027E3D0
// FUNCTION: ENGINE 0x1027E4E0
// FUNCTION: ENGINE 0x1027E510
// FUNCTION: ENGINE 0x1027E530
