#include <math.h>

#include "code/math/aabb.h"
#include "code/math/mathconstants.h"
#include "code/math/matrix.h"
#include "code/math/plane.h"

namespace math
{
	// True when the sign bits of a and b are equal (the engine inlines this on copies of both values; name guessed)
	inline bool SameSign(float a, float b)
	{
		return ((*(int*)&a) ^ (*(int*)&b)) >= 0;
	}

	// FUNCTION: ENGINE 0x107D89E0
	// EQUIVALENT: same operations; the original multiplies e1.z * e2.y with the operands the other way round and adds
	// the dot product's z term before its y term (commutative); 96.1 % with the grouped dot
	void Plane::Set(const Vector& a, const Vector& b, const Vector& c)
	{
		Vector e1;
		e1.Sub(b, a);
		Vector e2;
		e2.Sub(c, a);
		normal.Cross(e1, e2);
		normal.NormalizeFast();
		d = -((a.x * normal.x + a.y * normal.y) + a.z * normal.z);
	}

	// FUNCTION: ENGINE 0x107D8AB0
	int Plane::IsBoxPartlyBehind(const AABB& box) const
	{
		float px;
		float py;
		float pz;
		if (normal.x >= 0.0f)
		{
			px = box.min.x;
		}
		else
		{
			px = box.max.x;
		}
		if (normal.y >= 0.0f)
		{
			py = box.min.y;
		}
		else
		{
			py = box.max.y;
		}
		if (normal.z >= 0.0f)
		{
			pz = box.min.z;
		}
		else
		{
			pz = box.max.z;
		}
		return normal.y * py + normal.z * pz + normal.x * px <= -d;
	}

	// FUNCTION: ENGINE 0x107D8B30
	int Plane::IsBoxBehind(const AABB& box) const
	{
		float px;
		float py;
		float pz;
		if (normal.x < 0.0f)
		{
			px = box.min.x;
		}
		else
		{
			px = box.max.x;
		}
		if (normal.y < 0.0f)
		{
			py = box.min.y;
		}
		else
		{
			py = box.max.y;
		}
		if (normal.z < 0.0f)
		{
			pz = box.min.z;
		}
		else
		{
			pz = box.max.z;
		}
		return normal.y * py + normal.z * pz + normal.x * px <= -d;
	}

	// FUNCTION: ENGINE 0x107D8BB0
	bool Plane::IntersectSegment(const Vector& a, const Vector& b, float* t) const
	{
		float da = a.y * normal.y + a.z * normal.z + a.x * normal.x + d;
		float db = b.y * normal.y + b.z * normal.z + b.x * normal.x + d;
		if (!SameSign(da, db))
		{
			float diff = da - db;
			if (EPSILON_SMALL >= fabsf(diff))
			{
				return false;
			}
			*t = da / diff;
			return true;
		}
		return false;
	}

	// 0x107D8C80 IntersectRay: not reconstructed yet (same instructions, different SSE register assignment; see
	// docs/math_worklist.md)

	// FUNCTION: ENGINE 0x107D8D50
	void Plane::Transform(const Matrix& m, const Plane& p)
	{
		m.Rotate(p.normal, normal);
		// A point of the moved plane: p's foot point rotated (p.normal rotated is this normal), plus m's translation
		float k = -p.d;
		Vector offset;
		offset.x = normal.x * k;
		offset.y = normal.y * k;
		offset.z = normal.z * k;
		Vector translation;
		m.GetTranslation(translation);
		Vector point;
		point.Add(translation, offset);
		d = -(normal.z * point.z + normal.y * point.y + normal.x * point.x);
	}

	// FUNCTION: ENGINE 0x107D8E10
	void Plane::Transform(const Matrix& m)
	{
		Transform(m, *this);
	}
}
