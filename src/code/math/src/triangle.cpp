#include <math.h>

#include "code/math/mathconstants.h"
#include "code/math/mathutils.h"
#include "code/math/triangle.h"

namespace math
{
	// 0x107D3420 ClosestPoint is not reconstructed yet (docs/math_worklist.md).

	// FUNCTION: ENGINE 0x107D2ED0
	// NONMATCHING: 52 %; Moller-Trumbore with the two sign cases written out. The grouping of each dot product was
	// swept; the original adds direction . q as (z + x) + y, which no source form reproduces, and keeps
	// direction.x in a register from the first cross product
#ifdef NONMATCHING
	bool Triangle::IntersectRay(const Vector& origin, const Vector& direction, float& t) const
	{
		Vector e1;
		e1.Sub(b, a);
		Vector e2;
		e2.Sub(c, a);
		Vector p;
		p.Cross(direction, e2);
		float det = (e1.y * p.y + e1.z * p.z) + e1.x * p.x;
		Vector s;
		Vector q;
		if (det > EPSILON_SMALL)
		{
			s.Sub(origin, a);
			float u = (s.y * p.y + s.z * p.z) + s.x * p.x;
			if (u < 0.0f || u > det)
			{
				return false;
			}
			q.Cross(s, e1);
			float v = (direction.y * q.y + direction.z * q.z) + direction.x * q.x;
			if (v < 0.0f || u + v > det)
			{
				return false;
			}
		}
		else if (det < -EPSILON_SMALL)
		{
			s.Sub(origin, a);
			float u = (s.y * p.y + s.z * p.z) + s.x * p.x;
			if (u > 0.0f || u < det)
			{
				return false;
			}
			q.Cross(s, e1);
			float v = (direction.y * q.y + direction.z * q.z) + direction.x * q.x;
			if (v > 0.0f || u + v < det)
			{
				return false;
			}
		}
		else
		{
			return false;
		}
		t = ((e2.x * q.x + e2.y * q.y) + e2.z * q.z) / det;
		return true;
	}
#endif

	// FUNCTION: ENGINE 0x107D31C0
	bool Triangle::Contains(const Vector& p) const
	{
		// Barycentric test on the sign bits: inside when u = x, v = y and 1 - u - v (z) are all non-negative; the dot
		// products' groupings are what keeps the original's order of the x87-free sums
		Vector e1;
		e1.Sub(b, a);
		Vector e2;
		e2.Sub(c, a);
		float aa = e1.z * e1.z + (e1.x * e1.x + e1.y * e1.y);
		float ab = (e1.y * e2.y + e1.z * e2.z) + e1.x * e2.x;
		float bb = (e2.y * e2.y + e2.z * e2.z) + e2.x * e2.x;
		Vector vp;
		vp.Sub(p, a);
		float d = (vp.x * e1.x + vp.y * e1.y) + vp.z * e1.z;
		float e = (vp.y * e2.y + vp.z * e2.z) + vp.x * e2.x;
		float x = d * bb - e * ab;
		float y = e * aa - d * ab;
		float z = x + y - (aa * bb - ab * ab);
		return ((*(int*)&z) & ~((*(int*)&x) | (*(int*)&y))) < 0;
	}

	// FUNCTION: ENGINE 0x107D3360
	// EQUIVALENT: same operations in the same order; the two factors of the first edge test sit in swapped
	// registers (88 %)
	bool Triangle::ContainsXZ(const Vector& p) const
	{
		float px = p.x;
		float pz = p.z;
		if ((px - a.x) * (b.z - a.z) - (pz - a.z) * (b.x - a.x) < 0.0f)
		{
			return false;
		}
		if ((c.z - b.z) * (px - b.x) - (pz - b.z) * (c.x - b.x) < 0.0f)
		{
			return false;
		}
		if ((a.z - c.z) * (px - c.x) - (a.x - c.x) * (pz - c.z) < 0.0f)
		{
			return false;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x107D3AA0
	float Area(const Vector& a, const Vector& b, const Vector& c)
	{
		Vector e1;
		e1.Sub(a, b);
		Vector e2;
		e2.Sub(b, c);
		float z = e2.y * e1.x - e1.y * e2.x;
		float x = e1.y * e2.z - e1.z * e2.y;
		float y = e1.z * e2.x - e1.x * e2.z;
		Vector n;
		n.Set(x, y, z);
		return sqrtf(n.x * n.x + n.y * n.y + n.z * n.z) * 0.5f;
	}

	// FUNCTION: ENGINE 0x107D3B50
	float Triangle::SmallestAngle() const
	{
		// The edges normalised; the largest |cos| between them gives the smallest angle (0 for a degenerate triangle)
		Vector e0;
		Vector e1;
		Vector e2;
		e0.Sub(a, b);
		e1.Sub(b, c);
		e2.Sub(c, a);
		float l0 = e0.Normalize();
		float l1 = e1.Normalize();
		float l2 = e2.Normalize();
		if (l2 * l1 * l0 == 0.0f)
		{
			return 0.0f;
		}
		float c0 = fabsf(e0.Dot(e1));
		float c1 = fabsf(e1.Dot(e2));
		float c2 = fabsf(e0.Dot(e2));
		return acosf(Clamp(Max(c2, Max(c1, c0)), 0.0f, 1.0f));
	}
}
