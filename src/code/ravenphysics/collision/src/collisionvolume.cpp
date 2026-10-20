// The collision volumes of the narrow phase: their head and the capsule, box, sphere and plane volumes (0x10663E30 -
// 0x10666800). The unit has no assert path of its own; the file name is a guess.
#include "code/math/worldbounds.h"
#include "code/math/mathutils.h"
#include "code/ravenphysics/collision/collisionobject.h"
#include <math.h>

namespace ravenphysics
{
	// The engine copies vectors component by component
	inline void Copy(math::Vector& to, const math::Vector& from)
	{
		to.x = from.x;
		to.y = from.y;
		to.z = from.z;
	}

	inline void Copy(math::Capsule& to, const math::Capsule& from)
	{
		Copy(to.centre, from.centre);
		to.halfLength = from.halfLength;
		Copy(to.direction, from.direction);
		to.radius = from.radius;
	}

	inline void Copy(math::Sphere& to, const math::Sphere& from)
	{
		Copy(to.centre, from.centre);
		to.radius = from.radius;
	}

	// a scaled component by component by b
	inline void Multiply(math::Vector& a, const math::Vector& b)
	{
		a.x = a.x * b.x;
		a.y = a.y * b.y;
		a.z = a.z * b.z;
	}

	// The printing of the math types, inlined where the volumes print them
	inline void PrintCapsule(const math::Capsule& capsule)
	{
		capsule.centre.Print();
		capsule.direction.Print();
	}

	inline void PrintOBB(const math::OBB& obb)
	{
		obb.centre.Print();
		obb.axis[0].Print();
		obb.axis[1].Print();
		obb.axis[2].Print();
		obb.extents.Print();
	}

	inline void PrintAABB(const math::AABB& box)
	{
		box.min.Print();
		box.max.Print();
	}

	// FUNCTION: ENGINE 0x10663E30
	CollisionVolume::CollisionVolume(unsigned char newType) :
		type(newType),
		swapped(0),
		material(0),
		unknown3(0)
	{
	}

	// FUNCTION: ENGINE 0x10663E60
	CollisionVolume::CollisionVolume(const CollisionVolume& other) :
		type(other.type),
		swapped(other.swapped),
		material(other.material),
		unknown3(0),
		bounds(other.bounds),
		filter(other.filter)
	{
	}

	// FUNCTION: ENGINE 0x106641A0
	void CollisionCapsule::GetLocalCapsule(math::Capsule* out) const
	{
		Copy(out->centre, localCentre);
		Copy(out->direction, localDirection);
		out->halfLength = capsule.halfLength;
		out->radius = capsule.radius;
	}

	// FUNCTION: ENGINE 0x106641E0
	void CollisionCapsule::UpdateBox()
	{
		capsule.GetAABB(bounds);
	}

	// FUNCTION: ENGINE 0x106641F0
	void CollisionCapsule::Print()
	{
		localCentre.Print();
		localDirection.Print();
		PrintCapsule(capsule);
	}

	// FUNCTION: ENGINE 0x10664A70
	CollisionCapsule::CollisionCapsule(const CollisionCapsule& other) :
		CollisionVolume(other),
		localCentre(other.localCentre),
		localDirection(other.localDirection),
		capsule(other.capsule)
	{
	}

	// FUNCTION: ENGINE 0x10664BA0
	// EQUIVALENT: the same stores in the same order; the engine addresses the capsule and the local vectors from this + 4 (the box it hands to GetAABB), ours from this, 26.2 %
	void CollisionCapsule::SetCapsule(const math::Capsule& newCapsule)
	{
		capsule.centre.x = newCapsule.centre.x;
		capsule.centre.y = newCapsule.centre.y;
		capsule.centre.z = newCapsule.centre.z;
		capsule.halfLength = newCapsule.halfLength;
		capsule.direction.x = newCapsule.direction.x;
		capsule.direction.y = newCapsule.direction.y;
		capsule.direction.z = newCapsule.direction.z;
		capsule.radius = newCapsule.radius;
		localCentre.x = newCapsule.centre.x;
		localCentre.y = newCapsule.centre.y;
		localCentre.z = newCapsule.centre.z;
		localDirection.x = newCapsule.direction.x;
		localDirection.y = newCapsule.direction.y;
		localDirection.z = newCapsule.direction.z;
		capsule.GetAABB(bounds);
	}

