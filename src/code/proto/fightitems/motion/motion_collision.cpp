// Fight items of the motion group: DetectObbCollisionCondition, HitSurfaceCondition (unit 0x10149DC0 - 0x1014A890; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_collision.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gDetectObbCollisionConditionProperties;  // 0x11254340

			// FUNCTION: ENGINE 0x10149DC0
			bool DetectObbCollisionCondition::SetCollideWith(int newValue)
			{
				collideWith = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10149DD0
			bool DetectObbCollisionCondition::SetMatch(bool newValue)
			{
				match = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10149F30
			bool DetectObbCollisionCondition::SetJoint(const fight::Name& newValue)
			{
				joint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10149DE0
			bool DetectObbCollisionCondition::SetOffset(const math::Vector& newValue)
			{
				offset.x = newValue.x;
				offset.y = newValue.y;
				offset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10149E00
			bool DetectObbCollisionCondition::SetOrientation(const math::Vector& newValue)
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

			// FUNCTION: ENGINE 0x10149E50
			bool DetectObbCollisionCondition::SetExtents(const math::Vector& newValue)
			{
				extents.x = newValue.x;
				extents.y = newValue.y;
				extents.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10149E90
			fight::Property* DetectObbCollisionCondition::GetProperty(int index)
			{
				return gDetectObbCollisionConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10149EB0
			void DetectObbCollisionCondition::ClearProperties()
			{
				fight::FreePropertyList(&gDetectObbCollisionConditionProperties);
			}

			// FUNCTION: ENGINE 0x10149F50
			DetectObbCollisionCondition::DetectObbCollisionCondition() : fight::Condition(0), extents(0.0f, 0.0f, 0.0f), offset(0.0f, 0.0f, 0.0f), orientation(0.0f, 0.0f, 0.0f), collideWith(0), match(true)
			{
			}

			// FUNCTION: ENGINE 0x10149FC0
			DetectObbCollisionCondition::~DetectObbCollisionCondition()
			{
			}

			// FUNCTION: ENGINE 0x1014A5C0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DetectObbCollisionCondition::RegisterProperties()
			{
				if (gDetectObbCollisionConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBitfieldConstList<DetectObbCollisionCondition>("collideWith", gDetectObbCollisionConditionCollideWithTable, gDetectObbCollisionConditionCollideWithCount, &DetectObbCollisionCondition::SetCollideWith);
					properties[0] = property;
					property = new fight::PropertyBool<DetectObbCollisionCondition>("match", &DetectObbCollisionCondition::SetMatch);
					properties[1] = property;
					property = new fight::PropertyNameList<DetectObbCollisionCondition>("joint", &DetectObbCollisionCondition::SetJoint);
					properties[2] = property;
					property = new fight::PropertyVector<DetectObbCollisionCondition>("offset", &DetectObbCollisionCondition::SetOffset);
					properties[3] = property;
					property = new fight::PropertyVector<DetectObbCollisionCondition>("orientation", &DetectObbCollisionCondition::SetOrientation);
					properties[4] = property;
					property = new fight::PropertyVector<DetectObbCollisionCondition>("extents", &DetectObbCollisionCondition::SetExtents);
					properties[5] = property;
					fight::RegisterPropertyList(properties, &gDetectObbCollisionConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1014A360
			fight::ConditionFactory* CreateDetectObbCollisionConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DetectObbCollisionCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1014A4B0
			void RegisterDetectObbCollisionConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DetectObbCollisionCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gHitSurfaceConditionProperties;  // 0x11254344

			// FUNCTION: ENGINE 0x10149E70
			bool HitSurfaceCondition::SetSurface(int newValue)
			{
				surface = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10149E80
			bool HitSurfaceCondition::SetHitSurface(bool newValue)
			{
				hitSurface = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10149EC0
			fight::Property* HitSurfaceCondition::GetProperty(int index)
			{
				return gHitSurfaceConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10149EE0
			void HitSurfaceCondition::ClearProperties()
			{
				fight::FreePropertyList(&gHitSurfaceConditionProperties);
			}

			// FUNCTION: ENGINE 0x10149EF0
			HitSurfaceCondition::HitSurfaceCondition() : fight::Condition(0), surface(0), hitSurface(true)
			{
			}

			// FUNCTION: ENGINE 0x10149F20
			HitSurfaceCondition::~HitSurfaceCondition()
			{
			}

			// FUNCTION: ENGINE 0x1014A3C0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void HitSurfaceCondition::RegisterProperties()
			{
				if (gHitSurfaceConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<HitSurfaceCondition>("surface", gHitSurfaceConditionSurfaceTable, gHitSurfaceConditionSurfaceCount, &HitSurfaceCondition::SetSurface);
					properties[0] = property;
					property = new fight::PropertyBool<HitSurfaceCondition>("hitSurface", &HitSurfaceCondition::SetHitSurface);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gHitSurfaceConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1014A390
			fight::ConditionFactory* CreateHitSurfaceConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HitSurfaceCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1014A4E0
			void RegisterHitSurfaceConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HitSurfaceCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			// ---- actions begin

			// ---- actions end
			template class fight::PropertyBitfieldConstList<DetectObbCollisionCondition>;
			template class fight::PropertyBool<DetectObbCollisionCondition>;
			template class fight::PropertyNameList<DetectObbCollisionCondition>;
			template class fight::PropertyVector<DetectObbCollisionCondition>;
			template class fight::ConditionFactoryTemplate<DetectObbCollisionCondition>;
			template class fight::ConditionFactoryCasterTemplate<DetectObbCollisionCondition>;
			template class fight::PropertyEnumConstList<HitSurfaceCondition>;
			template class fight::PropertyBool<HitSurfaceCondition>;
			template class fight::ConditionFactoryTemplate<HitSurfaceCondition>;
			template class fight::ConditionFactoryCasterTemplate<HitSurfaceCondition>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x100A2E50
// FUNCTION: ENGINE 0x100A2EB0
// FUNCTION: ENGINE 0x100A2EC0
