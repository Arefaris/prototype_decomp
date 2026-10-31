// Fight items of the motion group: JumpTrack (unit 0x10184060 - 0x10184DF0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_JUMP_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_JUMP_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::JumpTrack (16 vftable slots, 0x6C bytes)
			class JumpTrack : public fight::Track
			{
			public:
				// 0x10184340
				JumpTrack();
				virtual ~JumpTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100DFAE0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetFlightTimeMin(float newValue);
				bool SetFlightTimeMax(float newValue);
				bool SetUpDistanceMin(float newValue);
				bool SetUpDistanceMax(float newValue);
				bool SetForwardDistanceMin(float newValue);
				bool SetForwardDistanceMax(float newValue);
				bool SetMaxFallSpeed(float newValue);
				bool SetTurningVelocityMin(float newValue);
				bool SetTurningVelocityMinForwardSpeedCap(float newValue);
				bool SetTurningVelocityMax(float newValue);
				bool SetTurningVelocityMaxForwardSpeedCap(float newValue);
				bool SetRedirect(bool newValue);
				bool SetForceRedirect(bool newValue);
				bool SetForceRedirectAngle(float newValue);
				bool SetUnlockableFirst(int newValue);
				bool SetUnlockableLast(int newValue);
				bool SetUnlockableFlightTimeMin(float newValue);
				bool SetUnlockableUpDistanceMin(float newValue);
				bool SetUnlockableForwardDistanceMin(float newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float blendInTime;  // +0x10
					float blendOutTime;  // +0x14
					float flightTimeMax;  // +0x18
					float flightTimeMin;  // +0x1C
					float forceRedirectAngle;  // +0x20
					float forwardDistanceMax;  // +0x24
					float forwardDistanceMin;  // +0x28
					float maxFallSpeed;  // +0x2C
					float timeBegin;  // +0x30
					float timeEnd;  // +0x34
					float turningVelocityMax;  // +0x38
					float turningVelocityMaxForwardSpeedCap;  // +0x3C
					float turningVelocityMin;  // +0x40
					float turningVelocityMinForwardSpeedCap;  // +0x44
					float unlockableFlightTimeMin;  // +0x48
					float unlockableForwardDistanceMin;  // +0x4C
					float unlockableUpDistanceMin;  // +0x50
					float upDistanceMax;  // +0x54
					float upDistanceMin;  // +0x58
					int priority;  // +0x5C
					int unlockableFirst;  // +0x60
					int unlockableLast;  // +0x64
					bool forceRedirect;  // +0x68
					bool redirect;  // +0x69
					unsigned char unknown6A[0x2];
			};

			extern fight::Property** gJumpTrackProperties;
			fight::TrackFactory* CreateJumpTrackFactory(const char* name);
			void RegisterJumpTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
