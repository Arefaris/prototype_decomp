// More messages the actions of the ai fight items send (RTTI names from the engine; type, id and members from the engine's
// constructors, member names are guesses). The constructors are inline, expanded in every user.
#ifndef PROTO_FIGHTITEMS_AI_AIACTIONMESSAGES_H
#define PROTO_FIGHTITEMS_AI_AIACTIONMESSAGES_H

#include "code/proto/fightitems/ai/aimessages.h"

namespace fight
{
	class Action;
}

namespace proto
{
	// RTTI: proto::ClearFixedDestinationMessage: the object forgets the fixed destination an action gave it
	struct ClearFixedDestinationMessage : public MovementMessage
	{
		explicit ClearFixedDestinationMessage(fight::Action* newSource) : MovementMessage(0x18), source(newSource)
		{
		}
		virtual ~ClearFixedDestinationMessage()
		{
		}

		fight::Action* source;  // +0xC
	};

	// RTTI: proto::SetNPCLODStateAIMsg: the object takes a level of detail state
	struct SetNPCLODStateAIMsg : public LODAIMessage
	{
		explicit SetNPCLODStateAIMsg(int newState) : LODAIMessage(0x13), state(newState)
		{
		}
		virtual ~SetNPCLODStateAIMsg()
		{
		}

		int state;  // +0xC
	};
}

#endif
