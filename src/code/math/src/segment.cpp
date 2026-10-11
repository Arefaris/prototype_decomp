#include <math.h>

#include "code/math/aabb.h"
#include "code/math/mathconstants.h"
#include "code/math/segment.h"
#include "code/math/sphere.h"

namespace math
{
	// FUNCTION: ENGINE 0x107D6F40
	void Segment::GetAABB(AABB& out) const
	{
		for (int i = 3; i--; )
		{
			if ((&end.x)[i] > (&start.x)[i])
			{
				(&out.min.x)[i] = (&start.x)[i];
				(&out.max.x)[i] = (&end.x)[i];
			}
			else
			{
				(&out.max.x)[i] = (&start.x)[i];
				(&out.min.x)[i] = (&end.x)[i];
			}
		}
	}

	// FUNCTION: ENGINE 0x107D6F90
	float Segment::DistanceSquared(const Vector& p, float t, float lengthSquared) const
	{
		if (t <= EPSILON_FLOAT)
		{
			Vector d;
			d.Sub(p, start);
			return (d.y * d.y + d.x * d.x) + d.z * d.z;
		}
		if (t >= lengthSquared)
		{
			Vector d;
			d.Sub(p, end);
			return (d.x * d.x + d.z * d.z) + d.y * d.y;
		}
		float dx = p.x - start.x;
		float dy = p.y - start.y;
		float dz = p.z - start.z;
		return dx * dx + dy * dy + dz * dz - t * (t / lengthSquared);
	}

	// FUNCTION: ENGINE 0x107D7020
	float Segment::ClosestPoint(const Vector& p, Vector& out) const
	{
		Vector d;
		d.Sub(end, start);
		Vector v;
		v.Sub(p, start);
		float t = d.y * v.y + (d.x * v.x + d.z * v.z);
		if (t <= EPSILON_FLOAT)
		{
			out.x = start.x;
			out.y = start.y;
			out.z = start.z;
		}
		else
		{
			float lengthSquared = (d.z * d.z + d.x * d.x) + d.y * d.y;
			if (t >= lengthSquared)
			{
				out.x = end.x;
				out.y = end.y;
				out.z = end.z;
				float dx = p.x - end.x;
				float dy = p.y - end.y;
				float dz = p.z - end.z;
				return dx * dx + dy * dy + dz * dz;
			}
			out.x = start.x;
			out.y = start.y;
			out.z = start.z;
			t /= lengthSquared;
			out.x += d.x * t;
			out.y += d.y * t;
			out.z += d.z * t;
			v.Sub(p, out);
		}
		return (v.y * v.y + v.z * v.z) + v.x * v.x;
	}

	// FUNCTION: ENGINE 0x107D7190
	float Segment::ClosestPoint(const Vector& p, float t, float lengthSquared, Vector& out) const
	{
		if (t <= EPSILON_FLOAT)
		{
			out.x = start.x;
			out.y = start.y;
			out.z = start.z;
			float dx = p.x - start.x;
			float dy = p.y - start.y;
			float dz = p.z - start.z;
			return (dx * dx + dy * dy) + dz * dz;
		}
		if (t >= lengthSquared)
		{
			out.x = end.x;
			out.y = end.y;
			out.z = end.z;
			float dx = p.x - end.x;
			float dy = p.y - end.y;
			float dz = p.z - end.z;
			return (dx * dx + dz * dz) + dy * dy;
		}
		t /= lengthSquared;
		out.x = start.x;
		out.y = start.y;
		out.z = start.z;
		Vector d;
		d.Sub(end, start);
		out.x += d.x * t;
		out.y += d.y * t;
		out.z += d.z * t;
		Vector v;
		v.Sub(p, out);
		return (v.y * v.y + v.z * v.z) + v.x * v.x;
	}

	// FUNCTION: ENGINE 0x107D72D0
	float Segment::Parameter(const Vector& p) const
	{
		Vector d;
		d.Sub(end, start);
		Vector v;
		v.Sub(p, start);
		return (v.y * d.y + (d.z * v.z + d.x * v.x)) / ((d.x * d.x + d.y * d.y) + d.z * d.z);
	}

