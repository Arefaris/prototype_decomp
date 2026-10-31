// Fight items of the ai group: ConditionalExecuteTrack (unit 0x10226DB0 - 0x102272B0; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_conditionalexecute.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gConditionalExecuteTrackProperties;  // 0x112558F0

			// FUNCTION: ENGINE 0x10226DB0
			bool ConditionalExecuteTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10226DD0
			bool ConditionalExecuteTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10226DF0
			fight::BranchHolder* ConditionalExecuteTrack::SetBranch()
			{
				return &branch;
			}

			// FUNCTION: ENGINE 0x10226E00
			fight::ConditionList* ConditionalExecuteTrack::SetConditions()
			{
				return &conditions;
			}

			// FUNCTION: ENGINE 0x10226E10
			fight::Property* ConditionalExecuteTrack::GetProperty(int index)
			{
				return gConditionalExecuteTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10226E30
			void ConditionalExecuteTrack::ClearProperties()
			{
				fight::FreePropertyList(&gConditionalExecuteTrackProperties);
			}

			// FUNCTION: ENGINE 0x10226E40
			ConditionalExecuteTrack::ConditionalExecuteTrack() : branch(0), timeBegin(0.0f), timeEnd(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x10226E90
			float ConditionalExecuteTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10226EA0
			float ConditionalExecuteTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10226EB0
			ConditionalExecuteTrack::~ConditionalExecuteTrack()
			{
			}

			// FUNCTION: ENGINE 0x10227090
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ConditionalExecuteTrack::RegisterProperties()
			{
				if (gConditionalExecuteTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ConditionalExecuteTrack>("timeBegin", &ConditionalExecuteTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ConditionalExecuteTrack>("timeEnd", &ConditionalExecuteTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyBranch<ConditionalExecuteTrack>("branch", &ConditionalExecuteTrack::SetBranch);
					properties[2] = property;
					property = new fight::PropertyConditionGroup<ConditionalExecuteTrack>("conditions", &ConditionalExecuteTrack::SetConditions);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gConditionalExecuteTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10227060
			fight::TrackFactory* CreateConditionalExecuteTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ConditionalExecuteTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102271E0
			void RegisterConditionalExecuteTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ConditionalExecuteTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin

			// ---- actions end
			template class fight::PropertyFloatConstRange<ConditionalExecuteTrack>;
			template class fight::PropertyBranch<ConditionalExecuteTrack>;
			template class fight::PropertyConditionGroup<ConditionalExecuteTrack>;
			template class fight::TrackFactoryTemplate<ConditionalExecuteTrack>;
			template class fight::TrackFactoryCasterTemplate<ConditionalExecuteTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10226EE0
// FUNCTION: ENGINE 0x10226F10
// FUNCTION: ENGINE 0x10226F20
// FUNCTION: ENGINE 0x10226F50
// FUNCTION: ENGINE 0x10226F80
// FUNCTION: ENGINE 0x10226FB0
// FUNCTION: ENGINE 0x10226FC0
// FUNCTION: ENGINE 0x10226FF0
// FUNCTION: ENGINE 0x10227010
// FUNCTION: ENGINE 0x10227040
// FUNCTION: ENGINE 0x10227210
// FUNCTION: ENGINE 0x10227240
// FUNCTION: ENGINE 0x10227260