	// FUNCTION: ENGINE 0x10664E90
	void CollisionCapsule::Move(const math::Matrix& matrix)
	{
		capsule.Transform(matrix);
		UpdateBox();
	}

	// FUNCTION: ENGINE 0x106656F0
	CollisionCapsule::CollisionCapsule(const math::Capsule& newCapsule) :
		CollisionVolume(0)
	{
		SetCapsule(newCapsule);
		UpdateBox();
	}

	// FUNCTION: ENGINE 0x106643C0
	void CollisionSphere::GetLocalSphere(math::Sphere* out) const
	{
		Copy(out->centre, localCentre);
		out->radius = sphere.radius;
	}

	// FUNCTION: ENGINE 0x106645B0
	void CollisionSphere::Print()
	{
		localCentre.Print();
		sphere.centre.Print();
	}

	// FUNCTION: ENGINE 0x10664AE0
	CollisionSphere::CollisionSphere(const CollisionSphere& other) :
		CollisionVolume(other),
		localCentre(other.localCentre),
		sphere(other.sphere)
	{
	}

	// FUNCTION: ENGINE 0x10664530
	// EQUIVALENT: the same products and sum, the engine loads the centre ahead of the scale and multiplies it by the scale (ours the scale by the centre), 9.6 %
	void CollisionSphere::Scale(const math::Vector* scale)
	{
		float x = scale->x;
		float y = scale->y;
		float z = scale->z;
		localCentre.x = localCentre.x * x;
		localCentre.y = localCentre.y * y;
		localCentre.z = localCentre.z * z;
		sphere.radius = sphere.radius * ((x + y + z) * 0.33333334f);
		Copy(sphere.centre, localCentre);
	}

	// FUNCTION: ENGINE 0x10665510
	// EQUIVALENT: the same stores in the same order; the engine addresses the sphere and the local centre from this + 4 (the box it hands to GetAABB), ours from this, 40.0 %
	void CollisionSphere::SetSphere(const math::Sphere& newSphere)
	{
		Copy(sphere, newSphere);
		Copy(localCentre, newSphere.centre);
		sphere.GetAABB(bounds);
	}

	// FUNCTION: ENGINE 0x106647A0
	void CollisionPlane::GetLocalPlane(math::Plane* out) const
	{
		float distance = localPlane.d;
		Copy(out->normal, localPlane.normal);
		out->d = distance;
	}

	// FUNCTION: ENGINE 0x10664630
	void CollisionPlane::Print()
	{
		localPlane.normal.Print();
		PrintAABB(localBox);
		plane.normal.Print();
	}

	// FUNCTION: ENGINE 0x106645D0
	void CollisionPlane::UpdateWorld(CollisionObject* object)
	{
		plane.Transform(object->transform, localPlane);
		bounds.SetTransformed(object->transform, localBox);
	}

	// FUNCTION: ENGINE 0x10664600
	void CollisionPlane::Move(const math::Matrix& matrix)
	{
		plane.Transform(matrix, plane);
		bounds.SetTransformed(matrix, localBox);
	}

	// FUNCTION: ENGINE 0x10663F70
	CollisionPlane::CollisionPlane(const CollisionPlane& other) :
		CollisionVolume(other),
		localPlane(other.localPlane),
		localBox(other.localBox),
		plane(other.plane)
	{
	}

	// FUNCTION: ENGINE 0x10664370
	void CollisionOBB::Print()
	{
		localCentre.Print();
		localAxis0.Print();
		localAxis1.Print();
		PrintOBB(obb);
	}

