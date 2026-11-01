// The messages of the ai fight items' conditions and actions that no other header declares. Like aicodemessages.h: the RTTI names
// are the engine's, the constructors are inline there (expanded in every user), member names and argument lists are guesses.
#ifndef PROTO_FIGHTITEMS_AI_AIMESSAGES_H
#define PROTO_FIGHTITEMS_AI_AIMESSAGES_H

#include "code/proto/fightitems/ai/aicodemessages.h"
#include "code/proto/fightitems/ai/aicodecommon.h"

namespace proto
{
	// RTTI: proto::GetFixedDestinationMessage: the object answers whether it has a fixed destination
	struct GetFixedDestinationMessage : public MovementMessage
	{
		GetFixedDestinationMessage() : MovementMessage(0x16), destination(0)
		{
		}
		virtual ~GetFixedDestinationMessage()
		{
		}

		int destination;  // +0xC
	};

	// RTTI: proto::GetFixedAreaDestinationMessage: the object answers whether it has a fixed area destination
	struct GetFixedAreaDestinationMessage : public MovementMessage
	{
		GetFixedAreaDestinationMessage() : MovementMessage(0x19), destination(0)
		{
		}
		virtual ~GetFixedAreaDestinationMessage()
		{
		}

		int destination;  // +0xC
	};

	// RTTI: proto::GetEnabledAIMsg: the object answers whether its ai is enabled
	struct GetEnabledAIMsg : public AIMessage
	{
		GetEnabledAIMsg() : AIMessage(3), enabled(false)
		{
		}
		virtual ~GetEnabledAIMsg()
		{
		}

		bool enabled;  // +0xC
	};

	// RTTI: proto::GetTaskAIMsg: the object answers the name of its task
	struct GetTaskAIMsg : public AIMessage
	{
		GetTaskAIMsg() : AIMessage(5), task()
		{
		}
		virtual ~GetTaskAIMsg()
		{
		}

		int unknownC;
		core::Name<core::CaseSensitiveKey> task;  // +0x10
	};

	// RTTI: proto::GetGoalAIMsg: the object answers the name of its goal
	struct GetGoalAIMsg : public AIMessage
	{
		GetGoalAIMsg() : AIMessage(7), goal()
		{
		}
		virtual ~GetGoalAIMsg()
		{
		}

		int unknownC;
		core::Name<core::CaseSensitiveKey> goal;  // +0x10
	};

	// RTTI: proto::DisguiseMessage: the base of the messages about the disguise of an object (message type 0x2A)
	struct DisguiseMessage : public engine::IntrusiveMessage
	{
		explicit DisguiseMessage(short newId) : engine::IntrusiveMessage(0x2a, newId)
		{
		}
		virtual ~DisguiseMessage()
		{
		}
	};

	// RTTI: proto::GetAlertedDisguiseMsg: the object answers how alerted its disguise is
	struct GetAlertedDisguiseMsg : public DisguiseMessage
	{
		GetAlertedDisguiseMsg() : DisguiseMessage(0xd), unknownC(false), alert(0.0f)
		{
		}
		virtual ~GetAlertedDisguiseMsg()
		{
		}

		bool unknownC;
		float alert;  // +0x10
	};

	// RTTI: proto::GetTargetMessage: the object answers its target
	class GetTargetMessage : public TargetMessage
	{
	public:
		GetTargetMessage() : TargetMessage(0), target(), unknown10(0.0f)
		{
		}
		virtual ~GetTargetMessage()
		{
		}

		engine::GameObjectHandle target;  // +0xC
		float unknown10;
	};
}

#endif
