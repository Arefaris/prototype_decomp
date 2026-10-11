#include <float.h>
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

	// FUNCTION: ENGINE 0x107D4560
	// EQUIVALENT: the same products and sums; the original loads axis[2] and the first factor of each later stage
	// before the sign branches and computes z, y, x first (ours x, y, z), 3 bytes longer (a movaps)
	void OBB::GetCornerOffset(Vector& out, unsigned char bits) const
	{
		float ez = (bits & 1) ? -extents.z : extents.z;
		float x = axis[2].x * ez;
		float y = axis[2].y * ez;
		float z = axis[2].z * ez;
		float ey = (bits & 2) ? -extents.y : extents.y;
		x = axis[1].x * ey + x;
		y = axis[1].y * ey + y;
		z = axis[1].z * ey + z;
		float ex = (bits & 4) ? -extents.x : extents.x;
		x = axis[0].x * ex + x;
		y = axis[0].y * ex + y;
		z = axis[0].z * ex + z;
		out.x = x;
		out.y = y;
		out.z = z;
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

	// FUNCTION: ENGINE 0x107D46D0
	// EQUIVALENT: same operations in the same order (56.7 %); the original computes the offset stage by stage
	// (axis[0] terms, then axis[1], then axis[2], interleaved across components) where ours runs one chain per
	// component, and loads all three negated components before storing them; registers differ throughout
	void OBB::GetDirection(const Vector& p, Vector& direction, float& distance) const
	{
		Vector d;
		d.Sub(p, centre);
		float t[3];
		float c[3];
		t[0] = axis[0].Dot(d);
		t[1] = axis[1].Dot(d);
		t[2] = axis[2].Dot(d);
		bool inside = true;
		int nearest = 0;
		float best = -FLT_MAX;
		for (int i = 3; i != 0; )
		{
			i--;
			float v = t[i];
			float e = (&extents.x)[i];
			float a;
			if (v > 0.0f)
			{
				c[i] = e;
				a = v;
			}
			else
			{
				c[i] = -e;
				a = -v;
			}
			if (a >= e)
			{
				inside = false;
				t[i] = c[i];
			}
			else if (a >= best)
			{
				best = a;
				nearest = i;
			}
		}
		if (inside)
		{
			t[nearest] = c[nearest];
		}
		Vector offset;
		offset.Set((axis[0].x * t[0] + axis[1].x * t[1]) + axis[2].x * t[2], (axis[0].y * t[0] + axis[1].y * t[1]) + axis[2].y * t[2], (axis[0].z * t[0] + axis[1].z * t[1]) + axis[2].z * t[2]);
		direction.Sub(d, offset);
		float length = direction.Normalize();
		distance = length;
		if (inside)
		{
			distance = -length;
			direction.Set(-direction.x, -direction.y, -direction.z);
		}
	}

	// FUNCTION: ENGINE 0x107D49B0
	void OBB::GetCorner(Vector& out, unsigned char bits) const
	{
		GetCornerOffset(out, bits);
		out.x = out.x + centre.x;
		out.y = centre.y + out.y;
		out.z = centre.z + out.z;
	}
}
