// Fight items of the motion group: WallRunTrack, WallOrientTrack, WallRunEnterTrack (unit 0x101CE030 - 0x101D0240; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_WALLRUN_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_WALLRUN_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::WallRunTrack (16 vftable slots, 0xA8 bytes)
			class WallRunTrack : public fight::Track
			{
			public:
				// 0x101CE940
				WallRunTrack();
				virtual ~WallRunTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10132BE0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetVelocityMin(float newValue);
				bool SetVelocityMax(float newValue);
				bool SetAcceleration(float newValue);
				bool SetGravity(float newValue);
				bool SetTurningRate(float newValue);
				bool SetSurfaceAngleThreshold(float newValue);
				bool SetAnimUp(const fight::Name& newValue);
				bool SetAnimLeft(const fight::Name& newValue);
				bool SetAnimRight(const fight::Name& newValue);
				bool SetAnimUpLeft(const fight::Name& newValue);
				bool SetAnimUpRight(const fight::Name& newValue);
				bool SetAnimDownLeft(const fight::Name& newValue);
				bool SetAnimDownRight(const fight::Name& newValue);
				bool SetForceAnimationVelocities(bool newValue);
				bool SetSyncFrameUp(float newValue);
				bool SetSyncFrameLeft(float newValue);
				bool SetSyncFrameRight(float newValue);
				bool SetSyncFrameUpLeft(float newValue);
				bool SetSyncFrameUpRight(float newValue);
				bool SetSyncFrameDownLeft(float newValue);
				bool SetSyncFrameDownRight(float newValue);
				bool SetUnlockableVelocityMin(float newValue);
				bool SetUnlockableFirst(int newValue);
				bool SetUnlockableLast(int newValue);
				bool SetSprintVelocityDropRate(float newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name animDownLeft;  // +0x10
					fight::Name animDownRight;  // +0x18
					fight::Name animLeft;  // +0x20
					fight::Name animRight;  // +0x28
					fight::Name animUp;  // +0x30
					fight::Name animUpLeft;  // +0x38
					fight::Name animUpRight;  // +0x40
					float acceleration;  // +0x48
					float blendInTime;  // +0x4C
					float blendOutTime;  // +0x50
					float gravity;  // +0x54
					float sprintVelocityDropRate;  // +0x58
					float surfaceAngleThreshold;  // +0x5C
					float syncFrameDownLeft;  // +0x60
					float syncFrameDownRight;  // +0x64
					float syncFrameLeft;  // +0x68
					float syncFrameRight;  // +0x6C
					float syncFrameUp;  // +0x70
					float syncFrameUpLeft;  // +0x74
					float syncFrameUpRight;  // +0x78
					float timeBegin;  // +0x7C
					float timeEnd;  // +0x80
					float turningRate;  // +0x84
					float unlockableVelocityMin;  // +0x88
					float velocityMax;  // +0x8C
					float velocityMin;  // +0x90
					int priority;  // +0x94
					int unlockableFirst;  // +0x98
					int unlockableLast;  // +0x9C
					bool forceAnimationVelocities;  // +0xA0
					unsigned char unknownA1[0x7];
			};

			extern fight::Property** gWallRunTrackProperties;
			fight::TrackFactory* CreateWallRunTrackFactory(const char* name);
			void RegisterWallRunTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::WallOrientTrack (16 vftable slots, 0x2C bytes)
			class WallOrientTrack : public fight::Track
			{
			public:
				// 0x101CE670
				WallOrientTrack();
				virtual ~WallOrientTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10133700, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetOrientOffset(float newValue);
				bool SetTurningVelocity(float newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float blendInTime;  // +0x10
					float blendOutTime;  // +0x14
					float orientOffset;  // +0x18
					float timeBegin;  // +0x1C
					float timeEnd;  // +0x20
					float turningVelocity;  // +0x24
					int priority;  // +0x28
			};

			extern fight::Property** gWallOrientTrackProperties;
			fight::TrackFactory* CreateWallOrientTrackFactory(const char* name);
			void RegisterWallOrientTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::WallRunEnterTrack (16 vftable slots, 0x7C bytes)
			class WallRunEnterTrack : public fight::Track
			{
			public:
				// 0x101CE730
				WallRunEnterTrack();
				virtual ~WallRunEnterTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10133670, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetTimeCancel(float newValue);
				bool SetVelocityXZMin(float newValue);
				bool SetVelocityXZMax(float newValue);
				bool SetVelocityUpMin(float newValue);
				bool SetVelocityUpMax(float newValue);
				bool SetTurningVelocityMin(float newValue);
				bool SetTurningVelocityMax(float newValue);
				bool SetTurningAccelerationMin(float newValue);
				bool SetTurningAccelerationMax(float newValue);
				bool SetSurfaceDistance(float newValue);
				bool SetSurfacePushoutVelocityMax(float newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);
				fight::BranchHolder* SetBranch();
				bool SetInterruptPriority(int newValue);
				fight::ConditionList* SetConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder branch;  // +0x10
					fight::ConditionList conditions;  // +0x34
					float blendInTime;  // +0x38
					float blendOutTime;  // +0x3C
					float surfaceDistance;  // +0x40
					float surfacePushoutVelocityMax;  // +0x44
					float timeBegin;  // +0x48
					float timeCancel;  // +0x4C
					float timeEnd;  // +0x50
					float turningAccelerationMax;  // +0x54
					float turningAccelerationMin;  // +0x58
					float turningVelocityMax;  // +0x5C
					float turningVelocityMin;  // +0x60
					float velocityUpMax;  // +0x64
					float velocityUpMin;  // +0x68
					float velocityXZMax;  // +0x6C
					float velocityXZMin;  // +0x70
					int interruptPriority;  // +0x74
					int priority;  // +0x78
			};

			extern fight::Property** gWallRunEnterTrackProperties;
			fight::TrackFactory* CreateWallRunEnterTrackFactory(const char* name);
			void RegisterWallRunEnterTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// The owner of an action when it is a supporting surface event (kind 0x21006), else none
			inline core::IRefCount* AsSurfaceEventOwner(core::IRefCount* owner)
			{
				TrackOwner* trackOwner = (TrackOwner*)owner;
				if (trackOwner == 0)
				{
					return 0;
				}
				return (trackOwner->kind == 0x21006) ? owner : 0;
			}

			// RTTI: proto::fightitems::motion::WallRunAction (9 vftable slots, 0x58 bytes)
			class WallRunAction : public fight::Action
			{
			public:
				// 0x101307A0
				WallRunAction(WallRunTrack* newTrack, engine::GameObjectHandle newTarget, core::IRefCount* newEvent);
				// 0x101303C0
				virtual ~WallRunAction();

				// vftable slot 5 (0x10130890)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x10130410)
				virtual void Slot6();
				// vftable slot 7 (0x10132C60)
				virtual bool Slot7(int arg, float value);

				core::Link<WallRunTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				core::IRefCount* surfaceEvent;  // +0x2C
				choreo::Driver* driver;  // +0x30
				float unknown34;
				float unknown38;
				float unknown3C;
				float unknown40;
				float unknown44;
				float unknown48;
				bool unknown4C;
				bool unknown4D;
				float unknown50;
				float unknown54;
			};

			// RTTI: proto::fightitems::motion::WallOrientAction (9 vftable slots, 0x40 bytes)
			class WallOrientAction : public fight::Action
			{
			public:
				// 0x10132750
				WallOrientAction(WallOrientTrack* newTrack, engine::GameObjectHandle newTarget, core::IRefCount* newEvent);
				// 0x10130590
				virtual ~WallOrientAction();

				// vftable slot 5 (0x10132820)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101305E0)
				virtual void Slot6();
				// vftable slot 7 (0x10132A10)
				virtual bool Slot7(int arg, float value);

				core::Link<WallOrientTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				core::IRefCount* surfaceEvent;  // +0x2C
				choreo::Driver* driver;  // +0x30
				float unknown34;
				float unknown38;
				float unknown3C;
			};

			// ---- actions end
		}
	}
}

#endif
