// Fight items of the motion group: AnimationBlendVerticalAimTrack, AnimationBlendSimpleTrack, AnimationBlendVerticalAimStrafeTrack, AnimationBlendDirectionalTrack (unit 0x1013C5B0 - 0x10140FC0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_ANIMATIONBLEND_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_ANIMATIONBLEND_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::AnimationBlendVerticalAimTrack (16 vftable slots, 0xB0 bytes)
			class AnimationBlendVerticalAimTrack : public fight::Track
			{
			public:
				// 0x1013D700
				AnimationBlendVerticalAimTrack();
				virtual ~AnimationBlendVerticalAimTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100987C0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetAngleRate(float newValue);
				bool SetAngleDefault(float newValue);
				bool SetAngleOffset(float newValue);
				bool SetAngleOffsetMin(float newValue);
				bool SetAngleMin(float newValue);
				bool SetAngleMax(float newValue);
				bool SetOffsetInterpolationDist(float newValue);
				bool SetInterpolationDirection(int newValue);
				bool SetSpeed(float newValue);
				bool SetCyclic(int newValue);
				bool SetAnimUp(const fight::Name& newValue);
				bool SetAnimUpAngle(float newValue);
				bool SetAnimUpSyncFrame(float newValue);
				bool SetAnimUpStartFrame(float newValue);
				bool SetAnimUpEndFrame(float newValue);
				bool SetAnimUpSpeed(float newValue);
				bool SetAnimNeutral(const fight::Name& newValue);
				bool SetAnimNeutralAngle(float newValue);
				bool SetAnimNeutralSyncFrame(float newValue);
				bool SetAnimNeutralStartFrame(float newValue);
				bool SetAnimNeutralEndFrame(float newValue);
				bool SetAnimNeutralSpeed(float newValue);
				bool SetAnimDown(const fight::Name& newValue);
				bool SetAnimDownAngle(float newValue);
				bool SetAnimDownSyncFrame(float newValue);
				bool SetAnimDownStartFrame(float newValue);
				bool SetAnimDownEndFrame(float newValue);
				bool SetAnimDownSpeed(float newValue);
				bool SetPartition(const fight::Name& newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);
				bool SetTargetingMode(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name animDown;  // +0x10
					fight::Name animNeutral;  // +0x18
					fight::Name animUp;  // +0x20
					fight::Name partition;  // +0x28
					float angleDefault;  // +0x30
					float angleMax;  // +0x34
					float angleMin;  // +0x38
					float angleOffset;  // +0x3C
					float angleOffsetMin;  // +0x40
					float angleRate;  // +0x44
					float animDownAngle;  // +0x48
					float animDownEndFrame;  // +0x4C
					float animDownSpeed;  // +0x50
					float animDownStartFrame;  // +0x54
					float animDownSyncFrame;  // +0x58
					float animNeutralAngle;  // +0x5C
					float animNeutralEndFrame;  // +0x60
					float animNeutralSpeed;  // +0x64
					float animNeutralStartFrame;  // +0x68
					float animNeutralSyncFrame;  // +0x6C
					float animUpAngle;  // +0x70
					float animUpEndFrame;  // +0x74
					float animUpSpeed;  // +0x78
					float animUpStartFrame;  // +0x7C
					float animUpSyncFrame;  // +0x80
					float blendInTime;  // +0x84
					float blendOutTime;  // +0x88
					float offsetInterpolationDist;  // +0x8C
					float speed;  // +0x90
					float timeBegin;  // +0x94
					float timeEnd;  // +0x98
					int cyclic;  // +0x9C
					int interpolationDirection;  // +0xA0
					int priority;  // +0xA4
					int targetingMode;  // +0xA8
					unsigned char unknownAC[0x4];
			};

			extern fight::Property** gAnimationBlendVerticalAimTrackProperties;
			fight::TrackFactory* CreateAnimationBlendVerticalAimTrackFactory(const char* name);
			void RegisterAnimationBlendVerticalAimTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::AnimationBlendSimpleTrack (16 vftable slots, 0x70 bytes)
			class AnimationBlendSimpleTrack : public fight::Track
			{
			public:
				// 0x1013D8C0
				AnimationBlendSimpleTrack();
				virtual ~AnimationBlendSimpleTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10098860, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetWeightVariable(const fight::Name& newValue);
				bool SetSpeed(float newValue);
				bool SetCyclic(int newValue);
				bool SetAnimA(const fight::Name& newValue);
				bool SetAnimASyncFrame(float newValue);
				bool SetAnimAStartFrame(float newValue);
				bool SetAnimAEndFrame(float newValue);
				bool SetAnimASpeed(float newValue);
				bool SetAnimB(const fight::Name& newValue);
				bool SetAnimBSyncFrame(float newValue);
				bool SetAnimBStartFrame(float newValue);
				bool SetAnimBEndFrame(float newValue);
				bool SetAnimBSpeed(float newValue);
				bool SetPartition(const fight::Name& newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name animA;  // +0x10
					fight::Name animB;  // +0x18
					fight::Name partition;  // +0x20
					fight::Name weightVariable;  // +0x28
					float animAEndFrame;  // +0x30
					float animASpeed;  // +0x34
					float animAStartFrame;  // +0x38
					float animASyncFrame;  // +0x3C
					float animBEndFrame;  // +0x40
					float animBSpeed;  // +0x44
					float animBStartFrame;  // +0x48
					float animBSyncFrame;  // +0x4C
					float blendInTime;  // +0x50
					float blendOutTime;  // +0x54
					float speed;  // +0x58
					float timeBegin;  // +0x5C
					float timeEnd;  // +0x60
					int cyclic;  // +0x64
					int priority;  // +0x68
					unsigned char unknown6C[0x4];
			};

			extern fight::Property** gAnimationBlendSimpleTrackProperties;
			fight::TrackFactory* CreateAnimationBlendSimpleTrackFactory(const char* name);
			void RegisterAnimationBlendSimpleTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::AnimationBlendVerticalAimStrafeTrack (16 vftable slots, 0xF0 bytes)
			class AnimationBlendVerticalAimStrafeTrack : public fight::Track
			{
			public:
				// 0x1013D9B0
				AnimationBlendVerticalAimStrafeTrack();
				virtual ~AnimationBlendVerticalAimStrafeTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10098810, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetRefLocomotionName(const fight::Name& newValue);
				bool SetAngleRate(float newValue);
				bool SetAngleDefault(float newValue);
				bool SetAngleOffset(float newValue);
				bool SetAngleOffsetMin(float newValue);
				bool SetOffsetInterpolationDist(float newValue);
				bool SetInterpolationDirection(int newValue);
				bool SetSpeed(float newValue);
				bool SetCyclic(int newValue);
				bool SetPivotJoint(const fight::Name& newValue);
				bool SetPivotOffset(const math::Vector& newValue);
				bool SetTargetingMode(int newValue);
				bool SetAnimUpAngle(float newValue);
				bool SetAnimNeutralAngle(float newValue);
				bool SetAnimDownAngle(float newValue);
				bool SetAnimIdleUp(const fight::Name& newValue);
				bool SetAnimIdleNeutral(const fight::Name& newValue);
				bool SetAnimIdleDown(const fight::Name& newValue);
				bool SetAnimNorthUp(const fight::Name& newValue);
				bool SetAnimNorthNeutral(const fight::Name& newValue);
				bool SetAnimNorthDown(const fight::Name& newValue);
				bool SetAnimEastUp(const fight::Name& newValue);
				bool SetAnimEastNeutral(const fight::Name& newValue);
				bool SetAnimEastDown(const fight::Name& newValue);
				bool SetAnimSouthUp(const fight::Name& newValue);
				bool SetAnimSouthNeutral(const fight::Name& newValue);
				bool SetAnimSouthDown(const fight::Name& newValue);
				bool SetAnimWestUp(const fight::Name& newValue);
				bool SetAnimWestNeutral(const fight::Name& newValue);
				bool SetAnimWestDown(const fight::Name& newValue);
				bool SetPartition(const fight::Name& newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name animEastDown;  // +0x10
					fight::Name animEastNeutral;  // +0x18
					fight::Name animEastUp;  // +0x20
					fight::Name animIdleDown;  // +0x28
					fight::Name animIdleNeutral;  // +0x30
					fight::Name animIdleUp;  // +0x38
					fight::Name animNorthDown;  // +0x40
					fight::Name animNorthNeutral;  // +0x48
					fight::Name animNorthUp;  // +0x50
					fight::Name animSouthDown;  // +0x58
					fight::Name animSouthNeutral;  // +0x60
					fight::Name animSouthUp;  // +0x68
					fight::Name animWestDown;  // +0x70
					fight::Name animWestNeutral;  // +0x78
					fight::Name animWestUp;  // +0x80
					fight::Name partition;  // +0x88
					fight::Name pivotJoint;  // +0x90
					fight::Name refLocomotionName;  // +0x98
					math::Vector pivotOffset;  // +0xA0
					float angleDefault;  // +0xAC
					float angleOffset;  // +0xB0
					float angleOffsetMin;  // +0xB4
					float angleRate;  // +0xB8
					float animDownAngle;  // +0xBC
					float animNeutralAngle;  // +0xC0
					float animUpAngle;  // +0xC4
					float blendInTime;  // +0xC8
					float blendOutTime;  // +0xCC
					float offsetInterpolationDist;  // +0xD0
					float speed;  // +0xD4
					float timeBegin;  // +0xD8
					float timeEnd;  // +0xDC
					int cyclic;  // +0xE0
					int interpolationDirection;  // +0xE4
					int priority;  // +0xE8
					int targetingMode;  // +0xEC
			};

			extern fight::Property** gAnimationBlendVerticalAimStrafeTrackProperties;
			fight::TrackFactory* CreateAnimationBlendVerticalAimStrafeTrackFactory(const char* name);
			void RegisterAnimationBlendVerticalAimStrafeTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::AnimationBlendDirectionalTrack (16 vftable slots, 0xC8 bytes)
			class AnimationBlendDirectionalTrack : public fight::Track
			{
			public:
				// 0x1013DBB0
				AnimationBlendDirectionalTrack();
				virtual ~AnimationBlendDirectionalTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10098770, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetInput(int newValue);
				bool SetBlendRate(float newValue);
				bool SetSpeed(float newValue);
				bool SetCyclic(int newValue);
				bool SetAnimNeutral(const fight::Name& newValue);
				bool SetAnimNeutralSyncFrame(float newValue);
				bool SetAnimNeutralStartFrame(float newValue);
				bool SetAnimNeutralEndFrame(float newValue);
				bool SetAnimNeutralSpeed(float newValue);
				bool SetAnimNorth(const fight::Name& newValue);
				bool SetAnimNorthSyncFrame(float newValue);
				bool SetAnimNorthStartFrame(float newValue);
				bool SetAnimNorthEndFrame(float newValue);
				bool SetAnimNorthSpeed(float newValue);
				bool SetAnimNorthAllowedTransitions(int newValue);
				bool SetAnimEast(const fight::Name& newValue);
				bool SetAnimEastSyncFrame(float newValue);
				bool SetAnimEastStartFrame(float newValue);
				bool SetAnimEastEndFrame(float newValue);
				bool SetAnimEastSpeed(float newValue);
				bool SetAnimEastAllowedTransitions(int newValue);
				bool SetAnimSouth(const fight::Name& newValue);
				bool SetAnimSouthSyncFrame(float newValue);
				bool SetAnimSouthStartFrame(float newValue);
				bool SetAnimSouthEndFrame(float newValue);
				bool SetAnimSouthSpeed(float newValue);
				bool SetAnimSouthAllowedTransitions(int newValue);
				bool SetAnimWest(const fight::Name& newValue);
				bool SetAnimWestSyncFrame(float newValue);
				bool SetAnimWestStartFrame(float newValue);
				bool SetAnimWestEndFrame(float newValue);
				bool SetAnimWestSpeed(float newValue);
				bool SetAnimWestAllowedTransitions(int newValue);
				bool SetPartition(const fight::Name& newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name animEast;  // +0x10
					fight::Name animNeutral;  // +0x18
					fight::Name animNorth;  // +0x20
					fight::Name animSouth;  // +0x28
					fight::Name animWest;  // +0x30
					fight::Name partition;  // +0x38
					float animEastEndFrame;  // +0x40
					float animEastSpeed;  // +0x44
					float animEastStartFrame;  // +0x48
					float animEastSyncFrame;  // +0x4C
					float animNeutralEndFrame;  // +0x50
					float animNeutralSpeed;  // +0x54
					float animNeutralStartFrame;  // +0x58
					float animNeutralSyncFrame;  // +0x5C
					float animNorthEndFrame;  // +0x60
					float animNorthSpeed;  // +0x64
					float animNorthStartFrame;  // +0x68
					float animNorthSyncFrame;  // +0x6C
					float animSouthEndFrame;  // +0x70
					float animSouthSpeed;  // +0x74
					float animSouthStartFrame;  // +0x78
					float animSouthSyncFrame;  // +0x7C
					float animWestEndFrame;  // +0x80
					float animWestSpeed;  // +0x84
					float animWestStartFrame;  // +0x88
					float animWestSyncFrame;  // +0x8C
					float blendInTime;  // +0x90
					float blendOutTime;  // +0x94
					float blendRate;  // +0x98
					float speed;  // +0x9C
					float timeBegin;  // +0xA0
					float timeEnd;  // +0xA4
					int cyclic;  // +0xA8
					int input;  // +0xAC
					int priority;  // +0xB0
					int animEastAllowedTransitions;  // +0xB4
					int animNorthAllowedTransitions;  // +0xB8
					int animSouthAllowedTransitions;  // +0xBC
					int animWestAllowedTransitions;  // +0xC0
					unsigned char unknownC4[0x4];
			};

			extern fight::Property** gAnimationBlendDirectionalTrackProperties;
			fight::TrackFactory* CreateAnimationBlendDirectionalTrackFactory(const char* name);
			void RegisterAnimationBlendDirectionalTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
