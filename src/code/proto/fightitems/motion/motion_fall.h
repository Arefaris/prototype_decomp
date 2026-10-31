// Fight items of the motion group: FallTrack (unit 0x1015E4B0 - 0x1015F0E0; the assert path of the unit's actions names code/proto/fightitems/motion/motion_fall.cpp).
#ifndef PROTO_FIGHTITEMS_MOTION_FALL_H
#define PROTO_FIGHTITEMS_MOTION_FALL_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"
#include "code/engine/fight/expressionactions.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::FallTrack (16 vftable slots, 0x64 bytes)
			class FallTrack : public fight::Track
			{
			public:
				// 0x1015E710
				FallTrack();
				virtual ~FallTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100BD230, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetTurningVelocityMin(float newValue);
				bool SetTurningAccelerationMin(float newValue);
				bool SetTurningVelocityMinForwardSpeedCap(float newValue);
				bool SetTurningVelocityMax(float newValue);
				bool SetTurningAccelerationMax(float newValue);
				bool SetTurningVelocityMaxForwardSpeedCap(float newValue);
				bool SetPreserveMomentum(int newValue);
				bool SetInitialVelocity(const math::Vector& newValue);
				bool SetGravity(float newValue);
				bool SetMaxVelocity(float newValue);
				bool SetGravityDecreaseRate(float newValue);
				bool SetMaxVelocityXZ(float newValue);
				bool SetMaxVelocityUp(float newValue);
				bool SetLimitTurning(bool newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Vector initialVelocity;  // +0x10
					float blendInTime;  // +0x1C
					float blendOutTime;  // +0x20
					float gravity;  // +0x24
					float gravityDecreaseRate;  // +0x28
					float maxVelocity;  // +0x2C
					float maxVelocityUp;  // +0x30
					float maxVelocityXZ;  // +0x34
					float timeBegin;  // +0x38
					float timeEnd;  // +0x3C
					float turningAccelerationMax;  // +0x40
					float turningAccelerationMin;  // +0x44
					float turningVelocityMax;  // +0x48
					float turningVelocityMaxForwardSpeedCap;  // +0x4C
					float turningVelocityMin;  // +0x50
					float turningVelocityMinForwardSpeedCap;  // +0x54
					int priority;  // +0x58
					int preserveMomentum;  // +0x5C
					bool limitTurning;  // +0x60
					unsigned char unknown61[0x3];
			};

			extern fight::Property** gFallTrackProperties;
			fight::TrackFactory* CreateFallTrackFactory(const char* name);
			void RegisterFallTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin

			// RTTI: proto::fightitems::motion::FallAction (9 vftable slots, 0x44 bytes)
			class FallAction : public fight::Action
			{
			public:
				// 0x100BC320
				FallAction(FallTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x100BC200
				virtual ~FallAction();

				// vftable slot 5 (0x100BC430)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x100BC240)
				virtual void Slot6();
				// vftable slot 7 (0x100BCC60)
				virtual bool Slot7(int arg, float value);

				engine::GameObjectHandle target;  // +0x1C
				choreo::Driver* driver;  // +0x20
				core::Link<FallTrack> link;  // +0x24
				float unknown30;  // +0x30
				math::Vector unknown34;  // +0x34
				float unknown40;  // +0x40
			};

			// ---- actions end
		}
	}
}

#endif
