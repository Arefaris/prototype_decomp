// More of the ai system the actions of the ai fight items talk to (names are guesses; only what the actions use is declared).
#ifndef PROTO_FIGHTITEMS_AI_AIACTIONHELPERS_H
#define PROTO_FIGHTITEMS_AI_AIACTIONHELPERS_H

#include "code/engine/gameobject/gameobject.h"
#include "code/math/vector.h"

namespace proto
{
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
}

#endif
