// The messages the ai scripts and the ai fight items send to characters and squads (names from the RTTI; type, id, member
// layout and constructor arguments from the engine's constructors, member names are guesses): target, squad, perception,
// movement, ai, level of detail, disguise, state change, spawn, token, world and render requests. The constructors are
// inline (expanded in every user); the engine keeps one out-of-line copy of each in the unit 0x10360770 - 0x1037B800, which
// airequestmessages.cpp emits. The categories without a header of their own are declared here.
#ifndef PROTO_MESSAGES_AIREQUESTMESSAGES_H
#define PROTO_MESSAGES_AIREQUESTMESSAGES_H

#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/core/name.h"
#include "code/core/strings.h"
#include "code/engine/message.h"
#include "code/proto/fightitems/ai/aimessages.h"

namespace choreo
{
	extern const float gMinusOne;
}

namespace engine
{
	namespace driving
	{
		extern const float gOne;
	}
}

namespace proto
{
	// RTTI: proto::PerceptionMessage (message type 0x25)
	struct PerceptionMessage : public engine::IntrusiveMessage
	{
		explicit PerceptionMessage(short newId) : engine::IntrusiveMessage(0x25, newId)
		{
		}
		virtual ~PerceptionMessage()
		{
		}
	};

	// RTTI: proto::TokenMessage (message type 0x2E)
	struct TokenMessage : public engine::IntrusiveMessage
	{
		explicit TokenMessage(short newId) : engine::IntrusiveMessage(0x2e, newId)
		{
		}
		virtual ~TokenMessage()
		{
		}
	};

	// RTTI: proto::WorldMsg (message type 0x34)
	struct WorldMsg : public engine::IntrusiveMessage
	{
		explicit WorldMsg(short newId) : engine::IntrusiveMessage(0x34, newId)
		{
		}
		virtual ~WorldMsg()
		{
		}
	};

	// RTTI: proto::ProtoRenderMsg (message type 0x3D)
	struct ProtoRenderMsg : public engine::IntrusiveMessage
	{
		explicit ProtoRenderMsg(short newId) : engine::IntrusiveMessage(0x3d, newId)
		{
		}
		virtual ~ProtoRenderMsg()
		{
		}
	};

	// RTTI: proto::GetBlindPerceptionMessage
	struct GetBlindPerceptionMessage : public PerceptionMessage
	{
		GetBlindPerceptionMessage() : PerceptionMessage(4), unknownC(true)
		{
		}
		virtual ~GetBlindPerceptionMessage()
		{
		}

		bool unknownC;  // +0xC
	};

	// RTTI: proto::PlayerSeenPerceptionMessage
	struct PlayerSeenPerceptionMessage : public PerceptionMessage
	{
		PlayerSeenPerceptionMessage(int arg2, float arg3) : PerceptionMessage(6), unknownC(arg2), unknown10(arg3), unknown14(false)
		{
		}
		virtual ~PlayerSeenPerceptionMessage()
		{
		}

		int unknownC;  // +0xC
		float unknown10;  // +0x10
		bool unknown14;  // +0x14
	};

	// RTTI: proto::SetFixedTargetMessage
	struct SetFixedTargetMessage : public TargetMessage
	{
		explicit SetFixedTargetMessage(int arg2) : TargetMessage(11), unknownC(arg2)
		{
		}
		virtual ~SetFixedTargetMessage()
		{
		}

		int unknownC;  // +0xC
	};

	// RTTI: proto::GetFixedTargetMessage
	struct GetFixedTargetMessage : public TargetMessage
	{
		GetFixedTargetMessage() : TargetMessage(11), unknownC()
		{
		}
		virtual ~GetFixedTargetMessage()
		{
		}

		engine::GameObjectHandle unknownC;  // +0xC
	};

	// RTTI: proto::DontTargetMessage
	struct DontTargetMessage : public TargetMessage
	{
		explicit DontTargetMessage(bool arg2) : TargetMessage(12), unknownC(arg2)
		{
		}
		virtual ~DontTargetMessage()
		{
		}

		bool unknownC;  // +0xC
	};

	// RTTI: proto::AddBoostedTargetMessage
	struct AddBoostedTargetMessage : public TargetMessage
	{
		AddBoostedTargetMessage(const engine::GameObjectHandle& arg2, float arg3) : TargetMessage(15), unknownC(arg2), unknown10(arg3)
		{
		}
		virtual ~AddBoostedTargetMessage()
		{
		}

		engine::GameObjectHandle unknownC;  // +0xC
		float unknown10;  // +0x10
	};

	// RTTI: proto::ClearBoostedTargetsMessage
	struct ClearBoostedTargetsMessage : public TargetMessage
	{
		ClearBoostedTargetsMessage() : TargetMessage(16)
		{
		}
		virtual ~ClearBoostedTargetsMessage()
		{
		}
	};

	// RTTI: proto::SetClassWeightsTargetMessage
	struct SetClassWeightsTargetMessage : public TargetMessage
	{
		explicit SetClassWeightsTargetMessage(int arg2) : TargetMessage(18), unknownC(arg2)
		{
		}
		virtual ~SetClassWeightsTargetMessage()
		{
		}

		int unknownC;  // +0xC
	};

	// RTTI: proto::GetTemporaryTargetMessage
	struct GetTemporaryTargetMessage : public TargetMessage
	{
		GetTemporaryTargetMessage() : TargetMessage(20), unknownC()
		{
		}
		virtual ~GetTemporaryTargetMessage()
		{
		}

		engine::GameObjectHandle unknownC;  // +0xC
	};

