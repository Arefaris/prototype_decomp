// engine::CollisionCallback and engine::CollisionResponseCallback (RTTI names): what an object registers with the physics
// manager to hear about the collisions of a game object. Member names are guesses.
#ifndef ENGINE_PHYSICS_COLLISIONCALLBACK_H
#define ENGINE_PHYSICS_COLLISIONCALLBACK_H

#include "code/engine/gameobject/gameobjecthandle.h"

namespace ravenphysics
{
	extern const float gDefaultMaxForce;
}

namespace engine
{
	// RTTI: engine::CollisionCallback (the base: a list link, the object it listens for and whether it is armed)
	class CollisionCallback
	{
	public:
		// 0x1082BD60 (another unit)
		CollisionCallback();
		// 0x1082BD80 (another unit)
		virtual ~CollisionCallback();
		// 0x1082BDA0 (another unit): listens for the object and arms the callback
		void SetObject(const GameObjectHandle* newObject);

		CollisionCallback* next;  // +4
		GameObjectHandle object;  // +8
		bool armed;  // +0xC
	};

	// RTTI: engine::CollisionResponseCallback (a callback that answers collisions up to a force)
	class CollisionResponseCallback : public CollisionCallback
	{
	public:
		CollisionResponseCallback() : maxForce(ravenphysics::gDefaultMaxForce)
		{
		}

		// vftable slot 1 (pure): a collision of the object (the arguments are not known)
		virtual void OnCollision(int first, int second, int third) = 0;

		float maxForce;  // +0x10
	};
}

#endif
