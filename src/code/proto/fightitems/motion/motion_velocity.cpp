// Fight items of the motion group: VelocityYAngleCondition, VelocityAngleCondition (unit 0x101CB300 - 0x101CBD20; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_velocity.h"
#include <math.h>

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gVelocityYAngleConditionProperties;  // 0x11254C90

			// FUNCTION: ENGINE 0x101CB300
			bool VelocityYAngleCondition::SetType(int newValue)
			{
				type = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CB310
			bool VelocityYAngleCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CB320
			bool VelocityYAngleCondition::SetAngle(float newValue)
			{
				angle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101CB3A0
			fight::Property* VelocityYAngleCondition::GetProperty(int index)
			{
				return gVelocityYAngleConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101CB3C0
			void VelocityYAngleCondition::ClearProperties()
			{
				fight::FreePropertyList(&gVelocityYAngleConditionProperties);
			}

			// FUNCTION: ENGINE 0x101CB3D0
			VelocityYAngleCondition::VelocityYAngleCondition() : fight::Condition(0), angle(0.0f), compare(4), type(0)
			{
			}

			// FUNCTION: ENGINE 0x101CB410
			VelocityYAngleCondition::~VelocityYAngleCondition()
			{
			}

			// FUNCTION: ENGINE 0x101CB880
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void VelocityYAngleCondition::RegisterProperties()
			{
				if (gVelocityYAngleConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<VelocityYAngleCondition>("type", gVelocityYAngleConditionTypeTable, gVelocityYAngleConditionTypeCount, &VelocityYAngleCondition::SetType);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<VelocityYAngleCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &VelocityYAngleCondition::SetCompare);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<VelocityYAngleCondition>("angle", &VelocityYAngleCondition::SetAngle);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gVelocityYAngleConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101CB820
			fight::ConditionFactory* CreateVelocityYAngleConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<VelocityYAngleCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101CBB80
			void RegisterVelocityYAngleConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<VelocityYAngleCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gVelocityAngleConditionProperties;  // 0x11254C94

			// FUNCTION: ENGINE 0x101CB340
			bool VelocityAngleCondition::SetType(int newValue)
			{
				type = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CB350
			bool VelocityAngleCondition::SetCompareTime(int newValue)
			{
				compareTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CB360
			bool VelocityAngleCondition::SetAngle(float newValue)
			{
				angle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101CB380
			bool VelocityAngleCondition::SetXz(bool newValue)
			{
				xz = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CB390
			bool VelocityAngleCondition::SetSigned(bool newValue)
			{
				signedValue = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CB420
			fight::Property* VelocityAngleCondition::GetProperty(int index)
			{
				return gVelocityAngleConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101CB440
			void VelocityAngleCondition::ClearProperties()
			{
				fight::FreePropertyList(&gVelocityAngleConditionProperties);
			}

			// FUNCTION: ENGINE 0x101CB450
			VelocityAngleCondition::VelocityAngleCondition() : fight::Condition(0), angle(0.0f), compareTime(4), type(0), signedValue(false), xz(false)
			{
			}

			// FUNCTION: ENGINE 0x101CB490
			VelocityAngleCondition::~VelocityAngleCondition()
			{
			}

			// FUNCTION: ENGINE 0x101CB9C0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void VelocityAngleCondition::RegisterProperties()
			{
				if (gVelocityAngleConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<VelocityAngleCondition>("type", gVelocityYAngleConditionTypeTable, gVelocityYAngleConditionTypeCount, &VelocityAngleCondition::SetType);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<VelocityAngleCondition>("compareTime", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &VelocityAngleCondition::SetCompareTime);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<VelocityAngleCondition>("angle", &VelocityAngleCondition::SetAngle);
					properties[2] = property;
					property = new fight::PropertyBool<VelocityAngleCondition>("xz", &VelocityAngleCondition::SetXz);
					properties[3] = property;
					property = new fight::PropertyBool<VelocityAngleCondition>("signed", &VelocityAngleCondition::SetSigned);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gVelocityAngleConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101CB850
			fight::ConditionFactory* CreateVelocityAngleConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<VelocityAngleCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101CBBB0
			void RegisterVelocityAngleConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<VelocityAngleCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x1012BDF0
			// EQUIVALENT: scheduling: the engine loads the operator before the compared value and keeps the condition in eax, ours in esi (93.7 %)
			bool VelocityYAngleCondition::Evaluate(int a, int b, int c, int d)
			{
				engine::GameObject* object = engine::GetObjectHandle(AsOwner(c)).Get();
				if (object == 0)
				{
					return false;
				}
				math::Vector velocity;
				velocity.x = math::kZeroVector.x;
				velocity.y = math::kZeroVector.y;
				velocity.z = math::kZeroVector.z;
				engine::GetObjectVelocity(object, GetType(), &velocity);
				velocity.Normalize();
				float current = (float)asin(velocity.y);
				float wanted = GetAngle();
				return fight::CompareFloats(GetCompare(), &current, &wanted);
			}

			// FUNCTION: ENGINE 0x1012BB60
			// EQUIVALENT: scheduling and register allocation (the engine keeps a zero in bl, loads the three matrix components before negating them and sums the three products with the xorps of the clamp in another place); every operation and the order of the sum are the engine's (19.4 %)
			bool VelocityAngleCondition::Evaluate(int a, int b, int c, int d)
			{
				engine::GameObject* object = engine::GetObjectHandle(AsOwner(c)).Get();
				if (object == 0)
				{
					return false;
				}
				math::Vector velocity;
				velocity.x = math::kZeroVector.x;
				velocity.y = math::kZeroVector.y;
				velocity.z = math::kZeroVector.z;
				engine::GetObjectVelocity(object, GetType(), &velocity);
				if (GetXz())
				{
					velocity.y = 0.0f;
				}
				float angle = 0.0f;
				if (velocity.Normalize() > 0.00001f)
				{
					math::Matrix* matrix = object->transform->GetPointer();
					float rowX = matrix->m[2][0];
					float rowY = matrix->m[2][1];
					float rowZ = matrix->m[2][2];
					math::Vector forward(math::WORLD_MIN - rowX, math::WORLD_MIN - rowY, math::WORLD_MIN - rowZ);
					if (GetXz())
					{
						forward.y = 0.0f;
					}
					forward.Normalize();
					float dot = forward.z * velocity.z + forward.x * velocity.x + forward.y * velocity.y;
					if (!(dot - choreo::gMinusOne >= 0.0f))
					{
						dot = choreo::gMinusOne;
					}
					angle = dot;
					if (angle - engine::driving::gOne >= 0.0f)
					{
						angle = engine::driving::gOne;
					}
					angle = (float)acos(angle);
					if (GetSignedValue())
					{
						if (forward.z * velocity.x - velocity.z * forward.x < 0.0f)
						{
							angle = math::WORLD_MIN - angle;
						}
					}
				}
				float wanted = GetAngle();
				return fight::CompareFloats(GetCompareTime(), &angle, &wanted);
			}

			// ---- actions end
			template class fight::PropertyEnumConstList<VelocityYAngleCondition>;
			template class fight::PropertyFloatConstRange<VelocityYAngleCondition>;
			template class fight::ConditionFactoryTemplate<VelocityYAngleCondition>;
			template class fight::ConditionFactoryCasterTemplate<VelocityYAngleCondition>;
			template class fight::PropertyEnumConstList<VelocityAngleCondition>;
			template class fight::PropertyFloatConstRange<VelocityAngleCondition>;
			template class fight::PropertyBool<VelocityAngleCondition>;
			template class fight::ConditionFactoryTemplate<VelocityAngleCondition>;
			template class fight::ConditionFactoryCasterTemplate<VelocityAngleCondition>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1012BAE0
// FUNCTION: ENGINE 0x1012BAF0
// FUNCTION: ENGINE 0x1012BB00
// FUNCTION: ENGINE 0x1012BB10
// FUNCTION: ENGINE 0x1012BB20
// FUNCTION: ENGINE 0x1012BB30
// FUNCTION: ENGINE 0x1012BB40
// FUNCTION: ENGINE 0x1012BB50
// FUNCTION: ENGINE 0x101CB4A0
// FUNCTION: ENGINE 0x101CB4D0
// FUNCTION: ENGINE 0x101CB500
// FUNCTION: ENGINE 0x101CB510
// FUNCTION: ENGINE 0x101CB540
// FUNCTION: ENGINE 0x101CB550
// FUNCTION: ENGINE 0x101CB580
// FUNCTION: ENGINE 0x101CB5C0
// FUNCTION: ENGINE 0x101CB5D0
// FUNCTION: ENGINE 0x101CB600
// FUNCTION: ENGINE 0x101CB620
// FUNCTION: ENGINE 0x101CB630
// FUNCTION: ENGINE 0x101CB660
// FUNCTION: ENGINE 0x101CB690
// FUNCTION: ENGINE 0x101CB6A0
// FUNCTION: ENGINE 0x101CB6E0
// FUNCTION: ENGINE 0x101CB6F0
// FUNCTION: ENGINE 0x101CB720
// FUNCTION: ENGINE 0x101CB740
// FUNCTION: ENGINE 0x101CB750
// FUNCTION: ENGINE 0x101CB780
// FUNCTION: ENGINE 0x101CB7B0
// FUNCTION: ENGINE 0x101CB7C0
// FUNCTION: ENGINE 0x101CB7F0
// FUNCTION: ENGINE 0x101CB810
// FUNCTION: ENGINE 0x101CBBE0
// FUNCTION: ENGINE 0x101CBC10
// FUNCTION: ENGINE 0x101CBC30
// FUNCTION: ENGINE 0x101CBC60
// FUNCTION: ENGINE 0x101CBC80
// FUNCTION: ENGINE 0x101CBCD0
