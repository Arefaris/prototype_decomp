// Fight items of the motion group: FlyingAttackTrack (unit 0x1015F0E0 - 0x1015FAE0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_flyingattack.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gFlyingAttackTrackProperties;  // 0x11254530

			// FUNCTION: ENGINE 0x1015F0E0
			bool FlyingAttackTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015F100
			bool FlyingAttackTrack::SetTimeEndMin(float newValue)
			{
				timeEndMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015F120
			bool FlyingAttackTrack::SetTimeEndMax(float newValue)
			{
				timeEndMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015F140
			bool FlyingAttackTrack::SetDirection(const math::Vector& newValue)
			{
				direction.x = newValue.x;
				direction.y = newValue.y;
				direction.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1015F160
			bool FlyingAttackTrack::SetVelocityMin(float newValue)
			{
				velocityMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015F180
			bool FlyingAttackTrack::SetVelocityMax(float newValue)
			{
				velocityMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015F1A0
			bool FlyingAttackTrack::SetAccelerationMin(float newValue)
			{
				accelerationMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015F1C0
			bool FlyingAttackTrack::SetAccelerationMax(float newValue)
			{
				accelerationMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015F1E0
			bool FlyingAttackTrack::SetTrackingMin(float newValue)
			{
				trackingMin = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1015F200
			bool FlyingAttackTrack::SetTrackingMax(float newValue)
			{
				trackingMax = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1015F220
			bool FlyingAttackTrack::SetFaceDirection(bool newValue)
			{
				faceDirection = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015F230
			bool FlyingAttackTrack::SetUseAutoTarget(bool newValue)
			{
				useAutoTarget = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015F240
			bool FlyingAttackTrack::SetSlideOnGround(bool newValue)
			{
				slideOnGround = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015F250
			bool FlyingAttackTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015F260
			bool FlyingAttackTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015F280
			bool FlyingAttackTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015F2A0
			fight::Property* FlyingAttackTrack::GetProperty(int index)
			{
				return gFlyingAttackTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1015F2C0
			void FlyingAttackTrack::ClearProperties()
			{
				fight::FreePropertyList(&gFlyingAttackTrackProperties);
			}

			// FUNCTION: ENGINE 0x1015F2D0
			FlyingAttackTrack::FlyingAttackTrack() : direction(0.0f, 0.0f, -1.0f), accelerationMax(0.0f), accelerationMin(0.0f), blendInTime(0.0f), blendOutTime(0.0f), timeBegin(0.0f), timeEndMax(-1.0f), timeEndMin(-1.0f), trackingMax(3.1415927f), trackingMin(3.1415927f), velocityMax(5e+01f), velocityMin(5e+01f), priority(-5), faceDirection(false), slideOnGround(true), useAutoTarget(true)
			{
			}

			// FUNCTION: ENGINE 0x1015F380
			float FlyingAttackTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1015F390
			float FlyingAttackTrack::Slot10() const
			{
				return -1.0f;
			}

			// FUNCTION: ENGINE 0x1015F3A0
			FlyingAttackTrack::~FlyingAttackTrack()
			{
			}

			// FUNCTION: ENGINE 0x1015F5E0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void FlyingAttackTrack::RegisterProperties()
			{
				if (gFlyingAttackTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<FlyingAttackTrack>("timeBegin", &FlyingAttackTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<FlyingAttackTrack>("timeEndMin", &FlyingAttackTrack::SetTimeEndMin);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<FlyingAttackTrack>("timeEndMax", &FlyingAttackTrack::SetTimeEndMax);
					properties[2] = property;
					property = new fight::PropertyVector<FlyingAttackTrack>("direction", &FlyingAttackTrack::SetDirection);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<FlyingAttackTrack>("velocityMin", &FlyingAttackTrack::SetVelocityMin);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<FlyingAttackTrack>("velocityMax", &FlyingAttackTrack::SetVelocityMax);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<FlyingAttackTrack>("accelerationMin", &FlyingAttackTrack::SetAccelerationMin);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<FlyingAttackTrack>("accelerationMax", &FlyingAttackTrack::SetAccelerationMax);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<FlyingAttackTrack>("trackingMin", &FlyingAttackTrack::SetTrackingMin);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<FlyingAttackTrack>("trackingMax", &FlyingAttackTrack::SetTrackingMax);
					properties[9] = property;
					property = new fight::PropertyBool<FlyingAttackTrack>("faceDirection", &FlyingAttackTrack::SetFaceDirection);
					properties[10] = property;
					property = new fight::PropertyBool<FlyingAttackTrack>("useAutoTarget", &FlyingAttackTrack::SetUseAutoTarget);
					properties[11] = property;
					property = new fight::PropertyBool<FlyingAttackTrack>("slideOnGround", &FlyingAttackTrack::SetSlideOnGround);
					properties[12] = property;
					property = new fight::PropertyIntConstRange<FlyingAttackTrack>("priority", &FlyingAttackTrack::SetPriority);
					properties[13] = property;
					property = new fight::PropertyFloatConstRange<FlyingAttackTrack>("blendInTime", &FlyingAttackTrack::SetBlendInTime);
					properties[14] = property;
					property = new fight::PropertyFloatConstRange<FlyingAttackTrack>("blendOutTime", &FlyingAttackTrack::SetBlendOutTime);
					properties[15] = property;
					fight::RegisterPropertyList(properties, &gFlyingAttackTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1015F5B0
			fight::TrackFactory* CreateFlyingAttackTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<FlyingAttackTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1015FA10
			void RegisterFlyingAttackTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<FlyingAttackTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<FlyingAttackTrack>;
			template class fight::PropertyVector<FlyingAttackTrack>;
			template class fight::PropertyBool<FlyingAttackTrack>;
			template class fight::PropertyIntConstRange<FlyingAttackTrack>;
			template class fight::TrackFactoryTemplate<FlyingAttackTrack>;
			template class fight::TrackFactoryCasterTemplate<FlyingAttackTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1015F3B0
// FUNCTION: ENGINE 0x1015F3E0
// FUNCTION: ENGINE 0x1015F3F0
// FUNCTION: ENGINE 0x1015F420
// FUNCTION: ENGINE 0x1015F450
// FUNCTION: ENGINE 0x1015F480
// FUNCTION: ENGINE 0x1015F490
// FUNCTION: ENGINE 0x1015F4C0
// FUNCTION: ENGINE 0x1015F4E0
// FUNCTION: ENGINE 0x1015F4F0
// FUNCTION: ENGINE 0x1015F520
// FUNCTION: ENGINE 0x1015F540
// FUNCTION: ENGINE 0x1015F550
// FUNCTION: ENGINE 0x1015F580
// FUNCTION: ENGINE 0x1015F5A0
// FUNCTION: ENGINE 0x1015FA40
// FUNCTION: ENGINE 0x1015FA70
// FUNCTION: ENGINE 0x1015FA90