	// RTTI: proto::SetPlayerDamageOverrideFlagMessage
	struct SetPlayerDamageOverrideFlagMessage : public TargetMessage
	{
		SetPlayerDamageOverrideFlagMessage(bool arg2, float arg3) : TargetMessage(22), unknownC(arg2), unknown10(arg3)
		{
		}
		virtual ~SetPlayerDamageOverrideFlagMessage()
		{
		}

		bool unknownC;  // +0xC
		bool unknownD;  // +0xD
		bool unknownE;  // +0xE
		bool unknownF;  // +0xF
		float unknown10;  // +0x10
	};

	// RTTI: proto::AddMemberSquadMessage
	struct AddMemberSquadMessage : public SquadMessage
	{
		explicit AddMemberSquadMessage(int arg2) : SquadMessage(4), unknownC(arg2), unknown10(false)
		{
		}
		virtual ~AddMemberSquadMessage()
		{
		}

		int unknownC;  // +0xC
		bool unknown10;  // +0x10
	};

	// RTTI: proto::RemoveMemberSquadMessage
	struct RemoveMemberSquadMessage : public SquadMessage
	{
		explicit RemoveMemberSquadMessage(int arg2) : SquadMessage(5), unknownC(arg2)
		{
		}
		virtual ~RemoveMemberSquadMessage()
		{
		}

		int unknownC;  // +0xC
	};

	// RTTI: proto::EmptySquadMessage
	struct EmptySquadMessage : public SquadMessage
	{
		EmptySquadMessage() : SquadMessage(6)
		{
		}
		virtual ~EmptySquadMessage()
		{
		}
	};

	// RTTI: proto::SetSquadTargetMessage
	struct SetSquadTargetMessage : public SquadMessage
	{
		explicit SetSquadTargetMessage(int arg2) : SquadMessage(16), unknownC(arg2)
		{
		}
		virtual ~SetSquadTargetMessage()
		{
		}

		int unknownC;  // +0xC
	};

	// RTTI: proto::GetNumMembersSquadMessage
	struct GetNumMembersSquadMessage : public SquadMessage
	{
		GetNumMembersSquadMessage() : SquadMessage(8), unknownC(0)
		{
		}
		virtual ~GetNumMembersSquadMessage()
		{
		}

		int unknownC;  // +0xC
	};

	// RTTI: proto::GetNumAliveMembersSquadMessage
	struct GetNumAliveMembersSquadMessage : public SquadMessage
	{
		GetNumAliveMembersSquadMessage(bool arg2, bool arg3) : SquadMessage(9), unknownC(0), unknown10(arg2), unknown11(arg3)
		{
		}
		virtual ~GetNumAliveMembersSquadMessage()
		{
		}

		int unknownC;  // +0xC
		bool unknown10;  // +0x10
		bool unknown11;  // +0x11
	};

	// RTTI: proto::GetNumHealthyMembersSquadMessage
	struct GetNumHealthyMembersSquadMessage : public SquadMessage
	{
		GetNumHealthyMembersSquadMessage(bool arg2, bool arg3) : SquadMessage(10), unknownC(0), unknown10(arg2), unknown11(arg3)
		{
		}
		virtual ~GetNumHealthyMembersSquadMessage()
		{
		}

		int unknownC;  // +0xC
		bool unknown10;  // +0x10
		bool unknown11;  // +0x11
	};

	// RTTI: proto::GetNthMemberSquadMessage
	struct GetNthMemberSquadMessage : public SquadMessage
	{
		explicit GetNthMemberSquadMessage(int arg2) : SquadMessage(11), unknownC(arg2), unknown10()
		{
		}
		virtual ~GetNthMemberSquadMessage()
		{
		}

		int unknownC;  // +0xC
		engine::GameObjectHandle unknown10;  // +0x10
	};

	// RTTI: proto::SetBreakDistanceSquadMsg
	struct SetBreakDistanceSquadMsg : public SquadMessage
	{
		explicit SetBreakDistanceSquadMsg(float arg2) : SquadMessage(21), unknownC(arg2)
		{
		}
		virtual ~SetBreakDistanceSquadMsg()
		{
		}

		float unknownC;  // +0xC
	};

	// RTTI: proto::SetStopDuringCombatSquadMsg
	struct SetStopDuringCombatSquadMsg : public SquadMessage
	{
		explicit SetStopDuringCombatSquadMsg(bool arg2) : SquadMessage(22), unknownC(arg2)
		{
		}
		virtual ~SetStopDuringCombatSquadMsg()
		{
		}

		bool unknownC;  // +0xC
	};

	// RTTI: proto::SetCurveRadiusSquadMsg
	struct SetCurveRadiusSquadMsg : public SquadMessage
	{
		explicit SetCurveRadiusSquadMsg(float arg2) : SquadMessage(23), unknownC(arg2)
		{
		}
		virtual ~SetCurveRadiusSquadMsg()
		{
		}

		float unknownC;  // +0xC
	};

	// RTTI: proto::SetAttackRadiusSquadMsg
	struct SetAttackRadiusSquadMsg : public SquadMessage
	{
		explicit SetAttackRadiusSquadMsg(float arg2) : SquadMessage(24), unknownC(arg2)
		{
		}
		virtual ~SetAttackRadiusSquadMsg()
		{
		}

		float unknownC;  // +0xC
	};

	// RTTI: proto::SetTeleportFrozenSquadMsg
	struct SetTeleportFrozenSquadMsg : public SquadMessage
	{
		explicit SetTeleportFrozenSquadMsg(bool arg2) : SquadMessage(25), unknownC(arg2)
		{
		}
		virtual ~SetTeleportFrozenSquadMsg()
		{
		}

		bool unknownC;  // +0xC
	};

