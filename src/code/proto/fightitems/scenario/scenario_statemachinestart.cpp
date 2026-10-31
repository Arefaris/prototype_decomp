// Fight items of the scenario group: StateMachineStartTrack (unit 0x101DABA0 - 0x101DB2A0; no assert path, the file name is a guess).
#include "code/proto/fightitems/scenario/scenario_statemachinestart.h"
#include <new>

namespace proto
{
	namespace fightitems
	{
		namespace scenario
		{
			fight::Property** gStateMachineStartTrackProperties;  // 0x11254DD0

			// FUNCTION: ENGINE 0x101DABA0
			bool StateMachineStartTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101DABC0
			bool StateMachineStartTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101DACB0
			bool StateMachineStartTrack::SetName(const fight::Name& newValue)
			{
				name = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101DAC20
			bool StateMachineStartTrack::SetArgs(const char* newValue)
			{
				args = fight::ReplaceString(args, newValue);
				return true;
			}

			// FUNCTION: ENGINE 0x101DAC50
			bool StateMachineStartTrack::SetTags(const char* newValue)
			{
				tags = fight::ReplaceString(tags, newValue);
				return true;
			}

			// FUNCTION: ENGINE 0x101DAC80
			bool StateMachineStartTrack::SetChannel(const char* newValue)
			{
				channel = fight::ReplaceString(channel, newValue);
				return true;
			}

			// FUNCTION: ENGINE 0x101DABE0
			fight::BranchHolder* StateMachineStartTrack::SetStateMachineBranch()
			{
				return &stateMachineBranch;
			}

			// FUNCTION: ENGINE 0x101DABF0
			fight::Property* StateMachineStartTrack::GetProperty(int index)
			{
				return gStateMachineStartTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101DAC10
			void StateMachineStartTrack::ClearProperties()
			{
				fight::FreePropertyList(&gStateMachineStartTrackProperties);
			}

			// FUNCTION: ENGINE 0x101DACD0
			StateMachineStartTrack::StateMachineStartTrack() : stateMachineBranch(0), args(0), channel(0), tags(0), timeBegin(0.0f), timeEnd(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x101DAD40
			float StateMachineStartTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101DAD50
			float StateMachineStartTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101DAD60
			StateMachineStartTrack::~StateMachineStartTrack()
			{
				delete[] args;
				delete[] tags;
				delete[] channel;
			}

			// FUNCTION: ENGINE 0x101DAFF0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void StateMachineStartTrack::RegisterProperties()
			{
				if (gStateMachineStartTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<StateMachineStartTrack>("timeBegin", &StateMachineStartTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<StateMachineStartTrack>("timeEnd", &StateMachineStartTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyName<StateMachineStartTrack>("name", &StateMachineStartTrack::SetName);
					properties[2] = property;
					property = new fight::PropertyString<StateMachineStartTrack>("args", &StateMachineStartTrack::SetArgs);
					properties[3] = property;
					property = new fight::PropertyString<StateMachineStartTrack>("tags", &StateMachineStartTrack::SetTags);
					properties[4] = property;
					property = new fight::PropertyString<StateMachineStartTrack>("channel", &StateMachineStartTrack::SetChannel);
					properties[5] = property;
					property = new fight::PropertyBranch<StateMachineStartTrack>("stateMachineBranch", &StateMachineStartTrack::SetStateMachineBranch);
					properties[6] = property;
					fight::RegisterPropertyList(properties, &gStateMachineStartTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101DAF40
			fight::TrackFactory* CreateStateMachineStartTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<StateMachineStartTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101DAF70
			void RegisterStateMachineStartTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<StateMachineStartTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<StateMachineStartTrack>;
			template class fight::PropertyName<StateMachineStartTrack>;
			template class fight::PropertyString<StateMachineStartTrack>;
			template class fight::PropertyBranch<StateMachineStartTrack>;
			template class fight::TrackFactoryTemplate<StateMachineStartTrack>;
			template class fight::TrackFactoryCasterTemplate<StateMachineStartTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101DADB0
// FUNCTION: ENGINE 0x101DADC0
// FUNCTION: ENGINE 0x101DADF0
// FUNCTION: ENGINE 0x101DAE20
// FUNCTION: ENGINE 0x101DAE50
// FUNCTION: ENGINE 0x101DAE80
// FUNCTION: ENGINE 0x101DAE90
// FUNCTION: ENGINE 0x101DAEC0
// FUNCTION: ENGINE 0x101DAEE0
// FUNCTION: ENGINE 0x101DAEF0
// FUNCTION: ENGINE 0x101DAF20
// FUNCTION: ENGINE 0x101DAFA0
// FUNCTION: ENGINE 0x101DAFD0
// FUNCTION: ENGINE 0x101DB200
// FUNCTION: ENGINE 0x101DB230
// FUNCTION: ENGINE 0x101DB250
