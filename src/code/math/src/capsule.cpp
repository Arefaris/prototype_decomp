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

	// FUNCTION: ENGINE 0x107DC8C0
	// EQUIVALENT: same operations in the same order (26.7 %); the original's frame is 0x1c (ours 0x28), it reloads
	// the direction components between the products of the cap branch and keeps r in registers
	void Cylinder::GetDirection(const Vector& p, Vector& out, float& distance) const
	{
		Vector d;
		d.Sub(p, centre);
		float t = direction.Dot(d);
		float at = fabsf(t);
		if (at > halfLength)
		{
			float h = (t > 0.0f) ? halfLength : -halfLength;
			float k = h - t;
			float qx = direction.x * k + d.x;
			float qy = direction.y * k + d.y;
			float qz = direction.z * k + d.z;
			// q: d moved onto the cap's plane; c: the cap's centre (both relative to centre)
			Vector c;
			c.Set(direction.x * h, direction.y * h, direction.z * h);
			Vector r;
			r.Set(qx - c.x, qy - c.y, qz - c.z);
			float lengthSquared = r.z * r.z + r.y * r.y + r.x * r.x;
			// Outside the cap's disc: pulled back onto its rim
			if (lengthSquared > radius * radius)
			{
				r.Scale(radius / sqrtf(lengthSquared));
				qx = r.x + c.x;
				qy = r.y + c.y;
				qz = r.z + c.z;
			}
			out.Set(d.x - qx, d.y - qy, d.z - qz);
			distance = out.Normalize();
			return;
		}
		// Beside the side wall: away from the axis
		out.Set(d.x - direction.x * t, d.y - direction.y * t, d.z - direction.z * t);
		float length = out.Normalize();
		distance = length - radius;
		if (length - radius < 0.0f)
		{
			// Inside: through the nearer cap when that is closer than the wall
			float e = halfLength - at;
			if (e + length < radius)
			{
				float h = (t > 0.0f) ? e : -e;
				out.Set(direction.x * h + d.x - d.x, direction.y * h + d.y - d.y, direction.z * h + d.z - d.z);
				distance = -out.Normalize();
				return;
			}
			// On the axis: any direction perpendicular to it
			if (length == 0.0f)
			{
				out.Set(direction.y * -direction.y - direction.z * direction.x, direction.z * direction.z - direction.x * -direction.y,
					direction.x * direction.x - direction.y * direction.z);
				out.NormalizeFast();
			}
		}
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
