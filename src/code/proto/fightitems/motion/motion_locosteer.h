// Fight items of the motion group: LocoSteerTrack, LocoSteerLeanTrack (unit 0x1018AAB0 - 0x1018C680; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_LOCOSTEER_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_LOCOSTEER_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::LocoSteerTrack (16 vftable slots, 0x78 bytes)
			class LocoSteerTrack : public fight::Track
			{
			public:
				// 0x1018B140
				LocoSteerTrack();
				virtual ~LocoSteerTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100EA8D0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetAcceleration(float newValue);
				bool SetTurningVelocity(float newValue);
				bool SetVelocityWalk(float newValue);
				bool SetVelocityRun(float newValue);
				bool SetSmoothSteeringAngle(float newValue);
				bool SetUseWorldCoordinates(bool newValue);
				bool SetPhase(float newValue);
				bool SetLocomotion(const fight::Name& newValue);
				bool SetAnimIdle(const fight::Name& newValue);
				bool SetAnimWalk(const fight::Name& newValue);
				bool SetAnimRun(const fight::Name& newValue);
				bool SetSyncFrameIdle(float newValue);
				bool SetSyncFrameWalk(float newValue);
				bool SetSyncFrameRun(float newValue);
				bool SetPartition(const fight::Name& newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name animIdle;  // +0x10
					fight::Name animRun;  // +0x18
					fight::Name animWalk;  // +0x20
					fight::Name locomotion;  // +0x28
					fight::Name partition;  // +0x30
					float acceleration;  // +0x38
					float blendInTime;  // +0x3C
					float blendOutTime;  // +0x40
					float phase;  // +0x44
					float smoothSteeringAngle;  // +0x48
					float syncFrameIdle;  // +0x4C
					float syncFrameRun;  // +0x50
					float syncFrameWalk;  // +0x54
					float timeBegin;  // +0x58
					float timeEnd;  // +0x5C
					float turningVelocity;  // +0x60
					float velocityRun;  // +0x64
					float velocityWalk;  // +0x68
					int priority;  // +0x6C
					bool useWorldCoordinates;  // +0x70
					unsigned char unknown71[0x7];
			};

			extern fight::Property** gLocoSteerTrackProperties;
			fight::TrackFactory* CreateLocoSteerTrackFactory(const char* name);
			void RegisterLocoSteerTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::LocoSteerLeanTrack (16 vftable slots, 0xB0 bytes)
			class LocoSteerLeanTrack : public fight::Track
			{
			public:
				// 0x1018B240
				LocoSteerLeanTrack();
				virtual ~LocoSteerLeanTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100EA920, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetAcceleration(float newValue);
				bool SetTurningVelocity(float newValue);
				bool SetVelocityWalk(float newValue);
				bool SetVelocityRun(float newValue);
				bool SetLeanAngleThreshold(float newValue);
				bool SetLeanRateIn(float newValue);
				bool SetLeanRateOut(float newValue);
				bool SetUseWorldCoordinates(bool newValue);
				bool SetPhase(float newValue);
				bool SetLocomotion(const fight::Name& newValue);
				bool SetAnimIdle(const fight::Name& newValue);
				bool SetAnimWalk(const fight::Name& newValue);
				bool SetAnimWalkLeanEast(const fight::Name& newValue);
				bool SetAnimWalkLeanWest(const fight::Name& newValue);
				bool SetAnimRun(const fight::Name& newValue);
				bool SetAnimRunLeanEast(const fight::Name& newValue);
				bool SetAnimRunLeanWest(const fight::Name& newValue);
				bool SetSyncFrameIdle(float newValue);
				bool SetSyncFrameWalk(float newValue);
				bool SetSyncFrameWalkLeanEast(float newValue);
				bool SetSyncFrameWalkLeanWest(float newValue);
				bool SetSyncFrameRun(float newValue);
				bool SetSyncFrameRunLeanEast(float newValue);
				bool SetSyncFrameRunLeanWest(float newValue);
				bool SetPartition(const fight::Name& newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name animIdle;  // +0x10
					fight::Name animRun;  // +0x18
					fight::Name animRunLeanEast;  // +0x20
					fight::Name animRunLeanWest;  // +0x28
					fight::Name animWalk;  // +0x30
					fight::Name animWalkLeanEast;  // +0x38
					fight::Name animWalkLeanWest;  // +0x40
					fight::Name locomotion;  // +0x48
					fight::Name partition;  // +0x50
					float acceleration;  // +0x58
					float blendInTime;  // +0x5C
					float blendOutTime;  // +0x60
					float leanAngleThreshold;  // +0x64
					float leanRateIn;  // +0x68
					float leanRateOut;  // +0x6C
					float phase;  // +0x70
					float syncFrameIdle;  // +0x74
					float syncFrameRun;  // +0x78
					float syncFrameRunLeanEast;  // +0x7C
					float syncFrameRunLeanWest;  // +0x80
					float syncFrameWalk;  // +0x84
					float syncFrameWalkLeanEast;  // +0x88
					float syncFrameWalkLeanWest;  // +0x8C
					float timeBegin;  // +0x90
					float timeEnd;  // +0x94
					float turningVelocity;  // +0x98
					float velocityRun;  // +0x9C
					float velocityWalk;  // +0xA0
					int priority;  // +0xA4
					bool useWorldCoordinates;  // +0xA8
					unsigned char unknownA9[0x7];
			};

			extern fight::Property** gLocoSteerLeanTrackProperties;
			fight::TrackFactory* CreateLocoSteerLeanTrackFactory(const char* name);
			void RegisterLocoSteerLeanTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
