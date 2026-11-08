#include "code/proto/messages/statemachinemessages.h"
#include "code/proto/scenariomessages.h"

namespace engine
{
	// FUNCTION: ENGINE 0x10487DD0
	ScenarioMessage* ManuallyPlayBranchMessage::Clone(void* memory, int unused)
	{
		return 0;
	}
}

// A function that constructs each message with the expansion of inline functions off: the compiler keeps the out-of-line
// copy of the constructor and of the destructor the engine has too
#pragma inline_depth(0)
namespace
{
	void EmitNullMessage()
	{
		engine::NullMessage message;
	}

	void EmitStateMachineStateChangedMessage()
	{
		proto::StateMachineStateChangedMessage message((engine::GameObjectHandle()));
	}

	void EmitManuallyPlayBranchMessage()
	{
		engine::ManuallyPlayBranchMessage message;
	}

	void EmitGetScenarioRootMessage()
	{
		engine::GetScenarioRootMessage message;
	}

	void EmitStateMachineSetFirstChildMessage()
	{
		proto::StateMachineSetFirstChildMessage message((engine::HandleBase()));
	}

	void EmitStateMachineSetFirstSiblingMessage()
	{
		proto::StateMachineSetFirstSiblingMessage message((engine::HandleBase()));
		proto::StateMachineSetFirstSiblingMessage other;
	}

	void EmitStateMachineGetLastTransitionMessage()
	{
		proto::StateMachineGetLastTransitionMessage message;
	}

	void EmitStateMachineSetInfoMessageProperties()
	{
		proto::StateMachineSetInfoMessageProperties message;
	}

	void EmitStateMachinePropagateMessage()
	{
		proto::StateMachinePropagateMessage message(0);
	}

	void EmitStateMachineSetGONameMessage()
	{
		proto::StateMachineSetGONameMessage message;
	}

	void EmitSetLoadingFromCheckpointMessage()
	{
		proto::SetLoadingFromCheckpointMessage message;
	}

	void EmitGetPublicLuaEnvironmentMessage()
	{
		proto::GetPublicLuaEnvironmentMessage message;
	}

	void EmitStateMachineHardStopMessage()
	{
		proto::StateMachineHardStopMessage message;
	}
}
#pragma inline_depth()

// Kept copies (inline members and template instances of this unit):
// FUNCTION: ENGINE 0x10495170
// FUNCTION: ENGINE 0x10487DA0
// FUNCTION: ENGINE 0x10487DF0
// FUNCTION: ENGINE 0x10495200
// FUNCTION: ENGINE 0x10495240
// FUNCTION: ENGINE 0x10495270
// FUNCTION: ENGINE 0x10493990
// FUNCTION: ENGINE 0x104939C0
// FUNCTION: ENGINE 0x104938B0
// FUNCTION: ENGINE 0x10487E40
// FUNCTION: ENGINE 0x104938F0
// FUNCTION: ENGINE 0x10488EF0
// FUNCTION: ENGINE 0x10493E00
// FUNCTION: ENGINE 0x10493890
// FUNCTION: ENGINE 0x10487F80
// FUNCTION: ENGINE 0x104952C0
