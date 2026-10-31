// Fight items of the ai group: EnabledCondition, TaskCondition, GoalCondition (unit 0x10239F70 - 0x1023A830; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_enabled.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gEnabledConditionProperties;  // 0x11255A70

			// FUNCTION: ENGINE 0x10239F70
			bool EnabledCondition::SetIsEnabled(bool newValue)
			{
				isEnabled = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10239F80
			fight::Property* EnabledCondition::GetProperty(int index)
			{
				return gEnabledConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10239FA0
			void EnabledCondition::ClearProperties()
			{
				fight::FreePropertyList(&gEnabledConditionProperties);
			}

			// FUNCTION: ENGINE 0x10239FB0
			EnabledCondition::EnabledCondition() : fight::Condition(0), isEnabled(true)
			{
			}

			// FUNCTION: ENGINE 0x10239FD0
			EnabledCondition::~EnabledCondition()
			{
			}

			// FUNCTION: ENGINE 0x1023A340
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void EnabledCondition::RegisterProperties()
			{
				if (gEnabledConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<EnabledCondition>("isEnabled", &EnabledCondition::SetIsEnabled);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gEnabledConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1023A2B0
			fight::ConditionFactory* CreateEnabledConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<EnabledCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1023A3E0
			void RegisterEnabledConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<EnabledCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gTaskConditionProperties;  // 0x11255A74

			// FUNCTION: ENGINE 0x1023A040
			bool TaskCondition::SetTask(const fight::Name& newValue)
			{
				task = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10239FE0
			fight::Property* TaskCondition::GetProperty(int index)
			{
				return gTaskConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1023A000
			void TaskCondition::ClearProperties()
			{
				fight::FreePropertyList(&gTaskConditionProperties);
			}

			// FUNCTION: ENGINE 0x1023A0B0
			TaskCondition::TaskCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x1023A0E0
			TaskCondition::~TaskCondition()
			{
			}

			// FUNCTION: ENGINE 0x1023A560
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TaskCondition::RegisterProperties()
			{
				if (gTaskConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyName<TaskCondition>("task", &TaskCondition::SetTask);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gTaskConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1023A2E0
			fight::ConditionFactory* CreateTaskConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TaskCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1023A410
			void RegisterTaskConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TaskCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gGoalConditionProperties;  // 0x11255A78

			// FUNCTION: ENGINE 0x1023A060
			bool GoalCondition::SetGoal(const fight::Name& newValue)
			{
				goal = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023A010
			fight::Property* GoalCondition::GetProperty(int index)
			{
				return gGoalConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1023A030
			void GoalCondition::ClearProperties()
			{
				fight::FreePropertyList(&gGoalConditionProperties);
			}

			// FUNCTION: ENGINE 0x1023A0F0
			GoalCondition::GoalCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x1023A120
			GoalCondition::~GoalCondition()
			{
			}

			// FUNCTION: ENGINE 0x1023A600
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GoalCondition::RegisterProperties()
			{
				if (gGoalConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyName<GoalCondition>("goal", &GoalCondition::SetGoal);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gGoalConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1023A310
			fight::ConditionFactory* CreateGoalConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GoalCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1023A440
			void RegisterGoalConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GoalCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			template class fight::PropertyBool<EnabledCondition>;
			template class fight::ConditionFactoryTemplate<EnabledCondition>;
			template class fight::ConditionFactoryCasterTemplate<EnabledCondition>;
			template class fight::PropertyName<TaskCondition>;
			template class fight::ConditionFactoryTemplate<TaskCondition>;
			template class fight::ConditionFactoryCasterTemplate<TaskCondition>;
			template class fight::PropertyName<GoalCondition>;
			template class fight::ConditionFactoryTemplate<GoalCondition>;
			template class fight::ConditionFactoryCasterTemplate<GoalCondition>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1023A080
// FUNCTION: ENGINE 0x1023A130
// FUNCTION: ENGINE 0x1023A140
// FUNCTION: ENGINE 0x1023A170
// FUNCTION: ENGINE 0x1023A180
// FUNCTION: ENGINE 0x1023A1B0
// FUNCTION: ENGINE 0x1023A1C0
// FUNCTION: ENGINE 0x1023A1F0
// FUNCTION: ENGINE 0x1023A220
// FUNCTION: ENGINE 0x1023A250
// FUNCTION: ENGINE 0x1023A280
// FUNCTION: ENGINE 0x1023A2A0
// FUNCTION: ENGINE 0x1023A470
// FUNCTION: ENGINE 0x1023A4A0
// FUNCTION: ENGINE 0x1023A4C0
// FUNCTION: ENGINE 0x1023A4F0
// FUNCTION: ENGINE 0x1023A510
// FUNCTION: ENGINE 0x1023A540
// FUNCTION: ENGINE 0x1023A6A0
// FUNCTION: ENGINE 0x1023A6F0
// FUNCTION: ENGINE 0x1023A720
// FUNCTION: ENGINE 0x1023A740
// FUNCTION: ENGINE 0x1023A770
// FUNCTION: ENGINE 0x1023A790
// FUNCTION: ENGINE 0x1023A7E0
