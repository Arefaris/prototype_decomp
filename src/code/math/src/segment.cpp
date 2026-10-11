#include <math.h>

#include "code/math/aabb.h"
#include "code/math/mathconstants.h"
#include "code/math/mathutils.h"
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

	// FUNCTION: ENGINE 0x107D7770
	// EQUIVALENT: same operations in the same order (19.1 %); the original loads both start points into registers
	// before the differences, keeps more values on the stack (frame 0x34, ours 0x28) and squares the result in x87
	float Segment::DistanceSquared(const Segment& other) const
	{
		// Closest points of the two lines (s on this segment, t on the other, both scaled by denom), clamped to the
		// segments through the point-segment distance at an end point
		Vector d1;
		d1.Sub(end, start);
		Vector d2;
		d2.Sub(other.end, other.start);
		float a = (d1.z * d1.z + d1.y * d1.y) + d1.x * d1.x;
		float e = (d2.z * d2.z + d2.y * d2.y) + d2.x * d2.x;
		float b = (d2.z * d1.z + d1.y * d2.y) + d2.x * d1.x;
		Vector r;
		r.Sub(other.start, start);
		float c = (r.z * d1.z + r.y * d1.y) + r.x * d1.x;
		float f = (r.z * d2.z + r.y * d2.y) + r.x * d2.x;
		float denom = e * a - b * b;
		float s = c * e - f * b;
		if (s <= 0.0f)
		{
			return other.DistanceSquared(start, -f, e);
		}
		if (s >= denom)
		{
			Vector v;
			v.Sub(end, other.start);
			return other.DistanceSquared(end, (v.z * d2.z + v.y * d2.y) + v.x * d2.x, e);
		}
		float t = c * b - f * a;
		if (t <= 0.0f)
		{
			return DistanceSquared(other.start, c, a);
		}
		if (t >= denom)
		{
			Vector v;
			v.Sub(other.end, start);
			return DistanceSquared(other.end, (v.z * d1.z + v.y * d1.y) + v.x * d1.x, a);
		}
		if (denom < EPSILON_SMALL)
		{
			return (r.z * r.z + r.y * r.y) + r.x * r.x - c * (c / a);
		}
		float ns = -s;
		float x = (d2.x * t + r.x * denom) + ns * d1.x;
		float y = (d2.y * t + r.y * denom) + d1.y * ns;
		float z = (d2.z * t + r.z * denom) + d1.z * ns;
		return ((z * z + y * y) + x * x) / (denom * denom);
	}

	// FUNCTION: ENGINE 0x107D7B40
	// EQUIVALENT: same operations in the same order (19.6 %, 1346 bytes against 1407); register and stack-slot
	// choices differ throughout, as in DistanceSquared(const Segment&)
	float Segment::ClosestPoints(const Segment& other, Vector& p, Vector& q) const
	{
		// As DistanceSquared(const Segment&); when the lines' closest points fall outside a segment, the best of the
		// four end point projections
		Vector d1;
		d1.Sub(end, start);
		Vector d2;
		d2.Sub(other.end, other.start);
		float a = (d1.z * d1.z + d1.y * d1.y) + d1.x * d1.x;
		float e = (d2.z * d2.z + d2.y * d2.y) + d2.x * d2.x;
		float b = (d2.z * d1.z + d2.y * d1.y) + d2.x * d1.x;
		Vector r;
		r.Sub(other.start, start);
		float c = (r.z * d1.z + r.y * d1.y) + r.x * d1.x;
		float f = (r.z * d2.z + r.y * d2.y) + r.x * d2.x;
		float denom = e * a - b * b;
		float s = c * e - f * b;
		float t = c * b - f * a;
		if (s <= 0.0f || s >= denom || t <= 0.0f || t >= denom)
		{
			Vector q0;
			float dist0 = other.ClosestPoint(start, -f, e, q0);
			Vector q1;
			Vector v;
			v.Sub(end, other.start);
			float dist1 = other.ClosestPoint(end, (v.z * d2.z + v.y * d2.y) + v.x * d2.x, e, q1);
			Vector p2;
			float dist2 = ClosestPoint(other.start, c, a, p2);
			Vector p3;
			Vector w;
			w.Sub(other.end, start);
			float dist3 = ClosestPoint(other.end, (w.z * d1.z + w.y * d1.y) + w.x * d1.x, a, p3);
			float m = Min(Min(dist0, dist1), Min(dist2, dist3));
			if (dist0 <= m)
			{
				p = start;
				q = q0;
				return dist0;
			}
			if (dist1 <= m)
			{
				p = end;
				q = q1;
				return dist1;
			}
			if (dist2 <= m)
			{
				p = p2;
				q = other.start;
				return dist2;
			}
			if (dist3 <= m)
			{
				p = p3;
				q = other.end;
				return dist3;
			}
		}
		float inv = 1.0f / denom;
		float ss = inv * s;
		float tt = inv * t;
		p.x = d1.x * ss;
		p.y = d1.y * ss;
		p.z = d1.z * ss;
		q.z = d2.z * tt;
		q.y = d2.y * tt;
		q.x = d2.x * tt;
		float dz = (q.z + r.z) - p.z;
		float dy = (q.y + r.y) - p.y;
		float dx = (q.x + r.x) - p.x;
		p.x += start.x;
		p.y += start.y;
		p.z += start.z;
		q.x = other.start.x + q.x;
		q.y = other.start.y + q.y;
		q.z = q.z + other.start.z;
		return (dz * dz + dy * dy) + dx * dx;
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
