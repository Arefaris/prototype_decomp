// Fight items of the scenario group: StateMachineStartTrack (unit 0x101DABA0 - 0x101DB2A0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_SCENARIO_SCENARIO_STATEMACHINESTART_H
#define PROTO_FIGHTITEMS_SCENARIO_SCENARIO_STATEMACHINESTART_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/scenario/scenariodata.h"

namespace proto
{
	namespace fightitems
	{
		namespace scenario
		{
			// RTTI: proto::fightitems::scenario::StateMachineStartTrack (16 vftable slots, 0x58 bytes)
			class StateMachineStartTrack : public fight::Track
			{
			public:
				// 0x101DACD0
				StateMachineStartTrack();
				virtual ~StateMachineStartTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101D7BF0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetName(const fight::Name& newValue);
				bool SetArgs(const char* newValue);
				bool SetTags(const char* newValue);
				bool SetChannel(const char* newValue);
				fight::BranchHolder* SetStateMachineBranch();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder stateMachineBranch;  // +0x10
					unsigned char unknown34[0x4];
					fight::Name name;  // +0x38
					char* args;  // +0x40
					char* channel;  // +0x44
					char* tags;  // +0x48
					float timeBegin;  // +0x4C
					float timeEnd;  // +0x50
					unsigned char unknown54[0x4];
			};

			extern fight::Property** gStateMachineStartTrackProperties;
			fight::TrackFactory* CreateStateMachineStartTrackFactory(const char* name);
			void RegisterStateMachineStartTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
