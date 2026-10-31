// More data of the engine that the ai fight items read: the enum tables their properties pick from, the numbers of entries and some
// constants their constructors load (all defined by other units; names are guesses).
#ifndef PROTO_FIGHTITEMS_AI_AIDATA2_H
#define PROTO_FIGHTITEMS_AI_AIDATA2_H

#include "code/engine/fight/trackfactory.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			extern fight::EnumEntry gCombatDestinationFindTrackCameraVisibilityTable[];  // 0x11254E60
			extern fight::EnumEntry gHaveTokenConditionTypeTable[];  // 0x11254E78
			extern fight::EnumEntry gCombatDestinationFindTrackAllowedAreasTable[];  // 0x11254E88
			extern fight::EnumEntry gCombatDestinationFindTrackReferencePositionTable[];  // 0x11254EC8
			extern fight::EnumEntry gTargetHasLoFConditionCollisionFlagsTable[];  // 0x11254EE0
			extern fight::EnumEntry gHaveTokenConditionOwnerTable[];  // 0x11254F08
			extern fight::EnumEntry gCombatDestinationFindTrackHeightDifferenceCheckTable[];  // 0x11254F18
			extern fight::EnumEntry gCombatDestinationFindTrackHeuristicTable[];  // 0x11254F30
			extern fight::EnumEntry gFacingAngleTargetConditionTypeTable[];  // 0x11254F58
			extern fight::EnumEntry gHasCombatBudgetTokenConditionCombatTypeTable[];  // 0x11254FA0
			extern fight::EnumEntry gIsDisguiseActionEnabledConditionActionTable[];  // 0x11255208
			extern fight::EnumEntry gPerceptionEventConditionEventTable[];  // 0x112552F0
			extern fight::EnumEntry gEventConditionWhenTable[];  // 0x11255338
			extern fight::EnumEntry gNPCLODConditionValueTable[];  // 0x11255450
			extern fight::EnumEntry gEnableLODPatrolTrackActionOnEndTable[];  // 0x11255468
			extern fight::EnumEntry gEnableLODPatrolTrackActionOnBeginTable[];  // 0x11255488
			extern fight::EnumEntry gPeriodicMessageTrackTakerTable[];  // 0x112554C8
			extern fight::EnumEntry gAimTrackWhereTable[];  // 0x11255518
			extern fight::EnumEntry gTargetGoToTrackWhereTable[];  // 0x11255568
			extern fight::EnumEntry gLodSteerTrackWalkanimTable[];  // 0x11263AC8
			extern const int gCombatDestinationFindTrackHeuristicCount;  // 0x10DCA928
			extern const int gCombatDestinationFindTrackCameraVisibilityCount;  // 0x10DCA92C
			extern const int gCombatDestinationFindTrackReferencePositionCount;  // 0x10DCAA10
			extern const int gHaveTokenConditionTypeCount;  // 0x10DCAA14
			extern const int gHaveTokenConditionOwnerCount;  // 0x10DCAA18
			extern const int gCombatDestinationFindTrackAllowedAreasCount;  // 0x10DCAA1C
			extern const int gTargetHasLoFConditionCollisionFlagsCount;  // 0x10DCAA20
			extern const int gCombatDestinationFindTrackHeightDifferenceCheckCount;  // 0x10DCAA24
			extern const int gFacingAngleTargetConditionTypeCount;  // 0x10DCAA28
			extern const int gHasCombatBudgetTokenConditionCombatTypeCount;  // 0x10DCADD4
			extern const int gIsDisguiseActionEnabledConditionActionCount;  // 0x10DCB0D4
			extern const int gPerceptionEventConditionEventCount;  // 0x10DCBE54
			extern const int gEventConditionWhenCount;  // 0x10DCC284
			extern const int gEnableLODPatrolTrackActionOnBeginCount;  // 0x10DCD0B4
			extern const int gEnableLODPatrolTrackActionOnEndCount;  // 0x10DCD0B8
			extern const int gNPCLODConditionValueCount;  // 0x10DCD0BC
			extern const int gPeriodicMessageTrackTakerCount;  // 0x10DCD504
			extern const int gAimTrackWhereCount;  // 0x10DCD724
			extern const int gTargetGoToTrackWhereCount;  // 0x10DCD728
			extern const int gLodSteerTrackWalkanimCount;  // 0x10DF62C8
			extern const int gCombatDestinationFindTrackCollideWithTypeLOFDefault;  // 0x10DCA924
			extern const int gCombatDestinationFindTrackAllowedAreasDefault;  // 0x11040CD0
			extern fight::EnumEntry gPoisonTrackWhoTable[];  // 0x112555C8
			extern const int gPoisonTrackWhoCount;  // 0x10DCE104
			extern fight::EnumEntry gSpatialQueryConditionWhereTable[];  // 0x11255620
			extern fight::EnumEntry gSpatialQueryConditionWhatTable[];  // 0x11255630
			extern const int gSpatialQueryConditionWhatCount;  // 0x10DCE834
			extern const int gSpatialQueryConditionWhereCount;  // 0x10DCE838
			extern fight::EnumEntry gStrafeRunTrackHeuristicTable[];  // 0x11255698
			extern const int gStrafeRunTrackHeuristicCount;  // 0x10DCEC18
			extern fight::EnumEntry gTargetAlertSubStateConditionSubStateTable[];  // 0x112556C0
			extern fight::EnumEntry gTargetAlertStateConditionStateTable[];  // 0x112556D8
			extern fight::EnumEntry gTargetDefenseConditionDefenseTable[];  // 0x11255790
			extern const int gTargetAlertStateConditionStateCount;  // 0x10DCEF94
			extern const int gTargetAlertSubStateConditionSubStateCount;  // 0x10DCEF98
			extern const int gTargetDefenseConditionDefenseCount;  // 0x10DCEF9C
			extern fight::EnumEntry gThreatStoreConditionThreatObjectTable[];  // 0x112557D0
			extern const int gThreatStoreConditionThreatObjectCount;  // 0x10DCF3D4
		}
	}
}

#endif
