// The scenario messages of the proto layer (RTTI names, all derived from engine::ScenarioMessage): the events the
// game raises for the scenario scripts (an object spawned, consumed, damaged, a player seen, ...). Each carries up to
// four object handles and a few fields of its own, writes them into the script's event table (WriteFields) and
// copies itself into caller memory (Clone). The unit (0x10480000 - 0x10493xxx, no assert path) is named
// scenariomessages.cpp here; the names of the members are the keys the script receives.
#ifndef PROTO_SCENARIOMESSAGES_H
#define PROTO_SCENARIOMESSAGES_H

#include "code/engine/scenariomessage.h"

namespace proto
{
	struct ObjectSpawnedMessage : public engine::ScenarioMessage
	{
		ObjectSpawnedMessage() : engine::ScenarioMessage(0x14)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
	};

	struct ObjectConsumedMessage : public engine::ScenarioMessage
	{
		ObjectConsumedMessage() : engine::ScenarioMessage(0x13)
		{
		}
		ObjectConsumedMessage(const ObjectConsumedMessage& other) : engine::ScenarioMessage(other), unknownName20(other.unknownName20), stealth(other.stealth), healthGained(other.healthGained), woiTarget(other.woiTarget)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
		int unknown1C;  // +0x1C
		core::Name<core::CaseSensitiveKey> unknownName20;  // +0x20
		bool stealth;  // +0x28
		float healthGained;  // +0x2C
		bool woiTarget;  // +0x30
	};

	struct ObjectDamagedMessage : public engine::ScenarioMessage
	{
		ObjectDamagedMessage() : engine::ScenarioMessage(0x16)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
		int attackType;  // +0x1C
		float damageTaken;  // +0x20
		float damageGiven;  // +0x24
	};

	struct TargetChangedMessage : public engine::ScenarioMessage
	{
		TargetChangedMessage() : engine::ScenarioMessage(0x1B)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
	};

	struct FixedTargetDeadMessage : public engine::ScenarioMessage
	{
		FixedTargetDeadMessage() : engine::ScenarioMessage(0x1C)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
	};

	struct HintCancelledMessage : public engine::ScenarioMessage
	{
		HintCancelledMessage() : engine::ScenarioMessage(0x1B)
		{
		}
		HintCancelledMessage(const HintCancelledMessage& other) : engine::ScenarioMessage(other), stringUID(other.stringUID)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
		int unknown1C;  // +0x1C
		core::Name<core::CaseSensitiveKey> stringUID;  // +0x20
	};

	struct HeliLandedStateChangeMessage : public engine::ScenarioMessage
	{
		HeliLandedStateChangeMessage() : engine::ScenarioMessage(0x1E)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
		bool landed;  // +0x1C
	};

	struct EnterAlertScenarioMsg : public engine::ScenarioMessage
	{
		EnterAlertScenarioMsg() : engine::ScenarioMessage(0x1F)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
	};

	struct LeaveAlertScenarioMsg : public engine::ScenarioMessage
	{
		LeaveAlertScenarioMsg() : engine::ScenarioMessage(0x20)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
	};

	struct DisguiseBlownScenarioMsg : public engine::ScenarioMessage
	{
		DisguiseBlownScenarioMsg() : engine::ScenarioMessage(0x22)
		{
		}
		explicit DisguiseBlownScenarioMsg(engine::GameObjectHandle player) : engine::ScenarioMessage(0x22)
		{
			handles[0] = player;
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
	};

	struct DisguiseUnblownScenarioMsg : public engine::ScenarioMessage
	{
		DisguiseUnblownScenarioMsg() : engine::ScenarioMessage(0x23)
		{
		}
		explicit DisguiseUnblownScenarioMsg(engine::GameObjectHandle player) : engine::ScenarioMessage(0x23)
		{
			handles[0] = player;
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
	};

	struct PlayerWatchedScenarioMsg : public engine::ScenarioMessage
	{
		PlayerWatchedScenarioMsg() : engine::ScenarioMessage(0x24)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
	};

	struct PlayerUnwatchedScenarioMsg : public engine::ScenarioMessage
	{
		PlayerUnwatchedScenarioMsg() : engine::ScenarioMessage(0x25)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
	};

	struct BaseEnterAlertScenarioMsg : public engine::ScenarioMessage
	{
		BaseEnterAlertScenarioMsg() : engine::ScenarioMessage(0x26)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
	};

	struct BaseLeaveAlertScenarioMsg : public engine::ScenarioMessage
	{
		BaseLeaveAlertScenarioMsg() : engine::ScenarioMessage(0x27)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
	};

	struct BaseBackToIdleScenarioMsg : public engine::ScenarioMessage
	{
		BaseBackToIdleScenarioMsg() : engine::ScenarioMessage(0x28)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
	};

