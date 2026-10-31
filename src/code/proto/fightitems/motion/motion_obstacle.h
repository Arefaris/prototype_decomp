// Fight items of the motion group: ObstacleDistanceCondition, ObstacleTimeToObstacleCondition, ObstacleSlopeCondition, ObstacleFaceHeightSlopeCondition, ObstacleFaceHeightCondition, ObstacleColliderTypeCondition, ObstacleVelocityCondition, ObstacleLengthCondition, ObstacleWidthCondition, ObstacleHeightCondition, ObstacleAvoidExitTrack, ObstacleAvoidTrack, PushFromObstacleTrack, ObstacleTestTrack (unit 0x10193D60 - 0x10198800; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_OBSTACLE_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_OBSTACLE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::ObstacleDistanceCondition (10 vftable slots, 0x14 bytes)
			class ObstacleDistanceCondition : public fight::Condition
			{
			public:
				// 0x101944A0
				ObstacleDistanceCondition();
				virtual ~ObstacleDistanceCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100F8D30, another unit)
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

			extern fight::Property** gObstacleDistanceConditionProperties;
			fight::ConditionFactory* CreateObstacleDistanceConditionFactory(const char* name);
			void RegisterObstacleDistanceConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ObstacleTimeToObstacleCondition (10 vftable slots, 0x14 bytes)
			class ObstacleTimeToObstacleCondition : public fight::Condition
			{
			public:
				// 0x10194510
				ObstacleTimeToObstacleCondition();
				virtual ~ObstacleTimeToObstacleCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100F8F50, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float time;  // +0xC
					int compare;  // +0x10
			};

			extern fight::Property** gObstacleTimeToObstacleConditionProperties;
			fight::ConditionFactory* CreateObstacleTimeToObstacleConditionFactory(const char* name);
			void RegisterObstacleTimeToObstacleConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ObstacleSlopeCondition (10 vftable slots, 0x14 bytes)
			class ObstacleSlopeCondition : public fight::Condition
			{
			public:
				// 0x10194580
				ObstacleSlopeCondition();
				virtual ~ObstacleSlopeCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100F9500, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetSlope(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float slope;  // +0xC
					int compare;  // +0x10
			};

			extern fight::Property** gObstacleSlopeConditionProperties;
			fight::ConditionFactory* CreateObstacleSlopeConditionFactory(const char* name);
			void RegisterObstacleSlopeConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ObstacleFaceHeightSlopeCondition (10 vftable slots, 0x18 bytes)
			class ObstacleFaceHeightSlopeCondition : public fight::Condition
			{
			public:
				// 0x101945F0
				ObstacleFaceHeightSlopeCondition();
				virtual ~ObstacleFaceHeightSlopeCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100F95A0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetFaceHeightMin(float newValue);
				bool SetHeightMax(float newValue);
				bool SetSlopeMax(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float faceHeightMin;  // +0xC
					float heightMax;  // +0x10
					float slopeMax;  // +0x14
			};

			extern fight::Property** gObstacleFaceHeightSlopeConditionProperties;
			fight::ConditionFactory* CreateObstacleFaceHeightSlopeConditionFactory(const char* name);
			void RegisterObstacleFaceHeightSlopeConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ObstacleFaceHeightCondition (10 vftable slots, 0x14 bytes)
			class ObstacleFaceHeightCondition : public fight::Condition
			{
			public:
				// 0x10194680
				ObstacleFaceHeightCondition();
				virtual ~ObstacleFaceHeightCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100F93C0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetHeight(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float height;  // +0xC
					int compare;  // +0x10
			};

			extern fight::Property** gObstacleFaceHeightConditionProperties;
			fight::ConditionFactory* CreateObstacleFaceHeightConditionFactory(const char* name);
			void RegisterObstacleFaceHeightConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ObstacleColliderTypeCondition (10 vftable slots, 0x14 bytes)
			class ObstacleColliderTypeCondition : public fight::Condition
			{
			public:
				// 0x101946F0
				ObstacleColliderTypeCondition();
				virtual ~ObstacleColliderTypeCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100F97B0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetColliderType(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int compare;  // +0xC
					int colliderType;  // +0x10
			};

			extern fight::Property** gObstacleColliderTypeConditionProperties;
			fight::ConditionFactory* CreateObstacleColliderTypeConditionFactory(const char* name);
			void RegisterObstacleColliderTypeConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ObstacleVelocityCondition (10 vftable slots, 0x18 bytes)
			class ObstacleVelocityCondition : public fight::Condition
			{
			public:
				// 0x10194760
				ObstacleVelocityCondition();
				virtual ~ObstacleVelocityCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100F8EB0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetDirection(int newValue);
				bool SetCompare(int newValue);
				bool SetVelocity(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float velocity;  // +0xC
					int compare;  // +0x10
					int direction;  // +0x14
			};

			extern fight::Property** gObstacleVelocityConditionProperties;
			fight::ConditionFactory* CreateObstacleVelocityConditionFactory(const char* name);
			void RegisterObstacleVelocityConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ObstacleLengthCondition (10 vftable slots, 0x14 bytes)
			class ObstacleLengthCondition : public fight::Condition
			{
			public:
				// 0x101947E0
				ObstacleLengthCondition();
				virtual ~ObstacleLengthCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100F9280, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetLength(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float length;  // +0xC
					int compare;  // +0x10
			};

			extern fight::Property** gObstacleLengthConditionProperties;
			fight::ConditionFactory* CreateObstacleLengthConditionFactory(const char* name);
			void RegisterObstacleLengthConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ObstacleWidthCondition (10 vftable slots, 0x14 bytes)
			class ObstacleWidthCondition : public fight::Condition
			{
			public:
				// 0x10194850
				ObstacleWidthCondition();
				virtual ~ObstacleWidthCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100F9320, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetWidth(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float width;  // +0xC
					int compare;  // +0x10
			};

			extern fight::Property** gObstacleWidthConditionProperties;
			fight::ConditionFactory* CreateObstacleWidthConditionFactory(const char* name);
			void RegisterObstacleWidthConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ObstacleHeightCondition (10 vftable slots, 0x14 bytes)
			class ObstacleHeightCondition : public fight::Condition
			{
			public:
				// 0x101948C0
				ObstacleHeightCondition();
				virtual ~ObstacleHeightCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100F9140, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetHeight(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float height;  // +0xC
					int compare;  // +0x10
			};

			extern fight::Property** gObstacleHeightConditionProperties;
			fight::ConditionFactory* CreateObstacleHeightConditionFactory(const char* name);
			void RegisterObstacleHeightConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ObstacleAvoidExitTrack (16 vftable slots, 0x30 bytes)
			class ObstacleAvoidExitTrack : public fight::Track
			{
			public:
				// 0x10194930
				ObstacleAvoidExitTrack();
				virtual ~ObstacleAvoidExitTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100FCDF0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetTangentDistance(float newValue);
				bool SetNormalDistance(float newValue);
				bool SetTurningRate(float newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float blendInTime;  // +0x10
					float blendOutTime;  // +0x14
					float normalDistance;  // +0x18
					float tangentDistance;  // +0x1C
					float timeBegin;  // +0x20
					float timeEnd;  // +0x24
					float turningRate;  // +0x28
					int priority;  // +0x2C
			};

			extern fight::Property** gObstacleAvoidExitTrackProperties;
			fight::TrackFactory* CreateObstacleAvoidExitTrackFactory(const char* name);
			void RegisterObstacleAvoidExitTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ObstacleAvoidTrack (16 vftable slots, 0x48 bytes)
			class ObstacleAvoidTrack : public fight::Track
			{
			public:
				// 0x10194A00
				ObstacleAvoidTrack();
				virtual ~ObstacleAvoidTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100FD5C0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetHeightMin(float newValue);
				bool SetUpVelocityMax(float newValue);
				bool SetForwardVelocityMin(float newValue);
				bool SetForwardVelocityMax(float newValue);
				bool SetTurnVelocityMin(float newValue);
				bool SetTurnVelocityMax(float newValue);
				bool SetTurnAccelerationMin(float newValue);
				bool SetTurnAccelerationMax(float newValue);
				bool SetPoleAvoidVelocity(float newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float blendInTime;  // +0x10
					float blendOutTime;  // +0x14
					float forwardVelocityMax;  // +0x18
					float forwardVelocityMin;  // +0x1C
					float heightMin;  // +0x20
					float poleAvoidVelocity;  // +0x24
					float timeBegin;  // +0x28
					float timeEnd;  // +0x2C
					float turnAccelerationMax;  // +0x30
					float turnAccelerationMin;  // +0x34
					float turnVelocityMax;  // +0x38
					float turnVelocityMin;  // +0x3C
					float upVelocityMax;  // +0x40
					int priority;  // +0x44
			};

			extern fight::Property** gObstacleAvoidTrackProperties;
			fight::TrackFactory* CreateObstacleAvoidTrackFactory(const char* name);
			void RegisterObstacleAvoidTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::PushFromObstacleTrack (16 vftable slots, 0x40 bytes)
			class PushFromObstacleTrack : public fight::Track
			{
			public:
				// 0x10194EE0
				PushFromObstacleTrack();
				virtual ~PushFromObstacleTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100FCE60, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetJoint(const fight::Name& newValue);
				bool SetOffset(const math::Vector& newValue);
				bool SetRayVector(const math::Vector& newValue);
				bool SetCollideWith(int newValue);
				bool SetVelocity(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name joint;  // +0x10
					math::Vector offset;  // +0x18
					math::Vector rayVector;  // +0x24
					float timeBegin;  // +0x30
					float timeEnd;  // +0x34
					float velocity;  // +0x38
					int collideWith;  // +0x3C
			};

			extern fight::Property** gPushFromObstacleTrackProperties;
			fight::TrackFactory* CreatePushFromObstacleTrackFactory(const char* name);
			void RegisterPushFromObstacleTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ObstacleTestTrack (16 vftable slots, 0x74 bytes)
			class ObstacleTestTrack : public fight::Track
			{
			public:
				// 0x10194B40
				ObstacleTestTrack();
				virtual ~ObstacleTestTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100FD530, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetLookaheadDistance(float newValue);
				bool SetCharacterHeight(float newValue);
				bool SetCharacterWidth(float newValue);
				bool SetCharacterDepth(float newValue);
				bool SetCharacterSurfaceClearance(float newValue);
				bool SetObstacleHeightMin(float newValue);
				bool SetObstacleHeightMax(float newValue);
				bool SetObstacleLengthMax(float newValue);
				bool SetSurfaceNormalOverride(const math::Vector& newValue);
				bool SetPoleAvoidVelocity(float newValue);
				fight::BranchHolder* SetBranch();
				bool SetPriority(int newValue);
				fight::ConditionList* SetConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder branch;  // +0x10
					math::Vector surfaceNormalOverride;  // +0x34
					fight::ConditionList conditions;  // +0x40
					float characterDepth;  // +0x44
					float characterHeight;  // +0x48
					float characterSurfaceClearance;  // +0x4C
					float characterWidth;  // +0x50
					float lookaheadDistance;  // +0x54
					float obstacleHeightMax;  // +0x58
					float obstacleHeightMin;  // +0x5C
					float obstacleLengthMax;  // +0x60
					float poleAvoidVelocity;  // +0x64
					float timeBegin;  // +0x68
					float timeEnd;  // +0x6C
					int priority;  // +0x70
			};

			extern fight::Property** gObstacleTestTrackProperties;
			fight::TrackFactory* CreateObstacleTestTrackFactory(const char* name);
			void RegisterObstacleTestTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
