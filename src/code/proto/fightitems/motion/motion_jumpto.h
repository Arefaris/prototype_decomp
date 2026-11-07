// Fight items of the motion group: JumpToTrack (unit 0x10185900 - 0x101865E0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_JUMPTO_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_JUMPTO_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"
#include "code/proto/fightitems/motion/motion_boundary.h"
#include "code/engine/physics/collisioncallback.h"
#include "code/choreo/rootdriver.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::JumpToTrack (16 vftable slots, 0x68 bytes)
			class JumpToTrack : public fight::Track
			{
			public:
				// 0x10185B90
				JumpToTrack();
				virtual ~JumpToTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100E2280, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetUseTarget(bool newValue);
				bool SetChargeType(int newValue);
				bool SetDistanceMin(float newValue);
				bool SetDistanceMax(float newValue);
				bool SetUseDistanceWhenUsingTarget(bool newValue);
				bool SetMinInitialVelocityMin(float newValue);
				bool SetMinInitialVelocityMax(float newValue);
				bool SetMaxInitialVelocityMin(float newValue);
				bool SetMaxInitialVelocityMax(float newValue);
				bool SetTrackingMin(float newValue);
				bool SetTrackingMax(float newValue);
				bool SetMinSpeedTracking(float newValue);
				bool SetLaunchAngle(float newValue);
				bool SetMinLaunchAngle(float newValue);
				bool SetGravity(float newValue);
				bool SetOffset(const math::Vector& newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Vector offset;  // +0x10
					float blendInTime;  // +0x1C
					float blendOutTime;  // +0x20
					float distanceMax;  // +0x24
					float distanceMin;  // +0x28
					float gravity;  // +0x2C
					float launchAngle;  // +0x30
					float maxInitialVelocityMax;  // +0x34
					float maxInitialVelocityMin;  // +0x38
					float minInitialVelocityMax;  // +0x3C
					float minInitialVelocityMin;  // +0x40
					float minLaunchAngle;  // +0x44
					float minSpeedTracking;  // +0x48
					float timeBegin;  // +0x4C
					float timeEnd;  // +0x50
					float trackingMax;  // +0x54
					float trackingMin;  // +0x58
					int chargeType;  // +0x5C
					int priority;  // +0x60
					bool useDistanceWhenUsingTarget;  // +0x64
					bool useTarget;  // +0x65
					unsigned char unknown66[0x2];
			};

			extern fight::Property** gJumpToTrackProperties;
			fight::TrackFactory* CreateJumpToTrackFactory(const char* name);
			void RegisterJumpToTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::motion::JumpToAction (9 vftable slots, 0x74 bytes)
			class JumpToAction : public fight::Action
			{
			public:
				// RTTI: proto::fightitems::motion::JumpToAction::JumpToCollisionCallback (0x18 bytes): tells the action that the object collided
				class JumpToCollisionCallback : public engine::CollisionResponseCallback
				{
				public:
					JumpToCollisionCallback() : owner(0)
					{
					}
					// vftable slot 0 (0x100E1140): the compiler's destructor
					// vftable slot 1 (0x100E1170)
					virtual void OnCollision(int first, int second, int third);

					JumpToAction* owner;  // +0x14
				};

				// 0x100E1680
				JumpToAction(JumpToTrack* newTrack, core::IRefCount* owner);
				// 0x100E1260
				virtual ~JumpToAction();

				// vftable slot 5 (0x100E29A0, not reconstructed)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x100E12B0)
				virtual void Slot6();
				// vftable slot 7 (0x100E2B70, not reconstructed)
				virtual bool Slot7(int arg, float value);

				// 0x100E0EF0: a collision happened (the arguments are not known)
				void OnCollision(int first, int second, int third);

				core::Link<JumpToTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				JumpDestination destination;  // +0x2C
				JumpToCollisionCallback callback;  // +0x3C
				bool collided;  // +0x54
				choreo::Driver* driver;  // +0x58
				float unknown5C;
				float unknown60;
				float unknown64;
				float unknown68;
				float unknown6C;
				bool unknown70;
			};

			// ---- actions end

		}
	}
}

#endif
