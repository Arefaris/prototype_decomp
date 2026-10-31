// Fight items of the vehicle group: AvoidObstaclesTrack (unit 0x10276170 - 0x1027A6F0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_VEHICLE_VEHICLE_AVOIDOBSTACLES_H
#define PROTO_FIGHTITEMS_VEHICLE_VEHICLE_AVOIDOBSTACLES_H

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
			// RTTI: proto::fightitems::vehicle::AvoidObstaclesTrack (16 vftable slots, 0x40 bytes)
			class AvoidObstaclesTrack : public fight::Track
			{
			public:
				// 0x1027A280
				AvoidObstaclesTrack();
				virtual ~AvoidObstaclesTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x102769B0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				fight::BranchHolder* SetMyBranch();
				bool SetGiveUpWithNoGapFound(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder myBranch;  // +0x10
					float timeBegin;  // +0x34
					float timeEnd;  // +0x38
					bool giveUpWithNoGapFound;  // +0x3C
					unsigned char unknown3D[0x3];
			};

			extern fight::Property** gAvoidObstaclesTrackProperties;
			fight::TrackFactory* CreateAvoidObstaclesTrackFactory(const char* name);
			void RegisterAvoidObstaclesTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
