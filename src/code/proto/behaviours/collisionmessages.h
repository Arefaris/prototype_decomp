// The collision messages (message type 0x1D) the collision action behaviour answers, besides the proto::CollisionMessage
// base and the clear message that motionmessages.h declares (RTTI names; the ids come from their constructors, the member
// names are guesses from the behaviour's use).
#ifndef PROTO_BEHAVIOURS_COLLISIONMESSAGES_H
#define PROTO_BEHAVIOURS_COLLISIONMESSAGES_H

#include "code/proto/fightitems/motion/motionmessages.h"

namespace proto
{
	// The cached wall collision of the object is read (id 1)
	class GetCachedWallCollisionMessage : public CollisionMessage
	{
	public:
		GetCachedWallCollisionMessage() : CollisionMessage(1), found(false), unknown10(0.0f), unknown14(0.0f),
			unknown18(0.0f), unknown1C(0.0f), unknown20(0.0f), unknown24(0.0f), unknown28(0.0f)
		{
		}
		virtual ~GetCachedWallCollisionMessage()
		{
		}

		bool found;  // +0xC
		float unknown10;
		float unknown14;
		float unknown18;
		float unknown1C;
		float unknown20;
		float unknown24;
		float unknown28;
	};

	// Counts the requests to turn the collision on or off (id 2)
	class SetCollisionActiveMessage : public CollisionMessage
	{
	public:
		explicit SetCollisionActiveMessage(bool newActive) : CollisionMessage(2), active(newActive)
		{
		}
		virtual ~SetCollisionActiveMessage()
		{
		}

		bool active;  // +0xC
	};

	// Whether a collision with an object is to be reported (id 3), and the same for validation (id 4)
	class IsValidCollisionMessage : public CollisionMessage
	{
	public:
		IsValidCollisionMessage(int newObject, float newTime) : CollisionMessage(3), object(newObject), time(newTime),
			valid(false)
		{
		}
		virtual ~IsValidCollisionMessage()
		{
		}

		int object;  // +0xC
		float time;  // +0x10
		bool valid;  // +0x14
	};

	class ValidateCollisionMessage : public CollisionMessage
	{
	public:
		ValidateCollisionMessage(int newObject, float newTime) : CollisionMessage(4), object(newObject), time(newTime),
			valid(false)
		{
		}
		virtual ~ValidateCollisionMessage()
		{
		}

		int object;  // +0xC
		float time;  // +0x10
		bool valid;  // +0x14
	};

	// Whether an object is in the list of the recent colliders (id 5)
	class FindCachedColliderMessage : public CollisionMessage
	{
	public:
		explicit FindCachedColliderMessage(int newObject) : CollisionMessage(5), object(newObject), found(false)
		{
		}
		virtual ~FindCachedColliderMessage()
		{
		}

		int object;  // +0xC
		bool found;  // +0x10
	};

	// Puts an object in the list of the recent colliders (id 6)
	class AddCachedColliderMessage : public CollisionMessage
	{
	public:
		explicit AddCachedColliderMessage(int newObject) : CollisionMessage(6), object(newObject)
		{
		}
		virtual ~AddCachedColliderMessage()
		{
		}

		int object;  // +0xC
	};

	// The behaviour answers itself (id 7)
	class GetCollisionActionBehaviourMessage : public CollisionMessage
	{
	public:
		GetCollisionActionBehaviourMessage() : CollisionMessage(7), behaviour(0)
		{
		}
		virtual ~GetCollisionActionBehaviourMessage()
		{
		}

		class CollisionActionBehaviour* behaviour;  // +0xC
	};
}

#endif
