#include "code/proto/messages/airequestmessages.h"
#include "code/engine/physics/ragdollmessages.h"

// A function that constructs each message with the expansion of inline functions off: the compiler keeps the out-of-line
// copy of the constructor and of the destructor the engine has too (the natives that send the messages inline them)
#pragma inline_depth(0)
namespace
{
	void EmitGetBlindPerceptionMessage(engine::GameObjectHandle handle)
	{
		proto::GetBlindPerceptionMessage message;
	}

	void EmitPlayerSeenPerceptionMessage(engine::GameObjectHandle handle)
	{
		proto::PlayerSeenPerceptionMessage message(0, 0.0f);
	}

	void EmitSetFixedTargetMessage(engine::GameObjectHandle handle)
	{
		proto::SetFixedTargetMessage message(0);
	}

	void EmitGetFixedTargetMessage(engine::GameObjectHandle handle)
	{
		proto::GetFixedTargetMessage message;
	}

	void EmitDontTargetMessage(engine::GameObjectHandle handle)
	{
		proto::DontTargetMessage message(false);
	}

	void EmitAddBoostedTargetMessage(engine::GameObjectHandle handle)
	{
		proto::AddBoostedTargetMessage message(handle, 0.0f);
	}

	void EmitClearBoostedTargetsMessage(engine::GameObjectHandle handle)
	{
		proto::ClearBoostedTargetsMessage message;
	}

	void EmitSetClassWeightsTargetMessage(engine::GameObjectHandle handle)
	{
		proto::SetClassWeightsTargetMessage message(0);
	}

	void EmitGetTemporaryTargetMessage(engine::GameObjectHandle handle)
	{
		proto::GetTemporaryTargetMessage message;
	}

	void EmitSetPlayerDamageOverrideFlagMessage(engine::GameObjectHandle handle)
	{
		proto::SetPlayerDamageOverrideFlagMessage message(false, 0.0f);
	}

	void EmitAddMemberSquadMessage(engine::GameObjectHandle handle)
	{
		proto::AddMemberSquadMessage message(0);
	}

	void EmitRemoveMemberSquadMessage(engine::GameObjectHandle handle)
	{
		proto::RemoveMemberSquadMessage message(0);
	}

	void EmitEmptySquadMessage(engine::GameObjectHandle handle)
	{
		proto::EmptySquadMessage message;
	}

	void EmitSetSquadTargetMessage(engine::GameObjectHandle handle)
	{
		proto::SetSquadTargetMessage message(0);
	}

	void EmitGetNumMembersSquadMessage(engine::GameObjectHandle handle)
	{
		proto::GetNumMembersSquadMessage message;
	}

	void EmitGetNumAliveMembersSquadMessage(engine::GameObjectHandle handle)
	{
		proto::GetNumAliveMembersSquadMessage message(false, false);
	}

	void EmitGetNumHealthyMembersSquadMessage(engine::GameObjectHandle handle)
	{
		proto::GetNumHealthyMembersSquadMessage message(false, false);
	}

	void EmitGetNthMemberSquadMessage(engine::GameObjectHandle handle)
	{
		proto::GetNthMemberSquadMessage message(0);
	}

	void EmitSetBreakDistanceSquadMsg(engine::GameObjectHandle handle)
	{
		proto::SetBreakDistanceSquadMsg message(0.0f);
	}

	void EmitSetStopDuringCombatSquadMsg(engine::GameObjectHandle handle)
	{
		proto::SetStopDuringCombatSquadMsg message(false);
	}

	void EmitSetCurveRadiusSquadMsg(engine::GameObjectHandle handle)
	{
		proto::SetCurveRadiusSquadMsg message(0.0f);
	}

	void EmitSetAttackRadiusSquadMsg(engine::GameObjectHandle handle)
	{
		proto::SetAttackRadiusSquadMsg message(0.0f);
	}

	void EmitSetTeleportFrozenSquadMsg(engine::GameObjectHandle handle)
	{
		proto::SetTeleportFrozenSquadMsg message(false);
	}

	void EmitSetBrakeSquadMsg(engine::GameObjectHandle handle)
	{
		proto::SetBrakeSquadMsg message(false);
	}

