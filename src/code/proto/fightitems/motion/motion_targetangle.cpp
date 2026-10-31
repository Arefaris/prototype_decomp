// Fight items of the motion group: TargetAngleCondition (unit 0x101BBA40 - 0x101BBFD0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_targetangle.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gTargetAngleConditionProperties;  // 0x11254B80

			// FUNCTION: ENGINE 0x101BBA40
			bool TargetAngleCondition::SetCompareTime(int newValue)
			{
				compareTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BBA50
			bool TargetAngleCondition::SetAngle(float newValue)
			{
				angle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101BBA70
			bool TargetAngleCondition::SetArc(float newValue)
			{
				arc = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101BBA90
			bool TargetAngleCondition::SetUseMovementDirection(bool newValue)
			{
				useMovementDirection = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BBAA0
			bool TargetAngleCondition::SetUseInputDirection(bool newValue)
			{
				useInputDirection = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BBAB0
			fight::Property* TargetAngleCondition::GetProperty(int index)
			{
				return gTargetAngleConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101BBAD0
			void TargetAngleCondition::ClearProperties()
			{
				fight::FreePropertyList(&gTargetAngleConditionProperties);
			}

			// FUNCTION: ENGINE 0x101BBAE0
			TargetAngleCondition::TargetAngleCondition() : fight::Condition(0), angle(0.0f), arc(0.0f), compareTime(4), useInputDirection(false), useMovementDirection(false)
			{
			}

			// FUNCTION: ENGINE 0x101BBB20
			TargetAngleCondition::~TargetAngleCondition()
			{
			}

			// FUNCTION: ENGINE 0x101BBD50
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TargetAngleCondition::RegisterProperties()
			{
				if (gTargetAngleConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<TargetAngleCondition>("compareTime", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &TargetAngleCondition::SetCompareTime);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<TargetAngleCondition>("angle", &TargetAngleCondition::SetAngle);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<TargetAngleCondition>("arc", &TargetAngleCondition::SetArc);
					properties[2] = property;
					property = new fight::PropertyBool<TargetAngleCondition>("useMovementDirection", &TargetAngleCondition::SetUseMovementDirection);
					properties[3] = property;
					property = new fight::PropertyBool<TargetAngleCondition>("useInputDirection", &TargetAngleCondition::SetUseInputDirection);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gTargetAngleConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101BBD20
			fight::ConditionFactory* CreateTargetAngleConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetAngleCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101BBF00
			void RegisterTargetAngleConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetAngleCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			template class fight::PropertyEnumConstList<TargetAngleCondition>;
			template class fight::PropertyFloatConstRange<TargetAngleCondition>;
			template class fight::PropertyBool<TargetAngleCondition>;
			template class fight::ConditionFactoryTemplate<TargetAngleCondition>;
			template class fight::ConditionFactoryCasterTemplate<TargetAngleCondition>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101BBB30
// FUNCTION: ENGINE 0x101BBB60
// FUNCTION: ENGINE 0x101BBB70
// FUNCTION: ENGINE 0x101BBBA0
// FUNCTION: ENGINE 0x101BBBE0
// FUNCTION: ENGINE 0x101BBBF0
// FUNCTION: ENGINE 0x101BBC20
// FUNCTION: ENGINE 0x101BBC40
// FUNCTION: ENGINE 0x101BBC50
// FUNCTION: ENGINE 0x101BBC80
// FUNCTION: ENGINE 0x101BBCB0
// FUNCTION: ENGINE 0x101BBCC0
// FUNCTION: ENGINE 0x101BBCF0
// FUNCTION: ENGINE 0x101BBD10
// FUNCTION: ENGINE 0x101BBF30
// FUNCTION: ENGINE 0x101BBF60
// FUNCTION: ENGINE 0x101BBF80
