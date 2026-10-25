#include "code/math/matrix.h"
#include "code/math/symmetricmatrix.h"
#include "code/ravenphysics/collision/collisioninfo.h"
#include "code/ravenphysics/collision/meshfaceref.h"
#include "code/ravenphysics/physicsobject.h"

namespace ravenphysics
{
	// FUNCTION: ENGINE 0x10668A70
	CollisionVolume* CollisionInfo::GetVolume(int side)
	{
		return volumes[side];
	}

	// FUNCTION: ENGINE 0x10668A80
	bool CollisionInfo::IsDeeperThan(const CollisionInfo* other) const
	{
		return other->contact.depth > contact.depth;
	}

	// FUNCTION: ENGINE 0x10668AA0
	int CollisionInfo::GetSide(int bodyId)
	{
		if (bodyId == bodies[0]->GetUnknown48())
		{
			return 0;
		}
		return (bodyId == bodies[1]->GetUnknown48()) ? 1 : -1;
	}

	// FUNCTION: ENGINE 0x10668AE0
	int CollisionInfo::GetOtherSide(int bodyId)
	{
		if (bodyId == bodies[0]->GetUnknown48())
		{
			return 1;
		}
		return bodyId == bodies[1]->GetUnknown48() ? 0 : -1;
	}

	// FUNCTION: ENGINE 0x10668B20
	void CollisionInfo::GetSides(int bodyId, int* side, int* other)
	{
		if (bodyId == bodies[0]->GetUnknown48())
		{
			*side = 0;
			*other = 1;
			return;
		}
		if (bodyId == bodies[1]->GetUnknown48())
		{
			*side = 1;
			*other = 0;
			return;
		}
		*side = -1;
		*other = -1;
	}

	// FUNCTION: ENGINE 0x10668B90
	void CollisionInfo::Transform(const math::Matrix& matrix)
	{
		contact.Transform(matrix);
	}

	// FUNCTION: ENGINE 0x10668BA0
	void CollisionInfo::SetBody(int side, BroadPhaseObject* body)
	{
		bodies[side] = body;
		if (body != 0)
		{
			bodyHandles[side].value = body->id;
		}
		else
		{
			bodyHandles[side].value = 0xffffffff;
		}
	}

	// FUNCTION: ENGINE 0x10668BD0
	void CollisionInfo::SetObject(int side, CollisionObject* object)
	{
		objects[side] = object;
		if (object != 0)
		{
			objectHandles[side] = object->handle.value;
		}
		else
		{
			objectHandles[side] = 0xffffffff;
		}
	}

	// FUNCTION: ENGINE 0x10668C00
	// EQUIVALENT: the same loads and tests in the same order; the engine keeps the side in esi, the triangle number in dx, and leaves by a jump to GetMaterialOf after popping esi, ours keeps the number in esi and calls, 8.7 %
	IntersectionProperties* CollisionInfo::GetFilter(int side)
	{
		CollisionObject* object = objects[side];
		if (object == 0)
		{
			return &bodies[side]->masks;
		}
		CollisionVolume* volume;
		if (side == 1 && contact.faceIndex != 0xffff)
		{
			CollisionVolume6* mesh = static_cast<CollisionVolume6*>(objects[1]->volumes[volumeIndices[1]]);
			if (mesh->grid.unknownC8)
			{
				return (IntersectionProperties*)mesh->grid.GetMaterialOf(contact.faceIndex);
			}
			volume = mesh;
		}
		else
		{
			volume = object->volumes[volumeIndices[side]];
		}
		return &volume->filter;
	}

	// FUNCTION: ENGINE 0x10668C60
	GridFace* CollisionInfo::GetFace()
	{
		return static_cast<CollisionVolume6*>(volumes[1])->grid.faces + contact.faceIndex;
	}

	// FUNCTION: ENGINE 0x10668C80
	void CollisionInfo::GetFaceRef(MeshFaceRef* ref)
	{
		ref->Set(static_cast<CollisionVolume6*>(volumes[1]), contact.faceIndex);
	}

	// FUNCTION: ENGINE 0x10668CA0
	void CollisionInfo::GetVelocity(int side, math::Vector* velocity)
	{
		velocity->z = 0.0f;
		velocity->y = 0.0f;
		velocity->x = 0.0f;
		PhysicsObject* body = bodyHandles[side].GetObjectSecond();
		if ((body->collisionMode & 3) == 2)
		{
			objects[side]->GetVelocityAt(contact.points[side], velocity);
		}
	}

	// FUNCTION: ENGINE 0x10668D10
	unsigned char CollisionInfo::GetMaterial(int side)
	{
		CollisionObject* object = objects[side];
		if (object != 0)
		{
			if (side == 1 && contact.faceIndex != 0xffff)
			{
				return GetFace()->flags >> 3 & 0x3f;
			}
			return object->volumes[volumeIndices[side]]->material;
		}
		return 0;
	}
}

namespace math
{
	// FUNCTION: ENGINE 0x10668D90
	float SymmetricMatrix::Determinant() const
	{
		return (zz * yy - yz * yz) * xx + (xz * yz - zz * xy) * xy + (xy * yz - yy * xz) * xz;
	}
}
