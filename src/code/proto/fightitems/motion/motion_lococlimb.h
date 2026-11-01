// Fight items of the motion group: LocoClimbTrack (unit 0x10187C50 - 0x10188680; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_LOCOCLIMB_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_LOCOCLIMB_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::LocoClimbTrack (16 vftable slots, 0x70 bytes)
			class LocoClimbTrack : public fight::Track
			{
			public:
				// 0x10187E90
				LocoClimbTrack();
				virtual ~LocoClimbTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100E5C30, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetAcceleration(float newValue);
				bool SetVelocityNorth(float newValue);
				bool SetVelocityStrafe(float newValue);
				bool SetVelocitySouth(float newValue);
				bool SetPhase(float newValue);
				bool SetLocomotion(const fight::Name& newValue);
				bool SetAnimIdle(const fight::Name& newValue);
				bool SetAnimNorth(const fight::Name& newValue);
				bool SetAnimEast(const fight::Name& newValue);
				bool SetAnimSouth(const fight::Name& newValue);
				bool SetAnimWest(const fight::Name& newValue);
				bool SetPartition(const fight::Name& newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name animEast;  // +0x10
					fight::Name animIdle;  // +0x18
					fight::Name animNorth;  // +0x20
					fight::Name animSouth;  // +0x28
					fight::Name animWest;  // +0x30
					fight::Name locomotion;  // +0x38
					fight::Name partition;  // +0x40
					float acceleration;  // +0x48
					float blendInTime;  // +0x4C
					float blendOutTime;  // +0x50
					float phase;  // +0x54
					float timeBegin;  // +0x58
					float timeEnd;  // +0x5C
					float velocityNorth;  // +0x60
					float velocitySouth;  // +0x64
					float velocityStrafe;  // +0x68
					int priority;  // +0x6C
			};

			extern fight::Property** gLocoClimbTrackProperties;
			fight::TrackFactory* CreateLocoClimbTrackFactory(const char* name);
			void RegisterLocoClimbTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::motion::LocoClimbAction (9 vftable slots, 0x40 bytes)
			class LocoClimbAction : public fight::Action
			{
			public:
				// 0x100E5130
				LocoClimbAction(LocoClimbTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x100E5010
				virtual ~LocoClimbAction();

				// vftable slot 5 (0x100E53B0)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x100E5050)
				virtual void Slot6();
				// vftable slot 7 (0x100E5680)
				virtual bool Slot7(int arg, float value);

				core::Link<LocoClimbTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				choreo::Driver* driver;  // +0x2C
				unsigned char unknown30[0x10];
			};

			// ---- actions end
		}
	}
}

#endif
