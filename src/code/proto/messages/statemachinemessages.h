// More messages to the scenario's state machines (type 0x2D, names from the RTTI; ids, members and constructor
// arguments from the engine's constructors, member names are guesses). The first ones are declared with the other
// state machine messages in gamestatemessages.h. The constructors are inline; the engine keeps one out-of-line copy of
// some of them in the unit 0x10487DA0 - 0x10495270, which statemachinemessages.cpp emits.
#ifndef PROTO_MESSAGES_STATEMACHINEMESSAGES_H
#define PROTO_MESSAGES_STATEMACHINEMESSAGES_H

#include "code/container/string.h"
#include "code/core/name.h"
#include "code/engine/fight/branch.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/engine/message.h"
#include "code/engine/scenariomessage.h"
#include "code/proto/messages/gamestatemessages.h"
#include "code/proto/messages/statemessages.h"

namespace engine
{
	// RTTI: engine::ManuallyPlayBranchMessage: asks the scenario tree to run a branch at once (type 0xD, id 7; the
	// message is never copied into the queue)
	struct ManuallyPlayBranchMessage : public ScenarioMessage
	{
		ManuallyPlayBranchMessage() : ScenarioMessage(7), branch(0), scriptOwner(0), result(0)
		{
		}
		virtual ~ManuallyPlayBranchMessage()
		{
		}
		// 0x10487DD0: does not copy
		virtual ScenarioMessage* Clone(void* memory, int unused);

		fight::Branch* branch;  // +0x1C
		void* scriptOwner;  // +0x20
		int result;  // +0x24
	};

	// RTTI: engine::GetScenarioRootMessage (a NonintrusiveMessage of type 0xD, id 8): the scenario tree answers its root
	struct GetScenarioRootMessage : public NonintrusiveMessage
	{
		GetScenarioRootMessage() : NonintrusiveMessage(0xd, 8), root(0)
		{
		}
		virtual ~GetScenarioRootMessage()
		{
		}

		fight::Branch* root;  // +0xC
	};
}

namespace proto
{
	// RTTI: proto::StateMachineGetStateMessage: the state machine answers the branch it is in
	struct StateMachineGetStateMessage : public StateMachineMsg
	{
		StateMachineGetStateMessage() : StateMachineMsg(0), state(0)
		{
		}
		virtual ~StateMachineGetStateMessage()
		{
		}

		fight::Branch* state;  // +0xC
	};

	// RTTI: proto::StateMachineSetStateMessage: puts the state machine into a state (and a state to go to next)
	struct StateMachineSetStateMessage : public StateMachineMsg
	{
		StateMachineSetStateMessage() : StateMachineMsg(1)
		{
			nextState = 0;
			state = 0;
		}
		virtual ~StateMachineSetStateMessage()
		{
		}

		fight::Branch* state;  // +0xC
		fight::Branch* nextState;  // +0x10
	};

	// RTTI: proto::StateMachineSetFirstChildMessage: tells the state machine its first child
	struct StateMachineSetFirstChildMessage : public StateMachineMsg
	{
		explicit StateMachineSetFirstChildMessage(engine::HandleBase newChild) : StateMachineMsg(3), child(newChild)
		{
		}
		virtual ~StateMachineSetFirstChildMessage()
		{
		}

		engine::HandleBase child;  // +0xC
	};

	// RTTI: proto::StateMachineSetFirstSiblingMessage: tells the state machine its first sibling
	struct StateMachineSetFirstSiblingMessage : public StateMachineMsg
	{
		StateMachineSetFirstSiblingMessage() : StateMachineMsg(5)
		{
		}
		explicit StateMachineSetFirstSiblingMessage(engine::HandleBase newSibling) : StateMachineMsg(5), sibling(newSibling)
		{
		}
		virtual ~StateMachineSetFirstSiblingMessage()
		{
		}

		engine::HandleBase sibling;  // +0xC
	};

	// RTTI: proto::StateMachineGetLastTransitionMessage: the state machine answers the transition it made last
	struct StateMachineGetLastTransitionMessage : public StateMachineMsg
	{
		StateMachineGetLastTransitionMessage() : StateMachineMsg(9), transition(0)
		{
		}

		fight::BranchWatch transition;  // +0xC
	};

	// RTTI: proto::StateMachineSetInfoMessageProperties: sets the info text of the state machine
	struct StateMachineSetInfoMessageProperties : public StateMachineMsg
	{
		StateMachineSetInfoMessageProperties() : StateMachineMsg(0xc), enabled(false), text("")
		{
		}
		virtual ~StateMachineSetInfoMessageProperties()
		{
		}

		bool enabled;  // +0xC
		container::StringC<128> text;  // +0x10
	};

	// RTTI: proto::StateMachinePropagateMessage: the state machine hands a message on to its children
	struct StateMachinePropagateMessage : public StateMachineMsg
	{
		explicit StateMachinePropagateMessage(engine::Message* newMessage) : StateMachineMsg(0xd), message(newMessage)
		{
		}
		virtual ~StateMachinePropagateMessage()
		{
		}

		engine::Message* message;  // +0xC
	};

	// RTTI: proto::StateMachineSetGONameMessage: sets the name of the state machine's game object
	struct StateMachineSetGONameMessage : public StateMachineMsg
	{
		StateMachineSetGONameMessage() : StateMachineMsg(0x11)
		{
		}
		virtual ~StateMachineSetGONameMessage()
		{
		}

		int unknownC;
		core::Name<core::CaseSensitiveKey> name;  // +0x10
	};

	// RTTI: proto::SetLoadingFromCheckpointMessage: the state machine is told that a checkpoint is being loaded
	struct SetLoadingFromCheckpointMessage : public StateMachineMsg
	{
		SetLoadingFromCheckpointMessage() : StateMachineMsg(0x12)
		{
		}
		virtual ~SetLoadingFromCheckpointMessage()
		{
		}
	};

	// RTTI: proto::GetPublicLuaEnvironmentMessage: the state machine answers the reference of its public Lua table
	struct GetPublicLuaEnvironmentMessage : public StateMachineMsg
	{
		GetPublicLuaEnvironmentMessage() : StateMachineMsg(0x14), reference(0)
		{
		}
		virtual ~GetPublicLuaEnvironmentMessage()
		{
		}

		int reference;  // +0xC
	};

	// RTTI: proto::StateMachineHardStopMessage: stops the state machine at once
	struct StateMachineHardStopMessage : public StateMachineMsg
	{
		StateMachineHardStopMessage() : StateMachineMsg(0x15)
		{
		}
		virtual ~StateMachineHardStopMessage()
		{
		}
	};

	// RTTI: proto::SetIsInConstructionSquadMsg: tells a squad that it is (or is no longer) being put together
	struct SetIsInConstructionSquadMsg : public SquadMessage
	{
		explicit SetIsInConstructionSquadMsg(bool newInConstruction) : SquadMessage(0x14), inConstruction(newInConstruction)
		{
		}
		virtual ~SetIsInConstructionSquadMsg()
		{
		}

		bool inConstruction;  // +0xC
	};
}

#endif