	void EmitGetStatusAndSuspicionPerceptionMsg(engine::GameObjectHandle handle)
	{
		proto::GetStatusAndSuspicionPerceptionMsg message;
	}

	void EmitSetAffectSuspicionPerceptionMessage(engine::GameObjectHandle handle)
	{
		proto::SetAffectSuspicionPerceptionMessage message(false);
	}

	void EmitSetOmniscientTimePerceptionMessage(engine::GameObjectHandle handle)
	{
		proto::SetOmniscientTimePerceptionMessage message(0, 0.0f);
	}

	void EmitSetPlayerAlertRadiusPerceptionMessage(engine::GameObjectHandle handle)
	{
		proto::SetPlayerAlertRadiusPerceptionMessage message(0.0f);
	}

	void EmitCopyDiversionsPerceptionMessage(engine::GameObjectHandle handle)
	{
		proto::CopyDiversionsPerceptionMessage message;
	}

	void EmitHackToUseCombatPerceptionMessage(engine::GameObjectHandle handle)
	{
		proto::HackToUseCombatPerceptionMessage message;
	}

	void EmitSetMovementRestrictionsMessage(engine::GameObjectHandle handle)
	{
		proto::SetMovementRestrictionsMessage message(0);
	}

	void EmitClearMovementRestrictionsMessage(engine::GameObjectHandle handle)
	{
		proto::ClearMovementRestrictionsMessage message;
	}

	void EmitClearPatrolMovementMessage(engine::GameObjectHandle handle)
	{
		proto::ClearPatrolMovementMessage message;
	}

	void EmitSetPatrolClosedMovementMessage(engine::GameObjectHandle handle)
	{
		proto::SetPatrolClosedMovementMessage message(false);
	}

	void EmitSetPatrolUseOrientationMovementMessage(engine::GameObjectHandle handle)
	{
		proto::SetPatrolUseOrientationMovementMessage message(false);
	}

	void EmitSetPatrolToleranceMovementMessage(engine::GameObjectHandle handle)
	{
		proto::SetPatrolToleranceMovementMessage message(0.0f);
	}

	void EmitSetPatrolPathMovementMessage(engine::GameObjectHandle handle)
	{
		proto::SetPatrolPathMovementMessage message(0);
	}

	void EmitSetFixedDestinationMessage(engine::GameObjectHandle handle)
	{
		proto::SetFixedDestinationMessage message(0);
	}

	void EmitSetFixedAreaDestinationMessage(engine::GameObjectHandle handle)
	{
		proto::SetFixedAreaDestinationMessage message(0);
	}

	void EmitSetFollowInformationMessage(engine::GameObjectHandle handle)
	{
		proto::SetFollowInformationMessage message(0);
	}

	void EmitClearFollowInformationMessage(engine::GameObjectHandle handle)
	{
		proto::ClearFollowInformationMessage message;
	}

	void EmitForceSprintMovementMessage(engine::GameObjectHandle handle)
	{
		proto::ForceSprintMovementMessage message(false);
	}

	void EmitPreventSprintMovementMessage(engine::GameObjectHandle handle)
	{
		proto::PreventSprintMovementMessage message(false);
	}

	void EmitUseHunterShortRangeMovementMessage(engine::GameObjectHandle handle)
	{
		proto::UseHunterShortRangeMovementMessage message(false);
	}

	void EmitEnableAIMsg(engine::GameObjectHandle handle)
	{
		proto::EnableAIMsg message(false);
	}

	void EmitSetTimeslicePeriodAIMsg(engine::GameObjectHandle handle)
	{
		proto::SetTimeslicePeriodAIMsg message(0);
	}

	void EmitSetLifeTimeOwnerAIMsg(engine::GameObjectHandle handle)
	{
		proto::SetLifeTimeOwnerAIMsg message(0);
	}

	void EmitRecalculateHeightmapAIMsg(engine::GameObjectHandle handle)
	{
		proto::RecalculateHeightmapAIMsg message;
	}

	void EmitSetGameObjectLODAIMsg(engine::GameObjectHandle handle)
	{
		proto::SetGameObjectLODAIMsg message(0, false);
	}

