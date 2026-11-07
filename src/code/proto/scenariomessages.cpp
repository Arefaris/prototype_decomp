#include "code/proto/scenariomessages.h"
#include "code/proto/collectiblebehaviour.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/scenario/scenariolisters.h"
#include <new>

namespace engine
{
	namespace scenario
	{
		// The registration of a message kind (the same template as scenariolisters.cpp has)
		template<class Message> void RegisterMessageKind(int event, const char* name)
		{
			gScenarioMessageLister.Add(name, event);
			ScenarioHandleInfo info = Message::GetHandleInfo();
			for (unsigned int i = 0; i < info.count; i++)
			{
				gAffiliateLister.Add(info.names[i], i);
			}
		}
	}
}

namespace fight
{
	class TrackRegistry;
}

namespace proto
{
	namespace fightitems
	{
		// The registration of the scenario message kinds in the editor's lists; it is called with the track registry of
		// the factories (name from the call site), which it does not use
		void RegisterAt1048FCE0Factories(fight::TrackRegistry* registry);
	}

	// FUNCTION: ENGINE 0x10493810
	engine::ScenarioMessage* ObjectSpawnedMessage::Clone(void* memory, int unused)
	{
		return new (memory) ObjectSpawnedMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048C870
	void ObjectSpawnedMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetHandle("object", engine::SerializeHandle(handles[0]));
		context->SetHandle("parent", engine::SerializeHandle(handles[1]));
	}

	// FUNCTION: ENGINE 0x10492360
	engine::ScenarioMessage* ObjectConsumedMessage::Clone(void* memory, int unused)
	{
		return new (memory) ObjectConsumedMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048C8E0
	void ObjectConsumedMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetHandle("consumed", engine::SerializeHandle(handles[0]));
		context->SetHandle("object", engine::SerializeHandle(handles[0]));
		context->SetHandle("originator", engine::SerializeHandle(handles[1]));
		context->SetBool("stealth", stealth);
		context->SetFloat("healthGained", healthGained);
		context->SetBool("woiTarget", woiTarget);
	}

	// FUNCTION: ENGINE 0x104923A0
	engine::ScenarioMessage* ObjectDamagedMessage::Clone(void* memory, int unused)
	{
		return new (memory) ObjectDamagedMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048C9B0
	void ObjectDamagedMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetHandle("object", engine::SerializeHandle(handles[0]));
		context->SetHandle("originator", engine::SerializeHandle(handles[1]));
		context->SetInt("attackType", attackType);
		context->SetFloat("damageTaken", damageTaken);
		context->SetFloat("damageGiven", damageGiven);
	}

	// FUNCTION: ENGINE 0x10492400
	engine::ScenarioMessage* TargetChangedMessage::Clone(void* memory, int unused)
	{
		return new (memory) TargetChangedMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048CBC0
	void TargetChangedMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetHandle("object", engine::SerializeHandle(handles[0]));
		context->SetHandle("prevTarget", engine::SerializeHandle(handles[1]));
	}

	// FUNCTION: ENGINE 0x10492470
	engine::ScenarioMessage* FixedTargetDeadMessage::Clone(void* memory, int unused)
	{
		return new (memory) FixedTargetDeadMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048CC30
	void FixedTargetDeadMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetHandle("object", engine::SerializeHandle(handles[0]));
		context->SetHandle("target", engine::SerializeHandle(handles[1]));
	}

	// FUNCTION: ENGINE 0x104924E0
	engine::ScenarioMessage* HintCancelledMessage::Clone(void* memory, int unused)
	{
		return new (memory) HintCancelledMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048CCA0
	void HintCancelledMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetName("stringUID", stringUID);
	}

	// FUNCTION: ENGINE 0x10492500
	engine::ScenarioMessage* HeliLandedStateChangeMessage::Clone(void* memory, int unused)
	{
		return new (memory) HeliLandedStateChangeMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048CCC0
	void HeliLandedStateChangeMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetBool("landed", landed);
	}

	// FUNCTION: ENGINE 0x10492570
	engine::ScenarioMessage* EnterAlertScenarioMsg::Clone(void* memory, int unused)
	{
		return new (memory) EnterAlertScenarioMsg(*this);
	}

