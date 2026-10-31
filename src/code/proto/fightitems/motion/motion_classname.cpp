// Fight items of the motion group: ClassNameCondition (unit 0x10149690 - 0x10149A90; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_classname.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gClassNameConditionProperties;  // 0x11254338

			// FUNCTION: ENGINE 0x10149690
			bool ClassNameCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101496D0
			bool ClassNameCondition::SetValue(const fight::Name& newValue)
			{
				value = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101496A0
			fight::Property* ClassNameCondition::GetProperty(int index)
			{
				return gClassNameConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101496C0
			void ClassNameCondition::ClearProperties()
			{
				fight::FreePropertyList(&gClassNameConditionProperties);
			}

			// FUNCTION: ENGINE 0x101496F0
			ClassNameCondition::ClassNameCondition() : fight::Condition(0), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x10149720
			ClassNameCondition::~ClassNameCondition()
			{
			}

			// FUNCTION: ENGINE 0x10149900
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ClassNameCondition::RegisterProperties()
			{
				if (gClassNameConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<ClassNameCondition>("compare", gClassNameConditionCompareTable, gClassNameConditionCompareCount, &ClassNameCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyName<ClassNameCondition>("value", &ClassNameCondition::SetValue);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gClassNameConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10149850
			fight::ConditionFactory* CreateClassNameConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ClassNameCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10149880
			void RegisterClassNameConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ClassNameCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			// ---- actions begin

			// ---- actions end
			template class fight::PropertyEnumConstList<ClassNameCondition>;
			template class fight::PropertyName<ClassNameCondition>;
			template class fight::ConditionFactoryTemplate<ClassNameCondition>;
			template class fight::ConditionFactoryCasterTemplate<ClassNameCondition>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
