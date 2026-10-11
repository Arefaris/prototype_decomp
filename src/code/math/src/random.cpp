#include <math.h>

#include "code/math/random.h"

namespace math
{
	// FUNCTION: ENGINE 0x107D8380
	void Random::Seed(unsigned int seed)
	{
		if (seed == 0)
		{
			seed = 0xFC7D2BA2;
		}
		z = seed >> 16;
		w = seed & 0xFFFF;
		Step(z, 36969);
		Step(w, 18000);
		Step(z, 36969);
		Step(w, 18000);
	}

	// FUNCTION: ENGINE 0x107D83F0
	void Random::Seed(unsigned int seedZ, unsigned int seedW)
	{
		if (seedZ == 0)
		{
			seedZ = 0xFC7D2BA2;
		}
		if (seedW == 0)
		{
			seedW = 0x534FFD12;
		}
		z = seedZ;
		w = seedW;
		Step(z, 36969);
		Step(w, 18000);
		Step(z, 36969);
		Step(w, 18000);
	}

	// FUNCTION: ENGINE 0x107D8460
	Vector Random::NextVector01()
	{
		Vector v;
		v.x = NextFloat01();
		v.y = NextFloat01();
		v.z = NextFloat01();
		return v;
	}

	// FUNCTION: ENGINE 0x107D8560
	Vector Random::NextVector11()
	{
		Vector v;
		v.x = NextFloat11();
		v.y = NextFloat11();
		v.z = NextFloat11();
		return v;
	}

											// FUNCTION: ENGINE 0x107D8660
	// NONMATCHING: the loop and the scaling are right, but the original copies each NextVector11 result member-wise
	// into both the result and a second local (and scales that local into the result), where `v = NextVector11()`
	// copies with integer moves; local copies, Set and chained assignments did not reproduce it
#ifdef NONMATCHING
	Vector Random::NextUnitVector()
	{
		Vector v;
		float lengthSquared;
		do
		{
			v = NextVector11();
			lengthSquared = v.x * v.x + v.y * v.y + v.z * v.z;
		}
		while (lengthSquared > 1.0f || lengthSquared < 0.001f);
		float inv = 1.0f / sqrtf(lengthSquared);
		v.x *= inv;
		v.y *= inv;
		v.z *= inv;
		return v;
	}
#endif
}
