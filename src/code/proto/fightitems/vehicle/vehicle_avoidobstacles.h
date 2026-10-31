// Fight items of the vehicle group: AvoidObstaclesTrack (unit 0x10276170 - 0x1027A6F0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_VEHICLE_VEHICLE_AVOIDOBSTACLES_H
#define PROTO_FIGHTITEMS_VEHICLE_VEHICLE_AVOIDOBSTACLES_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/ai/aiaction.h"
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

			// ---- actions begin
			// RTTI: proto::fightitems::vehicle::AvoidObstaclesAction (9 vftable slots, 0x2C bytes)
			class AvoidObstaclesAction : public fight::Action
			{
			public:
				// 0x10276860
				AvoidObstaclesAction(AvoidObstaclesTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x102765D0
				virtual ~AvoidObstaclesAction();

				// vftable slot 5 (0x10276600)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x10276330)
				virtual void Slot6();
				// vftable slot 7 (0x10276A10)
				virtual bool Slot7(int arg, float value);

				core::Link<AvoidObstaclesTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				float unknown2C;  // +0x2C
				float unknown30;  // +0x30
				float unknown34;  // +0x34
				float unknown38;  // +0x38
				float unknown3C;  // +0x3C
				bool unknown40;  // +0x40
				unsigned char unknown41[0x3];
				int unknown44;  // +0x44
			};

			// ---- actions end
		}
	}
}

#endif
