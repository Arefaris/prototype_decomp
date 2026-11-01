// The proto fight contexts: the AI, Alert, Music, Vehicle and HitEffect contexts the game makes, with the factories of its fight
// items, and the extensions of the Playback and the NIS contexts (unit 0x10091620 - 0x10094600, no assert path; the file name and
// the function names are guesses). The registration functions belong to the units of the fight items they register; the ones that
// register a set of factories a unit has in common are not named in the binary and are named after their first factory.
#include "code/engine/fight/coretracks.h"
#include "code/engine/fight/coretracks.h"
#include "code/engine/fight/fightsystem.h"
#include "code/engine/scenario/luatracks.h"
#include "code/engine/scenario/luatracks.h"

namespace fight
{
	void RegisterBranchFactories(TrackRegistry* registry);
	void RegisterCoreFactories(TrackRegistry* registry);
	void RegisterCoreTrackFactories(TrackRegistry* registry);
	void RegisterFlowTrackFactories(TrackRegistry* registry);
	void RegisterEventTrackFactory(TrackRegistry* registry, const char* name);
	void RegisterWaitTrackFactory(TrackRegistry* registry, const char* name);
	void RegisterSpawnTrackFactory(TrackRegistry* registry, const char* name);
}

namespace engine
{
namespace animation
{
	void RegisterVelocityConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterShaderAnimationTrackFactory(fight::TrackRegistry* registry, const char* name);
}
}

namespace engine
{
	void RegisterAttributeNameConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterObjectTemplateConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterHealthConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSupportingSurfaceConditionFactories(fight::TrackRegistry* registry);
	void RegisterScenarioStringTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterAudioTrackFactories(fight::TrackRegistry* registry);
	void RegisterPlaybackTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterEffectTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterAbortEffectTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterMotionTrailTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSetEffectTimerTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterCheckEffectTimerConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDeleteAllDecalsTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterCollisionEnableByNameTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterEffectLODBiasTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterEffectLODSwitchTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterEffectLODDisableTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterPlaybackStateConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterHealthTrackFactory(fight::TrackRegistry* registry, const char* name);
}

namespace proto
{
namespace fightitems
{
namespace motion
{
	void RegisterClassNameConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTargetDistanceConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTargetDistanceWithOffsetConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTargetAngleConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterMotionStateConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterVariableIntCompareConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterVariableNameCompareConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTimerCompareConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterShootCheckAmmoCountConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterChargeConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTargetCanJumpToConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterGrabSlotFactories(fight::TrackRegistry* registry);
	void RegisterSetGrabIntersectionPropertiesTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterGrabTargetClearTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterStunnedFactories(fight::TrackRegistry* registry);
	void RegisterHasPatsyFactories(fight::TrackRegistry* registry);
	void RegisterFactionFactories(fight::TrackRegistry* registry);
	bool RegisterUndergroundStateFactories(fight::TrackRegistry* registry);
	void RegisterAccumulatedDamageFactories(fight::TrackRegistry* registry);
	void RegisterSupportingLimbTestSurfaceNormalAngleFactories(fight::TrackRegistry* registry);
	void RegisterHaveIconTypeConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterClearPatsyTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterClearFailedPatsyTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterVariableIntSetTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterVariableNameSetTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTimerSetTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTimerContinousSetTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterHUDMarkerTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterVariableIntTemporarySetTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterAccumulatedDamageResetTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterGrabSlotDetachTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterVehiclePlayAnimationTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterPatsyCreateTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDebugLayerFactories(fight::TrackRegistry* registry);
	void RegisterDeformTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterCollisionHitTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterHitReactionTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTargetClassTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterFXLight_PointTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterRadialBlurTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDeathTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterImpulseTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterPadRumbleClearFactories(fight::TrackRegistry* registry);
	void RegisterSlowMotionTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterGrabSlotDeathTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSetVehicleSolverEnabledTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSetVehicleAnimatedTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSetVehicleHeadlightTrackFactory(fight::TrackRegistry* registry, const char* name);
	bool RegisterHelicopterRotorCollisionFactories(fight::TrackRegistry* registry);
	void RegisterDecalTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterGrabbableClassConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterNISConsumeByParentTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterReactionThrowTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterStunTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterReactionEventConditionGroupFactories(fight::TrackRegistry* registry);
	void RegisterJointOrientationConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterAnimationBlendDirectionalTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterAnimationBlendVerticalAimTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterAnimationBlendVerticalAimStrafeTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterAnimationChargeTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterAutoTargetPositionTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterAutoTargetTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterPedestrianAutoTargetTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterAutoTargetClearTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterAutoTargetPlayerTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterBloodSplatterTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterChargeSetTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterChargeClearTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterChargeTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterClearCollisionRecordTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterCollisionGrabTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterConsumeTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterConsumeMeTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterConsumeGrabberTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterConsumeByParentTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterCrowdTestTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDeathOnEndTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDetectTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDevastatorTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTendrilDevastatorTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDevastatorUsedTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDevastatorTargetExecuteTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDevastatorTargetHitTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDevastatorTargetGroundSpikeTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDistanceToJointConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterInsidePlaneConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDisablePlayerControlTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDisableTimeWithNoDamageCounterTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDriftTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterEdgeNormalFactories(fight::TrackRegistry* registry);
	void RegisterEdgeDetectFactories(fight::TrackRegistry* registry);
	void RegisterEffectChameleonicSkinTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterEffectConsumeTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterFallTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterFlyingAttackTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterFlyingAutoTargetTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterFlyingBrakeTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterFlyingDashTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterFlyingGroundAttackTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterFootstepTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterFootstepDamageTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterFreezeScaleTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterGenderConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterGrabButtonStruggleTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterGrabObjectFromChildGrabSlotTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterGrabObjectFromParentGrabSlotTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDelayCollisionWithGrabbedTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterGrabSlotDetachThrowTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterGrabSlotExecuteTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterGrabSlotExecuteUsingChildTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterGrabSlotReverseAttachmentTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterGrabSlotSwapTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterGrabSlotUpdateAttachmentTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterGrabSlotUpdateAttachmentWithRestoreTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterGrabbedDetachTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterGrabbedExecuteOnParentTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterGrabbedExecuteUsingParentTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterGrabbedSwapGrabberSlotsTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterGrabbedUpdateAttachmentTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterGrabPlayerTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterGrabGrabTargetTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterGrabSetGrabbingTimerTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterGrabSlotEnableStuckTestTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterGrabbedPlaybackTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterGrappleLocoSprintTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterGrappleLocoSteerTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterGroundSlideTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterHeliLocoTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterHitReactionThrowTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterHitWeaponTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterIKSurfaceFixupTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterIntersectionPropertiesConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterInvulnerableTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterJawFlapTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterJointAnchorToAnimationTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterJointLookAtTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterJumpTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterJumpToTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterJumpYTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterLocoClimbTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterLocoCrowdTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterLocoSprintTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterLocoSprintChargeTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterLocoSteerTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterLocoSteerLeanTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterLocoStrafeTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterMoveAtVelocityTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterMoveChargedTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterNoPushbackTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterObstacleDistanceFactories(fight::TrackRegistry* registry);
	void RegisterOrientTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterWorldOrientTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterReactionFloatTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterReactionHitApplyImpulseTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterReactionHitAnimationTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterReactionHitExecuteTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterReactionHitGrabTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterReactionHitPushbackAddTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterReactionPushbackOrientTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterReactionPushbackTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterReactionTargetGiverTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterReactionTimeExecuteTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterReactionThrowSpinAngleFactories(fight::TrackRegistry* registry);
	void RegisterScaleJointForConsumeTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterScrubberTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSetVisibilityTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterShoulderConFixupTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterShieldHealthFactories(fight::TrackRegistry* registry);
	void RegisterShieldDeployTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterShieldSetStateTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterShieldReflectTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterShootTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterShootCalculateHitPositionTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterShootSetAmmoProfileTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterShootSetUserProfileTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterShootTakeAmmoFromParentTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterShootAutoTargetTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterShootSelectWeaponConfigurationTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterShootSwitchWeaponConfigurationTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSkidTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSkidPedalTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSlaveTransformTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSpawnGibTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSprintVelocityClearTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSurfaceMoveAtVelocityTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSupportingLimbSetActiveTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSupportingLimbSetDirectionTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSupportingLimbTestTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterVehicleReticuleTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterThrowTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTransformFadeTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTransformTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTransformCompleteTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTransformDesiredTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTransformStartTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTransformationAllowedTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTransformationDisallowedTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTurnRoundTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterUninterruptibleTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSpecificUninterruptibleTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterWallExitTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterWallJumpTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterWallJumpUpTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterWallRunTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterWallRunEnterTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterWallOrientTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterWallSlideTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTendrilTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTendrilFromParentTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterWhipFistExtendTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterWhipFistRetractTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterWhipFistMakeTautTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterWhipFistAnimatedTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterWhipFistSegmentFixToJointTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterWhipFistPullParentToTargetTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterWhipFistResetTargetTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterWhipFistFreezeSegmentsTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterWhipFistExtendBlockedOrNotConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterVehiclePowerOnOffTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSetSecondaryWeaponTypeTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterHelicopterSpawnBloodtoxTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterMotionStateTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterMagneticBootsTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterMagneticBootsTestWallTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterMagneticBootsTestCornerTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterMagneticBootsTurnCornerTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterMagneticBootsStickToWallTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterMagneticBootsResetInfoTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterMagneticBootsJumpTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterMagneticBootsTestJumpStuckTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterMagneticBootsDetachTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterMagneticBootsTestDetachTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterHunterShortRangeLocoTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterHunterShortRangeHopCornerTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterHunterShortRangeCorner2TrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterHunterLandedTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterHealthSetMultiplierTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterFactionDefaultTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterFactionSetTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTokenSetFloatDelayTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterUndergroundSetTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterUnlockableConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterAnchorToGroundTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterUndergroundTeleportTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterRadioHQTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTargetableTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTemporaryTargetableTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterAllowGrabbingTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterScenarioEventRadioAttemptTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterCharacterCloudStateFactories(fight::TrackRegistry* registry);
	void RegisterTempRegenerationTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTempRegenAbortTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterJumpAnimationTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterButtonHintShowTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterEnableButtonHintsTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterJointTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterOrientTowardsJumpInPositionTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterJumpFromWaterTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterFromWaterSetJumpToTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterIgnoreWaterReactionTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterAnimationBlendSimpleTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterHideHUDTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSetFireRateTimerTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterLaserTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSpecialistDodgeTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterIgnoreHitsTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterReloadTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSupportingLimbSetActiveRangeTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterAxisDirectionConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterHitSurfaceFactories(fight::TrackRegistry* registry);
	void RegisterConsumptionNameConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterCharacterCloudStateAt10102280Factories(fight::TrackRegistry* registry);
	void RegisterCrowdMinDistanceConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterCrowdPositionConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDetectedObjectAngleConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDetectedObjectConditionGroupConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDetectedObjectDistanceConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDetectedObjectFacingConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDetectedObjectIsSeenConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDetectedObjectIsTargetConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDevastatorAvailableConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDevastatorTargetDistanceConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDevastatorTargetConditionGroupConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterJointLookAtConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterOutOfCombatTimerConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterPushbackDirectionConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterPushbackVelocityConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterShootCheckCooldownTimeConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterShootCheckOverheatingConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterShootCurrentWeaponConfigurationConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTransformationAllowedConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTransformationSlotActiveConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTransformationSlotTransformDesiredConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTransformationSlotValidConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTransformationConsumeDescriptionValidConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTransformationDesiredSensesConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterAutoTargetDistanceConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterIsUndamageableFactories(fight::TrackRegistry* registry);
	void RegisterOrientationDesiredConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterVelocityAngleConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterVelocityYAngleConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterUsingHunterShortRangeConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterOrientationNormalAngleConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterMagneticBootsNextSurfaceNormalConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterInsideJumpInBoundaryConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterHeliBoundaryStatusConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDistanceFromWaterSurfaceConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterButtonHintShowingConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterHunterOnWallConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterHunterCanHopAroundCornerConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterGroundSpikeTestStateFactories(fight::TrackRegistry* registry);
	void RegisterGroundSpikeSpawnClusterFactories(fight::TrackRegistry* registry);
	void RegisterHasMarkerConditionFactory(fight::TrackRegistry* registry, const char* name);
}
}
}

