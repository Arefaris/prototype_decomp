// Fight items of the vehicle group: FishTailTrack, EBrakeTrack (unit 0x1027B0F0 - 0x1027BF20; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_VEHICLE_VEHICLE_FISHTAIL_H
#define PROTO_FIGHTITEMS_VEHICLE_VEHICLE_FISHTAIL_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/scenario/scenariodata.h"
#include "code/proto/fightitems/ai/aidata.h"
#include "code/proto/fightitems/vehicle/vehicledata.h"

namespace proto
{
	namespace fightitems
	{
		namespace vehicle
		{
			// RTTI: proto::fightitems::vehicle::FishTailTrack (16 vftable slots, 0x5C bytes)
			class FishTailTrack : public fight::Track
			{
			public:
				// 0x1027B380
				FishTailTrack();
				virtual ~FishTailTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10278970, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetMinTimeDelay(float newValue);
				bool SetMaxTimeDelay(float newValue);
				bool SetTurning(float newValue);
				bool SetDesiredVelocity(float newValue);
				bool SetAccelration(float newValue);
				bool SetBraking(float newValue);
				bool SetSkidSeverity(float newValue);
				bool SetFishTailSeverity(float newValue);
				fight::BranchHolder* SetMyBranch();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder myBranch;  // +0x10
					float accelration;  // +0x34
					float braking;  // +0x38
					float desiredVelocity;  // +0x3C
					float fishTailSeverity;  // +0x40
					float maxTimeDelay;  // +0x44
					float minTimeDelay;  // +0x48
					float skidSeverity;  // +0x4C
					float timeBegin;  // +0x50
					float timeEnd;  // +0x54
					float turning;  // +0x58
			};

			extern fight::Property** gFishTailTrackProperties;
			fight::TrackFactory* CreateFishTailTrackFactory(const char* name);
			void RegisterFishTailTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::vehicle::EBrakeTrack (16 vftable slots, 0x54 bytes)
			class EBrakeTrack : public fight::Track
			{
			public:
				// 0x1027B480
				EBrakeTrack();
				virtual ~EBrakeTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10278920, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetMinTimeDelay(float newValue);
				bool SetMaxTimeDelay(float newValue);
				bool SetTurningSpeed(float newValue);
				bool SetBraking(float newValue);
				bool SetTurningAmount(float newValue);
				bool SetSkidSeverity(float newValue);
				fight::BranchHolder* SetMyBranch();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder myBranch;  // +0x10
					float braking;  // +0x34
					float maxTimeDelay;  // +0x38
					float minTimeDelay;  // +0x3C
					float skidSeverity;  // +0x40
					float timeBegin;  // +0x44
					float timeEnd;  // +0x48
					float turningAmount;  // +0x4C
					float turningSpeed;  // +0x50
			};

			extern fight::Property** gEBrakeTrackProperties;
			fight::TrackFactory* CreateEBrakeTrackFactory(const char* name);
			void RegisterEBrakeTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
