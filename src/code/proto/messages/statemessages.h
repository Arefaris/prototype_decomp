// Small messages of the character, AI level of detail, squad, state change and perception categories whose vftables
// sit in the unit 0x10DFC25C - 0x10DFC370 (RTTI names). The constructors are inline in every user; the member names
// are guesses from the constructors the engine keeps (0x103B7950 - 0x103B8140).
#ifndef PROTO_MESSAGES_STATEMESSAGES_H
#define PROTO_MESSAGES_STATEMESSAGES_H

#include "code/proto/ai/ambientmanager/ambientmanagermessages.h"
#include "code/proto/fightitems/ai/aicodemessages.h"
#include "code/proto/fightitems/ai/aimessages.h"
#include "code/proto/messages/airequestmessages.h"
#include "code/engine/gameobject/gameobjectmessages.h"

namespace engine
{
	// Asks for the state of the player's control (message type 0x10, id 1)
	struct CharacterQueryPlayerControlStateMessage : public CharacterQueryMessage
	{
		CharacterQueryPlayerControlStateMessage() : CharacterQueryMessage(1), state(0)
		{
		}
		virtual ~CharacterQueryPlayerControlStateMessage()
		{
		}

		int state;  // +0xC
	};

	// Switches the rendering of an object (message type 7, id 0xB)
	struct ActivateRenderingMessage : public IntrusiveMessage
	{
		explicit ActivateRenderingMessage(bool newActive) : IntrusiveMessage(7, 0xb), active(newActive)
		{
		}
		virtual ~ActivateRenderingMessage()
		{
		}

		bool active;  // +0xC
	};
}

namespace proto
{
	// Perception (type 0x25, id 0xF): how suspicious the perception is of an object
	struct GetGameObjectSuspicionPerceptionMessage : public PerceptionMessage
	{
		explicit GetGameObjectSuspicionPerceptionMessage(int newObject) : PerceptionMessage(0xf), object(newObject),
			suspicion(0)
		{
		}
		virtual ~GetGameObjectSuspicionPerceptionMessage()
		{
		}

		int object;  // +0xC
		int suspicion;
	};

	// The level of detail messages (LODAIMessage, type 0x3A)
	struct GetLODStateAIMsg : public LODAIMessage
	{
		GetLODStateAIMsg() : LODAIMessage(0), state(0)
		{
		}
		virtual ~GetLODStateAIMsg()
		{
		}

		int state;  // +0xC
	};

	struct FreezeAIMsg : public LODAIMessage
	{
		FreezeAIMsg() : LODAIMessage(2)
		{
		}
		virtual ~FreezeAIMsg()
		{
		}
	};

	struct InstantFreezeAIMsg : public LODAIMessage
	{
		InstantFreezeAIMsg() : LODAIMessage(1)
		{
		}
		virtual ~InstantFreezeAIMsg()
		{
		}
	};

	struct ThawAIMsg : public LODAIMessage
	{
		ThawAIMsg() : LODAIMessage(3)
		{
		}
		virtual ~ThawAIMsg()
		{
		}
	};

	struct GetGameObjectLODAIMsg : public LODAIMessage
	{
		GetGameObjectLODAIMsg() : LODAIMessage(5), level(-2)
		{
		}
		virtual ~GetGameObjectLODAIMsg()
		{
		}

		int level;  // +0xC
	};

	struct GetSustainedGameObjectLODAIMsg : public LODAIMessage
	{
		GetSustainedGameObjectLODAIMsg() : LODAIMessage(6), level(-2)
		{
		}
		virtual ~GetSustainedGameObjectLODAIMsg()
		{
		}

		int level;  // +0xC
	};

	// Squad messages (type 0x27)
	struct CanBeInSquadSquadMessage : public SquadMessage
	{
		CanBeInSquadSquadMessage() : SquadMessage(2)
		{
		}
		virtual ~CanBeInSquadSquadMessage()
		{
		}
	};

	struct IsSquadSquadMessage : public SquadMessage
	{
		IsSquadSquadMessage() : SquadMessage(3), isSquad(false)
		{
		}
		virtual ~IsSquadSquadMessage()
		{
		}

		bool isSquad;  // +0xC
	};

	// State change messages (type 0x2F)
	struct GoUnderGroundStatChangeMessage : public StateChangeMessage
	{
		GoUnderGroundStatChangeMessage() : StateChangeMessage(5)
		{
		}
		virtual ~GoUnderGroundStatChangeMessage()
		{
		}
	};

	struct ComeOutsideStateChangeMessage : public StateChangeMessage
	{
		ComeOutsideStateChangeMessage() : StateChangeMessage(6)
		{
		}
		virtual ~ComeOutsideStateChangeMessage()
		{
		}
	};

	struct InstantGoUndergroundStateChangeMessage : public StateChangeMessage
	{
		InstantGoUndergroundStateChangeMessage() : StateChangeMessage(7)
		{
		}
		virtual ~InstantGoUndergroundStateChangeMessage()
		{
		}
	};

	struct InstantComeOutsideStateChangeMessage : public StateChangeMessage
	{
		InstantComeOutsideStateChangeMessage() : StateChangeMessage(8)
		{
		}
		virtual ~InstantComeOutsideStateChangeMessage()
		{
		}
	};
}

#endif
