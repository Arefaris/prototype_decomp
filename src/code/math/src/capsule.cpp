#include <math.h>

#include "code/math/aabb.h"
#include "code/math/capsule.h"
#include "code/math/mathutils.h"
#include "code/math/matrix.h"
#include "code/math/segment.h"

namespace math
{
	// FUNCTION: ENGINE 0x107DC470
	void Capsule::Transform(const Matrix& m)
	{
		centre.Transform(m);
		direction.Rotate(m);
	}

	// FUNCTION: ENGINE 0x107DC490
	void Capsule::Transform(const Matrix& m, const Capsule& src)
	{
		m.Transform(src.centre, centre);
		m.Rotate(src.direction, direction);
		halfLength = src.halfLength;
		radius = src.radius;
	}

	// FUNCTION: ENGINE 0x107DC4D0
	void Capsule::GetSegment(Segment& out) const
	{
		float dx = direction.x * halfLength;
		float dy = direction.y * halfLength;
		float dz = direction.z * halfLength;
		out.start.x = centre.x - dx;
		out.start.y = centre.y - dy;
		out.start.z = centre.z - dz;
		out.end.x = centre.x + dx;
		out.end.y = centre.y + dy;
		out.end.z = centre.z + dz;
	}

	// FUNCTION: ENGINE 0x107DC550
	// EQUIVALENT: as Cylinder::Contains: the original adds the z terms before the y terms (commutative) and offsets z
	// first (68 %)
	bool Capsule::Contains(const Vector& p) const
	{
		Vector d;
		d.Sub(p, centre);
		float t = d.Dot(direction);
		if (t > halfLength)
		{
			t = halfLength;
		}
		else if (t < -halfLength)
		{
			t = -halfLength;
		}
		Vector offset;
		offset.Set(direction.x * t, direction.y * t, direction.z * t);
		d.Sub(d, offset);
		return d.Dot(d) < radius * radius;
	}

	// FUNCTION: ENGINE 0x107DC760
	void Capsule::GetAABB(AABB& out) const
	{
		Segment segment;
		GetSegment(segment);
		segment.GetAABB(out);
		out.max.x += radius;
		out.max.y += radius;
		out.max.z += radius;
		out.min.x -= radius;
		out.min.y -= radius;
		out.min.z -= radius;
	}

	// FUNCTION: ENGINE 0x107DC7E0
	void Cylinder::Transform(const Matrix& m)
	{
		centre.Transform(m);
		direction.Rotate(m);
	}

	// FUNCTION: ENGINE 0x107DC800
	// EQUIVALENT: the original adds the z product before the y product in both dot products and subtracts z before
	// y (commutative, the same results); every inline / direct form tried gives y first (88 %)
	bool Cylinder::Contains(const Vector& p) const
	{
		Vector d;
		d.Sub(p, centre);
		float t = d.Dot(direction);
		if (fabsf(t) > halfLength)
		{
			return false;
		}
		Vector offset;
		offset.Set(direction.x * t, direction.y * t, direction.z * t);
		d.Sub(d, offset);
		return d.Dot(d) < radius * radius;
	}

	// FUNCTION: ENGINE 0x107DCC10
	void Cylinder::GetAABB(AABB& out) const
	{
		// Per axis: the end discs' extent sqrt(1 - a^2) * radius plus the axis' a * halfLength, a = |direction[i]|
		// clamped to 1; one variable reused for the three axes gives the original's frame
		Vector e;
		float a = Min(fabsf(direction.x), 1.0f);
		e.x = sqrtf(1.0f - a * a) * radius + halfLength * a;
		a = Min(fabsf(direction.y), 1.0f);
		e.y = sqrtf(1.0f - a * a) * radius + halfLength * a;
		a = Min(fabsf(direction.z), 1.0f);
		e.z = sqrtf(1.0f - a * a) * radius + halfLength * a;
		out.min.Sub(centre, e);
		out.max.Add(centre, e);
	}
}