	// FUNCTION: ENGINE 0x1048CCE0
	void EnterAlertScenarioMsg::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetHandle("player", engine::SerializeHandle(handles[0]));
	}

	// FUNCTION: ENGINE 0x104925E0
	engine::ScenarioMessage* LeaveAlertScenarioMsg::Clone(void* memory, int unused)
	{
		return new (memory) LeaveAlertScenarioMsg(*this);
	}

	// FUNCTION: ENGINE 0x1048CD10
	void LeaveAlertScenarioMsg::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetHandle("player", engine::SerializeHandle(handles[0]));
	}

	// FUNCTION: ENGINE 0x10492650
	engine::ScenarioMessage* DisguiseBlownScenarioMsg::Clone(void* memory, int unused)
	{
		return new (memory) DisguiseBlownScenarioMsg(*this);
	}

	// FUNCTION: ENGINE 0x1048CD40
	void DisguiseBlownScenarioMsg::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetHandle("player", engine::SerializeHandle(handles[0]));
	}

	// FUNCTION: ENGINE 0x104926C0
	engine::ScenarioMessage* DisguiseUnblownScenarioMsg::Clone(void* memory, int unused)
	{
		return new (memory) DisguiseUnblownScenarioMsg(*this);
	}

	// FUNCTION: ENGINE 0x1048CD70
	void DisguiseUnblownScenarioMsg::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetHandle("player", engine::SerializeHandle(handles[0]));
	}

	// FUNCTION: ENGINE 0x10492730
	engine::ScenarioMessage* PlayerWatchedScenarioMsg::Clone(void* memory, int unused)
	{
		return new (memory) PlayerWatchedScenarioMsg(*this);
	}

	// FUNCTION: ENGINE 0x1048CDA0
	void PlayerWatchedScenarioMsg::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetHandle("player", engine::SerializeHandle(handles[0]));
	}

	// FUNCTION: ENGINE 0x104927A0
	engine::ScenarioMessage* PlayerUnwatchedScenarioMsg::Clone(void* memory, int unused)
	{
		return new (memory) PlayerUnwatchedScenarioMsg(*this);
	}

	// FUNCTION: ENGINE 0x1048CDD0
	void PlayerUnwatchedScenarioMsg::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetHandle("player", engine::SerializeHandle(handles[0]));
	}

	// FUNCTION: ENGINE 0x10492810
	engine::ScenarioMessage* BaseEnterAlertScenarioMsg::Clone(void* memory, int unused)
	{
		return new (memory) BaseEnterAlertScenarioMsg(*this);
	}

	// FUNCTION: ENGINE 0x1048CE00
	void BaseEnterAlertScenarioMsg::WriteFields(engine::LuaScriptManager* context)
	{
	}

	// FUNCTION: ENGINE 0x10492880
	engine::ScenarioMessage* BaseLeaveAlertScenarioMsg::Clone(void* memory, int unused)
	{
		return new (memory) BaseLeaveAlertScenarioMsg(*this);
	}

	// FUNCTION: ENGINE 0x1048CE10
	void BaseLeaveAlertScenarioMsg::WriteFields(engine::LuaScriptManager* context)
	{
	}

	// FUNCTION: ENGINE 0x104928F0
	engine::ScenarioMessage* BaseBackToIdleScenarioMsg::Clone(void* memory, int unused)
	{
		return new (memory) BaseBackToIdleScenarioMsg(*this);
	}

	// FUNCTION: ENGINE 0x1048CE20
	void BaseBackToIdleScenarioMsg::WriteFields(engine::LuaScriptManager* context)
	{
	}

	// FUNCTION: ENGINE 0x10492960
	engine::ScenarioMessage* BaseEnterBeginCombatScenarioMsg::Clone(void* memory, int unused)
	{
		return new (memory) BaseEnterBeginCombatScenarioMsg(*this);
	}

	// FUNCTION: ENGINE 0x1048CE30
	void BaseEnterBeginCombatScenarioMsg::WriteFields(engine::LuaScriptManager* context)
	{
	}

	// FUNCTION: ENGINE 0x104929D0
	engine::ScenarioMessage* DisguiseHUDWhiteScenarioMsg::Clone(void* memory, int unused)
	{
		return new (memory) DisguiseHUDWhiteScenarioMsg(*this);
	}

	// FUNCTION: ENGINE 0x1048CE40
	void DisguiseHUDWhiteScenarioMsg::WriteFields(engine::LuaScriptManager* context)
	{
	}

	// FUNCTION: ENGINE 0x10492A40
	engine::ScenarioMessage* DisguiseHUDYellowScenarioMsg::Clone(void* memory, int unused)
	{
		return new (memory) DisguiseHUDYellowScenarioMsg(*this);
	}

	// FUNCTION: ENGINE 0x1048CE50
	void DisguiseHUDYellowScenarioMsg::WriteFields(engine::LuaScriptManager* context)
	{
	}

	// FUNCTION: ENGINE 0x10492AB0
	engine::ScenarioMessage* DisguiseHUDRedScenarioMsg::Clone(void* memory, int unused)
	{
		return new (memory) DisguiseHUDRedScenarioMsg(*this);
	}

	// FUNCTION: ENGINE 0x1048CE60
	void DisguiseHUDRedScenarioMsg::WriteFields(engine::LuaScriptManager* context)
	{
	}

	// FUNCTION: ENGINE 0x10492B20
	engine::ScenarioMessage* DisguiseHUDRedHideScenarioMsg::Clone(void* memory, int unused)
	{
		return new (memory) DisguiseHUDRedHideScenarioMsg(*this);
	}

	// FUNCTION: ENGINE 0x1048CE70
	void DisguiseHUDRedHideScenarioMsg::WriteFields(engine::LuaScriptManager* context)
	{
	}

	// FUNCTION: ENGINE 0x10492B90
	engine::ScenarioMessage* PlayerEngagedScenarioMsg::Clone(void* memory, int unused)
	{
		return new (memory) PlayerEngagedScenarioMsg(*this);
	}

	// FUNCTION: ENGINE 0x1048CE80
	void PlayerEngagedScenarioMsg::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetHandle("player", engine::SerializeHandle(handles[0]));
	}

	// FUNCTION: ENGINE 0x10492C00
	engine::ScenarioMessage* RadioAttemptScenarioMsg::Clone(void* memory, int unused)
	{
		return new (memory) RadioAttemptScenarioMsg(*this);
	}

	// FUNCTION: ENGINE 0x1048CEB0
	void RadioAttemptScenarioMsg::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetHandle("radioer", engine::SerializeHandle(handles[0]));
	}

	// FUNCTION: ENGINE 0x10492CE0
	engine::ScenarioMessage* DebugStateMachineStateChangedMessage::Clone(void* memory, int unused)
	{
		return new (memory) DebugStateMachineStateChangedMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048CF40
	void DebugStateMachineStateChangedMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetHandle("statemachine", engine::SerializeHandle(handles[0]));
	}

	// FUNCTION: ENGINE 0x10492D00
	engine::ScenarioMessage* DebugStateMachineStartedMessage::Clone(void* memory, int unused)
	{
		return new (memory) DebugStateMachineStartedMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048CF70
	void DebugStateMachineStartedMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetHandle("statemachine", engine::SerializeHandle(handles[0]));
	}

	// FUNCTION: ENGINE 0x10492D70
	engine::ScenarioMessage* DebugStateMachineStoppedMessage::Clone(void* memory, int unused)
	{
		return new (memory) DebugStateMachineStoppedMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048CFA0
	void DebugStateMachineStoppedMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetHandle("statemachine", engine::SerializeHandle(handles[0]));
	}

	// FUNCTION: ENGINE 0x10492D90
	engine::ScenarioMessage* SpawnerFinishedScenarioMessage::Clone(void* memory, int unused)
	{
		return new (memory) SpawnerFinishedScenarioMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048CFD0
	void SpawnerFinishedScenarioMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetHandle("spawner", engine::SerializeHandle(handles[0]));
	}

	// FUNCTION: ENGINE 0x10492E00
	engine::ScenarioMessage* SpawnerAllZeroHealthScenarioMessage::Clone(void* memory, int unused)
	{
		return new (memory) SpawnerAllZeroHealthScenarioMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048D000
	void SpawnerAllZeroHealthScenarioMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetHandle("spawner", engine::SerializeHandle(handles[0]));
	}

	// FUNCTION: ENGINE 0x10492E70
	engine::ScenarioMessage* SpawnerAllSpawnedScenarioMessage::Clone(void* memory, int unused)
	{
		return new (memory) SpawnerAllSpawnedScenarioMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048D030
	void SpawnerAllSpawnedScenarioMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetHandle("spawner", engine::SerializeHandle(handles[0]));
	}

	// FUNCTION: ENGINE 0x10492F50
	engine::ScenarioMessage* SquadDisbandedScenarioMessage::Clone(void* memory, int unused)
	{
		return new (memory) SquadDisbandedScenarioMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048D060
	void SquadDisbandedScenarioMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetHandle("squad", engine::SerializeHandle(handles[0]));
	}

	// FUNCTION: ENGINE 0x10492FC0
	engine::ScenarioMessage* EnterVehicleScenarioMessage::Clone(void* memory, int unused)
	{
		return new (memory) EnterVehicleScenarioMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048D090
	void EnterVehicleScenarioMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetHandle("character", engine::SerializeHandle(handles[0]));
		context->SetHandle("vehicle", engine::SerializeHandle(handles[1]));
		context->SetBool("hijackedByPlayer", hijackedByPlayer);
	}

	// FUNCTION: ENGINE 0x10493030
	engine::ScenarioMessage* ExitVehicleScenarioMessage::Clone(void* memory, int unused)
	{
		return new (memory) ExitVehicleScenarioMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048D110
	void ExitVehicleScenarioMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetHandle("character", engine::SerializeHandle(handles[0]));
		context->SetHandle("vehicle", engine::SerializeHandle(handles[1]));
	}

	// FUNCTION: ENGINE 0x104930A0
	engine::ScenarioMessage* ObjectGrabbedScenarioMessage::Clone(void* memory, int unused)
	{
		return new (memory) ObjectGrabbedScenarioMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048D180
	void ObjectGrabbedScenarioMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetHandle("grabber", engine::SerializeHandle(handles[0]));
		context->SetHandle("grabbed", engine::SerializeHandle(handles[1]));
		context->SetName("grabSlot", grabSlot);
	}

	// FUNCTION: ENGINE 0x104930C0
	engine::ScenarioMessage* ObjectDroppedScenarioMessage::Clone(void* memory, int unused)
	{
		return new (memory) ObjectDroppedScenarioMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048D200
	void ObjectDroppedScenarioMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetHandle("grabber", engine::SerializeHandle(handles[0]));
		context->SetHandle("dropped", engine::SerializeHandle(handles[1]));
		context->SetName("grabSlot", grabSlot);
	}

	// FUNCTION: ENGINE 0x104930E0
	engine::ScenarioMessage* ObjectThrownScenarioMessage::Clone(void* memory, int unused)
	{
		return new (memory) ObjectThrownScenarioMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048D280
	void ObjectThrownScenarioMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetHandle("object", engine::SerializeHandle(handles[0]));
		context->SetHandle("from", engine::SerializeHandle(handles[1]));
		context->SetHandle("to", engine::SerializeHandle(handles[2]));
	}

	// FUNCTION: ENGINE 0x10493150
	engine::ScenarioMessage* MotionStateScenarioMessage::Clone(void* memory, int unused)
	{
		return new (memory) MotionStateScenarioMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048D310
	void MotionStateScenarioMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetHandle("player", engine::SerializeHandle(handles[0]));
		context->SetInt("motionState", motionState);
		context->SetInt("prevMotionState", prevMotionState);
	}

	// FUNCTION: ENGINE 0x10493170
	engine::ScenarioMessage* SupportingSurfaceChangedScenarioMessage::Clone(void* memory, int unused)
	{
		return new (memory) SupportingSurfaceChangedScenarioMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048D380
	void SupportingSurfaceChangedScenarioMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetHandle("player", engine::SerializeHandle(handles[0]));
		context->SetBool("onSurface", onSurface);
	}

	// FUNCTION: ENGINE 0x104931E0
	engine::ScenarioMessage* CollectibleSpawnedScenarioMessage::Clone(void* memory, int unused)
	{
		return new (memory) CollectibleSpawnedScenarioMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048D3D0
	void CollectibleSpawnedScenarioMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetHandle("collectible", engine::SerializeHandle(handles[0]));
		context->SetInt("collectibleType", collectibleType);
		context->SetName("scriptedType", scriptedType);
	}

	// FUNCTION: ENGINE 0x10493200
	engine::ScenarioMessage* CollectibleCollectedScenarioMessage::Clone(void* memory, int unused)
	{
		return new (memory) CollectibleCollectedScenarioMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048D440
	void CollectibleCollectedScenarioMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetHandle("collectible", engine::SerializeHandle(handles[0]));
		context->SetInt("collectibleType", unknown1C);
		context->SetName("scriptedType", name);
	}

	// FUNCTION: ENGINE 0x10493220
	engine::ScenarioMessage* CollectibleEndOfLifeScenarioMessage::Clone(void* memory, int unused)
	{
		return new (memory) CollectibleEndOfLifeScenarioMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048D4B0
	void CollectibleEndOfLifeScenarioMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetInt("collectibleType", unknown1C);
		context->SetName("scriptedType", name);
	}

	// FUNCTION: ENGINE 0x10493240
	engine::ScenarioMessage* WOINodeStateScenarioMessage::Clone(void* memory, int unused)
	{
		return new (memory) WOINodeStateScenarioMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048D4F0
	void WOINodeStateScenarioMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetInt("nodeID", nodeID);
		context->SetInt("state", state);
	}

	// FUNCTION: ENGINE 0x10493260
	engine::ScenarioMessage* WOINodeFMVPlayedScenarioMessage::Clone(void* memory, int unused)
	{
		return new (memory) WOINodeFMVPlayedScenarioMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048D530
	void WOINodeFMVPlayedScenarioMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetInt("nodeID", nodeID);
	}

	// FUNCTION: ENGINE 0x104932D0
	engine::ScenarioMessage* PatrolDestroyedScenarioMessage::Clone(void* memory, int unused)
	{
		return new (memory) PatrolDestroyedScenarioMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048D550
	void PatrolDestroyedScenarioMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetInt("heightLevel", heightLevel);
		context->SetInt("numVehicles", numVehicles);
	}

	// FUNCTION: ENGINE 0x104932F0
	engine::ScenarioMessage* StrikeTeamDestroyedScenarioMessage::Clone(void* memory, int unused)
	{
		return new (memory) StrikeTeamDestroyedScenarioMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048D590
	void StrikeTeamDestroyedScenarioMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetHandle("strikeTeam", engine::SerializeHandle(handles[0]));
		context->SetHandle("originator", engine::SerializeHandle(handles[1]));
	}

	// FUNCTION: ENGINE 0x10493360
	engine::ScenarioMessage* StrikeTeamEvadedScenarioMessage::Clone(void* memory, int unused)
	{
		return new (memory) StrikeTeamEvadedScenarioMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048D600
	void StrikeTeamEvadedScenarioMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetHandle("strikeTeam", engine::SerializeHandle(handles[0]));
		context->SetHandle("originator", engine::SerializeHandle(handles[1]));
	}

	// FUNCTION: ENGINE 0x104933D0
	engine::ScenarioMessage* StrikeTeamInboundScenarioMessage::Clone(void* memory, int unused)
	{
		return new (memory) StrikeTeamInboundScenarioMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048D670
	void StrikeTeamInboundScenarioMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetHandle("strikeTeam", engine::SerializeHandle(handles[0]));
		context->SetHandle("target", engine::SerializeHandle(handles[1]));
	}

	// FUNCTION: ENGINE 0x10493440
	engine::ScenarioMessage* BaseOrHiveDestroyedScenarioMessage::Clone(void* memory, int unused)
	{
		return new (memory) BaseOrHiveDestroyedScenarioMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048D6E0
	void BaseOrHiveDestroyedScenarioMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetInt("cellNumber", cellNumber);
		context->SetBool("isHive", isHive);
	}

	// FUNCTION: ENGINE 0x10493460
	engine::ScenarioMessage* BaseOrHiveScenarioMessage::Clone(void* memory, int unused)
	{
		return new (memory) BaseOrHiveScenarioMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048D720
	void BaseOrHiveScenarioMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetInt("cellNumber", cellNumber);
		context->SetBool("isHive", isHive);
		context->SetName("action", action);
	}

	// FUNCTION: ENGINE 0x10493680
	engine::ScenarioMessage* NISDoneScenarioMessage::Clone(void* memory, int unused)
	{
		return new (memory) NISDoneScenarioMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048D8A0
	void NISDoneScenarioMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetName("NISName", NISName);
	}

	// FUNCTION: ENGINE 0x104936A0
	engine::ScenarioMessage* WOITargetSpawnedScenarioMessage::Clone(void* memory, int unused)
	{
		return new (memory) WOITargetSpawnedScenarioMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048D8C0
	void WOITargetSpawnedScenarioMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetHandle("targetObject", engine::SerializeHandle(handles[0]));
		context->SetInt("WOINodeID", WOINodeID);
	}

	// FUNCTION: ENGINE 0x10493710
	engine::ScenarioMessage* WOITargetConsumedScenarioMessage::Clone(void* memory, int unused)
	{
		return new (memory) WOITargetConsumedScenarioMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048D910
	void WOITargetConsumedScenarioMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetHandle("targetObject", engine::SerializeHandle(handles[0]));
		context->SetInt("NodeCompletedInEpisode", NodeCompletedInEpisode);
		context->SetInt("EpisodeComplete", EpisodeComplete);
		context->SetBool("WOIComplete", WOIComplete);
	}

	// FUNCTION: ENGINE 0x10493730
	engine::ScenarioMessage* UnlockableAcquiredScenarioMessage::Clone(void* memory, int unused)
	{
		return new (memory) UnlockableAcquiredScenarioMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048D990
	void UnlockableAcquiredScenarioMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetInt("unlockable", unlockable);
	}

	// FUNCTION: ENGINE 0x104937A0
	engine::ScenarioMessage* UnlockableIncrementedPurchaseTypeScenarioMessage::Clone(void* memory, int unused)
	{
		return new (memory) UnlockableIncrementedPurchaseTypeScenarioMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048D9B0
	void UnlockableIncrementedPurchaseTypeScenarioMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetInt("purchaseType", purchaseType);
	}

	// FUNCTION: ENGINE 0x10490130
	engine::ScenarioMessage* ObjectZeroHealthMessage::Clone(void* memory, int unused)
	{
		return new (memory) ObjectZeroHealthMessage(handles[0], handles[1], attackType, spawnCollectible);
	}

	// FUNCTION: ENGINE 0x1048CB00
	void ObjectZeroHealthMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetHandle("object", engine::SerializeHandle(handles[0]));
		context->SetHandle("originator", engine::SerializeHandle(handles[1]));
		context->SetInt("attackType", attackType);
		context->SetBool("spawnCollectible", spawnCollectible);
	}

	// FUNCTION: ENGINE 0x10490190
	engine::ScenarioMessage* ObjectOffscreenDespawnMessage::Clone(void* memory, int unused)
	{
		return new (memory) ObjectOffscreenDespawnMessage(handles[0]);
	}

	// FUNCTION: ENGINE 0x1048CB90
	void ObjectOffscreenDespawnMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetHandle("object", engine::SerializeHandle(handles[0]));
	}

	// FUNCTION: ENGINE 0x10492380
	engine::ScenarioMessage* DisguiseChangedMessage::Clone(void* memory, int unused)
	{
		return new (memory) DisguiseChangedMessage(*this);
	}

	// FUNCTION: ENGINE 0x104900C0
	void DisguiseChangedMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetHandle("object", engine::SerializeHandle(handles[0]));
		{
			core::Name<core::CaseSensitiveKey> faction(newFaction);
			context->SetName("newFaction", faction);
		}
	}

	// FUNCTION: ENGINE 0x104923C0
	engine::ScenarioMessage* ObjectDeadMessage::Clone(void* memory, int unused)
	{
		return new (memory) ObjectDeadMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048CA60
	void ObjectDeadMessage::WriteFields(engine::LuaScriptManager* context)
	{
		context->SetHandle("dead", engine::SerializeHandle(handles[0]));
		context->SetHandle("object", engine::SerializeHandle(handles[0]));
		context->SetHandle("originator", engine::SerializeHandle(handles[1]));
		context->SetInt("attackType", attackType);
	}

	// FUNCTION: ENGINE 0x10493480
	engine::ScenarioMessage* AboutToSaveGameScenarioMessage::Clone(void* memory, int unused)
	{
		return new (memory) AboutToSaveGameScenarioMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048D770
	bool AboutToSaveGameScenarioMessage::WriteEvent()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x104934F0
	engine::ScenarioMessage* AboutToSaveCheckpointScenarioMessage::Clone(void* memory, int unused)
	{
		return new (memory) AboutToSaveCheckpointScenarioMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048D780
	bool AboutToSaveCheckpointScenarioMessage::WriteEvent()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x10493560
	engine::ScenarioMessage* JustLoadedCheckpointScenarioMessage::Clone(void* memory, int unused)
	{
		return new (memory) JustLoadedCheckpointScenarioMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048D790
	bool JustLoadedCheckpointScenarioMessage::WriteEvent()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x104935D0
	engine::ScenarioMessage* AboutToLoadCheckpointScenarioMessage::Clone(void* memory, int unused)
	{
		return new (memory) AboutToLoadCheckpointScenarioMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048D7A0
	bool AboutToLoadCheckpointScenarioMessage::WriteEvent()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x10493640
	engine::ScenarioMessage* FreeRoamEventScenarioMessage::Clone(void* memory, int unused)
	{
		return new (memory) FreeRoamEventScenarioMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048D7B0
	bool FreeRoamEventScenarioMessage::WriteEvent()
	{
		engine::LuaScriptManager* context = engine::GetScriptManager();
		if (context == 0)
		{
			return false;
		}
		if (!context->OpenEvent())
		{
			return false;
		}
		context->SetInt("state", state);
		context->SetName("eventName", eventName);
		context->SetName("className", className);
		context->SetName("string", string);
		context->Close();
		return true;
	}

	// FUNCTION: ENGINE 0x10493660
	engine::ScenarioMessage* FramerCamEventScenarioMessage::Clone(void* memory, int unused)
	{
		return new (memory) FramerCamEventScenarioMessage(*this);
	}

	// FUNCTION: ENGINE 0x1048D840
	bool FramerCamEventScenarioMessage::WriteEvent()
	{
		engine::LuaScriptManager* context = engine::GetScriptManager();
		if (context == 0)
		{
			return false;
		}
		if (!context->OpenEvent())
		{
			return false;
		}
		context->SetInt("type", type);
		context->SetName("name", name);
		context->Close();
		return true;
	}

	// FUNCTION: ENGINE 0x104923E0
	engine::ScenarioMessage* DestinationReachedMessage::Clone(void* memory, int unused)
	{
		return new (memory) DestinationReachedMessage(*this);
	}

	// FUNCTION: ENGINE 0x10492C70
	engine::ScenarioMessage* StateMachineStateChangedMessage::Clone(void* memory, int unused)
	{
		return new (memory) StateMachineStateChangedMessage(*this);
	}

	// FUNCTION: ENGINE 0x10492EE0
	engine::ScenarioMessage* SquadSpawnedScenarioMessage::Clone(void* memory, int unused)
	{
		return new (memory) SquadSpawnedScenarioMessage(*this);
	}


	// FUNCTION: ENGINE 0x1048FCE0
	void fightitems::RegisterAt1048FCE0Factories(fight::TrackRegistry* registry)
	{
		engine::scenario::RegisterMessageKind<proto::DestinationReachedMessage>(0x1a, "Destination Reached");
		engine::scenario::RegisterMessageKind<proto::DisguiseChangedMessage>(0x15, "Disguise Changed");
		engine::scenario::RegisterMessageKind<proto::FixedTargetDeadMessage>(0x1c, "Fixed Target Dead");
		engine::scenario::RegisterMessageKind<proto::ObjectSpawnedMessage>(0x14, "Object Spawned");
		engine::scenario::RegisterMessageKind<proto::HeliLandedStateChangeMessage>(0x1e, "Heli Landed State Change");
		engine::scenario::RegisterMessageKind<proto::ObjectConsumedMessage>(0x13, "Object Consumed");
		engine::scenario::RegisterMessageKind<proto::ObjectDamagedMessage>(0x16, "Object Damaged");
		engine::scenario::RegisterMessageKind<proto::ObjectDeadMessage>(0x17, "Object Dead");
		engine::scenario::RegisterMessageKind<proto::ObjectZeroHealthMessage>(0x18, "Object Zero Health");
		engine::scenario::RegisterMessageKind<proto::ObjectOffscreenDespawnMessage>(0x19, "Object Offscreen Despawn");
		engine::scenario::RegisterMessageKind<proto::TargetChangedMessage>(0x1b, "Target Changed");
		engine::scenario::RegisterMessageKind<proto::HintCancelledMessage>(0x1b, "Hint Cancelled");
		engine::scenario::RegisterMessageKind<proto::StateMachineStateChangedMessage>(0x30, "State Machine State Change");
		engine::scenario::RegisterMessageKind<proto::EnterAlertScenarioMsg>(0x1f, "Enter Alert");
		engine::scenario::RegisterMessageKind<proto::LeaveAlertScenarioMsg>(0x20, "Leave Alert");
		engine::scenario::RegisterMessageKind<proto::DisguiseBlownScenarioMsg>(0x22, "Disguise Blown");
		engine::scenario::RegisterMessageKind<proto::DisguiseUnblownScenarioMsg>(0x23, "Disguise Unblown");
		engine::scenario::RegisterMessageKind<proto::PlayerWatchedScenarioMsg>(0x24, "Player Watched");
		engine::scenario::RegisterMessageKind<proto::PlayerUnwatchedScenarioMsg>(0x25, "Player Unwatched");
		engine::scenario::RegisterMessageKind<proto::BaseEnterAlertScenarioMsg>(0x26, "Base Enter Alert");
		engine::scenario::RegisterMessageKind<proto::BaseLeaveAlertScenarioMsg>(0x27, "Base Leave Alert");
		engine::scenario::RegisterMessageKind<proto::BaseBackToIdleScenarioMsg>(0x28, "Base Back To Idle");
		engine::scenario::RegisterMessageKind<proto::BaseEnterBeginCombatScenarioMsg>(0x29, "Base Enter BeginCombat");
		engine::scenario::RegisterMessageKind<proto::DisguiseHUDWhiteScenarioMsg>(0x2a, "Disguise HUD White");
		engine::scenario::RegisterMessageKind<proto::DisguiseHUDYellowScenarioMsg>(0x2b, "Disguise HUD Yellow");
		engine::scenario::RegisterMessageKind<proto::DisguiseHUDRedScenarioMsg>(0x2c, "Disguise HUD Red");
		engine::scenario::RegisterMessageKind<proto::DisguiseHUDRedHideScenarioMsg>(0x2d, "Disguise HUD Red Hide");
		engine::scenario::RegisterMessageKind<proto::PlayerEngagedScenarioMsg>(0x2e, "Player Engaged");
		engine::scenario::RegisterMessageKind<proto::RadioAttemptScenarioMsg>(0x2f, "Radio Attempt");
		engine::scenario::RegisterMessageKind<proto::SpawnerAllSpawnedScenarioMessage>(0x34, "Spawner All Spawned");
		engine::scenario::RegisterMessageKind<proto::SpawnerFinishedScenarioMessage>(0x35, "Spawner Finished");
		engine::scenario::RegisterMessageKind<proto::SpawnerAllZeroHealthScenarioMessage>(0x36, "Spawner All Zero Health");
		engine::scenario::RegisterMessageKind<proto::SquadSpawnedScenarioMessage>(0x37, "Squad Spawned");
		engine::scenario::RegisterMessageKind<proto::SquadDisbandedScenarioMessage>(0x38, "Squad Disbanded");
		engine::scenario::RegisterMessageKind<proto::EnterVehicleScenarioMessage>(0x39, "Enter Vehicle");
		engine::scenario::RegisterMessageKind<proto::ExitVehicleScenarioMessage>(0x3a, "Exit Vehicle");
		engine::scenario::RegisterMessageKind<proto::ObjectGrabbedScenarioMessage>(0x3b, "Object Grabbed");
		engine::scenario::RegisterMessageKind<proto::ObjectDroppedScenarioMessage>(0x3c, "Object Dropped");
		engine::scenario::RegisterMessageKind<proto::ObjectThrownScenarioMessage>(0x3d, "Object Thrown");
		engine::scenario::RegisterMessageKind<proto::MotionStateScenarioMessage>(0x3e, "Motion State Changed");
		engine::scenario::RegisterMessageKind<proto::SupportingSurfaceChangedScenarioMessage>(0x3f, "Supporting Surface Changed");
		engine::scenario::RegisterMessageKind<proto::CollectibleSpawnedScenarioMessage>(0x40, "Collectible Spawned");
		engine::scenario::RegisterMessageKind<proto::CollectibleCollectedScenarioMessage>(0x41, "Collectible Collected");
		engine::scenario::RegisterMessageKind<proto::CollectibleEndOfLifeScenarioMessage>(0x42, "Collectible End Of Life");
		engine::scenario::RegisterMessageKind<proto::WOINodeStateScenarioMessage>(0x43, "WOI Node State Changed");
		engine::scenario::RegisterMessageKind<proto::WOINodeFMVPlayedScenarioMessage>(0x44, "WOI FMV Played");
		engine::scenario::RegisterMessageKind<proto::PatrolDestroyedScenarioMessage>(0x45, "Patrol Destroyed");
		engine::scenario::RegisterMessageKind<proto::StrikeTeamDestroyedScenarioMessage>(0x46, "Strike Team Destroyed");
		engine::scenario::RegisterMessageKind<proto::StrikeTeamEvadedScenarioMessage>(0x47, "Strike Team Evaded");
		engine::scenario::RegisterMessageKind<proto::StrikeTeamInboundScenarioMessage>(0x48, "Strike Team Inbound");
		engine::scenario::RegisterMessageKind<proto::BaseOrHiveDestroyedScenarioMessage>(0x49, "Base or Hive Destroyed");
		engine::scenario::RegisterMessageKind<proto::BaseOrHiveScenarioMessage>(0x4a, "Base or Hive Generic");
		engine::scenario::RegisterMessageKind<proto::AboutToSaveGameScenarioMessage>(0x4b, "About to Save the Game");
		engine::scenario::RegisterMessageKind<proto::AboutToSaveCheckpointScenarioMessage>(0x4c, "About to Save a Checkpoint");
		engine::scenario::RegisterMessageKind<proto::JustLoadedCheckpointScenarioMessage>(0x4d, "Just loaded a Checkpoint");
		engine::scenario::RegisterMessageKind<proto::AboutToLoadCheckpointScenarioMessage>(0x4e, "About to Load a Checkpoint");
		engine::scenario::RegisterMessageKind<proto::FreeRoamEventScenarioMessage>(0x4f, "Free Roam Event");
		engine::scenario::RegisterMessageKind<proto::FramerCamEventScenarioMessage>(0x50, "Framer Camera Event");
		engine::scenario::RegisterMessageKind<proto::NISDoneScenarioMessage>(0x51, "NIS Done");
		engine::scenario::RegisterMessageKind<proto::WOITargetSpawnedScenarioMessage>(0x52, "WOI Target Spawned");
		engine::scenario::RegisterMessageKind<proto::WOITargetSpawnedScenarioMessage>(0x53, "WOI Target Consumed");
		engine::scenario::RegisterMessageKind<proto::UnlockableAcquiredScenarioMessage>(0x54, "Unlockable Acquired");
		engine::scenario::RegisterMessageKind<proto::UnlockableIncrementedPurchaseTypeScenarioMessage>(0x55, "Unlockable Incremented Purchase Type");
		engine::scenario::SortListers();
	}

}

namespace engine
{
	namespace scenario
	{
		// FUNCTION: ENGINE 0x1048DB80
		template void RegisterMessageKind<proto::ObjectSpawnedMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048DCA0
		template void RegisterMessageKind<proto::ObjectConsumedMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048DD30
		template void RegisterMessageKind<proto::ObjectDamagedMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048DF70
		template void RegisterMessageKind<proto::TargetChangedMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048DAF0
		template void RegisterMessageKind<proto::FixedTargetDeadMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048E000
		template void RegisterMessageKind<proto::HintCancelledMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048DC10
		template void RegisterMessageKind<proto::HeliLandedStateChangeMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048E120
		template void RegisterMessageKind<proto::EnterAlertScenarioMsg>(int, const char*);
		// FUNCTION: ENGINE 0x1048E1B0
		template void RegisterMessageKind<proto::LeaveAlertScenarioMsg>(int, const char*);
		// FUNCTION: ENGINE 0x1048E240
		template void RegisterMessageKind<proto::DisguiseBlownScenarioMsg>(int, const char*);
		// FUNCTION: ENGINE 0x1048E2D0
		template void RegisterMessageKind<proto::DisguiseUnblownScenarioMsg>(int, const char*);
		// FUNCTION: ENGINE 0x1048E360
		template void RegisterMessageKind<proto::PlayerWatchedScenarioMsg>(int, const char*);
		// FUNCTION: ENGINE 0x1048E3F0
		template void RegisterMessageKind<proto::PlayerUnwatchedScenarioMsg>(int, const char*);
		// FUNCTION: ENGINE 0x1048E480
		template void RegisterMessageKind<proto::BaseEnterAlertScenarioMsg>(int, const char*);
		// FUNCTION: ENGINE 0x1048E510
		template void RegisterMessageKind<proto::BaseLeaveAlertScenarioMsg>(int, const char*);
		// FUNCTION: ENGINE 0x1048E5A0
		template void RegisterMessageKind<proto::BaseBackToIdleScenarioMsg>(int, const char*);
		// FUNCTION: ENGINE 0x1048E630
		template void RegisterMessageKind<proto::BaseEnterBeginCombatScenarioMsg>(int, const char*);
		// FUNCTION: ENGINE 0x1048E6C0
		template void RegisterMessageKind<proto::DisguiseHUDWhiteScenarioMsg>(int, const char*);
		// FUNCTION: ENGINE 0x1048E750
		template void RegisterMessageKind<proto::DisguiseHUDYellowScenarioMsg>(int, const char*);
		// FUNCTION: ENGINE 0x1048E7E0
		template void RegisterMessageKind<proto::DisguiseHUDRedScenarioMsg>(int, const char*);
		// FUNCTION: ENGINE 0x1048E870
		template void RegisterMessageKind<proto::DisguiseHUDRedHideScenarioMsg>(int, const char*);
		// FUNCTION: ENGINE 0x1048E900
		template void RegisterMessageKind<proto::PlayerEngagedScenarioMsg>(int, const char*);
		// FUNCTION: ENGINE 0x1048E990
		template void RegisterMessageKind<proto::RadioAttemptScenarioMsg>(int, const char*);
		// FUNCTION: ENGINE 0x1048EAB0
		template void RegisterMessageKind<proto::SpawnerFinishedScenarioMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048EB40
		template void RegisterMessageKind<proto::SpawnerAllZeroHealthScenarioMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048EA20
		template void RegisterMessageKind<proto::SpawnerAllSpawnedScenarioMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048EC60
		template void RegisterMessageKind<proto::SquadDisbandedScenarioMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048ECF0
		template void RegisterMessageKind<proto::EnterVehicleScenarioMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048ED80
		template void RegisterMessageKind<proto::ExitVehicleScenarioMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048EE10
		template void RegisterMessageKind<proto::ObjectGrabbedScenarioMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048EEA0
		template void RegisterMessageKind<proto::ObjectDroppedScenarioMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048EF30
		template void RegisterMessageKind<proto::ObjectThrownScenarioMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048EFC0
		template void RegisterMessageKind<proto::MotionStateScenarioMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048F050
		template void RegisterMessageKind<proto::SupportingSurfaceChangedScenarioMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048F0E0
		template void RegisterMessageKind<proto::CollectibleSpawnedScenarioMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048F170
		template void RegisterMessageKind<proto::CollectibleCollectedScenarioMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048F200
		template void RegisterMessageKind<proto::CollectibleEndOfLifeScenarioMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048F290
		template void RegisterMessageKind<proto::WOINodeStateScenarioMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048F320
		template void RegisterMessageKind<proto::WOINodeFMVPlayedScenarioMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048F3B0
		template void RegisterMessageKind<proto::PatrolDestroyedScenarioMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048F440
		template void RegisterMessageKind<proto::StrikeTeamDestroyedScenarioMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048F4D0
		template void RegisterMessageKind<proto::StrikeTeamEvadedScenarioMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048F560
		template void RegisterMessageKind<proto::StrikeTeamInboundScenarioMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048F5F0
		template void RegisterMessageKind<proto::BaseOrHiveDestroyedScenarioMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048F680
		template void RegisterMessageKind<proto::BaseOrHiveScenarioMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048FA70
		template void RegisterMessageKind<proto::NISDoneScenarioMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048FB00
		template void RegisterMessageKind<proto::WOITargetSpawnedScenarioMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048FB90
		template void RegisterMessageKind<proto::UnlockableAcquiredScenarioMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048FC20
		template void RegisterMessageKind<proto::UnlockableIncrementedPurchaseTypeScenarioMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048DA60
		template void RegisterMessageKind<proto::DisguiseChangedMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048DDC0
		template void RegisterMessageKind<proto::ObjectDeadMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048DE50
		template void RegisterMessageKind<proto::ObjectZeroHealthMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048DEE0
		template void RegisterMessageKind<proto::ObjectOffscreenDespawnMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048F710
		template void RegisterMessageKind<proto::AboutToSaveGameScenarioMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048F7A0
		template void RegisterMessageKind<proto::AboutToSaveCheckpointScenarioMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048F830
		template void RegisterMessageKind<proto::JustLoadedCheckpointScenarioMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048F8C0
		template void RegisterMessageKind<proto::AboutToLoadCheckpointScenarioMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048F950
		template void RegisterMessageKind<proto::FreeRoamEventScenarioMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048F9E0
		template void RegisterMessageKind<proto::FramerCamEventScenarioMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048D9D0
		template void RegisterMessageKind<proto::DestinationReachedMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048E090
		template void RegisterMessageKind<proto::StateMachineStateChangedMessage>(int, const char*);
		// FUNCTION: ENGINE 0x1048EBD0
		template void RegisterMessageKind<proto::SquadSpawnedScenarioMessage>(int, const char*);
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10487DE0
// FUNCTION: ENGINE 0x10487E20
// FUNCTION: ENGINE 0x10487E70
// FUNCTION: ENGINE 0x10487FC0
// FUNCTION: ENGINE 0x10488F20
// FUNCTION: ENGINE 0x1048C840
// FUNCTION: ENGINE 0x104901D0
// FUNCTION: ENGINE 0x10490230
// FUNCTION: ENGINE 0x10490330
// FUNCTION: ENGINE 0x10490430
// FUNCTION: ENGINE 0x10490580
// FUNCTION: ENGINE 0x104905E0
// FUNCTION: ENGINE 0x10490640
// FUNCTION: ENGINE 0x104906B0
// FUNCTION: ENGINE 0x104906F0
// FUNCTION: ENGINE 0x10490760
// FUNCTION: ENGINE 0x104907C0
// FUNCTION: ENGINE 0x10490820
// FUNCTION: ENGINE 0x10490880
// FUNCTION: ENGINE 0x104908E0
// FUNCTION: ENGINE 0x10490940
// FUNCTION: ENGINE 0x104909A0
// FUNCTION: ENGINE 0x10490A00
// FUNCTION: ENGINE 0x10490A60
// FUNCTION: ENGINE 0x10490AC0
// FUNCTION: ENGINE 0x10490B20
// FUNCTION: ENGINE 0x10490B80
// FUNCTION: ENGINE 0x10490BE0
// FUNCTION: ENGINE 0x10490C40
// FUNCTION: ENGINE 0x10490CA0
// FUNCTION: ENGINE 0x10490D00
// FUNCTION: ENGINE 0x10490DD0
// FUNCTION: ENGINE 0x10490E10
// FUNCTION: ENGINE 0x10490E80
// FUNCTION: ENGINE 0x10490EC0
// FUNCTION: ENGINE 0x10490F20
// FUNCTION: ENGINE 0x10490F60
// FUNCTION: ENGINE 0x10490FD0
// FUNCTION: ENGINE 0x10491010
// FUNCTION: ENGINE 0x10491070
// FUNCTION: ENGINE 0x104910B0
// FUNCTION: ENGINE 0x10491110
// FUNCTION: ENGINE 0x10491150
// FUNCTION: ENGINE 0x104911B0
// FUNCTION: ENGINE 0x10491260
// FUNCTION: ENGINE 0x10491370
// FUNCTION: ENGINE 0x104913D0
// FUNCTION: ENGINE 0x10491440
// FUNCTION: ENGINE 0x104914A0
// FUNCTION: ENGINE 0x10491510
// FUNCTION: ENGINE 0x10491580
// FUNCTION: ENGINE 0x104915E0
// FUNCTION: ENGINE 0x10491650
// FUNCTION: ENGINE 0x104916C0
// FUNCTION: ENGINE 0x10491740
// FUNCTION: ENGINE 0x104917C0
// FUNCTION: ENGINE 0x10491800
// FUNCTION: ENGINE 0x10491880
// FUNCTION: ENGINE 0x104918C0
// FUNCTION: ENGINE 0x10491930
// FUNCTION: ENGINE 0x10491970
// FUNCTION: ENGINE 0x104919E0
// FUNCTION: ENGINE 0x10491A20
// FUNCTION: ENGINE 0x10491A90
// FUNCTION: ENGINE 0x10491AF0
// FUNCTION: ENGINE 0x10491B50
// FUNCTION: ENGINE 0x10491BB0
// FUNCTION: ENGINE 0x10491C20
// FUNCTION: ENGINE 0x10491EC0
// FUNCTION: ENGINE 0x10491F80
// FUNCTION: ENGINE 0x10491FF0
// FUNCTION: ENGINE 0x10492030
// FUNCTION: ENGINE 0x104920A0
// FUNCTION: ENGINE 0x104920E0
// FUNCTION: ENGINE 0x10492160
// FUNCTION: ENGINE 0x104921A0
// FUNCTION: ENGINE 0x10492210
// FUNCTION: ENGINE 0x10492250
// FUNCTION: ENGINE 0x104922C0
// FUNCTION: ENGINE 0x10492300
// FUNCTION: ENGINE 0x104938E0
// FUNCTION: ENGINE 0x10493920
// FUNCTION: ENGINE 0x10495190
// FUNCTION: ENGINE 0x10495230
// FUNCTION: ENGINE 0x104952B0
// FUNCTION: ENGINE 0x1048B890
// FUNCTION: ENGINE 0x1048B8D0
// FUNCTION: ENGINE 0x1048B950
// FUNCTION: ENGINE 0x1048BA90
// FUNCTION: ENGINE 0x1048BAD0
// FUNCTION: ENGINE 0x1048BB10
// FUNCTION: ENGINE 0x1048BB50
// FUNCTION: ENGINE 0x1048BBD0
// FUNCTION: ENGINE 0x1048BC10
// FUNCTION: ENGINE 0x1048BC50
// FUNCTION: ENGINE 0x1048BCD0
// FUNCTION: ENGINE 0x1048BD10
// FUNCTION: ENGINE 0x1048BD50
// FUNCTION: ENGINE 0x1048BD90
// FUNCTION: ENGINE 0x1048BDD0
// FUNCTION: ENGINE 0x1048BE10
// FUNCTION: ENGINE 0x1048BE50
// FUNCTION: ENGINE 0x1048BE90
// FUNCTION: ENGINE 0x1048BED0
// FUNCTION: ENGINE 0x1048BF10
// FUNCTION: ENGINE 0x1048BF50
// FUNCTION: ENGINE 0x1048BF90
// FUNCTION: ENGINE 0x1048BFD0
// FUNCTION: ENGINE 0x1048C010
// FUNCTION: ENGINE 0x1048C050
// FUNCTION: ENGINE 0x1048C090
// FUNCTION: ENGINE 0x1048C0D0
// FUNCTION: ENGINE 0x1048C110
// FUNCTION: ENGINE 0x1048C150
// FUNCTION: ENGINE 0x1048C190
// FUNCTION: ENGINE 0x1048C1D0
// FUNCTION: ENGINE 0x1048C210
// FUNCTION: ENGINE 0x1048C250
// FUNCTION: ENGINE 0x1048C290
// FUNCTION: ENGINE 0x1048C2D0
// FUNCTION: ENGINE 0x1048C310
// FUNCTION: ENGINE 0x1048C350
// FUNCTION: ENGINE 0x1048C390
// FUNCTION: ENGINE 0x1048C3D0
// FUNCTION: ENGINE 0x1048C410
// FUNCTION: ENGINE 0x1048C450
// FUNCTION: ENGINE 0x1048C490
// FUNCTION: ENGINE 0x1048C4D0
// FUNCTION: ENGINE 0x1048C510
// FUNCTION: ENGINE 0x1048C550
// FUNCTION: ENGINE 0x1048C710
// FUNCTION: ENGINE 0x1048C750
// FUNCTION: ENGINE 0x1048C790
// FUNCTION: ENGINE 0x1048C7D0
// FUNCTION: ENGINE 0x1048B910
// FUNCTION: ENGINE 0x1048B990
// FUNCTION: ENGINE 0x1048B9D0
// FUNCTION: ENGINE 0x1048BA10
// FUNCTION: ENGINE 0x104902C0
// FUNCTION: ENGINE 0x104903B0
// FUNCTION: ENGINE 0x1048C590
// FUNCTION: ENGINE 0x1048C5D0
// FUNCTION: ENGINE 0x1048C610
// FUNCTION: ENGINE 0x1048C650
// FUNCTION: ENGINE 0x1048C690
// FUNCTION: ENGINE 0x1048C6D0
// FUNCTION: ENGINE 0x10491CA0
// FUNCTION: ENGINE 0x10491D00
// FUNCTION: ENGINE 0x10491D60
// FUNCTION: ENGINE 0x10491DC0
// FUNCTION: ENGINE 0x10491E20
// FUNCTION: ENGINE 0x10491F00
// FUNCTION: ENGINE 0x1048BA50
// FUNCTION: ENGINE 0x1048BB90
// FUNCTION: ENGINE 0x1048BC90
// FUNCTION: ENGINE 0x10490470
// FUNCTION: ENGINE 0x10490D60
// FUNCTION: ENGINE 0x104911F0
