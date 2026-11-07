// Fight items of the motion group: GenderCondition (unit 0x10163BA0 - 0x10163FA0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_gender.h"
#include "code/engine/fight/fightcommon.h"
#include "code/proto/fightitems/motion/motionaction.h"
#include "code/proto/fightitems/motion/motioncommon.h"
#include "code/engine/gameobject/gameobject.h"

namespace engine
{
	extern core::Name<core::CaseSensitiveKey> gGender;  // 0x11256268
}

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gGenderConditionProperties;  // 0x1125456C

			// FUNCTION: ENGINE 0x10163BA0
			bool GenderCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10163BE0
			bool GenderCondition::SetValue(const fight::Name& newValue)
			{
				value = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10163BB0
			fight::Property* GenderCondition::GetProperty(int index)
			{
				return gGenderConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10163BD0
			void GenderCondition::ClearProperties()
			{
				fight::FreePropertyList(&gGenderConditionProperties);
			}

			// FUNCTION: ENGINE 0x10163C00
			GenderCondition::GenderCondition() : fight::Condition(0), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x10163C30
			GenderCondition::~GenderCondition()
			{
			}

			// FUNCTION: ENGINE 0x10163E10
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GenderCondition::RegisterProperties()
			{
				if (gGenderConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<GenderCondition>("compare", gClassNameConditionCompareTable, gClassNameConditionCompareCount, &GenderCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyName<GenderCondition>("value", &GenderCondition::SetValue);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gGenderConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10163D60
			fight::ConditionFactory* CreateGenderConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GenderCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10163D90
			void RegisterGenderConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GenderCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x100C1E20
			bool GenderCondition::Evaluate(int a, int b, int c, int d)
			{
				engine::GameObject* object = engine::GetObjectHandle(AsOwner(c)).Get();
				if (object == 0)
				{
					return false;
				}
				engine::BaseAttribute* attribute = object->FindAttribute(engine::gGender);
				if (attribute == 0)
				{
					return false;
				}
				core::Name<core::CaseSensitiveKey>* attributeValue = &((engine::Attribute<core::Name<core::CaseSensitiveKey> >*)attribute)->value;
				if (attributeValue == 0)
				{
					return false;
				}
				return fight::CompareNames(compare, attributeValue, &value);
			}

			// ---- actions end
			template class fight::PropertyEnumConstList<GenderCondition>;
			template class fight::PropertyName<GenderCondition>;
			template class fight::ConditionFactoryTemplate<GenderCondition>;
			template class fight::ConditionFactoryCasterTemplate<GenderCondition>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10163C40
// FUNCTION: ENGINE 0x10163C50
// FUNCTION: ENGINE 0x10163C80
// FUNCTION: ENGINE 0x10163CB0
// FUNCTION: ENGINE 0x10163CF0
// FUNCTION: ENGINE 0x10163D00
// FUNCTION: ENGINE 0x10163D30
// FUNCTION: ENGINE 0x10163D50
// FUNCTION: ENGINE 0x10163DC0
// FUNCTION: ENGINE 0x10163DF0
// FUNCTION: ENGINE 0x10163F00
// FUNCTION: ENGINE 0x10163F30
// FUNCTION: ENGINE 0x10163F50
