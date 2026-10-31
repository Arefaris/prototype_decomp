// The disguise messages the fight items send to the player or an ai character (message type 0x2A, the id selects the request;
// names from the RTTI; the member names are guesses from the requests' use). The "Get" messages carry the answer in their
// payload, the "Set" messages the new value.
#ifndef PROTO_MESSAGES_DISGUISEMESSAGES_H
#define PROTO_MESSAGES_DISGUISEMESSAGES_H

#include "code/engine/message.h"

namespace proto
{
	struct DisguiseMessage : public engine::IntrusiveMessage
	{
	public:
		DisguiseMessage(short newId) : engine::IntrusiveMessage(0x2a, newId)
		{
		}
	};

	struct GetBlownDisguiseMsg : public DisguiseMessage
	{
	public:
		GetBlownDisguiseMsg() : DisguiseMessage(0x14), time(0.0f)
		{
		}

		float time;  // +0xC
	};

	struct SetBlownDisguiseMsg : public DisguiseMessage
	{
	public:
		SetBlownDisguiseMsg(float newTime) : DisguiseMessage(0x15), time(newTime)
		{
		}

		float time;  // +0xC
	};

	struct GetDisguiseVariableDisguiseMsg : public DisguiseMessage
	{
	public:
		GetDisguiseVariableDisguiseMsg(int newVariable) : DisguiseMessage(0x10), variable(newVariable), value(0.0f)
		{
		}

		int variable;  // +0xC
		float value;  // +0x10
	};

	struct GetDisguiseVariableIncreasedSinceDisguiseMsg : public DisguiseMessage
	{
	public:
		GetDisguiseVariableIncreasedSinceDisguiseMsg(int newVariable) : DisguiseMessage(0x11), variable(newVariable), value(1e+12f)
		{
		}

		int variable;  // +0xC
		float value;  // +0x10
	};

	struct SetDisguiseVariableDisguiseMsg : public DisguiseMessage
	{
	public:
		SetDisguiseVariableDisguiseMsg(int newVariable, float newValue) : DisguiseMessage(0x12), variable(newVariable), value(newValue)
		{
		}

		int variable;  // +0xC
		float value;  // +0x10
	};

	struct ResetDisguiseVariablesDisguiseMsg : public DisguiseMessage
	{
	public:
		ResetDisguiseVariablesDisguiseMsg(bool newResetJustTime, bool newDontResetFactionIfSniffer) : DisguiseMessage(0x13), resetJustTime(newResetJustTime), dontResetFactionIfSniffer(newDontResetFactionIfSniffer)
		{
		}

		bool resetJustTime;  // +0xC
		bool dontResetFactionIfSniffer;  // +0xD
	};

	struct GetGraceSwitchDisguisesMsg : public DisguiseMessage
	{
	public:
		GetGraceSwitchDisguisesMsg() : DisguiseMessage(0x1a), time(0.0f)
		{
		}

		float time;  // +0xC
	};

	struct GetSeenStatusDisguiseMsg : public DisguiseMessage
	{
	public:
		GetSeenStatusDisguiseMsg() : DisguiseMessage(0x1f), value0(0.0f), value1(0.0f), value2(0.0f), value3(0.0f)
		{
		}

		float value0;  // +0xC
		float value1;  // +0x10
		float value2;  // +0x14
		float value3;  // +0x18
	};

	struct GetTimeInPursuitDisguiseMsg : public DisguiseMessage
	{
	public:
		GetTimeInPursuitDisguiseMsg() : DisguiseMessage(0x21), time(0.0f)
		{
		}

		float time;  // +0xC
	};

	struct SetInPursuitDisguiseMsg : public DisguiseMessage
	{
	public:
		SetInPursuitDisguiseMsg(bool newPursuit) : DisguiseMessage(0x22), pursuit(newPursuit)
		{
		}

		bool pursuit;  // +0xC
	};

	struct GetChasingDisguiseMsg : public DisguiseMessage
	{
	public:
		GetChasingDisguiseMsg() : DisguiseMessage(0x27), guys(0)
		{
		}

		int guys;  // +0xC
	};

	struct GetBeginningCombatDisguiseMsg : public DisguiseMessage
	{
	public:
		GetBeginningCombatDisguiseMsg() : DisguiseMessage(0x29), guys(0)
		{
		}

		int guys;  // +0xC
	};

	struct SetHoldOnContinuousEventsDisguiseMsg : public DisguiseMessage
	{
	public:
		SetHoldOnContinuousEventsDisguiseMsg(bool newHold) : DisguiseMessage(0x2a), hold(newHold)
		{
		}

		bool hold;  // +0xC
	};

	struct GetInsideAlertCircleDisguiseMsg : public DisguiseMessage
	{
	public:
		GetInsideAlertCircleDisguiseMsg() : DisguiseMessage(0x31), inside(false), distance(0.0f)
		{
		}

		bool inside;  // +0xC
		float distance;  // +0x10
	};

	struct GetAllyWithMilitaryDisguiseMsg : public DisguiseMessage
	{
	public:
		GetAllyWithMilitaryDisguiseMsg() : DisguiseMessage(0x36), ally(false)
		{
		}

		bool ally;  // +0xC
	};

	struct GetHostileWithMilitaryDisguiseMsg : public DisguiseMessage
	{
	public:
		GetHostileWithMilitaryDisguiseMsg() : DisguiseMessage(0x38), hostile(false)
		{
		}

		bool hostile;  // +0xC
	};

	struct GetMilitaryRadioedDisguiseMsg : public DisguiseMessage
	{
	public:
		GetMilitaryRadioedDisguiseMsg() : DisguiseMessage(0x3c), radioed(false)
		{
		}

		bool radioed;  // +0xC
	};

	struct SetMilitaryRadioedDisguiseMsg : public DisguiseMessage
	{
	public:
		SetMilitaryRadioedDisguiseMsg(bool newRadioed) : DisguiseMessage(0x3d), radioed(newRadioed)
		{
		}

		bool radioed;  // +0xC
	};

	struct SetReactionDisguiseMsg : public DisguiseMessage
	{
	public:
		SetReactionDisguiseMsg(int newReaction) : DisguiseMessage(0x25), reaction(newReaction)
		{
		}

		int reaction;  // +0xC
	};
}

#endif
