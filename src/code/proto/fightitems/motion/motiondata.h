// Data of the engine that the motion fight items read: the enum tables their properties pick from, the numbers of entries and some
// constants their constructors load (all defined by other units; names are guesses).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTIONDATA_H
#define PROTO_FIGHTITEMS_MOTION_MOTIONDATA_H

#include "code/engine/fight/trackfactory.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			extern fight::EnumEntry gAutoTargetTrackTargetOverridesTable[];  // 0x112535F8
			extern fight::EnumEntry gHeliBoundaryStatusConditionHeliBoundaryStatusTable[];  // 0x11253640
			extern fight::EnumEntry gButtonHintShowTrackPressTypeTable[];  // 0x11253660
			extern fight::EnumEntry gChargeConditionTypeTable[];  // 0x11253680
			extern fight::EnumEntry gHitSurfaceConditionSurfaceTable[];  // 0x11253700
			extern fight::EnumEntry gCollisionHitTrackTravelTowardTargetTable[];  // 0x11253760
			extern fight::EnumEntry gEffectConsumeTrackRevealModeTable[];  // 0x112537D0
			extern fight::EnumEntry gEffectConsumeTrackConsumeModeTable[];  // 0x112537F0
			extern fight::EnumEntry gFactionTypeConditionFactionTypeTable[];  // 0x11253818
			extern fight::EnumEntry gFallTrackPreserveMomentumTable[];  // 0x11253840
			extern fight::EnumEntry gCollisionGrabTrackPhysicsModeTable[];  // 0x11253F98
			extern fight::EnumEntry gDetectObbCollisionConditionCollideWithTable[];  // 0x11253FD0
			extern fight::EnumEntry gDetectedObjectAngleConditionTypeTable[];  // 0x11254408
			extern fight::EnumEntry gEdgePositionConditionComponentTable[];  // 0x11254488
			extern fight::EnumEntry gEffectChameleonicSkinTrackColourTypeTable[];  // 0x112544B0
			extern fight::EnumEntry gEffectChameleonicSkinTrackActionOnBeginTable[];  // 0x112544C0
			extern fight::EnumEntry gEffectChameleonicSkinTrackActionOnEndTable[];  // 0x112544D8
			extern fight::EnumEntry gAutoTargetTrackMinPriorityTargetClassTable[];  // 0x1125B320
			extern fight::EnumEntry gAutoTargetTrackTargetFilterTable[];  // 0x1125B4D0
			extern fight::EnumEntry gTendrilDevastatorTrackAttackTypeTable[];  // 0x1125B658
			extern fight::EnumEntry gDevastatorTargetHitTrackDamageTypeTable[];  // 0x1125B768
			extern fight::EnumEntry gCollisionHitTrackPropAreaEmissionScaleFunctionTable[];  // 0x1126F468
			extern fight::EnumEntry gDistanceFromWaterSurfaceConditionCompareTable[];  // 0x11276158
			extern fight::EnumEntry gClassNameConditionCompareTable[];  // 0x112761B0
			extern fight::EnumEntry gCrowdPositionConditionDirectionTable[];  // 0x112837B8
			extern const int gAutoTargetTrackTargetOverridesCount;  // 0x10D9C108
			extern const int gHeliBoundaryStatusConditionHeliBoundaryStatusCount;  // 0x10D9C698
			extern const int gButtonHintShowTrackPressTypeCount;  // 0x10D9C924
			extern const int gChargeConditionTypeCount;  // 0x10D9CB24
			extern const int gHitSurfaceConditionSurfaceCount;  // 0x10D9D048
			extern const int gCollisionHitTrackTravelTowardTargetCount;  // 0x10D9D454
			extern const int gEffectConsumeTrackConsumeModeCount;  // 0x10D9F0C4
			extern const int gEffectConsumeTrackRevealModeCount;  // 0x10D9F0C8
			extern const int gFactionTypeConditionFactionTypeCount;  // 0x10D9F2A4
			extern const int gFallTrackPreserveMomentumCount;  // 0x10D9F4C4
			extern const int gDetectObbCollisionConditionCollideWithCount;  // 0x10DA960C
			extern const int gCollisionGrabTrackPhysicsModeCount;  // 0x10DA9710
			extern const int gAutoTargetTrackMinPriorityTargetClassCount;  // 0x10DE6674
			extern const int gAutoTargetTrackTargetFilterCount;  // 0x10DE6678
			extern const int gTendrilDevastatorTrackAttackTypeCount;  // 0x10DE69A0
			extern const int gDevastatorTargetHitTrackDamageTypeCount;  // 0x10DE69A4
			extern const int gCollisionHitTrackPropAreaEmissionScaleFunctionCount;  // 0x10E1BE84
			extern const int gDistanceFromWaterSurfaceConditionCompareCount;  // 0x10E2C7D8
			extern const int gClassNameConditionCompareCount;  // 0x10E2C7DC
			extern const int gCrowdPositionConditionDirectionCount;  // 0x10E69988
			extern const int gAutoTargetTrackTargetFilterDefault;  // 0x10D9C104
			extern const int gFlyingAutoTargetTrackTargetFilterDefault;  // 0x10D9C10C
			extern const int gCollisionGrabTrackCollideWithDefault;  // 0x10FF132C
			extern const int gCollisionHitTrackCollideWithDefault;  // 0x10FF1694
			extern const int gDetectTrackCollideWithDefault;  // 0x10FF268C
		}
	}
}

#endif
