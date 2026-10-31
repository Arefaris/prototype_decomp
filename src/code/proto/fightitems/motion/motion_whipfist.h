// Fight items of the motion group: WhipFistExtendBlockedOrNotCondition, WhipFistResetTargetTrack, TendrilTrack, WhipFistRetractTrack, WhipFistFreezeSegmentsTrack, WhipFistSegmentFixToJointTrack, TendrilFromParentTrack, WhipFistExtendTrack, WhipFistPullParentToTargetTrack, WhipFistAnimatedTrack, WhipFistMakeTautTrack (unit 0x101D0A00 - 0x101D5F50; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_WHIPFIST_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_WHIPFIST_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::WhipFistExtendBlockedOrNotCondition (10 vftable slots, 0x10 bytes)
			class WhipFistExtendBlockedOrNotCondition : public fight::Condition
			{
			public:
				// 0x101D1790
				WhipFistExtendBlockedOrNotCondition();
				virtual ~WhipFistExtendBlockedOrNotCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10137940, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetBlocked(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool blocked;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gWhipFistExtendBlockedOrNotConditionProperties;
			fight::ConditionFactory* CreateWhipFistExtendBlockedOrNotConditionFactory(const char* name);
			void RegisterWhipFistExtendBlockedOrNotConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::WhipFistResetTargetTrack (16 vftable slots, 0x14 bytes)
			class WhipFistResetTargetTrack : public fight::Track
			{
			public:
				// 0x101D17F0
				WhipFistResetTargetTrack();
				virtual ~WhipFistResetTargetTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10136920, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
			};

			extern fight::Property** gWhipFistResetTargetTrackProperties;
			fight::TrackFactory* CreateWhipFistResetTargetTrackFactory(const char* name);
			void RegisterWhipFistResetTargetTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::TendrilTrack (16 vftable slots, 0xB0 bytes)
			class TendrilTrack : public fight::Track
			{
			public:
				// 0x101D1F00
				TendrilTrack();
				virtual ~TendrilTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1013BC20, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeReverse(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetDrawable(const fight::Name& newValue);
				bool SetScale(float newValue);
				bool SetKeepGoing(bool newValue);
				bool SetHitRadius(float newValue);
				bool SetTrackingVelocity(float newValue);
				bool SetTrackingDeceleration(float newValue);
				bool SetSwapDirection(bool newValue);
				bool SetStaticEndPoint(bool newValue);
				bool SetStartJoint(const fight::Name& newValue);
				bool SetStartJointOffset(const math::Vector& newValue);
				bool SetGrabSlot(const fight::Name& newValue);
				bool SetUseGrabber(bool newValue);
				bool SetGrabSlotJoint(const fight::Name& newValue);
				bool SetGrabSlotJointOffset(const math::Vector& newValue);
				bool SetForwardVelocity(float newValue);
				bool SetReverseVelocity(float newValue);
				bool SetCircleRadius(float newValue);
				bool SetZAxisRotation(float newValue);
				bool SetXAxisRotation(float newValue);
				bool SetSegmentCount(int newValue);
				bool SetWaveSpeed(float newValue);
				bool SetWaveLength(float newValue);
				bool SetWaveAmplitude(float newValue);
				bool SetWaveAmplitudeRampUp(float newValue);
				bool SetWaveAmplitudeRampDown(float newValue);
				bool SetCorkscrewAngle(float newValue);
				bool SetCorkscrewRotationSpeed(float newValue);
				bool SetCorkscrewTravelingSpeed(float newValue);
				bool SetDevastatorDamageMultiplier(float newValue);
				bool SetTimeBetweenHits(float newValue);
				fight::ConditionList* SetReverseConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name drawable;  // +0x10
					fight::Name grabSlot;  // +0x18
					fight::Name grabSlotJoint;  // +0x20
					fight::Name startJoint;  // +0x28
					math::Vector grabSlotJointOffset;  // +0x30
					math::Vector startJointOffset;  // +0x3C
					fight::ConditionList reverseConditions;  // +0x48
					float circleRadius;  // +0x4C
					float corkscrewAngle;  // +0x50
					float corkscrewRotationSpeed;  // +0x54
					float corkscrewTravelingSpeed;  // +0x58
					float devastatorDamageMultiplier;  // +0x5C
					float forwardVelocity;  // +0x60
					float hitRadius;  // +0x64
					float reverseVelocity;  // +0x68
					float scale;  // +0x6C
					float timeBegin;  // +0x70
					float timeBetweenHits;  // +0x74
					float timeEnd;  // +0x78
					float timeReverse;  // +0x7C
					float trackingDeceleration;  // +0x80
					float trackingVelocity;  // +0x84
					float waveAmplitude;  // +0x88
					float waveAmplitudeRampDown;  // +0x8C
					float waveAmplitudeRampUp;  // +0x90
					float waveLength;  // +0x94
					float waveSpeed;  // +0x98
					float xAxisRotation;  // +0x9C
					float zAxisRotation;  // +0xA0
					int segmentCount;  // +0xA4
					bool keepGoing;  // +0xA8
					bool staticEndPoint;  // +0xA9
					bool swapDirection;  // +0xAA
					bool useGrabber;  // +0xAB
					unsigned char unknownAC[0x4];
			};

			extern fight::Property** gTendrilTrackProperties;
			fight::TrackFactory* CreateTendrilTrackFactory(const char* name);
			void RegisterTendrilTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::WhipFistRetractTrack (16 vftable slots, 0x24 bytes)
			class WhipFistRetractTrack : public fight::Track
			{
			public:
				// 0x101D18B0
				WhipFistRetractTrack();
				virtual ~WhipFistRetractTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1013BDD0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetVelocity(float newValue);
				bool SetSoundLeadTime(float newValue);
				bool SetMinSegmentsRemaining(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float soundLeadTime;  // +0x10
					float timeBegin;  // +0x14
					float timeEnd;  // +0x18
					float velocity;  // +0x1C
					int minSegmentsRemaining;  // +0x20
			};

			extern fight::Property** gWhipFistRetractTrackProperties;
			fight::TrackFactory* CreateWhipFistRetractTrackFactory(const char* name);
			void RegisterWhipFistRetractTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::WhipFistFreezeSegmentsTrack (16 vftable slots, 0x1C bytes)
			class WhipFistFreezeSegmentsTrack : public fight::Track
			{
			public:
				// 0x101D1950
				WhipFistFreezeSegmentsTrack();
				virtual ~WhipFistFreezeSegmentsTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1013BFB0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetNumSegments(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
					int numSegments;  // +0x18
			};

			extern fight::Property** gWhipFistFreezeSegmentsTrackProperties;
			fight::TrackFactory* CreateWhipFistFreezeSegmentsTrackFactory(const char* name);
			void RegisterWhipFistFreezeSegmentsTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::WhipFistSegmentFixToJointTrack (16 vftable slots, 0x30 bytes)
			class WhipFistSegmentFixToJointTrack : public fight::Track
			{
			public:
				// 0x101D2140
				WhipFistSegmentFixToJointTrack();
				virtual ~WhipFistSegmentFixToJointTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1013BEF0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetSegmentIndexFromStart(int newValue);
				bool SetJoint(const fight::Name& newValue);
				bool SetOffset(const math::Vector& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name joint;  // +0x10
					math::Vector offset;  // +0x18
					float timeBegin;  // +0x24
					float timeEnd;  // +0x28
					int segmentIndexFromStart;  // +0x2C
			};

			extern fight::Property** gWhipFistSegmentFixToJointTrackProperties;
			fight::TrackFactory* CreateWhipFistSegmentFixToJointTrackFactory(const char* name);
			void RegisterWhipFistSegmentFixToJointTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::TendrilFromParentTrack (16 vftable slots, 0xA8 bytes)
			class TendrilFromParentTrack : public fight::Track
			{
			public:
				// 0x101D21D0
				TendrilFromParentTrack();
				virtual ~TendrilFromParentTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1013BCD0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeReverse(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetDrawable(const fight::Name& newValue);
				bool SetScale(float newValue);
				bool SetKeepGoing(bool newValue);
				bool SetHitRadius(float newValue);
				bool SetTrackingVelocity(float newValue);
				bool SetTrackingDeceleration(float newValue);
				bool SetSwapDirection(bool newValue);
				bool SetStaticEndPoint(bool newValue);
				bool SetStartJoint(const fight::Name& newValue);
				bool SetStartJointOffset(const math::Vector& newValue);
				bool SetGrabSlotJoint(const fight::Name& newValue);
				bool SetGrabSlotJointOffset(const math::Vector& newValue);
				bool SetForwardVelocity(float newValue);
				bool SetReverseVelocity(float newValue);
				bool SetCircleRadius(float newValue);
				bool SetZAxisRotation(float newValue);
				bool SetXAxisRotation(float newValue);
				bool SetSegmentCount(int newValue);
				bool SetWaveSpeed(float newValue);
				bool SetWaveLength(float newValue);
				bool SetWaveAmplitude(float newValue);
				bool SetWaveAmplitudeRampUp(float newValue);
				bool SetWaveAmplitudeRampDown(float newValue);
				bool SetCorkscrewAngle(float newValue);
				bool SetCorkscrewRotationSpeed(float newValue);
				bool SetCorkscrewTravelingSpeed(float newValue);
				bool SetDevastatorDamageMultiplier(float newValue);
				bool SetTimeBetweenHits(float newValue);
				fight::ConditionList* SetReverseConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name drawable;  // +0x10
					fight::Name grabSlotJoint;  // +0x18
					fight::Name startJoint;  // +0x20
					math::Vector grabSlotJointOffset;  // +0x28
					math::Vector startJointOffset;  // +0x34
					fight::ConditionList reverseConditions;  // +0x40
					float circleRadius;  // +0x44
					float corkscrewAngle;  // +0x48
					float corkscrewRotationSpeed;  // +0x4C
					float corkscrewTravelingSpeed;  // +0x50
					float devastatorDamageMultiplier;  // +0x54
					float forwardVelocity;  // +0x58
					float hitRadius;  // +0x5C
					float reverseVelocity;  // +0x60
					float scale;  // +0x64
					float timeBegin;  // +0x68
					float timeBetweenHits;  // +0x6C
					float timeEnd;  // +0x70
					float timeReverse;  // +0x74
					float trackingDeceleration;  // +0x78
					float trackingVelocity;  // +0x7C
					float waveAmplitude;  // +0x80
					float waveAmplitudeRampDown;  // +0x84
					float waveAmplitudeRampUp;  // +0x88
					float waveLength;  // +0x8C
					float waveSpeed;  // +0x90
					float xAxisRotation;  // +0x94
					float zAxisRotation;  // +0x98
					int segmentCount;  // +0x9C
					bool keepGoing;  // +0xA0
					bool staticEndPoint;  // +0xA1
					bool swapDirection;  // +0xA2
					unsigned char unknownA3[0x5];
			};

			extern fight::Property** gTendrilFromParentTrackProperties;
			fight::TrackFactory* CreateTendrilFromParentTrackFactory(const char* name);
			void RegisterTendrilFromParentTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::WhipFistExtendTrack (16 vftable slots, 0x5C bytes)
			class WhipFistExtendTrack : public fight::Track
			{
			public:
				// 0x101D1A50
				WhipFistExtendTrack();
				virtual ~WhipFistExtendTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1013BD70, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetVelocityMin(float newValue);
				bool SetVelocityMax(float newValue);
				bool SetDistanceMin(float newValue);
				bool SetDistanceMax(float newValue);
				bool SetTrackingMin(float newValue);
				bool SetTrackingMax(float newValue);
				bool SetDamageMin(float newValue);
				bool SetDamageMax(float newValue);
				bool SetWaveSpeed(float newValue);
				bool SetWaveLength(float newValue);
				bool SetWaveAmplitude(float newValue);
				bool SetWaveAmplitudeRampUp(float newValue);
				bool SetWaveAmplitudeRampDown(float newValue);
				bool SetCorkscrewAngle(float newValue);
				bool SetCorkscrewRotationSpeed(float newValue);
				bool SetCorkscrewTravelingSpeed(float newValue);
				bool SetTarget(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float corkscrewAngle;  // +0x10
					float corkscrewRotationSpeed;  // +0x14
					float corkscrewTravelingSpeed;  // +0x18
					float damageMax;  // +0x1C
					float damageMin;  // +0x20
					float distanceMax;  // +0x24
					float distanceMin;  // +0x28
					float timeBegin;  // +0x2C
					float timeEnd;  // +0x30
					float trackingMax;  // +0x34
					float trackingMin;  // +0x38
					float velocityMax;  // +0x3C
					float velocityMin;  // +0x40
					float waveAmplitude;  // +0x44
					float waveAmplitudeRampDown;  // +0x48
					float waveAmplitudeRampUp;  // +0x4C
					float waveLength;  // +0x50
					float waveSpeed;  // +0x54
					int target;  // +0x58
			};

			extern fight::Property** gWhipFistExtendTrackProperties;
			fight::TrackFactory* CreateWhipFistExtendTrackFactory(const char* name);
			void RegisterWhipFistExtendTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::WhipFistPullParentToTargetTrack (16 vftable slots, 0x48 bytes)
			class WhipFistPullParentToTargetTrack : public fight::Track
			{
			public:
				// 0x101D1B80
				WhipFistPullParentToTargetTrack();
				virtual ~WhipFistPullParentToTargetTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1013BF50, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetVelocity(float newValue);
				bool SetAcceleration(float newValue);
				bool SetParabolicConstant(float newValue);
				bool SetParabolicOffset(float newValue);
				bool SetGoalOffsetFromTarget(const math::Vector& newValue);
				bool SetFaceTargetMaxTurnRate(float newValue);
				bool SetMaxStuckTime(float newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Vector goalOffsetFromTarget;  // +0x10
					float acceleration;  // +0x1C
					float blendInTime;  // +0x20
					float blendOutTime;  // +0x24
					float faceTargetMaxTurnRate;  // +0x28
					float maxStuckTime;  // +0x2C
					float parabolicConstant;  // +0x30
					float parabolicOffset;  // +0x34
					float timeBegin;  // +0x38
					float timeEnd;  // +0x3C
					float velocity;  // +0x40
					int priority;  // +0x44
			};

			extern fight::Property** gWhipFistPullParentToTargetTrackProperties;
			fight::TrackFactory* CreateWhipFistPullParentToTargetTrackFactory(const char* name);
			void RegisterWhipFistPullParentToTargetTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::WhipFistAnimatedTrack (16 vftable slots, 0x18 bytes)
			class WhipFistAnimatedTrack : public fight::Track
			{
			public:
				// 0x101D1CA0
				WhipFistAnimatedTrack();
				virtual ~WhipFistAnimatedTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1013BE90, another unit)
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

			extern fight::Property** gWhipFistAnimatedTrackProperties;
			fight::TrackFactory* CreateWhipFistAnimatedTrackFactory(const char* name);
			void RegisterWhipFistAnimatedTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::WhipFistMakeTautTrack (16 vftable slots, 0x1C bytes)
			class WhipFistMakeTautTrack : public fight::Track
			{
			public:
				// 0x101D1D30
				WhipFistMakeTautTrack();
				virtual ~WhipFistMakeTautTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1013BE30, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetTautTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float tautTime;  // +0x10
					float timeBegin;  // +0x14
					float timeEnd;  // +0x18
			};

			extern fight::Property** gWhipFistMakeTautTrackProperties;
			fight::TrackFactory* CreateWhipFistMakeTautTrackFactory(const char* name);
			void RegisterWhipFistMakeTautTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
