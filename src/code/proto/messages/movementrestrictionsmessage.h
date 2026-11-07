// proto::GetMovementRestrictionsMessage (RTTI name; a movement message, type 0x26 id 7): asked of the movement of an
// object for the restrictions that bound its aim. The constructor is inline in every user; the member names are guesses.
#ifndef PROTO_MESSAGES_MOVEMENTRESTRICTIONSMESSAGE_H
#define PROTO_MESSAGES_MOVEMENTRESTRICTIONSMESSAGE_H

#include "code/math/vector.h"
#include "code/proto/fightitems/ai/aicodemessages.h"

namespace proto
{
	// The answer of the movement (0x1C bytes; the point to aim at starts at +0x10)
	struct MovementRestrictions
	{
		int unknown0;
		int unknown4;
		int unknown8;
		int unknownC;
		math::Vector point;  // +0x10
	};

	struct GetMovementRestrictionsMessage : public MovementMessage
	{
		GetMovementRestrictionsMessage() : MovementMessage(7), restrictions(0), unknown10(true), unknown11(true)
		{
		}
		virtual ~GetMovementRestrictionsMessage()
		{
		}

		MovementRestrictions* restrictions;  // +0xC
		bool unknown10;
		bool unknown11;
	};
}

#endif