namespace proto
{
namespace fightitems
{
namespace ai
{
	void RegisterEmotionalStateConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTargetingFactories(fight::TrackRegistry* registry);
	void RegisterPerceptionEventConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterEnabledFactories(fight::TrackRegistry* registry);
	void RegisterHasFixedDestinationConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterHasFixedAreaDestinationConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterHasPatrolPathConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterRequestSuspicionFactories(fight::TrackRegistry* registry);
	void RegisterInAlertModeConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDriverStateConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTargetFreeHeightRadiusConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterCanStrafeRunConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDestinationTargetDistanceConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTargetHasLoFConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTargetHasLoFDistanceConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterAimingAtTargetConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterAimingAtConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterFacingAngleTargetConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterHaveTokenConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterFloatShotAllowedConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterHaveStrafeRunTokenConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDestinationHaveArrivedConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDestinationDistanceConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterFixedDestinationDistanceConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterHaveDestinationConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterThreatConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterThreatCanSeeConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterThreatInMemoryConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterLastThreatConditionGroupConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterEventConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterEventValueConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterVehicleStateConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTargetBeingHeldConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTargetIsHumanConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterShouldSpawnConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSpawnTemplateConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterThreatCanGrabConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterThreatStoreConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterShouldRadioHQConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterIsPoisonedConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterPoisonedTimeConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterNPCLODConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterCanReserveSoldierBudgetConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterIsInLoadedCellConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSpatialQueryConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterInFormationConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterFormationReformingConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterAtRoofsEdgeConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterNearRoofsEdgeConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterIsInRooftopConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterInHotZoneConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterInBlastAreaConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterInReservedAreaConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterInsideReservedVolumeConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterGroundDistanceConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterStuckConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDestinationTargetOrientationConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterNavMeshAreaConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterAnyPlayerDistanceConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSetAvoidanceGapAnywhereTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterInTargetsCameraConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterAbsoluteHeightConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterIdleTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterFlyingIdleTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterAirHoverTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterAirDodgeTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterCircleStrafeTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterCirclePatrolTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterIntersectionCirclePatrolTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTryStrafeRunTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterStrafeRunTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTightStrafeRunTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterPrepareTightStrafeRunTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTryOpenStrafeRunTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSimpleOpenStrafeRunTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterPredefinedPatrolTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterLandTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTakeOffTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterZiplineTakeOffTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterZiplineLandTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterForceEmotionalStateTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterMessageTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterPeriodicMessageTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterCheckBodyTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterExecuteTaskTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSpawnTaskTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterGoToTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterFixedDestinationGotoTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterFixedDestinationFlytoTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterPatrolTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterPathPatrolTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDestinationGoToTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDestinationFlyToTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDestinationJumpToTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterAimTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterHelicopterStrafeModeTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterStopTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSpeedTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTempSpeedTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterReservePositionTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterReserveTargetsPositionTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterReserveVolumeTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterReserveHydraPositionTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterCombatDestinationFindTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterRooftopDestinationFindTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterActionTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterRequestTokenTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterRefreshStrafeRunTokenTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTargetTokenBoostTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTargetGoToTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterFleeTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDrawDebugTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterAiTreeEventSendTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSetVehicleStateTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSetUserTooltipTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterPlayDebugDialogTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterThreatMemoryResetTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterThreatDodgeTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterConditionalExecuteTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterPeriodicOpportunityTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDelayedSequenceTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterForceRecalculatePathTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterForceMotionTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterFollowTargetTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterFollowFormationTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterReformTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSetBrakeDistanceTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDumbGotoTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDumbGotoLODTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTankRamTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterActivateVehicleBehaviourTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterActivateScaryMonsterBehaviourTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDestinationSetDeadBodyTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDrawObjectDebugTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterFixedDestinationJumpToTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterClearFixedAreaDestinationTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterCommanderInCombatTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterUnDowngradableTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterUpdateSoldierReservationBudgetTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterCharacterizeFromReservedTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterCharacterizeTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterLodGotoFixedDestinationTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterEnableLODPatrolTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterStayOnRoofTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterBlindTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDumpAlertCharactersTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterInfectedAlertedConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterThreatBallTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterRequestCombatBudgetTokenTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterHasCombatBudgetTokenConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterThreatSendToTargetTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterPoisonTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterCurePoisonTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDisableStayOnNavmeshTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterAddDiversionTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterShowDisguiseActionHUDTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDisguiseActionUsedTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterConfigureScaryMonsterBehaviourTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterAdjustHydraMovementTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterCanGunButtConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterObjectSpawnedTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterReserveGunButtTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSetPoisonCloudParametersTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSetNPCLODStateTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterGameObjectOrientTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterResetPhysicVelocitiesTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterLodSteerTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterLodMoveTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSetIntersectionPropertiesTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterIsDisguiseActionEnabledConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterAreDisguiseActionsEnabledConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSoldierWithinDistanceConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterCheckTagAvailableSpaceConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterIsMissileTargetingPlayerConditionFactory(fight::TrackRegistry* registry, const char* name);
}
}
}

namespace proto
{
namespace fightitems
{
namespace alert
{
	void RegisterDisguiseBlownConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterPlayerSeenConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterShouldCallStrikeTeamConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterBlowDisguiseTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterReactionTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSetAlertVariableTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterResetAlertVariablesTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSetInPursuitTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterScenarioMessageTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterStartStrikeTeamMeterTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterStopStrikeTeamMeterTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterRadioedSetTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterAlertReportTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDisablePoliceTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterReportBackToIdleTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterReportEnterBeginCombatTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterAlertVariableFactories(fight::TrackRegistry* registry);
	void RegisterDisguiseReactionConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterHoldOnAlertEventsTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterCallStrikeTeamTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterPlayerCallStrikeTeamTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterValidMilitaryDisguiseConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterMilitaryDisguiseConditionFactory(fight::TrackRegistry* registry, const char* name);
}
}
}

namespace proto
{
namespace fightitems
{
	void RegisterAt102061F0Factories(fight::TrackRegistry* registry);
	void RegisterAt10502080Factories(fight::TrackRegistry* registry);
	void RegisterAt103591C0Factories(fight::TrackRegistry* registry);
	bool RegisterPhysicsLODAndDoorsFactories(fight::TrackRegistry* registry);
	void RegisterAt104F3900Factories(fight::TrackRegistry* registry);
	void RegisterAt104FB8A0Factories(fight::TrackRegistry* registry);
	void RegisterAt105020B0Factories(fight::TrackRegistry* registry);
	void RegisterAt104FAC90Factories(fight::TrackRegistry* registry);
	void RegisterAt101D7500Factories(fight::TrackRegistry* registry);
	void RegisterAt101D6DA0Factories(fight::TrackRegistry* registry);
	void RegisterAt101D8B60Factories(fight::TrackRegistry* registry);
	void RegisterPunchinCameraFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterAt1048FCE0Factories(fight::TrackRegistry* registry);
	void RegisterAccelerationFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterBlockFramerCamFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterCameraHintFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterCameraResetFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterAt103585C0Factories(fight::TrackRegistry* registry);
	void RegisterDramaticCameraFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterScriptedCameraFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterPhysicsSetIntersectionPropertiesFactory(fight::TrackRegistry* registry, const char* name);
}
}

namespace engine
{
namespace scenario
{
	void RegisterLuaConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterLuaTrackFactory(fight::TrackRegistry* registry, const char* name);
}
}

namespace proto
{
namespace fightitems
{
namespace vehicle
{
	void RegisterSetPanicStateTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSpawnCopsOffScreenTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSpawnCopsBesideCarTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterAvoidObstaclesTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterPanicTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTerminateTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterReturnToNormalTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterStateConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterEBrakeTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSpeedConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterFishTailTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterWaitingForObjectConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterVehicleNameConditionFactory(fight::TrackRegistry* registry, const char* name);
}
}
}

namespace proto
{
namespace fightitems
{
namespace playback
{
	void RegisterSpawnObjectTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterManageLifetimeTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterShootTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSuckIntoPlayerTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterWasShotByPlayerConditionFactory(fight::TrackRegistry* registry, const char* name);
}
}
}

namespace proto
{
namespace fightitems
{
namespace render
{
	void RegisterFogTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterTimeOfDayBlendTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDistanceToCameraConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterGPUFillConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterBulletTracerTrackFactory(fight::TrackRegistry* registry, const char* name);
}
}
}

namespace proto
{
namespace fightitems
{
namespace citymanager
{
	void RegisterInZoneConditionFactory(fight::TrackRegistry* registry, const char* name);
}
}
}

namespace proto
{
	void RegisterNISExcludeVolumeTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterFMVTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterIsWOITargetConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterWOIFMVTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterWOISendEventTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterWOIPlayReactionTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterWOIShowTargetNameTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterSmartHintSetTimerTrackFactory(fight::TrackRegistry* registry, const char* name);
}

namespace proto
{
namespace fightitems
{
namespace proplogic
{
	void RegisterWaitOnCollisionTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterShootingEventConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterOnCollisionTrackFactory(fight::TrackRegistry* registry, const char* name);
}
}
}

namespace engine
{
namespace framebufferfx
{
	void RegisterToneMapTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterDepthOfFieldTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterBloomTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterScatterTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterColourMatrixTrackFactory(fight::TrackRegistry* registry, const char* name);
}
}

namespace proto
{
namespace fightitems
{
namespace scenario
{
	void RegisterStateMachineStartTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterStateMachineTransitionTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterStateMachineStopTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterCurrentStateFactories(fight::TrackRegistry* registry);
	void RegisterPackageLoadTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterPackageUnloadTrackFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterPackageReadyConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterAlertStatusFactories(fight::TrackRegistry* registry);
	void RegisterEvent_MotionStateConditionFactory(fight::TrackRegistry* registry, const char* name);
	void RegisterMissionConditionFactory(fight::TrackRegistry* registry, const char* name);
}
}
}

namespace proto
{
namespace fightitems
{
namespace freeroamevents
{
	void RegisterFREventTriggerTestFactories(fight::TrackRegistry* registry);
}
}
}

namespace proto
{
namespace fightitems
{
namespace online
{
	void RegisterOnlineTestForRespawnStateFactories(fight::TrackRegistry* registry);
	void RegisterOnlineFlagPlayerDeathFactories(fight::TrackRegistry* registry);
}
}
}

namespace engine
{
	extern LoadListeners* gLoadListeners;
	extern const char* gPlaybackContextName;
	extern const char* gNISContextName;
	// The name of the hit effect context (0x110A2FB4)
	extern const char* gHitEffectContextName;
	extern const char* gPropLogicContextName;
	extern const char* gMotionContextName;
	extern const char* gScenarioContextName;
}

namespace proto
{
	// The table of the event mask bits the 'onEvent' tracks of the game know (0x11253498, 0x16 entries, the count at 0x10D98E90)
	extern fight::EnumEntry gFightEventMasks[];
	extern const int gFightEventMaskCount;
	// The script hook the game replaces (0x11253570 / 0x11253574) and its replacement (0x100912C0)
	extern engine::ScriptHook gPreviousScriptHook;
	extern void* gPreviousScriptHookData;
	bool FightScriptHook(void* data, bool keepOpen, bool finish, engine::ScriptHookArgs* args);
	// 0x10091570: what follows the contexts' set-up (name guess)
	void FinishFightContexts();
}

namespace proto
{

