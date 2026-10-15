#include "code/core/debug.h"
#include "code/ravenphysics/collision/collisionobject.h"
#include "code/ravenphysics/physicsobject.h"

#define PHYSICSOBJECT_FILE "..\\..\\..\\code\\ravenphysics\\src\\physicsobject.cpp"

namespace ravenphysics
{
	// FUNCTION: ENGINE 0x106608A0
	void PhysicsObject::UpdateBounds()
	{
		OLD_ASSERT_AT(PHYSICSOBJECT_FILE, 804, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		float minX = 1e12f;
		float minY = 1e12f;
		float minZ = 1e12f;
		float maxX = -1e12f;
		float maxY = -1e12f;
		float maxZ = -1e12f;
		unsigned int total = objectCount;
		for (unsigned int i = 0; i < total; i++)
		{
			CollisionObject* object = objects[i];
			if ((object->state & 0x80000000) != 0)
			{
				unsigned int volumesLeft = object->volumeCount;
				if (volumesLeft > 0)
				{
					CollisionVolume** volumePointer = object->volumes;
					do
					{
						const float* bounds = &(*volumePointer)->boundsMin.x;
						if (!(bounds[0] > minX))
						{
							minX = bounds[0];
						}
						if (!(bounds[1] > minY))
						{
							minY = bounds[1];
						}
						if (!(bounds[2] > minZ))
						{
							minZ = bounds[2];
						}
						if (maxX < bounds[3])
						{
							maxX = bounds[3];
						}
						if (maxY < bounds[4])
						{
							maxY = bounds[4];
						}
						if (maxZ < bounds[5])
						{
							maxZ = bounds[5];
						}
						volumePointer++;
						volumesLeft--;
					}
					while (volumesLeft != 0);
				}
			}
		}
		boundsMax.Set(maxX, maxY, maxZ);
		boundsMin.Set(minX, minY, minZ);
		if (detector != 0)
		{
			BroadPhaseBox* box = detector->boxes + detectorIndex;
			box->boundsMax.Set(maxX, maxY, maxZ);
			box->boundsMin.Set(minX, minY, minZ);
		}
	}

	// FUNCTION: ENGINE 0x106612C0
	void PhysicsObject::RefreshBounds(bool unused)
	{
		OLD_ASSERT_AT(PHYSICSOBJECT_FILE, 328, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		bool changed = false;
		for (unsigned int i = 0; i != objectCount; i++)
		{
			changed = changed || objects[i]->TestAndClearChanged();
		}
		if (changed)
		{
			UpdateBounds();
		}
	}
}
