// Fight items of the motion group: LocoStrafeTrack (unit 0x1018C680 - 0x1018D500; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_LOCOSTRAFE_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_LOCOSTRAFE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::LocoStrafeTrack (16 vftable slots, 0xA8 bytes)
			class LocoStrafeTrack : public fight::Track
			{
			public:
				// 0x1018CA00
				LocoStrafeTrack();
				virtual ~LocoStrafeTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100EC160, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetAcceleration(float newValue);
				bool SetTurningVelocity(float newValue);
				bool SetFixedFacing(bool newValue);
				bool SetVelocityWalkNorth(float newValue);
				bool SetVelocityWalkStrafe(float newValue);
				bool SetVelocityWalkSouth(float newValue);
				bool SetVelocityRunNorth(float newValue);
				bool SetVelocityRunStrafe(float newValue);
				bool SetVelocityRunSouth(float newValue);
				bool SetPhase(float newValue);
				bool SetLocomotion(const fight::Name& newValue);
				bool SetAnimIdle(const fight::Name& newValue);
				bool SetAnimWalkNorth(const fight::Name& newValue);
				bool SetAnimWalkEast(const fight::Name& newValue);
				bool SetAnimWalkSouth(const fight::Name& newValue);
				bool SetAnimWalkWest(const fight::Name& newValue);
				bool SetAnimRunNorth(const fight::Name& newValue);
				bool SetAnimRunEast(const fight::Name& newValue);
				bool SetAnimRunSouth(const fight::Name& newValue);
				bool SetAnimRunWest(const fight::Name& newValue);
				bool SetPartition(const fight::Name& newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name animIdle;  // +0x10
					fight::Name animRunEast;  // +0x18
					fight::Name animRunNorth;  // +0x20
					fight::Name animRunSouth;  // +0x28
					fight::Name animRunWest;  // +0x30
					fight::Name animWalkEast;  // +0x38
					fight::Name animWalkNorth;  // +0x40
					fight::Name animWalkSouth;  // +0x48
					fight::Name animWalkWest;  // +0x50
					fight::Name locomotion;  // +0x58
					fight::Name partition;  // +0x60
					float acceleration;  // +0x68
					float blendInTime;  // +0x6C
					float blendOutTime;  // +0x70
					float phase;  // +0x74
					float timeBegin;  // +0x78
					float timeEnd;  // +0x7C
					float turningVelocity;  // +0x80
					float velocityRunNorth;  // +0x84
					float velocityRunSouth;  // +0x88
					float velocityRunStrafe;  // +0x8C
					float velocityWalkNorth;  // +0x90
					float velocityWalkSouth;  // +0x94
					float velocityWalkStrafe;  // +0x98
					int priority;  // +0x9C
					bool fixedFacing;  // +0xA0
					unsigned char unknownA1[0x7];
			};

			extern fight::Property** gLocoStrafeTrackProperties;
			fight::TrackFactory* CreateLocoStrafeTrackFactory(const char* name);
			void RegisterLocoStrafeTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