	struct BaseEnterBeginCombatScenarioMsg : public engine::ScenarioMessage
	{
		BaseEnterBeginCombatScenarioMsg() : engine::ScenarioMessage(0x29)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
	};

	struct DisguiseHUDWhiteScenarioMsg : public engine::ScenarioMessage
	{
		DisguiseHUDWhiteScenarioMsg() : engine::ScenarioMessage(0x2A)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
	};

	struct DisguiseHUDYellowScenarioMsg : public engine::ScenarioMessage
	{
		DisguiseHUDYellowScenarioMsg() : engine::ScenarioMessage(0x2B)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
	};

	struct DisguiseHUDRedScenarioMsg : public engine::ScenarioMessage
	{
		DisguiseHUDRedScenarioMsg() : engine::ScenarioMessage(0x2C)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
	};

	struct DisguiseHUDRedHideScenarioMsg : public engine::ScenarioMessage
	{
		DisguiseHUDRedHideScenarioMsg() : engine::ScenarioMessage(0x2D)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
	};

	struct PlayerEngagedScenarioMsg : public engine::ScenarioMessage
	{
		PlayerEngagedScenarioMsg() : engine::ScenarioMessage(0x2E)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
	};

	struct RadioAttemptScenarioMsg : public engine::ScenarioMessage
	{
		RadioAttemptScenarioMsg() : engine::ScenarioMessage(0x2F)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
	};

	struct DebugStateMachineStateChangedMessage : public engine::ScenarioMessage
	{
		DebugStateMachineStateChangedMessage() : engine::ScenarioMessage(0x0)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
		int unknown1C;  // +0x1C
		int unknown20;  // +0x20
	};

	struct DebugStateMachineStartedMessage : public engine::ScenarioMessage
	{
		DebugStateMachineStartedMessage() : engine::ScenarioMessage(0x0)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
	};

	struct DebugStateMachineStoppedMessage : public engine::ScenarioMessage
	{
		DebugStateMachineStoppedMessage() : engine::ScenarioMessage(0x0)
		{
		}
		DebugStateMachineStoppedMessage(const DebugStateMachineStoppedMessage& other) : engine::ScenarioMessage(other), unknownName20(other.unknownName20)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
		int unknown1C;  // +0x1C
		core::Name<core::CaseSensitiveKey> unknownName20;  // +0x20
	};

	struct SpawnerFinishedScenarioMessage : public engine::ScenarioMessage
	{
		SpawnerFinishedScenarioMessage() : engine::ScenarioMessage(0x35)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
	};

	struct SpawnerAllZeroHealthScenarioMessage : public engine::ScenarioMessage
	{
		SpawnerAllZeroHealthScenarioMessage() : engine::ScenarioMessage(0x36)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
	};

	struct SpawnerAllSpawnedScenarioMessage : public engine::ScenarioMessage
	{
		SpawnerAllSpawnedScenarioMessage() : engine::ScenarioMessage(0x34)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
	};

	struct SquadDisbandedScenarioMessage : public engine::ScenarioMessage
	{
		SquadDisbandedScenarioMessage() : engine::ScenarioMessage(0x38)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
	};

	struct EnterVehicleScenarioMessage : public engine::ScenarioMessage
	{
		EnterVehicleScenarioMessage() : engine::ScenarioMessage(0x39)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
		bool hijackedByPlayer;  // +0x1C
	};

	struct ExitVehicleScenarioMessage : public engine::ScenarioMessage
	{
		ExitVehicleScenarioMessage() : engine::ScenarioMessage(0x3A)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
	};

	struct ObjectGrabbedScenarioMessage : public engine::ScenarioMessage
	{
		ObjectGrabbedScenarioMessage() : engine::ScenarioMessage(0x3B)
		{
		}
		ObjectGrabbedScenarioMessage(const ObjectGrabbedScenarioMessage& other) : engine::ScenarioMessage(other), grabSlot(other.grabSlot)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
		int unknown1C;  // +0x1C
		core::Name<core::CaseSensitiveKey> grabSlot;  // +0x20
	};

	struct ObjectDroppedScenarioMessage : public engine::ScenarioMessage
	{
		ObjectDroppedScenarioMessage() : engine::ScenarioMessage(0x3C)
		{
		}
		ObjectDroppedScenarioMessage(const ObjectDroppedScenarioMessage& other) : engine::ScenarioMessage(other), grabSlot(other.grabSlot)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
		int unknown1C;  // +0x1C
		core::Name<core::CaseSensitiveKey> grabSlot;  // +0x20
	};

