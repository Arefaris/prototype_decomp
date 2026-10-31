// Fight items of the scenario group: Event_MotionStateCondition (unit 0x101D8CE0 - 0x101D9540; no assert path, the file name is a guess).
#include "code/proto/fightitems/scenario/scenario_motionstate.h"

namespace proto
{
	namespace fightitems
	{
		namespace scenario
		{
			fight::Property** gEvent_MotionStateConditionProperties;  // 0x11254DAC

			// FUNCTION: ENGINE 0x101D91F0
			bool Event_MotionStateCondition::SetMotionState(int newValue)
			{
				motionState = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D9200
			fight::Property* Event_MotionStateCondition::GetProperty(int index)
			{
				return gEvent_MotionStateConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101D9220
			void Event_MotionStateCondition::ClearProperties()
			{
				fight::FreePropertyList(&gEvent_MotionStateConditionProperties);
			}

			// FUNCTION: ENGINE 0x101D9230
			Event_MotionStateCondition::Event_MotionStateCondition() : fight::Condition(0), motionState(0)
			{
			}

			// FUNCTION: ENGINE 0x101D9260
			Event_MotionStateCondition::~Event_MotionStateCondition()
			{
			}

			// FUNCTION: ENGINE 0x101D93C0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void Event_MotionStateCondition::RegisterProperties()
			{
				if (gEvent_MotionStateConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<Event_MotionStateCondition>("motionState", gEvent_MotionStateConditionMotionStateTable, gEvent_MotionStateConditionMotionStateCount, &Event_MotionStateCondition::SetMotionState);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gEvent_MotionStateConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101D9390
			fight::ConditionFactory* CreateEvent_MotionStateConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<Event_MotionStateCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101D9470
			void RegisterEvent_MotionStateConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<Event_MotionStateCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			template class fight::PropertyEnumConstList<Event_MotionStateCondition>;
			template class fight::ConditionFactoryTemplate<Event_MotionStateCondition>;
			template class fight::ConditionFactoryCasterTemplate<Event_MotionStateCondition>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101D9270
// FUNCTION: ENGINE 0x101D92A0
// FUNCTION: ENGINE 0x101D92B0
// FUNCTION: ENGINE 0x101D92E0
// FUNCTION: ENGINE 0x101D9320
// FUNCTION: ENGINE 0x101D9330
// FUNCTION: ENGINE 0x101D9360
// FUNCTION: ENGINE 0x101D9380
// FUNCTION: ENGINE 0x101D94A0
// FUNCTION: ENGINE 0x101D94D0
// FUNCTION: ENGINE 0x101D94F0
