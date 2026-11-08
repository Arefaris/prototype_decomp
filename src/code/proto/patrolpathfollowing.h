// proto::PatrolPathFollowing and the followers it moves a patrolling object with (RTTI: class PatrolPathFollowing, its
// nested structs Follower and Notifier, struct CharacterFollower and struct SimpleTransformFollower, both derived from
// Follower). A follower is told where to go (slot 0), to stop (slot 1), where to look (slot 2) and answers how its
// movement goes (slot 3). Unit 0x103A6390 - 0x103A6570 (no assert path; the file name is a guess); member names are
// guesses.
#ifndef PROTO_PATROLPATHFOLLOWING_H
#define PROTO_PATROLPATHFOLLOWING_H

#include "code/engine/gameobject/gameobject.h"
#include "code/math/vector.h"

namespace proto
{
	class PatrolPathFollowing
	{
	public:
		struct Follower
		{
			virtual void MoveTo(const math::Vector* position, float tolerance, bool braking) = 0;
			virtual void Stop() = 0;
			virtual void LookAt(const math::Vector* direction) = 0;
			virtual int GetState(int unused) = 0;
		};
	};

	// Moves a game object through its movement behaviour (0x103A6390 - 0x103A64E0; slot 2 is 0x103A63F0)
	struct CharacterFollower : public PatrolPathFollowing::Follower
	{
		virtual void MoveTo(const math::Vector* position, float tolerance, bool braking);
		virtual void Stop();
		virtual void LookAt(const math::Vector* direction);
		virtual int GetState(int unused);

		engine::GameObject* owner;  // +4
	};

	// Remembers where it was sent (0x103A6520 - 0x103A6E70; slot 3 is 0x103A6E70)
	struct SimpleTransformFollower : public PatrolPathFollowing::Follower
	{
		virtual void MoveTo(const math::Vector* position, float tolerance, bool braking);
		virtual void Stop();
		virtual void LookAt(const math::Vector* direction);
		virtual int GetState(int unused);

		unsigned char unknown4[0xC];
		math::Vector target;  // +0x10
		float speed;  // +0x1C
	};
}

#endif
