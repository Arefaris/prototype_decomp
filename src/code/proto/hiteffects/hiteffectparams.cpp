// proto::HitEffectManager::HitEffectParams: what one hit passes to the fight tree of the hit effects (see the header).
#include "code/proto/hiteffects/hiteffectparams.h"

namespace proto
{
	namespace HitEffectManager
	{
		// FUNCTION: ENGINE 0x104F51A0
		// NONMATCHING: the engine zeroes the integer register after the floats' stores and writes the flag byte behind the serial, 71.9 %
#ifdef NONMATCHING
		HitEffectParams::HitEffectParams() : fight::Params(0x40000), kind(10), giver(), receiver(), chargeValue(0.0f), hitType(), effectType()
		{
			float one = engine::driving::gOne;
			unknown84.unknown0 = one;
			unknown84.unknownC = one;
			unknown84.unknown10 = one;
			unknown84.unknown4 = 0;
			unknown84.unknown8 = 0;
			physicsObject = -1;
			physicsObjectSerial = 0xFFFF;
			objectVolume = 0.0f;
			objectSpeed = 0.0f;
			fromMuscleMass = false;
		}
#endif

		// FUNCTION: ENGINE 0x104F5270
		HitEffectParams::~HitEffectParams()
		{
		}
		// FUNCTION: ENGINE 0x104F3630
		void HitEffectParams::SetDamageType(int newValue)
		{
			damageType = newValue;
		}

		// FUNCTION: ENGINE 0x104F3640
		void HitEffectParams::SetDamageGiven(float newValue)
		{
			damageGiven = newValue;
		}

		// FUNCTION: ENGINE 0x104F3660
		void HitEffectParams::SetDamageTaken(float newValue)
		{
			damageTaken = newValue;
		}

		// FUNCTION: ENGINE 0x104F3680
		void HitEffectParams::SetAttackType(int newValue)
		{
			attackType = newValue;
		}

		// FUNCTION: ENGINE 0x104F3690
		void HitEffectParams::SetUnknown7C(const math::Vector2& newValue)
		{
			unknown7C = newValue.x;
			unknown80 = newValue.y;
		}

		// FUNCTION: ENGINE 0x104F36B0
		void HitEffectParams::SetUnknown84(const HitEffectUnknown84* newValue)
		{
			if (newValue)
			{
				unknown84 = *newValue;
			}
			else
			{
				HitEffectUnknown84 defaults;
				unknown84 = defaults;
			}
		}

		// FUNCTION: ENGINE 0x104F3760
		void HitEffectParams::SetUnknown40(const math::Vector& newValue)
		{
			unknown40.x = newValue.x;
			unknown40.y = newValue.y;
			unknown40.z = newValue.z;
		}

		// FUNCTION: ENGINE 0x104F3780
		void HitEffectParams::SetSurfaceNormal(const math::Vector& newValue)
		{
			surfaceNormal.x = newValue.x;
			surfaceNormal.y = newValue.y;
			surfaceNormal.z = newValue.z;
		}

		// FUNCTION: ENGINE 0x104F37A0
		void HitEffectParams::SetUnknown64(const math::Vector& newValue)
		{
			unknown64.x = newValue.x;
			unknown64.y = newValue.y;
			unknown64.z = newValue.z;
		}

		// FUNCTION: ENGINE 0x104F37C0
		void HitEffectParams::SetUnknown70(const math::Vector& newValue)
		{
			unknown70.x = newValue.x;
			unknown70.y = newValue.y;
			unknown70.z = newValue.z;
		}

		// FUNCTION: ENGINE 0x104F37E0
		void HitEffectParams::SetGiver(engine::GameObjectHandle newValue)
		{
			giver = newValue;
		}

		// FUNCTION: ENGINE 0x104F37F0
		void HitEffectParams::SetReceiver(engine::GameObjectHandle newValue)
		{
			receiver = newValue;
		}

		// FUNCTION: ENGINE 0x104F3800
		void HitEffectParams::SetImpactDirection(const math::Vector& newValue)
		{
			impactDirection.x = newValue.x;
			impactDirection.y = newValue.y;
			impactDirection.z = newValue.z;
		}

		// FUNCTION: ENGINE 0x104F3820
		void HitEffectParams::SetMaterialType(unsigned char newValue)
		{
			materialType = newValue;
		}

		// FUNCTION: ENGINE 0x104F3850
		void HitEffectParams::SetChargeValue(float newValue)
		{
			chargeValue = newValue;
		}

		// FUNCTION: ENGINE 0x104F3870
		void HitEffectParams::SetObjectVolume(float newValue)
		{
			objectVolume = newValue;
		}

		// FUNCTION: ENGINE 0x104F3890
		void HitEffectParams::SetObjectSpeed(float newValue)
		{
			objectSpeed = newValue;
		}

		// FUNCTION: ENGINE 0x104F38B0
		void HitEffectParams::SetFromMuscleMass(bool newValue)
		{
			fromMuscleMass = newValue;
		}

		// FUNCTION: ENGINE 0x104F3A00
		void HitEffectParams::SetHitType(const fight::Name& newValue)
		{
			hitType = newValue;
		}

		// FUNCTION: ENGINE 0x104F3A10
		void HitEffectParams::SetEffectType(const fight::Name& newValue)
		{
			effectType = newValue;
		}
	}
}
