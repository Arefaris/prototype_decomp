// Fight items of the motion group: WallExitTrack (unit 0x101CBD20 - 0x101CC5E0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_wallexit.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gWallExitTrackProperties;  // 0x11254C9C

			// FUNCTION: ENGINE 0x101CBD20
			bool WallExitTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CBD40
			bool WallExitTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CBEC0
			bool WallExitTrack::SetSupportingLimb(const fight::Name& newValue)
			{
				supportingLimb = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CBD60
			bool WallExitTrack::SetVelocityMin(float newValue)
			{
				velocityMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CBD80
			bool WallExitTrack::SetVelocityMax(float newValue)
			{
				velocityMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CBDA0
			bool WallExitTrack::SetGravity(float newValue)
			{
				gravity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CBDC0
			bool WallExitTrack::SetWallAngleUp(float newValue)
			{
				wallAngleUp = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101CBDE0
			bool WallExitTrack::SetWallAngleLateral(float newValue)
			{
				wallAngleLateral = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101CBE00
			bool WallExitTrack::SetWallAngleDown(float newValue)
			{
				wallAngleDown = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101CBE20
			bool WallExitTrack::SetTurningVelocity(float newValue)
			{
				turningVelocity = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101CBE40
			bool WallExitTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CBE50
			bool WallExitTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CBE70
			bool WallExitTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CBE90
			fight::Property* WallExitTrack::GetProperty(int index)
			{
				return gWallExitTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101CBEB0
			void WallExitTrack::ClearProperties()
			{
				fight::FreePropertyList(&gWallExitTrackProperties);
			}

			// FUNCTION: ENGINE 0x101CBEE0
			WallExitTrack::WallExitTrack() : supportingLimb("Climb", 1), blendInTime(0.0f), blendOutTime(0.0f), gravity(2e+01f), timeBegin(0.0f), timeEnd(-1.0f), turningVelocity(0.5235988f), velocityMax(0.0f), velocityMin(0.0f), wallAngleDown(-0.5235988f), wallAngleLateral(0.0f), wallAngleUp(0.5235988f), priority(-5)
			{
			}

			// FUNCTION: ENGINE 0x101CBF90
			float WallExitTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101CBFA0
			float WallExitTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101CBFB0
			WallExitTrack::~WallExitTrack()
			{
			}

			// FUNCTION: ENGINE 0x101CC1C0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void WallExitTrack::RegisterProperties()
			{
				if (gWallExitTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<WallExitTrack>("timeBegin", &WallExitTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<WallExitTrack>("timeEnd", &WallExitTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyNameList<WallExitTrack>("supportingLimb", &WallExitTrack::SetSupportingLimb);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<WallExitTrack>("velocityMin", &WallExitTrack::SetVelocityMin);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<WallExitTrack>("velocityMax", &WallExitTrack::SetVelocityMax);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<WallExitTrack>("gravity", &WallExitTrack::SetGravity);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<WallExitTrack>("wallAngleUp", &WallExitTrack::SetWallAngleUp);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<WallExitTrack>("wallAngleLateral", &WallExitTrack::SetWallAngleLateral);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<WallExitTrack>("wallAngleDown", &WallExitTrack::SetWallAngleDown);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<WallExitTrack>("turningVelocity", &WallExitTrack::SetTurningVelocity);
					properties[9] = property;
					property = new fight::PropertyIntConstRange<WallExitTrack>("priority", &WallExitTrack::SetPriority);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<WallExitTrack>("blendInTime", &WallExitTrack::SetBlendInTime);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<WallExitTrack>("blendOutTime", &WallExitTrack::SetBlendOutTime);
					properties[12] = property;
					fight::RegisterPropertyList(properties, &gWallExitTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101CC100
			fight::TrackFactory* CreateWallExitTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<WallExitTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101CC130
			void RegisterWallExitTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<WallExitTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<WallExitTrack>;
			template class fight::PropertyNameList<WallExitTrack>;
			template class fight::PropertyIntConstRange<WallExitTrack>;
			template class fight::TrackFactoryTemplate<WallExitTrack>;
			template class fight::TrackFactoryCasterTemplate<WallExitTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101CBFC0
// FUNCTION: ENGINE 0x101CBFD0
// FUNCTION: ENGINE 0x101CC000
// FUNCTION: ENGINE 0x101CC030
// FUNCTION: ENGINE 0x101CC060
// FUNCTION: ENGINE 0x101CC090
// FUNCTION: ENGINE 0x101CC0A0
// FUNCTION: ENGINE 0x101CC0D0
// FUNCTION: ENGINE 0x101CC0F0
// FUNCTION: ENGINE 0x101CC160
// FUNCTION: ENGINE 0x101CC190
// FUNCTION: ENGINE 0x101CC1B0
// FUNCTION: ENGINE 0x101CC540
// FUNCTION: ENGINE 0x101CC570
// FUNCTION: ENGINE 0x101CC590
