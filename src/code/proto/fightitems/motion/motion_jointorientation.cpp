// Fight items of the motion group: JointOrientationCondition (unit 0x10183A80 - 0x10184060; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_jointorientation.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gJointOrientationConditionProperties;  // 0x11254794

			// FUNCTION: ENGINE 0x10183B20
			bool JointOrientationCondition::SetJoint(const fight::Name& newValue)
			{
				joint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10183A80
			bool JointOrientationCondition::SetFacing(const math::Vector& newValue)
			{
				facing.x = newValue.x;
				facing.y = newValue.y;
				facing.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10183AA0
			bool JointOrientationCondition::SetUp(const math::Vector& newValue)
			{
				up.x = newValue.x;
				up.y = newValue.y;
				up.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10183AC0
			bool JointOrientationCondition::SetThreshold(float newValue)
			{
				threshold = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10183AE0
			bool JointOrientationCondition::SetMatchFacing(bool newValue)
			{
				matchFacing = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10183AF0
			fight::Property* JointOrientationCondition::GetProperty(int index)
			{
				return gJointOrientationConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10183B10
			void JointOrientationCondition::ClearProperties()
			{
				fight::FreePropertyList(&gJointOrientationConditionProperties);
			}

			// FUNCTION: ENGINE 0x10183B40
			JointOrientationCondition::JointOrientationCondition() : fight::Condition(0), joint("Character_Root", 1), facing(0.0f, 0.0f, -1.0f), up(0.0f, 1.0f, 0.0f), threshold(0.17453294f), matchFacing(true)
			{
			}

			// FUNCTION: ENGINE 0x10183BC0
			JointOrientationCondition::~JointOrientationCondition()
			{
			}

			// FUNCTION: ENGINE 0x10183E30
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void JointOrientationCondition::RegisterProperties()
			{
				if (gJointOrientationConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyNameList<JointOrientationCondition>("joint", &JointOrientationCondition::SetJoint);
					properties[0] = property;
					property = new fight::PropertyVector<JointOrientationCondition>("facing", &JointOrientationCondition::SetFacing);
					properties[1] = property;
					property = new fight::PropertyVector<JointOrientationCondition>("up", &JointOrientationCondition::SetUp);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<JointOrientationCondition>("threshold", &JointOrientationCondition::SetThreshold);
					properties[3] = property;
					property = new fight::PropertyBool<JointOrientationCondition>("matchFacing", &JointOrientationCondition::SetMatchFacing);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gJointOrientationConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10183D70
			fight::ConditionFactory* CreateJointOrientationConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<JointOrientationCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10183DA0
			void RegisterJointOrientationConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<JointOrientationCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			template class fight::PropertyNameList<JointOrientationCondition>;
			template class fight::PropertyVector<JointOrientationCondition>;
			template class fight::PropertyFloatConstRange<JointOrientationCondition>;
			template class fight::PropertyBool<JointOrientationCondition>;
			template class fight::ConditionFactoryTemplate<JointOrientationCondition>;
			template class fight::ConditionFactoryCasterTemplate<JointOrientationCondition>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10183BD0
// FUNCTION: ENGINE 0x10183BE0
// FUNCTION: ENGINE 0x10183C10
// FUNCTION: ENGINE 0x10183C40
// FUNCTION: ENGINE 0x10183C70
// FUNCTION: ENGINE 0x10183C90
// FUNCTION: ENGINE 0x10183CA0
// FUNCTION: ENGINE 0x10183CD0
// FUNCTION: ENGINE 0x10183D00
// FUNCTION: ENGINE 0x10183D10
// FUNCTION: ENGINE 0x10183D40
// FUNCTION: ENGINE 0x10183D60
// FUNCTION: ENGINE 0x10183DD0
// FUNCTION: ENGINE 0x10183E00
// FUNCTION: ENGINE 0x10183E20
// FUNCTION: ENGINE 0x10183FC0
// FUNCTION: ENGINE 0x10183FF0
// FUNCTION: ENGINE 0x10184010
