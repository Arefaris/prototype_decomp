#include "code/proto/patrolpathfollowing.h"
#include "code/proto/fightitems/ai/aiactionhelpers.h"
#include "code/proto/fightitems/ai/aimessages.h"
#include "code/proto/fightitems/ai/aihelpers.h"

namespace proto
{
	// FUNCTION: ENGINE 0x103A61D0
	PatrolPathFollowing::PatrolPathFollowing(Follower* newFollower, Notifier* newNotifier) :
		notifier(newNotifier), unknown4(0), unknown8(0), follower(newFollower), unknown14(math::kZeroVector),
		unknown20(math::kZeroVector), unknown2C(-1), unknown30(-1), unknown34(0.0f)
	{
	}

	// FUNCTION: ENGINE 0x103A6270
	PatrolPathFollowing::~PatrolPathFollowing()
	{
	}

	// FUNCTION: ENGINE 0x103A6600
	SimplePathFollowing::SimplePathFollowing(PatrolPathFollowing::Follower* newFollower,
		PatrolPathFollowing::Notifier* newNotifier, float newUnknown38) :
		notifier(newNotifier), unknown4(0), unknown8(0), follower(newFollower), unknown14(math::kZeroVector),
		unknown20(math::kZeroVector), unknown34(0.0f), unknown2C(-1), unknown30(-1), unknown38(newUnknown38)
	{
	}

	// FUNCTION: ENGINE 0x103A66B0
	SimplePathFollowing::~SimplePathFollowing()
	{
		if (unknown8 != 0)
		{
			operator delete(unknown8);
		}
	}

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

	// FUNCTION: ENGINE 0x103A63F0
	// NONMATCHING: the engine reuses the register of the zero for the direction and stores the flag as an immediate (37.6 %)
#ifdef NONMATCHING
	void CharacterFollower::LookAt(const math::Vector* direction)
	{
		GetAimParametersMovementMessage message(true);
		owner->SendMessage(&message);
		if (message.parameters != 0)
		{
			message.parameters->active = 1;
			math::Vector* offset = &message.parameters->offset;
			offset->z = 0.0f;
			offset->y = 0.0f;
			offset->x = 0.0f;
			if (direction->IsZero())
			{
				message.parameters->where = 1;
				message.parameters->forceWorldAngles = false;
				return;
			}
			message.parameters->where = 7;
			math::Vector* look = &message.parameters->direction;
			look->x = direction->x;
			look->y = direction->y;
			look->z = direction->z;
			message.parameters->forceWorldAngles = false;
		}
	}
#endif

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
