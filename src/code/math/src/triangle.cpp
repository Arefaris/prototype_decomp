#include <math.h>

#include "code/math/mathconstants.h"
#include "code/math/triangle.h"

namespace math
{
	// 0x107D2ED0 ray test, 0x107D31C0 contains (barycentric), 0x107D3420 ClosestPoint and 0x107D3B50 corner
	// angle are not reconstructed yet (docs/math_worklist.md).

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
}
