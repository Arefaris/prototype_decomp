// Fight items of the motion group: FlyingAttackTrack (unit 0x1015F0E0 - 0x1015FAE0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_FLYINGATTACK_H
#define PROTO_FIGHTITEMS_MOTION_FLYINGATTACK_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"
#include "code/choreo/rootdriver.h"
#include "code/engine/fight/expressionactions.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::FlyingAttackTrack (16 vftable slots, 0x50 bytes)
			class FlyingAttackTrack : public fight::Track
			{
			public:
				// 0x1015F2D0
				FlyingAttackTrack();
				virtual ~FlyingAttackTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100BE080, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEndMin(float newValue);
				bool SetTimeEndMax(float newValue);
				bool SetDirection(const math::Vector& newValue);
				bool SetVelocityMin(float newValue);
				bool SetVelocityMax(float newValue);
				bool SetAccelerationMin(float newValue);
				bool SetAccelerationMax(float newValue);
				bool SetTrackingMin(float newValue);
				bool SetTrackingMax(float newValue);
				bool SetFaceDirection(bool newValue);
				bool SetUseAutoTarget(bool newValue);
				bool SetSlideOnGround(bool newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Vector direction;  // +0x10
					float accelerationMax;  // +0x1C
					float accelerationMin;  // +0x20
					float blendInTime;  // +0x24
					float blendOutTime;  // +0x28
					float timeBegin;  // +0x2C
					float timeEndMax;  // +0x30
					float timeEndMin;  // +0x34
					float trackingMax;  // +0x38
					float trackingMin;  // +0x3C
					float velocityMax;  // +0x40
					float velocityMin;  // +0x44
					int priority;  // +0x48
					bool faceDirection;  // +0x4C
					bool slideOnGround;  // +0x4D
					bool useAutoTarget;  // +0x4E
					unsigned char unknown4F[0x1];
			};

			extern fight::Property** gFlyingAttackTrackProperties;
			fight::TrackFactory* CreateFlyingAttackTrackFactory(const char* name);
			void RegisterFlyingAttackTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::motion::FlyingAttackAction (9 vftable slots, 0x2C bytes)
			class FlyingAttackAction : public fight::Action
			{
			public:
				// 0x100BD500
				FlyingAttackAction(FlyingAttackTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x100BD430
				virtual ~FlyingAttackAction();

				// vftable slot 5 (0x100BD5D0)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x100BE020)
				virtual void Slot6();
				// 0x100BD470 (another function of this unit): forgets the object the action looks at (name guess)
				void ClearTargetHandle();
				// vftable slot 7 (0x100BDA10)
				virtual bool Slot7(int arg, float value);

				core::Link<FlyingAttackTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				choreo::RootDriver* driver;  // +0x2C
				engine::HandleBase unknown30;  // +0x30
				math::Vector unknown34;  // +0x34

				float unknown40;  // +0x40
				float unknown44;  // +0x44
				float unknown48;  // +0x48
				float unknown4C;  // +0x4C
			};

			// ---- actions end
		}
	}
}

#endif
