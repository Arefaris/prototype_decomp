// Fight items of the motion group: WallSlideTrack (unit 0x101D0240 - 0x101D0A00; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_wallslide.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gWallSlideTrackProperties;  // 0x11254CBC

			// FUNCTION: ENGINE 0x101D0240
			bool WallSlideTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0260
			bool WallSlideTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0280
			bool WallSlideTrack::SetVelocityMin(float newValue)
			{
				velocityMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D02A0
			bool WallSlideTrack::SetVelocityMax(float newValue)
			{
				velocityMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D02C0
			bool WallSlideTrack::SetFrictionMin(float newValue)
			{
				frictionMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D02E0
			bool WallSlideTrack::SetFrictionMax(float newValue)
			{
				frictionMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0300
			bool WallSlideTrack::SetContinuous(bool newValue)
			{
				continuous = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0310
			bool WallSlideTrack::SetContinuousGravity(float newValue)
			{
				continuousGravity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0330
			bool WallSlideTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0340
			bool WallSlideTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0360
			bool WallSlideTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D0380
			fight::Property* WallSlideTrack::GetProperty(int index)
			{
				return gWallSlideTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101D03A0
			void WallSlideTrack::ClearProperties()
			{
				fight::FreePropertyList(&gWallSlideTrackProperties);
			}

			// FUNCTION: ENGINE 0x101D03B0
			WallSlideTrack::WallSlideTrack() : blendInTime(0.0f), blendOutTime(0.0f), continuousGravity(0.0f), frictionMax(2e+01f), frictionMin(1e+02f), timeBegin(0.0f), timeEnd(-1.0f), velocityMax(1e+02f), velocityMin(0.0f), priority(-5), continuous(false)
			{
			}

			// FUNCTION: ENGINE 0x101D0430
			float WallSlideTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101D0440
			float WallSlideTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101D0450
			WallSlideTrack::~WallSlideTrack()
			{
			}

			// FUNCTION: ENGINE 0x101D0630
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void WallSlideTrack::RegisterProperties()
			{
				if (gWallSlideTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<WallSlideTrack>("timeBegin", &WallSlideTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<WallSlideTrack>("timeEnd", &WallSlideTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<WallSlideTrack>("velocityMin", &WallSlideTrack::SetVelocityMin);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<WallSlideTrack>("velocityMax", &WallSlideTrack::SetVelocityMax);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<WallSlideTrack>("frictionMin", &WallSlideTrack::SetFrictionMin);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<WallSlideTrack>("frictionMax", &WallSlideTrack::SetFrictionMax);
					properties[5] = property;
					property = new fight::PropertyBool<WallSlideTrack>("continuous", &WallSlideTrack::SetContinuous);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<WallSlideTrack>("continuousGravity", &WallSlideTrack::SetContinuousGravity);
					properties[7] = property;
					property = new fight::PropertyIntConstRange<WallSlideTrack>("priority", &WallSlideTrack::SetPriority);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<WallSlideTrack>("blendInTime", &WallSlideTrack::SetBlendInTime);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<WallSlideTrack>("blendOutTime", &WallSlideTrack::SetBlendOutTime);
					properties[10] = property;
					fight::RegisterPropertyList(properties, &gWallSlideTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101D0600
			fight::TrackFactory* CreateWallSlideTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<WallSlideTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101D0930
			void RegisterWallSlideTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<WallSlideTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<WallSlideTrack>;
			template class fight::PropertyBool<WallSlideTrack>;
			template class fight::PropertyIntConstRange<WallSlideTrack>;
			template class fight::TrackFactoryTemplate<WallSlideTrack>;
			template class fight::TrackFactoryCasterTemplate<WallSlideTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101D0460
// FUNCTION: ENGINE 0x101D0490
// FUNCTION: ENGINE 0x101D04A0
// FUNCTION: ENGINE 0x101D04D0
// FUNCTION: ENGINE 0x101D0500
// FUNCTION: ENGINE 0x101D0530
// FUNCTION: ENGINE 0x101D0540
// FUNCTION: ENGINE 0x101D0570
// FUNCTION: ENGINE 0x101D0590
// FUNCTION: ENGINE 0x101D05A0
// FUNCTION: ENGINE 0x101D05D0
// FUNCTION: ENGINE 0x101D05F0
// FUNCTION: ENGINE 0x101D0960
// FUNCTION: ENGINE 0x101D0990
// FUNCTION: ENGINE 0x101D09B0
