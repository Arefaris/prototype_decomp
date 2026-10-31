// Fight items of the scenario group: StateMachineStopTrack (unit 0x101DB2A0 - 0x101DB630; no assert path, the file name is a guess).
#include "code/proto/fightitems/scenario/scenario_statemachinestop.h"

namespace proto
{
	namespace fightitems
	{
		namespace scenario
		{
			fight::Property** gStateMachineStopTrackProperties;  // 0x11254DD4

			// FUNCTION: ENGINE 0x101DB2A0
			bool StateMachineStopTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101DB2C0
			bool StateMachineStopTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101DB2E0
			fight::Property* StateMachineStopTrack::GetProperty(int index)
			{
				return gStateMachineStopTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101DB300
			void StateMachineStopTrack::ClearProperties()
			{
				fight::FreePropertyList(&gStateMachineStopTrackProperties);
			}

			// FUNCTION: ENGINE 0x101DB310
			StateMachineStopTrack::StateMachineStopTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x101DB340
			float StateMachineStopTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101DB350
			float StateMachineStopTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101DB360
			StateMachineStopTrack::~StateMachineStopTrack()
			{
			}

			// FUNCTION: ENGINE 0x101DB480
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void StateMachineStopTrack::RegisterProperties()
			{
				if (gStateMachineStopTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<StateMachineStopTrack>("timeBegin", &StateMachineStopTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<StateMachineStopTrack>("timeEnd", &StateMachineStopTrack::SetTimeEnd);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gStateMachineStopTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101DB450
			fight::TrackFactory* CreateStateMachineStopTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<StateMachineStopTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101DB560
			void RegisterStateMachineStopTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<StateMachineStopTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<StateMachineStopTrack>;
			template class fight::TrackFactoryTemplate<StateMachineStopTrack>;
			template class fight::TrackFactoryCasterTemplate<StateMachineStopTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101DB370
// FUNCTION: ENGINE 0x101DB3A0
// FUNCTION: ENGINE 0x101DB3B0
// FUNCTION: ENGINE 0x101DB3E0
// FUNCTION: ENGINE 0x101DB410
// FUNCTION: ENGINE 0x101DB440
// FUNCTION: ENGINE 0x101DB590
// FUNCTION: ENGINE 0x101DB5C0
// FUNCTION: ENGINE 0x101DB5E0
