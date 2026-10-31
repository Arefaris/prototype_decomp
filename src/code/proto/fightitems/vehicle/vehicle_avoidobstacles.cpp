// Fight items of the vehicle group: AvoidObstaclesTrack (unit 0x10276170 - 0x1027A6F0; no assert path, the file name is a guess).
#include "code/proto/fightitems/vehicle/vehicle_avoidobstacles.h"

namespace proto
{
	namespace fightitems
	{
		namespace vehicle
		{
			fight::Property** gAvoidObstaclesTrackProperties;  // 0x1125618C

			// FUNCTION: ENGINE 0x1027A1F0
			bool AvoidObstaclesTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027A210
			bool AvoidObstaclesTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027A230
			fight::BranchHolder* AvoidObstaclesTrack::SetMyBranch()
			{
				return &myBranch;
			}

			// FUNCTION: ENGINE 0x1027A240
			bool AvoidObstaclesTrack::SetGiveUpWithNoGapFound(bool newValue)
			{
				giveUpWithNoGapFound = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027A250
			fight::Property* AvoidObstaclesTrack::GetProperty(int index)
			{
				return gAvoidObstaclesTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1027A270
			void AvoidObstaclesTrack::ClearProperties()
			{
				fight::FreePropertyList(&gAvoidObstaclesTrackProperties);
			}

			// FUNCTION: ENGINE 0x1027A280
			AvoidObstaclesTrack::AvoidObstaclesTrack() : myBranch(0), timeBegin(0.0f), timeEnd(-1.0f), giveUpWithNoGapFound(true)
			{
			}

			// FUNCTION: ENGINE 0x1027A2D0
			float AvoidObstaclesTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1027A2E0
			float AvoidObstaclesTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1027A2F0
			AvoidObstaclesTrack::~AvoidObstaclesTrack()
			{
			}

			// FUNCTION: ENGINE 0x1027A4D0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void AvoidObstaclesTrack::RegisterProperties()
			{
				if (gAvoidObstaclesTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<AvoidObstaclesTrack>("timeBegin", &AvoidObstaclesTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<AvoidObstaclesTrack>("timeEnd", &AvoidObstaclesTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyBranch<AvoidObstaclesTrack>("myBranch", &AvoidObstaclesTrack::SetMyBranch);
					properties[2] = property;
					property = new fight::PropertyBool<AvoidObstaclesTrack>("giveUpWithNoGapFound", &AvoidObstaclesTrack::SetGiveUpWithNoGapFound);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gAvoidObstaclesTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1027A4A0
			fight::TrackFactory* CreateAvoidObstaclesTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<AvoidObstaclesTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1027A620
			void RegisterAvoidObstaclesTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<AvoidObstaclesTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<AvoidObstaclesTrack>;
			template class fight::PropertyBranch<AvoidObstaclesTrack>;
			template class fight::PropertyBool<AvoidObstaclesTrack>;
			template class fight::TrackFactoryTemplate<AvoidObstaclesTrack>;
			template class fight::TrackFactoryCasterTemplate<AvoidObstaclesTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1027A310
// FUNCTION: ENGINE 0x1027A340
// FUNCTION: ENGINE 0x1027A350
// FUNCTION: ENGINE 0x1027A380
// FUNCTION: ENGINE 0x1027A3B0
// FUNCTION: ENGINE 0x1027A3E0
// FUNCTION: ENGINE 0x1027A3F0
// FUNCTION: ENGINE 0x1027A420
// FUNCTION: ENGINE 0x1027A440
// FUNCTION: ENGINE 0x1027A470
// FUNCTION: ENGINE 0x1027A490
// FUNCTION: ENGINE 0x1027A650
// FUNCTION: ENGINE 0x1027A680
// FUNCTION: ENGINE 0x1027A6A0
