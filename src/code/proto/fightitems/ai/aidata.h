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
			extern fight::EnumEntry gCombatDestinationFindTrackCameraVisibilityTable[];  // 0x11254E60
			extern fight::EnumEntry gHaveTokenConditionTypeTable[];  // 0x11254E78
			extern fight::EnumEntry gCombatDestinationFindTrackAllowedAreasTable[];  // 0x11254E88
			extern fight::EnumEntry gCombatDestinationFindTrackReferencePositionTable[];  // 0x11254EC8
			extern fight::EnumEntry gTargetHasLoFConditionCollisionFlagsTable[];  // 0x11254EE0
			extern fight::EnumEntry gHaveTokenConditionOwnerTable[];  // 0x11254F08
			extern fight::EnumEntry gCombatDestinationFindTrackHeightDifferenceCheckTable[];  // 0x11254F18
			extern fight::EnumEntry gCombatDestinationFindTrackHeuristicTable[];  // 0x11254F30
			extern fight::EnumEntry gFacingAngleTargetConditionTypeTable[];  // 0x11254F58
			extern const int gCombatDestinationFindTrackHeuristicCount;  // 0x10DCA928
			extern const int gCombatDestinationFindTrackCameraVisibilityCount;  // 0x10DCA92C
			extern const int gCombatDestinationFindTrackReferencePositionCount;  // 0x10DCAA10
			extern const int gHaveTokenConditionTypeCount;  // 0x10DCAA14
			extern const int gHaveTokenConditionOwnerCount;  // 0x10DCAA18
			extern const int gCombatDestinationFindTrackAllowedAreasCount;  // 0x10DCAA1C
			extern const int gTargetHasLoFConditionCollisionFlagsCount;  // 0x10DCAA20
			extern const int gCombatDestinationFindTrackHeightDifferenceCheckCount;  // 0x10DCAA24
			extern const int gFacingAngleTargetConditionTypeCount;  // 0x10DCAA28
			extern const int gCombatDestinationFindTrackCollideWithTypeLOFDefault;  // 0x10DCA924
			extern const int gCombatDestinationFindTrackAllowedAreasDefault;  // 0x11040CD0
		}
	}
}

#endif
