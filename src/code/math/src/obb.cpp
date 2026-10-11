#include <math.h>

#include "code/math/matrix.h"
#include "code/math/obb.h"

namespace math
{
	// FUNCTION: ENGINE 0x107D43B0
	void OBB::Transform(const Matrix& m)
	{
		centre.Transform(m);
		m.Rotate(axis[0], axis[0]);
		m.Rotate(axis[1], axis[1]);
		m.Rotate(axis[2], axis[2]);
	}

	// FUNCTION: ENGINE 0x107D43F0
	void OBB::Transform(const Matrix& m, const OBB& src)
	{
		m.Transform(src.centre, centre);
		m.Rotate(src.axis[0], axis[0]);
		m.Rotate(src.axis[1], axis[1]);
		m.Rotate(src.axis[2], axis[2]);
		extents.x = src.extents.x;
		extents.y = src.extents.y;
		extents.z = src.extents.z;
	}

	// FUNCTION: ENGINE 0x107D4630
	bool OBB::Contains(const Vector& p) const
	{
		Vector d;
		d.Sub(p, centre);
		for (int i = 3; i--; )
		{
			const Vector& v = axis[i];
			if (fabsf((v.x * d.x + v.y * d.y) + v.z * d.z) > (&extents.x)[i])
			{
				return false;
			}
		}
		return true;
	}
}
