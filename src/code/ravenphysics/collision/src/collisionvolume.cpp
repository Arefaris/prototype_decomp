// The collision volumes of the narrow phase: their head and the capsule, box, sphere and plane volumes (0x10663E30 -
// 0x10666800). The unit has no assert path of its own; the file name is a guess.
#include "code/math/worldbounds.h"
#include "code/math/mathutils.h"
#include "code/core/heap.h"
#include "code/ravenphysics/collision/collisionobject.h"
#include <algorithm>
#include <new>
#include <string.h>
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

	// FUNCTION: ENGINE 0x10663EB0
	void CollisionVolume::MarkDestroyed()
	{
		unknown3 = 0xAB;
	}

	// FUNCTION: ENGINE 0x10663EC0
	void CollisionVolume::Retain()
	{
		unknown3 += 1;
	}

	// FUNCTION: ENGINE 0x10663ED0
	void CollisionVolume::Release()
	{
		unknown3 -= 1;
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

	// FUNCTION: ENGINE 0x10664EB0
	// EQUIVALENT: the same operations in the same order; the engine keeps the helper axis in a stack vector and reads it back through a pointer, ours keeps it in registers, and the scaled products are scheduled differently, 29.0 %
	void CollisionCapsule::Scale(const math::Vector* scale)
	{
		math::Capsule local;
		GetLocalCapsule(&local);
		float length = (float)sqrt((double)(local.direction.x * local.direction.x + local.direction.z * local.direction.z + local.direction.y * local.direction.y));
		float limit = length * 0.9f;
		math::Vector reference;
		if (local.direction.x > math::WORLD_MIN - limit && limit > local.direction.x)
		{
			reference.x = 1.0f;
			reference.y = 0.0f;
			reference.z = 0.0f;
		}
		else
		{
			reference.x = 0.0f;
			reference.y = 0.0f;
			reference.z = 1.0f;
		}
		math::Vector across;
		across.Cross(reference, local.direction);
		across.x = scale->x * across.x;
		across.y = scale->y * across.y;
		across.z = scale->z * across.z;
		float acrossLength = (float)sqrt((double)(across.z * across.z + across.y * across.y + across.x * across.x));
		local.direction.x = scale->x * local.direction.x;
		local.direction.y = scale->y * local.direction.y;
		local.direction.z = scale->z * local.direction.z;
		local.radius = acrossLength * local.radius;
		float scaledLength = local.direction.Normalize();
		local.centre.x = scale->x * local.centre.x;
		local.centre.y = local.centre.y * scale->y;
		local.centre.z = scale->z * local.centre.z;
		local.halfLength = (local.halfLength / length) * scaledLength;
		SetCapsule(local);
	}

	// FUNCTION: ENGINE 0x10665060
	// EQUIVALENT: the same products and differences (the third axis is the second crossed with the first); the engine loads the six components in another order and keeps the sums in other registers, 85.2 %
	void CollisionOBB::SetOBB(const math::OBB& newBox)
	{
		math::OBB* world = &obb;
		*world = newBox;
		float bx = world->axis[1].x;
		float ax = world->axis[0].x;
		float bz = world->axis[1].z;
		float az = world->axis[0].z;
		float ay = world->axis[0].y;
		world->axis[2].y = ax * bz - bx * az;
		float by = world->axis[1].y;
		world->axis[2].z = ay * bx - by * ax;
		world->axis[2].x = by * az - ay * bz;
		Copy(localCentre, newBox.centre);
		Copy(localAxis0, newBox.axis[0]);
		Copy(localAxis1, newBox.axis[1]);
		newBox.GetAABB(bounds);
	}

	// FUNCTION: ENGINE 0x10665470
	// EQUIVALENT: the same calls and the same cross product; the engine reads the axes back through their pointers, ours addresses them from the box, and the products are scheduled differently, 42.9 %
	void CollisionOBB::Move(const math::Matrix& matrix)
	{
		math::OBB* world = &obb;
		matrix.Transform(world->centre, world->centre);
		matrix.Rotate(world->axis[0], world->axis[0]);
		matrix.Rotate(world->axis[1], world->axis[1]);
		float ax = world->axis[0].x;
		float bx = world->axis[1].x;
		float az = world->axis[0].z;
		float bz = world->axis[1].z;
		float by = world->axis[1].y;
		float ay = world->axis[0].y;
		math::Vector* third = &world->axis[2];
		third->x = ay * bz - by * az;
		third->y = bx * az - ax * bz;
		third->z = by * ax - ay * bx;
		third->NormalizeFast();
		UpdateBox();
	}

	// FUNCTION: ENGINE 0x10665550
	void CollisionSphere::Move(const math::Matrix& matrix)
	{
		matrix.Transform(sphere.centre, sphere.centre);
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

	// FUNCTION: ENGINE 0x10663EE0
	const math::Vector* CollisionVolume::GetPosition()
	{
		switch (type)
		{
		case 0:
		case 4:
			return &((CollisionCapsule*)this)->capsule.centre;
		case 1:
			return &((CollisionOBB*)this)->obb.centre;
		case 2:
			return &((CollisionSphere*)this)->sphere.centre;
		case 3:
			return &((CollisionVolume3*)this)->world;
		default:
			return &math::kZeroVector;
		case 6:
			return (const math::Vector*)&((CollisionVolume6*)this)->grid.matrix.m[3][0];
		}
	}

	// FUNCTION: ENGINE 0x10663F30
	const math::Vector* CollisionVolume::GetLocalPosition()
	{
		switch (type)
		{
		case 0:
		case 1:
		case 2:
		case 4:
			return &((CollisionCapsule*)this)->localCentre;
		case 3:
			return &((CollisionVolume3*)this)->world;
		default:
			return &math::kZeroVector;
		case 6:
			return (const math::Vector*)&((CollisionVolume6*)this)->grid.matrix.m[3][0];
		}
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

	// FUNCTION: ENGINE 0x106643E0
	// EQUIVALENT: the same products and sums in the same order; the engine loads the centre and the radius ahead of the first product and keeps the sums in registers, 10.3 %
	void CollisionSphere::UpdateWorld(CollisionObject* object)
	{
		float z = localCentre.z;
		float y = localCentre.y;
		float x = localCentre.x;
		const math::Matrix& m = object->transform;
		float worldX = m.m[1][0] * y + m.m[2][0] * z + x * m.m[0][0] + m.m[3][0];
		float worldY = m.m[0][1] * x + m.m[1][1] * y + m.m[2][1] * z + m.m[3][1];
		float radius = sphere.radius;
		float worldZ = m.m[0][2] * x + m.m[1][2] * y + m.m[2][2] * z + m.m[3][2];
		bounds.min.x = worldX - radius;
		bounds.min.y = worldY - radius;
		bounds.min.z = worldZ - radius;
		bounds.max.x = worldX + radius;
		bounds.max.y = worldY + radius;
		bounds.max.z = worldZ + radius;
		sphere.centre.x = worldX;
		sphere.centre.y = worldY;
		sphere.centre.z = worldZ;
	}

	// FUNCTION: ENGINE 0x106646E0
	// NONMATCHING: the loop is addressed through the index register and the comparisons' operand order differs, best 15.4 %
#ifdef NONMATCHING
	bool CollisionVolume::AreBoundsFinite()
	{
		const float* values = (const float*)this;
		for (int i = 0; i < 3; i++)
		{
			float low = values[i + 1];
			float high = values[i + 4];
			if (!(fabs(low) < 1e12f))
			{
				return false;
			}
			if (!(fabs(high) < 1e12f))
			{
				return false;
			}
			if (low > high)
			{
				return false;
			}
		}
		return true;
	}
#endif

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

	// FUNCTION: ENGINE 0x10665600
	CollisionOBB::CollisionOBB(const CollisionOBB& other) :
		CollisionVolume(other),
		localCentre(other.localCentre),
		localAxis0(other.localAxis0),
		localAxis1(other.localAxis1),
		obb(other.obb)
	{
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
	void CollisionVolume3::UpdateWorld(CollisionObject* object)
	{
		matrix = object->transform;
		inverse = matrix;
		inverse.Invert();
		world.Transform(local, object->transform);
		bounds.SetTransformed(matrix, localBox);
	}
}

namespace ravenphysics
{
	// The counter the grids' serial numbers are made from (0x1127D404)
	extern unsigned int gGridSerial;

	// FUNCTION: ENGINE 0x10662F50
	void BroadPhaseGrid::Quantize(unsigned short* cell, const math::Vector& point)
	{
		for (int i = 3; i--; )
		{
			float v = ((&point.x)[i] - (&bounds.min.x)[i]) * (&scale.x)[i];
			if (!(v >= 0.0f))
			{
				v = 0.0f;
			}
			if (v - 65535.0f >= 0.0f)
			{
				v = 65535.0f;
			}
			cell[i] = (unsigned short)(int)v;
		}
	}

	// FUNCTION: ENGINE 0x10662E50
	unsigned int GridFace::GetMaterial() const
	{
		return (flags >> 9) & 0x3f;
	}

	// FUNCTION: ENGINE 0x10662E60
	void BroadPhaseGrid::GetTriangle(unsigned short face, math::Vector* corners)
	{
		const GridFace* record = faces + face;
		Copy(corners[0], vertices[record->vertex[0]]);
		Copy(corners[1], vertices[record->vertex[1]]);
		Copy(corners[2], vertices[record->vertex[2]]);
	}

	// FUNCTION: ENGINE 0x10662ED0
	void BroadPhaseGrid::GetTriangleAndFace(unsigned short face, GridFace* faceOut, math::Vector* corners)
	{
		*faceOut = faces[face];
		Copy(corners[0], vertices[faceOut->vertex[0]]);
		Copy(corners[1], vertices[faceOut->vertex[1]]);
		Copy(corners[2], vertices[faceOut->vertex[2]]);
	}

	// FUNCTION: ENGINE 0x10662FB0
	void BroadPhaseGrid::ToGridUnits(math::Vector* out, const math::Vector* point)
	{
		for (int i = 3; i--; )
		{
			(&out->x)[i] = ((&point->x)[i] - (&bounds.min.x)[i]) * (&scale.x)[i];
		}
	}

	// FUNCTION: ENGINE 0x106636F0
	MeshMaterial* BroadPhaseGrid::GetMaterialOf(unsigned short face)
	{
		return materialsBegin + ((faces[face].flags >> 9) & 0x3f);
	}

	// FUNCTION: ENGINE 0x10665BE0
	MeshSlot::MeshSlot() :
		refCount(0),
		unknown4(0),
		unknown8(0),
		unknownC(0)
	{
	}

	// FUNCTION: ENGINE 0x10665BF0
	MeshSlot::~MeshSlot()
	{
		if (unknown4 != 0)
		{
			delete[] unknown4;
		}
		if (unknown8 != 0)
		{
			delete unknown8;
		}
	}

	// FUNCTION: ENGINE 0x10665C20
	void MeshSlot::AddRef()
	{
		refCount++;
	}

	// FUNCTION: ENGINE 0x10666290
	void MeshSlot::Release()
	{
		refCount--;
		if (refCount < 1)
		{
			refCount = 0xbaad;
			delete this;
		}
	}

	// FUNCTION: ENGINE 0x10665C50
	BroadPhaseGrid& BroadPhaseGrid::Assign(const BroadPhaseGrid& other)
	{
		volume = other.volume;
		matrix = other.matrix;
		inverse = other.inverse;
		serial = other.serial;
		transformed = other.transformed;
		unknown8C = other.unknown8C;
		unknown90 = other.unknown90;
		unknown92 = other.unknown92;
		tree = other.tree;
		faces = other.faces;
		vertices = other.vertices;
		bounds.max.x = other.bounds.max.x;
		bounds.max.y = other.bounds.max.y;
		bounds.max.z = other.bounds.max.z;
		bounds.min.x = other.bounds.min.x;
		bounds.min.y = other.bounds.min.y;
		bounds.min.z = other.bounds.min.z;
		scale.x = other.scale.x;
		scale.y = other.scale.y;
		scale.z = other.scale.z;
		unknownC4 = other.unknownC4;
		unknownC8 = other.unknownC8;
		materialsBegin = other.materialsBegin;
		materialsEnd = other.materialsEnd;
		return *this;
	}

	// FUNCTION: ENGINE 0x106662C0
	// EQUIVALENT: the same stores and calls in the same order; the engine loads the first matrix's address after the first two stores and pushes the size of the slot after the box, ours ahead of them, 85.8 %
	BroadPhaseGrid::BroadPhaseGrid()
	{
		materialsBegin = 0;
		materialsEnd = 0;
		volume = 0;
		matrix.Identity();
		inverse.Identity();
		transformed = false;
		gGridSerial += 0x3d70000;
		serial = gGridSerial;
		unknown8C = 0;
		unknown90 = 0;
		unknown92 = 0;
		tree = 0;
		faces = 0;
		vertices = 0;
		bounds.Reset();
		scale.z = 0.0f;
		scale.y = 0.0f;
		scale.x = 0.0f;
		unknownC4 = 0.0f;
		unknownC8 = false;
		slot = new MeshSlot;
		slot->AddRef();
		unknownE4 = 0;
		unknownE8 = 0;
		unknownEC = 0;
	}

	// FUNCTION: ENGINE 0x106663D0
	BroadPhaseGrid::BroadPhaseGrid(const BroadPhaseGrid& other)
	{
		materialsBegin = 0;
		materialsEnd = 0;
		Assign(other);
		gGridSerial += 0x3d70000;
		serial = gGridSerial;
		slot = other.slot;
		slot->AddRef();
		unknownE4 = 0;
		unknownE8 = 0;
		unknownEC = 0;
	}

	// FUNCTION: ENGINE 0x10666430
	void BroadPhaseGrid::Destroy()
	{
		unsigned int owners = slot->refCount;
		slot->Release();
		slot = 0;
		if (owners == 1)
		{
			if (vertices != 0)
			{
				core::FreeAligned(vertices);
			}
			if (tree != 0)
			{
				core::FreeAligned(tree);
			}
			if (faces != 0)
			{
				core::FreeAligned(faces);
			}
			if (materialsBegin != 0)
			{
				delete[] materialsBegin;
			}
		}
		if (unknownE4 != 0)
		{
			delete[] unknownE4;
		}
		if (unknownEC != 0)
		{
			delete[] unknownEC;
		}
	}

	// FUNCTION: ENGINE 0x10665B20
	void CollisionVolume6::UpdateBox()
	{
		if (grid.transformed)
		{
			bounds.SetTransformed(grid.matrix, grid.bounds);
		}
		else
		{
			bounds.max.x = grid.bounds.max.x;
			bounds.max.y = grid.bounds.max.y;
			bounds.max.z = grid.bounds.max.z;
			bounds.min.x = grid.bounds.min.x;
			bounds.min.y = grid.bounds.min.y;
			bounds.min.z = grid.bounds.min.z;
		}
	}

	// FUNCTION: ENGINE 0x10665BD0
	void CollisionVolume6::SetUnknown120(int value)
	{
		unknown120 = value;
	}

	// FUNCTION: ENGINE 0x10665DF0
	void CollisionObjectTable::AddMesh(CollisionVolume6* mesh, CollisionHandle* newHandle)
	{
		Add(mesh, newHandle);
	}

	// FUNCTION: ENGINE 0x106661E0
	void CollisionVolume6::SetMeshFilter(const CollisionFilter* filter)
	{
		for (MeshMaterial* material = grid.materialsBegin; material != grid.materialsEnd; material++)
		{
			material->filter = filter->unknown0;
			material->filter2 = filter->unknown4;
		}
	}

	// FUNCTION: ENGINE 0x10666210
	void CollisionVolume6::SetMeshFilterBits(unsigned int mask, bool set)
	{
		for (MeshMaterial* material = grid.materialsBegin; material != grid.materialsEnd; material++)
		{
			if (set)
			{
				material->filter |= mask;
			}
			else
			{
				material->filter &= ~mask;
			}
		}
	}

	// FUNCTION: ENGINE 0x10666250
	void CollisionVolume6::SetMeshFilterBits2(unsigned int mask, bool set)
	{
		for (MeshMaterial* material = grid.materialsBegin; material != grid.materialsEnd; material++)
		{
			if (set)
			{
				material->filter2 |= mask;
			}
			else
			{
				material->filter2 &= ~mask;
			}
		}
	}

	// Whether the rows of a matrix are those of the identity matrix, by the first three components (inlined by the
	// engine in both updates of a mesh)
	__forceinline bool RowsDiffer(const math::Matrix* matrix)
	{
		const math::Matrix& identity = math::Matrix::IDENTITY;
		bool differs = math::VectorsDiffer(math::Vector(matrix->m[0][0], matrix->m[0][1], matrix->m[0][2]),
			math::Vector(identity.m[0][0], identity.m[0][1], identity.m[0][2]));
		if (!differs)
		{
			differs = math::VectorsDiffer(math::Vector(matrix->m[1][0], matrix->m[1][1], matrix->m[1][2]),
				math::Vector(identity.m[1][0], identity.m[1][1], identity.m[1][2]));
		}
		if (!differs)
		{
			differs = math::VectorsDiffer(math::Vector(matrix->m[2][0], matrix->m[2][1], matrix->m[2][2]),
				math::Vector(identity.m[2][0], identity.m[2][1], identity.m[2][2]));
		}
		if (!differs)
		{
			differs = math::VectorsDiffer(math::Vector(matrix->m[3][0], matrix->m[3][1], matrix->m[3][2]),
				math::Vector(identity.m[3][0], identity.m[3][1], identity.m[3][2]));
		}
		return differs;
	}

	// FUNCTION: ENGINE 0x10665E20
	// EQUIVALENT: the engine copies the rows into two reused 12-byte stack slots, ours takes new slots for every copy (frame 0x60 against 0x18); everything else is the same, 89.5 %
	void CollisionVolume6::UpdateWorld(CollisionObject* object)
	{
		grid.matrix = object->transform;
		grid.inverse = grid.matrix;
		grid.inverse.InvertOrthonormal();
		grid.transformed = RowsDiffer(&object->transform);
		UpdateBox();
	}

	// FUNCTION: ENGINE 0x10666000
	// EQUIVALENT: the engine copies the rows into two reused 12-byte stack slots, ours takes new slots for every copy (frame 0x60 against 0x18); everything else is the same, 89.5 %
	void CollisionVolume6::MultiplyWorld(const math::Matrix& matrix)
	{
		grid.matrix.Multiply(grid.matrix, matrix);
		grid.inverse = grid.matrix;
		grid.inverse.InvertOrthonormal();
		grid.transformed = RowsDiffer(&matrix);
		UpdateBox();
	}

	// FUNCTION: ENGINE 0x10664B20
	CollisionVolume4::CollisionVolume4(const CollisionVolume4& other) :
		CollisionVolume(other),
		unknown24(other.unknown24),
		unknown28(other.unknown28),
		unknown2C(other.unknown2C),
		unknown30(other.unknown30),
		unknown34(other.unknown34),
		unknown38(other.unknown38),
		unknown3C(other.unknown3C),
		unknown40(other.unknown40),
		unknown44(other.unknown44),
		unknown48(other.unknown48),
		unknown4C(other.unknown4C),
		unknown50(other.unknown50),
		unknown54(other.unknown54),
		unknown58(other.unknown58),
		materials(other.materials)
	{
	}

	// FUNCTION: ENGINE 0x10664740
	const char* CollisionVolume::GetTypeName()
	{
		switch (type)
		{
		case 0:
			return "Type_Capsule";
		case 1:
			return "Type_OBB";
		case 2:
			return "Type_Sphere";
		case 3:
			return "Type_ConvexHull";
		case 4:
			return "Type_Cylinder";
		case 6:
			return "Type_Mesh";
		case 5:
			return "Type_Plane";
		}
		return "Unknown volume type";
	}

	// FUNCTION: ENGINE 0x10664660
	void CollisionVolume::Print()
	{
		PrintAABB(bounds);
		switch (type)
		{
		case 0:
			static_cast<CollisionCapsule*>(this)->Print();
			break;
		case 1:
			static_cast<CollisionOBB*>(this)->Print();
			break;
		case 2:
			static_cast<CollisionSphere*>(this)->Print();
			break;
		case 3:
			static_cast<CollisionVolume6*>(this)->DumpHull();
			break;
		case 6:
			static_cast<CollisionVolume6*>(this)->PrintMesh();
			break;
		case 5:
			static_cast<CollisionPlane*>(this)->Print();
			break;
		}
	}

	// FUNCTION: ENGINE 0x10665690
	void CollisionVolume::UpdateBounds(CollisionObject* object)
	{
		switch (type)
		{
		case 0:
			static_cast<CollisionCapsule*>(this)->UpdateWorld(object);
			break;
		case 1:
			static_cast<CollisionOBB*>(this)->UpdateWorld(object);
			break;
		case 2:
			static_cast<CollisionSphere*>(this)->UpdateWorld(object);
			break;
		case 3:
			static_cast<CollisionVolume3*>(this)->UpdateWorld(object);
			break;
		case 4:
			UpdateBounds4(object);
			break;
		case 6:
			static_cast<CollisionVolume6*>(this)->UpdateWorld(object);
			break;
		case 5:
			static_cast<CollisionPlane*>(this)->UpdateWorld(object);
			break;
		}
	}

	// FUNCTION: ENGINE 0x10665A90
	void CollisionVolume::SetQuery(const void* query)
	{
		const math::Vector* scale = static_cast<const math::Vector*>(query);
		switch (type)
		{
		case 0:
			static_cast<CollisionCapsule*>(this)->Scale(scale);
			break;
		case 1:
			static_cast<CollisionOBB*>(this)->Scale(scale);
			break;
		case 2:
			static_cast<CollisionSphere*>(this)->Scale(scale);
			break;
		case 3:
			static_cast<CollisionVolume3*>(this)->Scale(scale);
			break;
		case 4:
			ScaleCylinder(scale);
			break;
		case 5:
			static_cast<CollisionPlane*>(this)->Scale(scale);
			break;
		case 6:
			static_cast<CollisionVolume6*>(this)->Scale(scale);
			break;
		}
	}

	// FUNCTION: ENGINE 0x10665990
	CollisionVolume* CollisionVolume::Clone()
	{
		switch (type)
		{
		case 0:
			return new CollisionCapsule(*static_cast<CollisionCapsule*>(this));
		case 1:
			return new CollisionOBB(*static_cast<CollisionOBB*>(this));
		case 2:
			return new CollisionSphere(*static_cast<CollisionSphere*>(this));
		case 3:
			return new CollisionVolume3(*static_cast<CollisionVolume3*>(this));
		case 4:
			return new CollisionVolume4(*static_cast<CollisionVolume4*>(this));
		case 5:
			return new CollisionPlane(*static_cast<CollisionPlane*>(this));
		case 6:
			return new CollisionVolume6(*static_cast<CollisionVolume6*>(this));
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10664120
	void CollisionVolume::SetFilter(const CollisionFilter* newFilter)
	{
		filter.unknown0 = newFilter->unknown0;
		filter.unknown4 = newFilter->unknown4;
		if (type == 6)
		{
			static_cast<CollisionVolume6*>(this)->SetMeshFilter(newFilter);
		}
	}

	// FUNCTION: ENGINE 0x10664140
	void CollisionVolume::SetFilterBits(unsigned int mask, bool set)
	{
		if (set)
		{
			filter.unknown0 |= mask;
		}
		else
		{
			filter.unknown0 &= ~mask;
		}
		if (type == 6)
		{
			static_cast<CollisionVolume6*>(this)->SetMeshFilterBits(mask, set);
		}
	}

	// FUNCTION: ENGINE 0x10664170
	void CollisionVolume::SetFilterBits2(unsigned int mask, bool set)
	{
		if (set)
		{
			filter.unknown4 |= mask;
		}
		else
		{
			filter.unknown4 &= ~mask;
		}
		if (type == 6)
		{
			static_cast<CollisionVolume6*>(this)->SetMeshFilterBits2(mask, set);
		}
	}

	// FUNCTION: ENGINE 0x10663FE0
	bool CollisionVolume::CastVolume(const void* query, math::Vector* point, float* distance)
	{
		const math::Vector* from = static_cast<const math::Vector*>(query);
		switch (type)
		{
		case 0:
			static_cast<CollisionCapsule*>(this)->capsule.GetDirection(*from, *point, *distance);
			{
				math::Vector negated(-point->x, -point->y, -point->z);
				point->x = negated.x;
				point->y = negated.y;
				point->z = negated.z;
			}
			return true;
		case 1:
			static_cast<CollisionOBB*>(this)->obb.GetDirection(*from, *point, *distance);
			{
				math::Vector negated(-point->x, -point->y, -point->z);
				point->x = negated.x;
				point->y = negated.y;
				point->z = negated.z;
			}
			return true;
		case 2:
			static_cast<CollisionSphere*>(this)->sphere.GetDirection(*from, *point, *distance);
			{
				math::Vector negated(-point->x, -point->y, -point->z);
				point->x = negated.x;
				point->y = negated.y;
				point->z = negated.z;
			}
			return true;
		case 4:
			static_cast<CollisionVolume4*>(this)->materials.GetDirection(query, point, distance);
			return true;
		case 3:
			static_cast<CollisionVolume3*>(this)->GetDirection(query, point, distance);
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x106664D0
	CollisionVolume6::CollisionVolume6() :
		CollisionVolume(6),
		unknown120(0)
	{
		grid.volume = this;
		gCollisionObjectTable->AddMesh(this, &handle);
	}

	// FUNCTION: ENGINE 0x10666510
	CollisionVolume6::CollisionVolume6(const CollisionVolume6& other) :
		CollisionVolume(other),
		grid(other.grid),
		unknown120(other.unknown120)
	{
		grid.volume = this;
		if (unknown120 != 0)
		{
			grid.unknownE4 = new unsigned short[grid.unknown92];
			memcpy(grid.unknownE4, other.grid.unknownE4, grid.unknown92 * 2);
			grid.unknownE8 = other.grid.unknownE8;
			grid.unknownEC = new MeshRecord[grid.unknownE8];
			memcpy(grid.unknownEC, other.grid.unknownEC, grid.unknownE8 * sizeof(MeshRecord));
		}
		gCollisionObjectTable->AddMesh(this, &handle);
	}

	// FUNCTION: ENGINE 0x106665F0
	CollisionVolume6::CollisionVolume6(const BroadPhaseGrid& newGrid) :
		CollisionVolume(6),
		grid(newGrid),
		unknown120(0)
	{
		grid.volume = this;
		gCollisionObjectTable->AddMesh(this, &handle);
		UpdateBox();
	}

	// FUNCTION: ENGINE 0x10666640
	CollisionVolume6::~CollisionVolume6()
	{
		gCollisionObjectTable->Remove(&handle);
		unknown120 = 0;
		grid.Destroy();
	}
}

namespace ravenphysics
{
	// A list of 16-bit numbers (name and layout are guesses)
	struct NumberList
	{
		// Sorts the numbers and drops the repeated ones (0x10666E80)
		void SortUnique();

		unsigned char unknown0[8];
		unsigned short* begin;     // 0x08
		unsigned short* end;       // 0x0C
	};

	// Sorts a range of 16-bit numbers (0x10666E60; name guess)
	void SortNumbers(unsigned short* first, unsigned short* last);

	// FUNCTION: ENGINE 0x10666E60
	void SortNumbers(unsigned short* first, unsigned short* last)
	{
		std::sort(first, last);
	}

	// FUNCTION: ENGINE 0x10666E80
	void NumberList::SortUnique()
	{
		if (begin != end)
		{
			SortNumbers(begin, end);
			unsigned short count = (unsigned short)(end - begin);
			unsigned short last = begin[0];
			unsigned short kept = 1;
			for (unsigned short i = 1; i < count; i++)
			{
				if (last != begin[i])
				{
					last = begin[i];
					begin[kept] = last;
					kept++;
				}
			}
			end = begin + kept;
		}
	}
}

// The unit's instances of the toolchain's <algorithm> for unsigned short (it sorts and de-duplicates lists of
// face numbers); the compiler reproduces every one of them
// FUNCTION: ENGINE 0x106666D0
template unsigned short* std::_Checked_base<unsigned short*>(unsigned short*&, std::_Unchanged_checked_iterator_base_type_tag);

// FUNCTION: ENGINE 0x106666E0
template struct std::pair<unsigned short*, unsigned short*>;

// FUNCTION: ENGINE 0x10666700
template int* std::_Dist_type<unsigned short*>(unsigned short*);

// FUNCTION: ENGINE 0x10666710
template unsigned short* std::_Val_type<unsigned short*>(unsigned short*);

// FUNCTION: ENGINE 0x10666720
template void std::swap<unsigned short>(unsigned short&, unsigned short&);

// FUNCTION: ENGINE 0x10666740
template void std::_Push_heap<unsigned short*, int, unsigned short>(unsigned short*, int, int, unsigned short);

// FUNCTION: ENGINE 0x106667A0
template std::random_access_iterator_tag std::_Iter_random<unsigned short*, unsigned short*>(unsigned short* const&, unsigned short* const&);

// FUNCTION: ENGINE 0x106667B0
template std::_Scalar_ptr_iterator_tag std::_Ptr_cat<unsigned short*, unsigned short*>(unsigned short*&, unsigned short*&);

// FUNCTION: ENGINE 0x106667C0
template unsigned short* std::_Copy_backward_opt<unsigned short*, unsigned short*, std::random_access_iterator_tag>(unsigned short*, unsigned short*, unsigned short*, std::random_access_iterator_tag, std::_Scalar_ptr_iterator_tag, std::_Range_checked_iterator_tag);

// FUNCTION: ENGINE 0x10666830
template unsigned short* std::_Checked_base<unsigned short*>(unsigned short*&);

// FUNCTION: ENGINE 0x10666840
template void std::iter_swap<unsigned short*, unsigned short*>(unsigned short*, unsigned short*);

// FUNCTION: ENGINE 0x10666860
template void std::_Med3<unsigned short*>(unsigned short*, unsigned short*, unsigned short*);

// FUNCTION: ENGINE 0x106668B0
template void std::_Adjust_heap<unsigned short*, int, unsigned short>(unsigned short*, int, int, unsigned short);

// FUNCTION: ENGINE 0x10666920
template unsigned short* stdext::unchecked_copy_backward<unsigned short*, unsigned short*>(unsigned short*, unsigned short*, unsigned short*);

// FUNCTION: ENGINE 0x10666950
template void std::_Pop_heap<unsigned short*, int, unsigned short>(unsigned short*, unsigned short*, unsigned short*, unsigned short, int*);

// FUNCTION: ENGINE 0x10666980
template void std::_Median<unsigned short*>(unsigned short*, unsigned short*, unsigned short*);

// FUNCTION: ENGINE 0x10666A10
template void std::_Make_heap<unsigned short*, int, unsigned short>(unsigned short*, unsigned short*, int*, unsigned short*);

// FUNCTION: ENGINE 0x10666A50
template void std::_Insertion_sort1<unsigned short*, unsigned short>(unsigned short*, unsigned short*, unsigned short*);

// FUNCTION: ENGINE 0x10666AF0
template void std::_Pop_heap_0<unsigned short*, unsigned short>(unsigned short*, unsigned short*, unsigned short*);

// FUNCTION: ENGINE 0x10666B20
template std::pair<unsigned short*, unsigned short*> std::_Unguarded_partition<unsigned short*>(unsigned short*, unsigned short*);

// FUNCTION: ENGINE 0x10666CB0
template void std::_Insertion_sort<unsigned short*>(unsigned short*, unsigned short*);

// FUNCTION: ENGINE 0x10666CD0
template void std::pop_heap<unsigned short*>(unsigned short*, unsigned short*);

// FUNCTION: ENGINE 0x10666D10
template void std::_Sort_heap<unsigned short*>(unsigned short*, unsigned short*);

// FUNCTION: ENGINE 0x10666D60
template void std::sort_heap<unsigned short*>(unsigned short*, unsigned short*);

// FUNCTION: ENGINE 0x10666D70
template void std::_Sort<unsigned short*, int>(unsigned short*, unsigned short*, int);

// FUNCTION: ENGINE 0x10666E40
template void std::sort<unsigned short*>(unsigned short*, unsigned short*);

