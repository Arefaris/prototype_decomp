// Fight items of the scenario group: StateMachineStopTrack (unit 0x101DB2A0 - 0x101DB630; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_SCENARIO_SCENARIO_STATEMACHINESTOP_H
#define PROTO_FIGHTITEMS_SCENARIO_SCENARIO_STATEMACHINESTOP_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/scenario/scenariodata.h"

namespace proto
{
	namespace fightitems
	{
		namespace scenario
		{
			// RTTI: proto::fightitems::scenario::StateMachineStopTrack (16 vftable slots, 0x18 bytes)
			class StateMachineStopTrack : public fight::Track
			{
			public:
				// 0x101DB310
				StateMachineStopTrack();
				virtual ~StateMachineStopTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101D7F50, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
			};

			extern fight::Property** gStateMachineStopTrackProperties;
			fight::TrackFactory* CreateStateMachineStopTrackFactory(const char* name);
			void RegisterStateMachineStopTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