	void EmitKissOfDeathAIMsg(engine::GameObjectHandle handle)
	{
		proto::KissOfDeathAIMsg message(0.0f, false);
	}

	void EmitKissOfLifeAIMsg(engine::GameObjectHandle handle)
	{
		proto::KissOfLifeAIMsg message;
	}

	void EmitSetPatrolSpeedAIMsg(engine::GameObjectHandle handle)
	{
		proto::SetPatrolSpeedAIMsg message(0.0f);
	}

	void EmitGetIdleDisguiseMsg(engine::GameObjectHandle handle)
	{
		proto::GetIdleDisguiseMsg message;
	}

	void EmitGetInRedRingDisguiseMsg(engine::GameObjectHandle handle)
	{
		proto::GetInRedRingDisguiseMsg message;
	}

	void EmitSetInsideMilitaryBaseDisguiseMsg(engine::GameObjectHandle handle)
	{
		proto::SetInsideMilitaryBaseDisguiseMsg message(false);
	}

	void EmitGetInsideMilitaryBaseDisguiseMsg(engine::GameObjectHandle handle)
	{
		proto::GetInsideMilitaryBaseDisguiseMsg message;
	}

	void EmitSetInsideMilitaryPerimeterDisguiseMsg(engine::GameObjectHandle handle)
	{
		proto::SetInsideMilitaryPerimeterDisguiseMsg message(false);
	}

	void EmitGetInsideMilitaryPerimeterDisguiseMsg(engine::GameObjectHandle handle)
	{
		proto::GetInsideMilitaryPerimeterDisguiseMsg message;
	}

	void EmitAddBaseVolumeDisguiseMsg(engine::GameObjectHandle handle)
	{
		proto::AddBaseVolumeDisguiseMsg message(0, false);
	}

	void EmitRemoveBaseVolumeDisguiseMsg(engine::GameObjectHandle handle)
	{
		proto::RemoveBaseVolumeDisguiseMsg message(0, false);
	}

	void EmitDumpBaseVolumesDisguiseMsg(engine::GameObjectHandle handle)
	{
		proto::DumpBaseVolumesDisguiseMsg message;
	}

	void EmitSetMaxBlownTimeDisguiseMsg(engine::GameObjectHandle handle)
	{
		proto::SetMaxBlownTimeDisguiseMsg message(0.0f);
	}

	void EmitSetAlwaysBlownDisguiseMsg(engine::GameObjectHandle handle)
	{
		proto::SetAlwaysBlownDisguiseMsg message(false);
	}

	void EmitClearAllBlownDisguiseDisguiseMsg(engine::GameObjectHandle handle)
	{
		proto::ClearAllBlownDisguiseDisguiseMsg message;
	}

	void EmitSetSeenStatusDisguiseMsg(engine::GameObjectHandle handle)
	{
		proto::SetSeenStatusDisguiseMsg message(0.0f, 0.0f, 0.0f, 0.0f);
	}

	void EmitForceSeenStatusDisguiseMsg(engine::GameObjectHandle handle)
	{
		proto::ForceSeenStatusDisguiseMsg message(0.0f);
	}

	void EmitSetAlertCircleRadiusDisguiseMsg(engine::GameObjectHandle handle)
	{
		proto::SetAlertCircleRadiusDisguiseMsg message(0.0f);
	}

	void EmitGetAllyWithMotherForcesDisguiseMsg(engine::GameObjectHandle handle)
	{
		proto::GetAllyWithMotherForcesDisguiseMsg message;
	}

	void EmitSetAllyWithMotherForcesDisguiseMsg(engine::GameObjectHandle handle)
	{
		proto::SetAllyWithMotherForcesDisguiseMsg message(false);
	}

	void EmitSetAllyWithMilitaryDisguiseMsg(engine::GameObjectHandle handle)
	{
		proto::SetAllyWithMilitaryDisguiseMsg message(false);
	}

	void EmitSetHostileWithMilitaryDisguiseMsg(engine::GameObjectHandle handle)
	{
		proto::SetHostileWithMilitaryDisguiseMsg message(false);
	}

