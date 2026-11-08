// engine::CollisionCallback (unit 0x1082BD60 - 0x1082BDB0, no assert path; the file name is a guess).
#include "code/engine/physics/collisioncallback.h"

namespace engine
{
	// FUNCTION: ENGINE 0x1082BD60
	CollisionCallback::CollisionCallback() : next(0), armed(false)
	{
	}

	// FUNCTION: ENGINE 0x1082BD80
	CollisionCallback::~CollisionCallback()
	{
	}

	// FUNCTION: ENGINE 0x1082BDA0
	void CollisionCallback::SetObject(const GameObjectHandle* newObject)
	{
		object = *newObject;
		armed = true;
	}
}
