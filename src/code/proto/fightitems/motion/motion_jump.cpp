// Fight items of the motion group: JumpTrack (unit 0x10184060 - 0x10184DF0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_jump.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gJumpTrackProperties;  // 0x11254798

			// FUNCTION: ENGINE 0x10184060
			bool JumpTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10184080
			bool JumpTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101840A0
			bool JumpTrack::SetFlightTimeMin(float newValue)
			{
				flightTimeMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101840C0
			bool JumpTrack::SetFlightTimeMax(float newValue)
			{
				flightTimeMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101840E0
			bool JumpTrack::SetUpDistanceMin(float newValue)
			{
				upDistanceMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10184100
			bool JumpTrack::SetUpDistanceMax(float newValue)
			{
				upDistanceMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10184120
			bool JumpTrack::SetForwardDistanceMin(float newValue)
			{
				forwardDistanceMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10184140
			bool JumpTrack::SetForwardDistanceMax(float newValue)
			{
				forwardDistanceMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10184160
			bool JumpTrack::SetMaxFallSpeed(float newValue)
			{
				maxFallSpeed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10184180
			bool JumpTrack::SetTurningVelocityMin(float newValue)
			{
				turningVelocityMin = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101841A0
			bool JumpTrack::SetTurningVelocityMinForwardSpeedCap(float newValue)
			{
				turningVelocityMinForwardSpeedCap = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101841C0
			bool JumpTrack::SetTurningVelocityMax(float newValue)
			{
				turningVelocityMax = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101841E0
			bool JumpTrack::SetTurningVelocityMaxForwardSpeedCap(float newValue)
			{
				turningVelocityMaxForwardSpeedCap = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10184200
			bool JumpTrack::SetRedirect(bool newValue)
			{
				redirect = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10184210
			bool JumpTrack::SetForceRedirect(bool newValue)
			{
				forceRedirect = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10184220
			bool JumpTrack::SetForceRedirectAngle(float newValue)
			{
				forceRedirectAngle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10184240
			bool JumpTrack::SetUnlockableFirst(int newValue)
			{
				unlockableFirst = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10184250
			bool JumpTrack::SetUnlockableLast(int newValue)
			{
				unlockableLast = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10184260
			bool JumpTrack::SetUnlockableFlightTimeMin(float newValue)
			{
				unlockableFlightTimeMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10184280
			bool JumpTrack::SetUnlockableUpDistanceMin(float newValue)
			{
				unlockableUpDistanceMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101842A0
			bool JumpTrack::SetUnlockableForwardDistanceMin(float newValue)
			{
				unlockableForwardDistanceMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101842C0
			bool JumpTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101842D0
			bool JumpTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101842F0
			bool JumpTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10184310
			fight::Property* JumpTrack::GetProperty(int index)
			{
				return gJumpTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10184330
			void JumpTrack::ClearProperties()
			{
				fight::FreePropertyList(&gJumpTrackProperties);
			}

			// FUNCTION: ENGINE 0x10184340
			JumpTrack::JumpTrack() : blendInTime(0.0f), blendOutTime(0.0f), flightTimeMax(4.0f), flightTimeMin(2.0f), forceRedirectAngle(0.0f), forwardDistanceMax(4.0f), forwardDistanceMin(2.0f), maxFallSpeed(5e+01f), timeBegin(0.0f), timeEnd(-1.0f), turningVelocityMax(0.0f), turningVelocityMaxForwardSpeedCap(0.0f), turningVelocityMin(0.0f), turningVelocityMinForwardSpeedCap(0.0f), unlockableFlightTimeMin(0.0f), unlockableForwardDistanceMin(0.0f), unlockableUpDistanceMin(0.0f), upDistanceMax(4.0f), upDistanceMin(2.0f), priority(-5), unlockableFirst(0), unlockableLast(0), forceRedirect(false), redirect(false)
			{
			}

			// FUNCTION: ENGINE 0x10184420
			float JumpTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10184430
			float JumpTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10184440
			JumpTrack::~JumpTrack()
			{
			}

			// FUNCTION: ENGINE 0x101846D0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void JumpTrack::RegisterProperties()
			{
				if (gJumpTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<JumpTrack>("timeBegin", &JumpTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<JumpTrack>("timeEnd", &JumpTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<JumpTrack>("flightTimeMin", &JumpTrack::SetFlightTimeMin);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<JumpTrack>("flightTimeMax", &JumpTrack::SetFlightTimeMax);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<JumpTrack>("upDistanceMin", &JumpTrack::SetUpDistanceMin);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<JumpTrack>("upDistanceMax", &JumpTrack::SetUpDistanceMax);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<JumpTrack>("forwardDistanceMin", &JumpTrack::SetForwardDistanceMin);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<JumpTrack>("forwardDistanceMax", &JumpTrack::SetForwardDistanceMax);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<JumpTrack>("maxFallSpeed", &JumpTrack::SetMaxFallSpeed);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<JumpTrack>("turningVelocityMin", &JumpTrack::SetTurningVelocityMin);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<JumpTrack>("turningVelocityMinForwardSpeedCap", &JumpTrack::SetTurningVelocityMinForwardSpeedCap);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<JumpTrack>("turningVelocityMax", &JumpTrack::SetTurningVelocityMax);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<JumpTrack>("turningVelocityMaxForwardSpeedCap", &JumpTrack::SetTurningVelocityMaxForwardSpeedCap);
					properties[12] = property;
					property = new fight::PropertyBool<JumpTrack>("redirect", &JumpTrack::SetRedirect);
					properties[13] = property;
					property = new fight::PropertyBool<JumpTrack>("forceRedirect", &JumpTrack::SetForceRedirect);
					properties[14] = property;
					property = new fight::PropertyFloatConstRange<JumpTrack>("forceRedirectAngle", &JumpTrack::SetForceRedirectAngle);
					properties[15] = property;
					property = new fight::PropertyEnumConstList<JumpTrack>("unlockableFirst", gJumpTrackUnlockableFirstTable, gJumpTrackUnlockableFirstCount, &JumpTrack::SetUnlockableFirst);
					properties[16] = property;
					property = new fight::PropertyEnumConstList<JumpTrack>("unlockableLast", gJumpTrackUnlockableFirstTable, gJumpTrackUnlockableFirstCount, &JumpTrack::SetUnlockableLast);
					properties[17] = property;
					property = new fight::PropertyFloatConstRange<JumpTrack>("unlockableFlightTimeMin", &JumpTrack::SetUnlockableFlightTimeMin);
					properties[18] = property;
					property = new fight::PropertyFloatConstRange<JumpTrack>("unlockableUpDistanceMin", &JumpTrack::SetUnlockableUpDistanceMin);
					properties[19] = property;
					property = new fight::PropertyFloatConstRange<JumpTrack>("unlockableForwardDistanceMin", &JumpTrack::SetUnlockableForwardDistanceMin);
					properties[20] = property;
					property = new fight::PropertyIntConstRange<JumpTrack>("priority", &JumpTrack::SetPriority);
					properties[21] = property;
					property = new fight::PropertyFloatConstRange<JumpTrack>("blendInTime", &JumpTrack::SetBlendInTime);
					properties[22] = property;
					property = new fight::PropertyFloatConstRange<JumpTrack>("blendOutTime", &JumpTrack::SetBlendOutTime);
					properties[23] = property;
					fight::RegisterPropertyList(properties, &gJumpTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101846A0
			fight::TrackFactory* CreateJumpTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<JumpTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10184D20
			void RegisterJumpTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<JumpTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<JumpTrack>;
			template class fight::PropertyBool<JumpTrack>;
			template class fight::PropertyEnumConstList<JumpTrack>;
			template class fight::PropertyIntConstRange<JumpTrack>;
			template class fight::TrackFactoryTemplate<JumpTrack>;
			template class fight::TrackFactoryCasterTemplate<JumpTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10184450
// FUNCTION: ENGINE 0x10184480
// FUNCTION: ENGINE 0x10184490
// FUNCTION: ENGINE 0x101844C0
// FUNCTION: ENGINE 0x101844F0
// FUNCTION: ENGINE 0x10184520
// FUNCTION: ENGINE 0x10184530
// FUNCTION: ENGINE 0x10184560
// FUNCTION: ENGINE 0x10184580
// FUNCTION: ENGINE 0x10184590
// FUNCTION: ENGINE 0x101845D0
// FUNCTION: ENGINE 0x101845E0
// FUNCTION: ENGINE 0x10184610
// FUNCTION: ENGINE 0x10184630
// FUNCTION: ENGINE 0x10184640
// FUNCTION: ENGINE 0x10184670
// FUNCTION: ENGINE 0x10184690
// FUNCTION: ENGINE 0x10184D50
// FUNCTION: ENGINE 0x10184D80
// FUNCTION: ENGINE 0x10184DA0
