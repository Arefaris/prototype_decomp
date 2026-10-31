// Fight items of the motion group: IntersectionPropertiesCondition (unit 0x10181350 - 0x10181890; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_intersectionproperties.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gIntersectionPropertiesConditionProperties;  // 0x11254750

			// FUNCTION: ENGINE 0x10181350
			bool IntersectionPropertiesCondition::SetType(int newValue)
			{
				type = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10181360
			bool IntersectionPropertiesCondition::SetColliderBits(int newValue)
			{
				colliderBits = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10181370
			bool IntersectionPropertiesCondition::SetMatch(bool newValue)
			{
				match = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10181380
			fight::Property* IntersectionPropertiesCondition::GetProperty(int index)
			{
				return gIntersectionPropertiesConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101813A0
			void IntersectionPropertiesCondition::ClearProperties()
			{
				fight::FreePropertyList(&gIntersectionPropertiesConditionProperties);
			}

			// FUNCTION: ENGINE 0x101813B0
			IntersectionPropertiesCondition::IntersectionPropertiesCondition() : fight::Condition(0), type(0), colliderBits(0), match(true)
			{
			}

			// FUNCTION: ENGINE 0x101813E0
			IntersectionPropertiesCondition::~IntersectionPropertiesCondition()
			{
			}

			// FUNCTION: ENGINE 0x10181680
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void IntersectionPropertiesCondition::RegisterProperties()
			{
				if (gIntersectionPropertiesConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<IntersectionPropertiesCondition>("type", gIntersectionPropertiesConditionTypeTable, 2, &IntersectionPropertiesCondition::SetType);
					properties[0] = property;
					property = new fight::PropertyBitfieldConstList<IntersectionPropertiesCondition>("colliderBits", gDetectObbCollisionConditionCollideWithTable, gDetectObbCollisionConditionCollideWithCount, &IntersectionPropertiesCondition::SetColliderBits);
					properties[1] = property;
					property = new fight::PropertyBool<IntersectionPropertiesCondition>("match", &IntersectionPropertiesCondition::SetMatch);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gIntersectionPropertiesConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10181650
			fight::ConditionFactory* CreateIntersectionPropertiesConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<IntersectionPropertiesCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101817C0
			void RegisterIntersectionPropertiesConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<IntersectionPropertiesCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			template class fight::PropertyEnumConstList<IntersectionPropertiesCondition>;
			template class fight::PropertyBitfieldConstList<IntersectionPropertiesCondition>;
			template class fight::PropertyBool<IntersectionPropertiesCondition>;
			template class fight::ConditionFactoryTemplate<IntersectionPropertiesCondition>;
			template class fight::ConditionFactoryCasterTemplate<IntersectionPropertiesCondition>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101813F0
// FUNCTION: ENGINE 0x10181420
// FUNCTION: ENGINE 0x10181430
// FUNCTION: ENGINE 0x10181460
// FUNCTION: ENGINE 0x101814A0
// FUNCTION: ENGINE 0x101814B0
// FUNCTION: ENGINE 0x101814E0
// FUNCTION: ENGINE 0x10181500
// FUNCTION: ENGINE 0x10181510
// FUNCTION: ENGINE 0x10181550
// FUNCTION: ENGINE 0x10181560
// FUNCTION: ENGINE 0x10181580
// FUNCTION: ENGINE 0x10181590
// FUNCTION: ENGINE 0x101815F0
// FUNCTION: ENGINE 0x10181620
// FUNCTION: ENGINE 0x10181640
// FUNCTION: ENGINE 0x101817F0
// FUNCTION: ENGINE 0x10181820
// FUNCTION: ENGINE 0x10181840
