// Fight items of the motion group: CrowdMinDistanceCondition, CrowdPositionCondition, LocoCrowdTrack, CrowdTestTrack (unit 0x1014F4D0 - 0x10151930; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_CROWD_H
#define PROTO_FIGHTITEMS_MOTION_CROWD_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::CrowdMinDistanceCondition (10 vftable slots, 0x14 bytes)
			class CrowdMinDistanceCondition : public fight::Condition
			{
			public:
				// 0x1014F9E0
				CrowdMinDistanceCondition();
				virtual ~CrowdMinDistanceCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100ADB90, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetDistance(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float distance;  // +0xC
					int compare;  // +0x10
			};

			extern fight::Property** gCrowdMinDistanceConditionProperties;
			fight::ConditionFactory* CreateCrowdMinDistanceConditionFactory(const char* name);
			void RegisterCrowdMinDistanceConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::CrowdPositionCondition (10 vftable slots, 0x18 bytes)
			class CrowdPositionCondition : public fight::Condition
			{
			public:
				// 0x1014FA50
				CrowdPositionCondition();
				virtual ~CrowdPositionCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100AE6C0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetDirection(int newValue);
				bool SetCompare(int newValue);
				bool SetPosition(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float position;  // +0xC
					int compare;  // +0x10
					int direction;  // +0x14
			};

			extern fight::Property** gCrowdPositionConditionProperties;
			fight::ConditionFactory* CreateCrowdPositionConditionFactory(const char* name);
			void RegisterCrowdPositionConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::LocoCrowdTrack (16 vftable slots, 0x100 bytes)
			class LocoCrowdTrack : public fight::Track
			{
			public:
				// 0x1014FD80
				LocoCrowdTrack();
				virtual ~LocoCrowdTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100AFB90, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetAcceleration(float newValue);
				bool SetTurningVelocity(float newValue);
				bool SetTwistRateOn(float newValue);
				bool SetTwistRateOff(float newValue);
				bool SetVelocityWalk(float newValue);
				bool SetVelocityRun(float newValue);
				bool SetSmoothSteeringAngle(float newValue);
				bool SetPhase(float newValue);
				bool SetLocomotion(const fight::Name& newValue);
				bool SetAnimIdle(const fight::Name& newValue);
				bool SetAnimIdleTwistLeft(const fight::Name& newValue);
				bool SetAnimIdleTwistRight(const fight::Name& newValue);
				bool SetAnimWalk(const fight::Name& newValue);
				bool SetAnimWalkTwistLeft(const fight::Name& newValue);
				bool SetAnimWalkTwistRight(const fight::Name& newValue);
				bool SetAnimRun(const fight::Name& newValue);
				bool SetAnimRunTwistLeft(const fight::Name& newValue);
				bool SetAnimRunTwistRight(const fight::Name& newValue);
				bool SetSyncFrameIdle(float newValue);
				bool SetSyncFrameIdleTwistLeft(float newValue);
				bool SetSyncFrameIdleTwistRight(float newValue);
				bool SetSyncFrameWalk(float newValue);
				bool SetSyncFrameWalkTwistLeft(float newValue);
				bool SetSyncFrameWalkTwistRight(float newValue);
				bool SetSyncFrameRun(float newValue);
				bool SetSyncFrameRunTwistLeft(float newValue);
				bool SetSyncFrameRunTwistRight(float newValue);
				bool SetPartition(const fight::Name& newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);
				bool SetRadiusMin(float newValue);
				bool SetRadiusMax(float newValue);
				bool SetOffsetMax(float newValue);
				fight::BranchHolder* SetBranch();
				bool SetInterruptPriority(int newValue);
				fight::ConditionList* SetConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder branch;  // +0x10
					unsigned char unknown34[0x4];
					fight::Name animIdle;  // +0x38
					fight::Name animIdleTwistLeft;  // +0x40
					fight::Name animIdleTwistRight;  // +0x48
					fight::Name animRun;  // +0x50
					fight::Name animRunTwistLeft;  // +0x58
					fight::Name animRunTwistRight;  // +0x60
					fight::Name animWalk;  // +0x68
					fight::Name animWalkTwistLeft;  // +0x70
					fight::Name animWalkTwistRight;  // +0x78
					fight::Name locomotion;  // +0x80
					fight::Name partition;  // +0x88
					fight::ConditionList conditions;  // +0x90
					float acceleration;  // +0x94
					float blendInTime;  // +0x98
					float blendOutTime;  // +0x9C
					float offsetMax;  // +0xA0
					float phase;  // +0xA4
					float radiusMax;  // +0xA8
					float radiusMin;  // +0xAC
					float smoothSteeringAngle;  // +0xB0
					float syncFrameIdle;  // +0xB4
					float syncFrameIdleTwistLeft;  // +0xB8
					float syncFrameIdleTwistRight;  // +0xBC
					float syncFrameRun;  // +0xC0
					float syncFrameRunTwistLeft;  // +0xC4
					float syncFrameRunTwistRight;  // +0xC8
					float syncFrameWalk;  // +0xCC
					float syncFrameWalkTwistLeft;  // +0xD0
					float syncFrameWalkTwistRight;  // +0xD4
					float timeBegin;  // +0xD8
					float timeEnd;  // +0xDC
					float turningVelocity;  // +0xE0
					float twistRateOff;  // +0xE4
					float twistRateOn;  // +0xE8
					float velocityRun;  // +0xEC
					float velocityWalk;  // +0xF0
					int interruptPriority;  // +0xF4
					int priority;  // +0xF8
					unsigned char unknownFC[0x4];
			};

			extern fight::Property** gLocoCrowdTrackProperties;
			fight::TrackFactory* CreateLocoCrowdTrackFactory(const char* name);
			void RegisterLocoCrowdTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::CrowdTestTrack (16 vftable slots, 0x54 bytes)
			class CrowdTestTrack : public fight::Track
			{
			public:
				// 0x1014FB00
				CrowdTestTrack();
				virtual ~CrowdTestTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100AFB30, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetVelocityCap(float newValue);
				bool SetRadiusMin(float newValue);
				bool SetRadiusMax(float newValue);
				bool SetOffsetMax(float newValue);
				fight::BranchHolder* SetBranch();
				bool SetPriority(int newValue);
				fight::ConditionList* SetConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder branch;  // +0x10
					fight::ConditionList conditions;  // +0x34
					float offsetMax;  // +0x38
					float radiusMax;  // +0x3C
					float radiusMin;  // +0x40
					float timeBegin;  // +0x44
					float timeEnd;  // +0x48
					float velocityCap;  // +0x4C
					int priority;  // +0x50
			};

			extern fight::Property** gCrowdTestTrackProperties;
			fight::TrackFactory* CreateCrowdTestTrackFactory(const char* name);
			void RegisterCrowdTestTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin

			// ---- actions end
		}
	}
}

#endif
