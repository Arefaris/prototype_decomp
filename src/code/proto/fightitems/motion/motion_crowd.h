// Fight items of the motion group: CrowdMinDistanceCondition, CrowdPositionCondition, LocoCrowdTrack, CrowdTestTrack (unit 0x1014F4D0 - 0x10151930; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_CROWD_H
#define PROTO_FIGHTITEMS_MOTION_CROWD_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"
#include "code/proto/fightitems/motion/motionreaction2.h"
#include "code/engine/fight/effecttrack.h"

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

				// Getters of the members (the engine keeps their copies)
				int GetCompare() const;
				float GetDistance() const;

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

				// Getters of the members (the engine keeps their copies)
				int GetDirection() const;
				int GetCompare() const;
				float GetPosition() const;

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

				// Getters of the members (the engine keeps their copies)
				float GetAcceleration() const;
				float GetTurningVelocity() const;
				float GetTwistRateOn() const;
				float GetTwistRateOff() const;
				float GetVelocityWalk() const;
				float GetVelocityRun() const;
				float GetSmoothSteeringAngle() const;
				float GetPhase() const;
				const fight::Name& GetLocomotion() const;
				const fight::Name& GetAnimIdle() const;
				const fight::Name& GetAnimIdleTwistLeft() const;
				const fight::Name& GetAnimIdleTwistRight() const;
				const fight::Name& GetAnimWalk() const;
				const fight::Name& GetAnimWalkTwistLeft() const;
				const fight::Name& GetAnimWalkTwistRight() const;
				const fight::Name& GetAnimRun() const;
				const fight::Name& GetAnimRunTwistLeft() const;
				const fight::Name& GetAnimRunTwistRight() const;
				float GetSyncFrameIdle() const;
				float GetSyncFrameIdleTwistLeft() const;
				float GetSyncFrameIdleTwistRight() const;
				float GetSyncFrameWalk() const;
				float GetSyncFrameWalkTwistLeft() const;
				float GetSyncFrameWalkTwistRight() const;
				float GetSyncFrameRun() const;
				float GetSyncFrameRunTwistLeft() const;
				float GetSyncFrameRunTwistRight() const;
				const fight::Name& GetPartition() const;
				int GetPriority() const;
				float GetBlendInTime() const;
				float GetBlendOutTime() const;
				float GetRadiusMin() const;
				float GetRadiusMax() const;
				float GetOffsetMax() const;
				const fight::BranchHolder& GetBranch() const;

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

				// Getters of the members (the engine keeps their copies)
				float GetVelocityCap() const;
				float GetRadiusMin() const;
				float GetRadiusMax() const;
				float GetOffsetMax() const;
				const fight::BranchHolder& GetBranch() const;
				int GetPriority() const;

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
			// The reaction event of kind 0x21008 (name guess) the crowd conditions read: the object it concerns, its position and a distance
			struct CrowdHitEvent : ReactionEvent
			{
				unsigned char unknown10[0x8];
				math::Vector position;  // +0x18
				float distance;  // +0x24
			};

			// RTTI: proto::fightitems::motion::CrowdTestBaseAction (9 vftable slots, 0x3C bytes)
			class CrowdTestBaseAction : public fight::Action
			{
			public:
				// 0x100ADAF0
				CrowdTestBaseAction(fight::Track* listener, core::IRefCount* newEffect, engine::GameObjectHandle newTarget);
				// 0x100ADB60
				virtual ~CrowdTestBaseAction();

				// vftable slot 5 (0x100ADD20)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x100AD980)
				virtual void Slot6();

				engine::GameObjectHandle target;  // +0x1C
				engine::TrackWatch watch;  // +0x20
				core::IRefCount* effect;  // +0x2C
				math::Vector position;  // +0x30
			};

			// RTTI: proto::fightitems::motion::CrowdTestAction (9 vftable slots, 0x48 bytes)
			class CrowdTestAction : public CrowdTestBaseAction
			{
			public:
				// 0x100AE890
				CrowdTestAction(CrowdTestTrack* newTrack, fight::Track* listener, core::IRefCount* newEffect, engine::GameObjectHandle newTarget);
				// 0x100AE5C0
				virtual ~CrowdTestAction();

				// vftable slot 7 (0x100AE930)
				virtual bool Slot7(int arg, float value);

				core::Link<CrowdTestTrack> link;  // +0x3C
			};

			// RTTI: proto::fightitems::motion::LocoCrowdAction (9 vftable slots, 0x54 bytes)
			class LocoCrowdAction : public CrowdTestBaseAction
			{
			public:
				// 0x100AEA40
				LocoCrowdAction(LocoCrowdTrack* newTrack, fight::Track* listener, core::IRefCount* newEffect, engine::GameObjectHandle newTarget);
				// 0x100AE610
				virtual ~LocoCrowdAction();

				// vftable slot 5 (0x100AEAE0)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x100AE650)
				virtual void Slot6();
				// vftable slot 7 (0x100AF2E0)
				virtual bool Slot7(int arg, float value);

				core::Link<LocoCrowdTrack> link;  // +0x3C
				choreo::Driver* driver;  // +0x48
				unsigned char unknown4C[0x8];
			};


			// ---- actions end
		}
	}
}

#endif
