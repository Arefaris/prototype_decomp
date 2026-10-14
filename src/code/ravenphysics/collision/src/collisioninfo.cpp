#include "code/ravenphysics/collision/collisioninfo.h"

namespace ravenphysics
{
	// FUNCTION: ENGINE 0x10668C60
	MeshFace* CollisionInfo::GetFace()
	{
		return mesh->faces + faceIndex;
	}

	// FUNCTION: ENGINE 0x10668D10
	unsigned char CollisionInfo::GetMaterial(int side)
	{
		CollisionObject* object = objects[side];
		if (object != 0)
		{
			if (side == 1 && faceIndex != 0xffff)
			{
				return GetFace()->flags >> 3 & 0x3f;
			}
			return object->volumes[volumeIndices[side]]->material;
		}
		return 0;
	}
}