	// FUNCTION: ENGINE 0x106642D0
	void CollisionOBB::UpdateBox()
	{
		obb.GetAABB(bounds);
	}

	// FUNCTION: ENGINE 0x106642E0
	// EQUIVALENT: the same products, the engine loads the stored value ahead of the scale (ours the scale first), 21.0 %
	void CollisionOBB::Scale(const math::Vector* scale)
	{
		Multiply(localCentre, *scale);
		Multiply(obb.extents, *scale);
		Copy(obb.centre, localCentre);
	}

	// FUNCTION: ENGINE 0x10664220
	// EQUIVALENT: the same cross product in the same order; the engine keeps the six axis components in registers, ours reads them from memory, 49.4 %
	void CollisionOBB::GetLocalOBB(math::OBB* out) const
	{
		Copy(out->centre, localCentre);
		Copy(out->axis[0], localAxis0);
		Copy(out->axis[1], localAxis1);
		const math::Vector& a = out->axis[0];
		const math::Vector& b = out->axis[1];
		out->axis[2].y = a.z * b.x - a.x * b.z;
		out->axis[2].z = a.x * b.y - a.y * b.x;
		out->axis[2].x = a.y * b.z - a.z * b.y;
		Copy(out->extents, obb.extents);
	}

	// FUNCTION: ENGINE 0x106644D0
	void CollisionSphere::UpdateBox()
	{
		math::Vector extent(sphere.radius, sphere.radius, sphere.radius);
		bounds.min.Sub(sphere.centre, extent);
		bounds.max.Add(sphere.centre, extent);
	}

	// FUNCTION: ENGINE 0x10665750
	CollisionSphere::CollisionSphere(const math::Sphere& newSphere) :
		CollisionVolume(2)
	{
		sphere.centre.x = 0.0f;
		sphere.centre.y = 0.0f;
		sphere.centre.z = 0.0f;
		SetSphere(newSphere);
		UpdateBox();
	}

	// FUNCTION: ENGINE 0x10665720
	CollisionOBB::CollisionOBB(const math::OBB& newBox) :
		CollisionVolume(1)
	{
		SetOBB(newBox);
		UpdateBox();
	}

	// FUNCTION: ENGINE 0x10665570
	void CollisionPlane::SetPlaneAndBox(const void* newPlane, const void* newBox)
	{
		const math::Plane* source = static_cast<const math::Plane*>(newPlane);
		const math::AABB* box = static_cast<const math::AABB*>(newBox);
		float distance = source->d;
		plane.normal.x = source->normal.x;
		plane.normal.y = source->normal.y;
		plane.normal.z = source->normal.z;
		plane.d = distance;
		distance = source->d;
		localPlane.normal.x = source->normal.x;
		localPlane.normal.y = source->normal.y;
		localPlane.normal.z = source->normal.z;
		localPlane.d = distance;
		localBox.max.x = box->max.x;
		localBox.max.y = box->max.y;
		localBox.max.z = box->max.z;
		localBox.min.x = box->min.x;
		localBox.min.y = box->min.y;
		localBox.min.z = box->min.z;
		bounds.max.x = box->max.x;
		bounds.max.y = box->max.y;
		bounds.max.z = box->max.z;
		bounds.min.x = box->min.x;
		bounds.min.y = box->min.y;
		bounds.min.z = box->min.z;
	}

