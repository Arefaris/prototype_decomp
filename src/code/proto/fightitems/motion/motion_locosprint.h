// Fight items of the motion group: SprintVelocityClearTrack, LocoSprintTrack, LocoSprintChargeTrack (unit 0x10188680 - 0x1018AAB0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_LOCOSPRINT_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_LOCOSPRINT_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::SprintVelocityClearTrack (16 vftable slots, 0x14 bytes)
			class SprintVelocityClearTrack : public fight::Track
			{
			public:
				// 0x10188C70
				SprintVelocityClearTrack();
				virtual ~SprintVelocityClearTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100E60D0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
			};

			extern fight::Property** gSprintVelocityClearTrackProperties;
			fight::TrackFactory* CreateSprintVelocityClearTrackFactory(const char* name);
			void RegisterSprintVelocityClearTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::LocoSprintTrack (16 vftable slots, 0xC8 bytes)
			class LocoSprintTrack : public fight::Track
			{
			public:
				// 0x10188F80
				LocoSprintTrack();
				virtual ~LocoSprintTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100E87C0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetVelocityMin(float newValue);
				bool SetVelocityMid(float newValue);
				bool SetVelocityMax(float newValue);
				bool SetAccelerationMin(float newValue);
				bool SetAccelerationMid(float newValue);
				bool SetAccelerationMax(float newValue);
				bool SetDeceleration(float newValue);
				bool SetTurnVelocityMin(float newValue);
				bool SetTurnVelocityMax(float newValue);
				bool SetTurnAccelerationMin(float newValue);
				bool SetTurnAccelerationMax(float newValue);
				bool SetTurnDeceleration(float newValue);
				bool SetLeanRate(float newValue);
				bool SetPhase(float newValue);
				bool SetLocomotion(const fight::Name& newValue);
				bool SetAnimMin(const fight::Name& newValue);
				bool SetAnimMinLeanEast(const fight::Name& newValue);
				bool SetAnimMinLeanWest(const fight::Name& newValue);
				bool SetAnimMid(const fight::Name& newValue);
				bool SetAnimMidLeanEast(const fight::Name& newValue);
				bool SetAnimMidLeanWest(const fight::Name& newValue);
				bool SetAnimMax(const fight::Name& newValue);
				bool SetAnimMaxLeanEast(const fight::Name& newValue);
				bool SetAnimMaxLeanWest(const fight::Name& newValue);
				bool SetForceAnimationVelocities(bool newValue);
				bool SetUnlockableVelocityMin(float newValue);
				bool SetUnlockableFirst(int newValue);
				bool SetUnlockableLast(int newValue);
				bool SetPartition(const fight::Name& newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name animMax;  // +0x10
					fight::Name animMaxLeanEast;  // +0x18
					fight::Name animMaxLeanWest;  // +0x20
					fight::Name animMid;  // +0x28
					fight::Name animMidLeanEast;  // +0x30
					fight::Name animMidLeanWest;  // +0x38
					fight::Name animMin;  // +0x40
					fight::Name animMinLeanEast;  // +0x48
					fight::Name animMinLeanWest;  // +0x50
					fight::Name locomotion;  // +0x58
					fight::Name partition;  // +0x60
					float accelerationMax;  // +0x68
					float accelerationMid;  // +0x6C
					float accelerationMin;  // +0x70
					float blendInTime;  // +0x74
					float blendOutTime;  // +0x78
					float deceleration;  // +0x7C
					float leanRate;  // +0x80
					float phase;  // +0x84
					float timeBegin;  // +0x88
					float timeEnd;  // +0x8C
					float turnAccelerationMax;  // +0x90
					float turnAccelerationMin;  // +0x94
					float turnDeceleration;  // +0x98
					float turnVelocityMax;  // +0x9C
					float turnVelocityMin;  // +0xA0
					float unlockableVelocityMin;  // +0xA4
					float velocityMax;  // +0xA8
					float velocityMid;  // +0xAC
					float velocityMin;  // +0xB0
					int priority;  // +0xB4
					int unlockableFirst;  // +0xB8
					int unlockableLast;  // +0xBC
					bool forceAnimationVelocities;  // +0xC0
					unsigned char unknownC1[0x7];
			};

			extern fight::Property** gLocoSprintTrackProperties;
			fight::TrackFactory* CreateLocoSprintTrackFactory(const char* name);
			void RegisterLocoSprintTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::LocoSprintChargeTrack (16 vftable slots, 0x90 bytes)
			class LocoSprintChargeTrack : public fight::Track
			{
			public:
				// 0x10189120
				LocoSprintChargeTrack();
				virtual ~LocoSprintChargeTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100E8810, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetVelocityMin(float newValue);
				bool SetVelocityMid(float newValue);
				bool SetVelocityMax(float newValue);
				bool SetAccelerationMin(float newValue);
				bool SetAccelerationMid(float newValue);
				bool SetAccelerationMax(float newValue);
				bool SetDeceleration(float newValue);
				bool SetTurnVelocityMin(float newValue);
				bool SetTurnVelocityMax(float newValue);
				bool SetTurnAccelerationMin(float newValue);
				bool SetTurnAccelerationMax(float newValue);
				bool SetTurnDeceleration(float newValue);
				bool SetLeanRate(float newValue);
				bool SetPhase(float newValue);
				bool SetLocomotion(const fight::Name& newValue);
				bool SetAnimChargeMin(const fight::Name& newValue);
				bool SetAnimChargeMax(const fight::Name& newValue);
				bool SetAnimLeanEast(const fight::Name& newValue);
				bool SetAnimLeanWest(const fight::Name& newValue);
				bool SetForceAnimationVelocities(bool newValue);
				bool SetPartition(const fight::Name& newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name animChargeMax;  // +0x10
					fight::Name animChargeMin;  // +0x18
					fight::Name animLeanEast;  // +0x20
					fight::Name animLeanWest;  // +0x28
					fight::Name locomotion;  // +0x30
					fight::Name partition;  // +0x38
					float accelerationMax;  // +0x40
					float accelerationMid;  // +0x44
					float accelerationMin;  // +0x48
					float blendInTime;  // +0x4C
					float blendOutTime;  // +0x50
					float deceleration;  // +0x54
					float leanRate;  // +0x58
					float phase;  // +0x5C
					float timeBegin;  // +0x60
					float timeEnd;  // +0x64
					float turnAccelerationMax;  // +0x68
					float turnAccelerationMin;  // +0x6C
					float turnDeceleration;  // +0x70
					float turnVelocityMax;  // +0x74
					float turnVelocityMin;  // +0x78
					float velocityMax;  // +0x7C
					float velocityMid;  // +0x80
					float velocityMin;  // +0x84
					int priority;  // +0x88
					bool forceAnimationVelocities;  // +0x8C
					unsigned char unknown8D[0x3];
			};

			extern fight::Property** gLocoSprintChargeTrackProperties;
			fight::TrackFactory* CreateLocoSprintChargeTrackFactory(const char* name);
			void RegisterLocoSprintChargeTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
