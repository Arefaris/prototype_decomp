// Fight items of the motion group: HitReactionThrowTrack, ThrowTrack (unit 0x101BE030 - 0x101BF880; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_throw.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gHitReactionThrowTrackProperties;  // 0x11254BA8

			// FUNCTION: ENGINE 0x101BE030
			bool HitReactionThrowTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE050
			bool HitReactionThrowTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE070
			bool HitReactionThrowTrack::SetAutoTargetArc(float newValue)
			{
				autoTargetArc = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE090
			bool HitReactionThrowTrack::SetMaxTargetArc(float newValue)
			{
				maxTargetArc = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE0B0
			bool HitReactionThrowTrack::SetDistanceMin(float newValue)
			{
				distanceMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE0D0
			bool HitReactionThrowTrack::SetDistanceMax(float newValue)
			{
				distanceMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE0F0
			bool HitReactionThrowTrack::SetVelocityMin(float newValue)
			{
				velocityMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE110
			bool HitReactionThrowTrack::SetVelocityMax(float newValue)
			{
				velocityMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE130
			bool HitReactionThrowTrack::SetTrackingMin(float newValue)
			{
				trackingMin = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE150
			bool HitReactionThrowTrack::SetTrackingMax(float newValue)
			{
				trackingMax = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE170
			bool HitReactionThrowTrack::SetSpinMin(float newValue)
			{
				spinMin = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE190
			bool HitReactionThrowTrack::SetSpinMax(float newValue)
			{
				spinMax = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE1B0
			bool HitReactionThrowTrack::SetArcRange(float newValue)
			{
				arcRange = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE1D0
			bool HitReactionThrowTrack::SetArcMax(float newValue)
			{
				arcMax = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE1F0
			bool HitReactionThrowTrack::SetDamageMin(float newValue)
			{
				damageMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE210
			bool HitReactionThrowTrack::SetDamageMax(float newValue)
			{
				damageMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE230
			bool HitReactionThrowTrack::SetImpulseMin(float newValue)
			{
				impulseMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE250
			bool HitReactionThrowTrack::SetImpulseMax(float newValue)
			{
				impulseMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE270
			bool HitReactionThrowTrack::SetFriendlyFire(float newValue)
			{
				friendlyFire = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE560
			bool HitReactionThrowTrack::SetHitType(const fight::Name& newValue)
			{
				hitType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE500
			fight::Property* HitReactionThrowTrack::GetProperty(int index)
			{
				return gHitReactionThrowTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101BE520
			void HitReactionThrowTrack::ClearProperties()
			{
				fight::FreePropertyList(&gHitReactionThrowTrackProperties);
			}

			// FUNCTION: ENGINE 0x101BE5C0
			HitReactionThrowTrack::HitReactionThrowTrack() : arcMax(0.0f), arcRange(0.0f), autoTargetArc(1.5707964f), damageMax(0.0f), damageMin(0.0f), distanceMax(0.0f), distanceMin(0.0f), friendlyFire(1.0f), impulseMax(0.0f), impulseMin(0.0f), maxTargetArc(3.1415927f), spinMax(0.0f), spinMin(0.0f), timeBegin(0.0f), timeEnd(-1.0f), trackingMax(0.0f), trackingMin(0.0f), velocityMax(0.0f), velocityMin(0.0f)
			{
			}

			// FUNCTION: ENGINE 0x101BE690
			float HitReactionThrowTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101BE6A0
			float HitReactionThrowTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101BE6B0
			HitReactionThrowTrack::~HitReactionThrowTrack()
			{
			}

			// FUNCTION: ENGINE 0x101BEC30
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void HitReactionThrowTrack::RegisterProperties()
			{
				if (gHitReactionThrowTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<HitReactionThrowTrack>("timeBegin", &HitReactionThrowTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<HitReactionThrowTrack>("timeEnd", &HitReactionThrowTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<HitReactionThrowTrack>("autoTargetArc", &HitReactionThrowTrack::SetAutoTargetArc);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<HitReactionThrowTrack>("maxTargetArc", &HitReactionThrowTrack::SetMaxTargetArc);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<HitReactionThrowTrack>("distanceMin", &HitReactionThrowTrack::SetDistanceMin);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<HitReactionThrowTrack>("distanceMax", &HitReactionThrowTrack::SetDistanceMax);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<HitReactionThrowTrack>("velocityMin", &HitReactionThrowTrack::SetVelocityMin);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<HitReactionThrowTrack>("velocityMax", &HitReactionThrowTrack::SetVelocityMax);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<HitReactionThrowTrack>("trackingMin", &HitReactionThrowTrack::SetTrackingMin);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<HitReactionThrowTrack>("trackingMax", &HitReactionThrowTrack::SetTrackingMax);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<HitReactionThrowTrack>("spinMin", &HitReactionThrowTrack::SetSpinMin);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<HitReactionThrowTrack>("spinMax", &HitReactionThrowTrack::SetSpinMax);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<HitReactionThrowTrack>("arcRange", &HitReactionThrowTrack::SetArcRange);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<HitReactionThrowTrack>("arcMax", &HitReactionThrowTrack::SetArcMax);
					properties[13] = property;
					property = new fight::PropertyFloatConstRange<HitReactionThrowTrack>("damageMin", &HitReactionThrowTrack::SetDamageMin);
					properties[14] = property;
					property = new fight::PropertyFloatConstRange<HitReactionThrowTrack>("damageMax", &HitReactionThrowTrack::SetDamageMax);
					properties[15] = property;
					property = new fight::PropertyFloatConstRange<HitReactionThrowTrack>("impulseMin", &HitReactionThrowTrack::SetImpulseMin);
					properties[16] = property;
					property = new fight::PropertyFloatConstRange<HitReactionThrowTrack>("impulseMax", &HitReactionThrowTrack::SetImpulseMax);
					properties[17] = property;
					property = new fight::PropertyFloatConstRange<HitReactionThrowTrack>("friendlyFire", &HitReactionThrowTrack::SetFriendlyFire);
					properties[18] = property;
					property = new fight::PropertyNameList<HitReactionThrowTrack>("hitType", &HitReactionThrowTrack::SetHitType);
					properties[19] = property;
					fight::RegisterPropertyList(properties, &gHitReactionThrowTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101BEAB0
			fight::TrackFactory* CreateHitReactionThrowTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<HitReactionThrowTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101BEB10
			void RegisterHitReactionThrowTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<HitReactionThrowTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gThrowTrackProperties;  // 0x11254BAC

			// FUNCTION: ENGINE 0x101BE290
			bool ThrowTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE580
			bool ThrowTrack::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE2B0
			bool ThrowTrack::SetDirection(const math::Vector& newValue)
			{
				direction.x = newValue.x;
				direction.y = newValue.y;
				direction.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE2D0
			bool ThrowTrack::SetDistanceMin(float newValue)
			{
				distanceMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE2F0
			bool ThrowTrack::SetDistanceMax(float newValue)
			{
				distanceMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE310
			bool ThrowTrack::SetVelocityMin(float newValue)
			{
				velocityMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE330
			bool ThrowTrack::SetVelocityMax(float newValue)
			{
				velocityMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE350
			bool ThrowTrack::SetTrackingMin(float newValue)
			{
				trackingMin = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE370
			bool ThrowTrack::SetTrackingMax(float newValue)
			{
				trackingMax = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE390
			bool ThrowTrack::SetSpinMin(float newValue)
			{
				spinMin = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE3B0
			bool ThrowTrack::SetSpinMax(float newValue)
			{
				spinMax = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE3D0
			bool ThrowTrack::SetArcRange(float newValue)
			{
				arcRange = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE3F0
			bool ThrowTrack::SetArcMax(float newValue)
			{
				arcMax = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE410
			bool ThrowTrack::SetDamageMin(float newValue)
			{
				damageMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE430
			bool ThrowTrack::SetDamageMax(float newValue)
			{
				damageMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE450
			bool ThrowTrack::SetImpulseMin(float newValue)
			{
				impulseMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE470
			bool ThrowTrack::SetImpulseMax(float newValue)
			{
				impulseMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE490
			bool ThrowTrack::SetFriendlyFire(float newValue)
			{
				friendlyFire = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE4B0
			bool ThrowTrack::SetUseTarget(bool newValue)
			{
				useTarget = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE4C0
			bool ThrowTrack::SetUseTargetVehicle(bool newValue)
			{
				useTargetVehicle = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE4D0
			bool ThrowTrack::SetRandomOffset(float newValue)
			{
				randomOffset = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE4F0
			bool ThrowTrack::SetInterruptPriority(int newValue)
			{
				interruptPriority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE5A0
			bool ThrowTrack::SetHitType(const fight::Name& newValue)
			{
				hitType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101BE530
			fight::Property* ThrowTrack::GetProperty(int index)
			{
				return gThrowTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101BE550
			void ThrowTrack::ClearProperties()
			{
				fight::FreePropertyList(&gThrowTrackProperties);
			}

			// FUNCTION: ENGINE 0x101BE6C0
			ThrowTrack::ThrowTrack() : direction(0.0f, 0.0f, -1.0f), arcMax(0.0f), arcRange(0.0f), damageMax(0.0f), damageMin(0.0f), distanceMax(0.0f), distanceMin(0.0f), friendlyFire(1.0f), impulseMax(0.0f), impulseMin(0.0f), randomOffset(0.0f), spinMax(0.0f), spinMin(0.0f), timeBegin(0.0f), trackingMax(0.0f), trackingMin(0.0f), velocityMax(0.0f), velocityMin(0.0f), interruptPriority(-5), useTarget(true), useTargetVehicle(false)
			{
			}

			// FUNCTION: ENGINE 0x101BE7A0
			float ThrowTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101BE7B0
			float ThrowTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101BE7C0
			ThrowTrack::~ThrowTrack()
			{
			}

			// FUNCTION: ENGINE 0x101BF160
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ThrowTrack::RegisterProperties()
			{
				if (gThrowTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ThrowTrack>("timeBegin", &ThrowTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyNameList<ThrowTrack>("grabSlot", &ThrowTrack::SetGrabSlot);
					properties[1] = property;
					property = new fight::PropertyVector<ThrowTrack>("direction", &ThrowTrack::SetDirection);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<ThrowTrack>("distanceMin", &ThrowTrack::SetDistanceMin);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<ThrowTrack>("distanceMax", &ThrowTrack::SetDistanceMax);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<ThrowTrack>("velocityMin", &ThrowTrack::SetVelocityMin);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<ThrowTrack>("velocityMax", &ThrowTrack::SetVelocityMax);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<ThrowTrack>("trackingMin", &ThrowTrack::SetTrackingMin);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<ThrowTrack>("trackingMax", &ThrowTrack::SetTrackingMax);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<ThrowTrack>("spinMin", &ThrowTrack::SetSpinMin);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<ThrowTrack>("spinMax", &ThrowTrack::SetSpinMax);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<ThrowTrack>("arcRange", &ThrowTrack::SetArcRange);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<ThrowTrack>("arcMax", &ThrowTrack::SetArcMax);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<ThrowTrack>("damageMin", &ThrowTrack::SetDamageMin);
					properties[13] = property;
					property = new fight::PropertyFloatConstRange<ThrowTrack>("damageMax", &ThrowTrack::SetDamageMax);
					properties[14] = property;
					property = new fight::PropertyFloatConstRange<ThrowTrack>("impulseMin", &ThrowTrack::SetImpulseMin);
					properties[15] = property;
					property = new fight::PropertyFloatConstRange<ThrowTrack>("impulseMax", &ThrowTrack::SetImpulseMax);
					properties[16] = property;
					property = new fight::PropertyFloatConstRange<ThrowTrack>("friendlyFire", &ThrowTrack::SetFriendlyFire);
					properties[17] = property;
					property = new fight::PropertyBool<ThrowTrack>("useTarget", &ThrowTrack::SetUseTarget);
					properties[18] = property;
					property = new fight::PropertyBool<ThrowTrack>("useTargetVehicle", &ThrowTrack::SetUseTargetVehicle);
					properties[19] = property;
					property = new fight::PropertyFloatConstRange<ThrowTrack>("randomOffset", &ThrowTrack::SetRandomOffset);
					properties[20] = property;
					property = new fight::PropertyIntConstRange<ThrowTrack>("interruptPriority", &ThrowTrack::SetInterruptPriority);
					properties[21] = property;
					property = new fight::PropertyNameList<ThrowTrack>("hitType", &ThrowTrack::SetHitType);
					properties[22] = property;
					fight::RegisterPropertyList(properties, &gThrowTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101BEAE0
			fight::TrackFactory* CreateThrowTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ThrowTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101BEB40
			void RegisterThrowTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ThrowTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<HitReactionThrowTrack>;
			template class fight::PropertyNameList<HitReactionThrowTrack>;
			template class fight::TrackFactoryTemplate<HitReactionThrowTrack>;
			template class fight::TrackFactoryCasterTemplate<HitReactionThrowTrack>;
			template class fight::PropertyFloatConstRange<ThrowTrack>;
			template class fight::PropertyNameList<ThrowTrack>;
			template class fight::PropertyVector<ThrowTrack>;
			template class fight::PropertyBool<ThrowTrack>;
			template class fight::PropertyIntConstRange<ThrowTrack>;
			template class fight::TrackFactoryTemplate<ThrowTrack>;
			template class fight::TrackFactoryCasterTemplate<ThrowTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101BE7D0
// FUNCTION: ENGINE 0x101BE7E0
// FUNCTION: ENGINE 0x101BE810
// FUNCTION: ENGINE 0x101BE820
// FUNCTION: ENGINE 0x101BE850
// FUNCTION: ENGINE 0x101BE880
// FUNCTION: ENGINE 0x101BE8B0
// FUNCTION: ENGINE 0x101BE8E0
// FUNCTION: ENGINE 0x101BE910
// FUNCTION: ENGINE 0x101BE920
// FUNCTION: ENGINE 0x101BE950
// FUNCTION: ENGINE 0x101BE980
// FUNCTION: ENGINE 0x101BE990
// FUNCTION: ENGINE 0x101BE9C0
// FUNCTION: ENGINE 0x101BE9E0
// FUNCTION: ENGINE 0x101BE9F0
// FUNCTION: ENGINE 0x101BEA20
// FUNCTION: ENGINE 0x101BEA40
// FUNCTION: ENGINE 0x101BEA50
// FUNCTION: ENGINE 0x101BEA80
// FUNCTION: ENGINE 0x101BEAA0
// FUNCTION: ENGINE 0x101BEB70
// FUNCTION: ENGINE 0x101BEBA0
// FUNCTION: ENGINE 0x101BEBC0
// FUNCTION: ENGINE 0x101BEBD0
// FUNCTION: ENGINE 0x101BEC00
// FUNCTION: ENGINE 0x101BEC20
// FUNCTION: ENGINE 0x101BF740
// FUNCTION: ENGINE 0x101BF770
// FUNCTION: ENGINE 0x101BF790
// FUNCTION: ENGINE 0x101BF7C0
// FUNCTION: ENGINE 0x101BF7E0
// FUNCTION: ENGINE 0x101BF830