	// FUNCTION: ENGINE 0x10091620
	void MakeAIContext()
	{
		engine::LoadListeners* listeners = engine::gLoadListeners;
		fight::TrackRegistry* registry = new fight::TrackRegistry;
		registry->SetName(fight::Name("AI", 1));
		listeners->AddContext(registry);
		fight::RegisterBranchFactories(registry);
		fight::RegisterCoreFactories(registry);
		fight::RegisterCoreTrackFactories(registry);
		fight::RegisterFlowTrackFactories(registry);
		fight::RegisterEventTrackFactory(registry, "onEvent");
		engine::animation::RegisterVelocityConditionFactory(registry, "velocity");
		engine::RegisterAttributeNameConditionFactory(registry, "attributeName");
		proto::fightitems::motion::RegisterClassNameConditionFactory(registry, "className");
		engine::RegisterObjectTemplateConditionFactory(registry, "objectTemplate");
		proto::fightitems::ai::RegisterEmotionalStateConditionFactory(registry, "emotionalState");
		proto::fightitems::ai::RegisterTargetingFactories(registry);
		proto::fightitems::ai::RegisterPerceptionEventConditionFactory(registry, "perceptionEvent");
		proto::fightitems::motion::RegisterTargetDistanceConditionFactory(registry, "targetDistance");
		proto::fightitems::motion::RegisterTargetDistanceWithOffsetConditionFactory(registry, "targetDistanceWithOffset");
		proto::fightitems::motion::RegisterTargetAngleConditionFactory(registry, "targetAngle");
		proto::fightitems::ai::RegisterEnabledFactories(registry);
		proto::fightitems::ai::RegisterHasFixedDestinationConditionFactory(registry, "hasFixedDestination");
		proto::fightitems::ai::RegisterHasFixedAreaDestinationConditionFactory(registry, "hasFixedAreaDestination");
		proto::fightitems::ai::RegisterHasPatrolPathConditionFactory(registry, "hasPatrolPath");
		proto::fightitems::motion::RegisterMotionStateConditionFactory(registry, "motionState");
		proto::fightitems::ai::RegisterRequestSuspicionFactories(registry);
		proto::fightitems::ai::RegisterInAlertModeConditionFactory(registry, "inAlertMode");
		proto::fightitems::ai::RegisterDriverStateConditionFactory(registry, "driverState");
		proto::fightitems::ai::RegisterTargetFreeHeightRadiusConditionFactory(registry, "freeTargetHeightRadius");
		proto::fightitems::ai::RegisterCanStrafeRunConditionFactory(registry, "canStrafeRun");
		proto::fightitems::ai::RegisterDestinationTargetDistanceConditionFactory(registry, "destinationTargetDistance");
		proto::fightitems::ai::RegisterTargetHasLoFConditionFactory(registry, "targetHasLoF");
		proto::fightitems::ai::RegisterTargetHasLoFDistanceConditionFactory(registry, "targetHasLoFDistance");
		proto::fightitems::ai::RegisterAimingAtTargetConditionFactory(registry, "aimingAtTarget");
		proto::fightitems::ai::RegisterAimingAtConditionFactory(registry, "aimingAt");
		proto::fightitems::ai::RegisterFacingAngleTargetConditionFactory(registry, "facingAngleTarget");
		proto::fightitems::ai::RegisterHaveTokenConditionFactory(registry, "haveToken");
		proto::fightitems::ai::RegisterFloatShotAllowedConditionFactory(registry, "floatShotAllowed");
		proto::fightitems::ai::RegisterHaveStrafeRunTokenConditionFactory(registry, "haveStrafeRunToken");
		proto::fightitems::ai::RegisterDestinationHaveArrivedConditionFactory(registry, "destinationHaveArrived");
		proto::fightitems::ai::RegisterDestinationDistanceConditionFactory(registry, "destinationDistance");
		proto::fightitems::ai::RegisterFixedDestinationDistanceConditionFactory(registry, "fixedDestinationDistance");
		proto::fightitems::ai::RegisterHaveDestinationConditionFactory(registry, "haveDestination");
		proto::fightitems::motion::RegisterVariableIntCompareConditionFactory(registry, "variableIntCompare");
		proto::fightitems::motion::RegisterVariableNameCompareConditionFactory(registry, "variableNameCompare");
		proto::fightitems::motion::RegisterTimerCompareConditionFactory(registry, "timerCompare");
		proto::fightitems::motion::RegisterShootCheckAmmoCountConditionFactory(registry, "shootCheckAmmoCount");
		engine::RegisterHealthConditionFactory(registry, "health");
		proto::fightitems::ai::RegisterThreatConditionFactory(registry, "threat");
		proto::fightitems::ai::RegisterThreatCanSeeConditionFactory(registry, "threatCanSee");
		proto::fightitems::ai::RegisterThreatInMemoryConditionFactory(registry, "threatInMemory");
		proto::fightitems::ai::RegisterLastThreatConditionGroupConditionFactory(registry, "lastThreatConditionGroup");
		proto::fightitems::ai::RegisterEventConditionFactory(registry, "event");
		proto::fightitems::ai::RegisterEventValueConditionFactory(registry, "eventValue");
		proto::fightitems::ai::RegisterVehicleStateConditionFactory(registry, "vehicleState");
		proto::fightitems::motion::RegisterChargeConditionFactory(registry, "charge");
		proto::fightitems::motion::RegisterTargetCanJumpToConditionFactory(registry, "targetCanJumpTo");
		proto::fightitems::ai::RegisterTargetBeingHeldConditionFactory(registry, "targetBeingHeld");
		proto::fightitems::ai::RegisterTargetIsHumanConditionFactory(registry, "targetIsHuman");
		proto::fightitems::motion::RegisterGrabSlotFactories(registry);
		proto::fightitems::motion::RegisterSetGrabIntersectionPropertiesTrackFactory(registry, "setGrabIntersectionProperties");
		proto::fightitems::motion::RegisterGrabTargetClearTrackFactory(registry, "grabTargetClear");
		proto::fightitems::ai::RegisterShouldSpawnConditionFactory(registry, "shouldSpawn");
		proto::fightitems::ai::RegisterSpawnTemplateConditionFactory(registry, "spawnTemplate");
		proto::fightitems::ai::RegisterThreatCanGrabConditionFactory(registry, "threatCanBeGrabbed");
		proto::fightitems::motion::RegisterStunnedFactories(registry);
		proto::fightitems::ai::RegisterThreatStoreConditionFactory(registry, "threatStore");
		proto::fightitems::ai::RegisterShouldRadioHQConditionFactory(registry, "shouldRadioHQ");
		proto::fightitems::ai::RegisterIsPoisonedConditionFactory(registry, "isPoisoned");
		proto::fightitems::ai::RegisterPoisonedTimeConditionFactory(registry, "poisonedTime");
		proto::fightitems::ai::RegisterNPCLODConditionFactory(registry, "npcLOD");
		proto::fightitems::ai::RegisterCanReserveSoldierBudgetConditionFactory(registry, "canReserveSoldierBudget");
		proto::fightitems::ai::RegisterIsInLoadedCellConditionFactory(registry, "isInLoadedCell");
		proto::fightitems::ai::RegisterSpatialQueryConditionFactory(registry, "npcSpatialQuery");
		proto::fightitems::motion::RegisterHasPatsyFactories(registry);
		proto::fightitems::motion::RegisterFactionFactories(registry);
		proto::fightitems::alert::RegisterDisguiseBlownConditionFactory(registry, "disguiseBlown");
		proto::fightitems::motion::RegisterUndergroundStateFactories(registry);
		proto::fightitems::motion::RegisterAccumulatedDamageFactories(registry);
		proto::fightitems::ai::RegisterInFormationConditionFactory(registry, "inFormation");
		proto::fightitems::ai::RegisterFormationReformingConditionFactory(registry, "formationReforming");
		proto::fightitems::ai::RegisterAtRoofsEdgeConditionFactory(registry, "atRoofsEdge");
		proto::fightitems::ai::RegisterNearRoofsEdgeConditionFactory(registry, "nearRoofsEdge");
		proto::fightitems::ai::RegisterIsInRooftopConditionFactory(registry, "isInRooftop");
		proto::fightitems::ai::RegisterInHotZoneConditionFactory(registry, "inHotZone");
		proto::fightitems::ai::RegisterInBlastAreaConditionFactory(registry, "inBlastArea");
		proto::fightitems::ai::RegisterInReservedAreaConditionFactory(registry, "inReservedArea");
		proto::fightitems::ai::RegisterInsideReservedVolumeConditionFactory(registry, "insideReservedVolume");
		proto::fightitems::ai::RegisterGroundDistanceConditionFactory(registry, "groundDistance");
		proto::fightitems::ai::RegisterStuckConditionFactory(registry, "stuck");
		proto::fightitems::ai::RegisterDestinationTargetOrientationConditionFactory(registry, "destinationTargetOrientation");
		engine::RegisterSupportingSurfaceConditionFactories(registry);
		proto::fightitems::motion::RegisterSupportingLimbTestSurfaceNormalAngleFactories(registry);
		proto::fightitems::ai::RegisterNavMeshAreaConditionFactory(registry, "navmeshArea");
		proto::fightitems::ai::RegisterAnyPlayerDistanceConditionFactory(registry, "anyPlayerDistance");
		proto::fightitems::motion::RegisterHaveIconTypeConditionFactory(registry, "haveIconType");
		proto::fightitems::alert::RegisterPlayerSeenConditionFactory(registry, "playerSeen");
		proto::fightitems::ai::RegisterSetAvoidanceGapAnywhereTrackFactory(registry, "setAvoidanceGapAnywhere");
		proto::fightitems::ai::RegisterInTargetsCameraConditionFactory(registry, "inTargetsCamera");
		proto::fightitems::RegisterAt102061F0Factories(registry);
		proto::fightitems::ai::RegisterAbsoluteHeightConditionFactory(registry, "absoluteHeight");
		proto::fightitems::alert::RegisterShouldCallStrikeTeamConditionFactory(registry, "shouldCallStrikeTeam");
		engine::scenario::RegisterLuaConditionFactory(registry, "lua");
		proto::fightitems::ai::RegisterIdleTrackFactory(registry, "idle");
		proto::fightitems::ai::RegisterFlyingIdleTrackFactory(registry, "flyingIdle");
		proto::fightitems::ai::RegisterAirHoverTrackFactory(registry, "airHover");
		proto::fightitems::ai::RegisterAirDodgeTrackFactory(registry, "airDodge");
		proto::fightitems::ai::RegisterCircleStrafeTrackFactory(registry, "circleStrafe");
		proto::fightitems::ai::RegisterCirclePatrolTrackFactory(registry, "circlePatrol");
		proto::fightitems::ai::RegisterIntersectionCirclePatrolTrackFactory(registry, "intersectionCirclePatrol");
		proto::fightitems::ai::RegisterTryStrafeRunTrackFactory(registry, "tryStrafeRun");
		proto::fightitems::ai::RegisterStrafeRunTrackFactory(registry, "strafeRun");
		proto::fightitems::ai::RegisterTightStrafeRunTrackFactory(registry, "tightStrafeRun");
		proto::fightitems::ai::RegisterPrepareTightStrafeRunTrackFactory(registry, "prepareTightStrafeRun");
		proto::fightitems::ai::RegisterTryOpenStrafeRunTrackFactory(registry, "tryOpenStrafeRun");
		proto::fightitems::ai::RegisterSimpleOpenStrafeRunTrackFactory(registry, "simpleOpenStrafeRun");
		proto::fightitems::ai::RegisterPredefinedPatrolTrackFactory(registry, "predefinedPatrol");
		proto::fightitems::ai::RegisterLandTrackFactory(registry, "land");
		proto::fightitems::ai::RegisterTakeOffTrackFactory(registry, "takeoff");
		proto::fightitems::ai::RegisterZiplineTakeOffTrackFactory(registry, "ziplineTakeOff");
		proto::fightitems::ai::RegisterZiplineLandTrackFactory(registry, "ziplineLand");
		proto::fightitems::ai::RegisterForceEmotionalStateTrackFactory(registry, "forceEmotionalState");
		proto::fightitems::ai::RegisterMessageTrackFactory(registry, "aiMessage");
		proto::fightitems::ai::RegisterPeriodicMessageTrackFactory(registry, "aiPeriodicMessage");
		proto::fightitems::ai::RegisterCheckBodyTrackFactory(registry, "checkBody");
		proto::fightitems::ai::RegisterExecuteTaskTrackFactory(registry, "executeTask");
		proto::fightitems::ai::RegisterSpawnTaskTrackFactory(registry, "spawnTask");
		proto::fightitems::ai::RegisterGoToTrackFactory(registry, "goto");
		proto::fightitems::ai::RegisterFixedDestinationGotoTrackFactory(registry, "fixedDestinationGoto");
		proto::fightitems::ai::RegisterFixedDestinationFlytoTrackFactory(registry, "fixedDestinationFlyto");
		proto::fightitems::ai::RegisterPatrolTrackFactory(registry, "patrol");
		proto::fightitems::ai::RegisterPathPatrolTrackFactory(registry, "pathPatrol");
		proto::fightitems::ai::RegisterDestinationGoToTrackFactory(registry, "destinationGoTo");
		proto::fightitems::ai::RegisterDestinationFlyToTrackFactory(registry, "destinationFlyTo");
		proto::fightitems::ai::RegisterDestinationJumpToTrackFactory(registry, "destinationJumpTo");
		proto::fightitems::ai::RegisterAimTrackFactory(registry, "aim");
		proto::fightitems::ai::RegisterHelicopterStrafeModeTrackFactory(registry, "helicopterStrafeMode");
		proto::fightitems::ai::RegisterStopTrackFactory(registry, "dontMove");
		proto::fightitems::ai::RegisterSpeedTrackFactory(registry, "speed");
		proto::fightitems::ai::RegisterTempSpeedTrackFactory(registry, "tempSpeed");
		proto::fightitems::ai::RegisterReservePositionTrackFactory(registry, "reservePosition");
		proto::fightitems::ai::RegisterReserveTargetsPositionTrackFactory(registry, "reserveTargetsPosition");
		proto::fightitems::ai::RegisterReserveVolumeTrackFactory(registry, "reserveVolume");
		proto::fightitems::ai::RegisterReserveHydraPositionTrackFactory(registry, "reserveHydraPosition");
		proto::fightitems::motion::RegisterClearPatsyTrackFactory(registry, "clearPatsy");
		proto::fightitems::motion::RegisterClearFailedPatsyTrackFactory(registry, "clearFailedPatsy");
		proto::fightitems::ai::RegisterCombatDestinationFindTrackFactory(registry, "combatDestinationFind");
		proto::fightitems::ai::RegisterRooftopDestinationFindTrackFactory(registry, "rooftopDestinationFind");
		proto::fightitems::ai::RegisterActionTrackFactory(registry, "action");
		proto::fightitems::ai::RegisterRequestTokenTrackFactory(registry, "requestToken");
		proto::fightitems::ai::RegisterRefreshStrafeRunTokenTrackFactory(registry, "refreshStrafeRunToken");
		proto::fightitems::ai::RegisterTargetTokenBoostTrackFactory(registry, "targetTokenBoost");
		proto::fightitems::ai::RegisterTargetGoToTrackFactory(registry, "targetGoTo");
		proto::fightitems::ai::RegisterFleeTrackFactory(registry, "flee");
		proto::fightitems::motion::RegisterVariableIntSetTrackFactory(registry, "variableIntSet");
		proto::fightitems::motion::RegisterVariableNameSetTrackFactory(registry, "variableNameSet");
		proto::fightitems::motion::RegisterTimerSetTrackFactory(registry, "timerSet");
		proto::fightitems::motion::RegisterTimerContinousSetTrackFactory(registry, "timerContinousSet");
		proto::fightitems::ai::RegisterDrawDebugTrackFactory(registry, "drawDebug");
		proto::fightitems::ai::RegisterAiTreeEventSendTrackFactory(registry, "eventSend");
		proto::fightitems::ai::RegisterSetVehicleStateTrackFactory(registry, "setVehicleState");
		proto::fightitems::ai::RegisterSetUserTooltipTrackFactory(registry, "setUserTooltip");
		proto::fightitems::ai::RegisterPlayDebugDialogTrackFactory(registry, "playDebugDialog");
		proto::fightitems::ai::RegisterThreatMemoryResetTrackFactory(registry, "threatMemoryReset");
		proto::fightitems::ai::RegisterThreatDodgeTrackFactory(registry, "threatDodge");
		proto::fightitems::ai::RegisterConditionalExecuteTrackFactory(registry, "conditionalExecute");
		proto::fightitems::ai::RegisterPeriodicOpportunityTrackFactory(registry, "periodicOpportunity");
		proto::fightitems::ai::RegisterDelayedSequenceTrackFactory(registry, "delayedSequence");
		proto::fightitems::ai::RegisterForceRecalculatePathTrackFactory(registry, "forceRecalculatePath");
		proto::fightitems::ai::RegisterForceMotionTrackFactory(registry, "forceMotion");
		proto::fightitems::ai::RegisterFollowTargetTrackFactory(registry, "followTarget");
		proto::fightitems::ai::RegisterFollowFormationTrackFactory(registry, "followFormation");
		proto::fightitems::ai::RegisterReformTrackFactory(registry, "reform");
		proto::fightitems::ai::RegisterSetBrakeDistanceTrackFactory(registry, "setBrakeDistance");
		proto::fightitems::ai::RegisterDumbGotoTrackFactory(registry, "dumbGoto");
		proto::fightitems::ai::RegisterDumbGotoLODTrackFactory(registry, "dumbGotoLOD");
		proto::fightitems::ai::RegisterTankRamTrackFactory(registry, "tankRam");
		proto::fightitems::ai::RegisterActivateVehicleBehaviourTrackFactory(registry, "activateVehicleBehaviour");
		proto::fightitems::ai::RegisterActivateScaryMonsterBehaviourTrackFactory(registry, "activateScaryMonster");
		proto::fightitems::ai::RegisterDestinationSetDeadBodyTrackFactory(registry, "destinationSetDeadBody");
		proto::fightitems::ai::RegisterDrawObjectDebugTrackFactory(registry, "drawObjectDebug");
		proto::fightitems::ai::RegisterFixedDestinationJumpToTrackFactory(registry, "fixedDestinationJumpTo");
		proto::fightitems::ai::RegisterClearFixedAreaDestinationTrackFactory(registry, "clearFixedAreaDestination");
		proto::fightitems::ai::RegisterCommanderInCombatTrackFactory(registry, "commanderInCombat");
		proto::fightitems::ai::RegisterUnDowngradableTrackFactory(registry, "unDowngradable");
		proto::fightitems::ai::RegisterUpdateSoldierReservationBudgetTrackFactory(registry, "updateSoldierReservationBudget");
		proto::fightitems::ai::RegisterCharacterizeFromReservedTrackFactory(registry, "characterizeFromReserved");
		proto::fightitems::ai::RegisterCharacterizeTrackFactory(registry, "characterize");
		proto::fightitems::ai::RegisterLodGotoFixedDestinationTrackFactory(registry, "lodGotoFixedDestinationAction");
		proto::fightitems::ai::RegisterEnableLODPatrolTrackFactory(registry, "enableLODPatrolTrack");
		proto::fightitems::ai::RegisterStayOnRoofTrackFactory(registry, "stayOnRoof");
		proto::fightitems::ai::RegisterBlindTrackFactory(registry, "blind");
		proto::fightitems::motion::RegisterHUDMarkerTrackFactory(registry, "HUDMarker");
		proto::fightitems::motion::RegisterVariableIntTemporarySetTrackFactory(registry, "variableIntTemporarySet");
		proto::fightitems::motion::RegisterAccumulatedDamageResetTrackFactory(registry, "accumulatedDamageReset");
		proto::fightitems::motion::RegisterGrabSlotDetachTrackFactory(registry, "grabSlotDetach");
		proto::fightitems::vehicle::RegisterSetPanicStateTrackFactory(registry, "setVehiclePanicState");
		proto::fightitems::vehicle::RegisterSpawnCopsOffScreenTrackFactory(registry, "spawnCopsOffScreen");
		proto::fightitems::vehicle::RegisterSpawnCopsBesideCarTrackFactory(registry, "spawnCopsBesideCar");
		engine::scenario::RegisterLuaTrackFactory(registry, "lua");
		proto::fightitems::motion::RegisterVehiclePlayAnimationTrackFactory(registry, "vehiclePlayAnimation");
		engine::RegisterScenarioStringTrackFactory(registry, "scenario_PostEventString");
		engine::RegisterAudioTrackFactories(registry);
		engine::RegisterPlaybackTrackFactory(registry, "playback");
		registry->Prepare();
		registry->Complete();
	}

