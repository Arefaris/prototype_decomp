// Fight items of the motion group: SkidTrack, SkidPedalTrack (unit 0x101B22B0 - 0x101B3470; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_SKID_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_SKID_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::SkidTrack (16 vftable slots, 0x3C bytes)
			class SkidTrack : public fight::Track
			{
			public:
				// 0x101B25C0
				SkidTrack();
				virtual ~SkidTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10115B70, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetVelocityInit(float newValue);
				bool SetVelocityMin(float newValue);
				bool SetVelocityMax(float newValue);
				bool SetDecelerationMin(float newValue);
				bool SetDecelerationMax(float newValue);
				bool SetSprintVelocityDeceleration(float newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float blendInTime;  // +0x10
					float blendOutTime;  // +0x14
					float decelerationMax;  // +0x18
					float decelerationMin;  // +0x1C
					float sprintVelocityDeceleration;  // +0x20
					float timeBegin;  // +0x24
					float timeEnd;  // +0x28
					float velocityInit;  // +0x2C
					float velocityMax;  // +0x30
					float velocityMin;  // +0x34
					int priority;  // +0x38
			};

			extern fight::Property** gSkidTrackProperties;
			fight::TrackFactory* CreateSkidTrackFactory(const char* name);
			void RegisterSkidTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::SkidPedalTrack (16 vftable slots, 0x68 bytes)
			class SkidPedalTrack : public fight::Track
			{
			public:
				// 0x101B2770
				SkidPedalTrack();
				virtual ~SkidPedalTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10115BC0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEndMin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetAcceleration(float newValue);
				bool SetVelocityMin(float newValue);
				bool SetVelocityMax(float newValue);
				bool SetTurnVelocityMin(float newValue);
				bool SetTurnVelocityMax(float newValue);
				bool SetTurnAccelerationMin(float newValue);
				bool SetTurnAccelerationMax(float newValue);
				bool SetAnimNorth(const fight::Name& newValue);
				bool SetAnimWest(const fight::Name& newValue);
				bool SetAnimSouth(const fight::Name& newValue);
				bool SetAnimEast(const fight::Name& newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name animEast;  // +0x10
					fight::Name animNorth;  // +0x18
					fight::Name animSouth;  // +0x20
					fight::Name animWest;  // +0x28
					float acceleration;  // +0x30
					float blendInTime;  // +0x34
					float blendOutTime;  // +0x38
					float timeBegin;  // +0x3C
					float timeEnd;  // +0x40
					float timeEndMin;  // +0x44
					float turnAccelerationMax;  // +0x48
					float turnAccelerationMin;  // +0x4C
					float turnVelocityMax;  // +0x50
					float turnVelocityMin;  // +0x54
					float velocityMax;  // +0x58
					float velocityMin;  // +0x5C
					int priority;  // +0x60
					unsigned char unknown64[0x4];
			};

			extern fight::Property** gSkidPedalTrackProperties;
			fight::TrackFactory* CreateSkidPedalTrackFactory(const char* name);
			void RegisterSkidPedalTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