	void EmitHasValidMilitaryDisguiseAvailableMsg(engine::GameObjectHandle handle)
	{
		proto::HasValidMilitaryDisguiseAvailableMsg message;
	}

	void EmitSetDisableFriendlyFireDisguiseMsg(engine::GameObjectHandle handle)
	{
		proto::SetDisableFriendlyFireDisguiseMsg message(false);
	}

	void EmitSetDisguiseDebugLevelDisguiseMsg(engine::GameObjectHandle handle)
	{
		proto::SetDisguiseDebugLevelDisguiseMsg message(0);
	}

	void EmitNoAIStateChangeMessage(engine::GameObjectHandle handle)
	{
		proto::NoAIStateChangeMessage message(false);
	}

	void EmitAdjustPositionOutsideStateChangeMessage(engine::GameObjectHandle handle)
	{
		proto::AdjustPositionOutsideStateChangeMessage message(false);
	}

	void EmitSetMaxTokensMsg(engine::GameObjectHandle handle)
	{
		proto::SetMaxTokensMsg message(0, 0);
	}

	void EmitGetMaxTokensMsg(engine::GameObjectHandle handle)
	{
		proto::GetMaxTokensMsg message(0);
	}

	void EmitSetTokenWeightsMsg(engine::GameObjectHandle handle)
	{
		proto::SetTokenWeightsMsg message(0);
	}

	void EmitNPCDrawableCreateMessage(engine::GameObjectHandle handle)
	{
		proto::NPCDrawableCreateMessage message(false);
	}

	void EmitNPCDrawableDestroyMessage(engine::GameObjectHandle handle)
	{
		proto::NPCDrawableDestroyMessage message;
	}

	void EmitRegenerationMessage(engine::GameObjectHandle handle)
	{
		proto::RegenerationMessage message(0.0f, 0.0f, 0.0f);
	}

	void EmitSetNpcDamageMultiplierMessage(engine::GameObjectHandle handle)
	{
		proto::SetNpcDamageMultiplierMessage message(0.0f);
	}

	void EmitAddChildHealthMessage(engine::GameObjectHandle handle)
	{
		proto::AddChildHealthMessage message(0);
	}

	void EmitClearChildrenHealthMessage(engine::GameObjectHandle handle)
	{
		proto::ClearChildrenHealthMessage message;
	}

	void EmitSetExtraFriendlyFireFactorMessage(engine::GameObjectHandle handle)
	{
		proto::SetExtraFriendlyFireFactorMessage message(0.0f);
	}

	void EmitWorldGetAmbientZoneInfoMessage(engine::GameObjectHandle handle)
	{
		proto::WorldGetAmbientZoneInfoMessage message;
	}

	void EmitWorldKillHiveMessage(engine::GameObjectHandle handle)
	{
		proto::WorldKillHiveMessage message(0.0f, 0.0f, 0.0f, 0.0f);
	}

	void EmitGetNumValidMembersSquadMessage(engine::GameObjectHandle handle)
	{
		proto::GetNumValidMembersSquadMessage message(false, false);
	}

	void EmitIsMemberSquadMessage(engine::GameObjectHandle handle)
	{
		proto::IsMemberSquadMessage message(0);
	}

	void EmitGetMemberListSquadMessage(engine::GameObjectHandle handle)
	{
		proto::GetMemberListSquadMessage message;
	}

	void EmitIsEngagedSquadMessage(engine::GameObjectHandle handle)
	{
		proto::IsEngagedSquadMessage message;
	}

	void EmitGetLastMemberChangeStateSquadMessage(engine::GameObjectHandle handle)
	{
		proto::GetLastMemberChangeStateSquadMessage message;
	}

	void EmitDisableDueToAlertMessage(engine::GameObjectHandle handle)
	{
		proto::DisableDueToAlertMessage message(false);
	}

	void EmitReturnObjectSpawnMessage(engine::GameObjectHandle handle)
	{
		proto::ReturnObjectSpawnMessage message(0);
	}

	void EmitGetUnDowngradableMsg(engine::GameObjectHandle handle)
	{
		proto::GetUnDowngradableMsg message;
	}

	void EmitPurgeKissOfDeathAIMsg(engine::GameObjectHandle handle)
	{
		proto::PurgeKissOfDeathAIMsg message;
	}

