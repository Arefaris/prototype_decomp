// More of the ai system the actions of the ai fight items talk to (names are guesses; only what the actions use is declared).
#ifndef PROTO_FIGHTITEMS_AI_AIACTIONHELPERS_H
#define PROTO_FIGHTITEMS_AI_AIACTIONHELPERS_H

#include "code/engine/gameobject/gameobject.h"
#include "code/math/vector.h"

namespace proto
{
	struct JumpDestination;

	// How an object is sent to a position (8 bytes)
	struct MoveParams
	{
		MoveParams() : tolerance(0.5f), braking(true), ignoreRestrictions(false), unknown6(false)
		{
		}

		float tolerance;
		bool braking;
		bool ignoreRestrictions;
		bool unknown6;
	};

	// 0x103B8330: sends the object to a position (name guess)
	void Unknown103B8330(engine::GameObject* object, const math::Vector* position, const MoveParams* params);
	// 0x103BAE00: sends the object to the position of a jump destination, which it brings up to date first (name guess)
	void Unknown103BAE00(engine::GameObject* object, JumpDestination* destination);
}

#endif