	// RTTI: proto::SetBrakeSquadMsg
	struct SetBrakeSquadMsg : public SquadMessage
	{
		explicit SetBrakeSquadMsg(bool arg2) : SquadMessage(26), unknownC(arg2)
		{
		}
		virtual ~SetBrakeSquadMsg()
		{
		}

		bool unknownC;  // +0xC
	};

	// RTTI: proto::GetStatusAndSuspicionPerceptionMsg
	struct GetStatusAndSuspicionPerceptionMsg : public PerceptionMessage
	{
		GetStatusAndSuspicionPerceptionMsg() : PerceptionMessage(10), unknownC(0), unknown10(false), unknown11(false)
		{
		}
		virtual ~GetStatusAndSuspicionPerceptionMsg()
		{
		}

		int unknownC;  // +0xC
		bool unknown10;  // +0x10
		bool unknown11;  // +0x11
	};

	// RTTI: proto::SetAffectSuspicionPerceptionMessage
	struct SetAffectSuspicionPerceptionMessage : public PerceptionMessage
	{
		explicit SetAffectSuspicionPerceptionMessage(bool arg2) : PerceptionMessage(5), unknownC(arg2)
		{
		}
		virtual ~SetAffectSuspicionPerceptionMessage()
		{
		}

		bool unknownC;  // +0xC
	};

	// RTTI: proto::SetOmniscientTimePerceptionMessage
	struct SetOmniscientTimePerceptionMessage : public PerceptionMessage
	{
		SetOmniscientTimePerceptionMessage(int arg2, float arg3) : PerceptionMessage(7), unknownC(arg2), unknown10(arg3)
		{
		}
		virtual ~SetOmniscientTimePerceptionMessage()
		{
		}

		int unknownC;  // +0xC
		float unknown10;  // +0x10
	};

	// RTTI: proto::SetPlayerAlertRadiusPerceptionMessage
	struct SetPlayerAlertRadiusPerceptionMessage : public PerceptionMessage
	{
		explicit SetPlayerAlertRadiusPerceptionMessage(float arg2) : PerceptionMessage(8), unknownC(arg2)
		{
		}
		virtual ~SetPlayerAlertRadiusPerceptionMessage()
		{
		}

		float unknownC;  // +0xC
	};

	// RTTI: proto::CopyDiversionsPerceptionMessage
	struct CopyDiversionsPerceptionMessage : public PerceptionMessage
	{
		CopyDiversionsPerceptionMessage() : PerceptionMessage(11)
		{
		}
		virtual ~CopyDiversionsPerceptionMessage()
		{
		}
	};

	// RTTI: proto::HackToUseCombatPerceptionMessage
	struct HackToUseCombatPerceptionMessage : public PerceptionMessage
	{
		HackToUseCombatPerceptionMessage() : PerceptionMessage(13)
		{
		}
		virtual ~HackToUseCombatPerceptionMessage()
		{
		}
	};

	// RTTI: proto::SetMovementRestrictionsMessage
	struct SetMovementRestrictionsMessage : public MovementMessage
	{
		explicit SetMovementRestrictionsMessage(int arg2) : MovementMessage(8), unknownC(arg2)
		{
		}
		virtual ~SetMovementRestrictionsMessage()
		{
		}

		int unknownC;  // +0xC
	};

	// RTTI: proto::ClearMovementRestrictionsMessage
	struct ClearMovementRestrictionsMessage : public MovementMessage
	{
		ClearMovementRestrictionsMessage() : MovementMessage(9)
		{
		}
		virtual ~ClearMovementRestrictionsMessage()
		{
		}
	};

	// RTTI: proto::AddPatrolPointMovementMessage
	struct AddPatrolPointMovementMessage : public MovementMessage
	{
		AddPatrolPointMovementMessage(float arg2, float arg3, float arg4, float arg5, float arg6, float arg7, int arg8) : MovementMessage(11), unknownC(arg2), unknown10(arg3), unknown14(arg4), unknown18(arg5), unknown1C(arg6), unknown20(arg7), unknown24(arg8)
		{
		}
		virtual ~AddPatrolPointMovementMessage()
		{
		}

		float unknownC;  // +0xC
		float unknown10;  // +0x10
		float unknown14;  // +0x14
		float unknown18;  // +0x18
		float unknown1C;  // +0x1C
		float unknown20;  // +0x20
		int unknown24;  // +0x24
	};

	// RTTI: proto::ClearPatrolMovementMessage
	struct ClearPatrolMovementMessage : public MovementMessage
	{
		ClearPatrolMovementMessage() : MovementMessage(12)
		{
		}
		virtual ~ClearPatrolMovementMessage()
		{
		}
	};

	// RTTI: proto::SetPatrolClosedMovementMessage
	struct SetPatrolClosedMovementMessage : public MovementMessage
	{
		explicit SetPatrolClosedMovementMessage(bool arg2) : MovementMessage(13), unknownC(arg2)
		{
		}
		virtual ~SetPatrolClosedMovementMessage()
		{
		}

		bool unknownC;  // +0xC
	};

	// RTTI: proto::SetPatrolUseOrientationMovementMessage
	struct SetPatrolUseOrientationMovementMessage : public MovementMessage
	{
		explicit SetPatrolUseOrientationMovementMessage(bool arg2) : MovementMessage(14), unknownC(arg2)
		{
		}
		virtual ~SetPatrolUseOrientationMovementMessage()
		{
		}

		bool unknownC;  // +0xC
	};

	// RTTI: proto::SetPatrolToleranceMovementMessage
	struct SetPatrolToleranceMovementMessage : public MovementMessage
	{
		explicit SetPatrolToleranceMovementMessage(float arg2) : MovementMessage(15), unknownC(arg2)
		{
		}
		virtual ~SetPatrolToleranceMovementMessage()
		{
		}

