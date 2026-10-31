// Fight items of the motion group: InsidePlaneCondition, DistanceToJointCondition (unit 0x10159C60 - 0x1015A810; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_distance.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gInsidePlaneConditionProperties;  // 0x11254468

			// FUNCTION: ENGINE 0x10159D90
			bool InsidePlaneCondition::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10159DB0
			bool InsidePlaneCondition::SetJoint(const fight::Name& newValue)
			{
				joint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10159C60
			bool InsidePlaneCondition::SetInside(bool newValue)
			{
				inside = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10159C70
			bool InsidePlaneCondition::SetOffset(const math::Vector& newValue)
			{
				offset.x = newValue.x;
				offset.y = newValue.y;
				offset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10159C90
			bool InsidePlaneCondition::SetOrientation(const math::Vector& newValue)
			{
				math::Vector scaled = newValue;
				scaled.x *= 0.017453292f;
				scaled.y *= 0.017453292f;
				scaled.z *= 0.017453292f;
				orientation.x = scaled.x;
				orientation.y = scaled.y;
				orientation.z = scaled.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10159D30
			fight::Property* InsidePlaneCondition::GetProperty(int index)
			{
				return gInsidePlaneConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10159D50
			void InsidePlaneCondition::ClearProperties()
			{
				fight::FreePropertyList(&gInsidePlaneConditionProperties);
			}

			// FUNCTION: ENGINE 0x10159E10
			InsidePlaneCondition::InsidePlaneCondition() : fight::Condition(0), offset(0.0f, 0.0f, 0.0f), orientation(0.0f, 0.0f, 0.0f), inside(true)
			{
			}

			// FUNCTION: ENGINE 0x10159E70
			InsidePlaneCondition::~InsidePlaneCondition()
			{
			}

			// FUNCTION: ENGINE 0x1015A390
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void InsidePlaneCondition::RegisterProperties()
			{
				if (gInsidePlaneConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyNameList<InsidePlaneCondition>("grabSlot", &InsidePlaneCondition::SetGrabSlot);
					properties[0] = property;
					property = new fight::PropertyNameList<InsidePlaneCondition>("joint", &InsidePlaneCondition::SetJoint);
					properties[1] = property;
					property = new fight::PropertyBool<InsidePlaneCondition>("inside", &InsidePlaneCondition::SetInside);
					properties[2] = property;
					property = new fight::PropertyVector<InsidePlaneCondition>("offset", &InsidePlaneCondition::SetOffset);
					properties[3] = property;
					property = new fight::PropertyVector<InsidePlaneCondition>("orientation", &InsidePlaneCondition::SetOrientation);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gInsidePlaneConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1015A210
			fight::ConditionFactory* CreateInsidePlaneConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<InsidePlaneCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1015A270
			void RegisterInsidePlaneConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<InsidePlaneCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gDistanceToJointConditionProperties;  // 0x1125446C

			// FUNCTION: ENGINE 0x10159DD0
			bool DistanceToJointCondition::SetJoint(const fight::Name& newValue)
			{
				joint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10159DF0
			bool DistanceToJointCondition::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10159CE0
			bool DistanceToJointCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10159CF0
			bool DistanceToJointCondition::SetDistance(float newValue)
			{
				distance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10159D10
			bool DistanceToJointCondition::SetOffset(const math::Vector& newValue)
			{
				offset.x = newValue.x;
				offset.y = newValue.y;
				offset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10159D60
			fight::Property* DistanceToJointCondition::GetProperty(int index)
			{
				return gDistanceToJointConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10159D80
			void DistanceToJointCondition::ClearProperties()
			{
				fight::FreePropertyList(&gDistanceToJointConditionProperties);
			}

			// FUNCTION: ENGINE 0x10159E80
			DistanceToJointCondition::DistanceToJointCondition() : fight::Condition(0), offset(0.0f, 0.0f, 0.0f), distance(0.0f), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x10159EE0
			DistanceToJointCondition::~DistanceToJointCondition()
			{
			}

			// FUNCTION: ENGINE 0x1015A520
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DistanceToJointCondition::RegisterProperties()
			{
				if (gDistanceToJointConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyNameList<DistanceToJointCondition>("joint", &DistanceToJointCondition::SetJoint);
					properties[0] = property;
					property = new fight::PropertyNameList<DistanceToJointCondition>("grabSlot", &DistanceToJointCondition::SetGrabSlot);
					properties[1] = property;
					property = new fight::PropertyEnumConstList<DistanceToJointCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &DistanceToJointCondition::SetCompare);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<DistanceToJointCondition>("distance", &DistanceToJointCondition::SetDistance);
					properties[3] = property;
					property = new fight::PropertyVector<DistanceToJointCondition>("offset", &DistanceToJointCondition::SetOffset);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gDistanceToJointConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1015A240
			fight::ConditionFactory* CreateDistanceToJointConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DistanceToJointCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1015A2A0
			void RegisterDistanceToJointConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DistanceToJointCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			// ---- actions begin

			// ---- actions end
			template class fight::PropertyNameList<InsidePlaneCondition>;
			template class fight::PropertyBool<InsidePlaneCondition>;
			template class fight::PropertyVector<InsidePlaneCondition>;
			template class fight::ConditionFactoryTemplate<InsidePlaneCondition>;
			template class fight::ConditionFactoryCasterTemplate<InsidePlaneCondition>;
			template class fight::PropertyNameList<DistanceToJointCondition>;
			template class fight::PropertyEnumConstList<DistanceToJointCondition>;
			template class fight::PropertyFloatConstRange<DistanceToJointCondition>;
			template class fight::PropertyVector<DistanceToJointCondition>;
			template class fight::ConditionFactoryTemplate<DistanceToJointCondition>;
			template class fight::ConditionFactoryCasterTemplate<DistanceToJointCondition>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10159EF0
// FUNCTION: ENGINE 0x10159F00
// FUNCTION: ENGINE 0x10159F30
// FUNCTION: ENGINE 0x10159F40
// FUNCTION: ENGINE 0x10159F70
// FUNCTION: ENGINE 0x10159FA0
// FUNCTION: ENGINE 0x10159FD0
// FUNCTION: ENGINE 0x1015A000
// FUNCTION: ENGINE 0x1015A020
// FUNCTION: ENGINE 0x1015A030
// FUNCTION: ENGINE 0x1015A060
// FUNCTION: ENGINE 0x1015A080
// FUNCTION: ENGINE 0x1015A090
// FUNCTION: ENGINE 0x1015A0D0
// FUNCTION: ENGINE 0x1015A0E0
// FUNCTION: ENGINE 0x1015A110
// FUNCTION: ENGINE 0x1015A130
// FUNCTION: ENGINE 0x1015A140
// FUNCTION: ENGINE 0x1015A170
// FUNCTION: ENGINE 0x1015A1A0
// FUNCTION: ENGINE 0x1015A1B0
// FUNCTION: ENGINE 0x1015A1E0
// FUNCTION: ENGINE 0x1015A200
// FUNCTION: ENGINE 0x1015A2D0
// FUNCTION: ENGINE 0x1015A300
// FUNCTION: ENGINE 0x1015A320
// FUNCTION: ENGINE 0x1015A330
// FUNCTION: ENGINE 0x1015A360
// FUNCTION: ENGINE 0x1015A380
// FUNCTION: ENGINE 0x1015A6D0
// FUNCTION: ENGINE 0x1015A700
// FUNCTION: ENGINE 0x1015A720
// FUNCTION: ENGINE 0x1015A750
// FUNCTION: ENGINE 0x1015A770
// FUNCTION: ENGINE 0x1015A7C0
