// Fight items of the motion group: HunterOnWallCondition, HunterCanHopAroundCornerCondition, HunterShortRangeLocoTrack, HunterShortRangeHopCornerTrack, HunterShortRangeCorner2Track, HunterLandedTrack (unit 0x1017D680 - 0x10180090; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_HUNTER_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_HUNTER_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::HunterOnWallCondition (10 vftable slots, 0x10 bytes)
			class HunterOnWallCondition : public fight::Condition
			{
			public:
				// 0x1017DC10
				HunterOnWallCondition();
				virtual ~HunterOnWallCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100D7CC0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetAngleThreshold(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float angleThreshold;  // +0xC
			};

			extern fight::Property** gHunterOnWallConditionProperties;
			fight::ConditionFactory* CreateHunterOnWallConditionFactory(const char* name);
			void RegisterHunterOnWallConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::HunterCanHopAroundCornerCondition (10 vftable slots, 0xC bytes)
			class HunterCanHopAroundCornerCondition : public fight::Condition
			{
			public:
				// 0x1017DCE0
				HunterCanHopAroundCornerCondition();
				virtual ~HunterCanHopAroundCornerCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100D7E30, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

			};

			extern fight::Property** gHunterCanHopAroundCornerConditionProperties;
			fight::ConditionFactory* CreateHunterCanHopAroundCornerConditionFactory(const char* name);
			void RegisterHunterCanHopAroundCornerConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::HunterShortRangeLocoTrack (16 vftable slots, 0xA8 bytes)
			class HunterShortRangeLocoTrack : public fight::Track
			{
			public:
				// 0x1017E000
				HunterShortRangeLocoTrack();
				virtual ~HunterShortRangeLocoTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100D96D0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetAcceleration(float newValue);
				bool SetTurningVelocity(float newValue);
				bool SetCorneringTime(float newValue);
				bool SetVelocityWalk(float newValue);
				bool SetVelocityRun(float newValue);
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
				bool SetDebugDraw(bool newValue);
				fight::BranchHolder* SetOnCorner();
				bool SetOnCornerPriority(int newValue);
				fight::ConditionList* SetOnCornerConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder onCorner;  // +0x10
					unsigned char unknown34[0x4];
					fight::Name animIdle;  // +0x38
					fight::Name animRun;  // +0x40
					fight::Name animWalk;  // +0x48
					fight::Name locomotion;  // +0x50
					fight::Name partition;  // +0x58
					fight::ConditionList onCornerConditions;  // +0x60
					float acceleration;  // +0x64
					float blendInTime;  // +0x68
					float blendOutTime;  // +0x6C
					float corneringTime;  // +0x70
					float phase;  // +0x74
					float syncFrameIdle;  // +0x78
					float syncFrameRun;  // +0x7C
					float syncFrameWalk;  // +0x80
					float timeBegin;  // +0x84
					float timeEnd;  // +0x88
					float turningVelocity;  // +0x8C
					float velocityRun;  // +0x90
					float velocityWalk;  // +0x94
					int onCornerPriority;  // +0x98
					int priority;  // +0x9C
					bool debugDraw;  // +0xA0
					unsigned char unknownA1[0x7];
			};

			extern fight::Property** gHunterShortRangeLocoTrackProperties;
			fight::TrackFactory* CreateHunterShortRangeLocoTrackFactory(const char* name);
			void RegisterHunterShortRangeLocoTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::HunterShortRangeHopCornerTrack (16 vftable slots, 0x40 bytes)
			class HunterShortRangeHopCornerTrack : public fight::Track
			{
			public:
				// 0x1017E170
				HunterShortRangeHopCornerTrack();
				virtual ~HunterShortRangeHopCornerTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100DA1D0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetVelocityRunUp(float newValue);
				bool SetVelocityHorizontal(float newValue);
				bool SetGravity(float newValue);
				bool SetOrientationBlendTime(float newValue);
				bool SetMaxFallSpeed(float newValue);
				bool SetNewSupportingLimb(const fight::Name& newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name newSupportingLimb;  // +0x10
					float blendInTime;  // +0x18
					float blendOutTime;  // +0x1C
					float gravity;  // +0x20
					float maxFallSpeed;  // +0x24
					float orientationBlendTime;  // +0x28
					float timeBegin;  // +0x2C
					float timeEnd;  // +0x30
					float velocityHorizontal;  // +0x34
					float velocityRunUp;  // +0x38
					int priority;  // +0x3C
			};

			extern fight::Property** gHunterShortRangeHopCornerTrackProperties;
			fight::TrackFactory* CreateHunterShortRangeHopCornerTrackFactory(const char* name);
			void RegisterHunterShortRangeHopCornerTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::HunterShortRangeCorner2Track (16 vftable slots, 0x70 bytes)
			class HunterShortRangeCorner2Track : public fight::Track
			{
			public:
				// 0x1017E250
				HunterShortRangeCorner2Track();
				virtual ~HunterShortRangeCorner2Track();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100DA670, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetAcceleration(float newValue);
				bool SetCorneringTime(float newValue);
				bool SetVelocityWalk(float newValue);
				bool SetVelocityRun(float newValue);
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
				bool SetDebugDraw(bool newValue);

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
					float corneringTime;  // +0x44
					float phase;  // +0x48
					float syncFrameIdle;  // +0x4C
					float syncFrameRun;  // +0x50
					float syncFrameWalk;  // +0x54
					float timeBegin;  // +0x58
					float timeEnd;  // +0x5C
					float velocityRun;  // +0x60
					float velocityWalk;  // +0x64
					int priority;  // +0x68
					bool debugDraw;  // +0x6C
					unsigned char unknown6D[0x3];
			};

			extern fight::Property** gHunterShortRangeCorner2TrackProperties;
			fight::TrackFactory* CreateHunterShortRangeCorner2TrackFactory(const char* name);
			void RegisterHunterShortRangeCorner2TrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::HunterLandedTrack (16 vftable slots, 0x18 bytes)
			class HunterLandedTrack : public fight::Track
			{
			public:
				// 0x1017DDD0
				HunterLandedTrack();
				virtual ~HunterLandedTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100DA6E0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
			};

			extern fight::Property** gHunterLandedTrackProperties;
			fight::TrackFactory* CreateHunterLandedTrackFactory(const char* name);
			void RegisterHunterLandedTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
