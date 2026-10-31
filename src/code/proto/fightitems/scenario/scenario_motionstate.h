// Fight items of the scenario group: Event_MotionStateCondition (unit 0x101D8CE0 - 0x101D9540; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_SCENARIO_SCENARIO_MOTIONSTATE_H
#define PROTO_FIGHTITEMS_SCENARIO_SCENARIO_MOTIONSTATE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/scenario/scenariodata.h"

namespace proto
{
	namespace fightitems
	{
		namespace scenario
		{
			// RTTI: proto::fightitems::scenario::Event_MotionStateCondition (10 vftable slots, 0x10 bytes)
			class Event_MotionStateCondition : public fight::Condition
			{
			public:
				// 0x101D9230
				Event_MotionStateCondition();
				virtual ~Event_MotionStateCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101D5F90, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetMotionState(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int motionState;  // +0xC
			};

			extern fight::Property** gEvent_MotionStateConditionProperties;
			fight::ConditionFactory* CreateEvent_MotionStateConditionFactory(const char* name);
			void RegisterEvent_MotionStateConditionFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
