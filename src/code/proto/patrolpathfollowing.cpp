#include "code/proto/patrolpathfollowing.h"
#include "code/proto/fightitems/ai/aiactionhelpers.h"
#include "code/proto/fightitems/ai/aihelpers.h"

namespace proto
{
	// FUNCTION: ENGINE 0x103A6390
	void CharacterFollower::MoveTo(const math::Vector* position, float tolerance, bool braking)
	{
		MoveParams params;
		params.braking = braking;
		params.unknown6 = false;
		params.tolerance = tolerance;
		params.ignoreRestrictions = true;
		Unknown103B8330(owner, position, &params);
	}

	// FUNCTION: ENGINE 0x103A63E0
	void CharacterFollower::Stop()
	{
		Unknown103B82F0(owner);
	}

	// FUNCTION: ENGINE 0x103A64E0
	int CharacterFollower::GetState(int unused)
	{
		if (Unknown103B84B0(owner))
		{
			return 2;
		}
		return !Unknown103B8440(owner);
	}

	// FUNCTION: ENGINE 0x103A6520
	// NONMATCHING: the engine stores the float after the last vector component (77.1 %)
#ifdef NONMATCHING
	void SimpleTransformFollower::MoveTo(const math::Vector* position, float tolerance, bool braking)
	{
		target.x = position->x;
		target.y = position->y;
		target.z = position->z;
		speed = tolerance;
	}
#endif

	// FUNCTION: ENGINE 0x103A6550
	void SimpleTransformFollower::Stop()
	{
	}

	// FUNCTION: ENGINE 0x103A6560
	void SimpleTransformFollower::LookAt(const math::Vector* direction)
	{
	}
}
