// Fight items of the scenario group: StateChangeCondition, CurrentStateCondition (unit 0x101DA5C0 - 0x101DABA0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_SCENARIO_SCENARIO_STATECONDITION_H
#define PROTO_FIGHTITEMS_SCENARIO_SCENARIO_STATECONDITION_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/scenario/scenariodata.h"

namespace proto
{
	namespace fightitems
	{
		namespace scenario
		{
			// RTTI: proto::fightitems::scenario::StateChangeCondition (10 vftable slots, 0x30 bytes)
			class StateChangeCondition : public fight::Condition
			{
			public:
				// 0x101DA610
				StateChangeCondition();
				virtual ~StateChangeCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101D7710, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				fight::BranchHolder* SetState();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder state;  // +0xC
			};

			extern fight::Property** gStateChangeConditionProperties;
			fight::ConditionFactory* CreateStateChangeConditionFactory(const char* name);
			void RegisterStateChangeConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::scenario::CurrentStateCondition (10 vftable slots, 0x30 bytes)
			class CurrentStateCondition : public fight::Condition
			{
			public:
				// 0x101DA690
				CurrentStateCondition();
				virtual ~CurrentStateCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101D77A0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				fight::BranchHolder* SetState();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder state;  // +0xC
			};

			extern fight::Property** gCurrentStateConditionProperties;
			fight::ConditionFactory* CreateCurrentStateConditionFactory(const char* name);
			void RegisterCurrentStateConditionFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
