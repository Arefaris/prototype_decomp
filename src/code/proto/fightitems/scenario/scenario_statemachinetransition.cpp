// Fight items of the scenario group: StateMachineTransitionTrack (unit 0x101DB630 - 0x101DBA70; no assert path, the file name is a guess).
#include "code/proto/fightitems/scenario/scenario_statemachinetransition.h"

namespace proto
{
	namespace fightitems
	{
		namespace scenario
		{
			fight::Property** gStateMachineTransitionTrackProperties;  // 0x11254DD8

			// FUNCTION: ENGINE 0x101DB630
			bool StateMachineTransitionTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101DB650
			bool StateMachineTransitionTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101DB670
			fight::BranchHolder* StateMachineTransitionTrack::SetTransitionBranch()
			{
				return &transitionBranch;
			}

			// FUNCTION: ENGINE 0x101DB680
			fight::Property* StateMachineTransitionTrack::GetProperty(int index)
			{
				return gStateMachineTransitionTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101DB6A0
			void StateMachineTransitionTrack::ClearProperties()
			{
				fight::FreePropertyList(&gStateMachineTransitionTrackProperties);
			}

			// FUNCTION: ENGINE 0x101DB6B0
			StateMachineTransitionTrack::StateMachineTransitionTrack() : transitionBranch(0), timeBegin(0.0f), timeEnd(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x101DB6F0
			float StateMachineTransitionTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101DB700
			float StateMachineTransitionTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101DB710
			StateMachineTransitionTrack::~StateMachineTransitionTrack()
			{
			}

			// FUNCTION: ENGINE 0x101DB890
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void StateMachineTransitionTrack::RegisterProperties()
			{
				if (gStateMachineTransitionTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<StateMachineTransitionTrack>("timeBegin", &StateMachineTransitionTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<StateMachineTransitionTrack>("timeEnd", &StateMachineTransitionTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyBranch<StateMachineTransitionTrack>("transitionBranch", &StateMachineTransitionTrack::SetTransitionBranch);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gStateMachineTransitionTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101DB860
			fight::TrackFactory* CreateStateMachineTransitionTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<StateMachineTransitionTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101DB9A0
			void RegisterStateMachineTransitionTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<StateMachineTransitionTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<StateMachineTransitionTrack>;
			template class fight::PropertyBranch<StateMachineTransitionTrack>;
			template class fight::TrackFactoryTemplate<StateMachineTransitionTrack>;
			template class fight::TrackFactoryCasterTemplate<StateMachineTransitionTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101DB730
// FUNCTION: ENGINE 0x101DB760
// FUNCTION: ENGINE 0x101DB770
// FUNCTION: ENGINE 0x101DB7A0
// FUNCTION: ENGINE 0x101DB7D0
// FUNCTION: ENGINE 0x101DB800
// FUNCTION: ENGINE 0x101DB810
// FUNCTION: ENGINE 0x101DB840
// FUNCTION: ENGINE 0x101DB9D0
// FUNCTION: ENGINE 0x101DBA00
// FUNCTION: ENGINE 0x101DBA20
