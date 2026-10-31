// Fight items of the motion group: MagneticBootsNextSurfaceNormalCondition, UsingHunterShortRangeCondition, OrientationNormalAngleCondition, MagneticBootsTestDetachTrack, MagneticBootsResetInfoTrack, MagneticBootsJumpTrack, MagneticBootsDetachTrack, MagneticBootsTestCornerTrack, MagneticBootsStickToWallTrack, MagneticBootsTurnCornerTrack, MagneticBootsTrack, MagneticBootsTestJumpStuckTrack, MagneticBootsTestWallTrack (unit 0x1018D500 - 0x10192C50; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_MAGNETICBOOTS_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_MAGNETICBOOTS_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::MagneticBootsNextSurfaceNormalCondition (10 vftable slots, 0x1C bytes)
			class MagneticBootsNextSurfaceNormalCondition : public fight::Condition
			{
			public:
				// 0x1018DF20
				MagneticBootsNextSurfaceNormalCondition();
				virtual ~MagneticBootsNextSurfaceNormalCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100ECC70, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetNormal(const math::Vector& newValue);
				bool SetArc(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Vector normal;  // +0xC
					float arc;  // +0x18
			};

			extern fight::Property** gMagneticBootsNextSurfaceNormalConditionProperties;
			fight::ConditionFactory* CreateMagneticBootsNextSurfaceNormalConditionFactory(const char* name);
			void RegisterMagneticBootsNextSurfaceNormalConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::UsingHunterShortRangeCondition (10 vftable slots, 0x10 bytes)
			class UsingHunterShortRangeCondition : public fight::Condition
			{
			public:
				// 0x1018DFA0
				UsingHunterShortRangeCondition();
				virtual ~UsingHunterShortRangeCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100EDE90, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetUsing(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool usingValue;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gUsingHunterShortRangeConditionProperties;
			fight::ConditionFactory* CreateUsingHunterShortRangeConditionFactory(const char* name);
			void RegisterUsingHunterShortRangeConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::OrientationNormalAngleCondition (10 vftable slots, 0x20 bytes)
			class OrientationNormalAngleCondition : public fight::Condition
			{
			public:
				// 0x1018E000
				OrientationNormalAngleCondition();
				virtual ~OrientationNormalAngleCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100EDF40, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetNormal(const math::Vector& newValue);
				bool SetCompare(int newValue);
				bool SetAngle(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Vector normal;  // +0xC
					float angle;  // +0x18
					int compare;  // +0x1C
			};

			extern fight::Property** gOrientationNormalAngleConditionProperties;
			fight::ConditionFactory* CreateOrientationNormalAngleConditionFactory(const char* name);
			void RegisterOrientationNormalAngleConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::MagneticBootsTestDetachTrack (16 vftable slots, 0x4C bytes)
			class MagneticBootsTestDetachTrack : public fight::Track
			{
			public:
				// 0x1018E090
				MagneticBootsTestDetachTrack();
				virtual ~MagneticBootsTestDetachTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100F5260, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetThresoldAngle(float newValue);
				bool SetDebugDraw(bool newValue);
				fight::BranchHolder* SetBranch();
				bool SetPriority(int newValue);
				fight::ConditionList* SetConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder branch;  // +0x10
					fight::ConditionList conditions;  // +0x34
					float thresoldAngle;  // +0x38
					float timeBegin;  // +0x3C
					float timeEnd;  // +0x40
					int priority;  // +0x44
					bool debugDraw;  // +0x48
					unsigned char unknown49[0x3];
			};

			extern fight::Property** gMagneticBootsTestDetachTrackProperties;
			fight::TrackFactory* CreateMagneticBootsTestDetachTrackFactory(const char* name);
			void RegisterMagneticBootsTestDetachTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::MagneticBootsResetInfoTrack (16 vftable slots, 0x18 bytes)
			class MagneticBootsResetInfoTrack : public fight::Track
			{
			public:
				// 0x1018E180
				MagneticBootsResetInfoTrack();
				virtual ~MagneticBootsResetInfoTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100F5620, another unit)
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

			extern fight::Property** gMagneticBootsResetInfoTrackProperties;
			fight::TrackFactory* CreateMagneticBootsResetInfoTrackFactory(const char* name);
			void RegisterMagneticBootsResetInfoTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::MagneticBootsJumpTrack (16 vftable slots, 0x34 bytes)
			class MagneticBootsJumpTrack : public fight::Track
			{
			public:
				// 0x1018E220
				MagneticBootsJumpTrack();
				virtual ~MagneticBootsJumpTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100F5670, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetFlightTime(float newValue);
				bool SetUpDistance(float newValue);
				bool SetForwardDistance(float newValue);
				bool SetMaxFallSpeed(float newValue);
				bool SetChoreoPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float blendInTime;  // +0x10
					float blendOutTime;  // +0x14
					float flightTime;  // +0x18
					float forwardDistance;  // +0x1C
					float maxFallSpeed;  // +0x20
					float timeBegin;  // +0x24
					float timeEnd;  // +0x28
					float upDistance;  // +0x2C
					int choreoPriority;  // +0x30
			};

			extern fight::Property** gMagneticBootsJumpTrackProperties;
			fight::TrackFactory* CreateMagneticBootsJumpTrackFactory(const char* name);
			void RegisterMagneticBootsJumpTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::MagneticBootsDetachTrack (16 vftable slots, 0x30 bytes)
			class MagneticBootsDetachTrack : public fight::Track
			{
			public:
				// 0x1018E300
				MagneticBootsDetachTrack();
				virtual ~MagneticBootsDetachTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100F55B0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetTime(float newValue);
				bool SetSeparation(float newValue);
				bool SetChoreoPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);
				bool SetDebugDraw(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float blendInTime;  // +0x10
					float blendOutTime;  // +0x14
					float separation;  // +0x18
					float time;  // +0x1C
					float timeBegin;  // +0x20
					float timeEnd;  // +0x24
					int choreoPriority;  // +0x28
					bool debugDraw;  // +0x2C
					unsigned char unknown2D[0x3];
			};

			extern fight::Property** gMagneticBootsDetachTrackProperties;
			fight::TrackFactory* CreateMagneticBootsDetachTrackFactory(const char* name);
			void RegisterMagneticBootsDetachTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::MagneticBootsTestCornerTrack (16 vftable slots, 0x58 bytes)
			class MagneticBootsTestCornerTrack : public fight::Track
			{
			public:
				// 0x1018E3D0
				MagneticBootsTestCornerTrack();
				virtual ~MagneticBootsTestCornerTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100F4DC0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetLookAhead(float newValue);
				bool SetCornerDepth(float newValue);
				bool SetCornerLookBack(float newValue);
				bool SetCollideWith(int newValue);
				bool SetDebugDraw(bool newValue);
				fight::BranchHolder* SetBranch();
				bool SetPriority(int newValue);
				fight::ConditionList* SetConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder branch;  // +0x10
					fight::ConditionList conditions;  // +0x34
					float cornerDepth;  // +0x38
					float cornerLookBack;  // +0x3C
					float lookAhead;  // +0x40
					float timeBegin;  // +0x44
					float timeEnd;  // +0x48
					int priority;  // +0x4C
					int collideWith;  // +0x50
					bool debugDraw;  // +0x54
					unsigned char unknown55[0x3];
			};

			extern fight::Property** gMagneticBootsTestCornerTrackProperties;
			fight::TrackFactory* CreateMagneticBootsTestCornerTrackFactory(const char* name);
			void RegisterMagneticBootsTestCornerTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::MagneticBootsStickToWallTrack (16 vftable slots, 0x3C bytes)
			class MagneticBootsStickToWallTrack : public fight::Track
			{
			public:
				// 0x1018E4E0
				MagneticBootsStickToWallTrack();
				virtual ~MagneticBootsStickToWallTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100F5540, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetSpeed(float newValue);
				bool SetAcceleration(float newValue);
				bool SetBeginTurn(float newValue);
				bool SetEndTurn(float newValue);
				bool SetVerticalOffset(float newValue);
				bool SetChoreoPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);
				bool SetDebugDraw(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float acceleration;  // +0x10
					float beginTurn;  // +0x14
					float blendInTime;  // +0x18
					float blendOutTime;  // +0x1C
					float endTurn;  // +0x20
					float speed;  // +0x24
					float timeBegin;  // +0x28
					float timeEnd;  // +0x2C
					float verticalOffset;  // +0x30
					int choreoPriority;  // +0x34
					bool debugDraw;  // +0x38
					unsigned char unknown39[0x3];
			};

			extern fight::Property** gMagneticBootsStickToWallTrackProperties;
			fight::TrackFactory* CreateMagneticBootsStickToWallTrackFactory(const char* name);
			void RegisterMagneticBootsStickToWallTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::MagneticBootsTurnCornerTrack (16 vftable slots, 0x38 bytes)
			class MagneticBootsTurnCornerTrack : public fight::Track
			{
			public:
				// 0x1018E5C0
				MagneticBootsTurnCornerTrack();
				virtual ~MagneticBootsTurnCornerTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100F54D0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetSpeed(float newValue);
				bool SetAcceleration(float newValue);
				bool SetBeginTurn(float newValue);
				bool SetEndTurn(float newValue);
				bool SetChoreoPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);
				bool SetDebugDraw(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float acceleration;  // +0x10
					float beginTurn;  // +0x14
					float blendInTime;  // +0x18
					float blendOutTime;  // +0x1C
					float endTurn;  // +0x20
					float speed;  // +0x24
					float timeBegin;  // +0x28
					float timeEnd;  // +0x2C
					int choreoPriority;  // +0x30
					bool debugDraw;  // +0x34
					unsigned char unknown35[0x3];
			};

			extern fight::Property** gMagneticBootsTurnCornerTrackProperties;
			fight::TrackFactory* CreateMagneticBootsTurnCornerTrackFactory(const char* name);
			void RegisterMagneticBootsTurnCornerTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::MagneticBootsTrack (16 vftable slots, 0x70 bytes)
			class MagneticBootsTrack : public fight::Track
			{
			public:
				// 0x1018EB10
				MagneticBootsTrack();
				virtual ~MagneticBootsTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100F4C60, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetAcceleration(float newValue);
				bool SetTurningVelocity(float newValue);
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
					float phase;  // +0x44
					float syncFrameIdle;  // +0x48
					float syncFrameRun;  // +0x4C
					float syncFrameWalk;  // +0x50
					float timeBegin;  // +0x54
					float timeEnd;  // +0x58
					float turningVelocity;  // +0x5C
					float velocityRun;  // +0x60
					float velocityWalk;  // +0x64
					int priority;  // +0x68
					bool debugDraw;  // +0x6C
					unsigned char unknown6D[0x3];
			};

			extern fight::Property** gMagneticBootsTrackProperties;
			fight::TrackFactory* CreateMagneticBootsTrackFactory(const char* name);
			void RegisterMagneticBootsTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::MagneticBootsTestJumpStuckTrack (16 vftable slots, 0x48 bytes)
			class MagneticBootsTestJumpStuckTrack : public fight::Track
			{
			public:
				// 0x1018E6C0
				MagneticBootsTestJumpStuckTrack();
				virtual ~MagneticBootsTestJumpStuckTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100F4EC0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetUseFacing(bool newValue);
				fight::BranchHolder* SetBranch();
				bool SetPriority(int newValue);
				fight::ConditionList* SetConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder branch;  // +0x10
					fight::ConditionList conditions;  // +0x34
					float timeBegin;  // +0x38
					float timeEnd;  // +0x3C
					int priority;  // +0x40
					bool useFacing;  // +0x44
					unsigned char unknown45[0x3];
			};

			extern fight::Property** gMagneticBootsTestJumpStuckTrackProperties;
			fight::TrackFactory* CreateMagneticBootsTestJumpStuckTrackFactory(const char* name);
			void RegisterMagneticBootsTestJumpStuckTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::MagneticBootsTestWallTrack (16 vftable slots, 0x60 bytes)
			class MagneticBootsTestWallTrack : public fight::Track
			{
			public:
				// 0x1018E7A0
				MagneticBootsTestWallTrack();
				virtual ~MagneticBootsTestWallTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100F4CC0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetOffset(const math::Vector& newValue);
				bool SetYawOffset(float newValue);
				bool SetLength(float newValue);
				bool SetCollideWith(int newValue);
				bool SetUseFacing(bool newValue);
				bool SetUseBackwardsFacing(bool newValue);
				bool SetDebugDraw(bool newValue);
				fight::BranchHolder* SetBranch();
				bool SetPriority(int newValue);
				fight::ConditionList* SetConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder branch;  // +0x10
					math::Vector offset;  // +0x34
					fight::ConditionList conditions;  // +0x40
					float length;  // +0x44
					float timeBegin;  // +0x48
					float timeEnd;  // +0x4C
					float yawOffset;  // +0x50
					int priority;  // +0x54
					int collideWith;  // +0x58
					bool debugDraw;  // +0x5C
					bool useBackwardsFacing;  // +0x5D
					bool useFacing;  // +0x5E
					unsigned char unknown5F[0x1];
			};

			extern fight::Property** gMagneticBootsTestWallTrackProperties;
			fight::TrackFactory* CreateMagneticBootsTestWallTrackFactory(const char* name);
			void RegisterMagneticBootsTestWallTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