	// FUNCTION: ENGINE 0x10092140
	void MakeAlertContext()
	{
		engine::LoadListeners* listeners = engine::gLoadListeners;
		fight::TrackRegistry* registry = new fight::TrackRegistry;
		registry->SetName(fight::Name("Alert", 1));
		listeners->AddContext(registry);
		fight::RegisterBranchFactories(registry);
		fight::RegisterCoreFactories(registry);
		fight::RegisterCoreTrackFactories(registry);
		fight::RegisterFlowTrackFactories(registry);
		proto::fightitems::alert::RegisterBlowDisguiseTrackFactory(registry, "blowDisguise");
		proto::fightitems::alert::RegisterReactionTrackFactory(registry, "reaction");
		proto::fightitems::alert::RegisterSetAlertVariableTrackFactory(registry, "alertVariableSet");
		proto::fightitems::alert::RegisterResetAlertVariablesTrackFactory(registry, "alertVariablesReset");
		proto::fightitems::alert::RegisterSetInPursuitTrackFactory(registry, "pursuitSet");
		proto::fightitems::alert::RegisterScenarioMessageTrackFactory(registry, "scenarioMessage");
		proto::fightitems::alert::RegisterStartStrikeTeamMeterTrackFactory(registry, "strikeTeamStart");
		proto::fightitems::alert::RegisterStopStrikeTeamMeterTrackFactory(registry, "strikeTeamStop");
		proto::fightitems::motion::RegisterPatsyCreateTrackFactory(registry, "patsyCreate");
		proto::fightitems::motion::RegisterClearPatsyTrackFactory(registry, "clearPatsy");
		proto::fightitems::motion::RegisterClearFailedPatsyTrackFactory(registry, "clearFailedPatsy");
		proto::fightitems::alert::RegisterRadioedSetTrackFactory(registry, "radioedSet");
		proto::fightitems::alert::RegisterAlertReportTrackFactory(registry, "alertReport");
		proto::fightitems::ai::RegisterConditionalExecuteTrackFactory(registry, "conditionalExecute");
		proto::fightitems::alert::RegisterDisablePoliceTrackFactory(registry, "disablePolice");
		proto::fightitems::alert::RegisterReportBackToIdleTrackFactory(registry, "reportBackToIdle");
		proto::fightitems::alert::RegisterReportEnterBeginCombatTrackFactory(registry, "reportEnterBeginCombat");
		engine::RegisterAudioTrackFactories(registry);
		engine::scenario::RegisterLuaConditionFactory(registry, "lua");
		engine::scenario::RegisterLuaTrackFactory(registry, "lua");
		proto::fightitems::alert::RegisterAlertVariableFactories(registry);
		proto::fightitems::alert::RegisterDisguiseBlownConditionFactory(registry, "disguiseBlown");
		proto::fightitems::alert::RegisterDisguiseReactionConditionFactory(registry, "disguiseReaction");
		proto::fightitems::motion::RegisterHasPatsyFactories(registry);
		proto::fightitems::motion::RegisterFactionFactories(registry);
		proto::fightitems::ai::RegisterDumpAlertCharactersTrackFactory(registry, "dumpAlertCharacters");
		registry->Prepare();
		registry->Complete();
	}

	// FUNCTION: ENGINE 0x10092330
	void MakeMusicContext()
	{
		engine::LoadListeners* listeners = engine::gLoadListeners;
		fight::TrackRegistry* registry = new fight::TrackRegistry;
		registry->SetName(fight::Name("Music", 1));
		listeners->AddContext(registry);
		fight::RegisterBranchFactories(registry);
		fight::RegisterCoreFactories(registry);
		fight::RegisterCoreTrackFactories(registry);
		fight::RegisterFlowTrackFactories(registry);
		engine::RegisterAudioTrackFactories(registry);
		proto::fightitems::alert::RegisterDisguiseReactionConditionFactory(registry, "disguiseReaction");
		proto::fightitems::ai::RegisterInfectedAlertedConditionFactory(registry, "infectedAlerted");
		registry->Prepare();
		registry->Complete();
	}

	// FUNCTION: ENGINE 0x100923F0
	void MakeVehicleContext()
	{
		engine::LoadListeners* listeners = engine::gLoadListeners;
		fight::TrackRegistry* registry = new fight::TrackRegistry;
		registry->SetName(fight::Name("Vehicle", 1));
		listeners->AddContext(registry);
		fight::RegisterBranchFactories(registry);
		fight::RegisterCoreFactories(registry);
		fight::RegisterCoreTrackFactories(registry);
		fight::RegisterFlowTrackFactories(registry);
		proto::fightitems::ai::RegisterFacingAngleTargetConditionFactory(registry, "facingAngleTarget");
		proto::fightitems::ai::RegisterTargetingFactories(registry);
		proto::fightitems::motion::RegisterTargetAngleConditionFactory(registry, "targetAngle");
		proto::fightitems::motion::RegisterTargetDistanceConditionFactory(registry, "targetDistance");
		proto::fightitems::vehicle::RegisterAvoidObstaclesTrackFactory(registry, "avoidObstacles");
		proto::fightitems::vehicle::RegisterPanicTrackFactory(registry, "panic");
		proto::fightitems::vehicle::RegisterTerminateTrackFactory(registry, "terminate");
		proto::fightitems::vehicle::RegisterReturnToNormalTrackFactory(registry, "returnToNormal");
		proto::fightitems::vehicle::RegisterStateConditionFactory(registry, "state");
		proto::fightitems::vehicle::RegisterEBrakeTrackFactory(registry, "e_brake");
		proto::fightitems::vehicle::RegisterSpeedConditionFactory(registry, "speed");
		proto::fightitems::vehicle::RegisterFishTailTrackFactory(registry, "fishTail");
		proto::fightitems::vehicle::RegisterWaitingForObjectConditionFactory(registry, "waitingForObj");
		proto::fightitems::vehicle::RegisterVehicleNameConditionFactory(registry, "vehicleName");
		proto::fightitems::ai::RegisterEmotionalStateConditionFactory(registry, "emotionalState");
		proto::fightitems::ai::RegisterThreatBallTrackFactory(registry, "threatBall");
		engine::RegisterEffectTrackFactory(registry, "effect");
		engine::RegisterAbortEffectTrackFactory(registry, "abortEffect");
		engine::RegisterAudioTrackFactories(registry);
		registry->Prepare();
		registry->Complete();
	}

	// FUNCTION: ENGINE 0x10092590
	void ExtendPlaybackContext()
	{
		engine::LoadListeners* listeners = engine::gLoadListeners;
		if (listeners != 0)
		{
			fight::TrackRegistry* registry = listeners->FindContext(fight::Name(engine::gPlaybackContextName, 1));
			if (registry != 0)
			{
				engine::scenario::RegisterLuaConditionFactory(registry, "lua");
				proto::fightitems::motion::RegisterGrabSlotFactories(registry);
				proto::fightitems::motion::RegisterDebugLayerFactories(registry);
				proto::fightitems::motion::RegisterDeformTrackFactory(registry, "deform");
				proto::fightitems::motion::RegisterCollisionHitTrackFactory(registry, "hit");
				proto::fightitems::motion::RegisterHitReactionTrackFactory(registry, "hitReaction");
				proto::fightitems::motion::RegisterTargetClassTrackFactory(registry, "targetClass");
				proto::fightitems::playback::RegisterSpawnObjectTrackFactory(registry, "spawnObject");
				proto::fightitems::playback::RegisterManageLifetimeTrackFactory(registry, "manageLifetime");
				proto::fightitems::ai::RegisterMessageTrackFactory(registry, "aiMessage");
				proto::fightitems::ai::RegisterPeriodicMessageTrackFactory(registry, "aiPeriodicMessage");
				proto::fightitems::motion::RegisterFXLight_PointTrackFactory(registry, "fxlight_point");
				proto::fightitems::motion::RegisterRadialBlurTrackFactory(registry, "radialBlur");
				proto::fightitems::render::RegisterFogTrackFactory(registry, "FX_fog");
				proto::fightitems::render::RegisterTimeOfDayBlendTrackFactory(registry, "FX_TimeOfDayBlend");
				proto::fightitems::render::RegisterDistanceToCameraConditionFactory(registry, "distanceToCamera");
				proto::fightitems::render::RegisterGPUFillConditionFactory(registry, "gpuFill");
				engine::RegisterMotionTrailTrackFactory(registry, "motionTrail");
				proto::fightitems::motion::RegisterDeathTrackFactory(registry, "characterDeath");
				proto::fightitems::motion::RegisterImpulseTrackFactory(registry, "Impulse");
				proto::fightitems::RegisterAt10502080Factories(registry);
				proto::fightitems::RegisterAt103591C0Factories(registry);
				proto::fightitems::RegisterPhysicsLODAndDoorsFactories(registry);
				engine::animation::RegisterShaderAnimationTrackFactory(registry, "shaderAnimation");
				engine::scenario::RegisterLuaTrackFactory(registry, "lua");
				proto::fightitems::playback::RegisterShootTrackFactory(registry, "shoot");
				proto::fightitems::playback::RegisterSuckIntoPlayerTrackFactory(registry, "suckIntoPlayer");
				fight::RegisterWaitTrackFactory(registry, "wait");
				proto::fightitems::ai::RegisterReserveTargetsPositionTrackFactory(registry, "reserveTargetsPosition");
				proto::fightitems::ai::RegisterThreatBallTrackFactory(registry, "threatBall");
				engine::RegisterSetEffectTimerTrackFactory(registry, "setEffectTimer");
				engine::RegisterCheckEffectTimerConditionFactory(registry, "checkEffectTimer");
				engine::RegisterDeleteAllDecalsTrackFactory(registry, "deleteAllDecals");
				engine::RegisterCollisionEnableByNameTrackFactory(registry, "collisionEnableByName");
				proto::fightitems::playback::RegisterWasShotByPlayerConditionFactory(registry, "wasShotByPlayer");
				proto::fightitems::motion::RegisterPadRumbleClearFactories(registry);
				proto::fightitems::motion::RegisterSlowMotionTrackFactory(registry, "slowMotion");
				proto::fightitems::motion::RegisterGrabSlotDeathTrackFactory(registry, "grabSlotDeath");
				proto::fightitems::motion::RegisterSetVehicleSolverEnabledTrackFactory(registry, "SetVehicleSolverEnabled");
				proto::fightitems::motion::RegisterSetVehicleAnimatedTrackFactory(registry, "SetVehicleAnimated");
				proto::fightitems::motion::RegisterSetVehicleHeadlightTrackFactory(registry, "SetVehicleHeadlight");
				proto::fightitems::motion::RegisterHelicopterRotorCollisionFactories(registry);
				fight::RegisterSpawnTrackFactory(registry, "spawn");
				registry->Prepare();
				registry->Complete();
			}
		}
	}

