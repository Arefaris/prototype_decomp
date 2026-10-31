// Fight items of the freeroamevents group: FREventTriggerTestCondition (unit 0x1027E100 - 0x1027E580; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_FREEROAMEVENTS_FREEROAMEVENTS_TRIGGERTEST_H
#define PROTO_FIGHTITEMS_FREEROAMEVENTS_FREEROAMEVENTS_TRIGGERTEST_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/scenario/scenariodata.h"
#include "code/proto/fightitems/ai/aidata.h"
#include "code/proto/fightitems/freeroamevents/freeroameventsdata.h"

namespace proto
{
	namespace fightitems
	{
		namespace freeroamevents
		{
			// RTTI: proto::fightitems::freeroamevents::FREventTriggerTestCondition (10 vftable slots, 0x10 bytes)
			class FREventTriggerTestCondition : public fight::Condition
			{
			public:
				// 0x1027E280
				FREventTriggerTestCondition();
				virtual ~FREventTriggerTestCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1027E140, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetName(const char* newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					char* name;  // +0xC
			};

			extern fight::Property** gFREventTriggerTestConditionProperties;
			fight::ConditionFactory* CreateFREventTriggerTestConditionFactory(const char* name);
			void RegisterFREventTriggerTestConditionFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
