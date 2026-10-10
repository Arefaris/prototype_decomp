#include <math.h>

#include "code/math/mathconstants.h"
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
}