	// FUNCTION: ENGINE 0x10665790
	void CollisionPlane::SetPlane(const void* description)
	{
		const math::Plane* source = static_cast<const math::Plane*>(description);
		math::AABB box;
		box.min.x = -1000.0f;
		box.min.y = -1000.0f;
		box.min.z = -1000.0f;
		box.max.x = 1000.0f;
		box.max.y = 1000.0f;
		box.max.z = 1000.0f;
		if (math::IsEqual(source->normal.x, 1.0f, 1e-5f))
		{
			bounds.max.x = math::WORLD_MIN - source->d;
		}
		else if (math::IsEqual(source->normal.y, 1.0f, 1e-5f))
		{
			bounds.max.y = math::WORLD_MIN - source->d;
		}
		else if (math::IsEqual(source->normal.z, 1.0f, 1e-5f))
		{
			bounds.max.z = math::WORLD_MIN - source->d;
		}
		else if (math::IsEqual(source->normal.x, -1.0f, 1e-5f))
		{
			bounds.max.x = source->d;
		}
		else if (math::IsEqual(source->normal.y, -1.0f, 1e-5f))
		{
			bounds.max.y = source->d;
		}
		else if (math::IsEqual(source->normal.z, -1.0f, 1e-5f))
		{
			bounds.max.z = source->d;
		}
		SetPlaneAndBox(source, &box);
	}

	// FUNCTION: ENGINE 0x10664C10
	// NONMATCHING: the engine builds the extents in a stack Vector and takes their absolute values through the x87 unit one at a time; the loads and sums of the transform are scheduled differently, 15.5 %
#ifdef NONMATCHING
	void CollisionCapsule::UpdateWorld(CollisionObject* object)
	{
		const float* m = &object->transform.m[0][0];
		float cy = localCentre.y;
		float cx = localCentre.x;
		float cz = localCentre.z;
		float dz = localDirection.z;
		float dx = localDirection.x;
		float dy = localDirection.y;
		float centreX = m[0] * cx + m[4] * cy + m[8] * cz + m[12];
		float centreY = m[1] * cx + m[5] * cy + m[9] * cz + m[13];
		float centreZ = m[2] * cx + m[6] * cy + m[10] * cz + m[14];
		float radius = capsule.radius;
		float directionX = dx * m[0] + dy * m[4] + dz * m[8];
		float directionY = dx * m[1] + dy * m[5] + dz * m[9];
		float directionZ = dx * m[2] + dy * m[6] + dz * m[10];
		float halfLength = capsule.halfLength;
		math::Vector scaled(directionX * halfLength, directionY * halfLength, directionZ * halfLength);
		math::Vector absolute(fabsf(scaled.x), fabsf(scaled.y), fabsf(scaled.z));
		float extentX = absolute.x + radius;
		float extentY = absolute.y + radius;
		float extentZ = absolute.z + radius;
		bounds.max.x = extentX + centreX;
		bounds.max.z = extentZ + centreZ;
		bounds.max.y = extentY + centreY;
		bounds.min.x = centreX - extentX;
		bounds.min.y = centreY - extentY;
		bounds.min.z = centreZ - extentZ;
		capsule.centre.x = centreX;
		capsule.centre.y = centreY;
		capsule.centre.z = centreZ;
		capsule.direction.x = directionX;
		capsule.direction.y = directionY;
		capsule.direction.z = directionZ;
	}
#endif

	// FUNCTION: ENGINE 0x10665AE0
	CollisionPlane::CollisionPlane(const void* description) :
		CollisionVolume(5)
	{
		SetPlane(description);
	}

	// FUNCTION: ENGINE 0x10665B00
	CollisionPlane::CollisionPlane(const void* description, int unused) :
		CollisionVolume(5)
	{
		SetPlane(description);
	}

	// FUNCTION: ENGINE 0x10665930
	void CollisionPlane::Scale(const math::Vector* scale)
	{
		float values[4];
		values[0] = localPlane.normal.x;
		values[1] = localPlane.normal.y;
		values[2] = localPlane.normal.z;
		values[3] = sqrtf(scale->x * scale->x + scale->y * scale->y + scale->z * scale->z) * localPlane.d;
		SetPlane(values);
	}

	// FUNCTION: ENGINE 0x10664A10
	void CollisionHull::UpdateWorld(CollisionObject* object)
	{
		matrix = object->transform;
		inverse = matrix;
		inverse.Invert();
		world.Transform(local, object->transform);
		bounds.SetTransformed(matrix, localBox);
	}
}
