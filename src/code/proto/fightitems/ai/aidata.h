// Data of the engine that the ai fight items read: the enum tables their properties pick from, the numbers of entries and some
// constants their constructors load (all defined by other units; names are guesses). Tables the motion items already name are
// used from motiondata.h.
#ifndef PROTO_FIGHTITEMS_AI_AIDATA_H
#define PROTO_FIGHTITEMS_AI_AIDATA_H

#include "code/engine/fight/trackfactory.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			extern fight::EnumEntry gHasCombatBudgetTokenConditionCombatTypeTable[];  // 0x11254FA0
			extern const int gHasCombatBudgetTokenConditionCombatTypeCount;  // 0x10DCADD4
			extern fight::EnumEntry gIsDisguiseActionEnabledConditionActionTable[];  // 0x11255208
			extern const int gIsDisguiseActionEnabledConditionActionCount;  // 0x10DCB0D4
			extern fight::EnumEntry gPerceptionEventConditionEventTable[];  // 0x112552F0
			extern const int gPerceptionEventConditionEventCount;  // 0x10DCBE54
			extern fight::EnumEntry gEventConditionWhenTable[];  // 0x11255338
			extern const int gEventConditionWhenCount;  // 0x10DCC284
			extern fight::EnumEntry gNPCLODConditionValueTable[];  // 0x11255450
			extern fight::EnumEntry gEnableLODPatrolTrackActionOnEndTable[];  // 0x11255468
			extern fight::EnumEntry gEnableLODPatrolTrackActionOnBeginTable[];  // 0x11255488
			extern fight::EnumEntry gLodSteerTrackWalkanimTable[];  // 0x11263AC8
			extern const int gEnableLODPatrolTrackActionOnBeginCount;  // 0x10DCD0B4
			extern const int gEnableLODPatrolTrackActionOnEndCount;  // 0x10DCD0B8
			extern const int gNPCLODConditionValueCount;  // 0x10DCD0BC
			extern const int gLodSteerTrackWalkanimCount;  // 0x10DF62C8
			extern fight::EnumEntry gPeriodicMessageTrackTakerTable[];  // 0x112554C8
			extern const int gPeriodicMessageTrackTakerCount;  // 0x10DCD504
			extern fight::EnumEntry gAimTrackWhereTable[];  // 0x11255518
			extern fight::EnumEntry gTargetGoToTrackWhereTable[];  // 0x11255568
			extern const int gAimTrackWhereCount;  // 0x10DCD724
			extern const int gTargetGoToTrackWhereCount;  // 0x10DCD728
		}
	}
}

#endif
