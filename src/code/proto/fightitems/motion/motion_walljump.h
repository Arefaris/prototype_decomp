// Fight items of the motion group: WallJumpTrack, WallJumpUpTrack (unit 0x101CC5E0 - 0x101CE030; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_WALLJUMP_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_WALLJUMP_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::WallJumpTrack (16 vftable slots, 0x50 bytes)
			class WallJumpTrack : public fight::Track
			{
			public:
				// 0x101CCBD0
				WallJumpTrack();
				virtual ~WallJumpTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1012FAD0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetVelocityMin(float newValue);
				bool SetVelocityMax(float newValue);
				bool SetVelocityXZMax(float newValue);
				bool SetGravity(float newValue);
				bool SetWallAngleMin(float newValue);
				bool SetWallAngleMax(float newValue);
				bool SetTurningVelocity(float newValue);
				bool SetUpThresholdArc(float newValue);
				bool SetUseMomentum(bool newValue);
				bool SetArc(float newValue);
				bool SetMinYAngle(float newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float arc;  // +0x10
					float blendInTime;  // +0x14
					float blendOutTime;  // +0x18
					float gravity;  // +0x1C
					float minYAngle;  // +0x20
					float timeBegin;  // +0x24
					float timeEnd;  // +0x28
					float turningVelocity;  // +0x2C
					float upThresholdArc;  // +0x30
					float velocityMax;  // +0x34
					float velocityMin;  // +0x38
					float velocityXZMax;  // +0x3C
					float wallAngleMax;  // +0x40
					float wallAngleMin;  // +0x44
					int priority;  // +0x48
					bool useMomentum;  // +0x4C
					unsigned char unknown4D[0x3];
			};

			extern fight::Property** gWallJumpTrackProperties;
			fight::TrackFactory* CreateWallJumpTrackFactory(const char* name);
			void RegisterWallJumpTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::WallJumpUpTrack (16 vftable slots, 0x8C bytes)
			class WallJumpUpTrack : public fight::Track
			{
			public:
				// 0x101CCCF0
				WallJumpUpTrack();
				virtual ~WallJumpUpTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1012FD60, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetFlightTimeMin(float newValue);
				bool SetFlightTimeMax(float newValue);
				bool SetHeightMin(float newValue);
				bool SetHeightMax(float newValue);
				bool SetTurnVelocityMin(float newValue);
				bool SetTurnVelocityMax(float newValue);
				bool SetTurnAccelerationMin(float newValue);
				bool SetTurnAccelerationMax(float newValue);
				bool SetUnlockableFirst(int newValue);
				bool SetUnlockableLast(int newValue);
				bool SetUnlockableFlightTimeMin(float newValue);
				bool SetUnlockableHeightMin(float newValue);
				bool SetObstacleLookaheadDistance(float newValue);
				bool SetCharacterHeight(float newValue);
				bool SetCharacterWidth(float newValue);
				bool SetCharacterDepth(float newValue);
				bool SetCharacterSurfaceClearance(float newValue);
				bool SetObstacleHeightMin(float newValue);
				bool SetObstacleHeightMax(float newValue);
				bool SetObstacleLengthMax(float newValue);
				bool SetPushOutHeightMin(float newValue);
				bool SetPushOutVelocityMax(float newValue);
				bool SetObstacleFaceHeightMin(float newValue);
				bool SetPushOutHeightMax(float newValue);
				bool SetObstacleSlopeMax(float newValue);
				bool SetAbortRayLength(float newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float abortRayLength;  // +0x10
					float blendInTime;  // +0x14
					float blendOutTime;  // +0x18
					float characterDepth;  // +0x1C
					float characterHeight;  // +0x20
					float characterSurfaceClearance;  // +0x24
					float characterWidth;  // +0x28
					float flightTimeMax;  // +0x2C
					float flightTimeMin;  // +0x30
					float heightMax;  // +0x34
					float heightMin;  // +0x38
					float obstacleFaceHeightMin;  // +0x3C
					float obstacleHeightMax;  // +0x40
					float obstacleHeightMin;  // +0x44
					float obstacleLengthMax;  // +0x48
					float obstacleLookaheadDistance;  // +0x4C
					float obstacleSlopeMax;  // +0x50
					float pushOutHeightMax;  // +0x54
					float pushOutHeightMin;  // +0x58
					float pushOutVelocityMax;  // +0x5C
					float timeBegin;  // +0x60
					float timeEnd;  // +0x64
					float turnAccelerationMax;  // +0x68
					float turnAccelerationMin;  // +0x6C
					float turnVelocityMax;  // +0x70
					float turnVelocityMin;  // +0x74
					float unlockableFlightTimeMin;  // +0x78
					float unlockableHeightMin;  // +0x7C
					int priority;  // +0x80
					int unlockableFirst;  // +0x84
					int unlockableLast;  // +0x88
			};

			extern fight::Property** gWallJumpUpTrackProperties;
			fight::TrackFactory* CreateWallJumpUpTrackFactory(const char* name);
			void RegisterWallJumpUpTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
