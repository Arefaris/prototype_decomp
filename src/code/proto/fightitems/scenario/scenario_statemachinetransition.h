// Fight items of the scenario group: StateMachineTransitionTrack (unit 0x101DB630 - 0x101DBA70; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_SCENARIO_SCENARIO_STATEMACHINETRANSITION_H
#define PROTO_FIGHTITEMS_SCENARIO_SCENARIO_STATEMACHINETRANSITION_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/scenario/scenariodata.h"

namespace proto
{
	namespace fightitems
	{
		namespace scenario
		{
			// RTTI: proto::fightitems::scenario::StateMachineTransitionTrack (16 vftable slots, 0x3C bytes)
			class StateMachineTransitionTrack : public fight::Track
			{
			public:
				// 0x101DB6B0
				StateMachineTransitionTrack();
				virtual ~StateMachineTransitionTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101D8530, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				fight::BranchHolder* SetTransitionBranch();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder transitionBranch;  // +0x10
					float timeBegin;  // +0x34
					float timeEnd;  // +0x38
			};

			extern fight::Property** gStateMachineTransitionTrackProperties;
			fight::TrackFactory* CreateStateMachineTransitionTrackFactory(const char* name);
			void RegisterStateMachineTransitionTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
