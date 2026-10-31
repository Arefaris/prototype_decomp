// Fight items of the motion group: JumpYTrack (unit 0x101865E0 - 0x10187250; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_jumpy.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gJumpYTrackProperties;  // 0x112547A4

			// FUNCTION: ENGINE 0x101865E0
			bool JumpYTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10186600
			bool JumpYTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10186620
			bool JumpYTrack::SetFlightTimeMin(float newValue)
			{
				flightTimeMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10186640
			bool JumpYTrack::SetFlightTimeMax(float newValue)
			{
				flightTimeMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10186660
			bool JumpYTrack::SetHeightMin(float newValue)
			{
				heightMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10186680
			bool JumpYTrack::SetHeightMax(float newValue)
			{
				heightMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101866A0
			bool JumpYTrack::SetForwardVelocityMin(float newValue)
			{
				forwardVelocityMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101866C0
			bool JumpYTrack::SetForwardVelocityMax(float newValue)
			{
				forwardVelocityMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101866E0
			bool JumpYTrack::SetMaxFallSpeed(float newValue)
			{
				maxFallSpeed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10186700
			bool JumpYTrack::SetUseSprintVelocity(bool newValue)
			{
				useSprintVelocity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10186710
			bool JumpYTrack::SetTurningVelocityMin(float newValue)
			{
				turningVelocityMin = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10186730
			bool JumpYTrack::SetTurningVelocityMinForwardSpeedCap(float newValue)
			{
				turningVelocityMinForwardSpeedCap = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10186750
			bool JumpYTrack::SetTurningVelocityMax(float newValue)
			{
				turningVelocityMax = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10186770
			bool JumpYTrack::SetTurningVelocityMaxForwardSpeedCap(float newValue)
			{
				turningVelocityMaxForwardSpeedCap = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10186790
			bool JumpYTrack::SetUnlockableFirst(int newValue)
			{
				unlockableFirst = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101867A0
			bool JumpYTrack::SetUnlockableLast(int newValue)
			{
				unlockableLast = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101867B0
			bool JumpYTrack::SetUnlockableFlightTimeMin(float newValue)
			{
				unlockableFlightTimeMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101867D0
			bool JumpYTrack::SetUnlockableHeightMin(float newValue)
			{
				unlockableHeightMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101867F0
			bool JumpYTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10186800
			bool JumpYTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10186820
			bool JumpYTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10186840
			fight::Property* JumpYTrack::GetProperty(int index)
			{
				return gJumpYTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10186860
			void JumpYTrack::ClearProperties()
			{
				fight::FreePropertyList(&gJumpYTrackProperties);
			}

			// FUNCTION: ENGINE 0x10186870
			JumpYTrack::JumpYTrack() : blendInTime(0.0f), blendOutTime(0.0f), flightTimeMax(4.0f), flightTimeMin(2.0f), forwardVelocityMax(-1.0f), forwardVelocityMin(0.0f), heightMax(4.0f), heightMin(2.0f), maxFallSpeed(5e+01f), timeBegin(0.0f), timeEnd(-1.0f), turningVelocityMax(0.0f), turningVelocityMaxForwardSpeedCap(0.0f), turningVelocityMin(0.0f), turningVelocityMinForwardSpeedCap(0.0f), unlockableFlightTimeMin(0.0f), unlockableHeightMin(0.0f), priority(-5), unlockableFirst(0), unlockableLast(0), useSprintVelocity(false)
			{
			}

			// FUNCTION: ENGINE 0x10186940
			float JumpYTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10186950
			float JumpYTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10186960
			JumpYTrack::~JumpYTrack()
			{
			}

			// FUNCTION: ENGINE 0x10186BF0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void JumpYTrack::RegisterProperties()
			{
				if (gJumpYTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<JumpYTrack>("timeBegin", &JumpYTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<JumpYTrack>("timeEnd", &JumpYTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<JumpYTrack>("flightTimeMin", &JumpYTrack::SetFlightTimeMin);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<JumpYTrack>("flightTimeMax", &JumpYTrack::SetFlightTimeMax);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<JumpYTrack>("heightMin", &JumpYTrack::SetHeightMin);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<JumpYTrack>("heightMax", &JumpYTrack::SetHeightMax);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<JumpYTrack>("forwardVelocityMin", &JumpYTrack::SetForwardVelocityMin);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<JumpYTrack>("forwardVelocityMax", &JumpYTrack::SetForwardVelocityMax);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<JumpYTrack>("maxFallSpeed", &JumpYTrack::SetMaxFallSpeed);
					properties[8] = property;
					property = new fight::PropertyBool<JumpYTrack>("useSprintVelocity", &JumpYTrack::SetUseSprintVelocity);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<JumpYTrack>("turningVelocityMin", &JumpYTrack::SetTurningVelocityMin);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<JumpYTrack>("turningVelocityMinForwardSpeedCap", &JumpYTrack::SetTurningVelocityMinForwardSpeedCap);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<JumpYTrack>("turningVelocityMax", &JumpYTrack::SetTurningVelocityMax);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<JumpYTrack>("turningVelocityMaxForwardSpeedCap", &JumpYTrack::SetTurningVelocityMaxForwardSpeedCap);
					properties[13] = property;
					property = new fight::PropertyEnumConstList<JumpYTrack>("unlockableFirst", gJumpTrackUnlockableFirstTable, gJumpTrackUnlockableFirstCount, &JumpYTrack::SetUnlockableFirst);
					properties[14] = property;
					property = new fight::PropertyEnumConstList<JumpYTrack>("unlockableLast", gJumpTrackUnlockableFirstTable, gJumpTrackUnlockableFirstCount, &JumpYTrack::SetUnlockableLast);
					properties[15] = property;
					property = new fight::PropertyFloatConstRange<JumpYTrack>("unlockableFlightTimeMin", &JumpYTrack::SetUnlockableFlightTimeMin);
					properties[16] = property;
					property = new fight::PropertyFloatConstRange<JumpYTrack>("unlockableHeightMin", &JumpYTrack::SetUnlockableHeightMin);
					properties[17] = property;
					property = new fight::PropertyIntConstRange<JumpYTrack>("priority", &JumpYTrack::SetPriority);
					properties[18] = property;
					property = new fight::PropertyFloatConstRange<JumpYTrack>("blendInTime", &JumpYTrack::SetBlendInTime);
					properties[19] = property;
					property = new fight::PropertyFloatConstRange<JumpYTrack>("blendOutTime", &JumpYTrack::SetBlendOutTime);
					properties[20] = property;
					fight::RegisterPropertyList(properties, &gJumpYTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10186BC0
			fight::TrackFactory* CreateJumpYTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<JumpYTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10187180
			void RegisterJumpYTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<JumpYTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<JumpYTrack>;
			template class fight::PropertyBool<JumpYTrack>;
			template class fight::PropertyEnumConstList<JumpYTrack>;
			template class fight::PropertyIntConstRange<JumpYTrack>;
			template class fight::TrackFactoryTemplate<JumpYTrack>;
			template class fight::TrackFactoryCasterTemplate<JumpYTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10186970
// FUNCTION: ENGINE 0x101869A0
// FUNCTION: ENGINE 0x101869B0
// FUNCTION: ENGINE 0x101869E0
// FUNCTION: ENGINE 0x10186A10
// FUNCTION: ENGINE 0x10186A40
// FUNCTION: ENGINE 0x10186A50
// FUNCTION: ENGINE 0x10186A80
// FUNCTION: ENGINE 0x10186AA0
// FUNCTION: ENGINE 0x10186AB0
// FUNCTION: ENGINE 0x10186AF0
// FUNCTION: ENGINE 0x10186B00
// FUNCTION: ENGINE 0x10186B30
// FUNCTION: ENGINE 0x10186B50
// FUNCTION: ENGINE 0x10186B60
// FUNCTION: ENGINE 0x10186B90
// FUNCTION: ENGINE 0x10186BB0
// FUNCTION: ENGINE 0x101871B0
// FUNCTION: ENGINE 0x101871E0
// FUNCTION: ENGINE 0x10187200
