// Fight items of the motion group: AccelerationCondition (unit 0x1013C010 - 0x1013C5B0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_acceleration.h"
#include "code/proto/behaviours/charactermotionbehaviour.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gAccelerationConditionProperties;  // 0x11254204

			// FUNCTION: ENGINE 0x1013C020
			bool AccelerationCondition::SetType(int newValue)
			{
				type = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013C030
			bool AccelerationCondition::SetDirection(int newValue)
			{
				direction = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013C040
			bool AccelerationCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013C050
			bool AccelerationCondition::SetAcceleration(float newValue)
			{
				acceleration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013C070
			fight::Property* AccelerationCondition::GetProperty(int index)
			{
				return gAccelerationConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1013C090
			void AccelerationCondition::ClearProperties()
			{
				fight::FreePropertyList(&gAccelerationConditionProperties);
			}

			// FUNCTION: ENGINE 0x1013C0A0
			AccelerationCondition::AccelerationCondition() : fight::Condition(0), acceleration(0.0f), compare(0), direction(2), type(0)
			{
			}

			// FUNCTION: ENGINE 0x1013C0F0
			AccelerationCondition::~AccelerationCondition()
			{
			}

			// FUNCTION: ENGINE 0x1013C350
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void AccelerationCondition::RegisterProperties()
			{
				if (gAccelerationConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<AccelerationCondition>("type", gVelocityYAngleConditionTypeTable, gVelocityYAngleConditionTypeCount, &AccelerationCondition::SetType);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<AccelerationCondition>("direction", gCrowdPositionConditionDirectionTable, gCrowdPositionConditionDirectionCount, &AccelerationCondition::SetDirection);
					properties[1] = property;
					property = new fight::PropertyEnumConstList<AccelerationCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &AccelerationCondition::SetCompare);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<AccelerationCondition>("acceleration", &AccelerationCondition::SetAcceleration);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gAccelerationConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1013C320
			fight::ConditionFactory* CreateAccelerationConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<AccelerationCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10094730
			// EQUIVALENT: register allocation (the engine keeps this in esi and the object in edi, ours the other way round) (93.6 %)
			bool AccelerationCondition::Evaluate(int a, int b, int c, int d)
			{
				engine::GameObject* object = engine::GetObjectHandle(AsOwner(c)).Get();
				if (object == 0)
				{
					return false;
				}
				AccelerationGetMessage message(type);
				object->SendMessage(&message);
				math::Vector local;
				local.x = message.acceleration.x;
				local.y = message.acceleration.y;
				local.z = message.acceleration.z;
				object->transform->value.RotateInverse(local, local);
				return fight::CompareVectorMeasure(compare, &local, direction, acceleration);
			}

			template class fight::PropertyEnumConstList<AccelerationCondition>;
			template class fight::PropertyFloatConstRange<AccelerationCondition>;
			template class fight::ConditionFactoryTemplate<AccelerationCondition>;
			template class fight::ConditionFactoryCasterTemplate<AccelerationCondition>;
		}

		// FUNCTION: ENGINE 0x1013C4E0
		void RegisterAccelerationFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::ConditionFactoryCasterTemplate<motion::AccelerationCondition> caster;
			registry->AddFactory(fight::FindConditionFactory(name, &caster));
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1013C120
// FUNCTION: ENGINE 0x1013C170
// FUNCTION: ENGINE 0x1013C180
// FUNCTION: ENGINE 0x1013C1B0
// FUNCTION: ENGINE 0x1013C230
// FUNCTION: ENGINE 0x1013C240
// FUNCTION: ENGINE 0x1013C270
// FUNCTION: ENGINE 0x1013C290
// FUNCTION: ENGINE 0x1013C2A0
// FUNCTION: ENGINE 0x1013C2E0
// FUNCTION: ENGINE 0x1013C310
// FUNCTION: ENGINE 0x1013C510
// FUNCTION: ENGINE 0x1013C540
// FUNCTION: ENGINE 0x1013C560