	void EmitRagdollGetEnabledMessage(engine::GameObjectHandle handle)
	{
		engine::RagdollGetEnabledMessage message;
	}

	void EmitSetGoalAIMsg(core::Name<core::CaseSensitiveKey> name)
	{
		proto::SetGoalAIMsg message(name);
	}

	void EmitSetTooltipAIMsg(const char* text)
	{
		proto::SetTooltipAIMsg message(text, 0);
	}

	void EmitWorldSetAmbientZoneInfoMessage(const proto::AmbientZoneInfo& info)
	{
		proto::WorldSetAmbientZoneInfoMessage message(info);
	}

}
#pragma inline_depth()

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102D3C80
// FUNCTION: ENGINE 0x103607D0
// FUNCTION: ENGINE 0x10360800
// FUNCTION: ENGINE 0x10360810
// FUNCTION: ENGINE 0x10360850
// FUNCTION: ENGINE 0x10361250
// FUNCTION: ENGINE 0x10361280
// FUNCTION: ENGINE 0x10364FD0
// FUNCTION: ENGINE 0x10365000
// FUNCTION: ENGINE 0x10365010
// FUNCTION: ENGINE 0x10365050
// FUNCTION: ENGINE 0x10365060
// FUNCTION: ENGINE 0x10365090
// FUNCTION: ENGINE 0x103650A0
// FUNCTION: ENGINE 0x103650E0
// FUNCTION: ENGINE 0x103650F0
// FUNCTION: ENGINE 0x10365120
// FUNCTION: ENGINE 0x10365130
// FUNCTION: ENGINE 0x10365160
// FUNCTION: ENGINE 0x10365170
// FUNCTION: ENGINE 0x103651B0
// FUNCTION: ENGINE 0x103651C0
// FUNCTION: ENGINE 0x10365200
// FUNCTION: ENGINE 0x10365230
// FUNCTION: ENGINE 0x10365270
// FUNCTION: ENGINE 0x10365280
// FUNCTION: ENGINE 0x103652B0
// FUNCTION: ENGINE 0x103652C0
// FUNCTION: ENGINE 0x103652F0
// FUNCTION: ENGINE 0x10365300
// FUNCTION: ENGINE 0x10365330
// FUNCTION: ENGINE 0x10365340
// FUNCTION: ENGINE 0x10365370
// FUNCTION: ENGINE 0x10365380
// FUNCTION: ENGINE 0x103653C0
// FUNCTION: ENGINE 0x103653D0
// FUNCTION: ENGINE 0x10365410
// FUNCTION: ENGINE 0x10365420
// FUNCTION: ENGINE 0x10365460
// FUNCTION: ENGINE 0x10365470
// FUNCTION: ENGINE 0x103654B0
// FUNCTION: ENGINE 0x103654C0
// FUNCTION: ENGINE 0x103654F0
// FUNCTION: ENGINE 0x10365500
// FUNCTION: ENGINE 0x10365540
// FUNCTION: ENGINE 0x10365550
// FUNCTION: ENGINE 0x10365590
// FUNCTION: ENGINE 0x103655A0
// FUNCTION: ENGINE 0x103655D0
// FUNCTION: ENGINE 0x103655E0
// FUNCTION: ENGINE 0x10365610
// FUNCTION: ENGINE 0x10365620
// FUNCTION: ENGINE 0x10365650
// FUNCTION: ENGINE 0x10365660
// FUNCTION: ENGINE 0x10365690
// FUNCTION: ENGINE 0x103656A0
// FUNCTION: ENGINE 0x103656E0
// FUNCTION: ENGINE 0x103656F0
// FUNCTION: ENGINE 0x10365730
// FUNCTION: ENGINE 0x10365740
// FUNCTION: ENGINE 0x10365770
// FUNCTION: ENGINE 0x10365780
// FUNCTION: ENGINE 0x103657B0
// FUNCTION: ENGINE 0x10365860
// FUNCTION: ENGINE 0x10365890
// FUNCTION: ENGINE 0x103658A0
// FUNCTION: ENGINE 0x103658D0
// FUNCTION: ENGINE 0x10365970
// FUNCTION: ENGINE 0x103659A0
// FUNCTION: ENGINE 0x103659B0
// FUNCTION: ENGINE 0x103659E0
// FUNCTION: ENGINE 0x103659F0
// FUNCTION: ENGINE 0x10365A20
// FUNCTION: ENGINE 0x10365A30
// FUNCTION: ENGINE 0x10365A70
// FUNCTION: ENGINE 0x10365A80
// FUNCTION: ENGINE 0x10365AB0
// FUNCTION: ENGINE 0x10365AC0
// FUNCTION: ENGINE 0x10365AF0
// FUNCTION: ENGINE 0x10365B00
// FUNCTION: ENGINE 0x10365B30
// FUNCTION: ENGINE 0x10365B40
// FUNCTION: ENGINE 0x10365B70
// FUNCTION: ENGINE 0x10365B80
// FUNCTION: ENGINE 0x10365BB0
// FUNCTION: ENGINE 0x10365BC0
// FUNCTION: ENGINE 0x10365BF0
// FUNCTION: ENGINE 0x10365C00
// FUNCTION: ENGINE 0x10365C30
// FUNCTION: ENGINE 0x10365C40
// FUNCTION: ENGINE 0x10365C70
// FUNCTION: ENGINE 0x10365C80
// FUNCTION: ENGINE 0x10365CB0
// FUNCTION: ENGINE 0x10365CC0
// FUNCTION: ENGINE 0x10365CF0
// FUNCTION: ENGINE 0x10365D00
// FUNCTION: ENGINE 0x10365D60
// FUNCTION: ENGINE 0x10365D70
// FUNCTION: ENGINE 0x10365DA0
// FUNCTION: ENGINE 0x10365DB0
// FUNCTION: ENGINE 0x10365DE0
// FUNCTION: ENGINE 0x10365DF0
// FUNCTION: ENGINE 0x10365E30
// FUNCTION: ENGINE 0x10365E40
// FUNCTION: ENGINE 0x10365E80
// FUNCTION: ENGINE 0x10365E90
// FUNCTION: ENGINE 0x10365EC0
// FUNCTION: ENGINE 0x10365ED0
// FUNCTION: ENGINE 0x10365F10
// FUNCTION: ENGINE 0x10366040
// FUNCTION: ENGINE 0x10366070
// FUNCTION: ENGINE 0x10366080
// FUNCTION: ENGINE 0x103660B0
// FUNCTION: ENGINE 0x103660C0
// FUNCTION: ENGINE 0x103660F0
// FUNCTION: ENGINE 0x10366100
// FUNCTION: ENGINE 0x10366130
// FUNCTION: ENGINE 0x10366140
// FUNCTION: ENGINE 0x10366170
// FUNCTION: ENGINE 0x10366180
// FUNCTION: ENGINE 0x103661B0
// FUNCTION: ENGINE 0x103661C0
// FUNCTION: ENGINE 0x10366200
// FUNCTION: ENGINE 0x10366210
// FUNCTION: ENGINE 0x10366250
// FUNCTION: ENGINE 0x10366260
// FUNCTION: ENGINE 0x10366290
// FUNCTION: ENGINE 0x103662A0
// FUNCTION: ENGINE 0x103662E0
// FUNCTION: ENGINE 0x10366340
// FUNCTION: ENGINE 0x10366370
// FUNCTION: ENGINE 0x103663A0
// FUNCTION: ENGINE 0x103663D0
// FUNCTION: ENGINE 0x103663E0
// FUNCTION: ENGINE 0x10366440
// FUNCTION: ENGINE 0x10366450
// FUNCTION: ENGINE 0x10366490
// FUNCTION: ENGINE 0x103664A0
// FUNCTION: ENGINE 0x103664E0
// FUNCTION: ENGINE 0x103664F0
// FUNCTION: ENGINE 0x10366520
// FUNCTION: ENGINE 0x10366530
// FUNCTION: ENGINE 0x10366560
// FUNCTION: ENGINE 0x10366570
// FUNCTION: ENGINE 0x103665A0
// FUNCTION: ENGINE 0x103665B0
// FUNCTION: ENGINE 0x103665E0
// FUNCTION: ENGINE 0x103665F0
// FUNCTION: ENGINE 0x10366620
// FUNCTION: ENGINE 0x10366630
// FUNCTION: ENGINE 0x10366660
// FUNCTION: ENGINE 0x10366670
// FUNCTION: ENGINE 0x103666A0
// FUNCTION: ENGINE 0x103666B0
// FUNCTION: ENGINE 0x103666E0
// FUNCTION: ENGINE 0x103666F0
// FUNCTION: ENGINE 0x10366720
// FUNCTION: ENGINE 0x10366730
// FUNCTION: ENGINE 0x10366770
// FUNCTION: ENGINE 0x10366780
// FUNCTION: ENGINE 0x103667C0
// FUNCTION: ENGINE 0x103667D0
// FUNCTION: ENGINE 0x10366800
// FUNCTION: ENGINE 0x10366810
// FUNCTION: ENGINE 0x10366840
// FUNCTION: ENGINE 0x10366850
// FUNCTION: ENGINE 0x10366880
// FUNCTION: ENGINE 0x10366890
// FUNCTION: ENGINE 0x103668E0
// FUNCTION: ENGINE 0x103668F0
// FUNCTION: ENGINE 0x10366930
// FUNCTION: ENGINE 0x10366990
// FUNCTION: ENGINE 0x103669C0
// FUNCTION: ENGINE 0x103669D0
// FUNCTION: ENGINE 0x10366A00
// FUNCTION: ENGINE 0x10366A10
// FUNCTION: ENGINE 0x10366A50
// FUNCTION: ENGINE 0x10366A90
// FUNCTION: ENGINE 0x10366AC0
// FUNCTION: ENGINE 0x10366AD0
// FUNCTION: ENGINE 0x10366B10
// FUNCTION: ENGINE 0x10366B20
// FUNCTION: ENGINE 0x10366B80
// FUNCTION: ENGINE 0x10367D10
// FUNCTION: ENGINE 0x10367D40
// FUNCTION: ENGINE 0x10367D70
// FUNCTION: ENGINE 0x10367DA0
// FUNCTION: ENGINE 0x10367DD0
// FUNCTION: ENGINE 0x10367E00
// FUNCTION: ENGINE 0x10367E30
// FUNCTION: ENGINE 0x10367E60
// FUNCTION: ENGINE 0x10367E90
// FUNCTION: ENGINE 0x10367EC0
// FUNCTION: ENGINE 0x10367EF0
// FUNCTION: ENGINE 0x10367F20
// FUNCTION: ENGINE 0x10367F50
// FUNCTION: ENGINE 0x10367F80
// FUNCTION: ENGINE 0x10367FB0
// FUNCTION: ENGINE 0x10367FE0
// FUNCTION: ENGINE 0x10368010
// FUNCTION: ENGINE 0x10368040
// FUNCTION: ENGINE 0x10368070
// FUNCTION: ENGINE 0x103680A0
// FUNCTION: ENGINE 0x103680D0
// FUNCTION: ENGINE 0x10368100
// FUNCTION: ENGINE 0x10368130
// FUNCTION: ENGINE 0x10368160
// FUNCTION: ENGINE 0x10368190
// FUNCTION: ENGINE 0x103681C0
// FUNCTION: ENGINE 0x103681F0
// FUNCTION: ENGINE 0x10368220
// FUNCTION: ENGINE 0x10368250
// FUNCTION: ENGINE 0x10368280
// FUNCTION: ENGINE 0x103682E0
// FUNCTION: ENGINE 0x10368310
// FUNCTION: ENGINE 0x10368340
// FUNCTION: ENGINE 0x10368370
// FUNCTION: ENGINE 0x103683A0
// FUNCTION: ENGINE 0x103683D0
// FUNCTION: ENGINE 0x10368400
// FUNCTION: ENGINE 0x10368430
// FUNCTION: ENGINE 0x10368460
// FUNCTION: ENGINE 0x10368490
// FUNCTION: ENGINE 0x103684C0
// FUNCTION: ENGINE 0x103684F0
// FUNCTION: ENGINE 0x10368520
// FUNCTION: ENGINE 0x10368550
// FUNCTION: ENGINE 0x10368590
// FUNCTION: ENGINE 0x103685A0
// FUNCTION: ENGINE 0x103685D0
// FUNCTION: ENGINE 0x10368600
// FUNCTION: ENGINE 0x10368630
// FUNCTION: ENGINE 0x10368660
// FUNCTION: ENGINE 0x10368690
// FUNCTION: ENGINE 0x103686C0
// FUNCTION: ENGINE 0x103686F0
// FUNCTION: ENGINE 0x10368720
// FUNCTION: ENGINE 0x10368750
// FUNCTION: ENGINE 0x10368780
// FUNCTION: ENGINE 0x103687B0
// FUNCTION: ENGINE 0x103687E0
// FUNCTION: ENGINE 0x10368810
// FUNCTION: ENGINE 0x10368840
// FUNCTION: ENGINE 0x10368870
// FUNCTION: ENGINE 0x103688A0
// FUNCTION: ENGINE 0x103688D0
// FUNCTION: ENGINE 0x10368930
// FUNCTION: ENGINE 0x103689F0
// FUNCTION: ENGINE 0x10368A20
// FUNCTION: ENGINE 0x10368A50
// FUNCTION: ENGINE 0x10368A80
// FUNCTION: ENGINE 0x10368AB0
// FUNCTION: ENGINE 0x10368AE0
// FUNCTION: ENGINE 0x10368B10
// FUNCTION: ENGINE 0x10368B40
// FUNCTION: ENGINE 0x10368B70
// FUNCTION: ENGINE 0x10368BA0
// FUNCTION: ENGINE 0x10368BD0
// FUNCTION: ENGINE 0x10368C00
// FUNCTION: ENGINE 0x10368C30
// FUNCTION: ENGINE 0x10368C60
// FUNCTION: ENGINE 0x10368C90
// FUNCTION: ENGINE 0x10368CC0
// FUNCTION: ENGINE 0x10368CF0
// FUNCTION: ENGINE 0x10368D20
// FUNCTION: ENGINE 0x10368D50
// FUNCTION: ENGINE 0x10368D80
// FUNCTION: ENGINE 0x10368DE0
// FUNCTION: ENGINE 0x10368E10
// FUNCTION: ENGINE 0x10368E40
// FUNCTION: ENGINE 0x10368E70
// FUNCTION: ENGINE 0x10368EA0
// FUNCTION: ENGINE 0x10368ED0
// FUNCTION: ENGINE 0x1036C3B0
// FUNCTION: ENGINE 0x1037B3C0
// FUNCTION: ENGINE 0x1037B400
// FUNCTION: ENGINE 0x1037B410
// FUNCTION: ENGINE 0x1037B450
// FUNCTION: ENGINE 0x1037B460
// FUNCTION: ENGINE 0x1037B490
// FUNCTION: ENGINE 0x1037B4A0
// FUNCTION: ENGINE 0x1037B4E0
// FUNCTION: ENGINE 0x1037B4F0
// FUNCTION: ENGINE 0x1037B520
// FUNCTION: ENGINE 0x1037B750
// FUNCTION: ENGINE 0x1037B780
// FUNCTION: ENGINE 0x1037C1C0
// FUNCTION: ENGINE 0x1037C1F0
// FUNCTION: ENGINE 0x1037C220
// FUNCTION: ENGINE 0x1037C250
// FUNCTION: ENGINE 0x1037C280
// FUNCTION: ENGINE 0x1037C400
// FUNCTION: ENGINE 0x103859E0
// FUNCTION: ENGINE 0x10385A10
// FUNCTION: ENGINE 0x10385A20
// FUNCTION: ENGINE 0x10385A50
// FUNCTION: ENGINE 0x10385A60
// FUNCTION: ENGINE 0x10385A90
// FUNCTION: ENGINE 0x10385AA0
// FUNCTION: ENGINE 0x10385AD0
// FUNCTION: ENGINE 0x10386340
// FUNCTION: ENGINE 0x10386370
// FUNCTION: ENGINE 0x103863A0
// FUNCTION: ENGINE 0x103863D0
