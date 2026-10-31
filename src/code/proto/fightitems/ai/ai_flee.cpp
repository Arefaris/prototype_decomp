// Fight items of the ai group: FleeTrack (unit 0x10231FB0 - 0x10232390; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_flee.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gFleeTrackProperties;  // 0x112559E0

			// FUNCTION: ENGINE 0x10231FB0
			bool FleeTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10231FD0
			bool FleeTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10231FF0
			bool FleeTrack::SetFleeDistance(float newValue)
			{
				fleeDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10232010
			fight::Property* FleeTrack::GetProperty(int index)
			{
				return gFleeTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10232030
			void FleeTrack::ClearProperties()
			{
				fight::FreePropertyList(&gFleeTrackProperties);
			}

			// FUNCTION: ENGINE 0x10232040
			FleeTrack::FleeTrack() : fleeDistance(0.0f), timeBegin(0.0f), timeEnd(0.0f)
			{
			}

			// FUNCTION: ENGINE 0x10232070
			float FleeTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10232080
			float FleeTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10232090
			FleeTrack::~FleeTrack()
			{
			}

			// FUNCTION: ENGINE 0x102321B0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void FleeTrack::RegisterProperties()
			{
				if (gFleeTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<FleeTrack>("timeBegin", &FleeTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<FleeTrack>("timeEnd", &FleeTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<FleeTrack>("fleeDistance", &FleeTrack::SetFleeDistance);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gFleeTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10232180
			fight::TrackFactory* CreateFleeTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<FleeTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102322C0
			void RegisterFleeTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<FleeTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin

			// ---- actions end
			template class fight::PropertyFloatConstRange<FleeTrack>;
			template class fight::TrackFactoryTemplate<FleeTrack>;
			template class fight::TrackFactoryCasterTemplate<FleeTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102320A0
// FUNCTION: ENGINE 0x102320D0
// FUNCTION: ENGINE 0x102320E0
// FUNCTION: ENGINE 0x10232110
// FUNCTION: ENGINE 0x10232140
// FUNCTION: ENGINE 0x10232170
// FUNCTION: ENGINE 0x102322F0
// FUNCTION: ENGINE 0x10232320
// FUNCTION: ENGINE 0x10232340
