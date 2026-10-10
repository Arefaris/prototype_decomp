#include <math.h>

#include "code/math/mathconstants.h"
#include "code/math/matrix.h"
#include "code/math/vector.h"

namespace math
{
	// FUNCTION: ENGINE 0x107CE3D0
	float Vector::Normalize()
	{
		float lengthSquared = x * x + y * y + z * z;
		float length = sqrtf(lengthSquared);
		float scale = (lengthSquared - EPSILON_FLOAT >= 0.0f) ? 1.0f / length : 0.0f;
		length = (lengthSquared - EPSILON_FLOAT >= 0.0f) ? length : 0.0f;
		x *= scale;
		y *= scale;
		z *= scale;
		return length;
	}

	// FUNCTION: ENGINE 0x107CE460
	void Vector::NormalizeFast()
	{
		float scale = 1.0f / sqrtf(x * x + y * y + z * z);
		x *= scale;
		y *= scale;
		z *= scale;
	}

	// FUNCTION: ENGINE 0x107CE4D0
	// NONMATCHING: the original multiplies y as "fld v.y; fmul st(1)", we get "fld st(0); fmul v.y" (80 %)
#ifdef NONMATCHING
	void Vector::Normalize(const Vector& v)
	{
		float scale = 1.0f / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
		x = v.x * scale;
		y = v.y * scale;
		z = v.z * scale;
	}
#endif

	// FUNCTION: ENGINE 0x107CE7A0
	int Vector::IsZero() const
	{
		return fabsf(x) < EPSILON_SMALL && fabsf(y) < EPSILON_SMALL && fabsf(z) < EPSILON_SMALL;
	}

	// FUNCTION: ENGINE 0x107CE7E0
	void Vector::Perpendicular(const Vector& v)
	{
		if (fabsf(v.y) <= EPSILON_SMALL && fabsf(v.z) <= EPSILON_SMALL)
		{
			Set(0.0f, 1.0f, 0.0f);
		}
		else
		{
			Set(0.0f, -v.z, v.y);
		}
	}

	// FUNCTION: ENGINE 0x107CE850
	// NONMATCHING: same size and instructions; the original interleaves the squares with the stores x, z, y (73.7 %)
#ifdef NONMATCHING
	bool Vector::CrossProduct(const Vector& a, const Vector& b)
	{
		Set(a.y * b.z - b.y * a.z, b.x * a.z - a.x * b.z, b.y * a.x - a.y * b.x);
		if (x * x + y * y + z * z <= EPSILON_FLOAT)
		{
			Perpendicular(a);
			return true;
		}
		return false;
	}
#endif

	// FUNCTION: ENGINE 0x107CE8F0
	unsigned int Vector::PackNormal() const
	{
		int iz = (int)(z * 511.0f);
		int iy = (int)(y * 511.0f);
		int ix = (int)(x * 511.0f);
		return ((((iz | 0xfffffc00) << 10) | (iy & 0x3ff)) << 10) | (ix & 0x3ff);
	}

	// FUNCTION: ENGINE 0x107CE990
	void Vector::UnpackNormal(unsigned int packed)
	{
		int ix = packed & 0x3ff;
		int iy = (packed >> 10) & 0x3ff;
		int iz = (packed >> 20) & 0x3ff;
		if (ix & 0x200) ix |= 0xfffffc00;
		if (iy & 0x200) iy |= 0xfffffc00;
		if (iz & 0x200) iz |= 0xfffffc00;
		x = ix * (1.0f / 511.0f) - 1.0f;
		y = iy * (1.0f / 511.0f) - 1.0f;
		z = iz * (1.0f / 511.0f) - 1.0f;
	}

	// FUNCTION: ENGINE 0x107CE520
	void Vector::Transform(const Matrix& m)
	{
		Vector t;
		m.Transform(*this, t);
		x = t.x;
		y = t.y;
		z = t.z;
	}

	// FUNCTION: ENGINE 0x107CE560
	void Vector::Transform(const Vector& v, const Matrix& m)
	{
		m.Transform(v, *this);
	}

	// FUNCTION: ENGINE 0x107CE580
	void Vector::Rotate(const Matrix& m)
	{
		Vector t;
		m.Rotate(*this, t);
		x = t.x;
		y = t.y;
		z = t.z;
	}

	// FUNCTION: ENGINE 0x107CE5C0
	void Vector::Rotate(const Vector& v, const Matrix& m)
	{
		m.Rotate(v, *this);
	}
}
