// Fight items of the motion group: JumpToTrack (unit 0x10185900 - 0x101865E0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_jumpto.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gJumpToTrackProperties;  // 0x112547A0

			// FUNCTION: ENGINE 0x10185900
			bool JumpToTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10185920
			bool JumpToTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10185940
			bool JumpToTrack::SetUseTarget(bool newValue)
			{
				useTarget = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10185950
			bool JumpToTrack::SetChargeType(int newValue)
			{
				chargeType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10185960
			bool JumpToTrack::SetDistanceMin(float newValue)
			{
				distanceMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10185980
			bool JumpToTrack::SetDistanceMax(float newValue)
			{
				distanceMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101859A0
			bool JumpToTrack::SetUseDistanceWhenUsingTarget(bool newValue)
			{
				useDistanceWhenUsingTarget = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101859B0
			bool JumpToTrack::SetMinInitialVelocityMin(float newValue)
			{
				minInitialVelocityMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101859D0
			bool JumpToTrack::SetMinInitialVelocityMax(float newValue)
			{
				minInitialVelocityMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101859F0
			bool JumpToTrack::SetMaxInitialVelocityMin(float newValue)
			{
				maxInitialVelocityMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10185A10
			bool JumpToTrack::SetMaxInitialVelocityMax(float newValue)
			{
				maxInitialVelocityMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10185A30
			bool JumpToTrack::SetTrackingMin(float newValue)
			{
				trackingMin = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10185A50
			bool JumpToTrack::SetTrackingMax(float newValue)
			{
				trackingMax = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10185A70
			bool JumpToTrack::SetMinSpeedTracking(float newValue)
			{
				minSpeedTracking = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10185A90
			bool JumpToTrack::SetLaunchAngle(float newValue)
			{
				launchAngle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10185AB0
			bool JumpToTrack::SetMinLaunchAngle(float newValue)
			{
				minLaunchAngle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10185AD0
			bool JumpToTrack::SetGravity(float newValue)
			{
				gravity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10185AF0
			bool JumpToTrack::SetOffset(const math::Vector& newValue)
			{
				offset.x = newValue.x;
				offset.y = newValue.y;
				offset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10185B10
			bool JumpToTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10185B20
			bool JumpToTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10185B40
			bool JumpToTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10185B60
			fight::Property* JumpToTrack::GetProperty(int index)
			{
				return gJumpToTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10185B80
			void JumpToTrack::ClearProperties()
			{
				fight::FreePropertyList(&gJumpToTrackProperties);
			}

			// FUNCTION: ENGINE 0x10185B90
			JumpToTrack::JumpToTrack() : offset(0.0f, 0.0f, 0.0f), blendInTime(0.0f), blendOutTime(0.0f), distanceMax(1e+02f), distanceMin(1e+02f), gravity(9.8f), launchAngle(0.7853982f), maxInitialVelocityMax(5e+01f), maxInitialVelocityMin(5e+01f), minInitialVelocityMax(1.0f), minInitialVelocityMin(1.0f), minLaunchAngle(0.0f), minSpeedTracking(-1e+02f), timeBegin(0.0f), timeEnd(-1.0f), trackingMax(0.0f), trackingMin(0.0f), chargeType(0), priority(-5), useDistanceWhenUsingTarget(false), useTarget(false)
			{
			}

			// FUNCTION: ENGINE 0x10185C80
			float JumpToTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10185C90
			float JumpToTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10185CA0
			JumpToTrack::~JumpToTrack()
			{
			}

			// FUNCTION: ENGINE 0x10185F90
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void JumpToTrack::RegisterProperties()
			{
				if (gJumpToTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<JumpToTrack>("timeBegin", &JumpToTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<JumpToTrack>("timeEnd", &JumpToTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyBool<JumpToTrack>("useTarget", &JumpToTrack::SetUseTarget);
					properties[2] = property;
					property = new fight::PropertyEnumConstList<JumpToTrack>("chargeType", gChargeConditionTypeTable, gChargeConditionTypeCount, &JumpToTrack::SetChargeType);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<JumpToTrack>("distanceMin", &JumpToTrack::SetDistanceMin);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<JumpToTrack>("distanceMax", &JumpToTrack::SetDistanceMax);
					properties[5] = property;
					property = new fight::PropertyBool<JumpToTrack>("useDistanceWhenUsingTarget", &JumpToTrack::SetUseDistanceWhenUsingTarget);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<JumpToTrack>("minInitialVelocityMin", &JumpToTrack::SetMinInitialVelocityMin);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<JumpToTrack>("minInitialVelocityMax", &JumpToTrack::SetMinInitialVelocityMax);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<JumpToTrack>("maxInitialVelocityMin", &JumpToTrack::SetMaxInitialVelocityMin);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<JumpToTrack>("maxInitialVelocityMax", &JumpToTrack::SetMaxInitialVelocityMax);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<JumpToTrack>("trackingMin", &JumpToTrack::SetTrackingMin);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<JumpToTrack>("trackingMax", &JumpToTrack::SetTrackingMax);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<JumpToTrack>("minSpeedTracking", &JumpToTrack::SetMinSpeedTracking);
					properties[13] = property;
					property = new fight::PropertyFloatConstRange<JumpToTrack>("launchAngle", &JumpToTrack::SetLaunchAngle);
					properties[14] = property;
					property = new fight::PropertyFloatConstRange<JumpToTrack>("minLaunchAngle", &JumpToTrack::SetMinLaunchAngle);
					properties[15] = property;
					property = new fight::PropertyFloatConstRange<JumpToTrack>("gravity", &JumpToTrack::SetGravity);
					properties[16] = property;
					property = new fight::PropertyVector<JumpToTrack>("offset", &JumpToTrack::SetOffset);
					properties[17] = property;
					property = new fight::PropertyIntConstRange<JumpToTrack>("priority", &JumpToTrack::SetPriority);
					properties[18] = property;
					property = new fight::PropertyFloatConstRange<JumpToTrack>("blendInTime", &JumpToTrack::SetBlendInTime);
					properties[19] = property;
					property = new fight::PropertyFloatConstRange<JumpToTrack>("blendOutTime", &JumpToTrack::SetBlendOutTime);
					properties[20] = property;
					fight::RegisterPropertyList(properties, &gJumpToTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10185F60
			fight::TrackFactory* CreateJumpToTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<JumpToTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10186510
			void RegisterJumpToTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<JumpToTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<JumpToTrack>;
			template class fight::PropertyBool<JumpToTrack>;
			template class fight::PropertyEnumConstList<JumpToTrack>;
			template class fight::PropertyVector<JumpToTrack>;
			template class fight::PropertyIntConstRange<JumpToTrack>;
			template class fight::TrackFactoryTemplate<JumpToTrack>;
			template class fight::TrackFactoryCasterTemplate<JumpToTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10185CB0
// FUNCTION: ENGINE 0x10185CE0
// FUNCTION: ENGINE 0x10185CF0
// FUNCTION: ENGINE 0x10185D20
// FUNCTION: ENGINE 0x10185D50
// FUNCTION: ENGINE 0x10185D80
// FUNCTION: ENGINE 0x10185D90
// FUNCTION: ENGINE 0x10185DC0
// FUNCTION: ENGINE 0x10185DE0
// FUNCTION: ENGINE 0x10185DF0
// FUNCTION: ENGINE 0x10185E30
// FUNCTION: ENGINE 0x10185E40
// FUNCTION: ENGINE 0x10185E70
// FUNCTION: ENGINE 0x10185E90
// FUNCTION: ENGINE 0x10185EA0
// FUNCTION: ENGINE 0x10185ED0
// FUNCTION: ENGINE 0x10185EF0
// FUNCTION: ENGINE 0x10185F00
// FUNCTION: ENGINE 0x10185F30
// FUNCTION: ENGINE 0x10185F50
// FUNCTION: ENGINE 0x10186540
// FUNCTION: ENGINE 0x10186570
// FUNCTION: ENGINE 0x10186590