		float unknownC;  // +0xC
	};

	// RTTI: proto::SetPatrolPathMovementMessage
	struct SetPatrolPathMovementMessage : public MovementMessage
	{
		explicit SetPatrolPathMovementMessage(int arg2) : MovementMessage(21), unknownC(arg2)
		{
		}
		virtual ~SetPatrolPathMovementMessage()
		{
		}

		int unknownC;  // +0xC
	};

	// RTTI: proto::SetFixedDestinationMessage
	struct SetFixedDestinationMessage : public MovementMessage
	{
		explicit SetFixedDestinationMessage(int arg2) : MovementMessage(23), unknownC(arg2)
		{
		}
		virtual ~SetFixedDestinationMessage()
		{
		}

		int unknownC;  // +0xC
	};

	// RTTI: proto::SetFixedAreaDestinationMessage
	struct SetFixedAreaDestinationMessage : public MovementMessage
	{
		explicit SetFixedAreaDestinationMessage(int arg2) : MovementMessage(26), unknownC(arg2)
		{
		}
		virtual ~SetFixedAreaDestinationMessage()
		{
		}

		int unknownC;  // +0xC
	};

	// RTTI: proto::SetFollowInformationMessage
	struct SetFollowInformationMessage : public MovementMessage
	{
		explicit SetFollowInformationMessage(int arg2) : MovementMessage(56), unknownC(arg2)
		{
		}
		virtual ~SetFollowInformationMessage()
		{
		}

		int unknownC;  // +0xC
	};

	// RTTI: proto::ClearFollowInformationMessage
	struct ClearFollowInformationMessage : public MovementMessage
	{
		ClearFollowInformationMessage() : MovementMessage(57)
		{
		}
		virtual ~ClearFollowInformationMessage()
		{
		}
	};

	// RTTI: proto::ForceSprintMovementMessage
	struct ForceSprintMovementMessage : public MovementMessage
	{
		explicit ForceSprintMovementMessage(bool arg2) : MovementMessage(43), unknownC(arg2)
		{
		}
		virtual ~ForceSprintMovementMessage()
		{
		}

		bool unknownC;  // +0xC
	};

	// RTTI: proto::PreventSprintMovementMessage
	struct PreventSprintMovementMessage : public MovementMessage
	{
		explicit PreventSprintMovementMessage(bool arg2) : MovementMessage(44), unknownC(arg2)
		{
		}
		virtual ~PreventSprintMovementMessage()
		{
		}

		bool unknownC;  // +0xC
	};

	// RTTI: proto::UseHunterShortRangeMovementMessage
	struct UseHunterShortRangeMovementMessage : public MovementMessage
	{
		explicit UseHunterShortRangeMovementMessage(bool arg2) : MovementMessage(80), unknownC(arg2)
		{
		}
		virtual ~UseHunterShortRangeMovementMessage()
		{
		}

		bool unknownC;  // +0xC
	};

	// RTTI: proto::EnableAIMsg
	struct EnableAIMsg : public AIMessage
	{
		explicit EnableAIMsg(bool arg2) : AIMessage(1), unknownC(arg2)
		{
		}
		virtual ~EnableAIMsg()
		{
		}

		bool unknownC;  // +0xC
	};

	// RTTI: proto::SetTimeslicePeriodAIMsg
	struct SetTimeslicePeriodAIMsg : public AIMessage
	{
		explicit SetTimeslicePeriodAIMsg(int arg2) : AIMessage(10), unknownC(arg2)
		{
		}
		virtual ~SetTimeslicePeriodAIMsg()
		{
		}

		int unknownC;  // +0xC
	};

	// RTTI: proto::SetLifeTimeOwnerAIMsg
	struct SetLifeTimeOwnerAIMsg : public AIMessage
	{
		explicit SetLifeTimeOwnerAIMsg(int arg2) : AIMessage(13), unknownC(arg2)
		{
		}
		virtual ~SetLifeTimeOwnerAIMsg()
		{
		}

		int unknownC;  // +0xC
	};

	// RTTI: proto::RecalculateHeightmapAIMsg
	struct RecalculateHeightmapAIMsg : public AIMessage
	{
		RecalculateHeightmapAIMsg() : AIMessage(16)
		{
		}
		virtual ~RecalculateHeightmapAIMsg()
		{
		}
	};

	// RTTI: proto::SetGameObjectLODAIMsg
	struct SetGameObjectLODAIMsg : public LODAIMessage
	{
		SetGameObjectLODAIMsg(int arg2, bool arg3) : LODAIMessage(4), unknownC(arg2), unknown10(arg3)
		{
		}
		virtual ~SetGameObjectLODAIMsg()
		{
		}

		int unknownC;  // +0xC
		bool unknown10;  // +0x10
	};

	// RTTI: proto::KissOfDeathAIMsg
	struct KissOfDeathAIMsg : public LODAIMessage
	{
		KissOfDeathAIMsg(float arg2, bool arg3) : LODAIMessage(9), unknownC(arg2), unknown10(arg3)
		{
		}
		virtual ~KissOfDeathAIMsg()
		{
		}

		float unknownC;  // +0xC
		bool unknown10;  // +0x10
	};

	// RTTI: proto::KissOfLifeAIMsg
	struct KissOfLifeAIMsg : public LODAIMessage
	{
		KissOfLifeAIMsg() : LODAIMessage(11)
		{
		}
		virtual ~KissOfLifeAIMsg()
		{
		}
	};

