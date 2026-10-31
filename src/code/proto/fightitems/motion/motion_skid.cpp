// Fight items of the motion group: SkidTrack, SkidPedalTrack (unit 0x101B22B0 - 0x101B3470; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_skid.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gSkidTrackProperties;  // 0x11254ACC

			// FUNCTION: ENGINE 0x101B22B0
			bool SkidTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B22D0
			bool SkidTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B22F0
			bool SkidTrack::SetVelocityInit(float newValue)
			{
				velocityInit = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B2310
			bool SkidTrack::SetVelocityMin(float newValue)
			{
				velocityMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B2330
			bool SkidTrack::SetVelocityMax(float newValue)
			{
				velocityMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B2350
			bool SkidTrack::SetDecelerationMin(float newValue)
			{
				decelerationMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B2370
			bool SkidTrack::SetDecelerationMax(float newValue)
			{
				decelerationMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B2390
			bool SkidTrack::SetSprintVelocityDeceleration(float newValue)
			{
				sprintVelocityDeceleration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B23B0
			bool SkidTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B23C0
			bool SkidTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B23E0
			bool SkidTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B2590
			fight::Property* SkidTrack::GetProperty(int index)
			{
				return gSkidTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101B25B0
			void SkidTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSkidTrackProperties);
			}

			// FUNCTION: ENGINE 0x101B25C0
			SkidTrack::SkidTrack() : blendInTime(0.0f), blendOutTime(0.0f), decelerationMax(2e+01f), decelerationMin(2e+01f), sprintVelocityDeceleration(2.0f), timeBegin(0.0f), timeEnd(-1.0f), velocityInit(0.0f), velocityMax(1e+02f), velocityMin(1e+01f), priority(-5)
			{
			}

			// FUNCTION: ENGINE 0x101B2660
			float SkidTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101B2670
			float SkidTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101B2680
			SkidTrack::~SkidTrack()
			{
			}

			// FUNCTION: ENGINE 0x101B2B10
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SkidTrack::RegisterProperties()
			{
				if (gSkidTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<SkidTrack>("timeBegin", &SkidTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<SkidTrack>("timeEnd", &SkidTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<SkidTrack>("velocityInit", &SkidTrack::SetVelocityInit);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<SkidTrack>("velocityMin", &SkidTrack::SetVelocityMin);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<SkidTrack>("velocityMax", &SkidTrack::SetVelocityMax);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<SkidTrack>("decelerationMin", &SkidTrack::SetDecelerationMin);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<SkidTrack>("decelerationMax", &SkidTrack::SetDecelerationMax);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<SkidTrack>("sprintVelocityDeceleration", &SkidTrack::SetSprintVelocityDeceleration);
					properties[7] = property;
					property = new fight::PropertyIntConstRange<SkidTrack>("priority", &SkidTrack::SetPriority);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<SkidTrack>("blendInTime", &SkidTrack::SetBlendInTime);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<SkidTrack>("blendOutTime", &SkidTrack::SetBlendOutTime);
					properties[10] = property;
					fight::RegisterPropertyList(properties, &gSkidTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101B2AB0
			fight::TrackFactory* CreateSkidTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SkidTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101B2E10
			void RegisterSkidTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SkidTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gSkidPedalTrackProperties;  // 0x11254AD0

			// FUNCTION: ENGINE 0x101B2400
			bool SkidPedalTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B2420
			bool SkidPedalTrack::SetTimeEndMin(float newValue)
			{
				timeEndMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B2440
			bool SkidPedalTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B2460
			bool SkidPedalTrack::SetAcceleration(float newValue)
			{
				acceleration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B2480
			bool SkidPedalTrack::SetVelocityMin(float newValue)
			{
				velocityMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B24A0
			bool SkidPedalTrack::SetVelocityMax(float newValue)
			{
				velocityMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B24C0
			bool SkidPedalTrack::SetTurnVelocityMin(float newValue)
			{
				turnVelocityMin = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101B24E0
			bool SkidPedalTrack::SetTurnVelocityMax(float newValue)
			{
				turnVelocityMax = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101B2500
			bool SkidPedalTrack::SetTurnAccelerationMin(float newValue)
			{
				turnAccelerationMin = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101B2520
			bool SkidPedalTrack::SetTurnAccelerationMax(float newValue)
			{
				turnAccelerationMax = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101B26C0
			bool SkidPedalTrack::SetAnimNorth(const fight::Name& newValue)
			{
				animNorth = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B26E0
			bool SkidPedalTrack::SetAnimWest(const fight::Name& newValue)
			{
				animWest = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B2700
			bool SkidPedalTrack::SetAnimSouth(const fight::Name& newValue)
			{
				animSouth = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B2720
			bool SkidPedalTrack::SetAnimEast(const fight::Name& newValue)
			{
				animEast = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B2540
			bool SkidPedalTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B2550
			bool SkidPedalTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B2570
			bool SkidPedalTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101B2690
			fight::Property* SkidPedalTrack::GetProperty(int index)
			{
				return gSkidPedalTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101B26B0
			void SkidPedalTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSkidPedalTrackProperties);
			}

			// FUNCTION: ENGINE 0x101B2770
			SkidPedalTrack::SkidPedalTrack() : acceleration(2e+01f), blendInTime(0.0f), blendOutTime(0.0f), timeBegin(0.0f), timeEnd(-1.0f), timeEndMin(-1.0f), turnAccelerationMax(0.0f), turnAccelerationMin(0.0f), turnVelocityMax(0.0f), turnVelocityMin(0.0f), velocityMax(3e+01f), velocityMin(1e+01f), priority(0)
			{
			}

			// FUNCTION: ENGINE 0x101B2830
			float SkidPedalTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101B2840
			float SkidPedalTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101B2850
			SkidPedalTrack::~SkidPedalTrack()
			{
			}

			// FUNCTION: ENGINE 0x101B2F10
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SkidPedalTrack::RegisterProperties()
			{
				if (gSkidPedalTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<SkidPedalTrack>("timeBegin", &SkidPedalTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<SkidPedalTrack>("timeEndMin", &SkidPedalTrack::SetTimeEndMin);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<SkidPedalTrack>("timeEnd", &SkidPedalTrack::SetTimeEnd);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<SkidPedalTrack>("acceleration", &SkidPedalTrack::SetAcceleration);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<SkidPedalTrack>("velocityMin", &SkidPedalTrack::SetVelocityMin);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<SkidPedalTrack>("velocityMax", &SkidPedalTrack::SetVelocityMax);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<SkidPedalTrack>("turnVelocityMin", &SkidPedalTrack::SetTurnVelocityMin);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<SkidPedalTrack>("turnVelocityMax", &SkidPedalTrack::SetTurnVelocityMax);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<SkidPedalTrack>("turnAccelerationMin", &SkidPedalTrack::SetTurnAccelerationMin);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<SkidPedalTrack>("turnAccelerationMax", &SkidPedalTrack::SetTurnAccelerationMax);
					properties[9] = property;
					property = new fight::PropertyName<SkidPedalTrack>("animNorth", &SkidPedalTrack::SetAnimNorth);
					properties[10] = property;
					property = new fight::PropertyName<SkidPedalTrack>("animWest", &SkidPedalTrack::SetAnimWest);
					properties[11] = property;
					property = new fight::PropertyName<SkidPedalTrack>("animSouth", &SkidPedalTrack::SetAnimSouth);
					properties[12] = property;
					property = new fight::PropertyName<SkidPedalTrack>("animEast", &SkidPedalTrack::SetAnimEast);
					properties[13] = property;
					property = new fight::PropertyIntConstRange<SkidPedalTrack>("priority", &SkidPedalTrack::SetPriority);
					properties[14] = property;
					property = new fight::PropertyFloatConstRange<SkidPedalTrack>("blendInTime", &SkidPedalTrack::SetBlendInTime);
					properties[15] = property;
					property = new fight::PropertyFloatConstRange<SkidPedalTrack>("blendOutTime", &SkidPedalTrack::SetBlendOutTime);
					properties[16] = property;
					fight::RegisterPropertyList(properties, &gSkidPedalTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101B2AE0
			fight::TrackFactory* CreateSkidPedalTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SkidPedalTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101B2E40
			void RegisterSkidPedalTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SkidPedalTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<SkidTrack>;
			template class fight::PropertyIntConstRange<SkidTrack>;
			template class fight::TrackFactoryTemplate<SkidTrack>;
			template class fight::TrackFactoryCasterTemplate<SkidTrack>;
			template class fight::PropertyFloatConstRange<SkidPedalTrack>;
			template class fight::PropertyName<SkidPedalTrack>;
			template class fight::PropertyIntConstRange<SkidPedalTrack>;
			template class fight::TrackFactoryTemplate<SkidPedalTrack>;
			template class fight::TrackFactoryCasterTemplate<SkidPedalTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101B2740
// FUNCTION: ENGINE 0x101B2860
// FUNCTION: ENGINE 0x101B2870
// FUNCTION: ENGINE 0x101B28A0
// FUNCTION: ENGINE 0x101B28B0
// FUNCTION: ENGINE 0x101B28E0
// FUNCTION: ENGINE 0x101B2910
// FUNCTION: ENGINE 0x101B2940
// FUNCTION: ENGINE 0x101B2970
// FUNCTION: ENGINE 0x101B2980
// FUNCTION: ENGINE 0x101B29B0
// FUNCTION: ENGINE 0x101B29D0
// FUNCTION: ENGINE 0x101B29E0
// FUNCTION: ENGINE 0x101B2A10
// FUNCTION: ENGINE 0x101B2A40
// FUNCTION: ENGINE 0x101B2A50
// FUNCTION: ENGINE 0x101B2A80
// FUNCTION: ENGINE 0x101B2AA0
// FUNCTION: ENGINE 0x101B2E70
// FUNCTION: ENGINE 0x101B2EA0
// FUNCTION: ENGINE 0x101B2EC0
// FUNCTION: ENGINE 0x101B2EF0
// FUNCTION: ENGINE 0x101B3380
// FUNCTION: ENGINE 0x101B33D0
// FUNCTION: ENGINE 0x101B3400
// FUNCTION: ENGINE 0x101B3420
