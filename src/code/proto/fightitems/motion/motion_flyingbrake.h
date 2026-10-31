// Fight items of the motion group: FlyingBrakeTrack (unit 0x1015FAE0 - 0x101601F0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_FLYINGBRAKE_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_FLYINGBRAKE_H

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
			// RTTI: proto::fightitems::motion::FlyingBrakeTrack (16 vftable slots, 0x38 bytes)
			class FlyingBrakeTrack : public fight::Track
			{
			public:
				// 0x1015FC40
				FlyingBrakeTrack();
				virtual ~FlyingBrakeTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100BE8E0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetVelocityXZ(float newValue);
				bool SetGravity(float newValue);
				bool SetGravityUp(float newValue);
				bool SetTerminalVelocity(float newValue);
				bool SetVelocityUp(float newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float blendInTime;  // +0x10
					float blendOutTime;  // +0x14
					float gravity;  // +0x18
					float gravityUp;  // +0x1C
					float terminalVelocity;  // +0x20
					float timeBegin;  // +0x24
					float timeEnd;  // +0x28
					float velocityUp;  // +0x2C
					float velocityXZ;  // +0x30
					int priority;  // +0x34
			};

			extern fight::Property** gFlyingBrakeTrackProperties;
			fight::TrackFactory* CreateFlyingBrakeTrackFactory(const char* name);
			void RegisterFlyingBrakeTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::motion::FlyingBrakeAction (9 vftable slots, 0x2C bytes)
			class FlyingBrakeAction : public fight::Action
			{
			public:
				// 0x100BE320
				FlyingBrakeAction(FlyingBrakeTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x100BE200
				virtual ~FlyingBrakeAction();

				// vftable slot 5 (0x100BE3F0)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x100BE240)
				virtual void Slot6();
				// vftable slot 7 (0x100BE700)
				virtual bool Slot7(int arg, float value);

				core::Link<FlyingBrakeTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				choreo::RootDriver* driver;  // +0x2C
				math::Vector unknown30;  // +0x30
				math::Vector unknown3C;  // +0x3C
				float unknown48;  // +0x48
			};

			// ---- actions end
		}
	}
}

#endif
