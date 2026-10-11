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
}
