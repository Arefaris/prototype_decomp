// Fight items of the motion group: JumpYTrack (unit 0x101865E0 - 0x10187250; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_JUMPY_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_JUMPY_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::JumpYTrack (16 vftable slots, 0x64 bytes)
			class JumpYTrack : public fight::Track
			{
			public:
				// 0x10186870
				JumpYTrack();
				virtual ~JumpYTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100E35E0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetFlightTimeMin(float newValue);
				bool SetFlightTimeMax(float newValue);
				bool SetHeightMin(float newValue);
				bool SetHeightMax(float newValue);
				bool SetForwardVelocityMin(float newValue);
				bool SetForwardVelocityMax(float newValue);
				bool SetMaxFallSpeed(float newValue);
				bool SetUseSprintVelocity(bool newValue);
				bool SetTurningVelocityMin(float newValue);
				bool SetTurningVelocityMinForwardSpeedCap(float newValue);
				bool SetTurningVelocityMax(float newValue);
				bool SetTurningVelocityMaxForwardSpeedCap(float newValue);
				bool SetUnlockableFirst(int newValue);
				bool SetUnlockableLast(int newValue);
				bool SetUnlockableFlightTimeMin(float newValue);
				bool SetUnlockableHeightMin(float newValue);
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
					float forwardVelocityMax;  // +0x20
					float forwardVelocityMin;  // +0x24
					float heightMax;  // +0x28
					float heightMin;  // +0x2C
					float maxFallSpeed;  // +0x30
					float timeBegin;  // +0x34
					float timeEnd;  // +0x38
					float turningVelocityMax;  // +0x3C
					float turningVelocityMaxForwardSpeedCap;  // +0x40
					float turningVelocityMin;  // +0x44
					float turningVelocityMinForwardSpeedCap;  // +0x48
					float unlockableFlightTimeMin;  // +0x4C
					float unlockableHeightMin;  // +0x50
					int priority;  // +0x54
					int unlockableFirst;  // +0x58
					int unlockableLast;  // +0x5C
					bool useSprintVelocity;  // +0x60
					unsigned char unknown61[0x3];
			};

			extern fight::Property** gJumpYTrackProperties;
			fight::TrackFactory* CreateJumpYTrackFactory(const char* name);
			void RegisterJumpYTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