	// RTTI: proto::SetPatrolSpeedAIMsg
	struct SetPatrolSpeedAIMsg : public LODAIMessage
	{
		explicit SetPatrolSpeedAIMsg(float arg2) : LODAIMessage(17), unknownC(arg2)
		{
		}
		virtual ~SetPatrolSpeedAIMsg()
		{
		}

		float unknownC;  // +0xC
	};

	// RTTI: proto::GetIdleDisguiseMsg
	struct GetIdleDisguiseMsg : public DisguiseMessage
	{
		GetIdleDisguiseMsg() : DisguiseMessage(14), unknownC(false)
		{
		}
		virtual ~GetIdleDisguiseMsg()
		{
		}

		bool unknownC;  // +0xC
	};

	// RTTI: proto::GetInRedRingDisguiseMsg
	struct GetInRedRingDisguiseMsg : public DisguiseMessage
	{
		GetInRedRingDisguiseMsg() : DisguiseMessage(15), unknownC(false)
		{
		}
		virtual ~GetInRedRingDisguiseMsg()
		{
		}

		bool unknownC;  // +0xC
	};

	// RTTI: proto::SetInsideMilitaryBaseDisguiseMsg
	struct SetInsideMilitaryBaseDisguiseMsg : public DisguiseMessage
	{
		explicit SetInsideMilitaryBaseDisguiseMsg(bool arg2) : DisguiseMessage(5), unknownC(arg2)
		{
		}
		virtual ~SetInsideMilitaryBaseDisguiseMsg()
		{
		}

		bool unknownC;  // +0xC
	};

	// RTTI: proto::GetInsideMilitaryBaseDisguiseMsg
	struct GetInsideMilitaryBaseDisguiseMsg : public DisguiseMessage
	{
		GetInsideMilitaryBaseDisguiseMsg() : DisguiseMessage(6), unknownC(0)
		{
		}
		virtual ~GetInsideMilitaryBaseDisguiseMsg()
		{
		}

		int unknownC;  // +0xC
	};

	// RTTI: proto::SetInsideMilitaryPerimeterDisguiseMsg
	struct SetInsideMilitaryPerimeterDisguiseMsg : public DisguiseMessage
	{
		explicit SetInsideMilitaryPerimeterDisguiseMsg(bool arg2) : DisguiseMessage(7), unknownC(arg2)
		{
		}
		virtual ~SetInsideMilitaryPerimeterDisguiseMsg()
		{
		}

		bool unknownC;  // +0xC
	};

	// RTTI: proto::GetInsideMilitaryPerimeterDisguiseMsg
	struct GetInsideMilitaryPerimeterDisguiseMsg : public DisguiseMessage
	{
		GetInsideMilitaryPerimeterDisguiseMsg() : DisguiseMessage(8), unknownC(0)
		{
		}
		virtual ~GetInsideMilitaryPerimeterDisguiseMsg()
		{
		}

		int unknownC;  // +0xC
	};

	// RTTI: proto::AddBaseVolumeDisguiseMsg
	struct AddBaseVolumeDisguiseMsg : public DisguiseMessage
	{
		AddBaseVolumeDisguiseMsg(int arg2, bool arg3) : DisguiseMessage(9), unknownC(arg2), unknown10(arg3)
		{
		}
		virtual ~AddBaseVolumeDisguiseMsg()
		{
		}

		int unknownC;  // +0xC
		bool unknown10;  // +0x10
	};

	// RTTI: proto::RemoveBaseVolumeDisguiseMsg
	struct RemoveBaseVolumeDisguiseMsg : public DisguiseMessage
	{
		RemoveBaseVolumeDisguiseMsg(int arg2, bool arg3) : DisguiseMessage(10), unknownC(arg2), unknown10(arg3)
		{
		}
		virtual ~RemoveBaseVolumeDisguiseMsg()
		{
		}

		int unknownC;  // +0xC
		bool unknown10;  // +0x10
	};

	// RTTI: proto::DumpBaseVolumesDisguiseMsg
	struct DumpBaseVolumesDisguiseMsg : public DisguiseMessage
	{
		DumpBaseVolumesDisguiseMsg() : DisguiseMessage(12)
		{
		}
		virtual ~DumpBaseVolumesDisguiseMsg()
		{
		}
	};

	// RTTI: proto::SetMaxBlownTimeDisguiseMsg
	struct SetMaxBlownTimeDisguiseMsg : public DisguiseMessage
	{
		explicit SetMaxBlownTimeDisguiseMsg(float arg2) : DisguiseMessage(22), unknownC(arg2)
		{
		}
		virtual ~SetMaxBlownTimeDisguiseMsg()
		{
		}

		float unknownC;  // +0xC
	};

	// RTTI: proto::SetAlwaysBlownDisguiseMsg
	struct SetAlwaysBlownDisguiseMsg : public DisguiseMessage
	{
		explicit SetAlwaysBlownDisguiseMsg(bool arg2) : DisguiseMessage(24), unknownC(arg2)
		{
		}
		virtual ~SetAlwaysBlownDisguiseMsg()
		{
		}

		bool unknownC;  // +0xC
	};

	// RTTI: proto::ClearAllBlownDisguiseDisguiseMsg
	struct ClearAllBlownDisguiseDisguiseMsg : public DisguiseMessage
	{
		ClearAllBlownDisguiseDisguiseMsg() : DisguiseMessage(28)
		{
		}
		virtual ~ClearAllBlownDisguiseDisguiseMsg()
		{
		}
	};