	// FUNCTION: ENGINE 0x10092820
	void MakeHitEffectContext()
	{
		engine::LoadListeners* listeners = engine::gLoadListeners;
		if (listeners != 0)
		{
			fight::TrackRegistry* registry = new fight::TrackRegistry;
			registry->SetName(fight::Name(engine::gHitEffectContextName, 1));
			listeners->AddContext(registry);
			fight::RegisterBranchFactories(registry);
			fight::RegisterCoreFactories(registry);
			fight::RegisterCoreTrackFactories(registry);
			fight::RegisterFlowTrackFactories(registry);
			proto::fightitems::RegisterAt103591C0Factories(registry);
			proto::fightitems::RegisterAt104F3900Factories(registry);
			engine::RegisterAudioTrackFactories(registry);
			engine::RegisterScenarioStringTrackFactory(registry, "scenario_PostEventString");
			proto::fightitems::ai::RegisterMessageTrackFactory(registry, "aiMessage");
			proto::fightitems::ai::RegisterPeriodicMessageTrackFactory(registry, "aiPeriodicMessage");
			proto::fightitems::citymanager::RegisterInZoneConditionFactory(registry, "inZone");
			proto::fightitems::motion::RegisterCollisionHitTrackFactory(registry, "hit");
			proto::fightitems::motion::RegisterDecalTrackFactory(registry, "decalCharacter");
			proto::fightitems::motion::RegisterRadialBlurTrackFactory(registry, "radialBlur");
			proto::fightitems::motion::RegisterMotionStateConditionFactory(registry, "motionState");
			proto::fightitems::motion::RegisterClassNameConditionFactory(registry, "className");
			proto::fightitems::motion::RegisterGrabbableClassConditionFactory(registry, "grabbableClass");
			proto::fightitems::motion::RegisterPadRumbleClearFactories(registry);
			proto::fightitems::playback::RegisterSpawnObjectTrackFactory(registry, "spawnObject");
			proto::fightitems::playback::RegisterManageLifetimeTrackFactory(registry, "manageLifetime");
			proto::fightitems::render::RegisterFogTrackFactory(registry, "FX_fog");
			proto::fightitems::render::RegisterTimeOfDayBlendTrackFactory(registry, "FX_TimeOfDayBlend");
			proto::fightitems::render::RegisterDistanceToCameraConditionFactory(registry, "distanceToCamera");
			proto::fightitems::render::RegisterGPUFillConditionFactory(registry, "gpuFill");
			engine::RegisterSetEffectTimerTrackFactory(registry, "setEffectTimer");
			engine::RegisterCheckEffectTimerConditionFactory(registry, "checkEffectTimer");
			engine::RegisterEffectLODBiasTrackFactory(registry, "effectLODBias");
			engine::RegisterEffectLODSwitchTrackFactory(registry, "effectLODSwitch");
			engine::RegisterEffectLODDisableTrackFactory(registry, "effectLODDisable");
			engine::RegisterPlaybackStateConditionFactory(registry, "playbackState");
		}
	}

	// FUNCTION: ENGINE 0x10092A10
	void ExtendNISContext()
	{
		engine::LoadListeners* listeners = engine::gLoadListeners;
		if (listeners != 0)
		{
			fight::TrackRegistry* registry = listeners->FindContext(fight::Name(engine::gNISContextName, 1));
			if (registry != 0)
			{
				proto::fightitems::render::RegisterFogTrackFactory(registry, "FX_fog");
				proto::fightitems::render::RegisterTimeOfDayBlendTrackFactory(registry, "FX_TimeOfDayBlend");
				proto::fightitems::motion::RegisterFXLight_PointTrackFactory(registry, "fxlight_point");
				proto::RegisterNISExcludeVolumeTrackFactory(registry, "excludeVolume");
				proto::RegisterFMVTrackFactory(registry, "fmv");
				proto::fightitems::RegisterAt103591C0Factories(registry);
				proto::fightitems::motion::RegisterRadialBlurTrackFactory(registry, "radialBlur");
				proto::fightitems::motion::RegisterPadRumbleClearFactories(registry);
				proto::fightitems::RegisterAt104FB8A0Factories(registry);
				proto::fightitems::RegisterAt105020B0Factories(registry);
				proto::fightitems::motion::RegisterNISConsumeByParentTrackFactory(registry, "consumeByParent");
				registry->Prepare();
				registry->Complete();
			}
		}
	}



