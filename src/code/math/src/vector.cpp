#include "code/math/vector.h"

namespace math
{
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
