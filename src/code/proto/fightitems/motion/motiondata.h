// Data of the engine that the motion fight items read: the enum tables their properties pick from, the numbers of entries and some
// constants their constructors load (all defined by other units; names are guesses).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTIONDATA_H
#define PROTO_FIGHTITEMS_MOTION_MOTIONDATA_H

#include "code/core/name.h"
#include "code/engine/fight/trackfactory.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// 0x11251200: the name of the button hint that is showing when none is (name guess)
			extern const core::Name<core::CaseSensitiveKey> gNoButtonHint;
			extern fight::EnumEntry gAnimationBlendDirectionalTrackAnimNorthAllowedTransitionsTable[];  // 0x11253590
			extern fight::EnumEntry gAnimationBlendVerticalAimTrackTargetingModeTable[];  // 0x112535B0
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
			extern fight::EnumEntry gAnimationBlendDirectionalTrackCyclicTable[];  // 0x11254218
			extern fight::EnumEntry gAnimationBlendVerticalAimStrafeTrackCyclicTable[];  // 0x11254230
			extern fight::EnumEntry gAnimationBlendDirectionalTrackInputTable[];  // 0x11254248
			extern fight::EnumEntry gAnimationBlendVerticalAimTrackCyclicTable[];  // 0x11254250
			extern fight::EnumEntry gAnimationBlendSimpleTrackCyclicTable[];  // 0x11254268
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
			extern const int gAnimationBlendDirectionalTrackAnimNorthAllowedTransitionsCount;  // 0x10D9BE5C
			extern const int gAnimationBlendVerticalAimTrackTargetingModeCount;  // 0x10D9BF60
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
			extern fight::EnumEntry gAxisDirectionConditionAxisTable[];  // 0x112539E0
			extern const int gAxisDirectionConditionAxisCount;  // 0x10DA27B4
			extern fight::EnumEntry gIntersectionPropertiesConditionTypeTable[];  // 0x11254758
			extern fight::EnumEntry gJointLookAtTrackWhereTable[];  // 0x11253A08
			extern const int gJointLookAtTrackWhereCount;  // 0x10DA2DA8
			extern fight::EnumEntry gJumpTrackUnlockableFirstTable[];  // 0x112738D8
			extern const int gJumpTrackUnlockableFirstCount;  // 0x10E25FF4
			extern const int gMagneticBootsTestWallTrackCollideWithDefault;  // 0x10FF78DC
			extern const int gMagneticBootsTestCornerTrackCollideWithDefault;  // 0x10FF78E0
			extern fight::EnumEntry gObstacleColliderTypeConditionCompareTable[];  // 0x11254878
			extern const int gPushFromObstacleTrackCollideWithDefault;  // 0x10FF80E4
			extern fight::EnumEntry gPadRumbleSetTrackMotorTable[];  // 0x11253B10
			extern const int gPadRumbleSetTrackMotorCount;  // 0x10DA4CA4
			extern fight::EnumEntry gPatsyCreateTrackWhoTable[];  // 0x11253B28
			extern const int gPatsyCreateTrackWhoCount;  // 0x10DA4EE4
			extern fight::EnumEntry gCharacterCloudStateConditionStateTable[];  // 0x11253B80
			extern fight::EnumEntry gPedestrianAlertStateConditionStateTable[];  // 0x11263BB8
			extern fight::EnumEntry gPedestrianStateConditionStateTable[];  // 0x11268120
			extern const int gCharacterCloudStateConditionStateCount;  // 0x10DA5194
			extern const int gPedestrianAlertStateConditionStateCount;  // 0x10DF62C4
			extern const int gPedestrianStateConditionStateCount;  // 0x10E03998
			extern fight::EnumEntry gRadialBlurTrackAttachSpaceTable[];  // 0x11253860
			extern const int gRadialBlurTrackAttachSpaceCount;  // 0x10DA0468
			extern fight::EnumEntry gFXLight_PointTrackAttachSpaceTable[];  // 0x11253860
			extern fight::EnumEntry gFXLight_PointTrackEmitSpaceTable[];  // 0x11253880
			extern const int gFXLight_PointTrackAttachSpaceCount;  // 0x10DA0468
			extern const int gFXLight_PointTrackEmitSpaceCount;  // 0x10DA046C
			extern fight::EnumEntry gAllowGrabbingTrackOnEndTable[];  // 0x112538B0
			extern fight::EnumEntry gAllowGrabbingTrackOnBeginTable[];  // 0x112538C8
			extern fight::EnumEntry gGrabSlotDetachThrowTrackLinearVelocityReferenceTable[];  // 0x112538E0
			extern fight::EnumEntry gGrabPlayerTrackActionOnEndTable[];  // 0x112538F8
			extern fight::EnumEntry gReactionHitGrabTrackObjectTable[];  // 0x11253C28
			extern fight::EnumEntry gGrabSlotReverseAttachmentTrackPhysicsModeTable[];  // 0x11254660
			extern fight::EnumEntry gGrabPlayerTrackGrabbingPlayerTable[];  // 0x1126E378
			extern const int gGrabPlayerTrackActionOnEndCount;  // 0x10DA09E4
			extern const int gAllowGrabbingTrackOnBeginCount;  // 0x10DA09E8
			extern const int gAllowGrabbingTrackOnEndCount;  // 0x10DA09EC
			extern const int gGrabSlotDetachThrowTrackLinearVelocityReferenceCount;  // 0x10DA0AF0
			extern const int gReactionHitGrabTrackObjectCount;  // 0x10DA5A08
			extern const int gGrabPlayerTrackGrabbingPlayerCount;  // 0x10E17B38
			extern fight::EnumEntry gGroundSpikeAnimateClusterRadiiTrackSpawnRadiusVelocityTypeTable[];  // 0x11253920
			extern fight::EnumEntry gGroundSpikeTestStateConditionTestTypeTable[];  // 0x11253958
			extern const int gGroundSpikeTestStateConditionTestTypeCount;  // 0x10DA1458
			extern const int gGroundSpikeAnimateClusterRadiiTrackSpawnRadiusVelocityTypeCount;  // 0x10DA145C
			extern fight::EnumEntry gHUDMarkerTrackAnimTypeTable[];  // 0x11254FC8
			extern fight::EnumEntry gHUDMarkerTrackDisplayTypeTable[];  // 0x11254FF0
			extern fight::EnumEntry gHaveIconTypeConditionTypeTable[];  // 0x11255010
			extern fight::EnumEntry gHUDMarkerTrackColorTable[];  // 0x11255148
			extern const int gHaveIconTypeConditionTypeCount;  // 0x10DCAFC4
			extern const int gHUDMarkerTrackColorCount;  // 0x10DCAFC8
			extern const int gHUDMarkerTrackDisplayTypeCount;  // 0x10DCAFCC
			extern const int gHUDMarkerTrackAnimTypeCount;  // 0x10DCB0D0
			extern fight::EnumEntry gHideHUDTrackHideIndividualElementsHideElementsTable[];  // 0x1126D2E0
			extern const int gHideHUDTrackHideIndividualElementsHideElementsCount;  // 0x10E11290
			extern fight::EnumEntry gReactionGiverIsBeingGrabbedConditionGrabTypeTable[];  // 0x11253BD8
			extern fight::EnumEntry gReactionEventConditionReactionTypeTable[];  // 0x11253BF0
			extern fight::EnumEntry gReactionHitDamageConditionTypeTable[];  // 0x11253C18
			extern fight::EnumEntry gReactionHitCollisionPositionConditionComponentTable[];  // 0x112549C8
			extern const int gReactionEventConditionReactionTypeCount;  // 0x10DA5A04
			extern const int gReactionHitDamageConditionTypeCount;  // 0x10DA5A0C
			extern const int gReactionGiverIsBeingGrabbedConditionGrabTypeCount;  // 0x10DA5B10
			extern fight::EnumEntry gReactionHitAnimationTrackCyclicTable[];  // 0x11254A28
			extern fight::EnumEntry gSetVisibilityTrackActionOnBeginTable[];  // 0x11253C90
			extern fight::EnumEntry gSetVisibilityTrackActionOnEndTable[];  // 0x11253CA0
			extern const int gSetVisibilityTrackActionOnBeginCount;  // 0x10DA6DB4
			extern const int gSetVisibilityTrackActionOnEndCount;  // 0x10DA6DB8
			extern fight::EnumEntry gShieldStateConditionStateTable[];  // 0x11253CC0
			extern const int gShieldStateConditionStateCount;  // 0x10DA6F54
			extern fight::EnumEntry gShootTrackFixedDirectionSpaceTable[];  // 0x11255CB0
			extern const int gShootTrackFixedDirectionSpaceCount;  // 0x10DDB6D4
			extern fight::EnumEntry gMotionStateConditionStateTable[];  // 0x11253DC8
			extern const int gMotionStateConditionStateCount;  // 0x10DA7F44
			extern fight::EnumEntry gStunTrackOnEndTable[];  // 0x11253EA8
			extern fight::EnumEntry gStunTrackOnBeginTable[];  // 0x11253EC0
			extern const int gStunTrackOnBeginCount;  // 0x10DA80F4
			extern const int gStunTrackOnEndCount;  // 0x10DA80F8
			extern fight::EnumEntry gSupportingLimbSurfaceIntersectionPropertiesConditionMatchAgainstTable[];  // 0x11254B50
			extern fight::EnumEntry gSupportingLimbTestSurfaceNormalVelocityArcConditionVelocityTypeTable[];  // 0x112837F8
			extern const int gSupportingLimbTestSurfaceNormalVelocityArcConditionVelocityTypeCount;  // 0x10E69984
			extern fight::EnumEntry gTemporaryTargetableTrackOnBeginTable[];  // 0x11253F10
			extern const int gTemporaryTargetableTrackOnBeginCount;  // 0x10DA89E4
			extern fight::EnumEntry gUndergroundStateConditionStateTable[];  // 0x11253F60
			extern const int gUndergroundStateConditionStateCount;  // 0x10DA92A4
			extern fight::EnumEntry gVariableIntSetTrackOperatorTable[];  // 0x11254118
			extern const int gVariableIntSetTrackOperatorCount;  // 0x10DA9984
			extern fight::EnumEntry gSecondaryWeaponTypeConditionTypeTable[];  // 0x11254168
			extern const int gSecondaryWeaponTypeConditionTypeCount;  // 0x10DA9C24
			extern fight::EnumEntry gVelocityYAngleConditionTypeTable[];  // 0x112837F8
			extern const int gVelocityYAngleConditionTypeCount;  // 0x10E69984
			extern fight::EnumEntry gWhipFistExtendTrackTargetTable[];  // 0x112541E0
			extern const int gWhipFistExtendTrackTargetCount;  // 0x10DAAA34
		}
	}
}

#endif