	// FUNCTION: ENGINE 0x10092AF0
	// EQUIVALENT: the same calls with the same arguments in the same order; the engine keeps the listeners in ebx and the
	// contexts in esi and edi, and reserves 16 bytes for the temporary names where ours reserves 8 (95.5 %)
	void RegisterFightContexts()
	{
		engine::LoadListeners* listeners = engine::gLoadListeners;
		fight::SetEventMaskTable(gFightEventMasks, gFightEventMaskCount);
		engine::GetScriptHook(&gPreviousScriptHook, &gPreviousScriptHookData);
		engine::SetScriptHook(FightScriptHook, 0);
		fight::TrackRegistry* registry = listeners->FindContext(fight::Name(engine::gPropLogicContextName, 1));
		proto::fightitems::motion::RegisterReactionThrowTrackFactory(registry, "reactionThrow");
		proto::fightitems::proplogic::RegisterWaitOnCollisionTrackFactory(registry, "waitOnCollision");
		proto::fightitems::ai::RegisterRequestCombatBudgetTokenTrackFactory(registry, "requestCombatBudgetToken");
		proto::fightitems::ai::RegisterUnDowngradableTrackFactory(registry, "unDowngradable");
		proto::fightitems::motion::RegisterStunTrackFactory(registry, "stun");
		proto::fightitems::ai::RegisterMessageTrackFactory(registry, "aiMessage");
		proto::fightitems::motion::RegisterReactionEventConditionGroupFactories(registry);
		proto::fightitems::proplogic::RegisterShootingEventConditionFactory(registry, "shootingEvent");
		proto::fightitems::ai::RegisterHasCombatBudgetTokenConditionFactory(registry, "hasCombatBudgetToken");
		proto::fightitems::motion::RegisterClassNameConditionFactory(registry, "className");
		proto::fightitems::motion::RegisterHelicopterRotorCollisionFactories(registry);
		proto::fightitems::ai::RegisterNPCLODConditionFactory(registry, "npcLOD");
		proto::fightitems::ai::RegisterDriverStateConditionFactory(registry, "driverState");
		proto::fightitems::ai::RegisterEmotionalStateConditionFactory(registry, "emotionalState");
		proto::fightitems::motion::RegisterPadRumbleClearFactories(registry);
		proto::fightitems::motion::RegisterGrabSlotFactories(registry);
		proto::fightitems::RegisterAt104FAC90Factories(registry);
		proto::fightitems::motion::RegisterJointOrientationConditionFactory(registry, "jointOrientation");
		registry->Prepare();
		registry->Complete();
		registry = listeners->FindContext(fight::Name(engine::gScenarioContextName, 1));
		proto::fightitems::RegisterAt101D7500Factories(registry);
		proto::fightitems::RegisterAt101D6DA0Factories(registry);
		proto::fightitems::RegisterAt101D8B60Factories(registry);
		proto::RegisterFMVTrackFactory(registry, "FMV");
		engine::framebufferfx::RegisterToneMapTrackFactory(registry, "FX_toneMap");
		engine::framebufferfx::RegisterDepthOfFieldTrackFactory(registry, "FX_depthOfField");
		engine::framebufferfx::RegisterBloomTrackFactory(registry, "FX_bloom");
		engine::framebufferfx::RegisterScatterTrackFactory(registry, "FX_scatter");
		engine::framebufferfx::RegisterColourMatrixTrackFactory(registry, "FX_colourMatrix");
		proto::fightitems::render::RegisterTimeOfDayBlendTrackFactory(registry, "FX_TimeOfDayBlend");
		proto::fightitems::motion::RegisterSlowMotionTrackFactory(registry, "slowMotion");
		proto::fightitems::RegisterPunchinCameraFactory(registry, "punchinCamera");
		proto::RegisterNISExcludeVolumeTrackFactory(registry, "excludeVolume");
		proto::fightitems::scenario::RegisterStateMachineStartTrackFactory(registry, "stateMachine_Start");
		proto::fightitems::scenario::RegisterStateMachineTransitionTrackFactory(registry, "stateMachine_Transition");
		proto::fightitems::scenario::RegisterStateMachineStopTrackFactory(registry, "stateMachine_StopCurrent");
		proto::fightitems::scenario::RegisterCurrentStateFactories(registry);
		proto::fightitems::scenario::RegisterPackageLoadTrackFactory(registry, "packageLoad");
		proto::fightitems::scenario::RegisterPackageUnloadTrackFactory(registry, "packageUnload");
		proto::fightitems::scenario::RegisterPackageReadyConditionFactory(registry, "packageReady");
		proto::fightitems::scenario::RegisterAlertStatusFactories(registry);
		proto::fightitems::scenario::RegisterEvent_MotionStateConditionFactory(registry, "event_MotionState");
		proto::fightitems::freeroamevents::RegisterFREventTriggerTestFactories(registry);
		proto::fightitems::ai::RegisterMessageTrackFactory(registry, "aiMessage");
		proto::fightitems::ai::RegisterPeriodicMessageTrackFactory(registry, "aiPeriodicMessage");
		proto::fightitems::RegisterAt1048FCE0Factories(registry);
		registry->Prepare();
		registry->Complete();
		registry = listeners->FindContext(fight::Name(engine::gMotionContextName, 1));
		proto::fightitems::ai::RegisterForceEmotionalStateTrackFactory(registry, "forceEmotionalState");
		proto::fightitems::RegisterAccelerationFactory(registry, "acceleration");
		proto::fightitems::motion::RegisterAnimationBlendDirectionalTrackFactory(registry, "animationBlendDirectional");
		proto::fightitems::motion::RegisterAnimationBlendVerticalAimTrackFactory(registry, "animationBlendVerticalAim");
		proto::fightitems::motion::RegisterAnimationBlendVerticalAimStrafeTrackFactory(registry, "animationBlendVerticalAimStrafe");
		proto::fightitems::motion::RegisterAnimationChargeTrackFactory(registry, "animationCharge");
		proto::fightitems::motion::RegisterAutoTargetPositionTrackFactory(registry, "autoTargetPosition");
		proto::fightitems::motion::RegisterAutoTargetTrackFactory(registry, "autoTarget");
		proto::fightitems::motion::RegisterPedestrianAutoTargetTrackFactory(registry, "pedestrianAutoTarget");
		proto::fightitems::motion::RegisterAutoTargetClearTrackFactory(registry, "autoTargetClear");
		proto::fightitems::motion::RegisterAutoTargetPlayerTrackFactory(registry, "autoTargetPlayer");
		proto::fightitems::motion::RegisterBloodSplatterTrackFactory(registry, "bloodSplatter");
		proto::fightitems::RegisterBlockFramerCamFactory(registry, "blockFramerCam");
		proto::fightitems::RegisterCameraHintFactory(registry, "cameraHint");
		proto::fightitems::RegisterCameraResetFactory(registry, "cameraReset");
		proto::fightitems::RegisterAt103591C0Factories(registry);
		proto::fightitems::RegisterAt103585C0Factories(registry);
		proto::fightitems::motion::RegisterChargeSetTrackFactory(registry, "chargeSet");
		proto::fightitems::motion::RegisterChargeClearTrackFactory(registry, "chargeClear");
		proto::fightitems::motion::RegisterChargeTrackFactory(registry, "charge");
		proto::fightitems::motion::RegisterClassNameConditionFactory(registry, "className");
		proto::fightitems::motion::RegisterClearCollisionRecordTrackFactory(registry, "clearCollisionRecord");
		proto::fightitems::motion::RegisterCollisionGrabTrackFactory(registry, "grab");
		proto::fightitems::motion::RegisterCollisionHitTrackFactory(registry, "hit");
		proto::fightitems::motion::RegisterConsumeTrackFactory(registry, "consume");
		proto::fightitems::motion::RegisterConsumeMeTrackFactory(registry, "consumeMe");
		proto::fightitems::motion::RegisterConsumeGrabberTrackFactory(registry, "consumeGrabber");
		proto::fightitems::motion::RegisterConsumeByParentTrackFactory(registry, "consumeByParent");
		proto::fightitems::motion::RegisterCrowdTestTrackFactory(registry, "crowdTest");
		proto::fightitems::motion::RegisterDeathTrackFactory(registry, "death");
		proto::fightitems::motion::RegisterDeathOnEndTrackFactory(registry, "deathOnEnd");
		proto::fightitems::motion::RegisterDebugLayerFactories(registry);
		proto::fightitems::motion::RegisterDecalTrackFactory(registry, "decal");
		proto::fightitems::motion::RegisterDeformTrackFactory(registry, "deform");
		proto::fightitems::motion::RegisterDetectTrackFactory(registry, "detect");
		proto::fightitems::motion::RegisterDevastatorTrackFactory(registry, "devastator");
		proto::fightitems::motion::RegisterTendrilDevastatorTrackFactory(registry, "tendrilDevastator");
		proto::fightitems::motion::RegisterDevastatorUsedTrackFactory(registry, "devastatorUsed");
		proto::fightitems::motion::RegisterDevastatorTargetExecuteTrackFactory(registry, "devastatorTargetExecute");
		proto::fightitems::motion::RegisterDevastatorTargetHitTrackFactory(registry, "devastatorTargetHit");
		proto::fightitems::motion::RegisterDevastatorTargetGroundSpikeTrackFactory(registry, "devastatorTargetGroundSpike");
		proto::fightitems::motion::RegisterDistanceToJointConditionFactory(registry, "distanceToJoint");
		proto::fightitems::motion::RegisterInsidePlaneConditionFactory(registry, "insidePlane");
		proto::fightitems::motion::RegisterDisablePlayerControlTrackFactory(registry, "disableplayercontrol");
		proto::fightitems::motion::RegisterDisableTimeWithNoDamageCounterTrackFactory(registry, "disableTimeWithNoDamageCounter");
		proto::fightitems::RegisterDramaticCameraFactory(registry, "dramaticCamera");
		proto::fightitems::motion::RegisterDriftTrackFactory(registry, "drift");
		proto::fightitems::motion::RegisterEdgeNormalFactories(registry);
		proto::fightitems::motion::RegisterEdgeDetectFactories(registry);
		proto::fightitems::motion::RegisterEffectChameleonicSkinTrackFactory(registry, "effectChameleonicSkin");
		proto::fightitems::motion::RegisterEffectConsumeTrackFactory(registry, "effectConsume");
		proto::fightitems::motion::RegisterFallTrackFactory(registry, "fall");
		proto::fightitems::motion::RegisterFXLight_PointTrackFactory(registry, "fxlight_point");
		proto::fightitems::motion::RegisterFlyingAttackTrackFactory(registry, "flyingAttack");
		proto::fightitems::motion::RegisterFlyingAutoTargetTrackFactory(registry, "flyingAutoTarget");
		proto::fightitems::motion::RegisterFlyingBrakeTrackFactory(registry, "flyingBrake");
		proto::fightitems::motion::RegisterFlyingDashTrackFactory(registry, "flyingDash");
		proto::fightitems::motion::RegisterFlyingGroundAttackTrackFactory(registry, "flyingGroundAttack");
		proto::fightitems::motion::RegisterFootstepTrackFactory(registry, "footstep");
		proto::fightitems::motion::RegisterFootstepDamageTrackFactory(registry, "footstepDamage");
		proto::fightitems::motion::RegisterFreezeScaleTrackFactory(registry, "freezeScale");
		proto::fightitems::motion::RegisterGenderConditionFactory(registry, "gender");
		proto::fightitems::motion::RegisterGrabButtonStruggleTrackFactory(registry, "grabButtonStruggle");
		proto::fightitems::motion::RegisterGrabObjectFromChildGrabSlotTrackFactory(registry, "grabObjectFromChildGrabSlot");
		proto::fightitems::motion::RegisterGrabObjectFromParentGrabSlotTrackFactory(registry, "grabObjectFromParentGrabSlot");
		proto::fightitems::motion::RegisterDelayCollisionWithGrabbedTrackFactory(registry, "delayCollisionWithGrabbed");
		proto::fightitems::motion::RegisterGrabSlotDeathTrackFactory(registry, "grabSlotDeath");
		proto::fightitems::motion::RegisterGrabSlotDetachTrackFactory(registry, "grabSlotDetach");
		proto::fightitems::motion::RegisterGrabSlotDetachThrowTrackFactory(registry, "grabSlotDetachThrow");
		proto::fightitems::motion::RegisterGrabSlotExecuteTrackFactory(registry, "grabSlotExecute");
		proto::fightitems::motion::RegisterGrabSlotExecuteUsingChildTrackFactory(registry, "grabSlotExecuteUsingChild");
		proto::fightitems::motion::RegisterGrabSlotReverseAttachmentTrackFactory(registry, "grabSlotReverseAttachment");
		proto::fightitems::motion::RegisterGrabSlotSwapTrackFactory(registry, "grabSlotSwap");
		proto::fightitems::motion::RegisterGrabSlotUpdateAttachmentTrackFactory(registry, "grabSlotUpdateAttachment");
		proto::fightitems::motion::RegisterGrabSlotUpdateAttachmentWithRestoreTrackFactory(registry, "grabSlotUpdateAttachmentWithRestore");
		proto::fightitems::motion::RegisterGrabbedDetachTrackFactory(registry, "grabbedDetach");
		proto::fightitems::motion::RegisterGrabbedExecuteOnParentTrackFactory(registry, "grabbedExecuteOnParent");
		proto::fightitems::motion::RegisterGrabbedExecuteUsingParentTrackFactory(registry, "grabbedExecuteUsingParent");
		proto::fightitems::motion::RegisterGrabbedSwapGrabberSlotsTrackFactory(registry, "grabbedSwapGrabberSlots");
		proto::fightitems::motion::RegisterGrabbedUpdateAttachmentTrackFactory(registry, "grabbedUpdateAttachment");
		proto::fightitems::motion::RegisterGrabPlayerTrackFactory(registry, "grabPlayer");
		proto::fightitems::motion::RegisterGrabGrabTargetTrackFactory(registry, "grabGrabTarget");
		proto::fightitems::motion::RegisterGrabSetGrabbingTimerTrackFactory(registry, "grabSetGrabbingTimer");
		proto::fightitems::motion::RegisterSetGrabIntersectionPropertiesTrackFactory(registry, "setGrabIntersectionProperties");
		proto::fightitems::motion::RegisterGrabTargetClearTrackFactory(registry, "grabTargetClear");
		proto::fightitems::motion::RegisterGrabSlotEnableStuckTestTrackFactory(registry, "grabSlotEnableStuckTest");
		proto::fightitems::motion::RegisterGrabbedPlaybackTrackFactory(registry, "grabbedPlayback");
		proto::fightitems::motion::RegisterGrappleLocoSprintTrackFactory(registry, "grappleLocoSprint");
		proto::fightitems::motion::RegisterGrappleLocoSteerTrackFactory(registry, "grappleLocoSteer");
		proto::fightitems::motion::RegisterGroundSlideTrackFactory(registry, "groundSlide");
		proto::fightitems::motion::RegisterHeliLocoTrackFactory(registry, "heliLoco");
		proto::fightitems::motion::RegisterHitReactionTrackFactory(registry, "hitReaction");
		proto::fightitems::motion::RegisterHitReactionThrowTrackFactory(registry, "hitReactionThrow");
		proto::fightitems::motion::RegisterHitWeaponTrackFactory(registry, "hitWeapon");
		proto::fightitems::motion::RegisterIKSurfaceFixupTrackFactory(registry, "ikSurfaceFixup");
		proto::fightitems::motion::RegisterImpulseTrackFactory(registry, "Impulse");
		proto::fightitems::motion::RegisterIntersectionPropertiesConditionFactory(registry, "intersectionProperties");
		proto::fightitems::motion::RegisterInvulnerableTrackFactory(registry, "invulnerable");
		proto::fightitems::motion::RegisterJawFlapTrackFactory(registry, "jawflap");
		proto::fightitems::motion::RegisterJointAnchorToAnimationTrackFactory(registry, "jointAnchorToAnimation");
		proto::fightitems::motion::RegisterJointLookAtTrackFactory(registry, "jointLookAt");
		proto::fightitems::motion::RegisterJumpTrackFactory(registry, "jump");
		proto::fightitems::motion::RegisterJumpToTrackFactory(registry, "jumpTo");
		proto::fightitems::motion::RegisterJumpYTrackFactory(registry, "jumpY");
		proto::fightitems::motion::RegisterLocoClimbTrackFactory(registry, "locoClimb");
		proto::fightitems::motion::RegisterLocoCrowdTrackFactory(registry, "locoCrowd");
		proto::fightitems::motion::RegisterLocoSprintTrackFactory(registry, "locoSprint");
		proto::fightitems::motion::RegisterLocoSprintChargeTrackFactory(registry, "locoSprintCharge");
		proto::fightitems::motion::RegisterLocoSteerTrackFactory(registry, "locoSteer");
		proto::fightitems::motion::RegisterLocoSteerLeanTrackFactory(registry, "locoSteerLean");
		proto::fightitems::motion::RegisterLocoStrafeTrackFactory(registry, "locoStrafe");
		proto::fightitems::motion::RegisterMoveAtVelocityTrackFactory(registry, "moveAtVelocity");
		proto::fightitems::motion::RegisterMoveChargedTrackFactory(registry, "moveCharged");
		proto::fightitems::motion::RegisterNoPushbackTrackFactory(registry, "noPushback");
		proto::fightitems::motion::RegisterObstacleDistanceFactories(registry);
		proto::fightitems::proplogic::RegisterOnCollisionTrackFactory(registry, "onCollision");
		proto::fightitems::motion::RegisterOrientTrackFactory(registry, "orient");
		proto::fightitems::motion::RegisterWorldOrientTrackFactory(registry, "worldOrient");
		proto::fightitems::RegisterPunchinCameraFactory(registry, "punchinCamera");
		proto::fightitems::motion::RegisterRadialBlurTrackFactory(registry, "radialBlur");
		proto::fightitems::motion::RegisterReactionFloatTrackFactory(registry, "reactionFloat");
		proto::fightitems::motion::RegisterReactionHitApplyImpulseTrackFactory(registry, "reactionHitApplyImpulse");
		proto::fightitems::motion::RegisterReactionHitAnimationTrackFactory(registry, "reactionHitAnimation");
		proto::fightitems::motion::RegisterReactionHitExecuteTrackFactory(registry, "reactionHitExecute");
		proto::fightitems::motion::RegisterReactionHitGrabTrackFactory(registry, "reactionHitGrab");
		proto::fightitems::motion::RegisterReactionHitPushbackAddTrackFactory(registry, "reactionHitPushbackAdd");
		proto::fightitems::motion::RegisterReactionPushbackOrientTrackFactory(registry, "reactionPushbackOrient");
		proto::fightitems::motion::RegisterReactionPushbackTrackFactory(registry, "reactionPushback");
		proto::fightitems::motion::RegisterReactionTargetGiverTrackFactory(registry, "reactionTargetGiver");
		proto::fightitems::motion::RegisterReactionTimeExecuteTrackFactory(registry, "reactionTimeExecute");
		proto::fightitems::motion::RegisterReactionThrowSpinAngleFactories(registry);
		proto::fightitems::motion::RegisterReactionThrowTrackFactory(registry, "reactionThrow");
		proto::fightitems::motion::RegisterScaleJointForConsumeTrackFactory(registry, "scaleJointForConsume");
		proto::fightitems::RegisterScriptedCameraFactory(registry, "scriptedCamera");
		proto::fightitems::motion::RegisterScrubberTrackFactory(registry, "scrubber");
		proto::fightitems::motion::RegisterSetVisibilityTrackFactory(registry, "setVisibility");
		proto::fightitems::motion::RegisterShoulderConFixupTrackFactory(registry, "shoulderConFixup");
		proto::fightitems::motion::RegisterSlowMotionTrackFactory(registry, "slowMotion");
		proto::fightitems::motion::RegisterShieldHealthFactories(registry);
		proto::fightitems::motion::RegisterShieldDeployTrackFactory(registry, "shieldDeploy");
		proto::fightitems::motion::RegisterShieldSetStateTrackFactory(registry, "shieldSetState");
		proto::fightitems::motion::RegisterShieldReflectTrackFactory(registry, "shieldReflect");
		proto::fightitems::motion::RegisterShootTrackFactory(registry, "shoot");
		proto::fightitems::motion::RegisterShootCalculateHitPositionTrackFactory(registry, "shootCalculateHitPosition");
		proto::fightitems::motion::RegisterShootSetAmmoProfileTrackFactory(registry, "shootSetAmmoProfile");
		proto::fightitems::motion::RegisterShootSetUserProfileTrackFactory(registry, "shootSetUserProfile");
		proto::fightitems::motion::RegisterShootTakeAmmoFromParentTrackFactory(registry, "shootTakeAmmoFromParent");
		proto::fightitems::motion::RegisterShootAutoTargetTrackFactory(registry, "shootAutoTarget");
		proto::fightitems::motion::RegisterShootSelectWeaponConfigurationTrackFactory(registry, "shootSelectWeaponConfiguration");
		proto::fightitems::motion::RegisterShootSwitchWeaponConfigurationTrackFactory(registry, "shootSwitchWeaponConfiguration");
		proto::fightitems::motion::RegisterSkidTrackFactory(registry, "skid");
		proto::fightitems::motion::RegisterSkidPedalTrackFactory(registry, "skidPedal");
		proto::fightitems::motion::RegisterSlaveTransformTrackFactory(registry, "slaveTransform");
		proto::fightitems::motion::RegisterSpawnGibTrackFactory(registry, "spawnGib");
		proto::fightitems::motion::RegisterSprintVelocityClearTrackFactory(registry, "sprintVelocityClear");
		proto::fightitems::motion::RegisterSurfaceMoveAtVelocityTrackFactory(registry, "surfaceMoveAtVelocity");
		proto::fightitems::motion::RegisterSupportingLimbSetActiveTrackFactory(registry, "supportingLimbSetActive");
		proto::fightitems::motion::RegisterSupportingLimbSetDirectionTrackFactory(registry, "supportingLimbSetDirection");
		proto::fightitems::motion::RegisterSupportingLimbTestTrackFactory(registry, "supportingLimbTest");
		proto::fightitems::motion::RegisterTargetClassTrackFactory(registry, "targetClass");
		proto::fightitems::motion::RegisterVehicleReticuleTrackFactory(registry, "vehicleReticule");
		proto::fightitems::motion::RegisterThrowTrackFactory(registry, "throw");
		proto::fightitems::motion::RegisterTimerSetTrackFactory(registry, "timerSet");
		proto::fightitems::motion::RegisterTimerContinousSetTrackFactory(registry, "timerContinousSet");
		proto::fightitems::motion::RegisterTransformFadeTrackFactory(registry, "transformFade");
		proto::fightitems::motion::RegisterTransformTrackFactory(registry, "transform");
		proto::fightitems::motion::RegisterTransformCompleteTrackFactory(registry, "transformComplete");
		proto::fightitems::motion::RegisterTransformDesiredTrackFactory(registry, "transformDesired");
		proto::fightitems::motion::RegisterTransformStartTrackFactory(registry, "transformStart");
		proto::fightitems::motion::RegisterTransformationAllowedTrackFactory(registry, "transformationAllowed");
		proto::fightitems::motion::RegisterTransformationDisallowedTrackFactory(registry, "transformationDisallowed");
		proto::fightitems::motion::RegisterTurnRoundTrackFactory(registry, "turnToTargetOrCamera");
		proto::fightitems::motion::RegisterUninterruptibleTrackFactory(registry, "uninterruptible");
		proto::fightitems::motion::RegisterSpecificUninterruptibleTrackFactory(registry, "specificUninterruptible");
		proto::fightitems::motion::RegisterVariableIntSetTrackFactory(registry, "variableIntSet");
		proto::fightitems::motion::RegisterVariableNameSetTrackFactory(registry, "variableNameSet");
		proto::fightitems::motion::RegisterWallExitTrackFactory(registry, "wallExit");
		proto::fightitems::motion::RegisterWallJumpTrackFactory(registry, "wallJump");
		proto::fightitems::motion::RegisterWallJumpUpTrackFactory(registry, "wallJumpUp");
		proto::fightitems::motion::RegisterWallRunTrackFactory(registry, "wallRun");
		proto::fightitems::motion::RegisterWallRunEnterTrackFactory(registry, "wallRunEnter");
		proto::fightitems::motion::RegisterWallOrientTrackFactory(registry, "wallOrient");
		proto::fightitems::motion::RegisterWallSlideTrackFactory(registry, "wallSlide");
		proto::fightitems::motion::RegisterTendrilTrackFactory(registry, "tendril");
		proto::fightitems::motion::RegisterTendrilFromParentTrackFactory(registry, "tendrilFromParent");
		proto::fightitems::motion::RegisterWhipFistExtendTrackFactory(registry, "whipFistExtend");
		proto::fightitems::motion::RegisterWhipFistRetractTrackFactory(registry, "whipFistRetract");
		proto::fightitems::motion::RegisterWhipFistMakeTautTrackFactory(registry, "whipFistMakeTaut");
		proto::fightitems::motion::RegisterWhipFistAnimatedTrackFactory(registry, "whipFistAnimated");
		proto::fightitems::motion::RegisterWhipFistSegmentFixToJointTrackFactory(registry, "whipFistSegmentFixToJoint");
		proto::fightitems::motion::RegisterWhipFistPullParentToTargetTrackFactory(registry, "whipFistPullParentToTarget");
		proto::fightitems::motion::RegisterWhipFistResetTargetTrackFactory(registry, "whipFistResetTarget");
		proto::fightitems::motion::RegisterWhipFistFreezeSegmentsTrackFactory(registry, "whipFistFreezeSegments");
		proto::fightitems::motion::RegisterWhipFistExtendBlockedOrNotConditionFactory(registry, "whipFistExtendBlockedOrNot");
		proto::fightitems::motion::RegisterVehiclePlayAnimationTrackFactory(registry, "vehiclePlayAnimation");
		proto::fightitems::motion::RegisterVehiclePowerOnOffTrackFactory(registry, "VehiclePowerOnOff");
		proto::fightitems::motion::RegisterSetSecondaryWeaponTypeTrackFactory(registry, "SetSecondaryWeaponType");
		proto::fightitems::motion::RegisterSetVehicleSolverEnabledTrackFactory(registry, "SetVehicleSolverEnabled");
		proto::fightitems::motion::RegisterSetVehicleAnimatedTrackFactory(registry, "SetVehicleAnimated");
		proto::fightitems::motion::RegisterSetVehicleHeadlightTrackFactory(registry, "SetVehicleHeadlight");
		proto::fightitems::motion::RegisterHelicopterSpawnBloodtoxTrackFactory(registry, "helicopterSpawnBloodtox");
		proto::fightitems::motion::RegisterMotionStateTrackFactory(registry, "motionState");
		proto::fightitems::motion::RegisterMagneticBootsTrackFactory(registry, "magneticBoots");
		proto::fightitems::motion::RegisterMagneticBootsTestWallTrackFactory(registry, "magneticBootsTestWall");
		proto::fightitems::motion::RegisterMagneticBootsTestCornerTrackFactory(registry, "magneticBootsTestCorner");
		proto::fightitems::motion::RegisterMagneticBootsTurnCornerTrackFactory(registry, "magneticBootsTurnCorner");
		proto::fightitems::motion::RegisterMagneticBootsStickToWallTrackFactory(registry, "magneticBootsStickToWall");
		proto::fightitems::motion::RegisterMagneticBootsResetInfoTrackFactory(registry, "magneticBootsResetInfo");
		proto::fightitems::motion::RegisterMagneticBootsJumpTrackFactory(registry, "magneticBootsJump");
		proto::fightitems::motion::RegisterMagneticBootsTestJumpStuckTrackFactory(registry, "magneticBootsTestJumpStuck");
		proto::fightitems::motion::RegisterMagneticBootsDetachTrackFactory(registry, "magneticBootsDetach");
		proto::fightitems::motion::RegisterMagneticBootsTestDetachTrackFactory(registry, "magneticBootsTestDetach");
		proto::fightitems::motion::RegisterHunterShortRangeLocoTrackFactory(registry, "hunterShortRangeLoco");
		proto::fightitems::motion::RegisterHunterShortRangeHopCornerTrackFactory(registry, "hunterShortRangeHopCorner");
		proto::fightitems::motion::RegisterHunterShortRangeCorner2TrackFactory(registry, "hunterShortRangeCorner");
		proto::fightitems::motion::RegisterHunterLandedTrackFactory(registry, "reportLanded");
		proto::fightitems::motion::RegisterHealthSetMultiplierTrackFactory(registry, "healthSetMultiplier");
		proto::fightitems::motion::RegisterFactionDefaultTrackFactory(registry, "factionFromTransform");
		proto::fightitems::motion::RegisterFactionSetTrackFactory(registry, "factionSet");
		proto::fightitems::motion::RegisterAccumulatedDamageResetTrackFactory(registry, "accumulatedDamageReset");
		proto::fightitems::render::RegisterFogTrackFactory(registry, "FX_fog");
		proto::fightitems::render::RegisterTimeOfDayBlendTrackFactory(registry, "FX_TimeOfDayBlend");
		proto::fightitems::render::RegisterBulletTracerTrackFactory(registry, "FX_BulletTracer");
		proto::fightitems::render::RegisterDistanceToCameraConditionFactory(registry, "distanceToCamera");
		proto::fightitems::render::RegisterGPUFillConditionFactory(registry, "gpuFill");
		engine::RegisterSetEffectTimerTrackFactory(registry, "setEffectTimer");
		engine::RegisterCheckEffectTimerConditionFactory(registry, "checkEffectTimer");
		engine::RegisterDeleteAllDecalsTrackFactory(registry, "deleteAllDecals");
		proto::fightitems::ai::RegisterThreatMemoryResetTrackFactory(registry, "threatMemoryReset");
		proto::fightitems::motion::RegisterTokenSetFloatDelayTrackFactory(registry, "tokenSetFloatDelay");
		proto::fightitems::ai::RegisterForceRecalculatePathTrackFactory(registry, "forceRecalculatePath");
		proto::fightitems::ai::RegisterThreatSendToTargetTrackFactory(registry, "threatSendToTarget");
		proto::fightitems::alert::RegisterHoldOnAlertEventsTrackFactory(registry, "holdOnAlertEvents");
		proto::fightitems::motion::RegisterUndergroundSetTrackFactory(registry, "undergroundSet");
		proto::fightitems::motion::RegisterUnlockableConditionFactory(registry, "unlockable");
		proto::fightitems::motion::RegisterAnchorToGroundTrackFactory(registry, "anchorToGround");
		proto::fightitems::motion::RegisterUndergroundTeleportTrackFactory(registry, "undergroundTeleport");
		proto::fightitems::motion::RegisterPatsyCreateTrackFactory(registry, "patsyCreate");
		proto::fightitems::motion::RegisterClearPatsyTrackFactory(registry, "clearPatsy");
		proto::fightitems::motion::RegisterClearFailedPatsyTrackFactory(registry, "clearFailedPatsy");
		proto::fightitems::motion::RegisterStunTrackFactory(registry, "stun");
		proto::fightitems::motion::RegisterRadioHQTrackFactory(registry, "radioHQ");
		proto::fightitems::motion::RegisterHUDMarkerTrackFactory(registry, "HUDMarker");
		proto::fightitems::motion::RegisterTargetableTrackFactory(registry, "targetable");
		proto::fightitems::motion::RegisterTemporaryTargetableTrackFactory(registry, "temporaryTargetable");
		proto::fightitems::ai::RegisterCombatDestinationFindTrackFactory(registry, "combatDestinationFind");
		proto::fightitems::ai::RegisterRooftopDestinationFindTrackFactory(registry, "rooftopDestinationFind");
		proto::fightitems::motion::RegisterAllowGrabbingTrackFactory(registry, "allowGrabbing");
		proto::fightitems::motion::RegisterScenarioEventRadioAttemptTrackFactory(registry, "scenarioEventRadioAttempt");
		proto::fightitems::ai::RegisterPoisonTrackFactory(registry, "poison");
		proto::fightitems::ai::RegisterCurePoisonTrackFactory(registry, "curePoison");
		proto::fightitems::motion::RegisterCharacterCloudStateFactories(registry);
		proto::fightitems::ai::RegisterConditionalExecuteTrackFactory(registry, "conditionalExecute");
		proto::fightitems::ai::RegisterPeriodicOpportunityTrackFactory(registry, "periodicOpportunity");
		proto::fightitems::ai::RegisterDelayedSequenceTrackFactory(registry, "delayedSequence");
		proto::fightitems::motion::RegisterTempRegenerationTrackFactory(registry, "tempRegeneration");
		proto::fightitems::motion::RegisterTempRegenAbortTrackFactory(registry, "tempRegenAbort");
		proto::fightitems::motion::RegisterJumpAnimationTrackFactory(registry, "jumpAnimation");
		proto::fightitems::motion::RegisterButtonHintShowTrackFactory(registry, "buttonHintShow");
		proto::fightitems::motion::RegisterEnableButtonHintsTrackFactory(registry, "enableButtonHints");
		proto::fightitems::motion::RegisterJointTrackFactory(registry, "joint");
		proto::fightitems::RegisterPhysicsSetIntersectionPropertiesFactory(registry, "physicsSetIntersectionProperties");
		proto::fightitems::motion::RegisterOrientTowardsJumpInPositionTrackFactory(registry, "orientTowardsJumpInPosition");
		proto::fightitems::motion::RegisterJumpFromWaterTrackFactory(registry, "jumpFromWater");
		proto::fightitems::motion::RegisterFromWaterSetJumpToTrackFactory(registry, "fromWaterSetJumpTo");
		proto::fightitems::motion::RegisterIgnoreWaterReactionTrackFactory(registry, "playerIgnoreWaterReaction");
		proto::fightitems::motion::RegisterAnimationBlendSimpleTrackFactory(registry, "animationBlendSimple");
		proto::fightitems::motion::RegisterHideHUDTrackFactory(registry, "hideHUD");
		proto::fightitems::motion::RegisterHideHUDTrackFactory(registry, "hideHUD");
		proto::fightitems::motion::RegisterSetFireRateTimerTrackFactory(registry, "setFireRateTimer");
		proto::fightitems::motion::RegisterLaserTrackFactory(registry, "laser");
		proto::fightitems::motion::RegisterSpecialistDodgeTrackFactory(registry, "specialistDodge");
		proto::fightitems::motion::RegisterIgnoreHitsTrackFactory(registry, "ignoreHits");
		proto::fightitems::ai::RegisterDisableStayOnNavmeshTrackFactory(registry, "disableStayOnNavmesh");
		proto::fightitems::ai::RegisterAddDiversionTrackFactory(registry, "addDiversion");
		proto::fightitems::ai::RegisterShowDisguiseActionHUDTrackFactory(registry, "showDisguiseActionHUD");
		proto::fightitems::ai::RegisterDisguiseActionUsedTrackFactory(registry, "disguiseActionUsed");
		proto::fightitems::ai::RegisterActivateScaryMonsterBehaviourTrackFactory(registry, "activateScaryMonster");
		proto::fightitems::ai::RegisterConfigureScaryMonsterBehaviourTrackFactory(registry, "configureScaryMonster");
		proto::fightitems::ai::RegisterAdjustHydraMovementTrackFactory(registry, "adjustHydraMovement");
		proto::fightitems::ai::RegisterCanGunButtConditionFactory(registry, "canGunButt");
		proto::fightitems::ai::RegisterSpawnTemplateConditionFactory(registry, "spawnTemplate");
		proto::fightitems::alert::RegisterShouldCallStrikeTeamConditionFactory(registry, "shouldCallStrikeTeam");
		proto::fightitems::motion::RegisterHaveIconTypeConditionFactory(registry, "haveIconType");
		proto::fightitems::ai::RegisterThreatBallTrackFactory(registry, "threatBall");
		proto::fightitems::ai::RegisterAiTreeEventSendTrackFactory(registry, "aiTreeEventSend");
		proto::fightitems::motion::RegisterReloadTrackFactory(registry, "reload");
		proto::fightitems::ai::RegisterMessageTrackFactory(registry, "aiMessage");
		proto::fightitems::ai::RegisterPeriodicMessageTrackFactory(registry, "aiPeriodicMessage");
		proto::fightitems::ai::RegisterBlindTrackFactory(registry, "blind");
		proto::fightitems::playback::RegisterSpawnObjectTrackFactory(registry, "spawnObject");
		proto::fightitems::playback::RegisterManageLifetimeTrackFactory(registry, "manageLifetime");
		proto::fightitems::ai::RegisterSetVehicleStateTrackFactory(registry, "setVehicleState");
		proto::fightitems::vehicle::RegisterSetPanicStateTrackFactory(registry, "setVehiclePanicState");
		proto::fightitems::ai::RegisterFacingAngleTargetConditionFactory(registry, "facingAngleTarget");
		proto::fightitems::ai::RegisterForceMotionTrackFactory(registry, "forceMotion");
		proto::fightitems::ai::RegisterObjectSpawnedTrackFactory(registry, "objectSpawned");
		proto::fightitems::ai::RegisterReserveTargetsPositionTrackFactory(registry, "reserveTargetsPosition");
		proto::fightitems::ai::RegisterReserveGunButtTrackFactory(registry, "reserveGunButt");
		proto::fightitems::ai::RegisterReservePositionTrackFactory(registry, "reservePosition");
		proto::fightitems::ai::RegisterReserveVolumeTrackFactory(registry, "reserveVolume");
		proto::fightitems::ai::RegisterReserveHydraPositionTrackFactory(registry, "reserveHydraPosition");
		proto::fightitems::motion::RegisterSupportingLimbSetActiveRangeTrackFactory(registry, "supportingLimbSetActiveRange");
		proto::fightitems::ai::RegisterTankRamTrackFactory(registry, "tankRam");
		proto::fightitems::ai::RegisterDrawObjectDebugTrackFactory(registry, "drawObjectDebug");
		proto::fightitems::ai::RegisterPlayDebugDialogTrackFactory(registry, "playDebugDialog");
		proto::fightitems::motion::RegisterVariableIntTemporarySetTrackFactory(registry, "variableIntTemporarySet");
		proto::fightitems::ai::RegisterZiplineTakeOffTrackFactory(registry, "ziplineTakeOff");
		proto::fightitems::ai::RegisterZiplineLandTrackFactory(registry, "ziplineLand");
		proto::fightitems::ai::RegisterSetPoisonCloudParametersTrackFactory(registry, "setPoisonCloudParameters");
		proto::fightitems::ai::RegisterSetNPCLODStateTrackFactory(registry, "setNPCLODState");
		proto::fightitems::ai::RegisterGameObjectOrientTrackFactory(registry, "gameObjectOrient");
		proto::fightitems::ai::RegisterResetPhysicVelocitiesTrackFactory(registry, "resetPhysicVelocities");
		proto::fightitems::ai::RegisterLodSteerTrackFactory(registry, "lodSteer");
		proto::fightitems::ai::RegisterLodMoveTrackFactory(registry, "lodMove");
		proto::fightitems::ai::RegisterUnDowngradableTrackFactory(registry, "unDowngradable");
		proto::fightitems::ai::RegisterCharacterizeFromReservedTrackFactory(registry, "characterizeFromReserved");
		proto::fightitems::ai::RegisterCharacterizeTrackFactory(registry, "characterize");
		proto::fightitems::ai::RegisterUpdateSoldierReservationBudgetTrackFactory(registry, "updateSoldierReservationBudget");
		proto::fightitems::ai::RegisterSetIntersectionPropertiesTrackFactory(registry, "setIntersectionProperties");
		proto::fightitems::alert::RegisterCallStrikeTeamTrackFactory(registry, "callStrikeTeam");
		proto::fightitems::alert::RegisterPlayerCallStrikeTeamTrackFactory(registry, "playerCallStrikeTeam");
		proto::fightitems::ai::RegisterRequestCombatBudgetTokenTrackFactory(registry, "requestCombatBudgetToken");
		proto::fightitems::ai::RegisterStayOnRoofTrackFactory(registry, "stayOnRoof");
		engine::RegisterHealthTrackFactory(registry, "health");
		proto::RegisterFMVTrackFactory(registry, "FMV");
		proto::fightitems::ai::RegisterEmotionalStateConditionFactory(registry, "emotionalState");
		proto::fightitems::ai::RegisterTargetingFactories(registry);
		proto::fightitems::ai::RegisterDriverStateConditionFactory(registry, "driverState");
		proto::fightitems::ai::RegisterTargetHasLoFConditionFactory(registry, "targetHasLoF");
		proto::fightitems::ai::RegisterTargetHasLoFDistanceConditionFactory(registry, "targetHasLoFDistance");
		proto::fightitems::ai::RegisterAimingAtTargetConditionFactory(registry, "aimingAtTarget");
		proto::fightitems::ai::RegisterAimingAtConditionFactory(registry, "aimingAt");
		proto::fightitems::ai::RegisterVehicleStateConditionFactory(registry, "vehicleState");
		proto::fightitems::ai::RegisterThreatConditionFactory(registry, "threat");
		proto::fightitems::ai::RegisterThreatCanSeeConditionFactory(registry, "threatCanSee");
		proto::fightitems::ai::RegisterThreatCanGrabConditionFactory(registry, "threatCanBeGrabbed");
		proto::fightitems::ai::RegisterThreatInMemoryConditionFactory(registry, "threatInMemory");
		proto::fightitems::ai::RegisterLastThreatConditionGroupConditionFactory(registry, "lastThreatConditionGroup");
		proto::fightitems::ai::RegisterThreatStoreConditionFactory(registry, "threatStore");
		proto::fightitems::motion::RegisterAxisDirectionConditionFactory(registry, "axisDirection");
		proto::fightitems::motion::RegisterChargeConditionFactory(registry, "charge");
		proto::fightitems::motion::RegisterHitSurfaceFactories(registry);
		proto::fightitems::motion::RegisterConsumptionNameConditionFactory(registry, "consumptionName");
		proto::fightitems::motion::RegisterCharacterCloudStateAt10102280Factories(registry);
		proto::fightitems::motion::RegisterCrowdMinDistanceConditionFactory(registry, "crowdMinDistance");
		proto::fightitems::motion::RegisterCrowdPositionConditionFactory(registry, "crowdPosition");
		proto::fightitems::motion::RegisterDetectedObjectAngleConditionFactory(registry, "detectedObjectAngle");
		proto::fightitems::motion::RegisterDetectedObjectConditionGroupConditionFactory(registry, "detectedObjectConditionGroup");
		proto::fightitems::motion::RegisterDetectedObjectDistanceConditionFactory(registry, "detectedObjectDistance");
		proto::fightitems::motion::RegisterDetectedObjectFacingConditionFactory(registry, "detectedObjectFacing");
		proto::fightitems::motion::RegisterDetectedObjectIsSeenConditionFactory(registry, "detectedObjectIsSeen");
		proto::fightitems::motion::RegisterDetectedObjectIsTargetConditionFactory(registry, "detectedObjectIsTarget");
		proto::fightitems::motion::RegisterDevastatorAvailableConditionFactory(registry, "devastatorAvailable");
		proto::fightitems::motion::RegisterDevastatorTargetDistanceConditionFactory(registry, "devastatorTargetDistance");
		proto::fightitems::motion::RegisterDevastatorTargetConditionGroupConditionFactory(registry, "devastatorTargetConditionGroup");
		proto::fightitems::motion::RegisterGrabSlotFactories(registry);
		proto::fightitems::motion::RegisterJointLookAtConditionFactory(registry, "jointLookAtCondition");
		proto::fightitems::motion::RegisterJointOrientationConditionFactory(registry, "jointOrientation");
		proto::fightitems::motion::RegisterOutOfCombatTimerConditionFactory(registry, "outOfCombatTimer");
		proto::fightitems::motion::RegisterPushbackDirectionConditionFactory(registry, "pushbackDirection");
		proto::fightitems::motion::RegisterPushbackVelocityConditionFactory(registry, "pushbackVelocity");
		proto::fightitems::motion::RegisterReactionEventConditionGroupFactories(registry);
		proto::fightitems::motion::RegisterShootCheckAmmoCountConditionFactory(registry, "shootCheckAmmoCount");
		proto::fightitems::motion::RegisterShootCheckCooldownTimeConditionFactory(registry, "shootCheckCooldownTime");
		proto::fightitems::motion::RegisterShootCheckOverheatingConditionFactory(registry, "shootCheckOverheating");
		proto::fightitems::motion::RegisterShootCurrentWeaponConfigurationConditionFactory(registry, "shootWeaponConfiguration");
		proto::fightitems::motion::RegisterSupportingLimbTestSurfaceNormalAngleFactories(registry);
		proto::fightitems::motion::RegisterTargetAngleConditionFactory(registry, "targetAngle");
		proto::fightitems::motion::RegisterTimerCompareConditionFactory(registry, "timerCompare");
		proto::fightitems::motion::RegisterTransformationAllowedConditionFactory(registry, "transformationAllowed");
		proto::fightitems::motion::RegisterTransformationSlotActiveConditionFactory(registry, "transformationSlotActive");
		proto::fightitems::motion::RegisterTransformationSlotTransformDesiredConditionFactory(registry, "transformationSlotTransformDesired");
		proto::fightitems::motion::RegisterTransformationSlotValidConditionFactory(registry, "transformationSlotValid");
		proto::fightitems::motion::RegisterTransformationConsumeDescriptionValidConditionFactory(registry, "transformationConsumeDescriptionValid");
		proto::fightitems::motion::RegisterTransformationDesiredSensesConditionFactory(registry, "transformationDesiredSenses");
		proto::fightitems::motion::RegisterVariableIntCompareConditionFactory(registry, "variableIntCompare");
		proto::fightitems::motion::RegisterVariableNameCompareConditionFactory(registry, "variableNameCompare");
		proto::fightitems::motion::RegisterAutoTargetDistanceConditionFactory(registry, "autoTargetDistance");
		proto::fightitems::motion::RegisterTargetDistanceConditionFactory(registry, "targetDistance");
		proto::fightitems::motion::RegisterTargetDistanceWithOffsetConditionFactory(registry, "targetDistanceWithOffset");
		proto::fightitems::motion::RegisterMotionStateConditionFactory(registry, "motionState");
		proto::fightitems::motion::RegisterAccumulatedDamageFactories(registry);
		proto::fightitems::motion::RegisterIsUndamageableFactories(registry);
		proto::fightitems::motion::RegisterTargetCanJumpToConditionFactory(registry, "targetCanJumpTo");
		proto::fightitems::ai::RegisterTargetIsHumanConditionFactory(registry, "targetIsHuman");
		proto::fightitems::ai::RegisterStuckConditionFactory(registry, "stuck");
		proto::fightitems::ai::RegisterInHotZoneConditionFactory(registry, "inHotZone");
		proto::fightitems::ai::RegisterInsideReservedVolumeConditionFactory(registry, "insideReservedVolume");
		proto::fightitems::ai::RegisterGroundDistanceConditionFactory(registry, "groundDistance");
		proto::fightitems::motion::RegisterUndergroundStateFactories(registry);
		proto::fightitems::motion::RegisterOrientationDesiredConditionFactory(registry, "orientationDesired");
		proto::fightitems::motion::RegisterHasPatsyFactories(registry);
		proto::fightitems::motion::RegisterFactionFactories(registry);
		proto::fightitems::motion::RegisterStunnedFactories(registry);
		proto::fightitems::ai::RegisterNPCLODConditionFactory(registry, "npcLOD");
		proto::fightitems::ai::RegisterCanReserveSoldierBudgetConditionFactory(registry, "canReserveSoldierBudget");
		proto::fightitems::ai::RegisterIsInLoadedCellConditionFactory(registry, "isInLoadedCell");
		proto::fightitems::ai::RegisterIsDisguiseActionEnabledConditionFactory(registry, "isDisguiseActionEnabled");
		proto::fightitems::ai::RegisterAreDisguiseActionsEnabledConditionFactory(registry, "areDisguiseActionsEnabled");
		proto::fightitems::ai::RegisterAbsoluteHeightConditionFactory(registry, "absoluteHeight");
		proto::fightitems::ai::RegisterSpatialQueryConditionFactory(registry, "npcSpatialQuery");
		proto::fightitems::ai::RegisterSoldierWithinDistanceConditionFactory(registry, "soldierWithinDistance");
		proto::fightitems::ai::RegisterAnyPlayerDistanceConditionFactory(registry, "anyPlayerDistance");
		proto::fightitems::alert::RegisterValidMilitaryDisguiseConditionFactory(registry, "validMilitaryDisguise");
		proto::fightitems::alert::RegisterDisguiseBlownConditionFactory(registry, "disguiseBlown");
		proto::fightitems::alert::RegisterMilitaryDisguiseConditionFactory(registry, "militaryDisguise");
		proto::fightitems::motion::RegisterHelicopterRotorCollisionFactories(registry);
		proto::fightitems::proplogic::RegisterWaitOnCollisionTrackFactory(registry, "waitOnCollision");
		proto::fightitems::scenario::RegisterMissionConditionFactory(registry, "mission");
		proto::fightitems::motion::RegisterVelocityAngleConditionFactory(registry, "velocityAngle");
		proto::fightitems::motion::RegisterVelocityYAngleConditionFactory(registry, "velocityYAngle");
		proto::fightitems::motion::RegisterUsingHunterShortRangeConditionFactory(registry, "usingHunterShortRange");
		proto::fightitems::motion::RegisterOrientationNormalAngleConditionFactory(registry, "orientationNormalAngle");
		proto::fightitems::motion::RegisterMagneticBootsNextSurfaceNormalConditionFactory(registry, "magneticBootsNextSurfaceNormal");
		proto::fightitems::ai::RegisterTargetBeingHeldConditionFactory(registry, "targetBeingHeld");
		proto::fightitems::motion::RegisterInsideJumpInBoundaryConditionFactory(registry, "insideJumpInBoundary");
		proto::fightitems::motion::RegisterHeliBoundaryStatusConditionFactory(registry, "heliBoundaryStatus");
		proto::fightitems::motion::RegisterDistanceFromWaterSurfaceConditionFactory(registry, "DistanceFromWaterSurface");
		proto::fightitems::motion::RegisterButtonHintShowingConditionFactory(registry, "buttonHintShowing");
		proto::fightitems::motion::RegisterHunterOnWallConditionFactory(registry, "hunterOnWall");
		proto::fightitems::motion::RegisterHunterCanHopAroundCornerConditionFactory(registry, "hunterCanHopAroundCorner");
		proto::fightitems::motion::RegisterGroundSpikeTestStateFactories(registry);
		proto::fightitems::motion::RegisterGroundSpikeSpawnClusterFactories(registry);
		proto::fightitems::motion::RegisterHasMarkerConditionFactory(registry, "hasMarker");
		proto::fightitems::ai::RegisterNearRoofsEdgeConditionFactory(registry, "nearRoofsEdge");
		proto::fightitems::ai::RegisterHasCombatBudgetTokenConditionFactory(registry, "hasCombatBudgetToken");
		proto::fightitems::ai::RegisterCheckTagAvailableSpaceConditionFactory(registry, "checkTagAvailableSpace");
		proto::fightitems::ai::RegisterIsMissileTargetingPlayerConditionFactory(registry, "isMissileTargetingPlayer");
		proto::fightitems::online::RegisterOnlineTestForRespawnStateFactories(registry);
		proto::fightitems::online::RegisterOnlineFlagPlayerDeathFactories(registry);
		proto::fightitems::RegisterAt10502080Factories(registry);
		proto::fightitems::RegisterAt104FAC90Factories(registry);
		proto::fightitems::motion::RegisterPadRumbleClearFactories(registry);
		proto::RegisterIsWOITargetConditionFactory(registry, "isWOITarget");
		proto::RegisterWOIFMVTrackFactory(registry, "WOIFmv");
		proto::RegisterWOISendEventTrackFactory(registry, "WOISendEvent");
		proto::RegisterWOIPlayReactionTrackFactory(registry, "WOIPlayReaction");
		proto::RegisterWOIShowTargetNameTrackFactory(registry, "WOIShowTargetName");
		proto::fightitems::RegisterPhysicsLODAndDoorsFactories(registry);
		proto::RegisterSmartHintSetTimerTrackFactory(registry, "smartHintSetTimer");
		registry->Prepare();
		registry->Complete();
		MakeAIContext();
		ExtendPlaybackContext();
		MakeAlertContext();
		MakeVehicleContext();
		ExtendNISContext();
		MakeHitEffectContext();
		MakeMusicContext();
		FinishFightContexts();
	}
}
