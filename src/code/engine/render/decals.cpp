// The renderer's decal unit (0x10849070 - 0x1084CBB0, with the draw task; no assert path, file name guessed). Of the unit
// only what is on real types.
#include "code/ravenphysics/collision/collisionobject.h"
#include "code/ravenphysics/context.h"
#include "code/ravenphysics/physicsobject.h"

namespace engine
{
	// FUNCTION: ENGINE 0x1084CAA0
	// Empties the collision objects of a physics object and sets its collision mode to 1 (name guessed)
	void ResetObjectCollisions(ravenphysics::ObjectHandle handle)
	{
		if (handle.IsValid())
		{
			ravenphysics::PhysicsObject* object = handle.GetObject();
			unsigned int count = object->objectCount;
			for (unsigned int i = 0; i < count; i++)
			{
				object->objects[i]->Clear();
			}
			object->SetCollisionMode(1);
		}
	}
}