	// RTTI: proto::SetSeenStatusDisguiseMsg
	struct SetSeenStatusDisguiseMsg : public DisguiseMessage
	{
		SetSeenStatusDisguiseMsg(float arg2, float arg3, float arg4, float arg5) : DisguiseMessage(32), unknownC(arg2), unknown10(arg3), unknown14(arg4), unknown18(arg5)
		{
		}
		virtual ~SetSeenStatusDisguiseMsg()
		{
		}

		float unknownC;  // +0xC
		float unknown10;  // +0x10
		float unknown14;  // +0x14
		float unknown18;  // +0x18
	};

	// RTTI: proto::ForceSeenStatusDisguiseMsg
	struct ForceSeenStatusDisguiseMsg : public DisguiseMessage
	{
		explicit ForceSeenStatusDisguiseMsg(float arg2) : DisguiseMessage(35), unknownC(arg2)
		{
		}
		virtual ~ForceSeenStatusDisguiseMsg()
		{
		}

		float unknownC;  // +0xC
	};

	// RTTI: proto::SetAlertCircleRadiusDisguiseMsg
	struct SetAlertCircleRadiusDisguiseMsg : public DisguiseMessage
	{
		explicit SetAlertCircleRadiusDisguiseMsg(float arg2) : DisguiseMessage(51), unknownC(arg2)
		{
		}
		virtual ~SetAlertCircleRadiusDisguiseMsg()
		{
		}

		float unknownC;  // +0xC
	};

	// RTTI: proto::GetAllyWithMotherForcesDisguiseMsg
	struct GetAllyWithMotherForcesDisguiseMsg : public DisguiseMessage
	{
		GetAllyWithMotherForcesDisguiseMsg() : DisguiseMessage(52), unknownC(false)
		{
		}
		virtual ~GetAllyWithMotherForcesDisguiseMsg()
		{
		}

		bool unknownC;  // +0xC
	};

	// RTTI: proto::SetAllyWithMotherForcesDisguiseMsg
	struct SetAllyWithMotherForcesDisguiseMsg : public DisguiseMessage
	{
		explicit SetAllyWithMotherForcesDisguiseMsg(bool arg2) : DisguiseMessage(53), unknownC(arg2)
		{
		}
		virtual ~SetAllyWithMotherForcesDisguiseMsg()
		{
		}

		bool unknownC;  // +0xC
	};

	// RTTI: proto::SetAllyWithMilitaryDisguiseMsg
	struct SetAllyWithMilitaryDisguiseMsg : public DisguiseMessage
	{
		explicit SetAllyWithMilitaryDisguiseMsg(bool arg2) : DisguiseMessage(55), unknownC(arg2)
		{
		}
		virtual ~SetAllyWithMilitaryDisguiseMsg()
		{
		}

		bool unknownC;  // +0xC
	};

	// RTTI: proto::SetHostileWithMilitaryDisguiseMsg
	struct SetHostileWithMilitaryDisguiseMsg : public DisguiseMessage
	{
		explicit SetHostileWithMilitaryDisguiseMsg(bool arg2) : DisguiseMessage(57), unknownC(arg2)
		{
		}
		virtual ~SetHostileWithMilitaryDisguiseMsg()
		{
		}

		bool unknownC;  // +0xC
	};

	// RTTI: proto::HasValidMilitaryDisguiseAvailableMsg
	struct HasValidMilitaryDisguiseAvailableMsg : public DisguiseMessage
	{
		HasValidMilitaryDisguiseAvailableMsg() : DisguiseMessage(58), unknownC(false)
		{
		}
		virtual ~HasValidMilitaryDisguiseAvailableMsg()
		{
		}

		bool unknownC;  // +0xC
	};

	// RTTI: proto::SetDisableFriendlyFireDisguiseMsg
	struct SetDisableFriendlyFireDisguiseMsg : public DisguiseMessage
	{
		explicit SetDisableFriendlyFireDisguiseMsg(bool arg2) : DisguiseMessage(59), unknownC(arg2)
		{
		}
		virtual ~SetDisableFriendlyFireDisguiseMsg()
		{
		}

		bool unknownC;  // +0xC
	};

	// RTTI: proto::SetDisguiseDebugLevelDisguiseMsg
	struct SetDisguiseDebugLevelDisguiseMsg : public DisguiseMessage
	{
		explicit SetDisguiseDebugLevelDisguiseMsg(int arg2) : DisguiseMessage(62), unknownC(arg2)
		{
		}
		virtual ~SetDisguiseDebugLevelDisguiseMsg()
		{
		}

		int unknownC;  // +0xC
	};

	// RTTI: proto::NoAIStateChangeMessage
	struct NoAIStateChangeMessage : public StateChangeMessage
	{
		explicit NoAIStateChangeMessage(bool arg2) : StateChangeMessage(2), unknownC(arg2)
		{
		}
		virtual ~NoAIStateChangeMessage()
		{
		}

		bool unknownC;  // +0xC
	};

	// RTTI: proto::AdjustPositionOutsideStateChangeMessage
	struct AdjustPositionOutsideStateChangeMessage : public StateChangeMessage
	{
		explicit AdjustPositionOutsideStateChangeMessage(bool arg2) : StateChangeMessage(11), unknownC(arg2)
		{
		}
		virtual ~AdjustPositionOutsideStateChangeMessage()
		{
		}

		bool unknownC;  // +0xC
	};

	// RTTI: proto::SetMaxTokensMsg
	struct SetMaxTokensMsg : public TokenMessage
	{
		SetMaxTokensMsg(int arg2, int arg3) : TokenMessage(3), unknownC(arg3), unknown10(arg2)
		{
		}
		virtual ~SetMaxTokensMsg()
		{
		}

		int unknownC;  // +0xC
		int unknown10;  // +0x10
	};