	struct ObjectThrownScenarioMessage : public engine::ScenarioMessage
	{
		ObjectThrownScenarioMessage() : engine::ScenarioMessage(0x3D)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
	};

	struct MotionStateScenarioMessage : public engine::ScenarioMessage
	{
		MotionStateScenarioMessage() : engine::ScenarioMessage(0x3E)
		{
		}
		MotionStateScenarioMessage(engine::GameObjectHandle newObject, int newMotionState, int newPrevMotionState) :
			engine::ScenarioMessage(0x3E), motionState(newMotionState), prevMotionState(newPrevMotionState)
		{
			handles[0] = newObject;
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
		int motionState;  // +0x1C
		int prevMotionState;  // +0x20
	};

	struct SupportingSurfaceChangedScenarioMessage : public engine::ScenarioMessage
	{
		SupportingSurfaceChangedScenarioMessage() : engine::ScenarioMessage(0x3F)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
		bool onSurface;  // +0x1C
	};

	struct CollectibleSpawnedScenarioMessage : public engine::ScenarioMessage
	{
		CollectibleSpawnedScenarioMessage() : engine::ScenarioMessage(0x40)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
		int collectibleType;  // +0x1C
		core::Name<core::CaseSensitiveKey> scriptedType;  // +0x20
	};

	struct WOINodeStateScenarioMessage : public engine::ScenarioMessage
	{
		WOINodeStateScenarioMessage() : engine::ScenarioMessage(0x43)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
		int nodeID;  // +0x1C
		int state;  // +0x20
	};

	struct WOINodeFMVPlayedScenarioMessage : public engine::ScenarioMessage
	{
		WOINodeFMVPlayedScenarioMessage() : engine::ScenarioMessage(0x44)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
		int nodeID;  // +0x1C
	};

	struct PatrolDestroyedScenarioMessage : public engine::ScenarioMessage
	{
		PatrolDestroyedScenarioMessage() : engine::ScenarioMessage(0x45)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
		int heightLevel;  // +0x1C
		int numVehicles;  // +0x20
	};

	struct StrikeTeamDestroyedScenarioMessage : public engine::ScenarioMessage
	{
		StrikeTeamDestroyedScenarioMessage() : engine::ScenarioMessage(0x46)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
	};

	struct StrikeTeamEvadedScenarioMessage : public engine::ScenarioMessage
	{
		StrikeTeamEvadedScenarioMessage() : engine::ScenarioMessage(0x47)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
	};

	struct StrikeTeamInboundScenarioMessage : public engine::ScenarioMessage
	{
		StrikeTeamInboundScenarioMessage() : engine::ScenarioMessage(0x48)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
	};

	struct BaseOrHiveDestroyedScenarioMessage : public engine::ScenarioMessage
	{
		BaseOrHiveDestroyedScenarioMessage() : engine::ScenarioMessage(0x49)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
		int cellNumber;  // +0x1C
		bool isHive;  // +0x20
	};

	struct BaseOrHiveScenarioMessage : public engine::ScenarioMessage
	{
		BaseOrHiveScenarioMessage() : engine::ScenarioMessage(0x4A)
		{
		}
		BaseOrHiveScenarioMessage(const BaseOrHiveScenarioMessage& other) : engine::ScenarioMessage(other), cellNumber(other.cellNumber), isHive(other.isHive), action(other.action)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
		int cellNumber;  // +0x1C
		bool isHive;  // +0x20
		int unknown24;  // +0x24
		core::Name<core::CaseSensitiveKey> action;  // +0x28
	};

	struct NISDoneScenarioMessage : public engine::ScenarioMessage
	{
		NISDoneScenarioMessage() : engine::ScenarioMessage(0x51)
		{
		}
		NISDoneScenarioMessage(const NISDoneScenarioMessage& other) : engine::ScenarioMessage(other), NISName(other.NISName)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
		int unknown1C;  // +0x1C
		core::Name<core::CaseSensitiveKey> NISName;  // +0x20
	};

	struct WOITargetSpawnedScenarioMessage : public engine::ScenarioMessage
	{
		WOITargetSpawnedScenarioMessage() : engine::ScenarioMessage(0x52)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
		int WOINodeID;  // +0x1C
	};

	struct WOITargetConsumedScenarioMessage : public engine::ScenarioMessage
	{
		WOITargetConsumedScenarioMessage() : engine::ScenarioMessage(0x53)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
		int NodeCompletedInEpisode;  // +0x1C
		int EpisodeComplete;  // +0x20
		bool WOIComplete;  // +0x24
	};

	struct UnlockableAcquiredScenarioMessage : public engine::ScenarioMessage
	{
		UnlockableAcquiredScenarioMessage() : engine::ScenarioMessage(0x54)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
		int unlockable;  // +0x1C
	};

