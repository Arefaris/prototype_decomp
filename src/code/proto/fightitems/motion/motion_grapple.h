// Fight items of the motion group: GrappleLocoSprintTrack, GrappleLocoSteerTrack (unit 0x10173B80 - 0x10174CA0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_GRAPPLE_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_GRAPPLE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::GrappleLocoSprintTrack (16 vftable slots, 0x58 bytes)
			class GrappleLocoSprintTrack : public fight::Track
			{
			public:
				// 0x10173F00
				GrappleLocoSprintTrack();
				virtual ~GrappleLocoSprintTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100CDDD0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetLocomotion(const fight::Name& newValue);
				bool SetAnimRun(const fight::Name& newValue);
				bool SetAnimLeanEast(const fight::Name& newValue);
				bool SetAnimLeanWest(const fight::Name& newValue);
				bool SetSyncFrameRun(float newValue);
				bool SetSyncFrameLeanEast(float newValue);
				bool SetSyncFrameLeanWest(float newValue);
				bool SetPartition(const fight::Name& newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name animLeanEast;  // +0x10
					fight::Name animLeanWest;  // +0x18
					fight::Name animRun;  // +0x20
					fight::Name locomotion;  // +0x28
					fight::Name partition;  // +0x30
					float blendInTime;  // +0x38
					float blendOutTime;  // +0x3C
					float syncFrameLeanEast;  // +0x40
					float syncFrameLeanWest;  // +0x44
					float syncFrameRun;  // +0x48
					float timeBegin;  // +0x4C
					float timeEnd;  // +0x50
					int priority;  // +0x54
			};

			extern fight::Property** gGrappleLocoSprintTrackProperties;
			fight::TrackFactory* CreateGrappleLocoSprintTrackFactory(const char* name);
			void RegisterGrappleLocoSprintTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GrappleLocoSteerTrack (16 vftable slots, 0x58 bytes)
			class GrappleLocoSteerTrack : public fight::Track
			{
			public:
				// 0x10173FC0
				GrappleLocoSteerTrack();
				virtual ~GrappleLocoSteerTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100CDD80, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetLocomotion(const fight::Name& newValue);
				bool SetAnimIdle(const fight::Name& newValue);
				bool SetAnimWalk(const fight::Name& newValue);
				bool SetAnimRun(const fight::Name& newValue);
				bool SetSyncFrameIdle(float newValue);
				bool SetSyncFrameWalk(float newValue);
				bool SetSyncFrameRun(float newValue);
				bool SetPartition(const fight::Name& newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name animIdle;  // +0x10
					fight::Name animRun;  // +0x18
					fight::Name animWalk;  // +0x20
					fight::Name locomotion;  // +0x28
					fight::Name partition;  // +0x30
					float blendInTime;  // +0x38
					float blendOutTime;  // +0x3C
					float syncFrameIdle;  // +0x40
					float syncFrameRun;  // +0x44
					float syncFrameWalk;  // +0x48
					float timeBegin;  // +0x4C
					float timeEnd;  // +0x50
					int priority;  // +0x54
			};

			extern fight::Property** gGrappleLocoSteerTrackProperties;
			fight::TrackFactory* CreateGrappleLocoSteerTrackFactory(const char* name);
			void RegisterGrappleLocoSteerTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
