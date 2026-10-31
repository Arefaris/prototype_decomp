// Data of the engine that the scenario fight items read: the enum tables their properties pick from, the numbers of entries and some
// constants their constructors load (all defined by other units; names are guesses).
#ifndef PROTO_FIGHTITEMS_SCENARIO_SCENARIODATA_H
#define PROTO_FIGHTITEMS_SCENARIO_SCENARIODATA_H

#include "code/engine/fight/trackfactory.h"

namespace proto
{
	namespace fightitems
	{
		namespace scenario
		{
			extern fight::EnumEntry gEvent_MotionStateConditionMotionStateTable[];  // 0x11253DC8
			extern const int gEvent_MotionStateConditionMotionStateCount;  // 0x10DA7F44
			extern fight::EnumEntry gTriggerVolumeEventConditionTypeTable[];  // 0x11254D88
			extern const int gTriggerVolumeEventConditionTypeCount;  // 0x10DC8E24
			extern const int gTriggerVolumeEventConditionTriggerVolumeAttributesTagsMembers[];  // 0x1103F78C
			extern const int gTriggerVolumeEventConditionTouchAttributesTagsMembers[];  // 0x1103F7A4
		}
	}
}

#endif
