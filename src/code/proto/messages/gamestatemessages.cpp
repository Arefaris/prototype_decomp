#include "code/proto/messages/gamestatemessages.h"
#include "code/engine/luaenvironmentmessage.h"
#include "code/proto/scenariomessages.h"

// A function that constructs each message with the expansion of inline functions off: the compiler keeps the out-of-line
// copy of the constructor and of the destructor the engine has too
#pragma inline_depth(0)
namespace
{
	void EmitGetLuaEnvironmentMessage()
	{
		engine::GetLuaEnvironmentMessage message;
	}

	void EmitScenarioBlockMessagesMessage()
	{
		engine::ScenarioBlockMessagesMessage message(false, false);
	}

	void EmitAboutToSaveGameScenarioMessage()
	{
		proto::AboutToSaveGameScenarioMessage message;
	}

	void EmitAboutToSaveCheckpointScenarioMessage()
	{
		proto::AboutToSaveCheckpointScenarioMessage message;
	}

	void EmitJustLoadedCheckpointScenarioMessage()
	{
		proto::JustLoadedCheckpointScenarioMessage message;
	}

	void EmitAboutToLoadCheckpointScenarioMessage()
	{
		proto::AboutToLoadCheckpointScenarioMessage message;
	}

	void EmitStateMachineGetFirstChildMessage()
	{
		proto::StateMachineGetFirstChildMessage message;
	}

	void EmitStateMachineGetFirstSiblingMessage()
	{
		proto::StateMachineGetFirstSiblingMessage message;
	}

	void EmitStateMachineGetParentMessage()
	{
		proto::StateMachineGetParentMessage message;
	}

	void EmitStateMachineSerializeMessage()
	{
		proto::StateMachineSerializeMessage message(0);
	}

	void EmitStateMachineUnserializeMessage()
	{
		proto::StateMachineUnserializeMessage message(0);
	}

	void EmitGetNameSpawnMessage()
	{
		proto::GetNameSpawnMessage message;
	}

	void EmitEncounterFinishedSpawnMessage()
	{
		proto::EncounterFinishedSpawnMessage message;
	}

	void EmitGetTypeSpawnMessage()
	{
		proto::GetTypeSpawnMessage message;
	}

	void EmitGetSpawnRadiusSpawnMessage()
	{
		proto::GetSpawnRadiusSpawnMessage message;
	}

	void EmitSetBlockUpdatesSpawnerMessage()
	{
		proto::SetBlockUpdatesSpawnerMessage message(false);
	}

	void EmitCheckpointMessage()
	{
		proto::CheckpointMessage message(0);
	}

	void EmitSerializeCharacterCheckpointMessage()
	{
		proto::SerializeCharacterCheckpointMessage message(0);
	}

	void EmitUnserializeCharacterCheckpointMessage()
	{
		proto::UnserializeCharacterCheckpointMessage message(0);
	}

	void EmitInfoForCheckpointAIMsg()
	{
		proto::InfoForCheckpointAIMsg message;
	}

	void EmitBlockStreamerMessage()
	{
		engine::BlockStreamerMessage message(false);
	}
}
#pragma inline_depth()

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1047F030
// FUNCTION: ENGINE 0x1047F060
// FUNCTION: ENGINE 0x1047F070
// FUNCTION: ENGINE 0x1047F0B0
// FUNCTION: ENGINE 0x1047F150
// FUNCTION: ENGINE 0x1047F170
// FUNCTION: ENGINE 0x1047F180
// FUNCTION: ENGINE 0x1047F1A0
// FUNCTION: ENGINE 0x1047F1B0
// FUNCTION: ENGINE 0x1047F1D0
// FUNCTION: ENGINE 0x1047F1E0
// FUNCTION: ENGINE 0x1047F200
// FUNCTION: ENGINE 0x1047F210
// FUNCTION: ENGINE 0x1047F250
// FUNCTION: ENGINE 0x1047F260
// FUNCTION: ENGINE 0x1047F2A0
// FUNCTION: ENGINE 0x1047F2B0
// FUNCTION: ENGINE 0x1047F2F0
// FUNCTION: ENGINE 0x1047F300
// FUNCTION: ENGINE 0x1047F330
// FUNCTION: ENGINE 0x1047F340
// FUNCTION: ENGINE 0x1047F370
// FUNCTION: ENGINE 0x1047F380
// FUNCTION: ENGINE 0x1047F3B0
// FUNCTION: ENGINE 0x1047F3C0
// FUNCTION: ENGINE 0x1047F3F0
// FUNCTION: ENGINE 0x1047F400
// FUNCTION: ENGINE 0x1047F430
// FUNCTION: ENGINE 0x1047F440
// FUNCTION: ENGINE 0x1047F470
// FUNCTION: ENGINE 0x1047F480
// FUNCTION: ENGINE 0x1047F4B0
// FUNCTION: ENGINE 0x1047F4C0
// FUNCTION: ENGINE 0x1047F4F0
// FUNCTION: ENGINE 0x1047F500
// FUNCTION: ENGINE 0x1047F530
// FUNCTION: ENGINE 0x1047F540
// FUNCTION: ENGINE 0x1047F570
// FUNCTION: ENGINE 0x1047F580
// FUNCTION: ENGINE 0x1047F5B0
// FUNCTION: ENGINE 0x1047F5F0
// FUNCTION: ENGINE 0x1047F620
