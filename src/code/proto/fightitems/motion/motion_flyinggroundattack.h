// Fight items of the motion group: FlyingGroundAttackTrack (unit 0x10160940 - 0x101610C0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_FLYINGGROUNDATTACK_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_FLYINGGROUNDATTACK_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"
#include "code/engine/fight/expressionactions.h"
#include "code/choreo/rootdriver.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::FlyingGroundAttackTrack (16 vftable slots, 0x3C bytes)
			class FlyingGroundAttackTrack : public fight::Track
			{
			public:
				// 0x10160AC0
				FlyingGroundAttackTrack();
				virtual ~FlyingGroundAttackTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100BFE10, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetVelocityXZMin(float newValue);
				bool SetVelocityXZMax(float newValue);
				bool SetAccelerationXZ(float newValue);
				bool SetGravity(float newValue);
				bool SetTurningVelocity(float newValue);
				bool SetTargetOffset(float newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float accelerationXZ;  // +0x10
					float blendInTime;  // +0x14
					float blendOutTime;  // +0x18
					float gravity;  // +0x1C
					float targetOffset;  // +0x20
					float timeBegin;  // +0x24
					float timeEnd;  // +0x28
					float turningVelocity;  // +0x2C
					float velocityXZMax;  // +0x30
					float velocityXZMin;  // +0x34
					int priority;  // +0x38
			};

			extern fight::Property** gFlyingGroundAttackTrackProperties;
			fight::TrackFactory* CreateFlyingGroundAttackTrackFactory(const char* name);
			void RegisterFlyingGroundAttackTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::motion::FlyingGroundAttackAction (9 vftable slots, 0x2C bytes)
			class FlyingGroundAttackAction : public fight::Action
			{
			public:
				// 0x100BF5B0
				FlyingGroundAttackAction(FlyingGroundAttackTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x100BF4A0
				virtual ~FlyingGroundAttackAction();

				// vftable slot 5 (0x100BF660)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x100BF4E0)
				virtual void Slot6();
				// vftable slot 7 (0x100BF880)
				virtual bool Slot7(int arg, float value);

				core::Link<FlyingGroundAttackTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				choreo::RootDriver* driver;  // +0x2C
				engine::HandleBase unknown30;  // +0x30
				float unknown34;  // +0x34
				float unknown38;  // +0x38
			};

			// ---- actions end
		}
	}
}

#endif
