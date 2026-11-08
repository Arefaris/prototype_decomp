// Movement messages (RTTI names; message type 0x26, the base proto::MovementMessage is in fightitems/ai/aicodemessages.h)
// that the AI helpers send to the movement of an object. The constructors are inline in every user; the vftables of
// the ones below are in the unit 0x103B8xxx - 0x103BAxxx. Member names are guesses from the senders.
#ifndef PROTO_MESSAGES_MOVEMENTMESSAGES_H
#define PROTO_MESSAGES_MOVEMENTMESSAGES_H

#include "code/math/vector.h"
#include "code/proto/fightitems/ai/aicodemessages.h"

namespace proto
{
	// Sends the object to a position (id 0)
	struct SetDestinationMovementMessage : public MovementMessage
	{
		SetDestinationMovementMessage(const math::Vector& newDestination, float newTolerance, bool newBraking,
			bool newIgnoreRestrictions, bool newUnknown1E)
			: MovementMessage(0), destination(newDestination), tolerance(newTolerance), braking(newBraking),
			ignoreRestrictions(newIgnoreRestrictions), unknown1E(newUnknown1E)
		{
		}
		virtual ~SetDestinationMovementMessage()
		{
		}

		math::Vector destination;  // +0xC
		float tolerance;  // +0x18
		bool braking;  // +0x1C
		bool ignoreRestrictions;
		bool unknown1E;
	};

	// Stops the object (id 3)
	struct StopMovementMessage : public MovementMessage
	{
		StopMovementMessage() : MovementMessage(3)
		{
		}
		virtual ~StopMovementMessage()
		{
		}
	};

	// Asks for the state of the movement (id 4)
	struct GetStateMovementMessage : public MovementMessage
	{
		GetStateMovementMessage() : MovementMessage(4), state(0)
		{
		}
		virtual ~GetStateMovementMessage()
		{
		}

		int state;  // +0xC
	};

	// A motion in a direction (id 0x1e) and relative to the object's heading (id 0x1f)
	struct SetMotionMovementMessage : public MovementMessage
	{
		SetMotionMovementMessage(float newSpeed, const math::Vector& newMotion, bool newFlag)
			: MovementMessage(0x1e), speed(newSpeed), motion(newMotion), flag(newFlag)
		{
		}
		virtual ~SetMotionMovementMessage()
		{
		}

		float speed;  // +0xC
		math::Vector motion;  // +0x10
		bool flag;  // +0x1C
	};

	struct SetMotionRelativeMovementMessage : public MovementMessage
	{
		SetMotionRelativeMovementMessage(float newSpeed, const math::Vector& newMotion, bool newFlag)
			: MovementMessage(0x1f), speed(newSpeed), motion(newMotion), flag(newFlag)
		{
		}
		virtual ~SetMotionRelativeMovementMessage()
		{
		}

		float speed;  // +0xC
		math::Vector motion;  // +0x10
		bool flag;  // +0x1C
	};

	// Walk or run (id 0x2a)
	struct RunMovementMessage : public MovementMessage
	{
		RunMovementMessage(bool newRun, bool newUnknownD) : MovementMessage(0x2a), run(newRun), unknownD(newUnknownD)
		{
		}
		virtual ~RunMovementMessage()
		{
		}

		bool run;  // +0xC
		bool unknownD;
	};

	// The facing direction of the base of a tank (id 0x30)
	struct SetTankBaseFacingDirectionMessage : public MovementMessage
	{
		explicit SetTankBaseFacingDirectionMessage(const math::Vector& newDirection)
			: MovementMessage(0x30), direction(newDirection)
		{
		}
		virtual ~SetTankBaseFacingDirectionMessage()
		{
		}

		math::Vector direction;  // +0xC
	};

	// Sends the object along a flight path (id 0x4a)
	struct GotoFlyPathMovementMessage : public MovementMessage
	{
		GotoFlyPathMovementMessage(float newSpeed, bool newUnknown14, bool newUnknown15, void* newPath)
			: MovementMessage(0x4a), path(newPath), speed(newSpeed), unknown14(newUnknown14), unknown15(newUnknown15)
		{
		}
		virtual ~GotoFlyPathMovementMessage()
		{
		}

		void* path;  // +0xC
		float speed;  // +0x10
		bool unknown14;
		bool unknown15;
	};

	// The target of a hydra's move is worked out from a point (id 0x36)
	struct HydraEvaluateDestinationMovementMessage : public MovementMessage
	{
		HydraEvaluateDestinationMovementMessage(const math::Vector& newPoint, bool newUnknown18)
			: MovementMessage(0x36), point(newPoint), unknown18(newUnknown18), unknown1C(0.0f)
		{
		}
		virtual ~HydraEvaluateDestinationMovementMessage()
		{
		}

		math::Vector point;  // +0xC
		bool unknown18;
		float unknown1C;
	};

	// The frame information of the AI is thrown away (id 0x58)
	struct ResetAIFrameInfoMovementMessage : public MovementMessage
	{
		ResetAIFrameInfoMovementMessage() : MovementMessage(0x58)
		{
		}
		virtual ~ResetAIFrameInfoMovementMessage()
		{
		}
	};

	// The patrol point queries (ids 0x10 - 0x14; the answers are written behind the id)
	struct GetPatrolPointMovementMessage : public MovementMessage
	{
		explicit GetPatrolPointMovementMessage(int newIndex) : MovementMessage(0x10), index(newIndex), unknown10(0)
		{
		}
		virtual ~GetPatrolPointMovementMessage()
		{
		}

		int index;  // +0xC
		int unknown10;
	};

	struct GetLastPatrolPointMovementMessage : public MovementMessage
	{
		GetLastPatrolPointMovementMessage() : MovementMessage(0x11), unknownC(0)
		{
		}
		virtual ~GetLastPatrolPointMovementMessage()
		{
		}

		int unknownC;
	};

	struct GetNumberPatrolPointsMovementMessage : public MovementMessage
	{
		GetNumberPatrolPointsMovementMessage() : MovementMessage(0x12), count(0)
		{
		}
		virtual ~GetNumberPatrolPointsMovementMessage()
		{
		}

		int count;  // +0xC
	};

	struct GetPatrolPathMovementMessage : public MovementMessage
	{
		GetPatrolPathMovementMessage() : MovementMessage(0x13), path(0)
		{
		}
		virtual ~GetPatrolPathMovementMessage()
		{
		}

		void* path;  // +0xC
	};

	struct GetPatrolPathInfoMovementMessage : public MovementMessage
	{
		GetPatrolPathInfoMovementMessage() : MovementMessage(0x14), info(0)
		{
		}
		virtual ~GetPatrolPathInfoMovementMessage()
		{
		}

		void* info;  // +0xC
	};
}

#endif
