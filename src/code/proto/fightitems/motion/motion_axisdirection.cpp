// Fight items of the motion group: AxisDirectionCondition (unit 0x10180EC0 - 0x10181350; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_axisdirection.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gAxisDirectionConditionProperties;  // 0x1125474C

			// FUNCTION: ENGINE 0x10180EC0
			bool AxisDirectionCondition::SetAxis(int newValue)
			{
				axis = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10180ED0
			bool AxisDirectionCondition::SetDirection(float newValue)
			{
				direction = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10180EF0
			bool AxisDirectionCondition::SetArc(float newValue)
			{
				arc = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10180F10
			fight::Property* AxisDirectionCondition::GetProperty(int index)
			{
				return gAxisDirectionConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10180F30
			void AxisDirectionCondition::ClearProperties()
			{
				fight::FreePropertyList(&gAxisDirectionConditionProperties);
			}

			// FUNCTION: ENGINE 0x10180F40
			AxisDirectionCondition::AxisDirectionCondition() : fight::Condition(0), arc(0.0f), direction(0.0f), axis(0)
			{
			}

			// FUNCTION: ENGINE 0x10180F80
			AxisDirectionCondition::~AxisDirectionCondition()
			{
			}

			// FUNCTION: ENGINE 0x10181150
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void AxisDirectionCondition::RegisterProperties()
			{
				if (gAxisDirectionConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<AxisDirectionCondition>("axis", gAxisDirectionConditionAxisTable, gAxisDirectionConditionAxisCount, &AxisDirectionCondition::SetAxis);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<AxisDirectionCondition>("direction", &AxisDirectionCondition::SetDirection);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<AxisDirectionCondition>("arc", &AxisDirectionCondition::SetArc);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gAxisDirectionConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10181120
			fight::ConditionFactory* CreateAxisDirectionConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<AxisDirectionCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10181280
			void RegisterAxisDirectionConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<AxisDirectionCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			template class fight::PropertyEnumConstList<AxisDirectionCondition>;
			template class fight::PropertyFloatConstRange<AxisDirectionCondition>;
			template class fight::ConditionFactoryTemplate<AxisDirectionCondition>;
			template class fight::ConditionFactoryCasterTemplate<AxisDirectionCondition>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10180F90
// FUNCTION: ENGINE 0x10180FC0
// FUNCTION: ENGINE 0x10180FD0
// FUNCTION: ENGINE 0x10181000
// FUNCTION: ENGINE 0x10181040
// FUNCTION: ENGINE 0x10181050
// FUNCTION: ENGINE 0x10181080
// FUNCTION: ENGINE 0x101810A0
// FUNCTION: ENGINE 0x101810B0
// FUNCTION: ENGINE 0x101810E0
// FUNCTION: ENGINE 0x10181110
// FUNCTION: ENGINE 0x101812B0
// FUNCTION: ENGINE 0x101812E0
// FUNCTION: ENGINE 0x10181300