	// FUNCTION: ENGINE 0x107D7380
	void Segment::GetSphere(Sphere& out) const
	{
		Vector d;
		d.Sub(start, end);
		Vector sum;
		sum.Set(start.x + end.x, end.y + start.y, end.z + start.z);
		out.centre.Set(sum.x * 0.5f, sum.y * 0.5f, sum.z * 0.5f);
		out.radius = sqrtf((d.y * d.y + d.z * d.z) + d.x * d.x);
	}

	// FUNCTION: ENGINE 0x107D7420
	// EQUIVALENT: the original adds z^2 + x^2 in the first branch, we get x^2 + z^2 (commutative, the same result);
	// no grouping or operand order of that sum changes the pair's load order (99.4 %)
	float Segment::DistanceSquared(const Vector& p) const
	{
		Vector d;
		d.Sub(end, start);
		Vector v;
		v.Sub(p, start);
		float t = (d.z * v.z + d.x * v.x) + v.y * d.y;
		if (t <= EPSILON_FLOAT)
		{
			return (v.x * v.x + v.z * v.z) + v.y * v.y;
		}
		float lengthSquared = (d.y * d.y + d.x * d.x) + d.z * d.z;
		if (t >= lengthSquared)
		{
			float dx = p.x - end.x;
			float dy = p.y - end.y;
			float dz = p.z - end.z;
			return dx * dx + dy * dy + dz * dz;
		}
		t /= lengthSquared;
		Vector projection;
		projection.Set(d.x * t, d.y * t, d.z * t);
		Vector w;
		w.Sub(v, projection);
		return (w.y * w.y + w.z * w.z) + w.x * w.x;
	}

	// FUNCTION: ENGINE 0x107D7570
	float Segment::DistanceSquaredToLine(const Vector& p) const
	{
		Vector d;
		d.Sub(end, start);
		Vector v;
		v.Sub(p, start);
		float t = (d.y * v.y + (d.z * v.z + d.x * v.x)) / ((d.x * d.x + d.y * d.y) + d.z * d.z);
		Vector projection;
		projection.Set(d.x * t, d.y * t, d.z * t);
		Vector w;
		w.Sub(v, projection);
		return (w.y * w.y + w.z * w.z) + w.x * w.x;
	}

	// FUNCTION: ENGINE 0x107D7650
	// EQUIVALENT: the original squares d.z before d.x for the denominator (dz^2 + dx^2, commutative); we get the
	// two in swapped registers (98.6 %)
	float Segment::ClosestPointOnLine(const Vector& p, Vector& out) const
	{
		Vector d;
		d.Sub(end, start);
		Vector v;
		v.Sub(p, start);
		float t = ((v.z * d.z + d.x * v.x) + d.y * v.y) / ((d.x * d.x + d.z * d.z) + d.y * d.y);
		Vector projection;
		projection.Set(d.x * t, d.y * t, d.z * t);
		Vector w;
		w.Sub(v, projection);
		// The closest point is p - w
		out.x = p.x;
		out.y = p.y;
		out.z = p.z;
		out.x -= w.x;
		out.y -= w.y;
		out.z -= w.z;
		return (w.y * w.y + w.z * w.z) + w.x * w.x;
	}

	// FUNCTION: ENGINE 0x107D80C0
	// EQUIVALENT: same operations; the original keeps e.x, d.y, d.z in xmm1, xmm5, xmm6 (we get xmm6, xmm1, xmm5)
	// and multiplies e.x * d.y where we get d.y * e.x (76 %)
	float Segment::LineDistanceSquared(const Segment& other) const
	{
		Vector d;
		d.Sub(end, start);
		Vector e;
		e.Sub(other.end, other.start);
		Vector n;
		n.Cross(d, e);
		float nn = (n.y * n.y + n.z * n.z) + n.x * n.x;
		if (nn < EPSILON_SMALL)
		{
			return DistanceSquaredToLine(other.start);
		}
		Vector w;
		w.Sub(other.start, start);
		float t = (w.z * n.z + w.y * n.y) + w.x * n.x;
		return t * (t / nn);
	}
}