	// RTTI: proto::GetMaxTokensMsg
	struct GetMaxTokensMsg : public TokenMessage
	{
		explicit GetMaxTokensMsg(int arg2) : TokenMessage(4), unknownC(0), unknown10(arg2)
		{
		}
		virtual ~GetMaxTokensMsg()
		{
		}

		int unknownC;  // +0xC
		int unknown10;  // +0x10
	};

	// RTTI: proto::SetTokenWeightsMsg
	struct SetTokenWeightsMsg : public TokenMessage
	{
		explicit SetTokenWeightsMsg(int arg2) : TokenMessage(8), unknownC(arg2)
		{
		}
		virtual ~SetTokenWeightsMsg()
		{
		}

		int unknownC;  // +0xC
	};

	// RTTI: proto::NPCDrawableCreateMessage
	struct NPCDrawableCreateMessage : public ProtoRenderMsg
	{
		explicit NPCDrawableCreateMessage(bool arg2) : ProtoRenderMsg(12), unknownC(arg2)
		{
		}
		virtual ~NPCDrawableCreateMessage()
		{
		}

		bool unknownC;  // +0xC
	};

	// RTTI: proto::NPCDrawableDestroyMessage
	struct NPCDrawableDestroyMessage : public ProtoRenderMsg
	{
		NPCDrawableDestroyMessage() : ProtoRenderMsg(13)
		{
		}
		virtual ~NPCDrawableDestroyMessage()
		{
		}
	};

	// RTTI: proto::RegenerationMessage
	struct RegenerationMessage : public engine::IntrusiveMessage
	{
		RegenerationMessage(float arg2, float arg3, float arg4) : engine::IntrusiveMessage(0x14, 28), unknownC(arg2), unknown10(arg3), unknown14(arg4)
		{
		}
		virtual ~RegenerationMessage()
		{
		}

		float unknownC;  // +0xC
		float unknown10;  // +0x10
		float unknown14;  // +0x14
	};

	// RTTI: proto::SetNpcDamageMultiplierMessage
	struct SetNpcDamageMultiplierMessage : public engine::IntrusiveMessage
	{
		explicit SetNpcDamageMultiplierMessage(float arg2) : engine::IntrusiveMessage(0x14, 35), unknownC(arg2)
		{
		}
		virtual ~SetNpcDamageMultiplierMessage()
		{
		}

		float unknownC;  // +0xC
	};

	// RTTI: proto::AddChildHealthMessage
	struct AddChildHealthMessage : public engine::IntrusiveMessage
	{
		explicit AddChildHealthMessage(int arg2) : engine::IntrusiveMessage(0x14, 42), unknownC(arg2)
		{
		}
		virtual ~AddChildHealthMessage()
		{
		}

		int unknownC;  // +0xC
	};

	// RTTI: proto::ClearChildrenHealthMessage
	struct ClearChildrenHealthMessage : public engine::IntrusiveMessage
	{
		ClearChildrenHealthMessage() : engine::IntrusiveMessage(0x14, 43)
		{
		}
		virtual ~ClearChildrenHealthMessage()
		{
		}
	};

	// RTTI: proto::SetExtraFriendlyFireFactorMessage
	struct SetExtraFriendlyFireFactorMessage : public engine::IntrusiveMessage
	{
		explicit SetExtraFriendlyFireFactorMessage(float arg2) : engine::IntrusiveMessage(0x14, 46), unknownC(arg2)
		{
		}
		virtual ~SetExtraFriendlyFireFactorMessage()
		{
		}

		float unknownC;  // +0xC
	};

	// RTTI: proto::WorldGetAmbientZoneInfoMessage
	struct WorldGetAmbientZoneInfoMessage : public WorldMsg
	{
		WorldGetAmbientZoneInfoMessage() : WorldMsg(5)
		{
		}
		virtual ~WorldGetAmbientZoneInfoMessage()
		{
		}
	};

	// RTTI: proto::WorldKillHiveMessage
	struct WorldKillHiveMessage : public WorldMsg
	{
		WorldKillHiveMessage(float arg2, float arg3, float arg4, float arg5) : WorldMsg(8), unknownC(arg2), unknown10(arg3), unknown14(arg4), unknown18(arg5)
		{
		}
		virtual ~WorldKillHiveMessage()
		{
		}

		float unknownC;  // +0xC
		float unknown10;  // +0x10
		float unknown14;  // +0x14
		float unknown18;  // +0x18
	};

	// RTTI: proto::GetNumValidMembersSquadMessage
	struct GetNumValidMembersSquadMessage : public SquadMessage
	{
		GetNumValidMembersSquadMessage(bool arg2, bool arg3) : SquadMessage(12), unknownC(0), unknown10(arg2), unknown11(arg3)
		{
		}
		virtual ~GetNumValidMembersSquadMessage()
		{
		}

		int unknownC;  // +0xC
		bool unknown10;  // +0x10
		bool unknown11;  // +0x11
	};

	// RTTI: proto::IsMemberSquadMessage
	struct IsMemberSquadMessage : public SquadMessage
	{
		explicit IsMemberSquadMessage(int arg2) : SquadMessage(13), unknownC(arg2), unknown10(false)
		{
		}
		virtual ~IsMemberSquadMessage()
		{
		}

		int unknownC;  // +0xC
		bool unknown10;  // +0x10
	};

	// RTTI: proto::GetMemberListSquadMessage
	struct GetMemberListSquadMessage : public SquadMessage
	{
		GetMemberListSquadMessage() : SquadMessage(7), unknownC(0), unknown10(0)
		{
		}
		virtual ~GetMemberListSquadMessage()
		{
		}

		int unknownC;  // +0xC
		int unknown10;  // +0x10
	};