	struct UnlockableIncrementedPurchaseTypeScenarioMessage : public engine::ScenarioMessage
	{
		UnlockableIncrementedPurchaseTypeScenarioMessage() : engine::ScenarioMessage(0x55)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
		int purchaseType;  // +0x1C
	};

	struct ObjectZeroHealthMessage : public engine::ScenarioMessage
	{
		ObjectZeroHealthMessage(engine::GameObjectHandle object, engine::GameObjectHandle originator, int newAttackType,
			bool newSpawnCollectible) : engine::ScenarioMessage(0x18), attackType(newAttackType),
			spawnCollectible(newSpawnCollectible)
		{
			handles[0] = object;
			handles[1] = originator;
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
		int attackType;  // +0x1C
		bool spawnCollectible;  // +0x20
	};

	struct ObjectOffscreenDespawnMessage : public engine::ScenarioMessage
	{
		explicit ObjectOffscreenDespawnMessage(engine::GameObjectHandle object) : engine::ScenarioMessage(0x19)
		{
			handles[0] = object;
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
	};

	struct DisguiseChangedMessage : public engine::ScenarioMessage
	{
		DisguiseChangedMessage() : engine::ScenarioMessage(0x15)
		{
		}
		DisguiseChangedMessage(const DisguiseChangedMessage& other) : engine::ScenarioMessage(other),
			newFaction(other.newFaction)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
		int unknown1C;  // +0x1C
		core::Name<core::CaseSensitiveKey> newFaction;  // +0x20
	};

	struct ObjectDeadMessage : public engine::ScenarioMessage
	{
		ObjectDeadMessage() : engine::ScenarioMessage(0x17)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
		int attackType;  // +0x1C
		core::Name<core::CaseSensitiveKey> unknownName20;  // +0x20
	};

	struct AboutToSaveGameScenarioMessage : public engine::ScenarioMessage
	{
		AboutToSaveGameScenarioMessage() : engine::ScenarioMessage(0x4B)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual bool WriteEvent();

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
	};

	struct AboutToSaveCheckpointScenarioMessage : public engine::ScenarioMessage
	{
		AboutToSaveCheckpointScenarioMessage() : engine::ScenarioMessage(0x4C)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual bool WriteEvent();

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
	};

	struct JustLoadedCheckpointScenarioMessage : public engine::ScenarioMessage
	{
		JustLoadedCheckpointScenarioMessage() : engine::ScenarioMessage(0x4D)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual bool WriteEvent();

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
	};

	struct AboutToLoadCheckpointScenarioMessage : public engine::ScenarioMessage
	{
		AboutToLoadCheckpointScenarioMessage() : engine::ScenarioMessage(0x4E)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual bool WriteEvent();

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
	};

	struct FreeRoamEventScenarioMessage : public engine::ScenarioMessage
	{
		FreeRoamEventScenarioMessage() : engine::ScenarioMessage(0x4F)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual bool WriteEvent();

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
		int state;  // +0x1C
		core::Name<core::CaseSensitiveKey> eventName;  // +0x20
		core::Name<core::CaseSensitiveKey> className;  // +0x28
		core::Name<core::CaseSensitiveKey> string;  // +0x30
	};

	struct FramerCamEventScenarioMessage : public engine::ScenarioMessage
	{
		FramerCamEventScenarioMessage() : engine::ScenarioMessage(0x50)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual bool WriteEvent();

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
		int type;  // +0x1C
		core::Name<core::CaseSensitiveKey> name;  // +0x20
	};

	struct DestinationReachedMessage : public engine::ScenarioMessage
	{
		DestinationReachedMessage() : engine::ScenarioMessage(0x1A)
		{
		}
		// 0x101F1030 (the ai fight items' unit): the object that arrived, and what it did
		DestinationReachedMessage(engine::GameObjectHandle arrived, const char* newData);
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
		char data[64];  // +0x1C
	};

	struct StateMachineStateChangedMessage : public engine::ScenarioMessage
	{
		StateMachineStateChangedMessage() : engine::ScenarioMessage(0x30)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
		void* newState;  // +0x1C: the state (its name is at +8)
	};

	struct SquadSpawnedScenarioMessage : public engine::ScenarioMessage
	{
		SquadSpawnedScenarioMessage() : engine::ScenarioMessage(0x37)
		{
		}
		virtual engine::ScenarioMessage* Clone(void* memory, int unused);
		virtual void WriteFields(engine::LuaScriptManager* context);

		static engine::ScenarioHandleInfo GetHandleInfo()
		{
			return sHandleInfo;
		}

		static engine::ScenarioHandleInfo sHandleInfo;
		int unknown1C;  // +0x1C
	};

}

#endif
