// The messages about the state of the game and of its objects (names from the RTTI; type, id, member layout and
// constructor arguments from the engine's constructors, member names are guesses): the state machine messages (type
// 0x2D), the spawner messages (type 0x29, the base is declared with the fight items' messages), the checkpoint messages
// (type 0x39, the base is declared with the fight variables), the block messages of the scenario and the block
// streamer message. The constructors are inline (expanded in every user); the engine keeps one out-of-line copy of each
// in the unit 0x1047F030 - 0x1047F640, which gamestatemessages.cpp emits.
#ifndef PROTO_MESSAGES_GAMESTATEMESSAGES_H
#define PROTO_MESSAGES_GAMESTATEMESSAGES_H

#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/engine/message.h"
#include "code/proto/behaviours/fightvariablesbehaviour.h"
#include "code/proto/fightitems/ai/aicodemessages.h"

namespace engine
{
	// RTTI: engine::ScenarioBlockMessagesMessage: blocks the messages of the scenario (or lets them through again)
	struct ScenarioBlockMessagesMessage : public IntrusiveMessage
	{
		ScenarioBlockMessagesMessage(bool newBlock, bool newFlag) : IntrusiveMessage(0xd, 0x12), block(newBlock), flag(newFlag)
		{
		}
		virtual ~ScenarioBlockMessagesMessage()
		{
		}

		bool block;  // +0xC
		bool flag;  // +0xD
	};

	// RTTI: engine::BlockStreamerMessage: blocks or releases the streamer
	struct BlockStreamerMessage : public IntrusiveMessage
	{
		explicit BlockStreamerMessage(bool newBlock) : IntrusiveMessage(0x18, 0xc), block(newBlock)
		{
		}
		virtual ~BlockStreamerMessage()
		{
		}

		bool block;  // +0xC
	};
}

namespace proto
{
	// RTTI: proto::StateMachineMsg: the base of the messages to the state machines (message type 0x2D)
	struct StateMachineMsg : public engine::IntrusiveMessage
	{
		explicit StateMachineMsg(short newId) : engine::IntrusiveMessage(0x2d, newId)
		{
		}
		virtual ~StateMachineMsg()
		{
		}
	};

	// RTTI: proto::StateMachineGetFirstChildMessage: the state machine answers its first child
	struct StateMachineGetFirstChildMessage : public StateMachineMsg
	{
		StateMachineGetFirstChildMessage() : StateMachineMsg(2)
		{
		}
		virtual ~StateMachineGetFirstChildMessage()
		{
		}

		engine::HandleBase child;  // +0xC
	};

	// RTTI: proto::StateMachineGetFirstSiblingMessage: the state machine answers its first sibling
	struct StateMachineGetFirstSiblingMessage : public StateMachineMsg
	{
		StateMachineGetFirstSiblingMessage() : StateMachineMsg(4)
		{
		}
		virtual ~StateMachineGetFirstSiblingMessage()
		{
		}

		engine::HandleBase sibling;  // +0xC
	};

	// RTTI: proto::StateMachineGetParentMessage: the state machine answers its parent
	struct StateMachineGetParentMessage : public StateMachineMsg
	{
		StateMachineGetParentMessage() : StateMachineMsg(7), unknown10(0)
		{
		}
		virtual ~StateMachineGetParentMessage()
		{
		}

		engine::HandleBase parent;  // +0xC
		int unknown10;
	};

	// RTTI: proto::StateMachineSerializeMessage: the state machine writes its state to the stream
	struct StateMachineSerializeMessage : public StateMachineMsg
	{
		explicit StateMachineSerializeMessage(void* newStream) : StateMachineMsg(0xe), stream(newStream)
		{
		}
		virtual ~StateMachineSerializeMessage()
		{
		}

		void* stream;  // +0xC
	};

	// RTTI: proto::StateMachineUnserializeMessage: the state machine reads its state from the stream
	struct StateMachineUnserializeMessage : public StateMachineMsg
	{
		explicit StateMachineUnserializeMessage(void* newStream) : StateMachineMsg(0xf), stream(newStream)
		{
		}
		virtual ~StateMachineUnserializeMessage()
		{
		}

		void* stream;  // +0xC
	};

	// RTTI: proto::GetNameSpawnMessage: the spawner answers its name
	struct GetNameSpawnMessage : public SpawnMessage
	{
		GetNameSpawnMessage() : SpawnMessage(0xf), name(0)
		{
		}
		virtual ~GetNameSpawnMessage()
		{
		}

		int name;  // +0xC
	};

	// RTTI: proto::EncounterFinishedSpawnMessage: the spawner answers whether its encounter is finished
	struct EncounterFinishedSpawnMessage : public SpawnMessage
	{
		EncounterFinishedSpawnMessage() : SpawnMessage(0x13), finished(false)
		{
		}
		virtual ~EncounterFinishedSpawnMessage()
		{
		}

		bool finished;  // +0xC
	};

	// RTTI: proto::GetTypeSpawnMessage: the spawner answers its type
	struct GetTypeSpawnMessage : public SpawnMessage
	{
		GetTypeSpawnMessage() : SpawnMessage(0x11), spawnerType(0)
		{
		}
		virtual ~GetTypeSpawnMessage()
		{
		}

		int spawnerType;  // +0xC
	};

	// RTTI: proto::GetSpawnRadiusSpawnMessage: the spawner answers its radius
	struct GetSpawnRadiusSpawnMessage : public SpawnMessage
	{
		GetSpawnRadiusSpawnMessage() : SpawnMessage(0x14), radius(0.0f)
		{
		}
		virtual ~GetSpawnRadiusSpawnMessage()
		{
		}

		float radius;  // +0xC
	};

	// RTTI: proto::SetBlockUpdatesSpawnerMessage: the spawner blocks (or allows) its updates
	struct SetBlockUpdatesSpawnerMessage : public SpawnMessage
	{
		explicit SetBlockUpdatesSpawnerMessage(bool newBlock) : SpawnMessage(0x18), block(newBlock)
		{
		}
		virtual ~SetBlockUpdatesSpawnerMessage()
		{
		}

		bool block;  // +0xC
	};

	// RTTI: proto::InfoForCheckpointAIMsg: the AI answers what the checkpoint needs of it
	struct InfoForCheckpointAIMsg : public CheckpointMessage
	{
		InfoForCheckpointAIMsg() : CheckpointMessage(2), first(false), second(false), third(false)
		{
		}
		virtual ~InfoForCheckpointAIMsg()
		{
		}

		bool first;  // +0xC
		bool second;  // +0xD
		bool third;  // +0xE
	};
}

#endif