	// RTTI: proto::IsEngagedSquadMessage
	struct IsEngagedSquadMessage : public SquadMessage
	{
		IsEngagedSquadMessage() : SquadMessage(17), unknownC(11), unknown10()
		{
		}
		virtual ~IsEngagedSquadMessage()
		{
		}

		int unknownC;  // +0xC
		engine::GameObjectHandle unknown10;  // +0x10
	};

	// RTTI: proto::GetLastMemberChangeStateSquadMessage
	struct GetLastMemberChangeStateSquadMessage : public SquadMessage
	{
		GetLastMemberChangeStateSquadMessage() : SquadMessage(31), unknownC(0)
		{
		}
		virtual ~GetLastMemberChangeStateSquadMessage()
		{
		}

		int unknownC;  // +0xC
	};

	// RTTI: proto::DisableDueToAlertMessage
	struct DisableDueToAlertMessage : public SpawnMessage
	{
		explicit DisableDueToAlertMessage(bool arg2) : SpawnMessage(22), unknownC(arg2)
		{
		}
		virtual ~DisableDueToAlertMessage()
		{
		}

		bool unknownC;  // +0xC
	};

	// RTTI: proto::ReturnObjectSpawnMessage
	struct ReturnObjectSpawnMessage : public SpawnMessage
	{
		explicit ReturnObjectSpawnMessage(int arg2) : SpawnMessage(8), unknownC(arg2)
		{
		}
		virtual ~ReturnObjectSpawnMessage()
		{
		}

		int unknownC;  // +0xC
	};

	// RTTI: proto::GetUnDowngradableMsg
	struct GetUnDowngradableMsg : public LODAIMessage
	{
		GetUnDowngradableMsg() : LODAIMessage(8), unknownC(false)
		{
		}
		virtual ~GetUnDowngradableMsg()
		{
		}

		bool unknownC;  // +0xC
	};

	// RTTI: proto::PurgeKissOfDeathAIMsg
	struct PurgeKissOfDeathAIMsg : public LODAIMessage
	{
		PurgeKissOfDeathAIMsg() : LODAIMessage(12)
		{
		}
		virtual ~PurgeKissOfDeathAIMsg()
		{
		}
	};

	// RTTI: proto::GetSightRadiusPerceptionMessage
	struct GetSightRadiusPerceptionMessage : public PerceptionMessage
	{
		explicit GetSightRadiusPerceptionMessage(int arg2) : PerceptionMessage(16), unknownC(arg2), unknown10(choreo::gMinusOne)
		{
		}
		virtual ~GetSightRadiusPerceptionMessage()
		{
		}

		int unknownC;  // +0xC
		float unknown10;  // +0x10
	};

	// RTTI: proto::GetMaxBlownTimeDisguiseMsg
	struct GetMaxBlownTimeDisguiseMsg : public DisguiseMessage
	{
		GetMaxBlownTimeDisguiseMsg() : DisguiseMessage(23), unknownC(choreo::gMinusOne)
		{
		}
		virtual ~GetMaxBlownTimeDisguiseMsg()
		{
		}

		float unknownC;  // +0xC
	};

	// RTTI: proto::GetNpcDamageMultiplierMessage
	struct GetNpcDamageMultiplierMessage : public engine::IntrusiveMessage
	{
		GetNpcDamageMultiplierMessage() : engine::IntrusiveMessage(0x14, 36), unknownC(engine::driving::gOne)
		{
		}
		virtual ~GetNpcDamageMultiplierMessage()
		{
		}

		float unknownC;  // +0xC
	};

	// RTTI: proto::SetGoalAIMsg
	struct SetGoalAIMsg : public AIMessage
	{
		explicit SetGoalAIMsg(core::Name<core::CaseSensitiveKey> arg2) : AIMessage(6), goal(arg2)
		{
		}
		virtual ~SetGoalAIMsg()
		{
		}

		int unknownC;  // +0xC
		core::Name<core::CaseSensitiveKey> goal;  // +0x10
	};

	// RTTI: proto::SetBlownTimeForFactionDisguiseMsg
	struct SetBlownTimeForFactionDisguiseMsg : public DisguiseMessage
	{
		SetBlownTimeForFactionDisguiseMsg(core::Name<core::CaseSensitiveKey> arg2, float arg3) : DisguiseMessage(27), faction(arg2), unknown18(arg3)
		{
		}
		virtual ~SetBlownTimeForFactionDisguiseMsg()
		{
		}

		int unknownC;  // +0xC
		core::Name<core::CaseSensitiveKey> faction;  // +0x10
		float unknown18;  // +0x18
	};

	// RTTI: proto::SetTooltipAIMsg
	struct SetTooltipAIMsg : public AIMessage
	{
		SetTooltipAIMsg(const char* arg2, int arg3) : AIMessage(12), unknown40C(arg3)
		{
			core::StrNCpy(text, arg2, 0x400u);
		}
		virtual ~SetTooltipAIMsg()
		{
		}

		char text[0x400];  // +0xC
		int unknown40C;  // +0x40C
	};

	// The 48 bytes of the ambient zone information (layout unknown)
	struct AmbientZoneInfo
	{
		int unknown[12];
	};

	// RTTI: proto::WorldSetAmbientZoneInfoMessage
	struct WorldSetAmbientZoneInfoMessage : public WorldMsg
	{
		explicit WorldSetAmbientZoneInfoMessage(const AmbientZoneInfo& arg2) : WorldMsg(6), info(arg2)
		{
		}
		virtual ~WorldSetAmbientZoneInfoMessage()
		{
		}

		AmbientZoneInfo info;  // +0xC
	};
}

#endif
