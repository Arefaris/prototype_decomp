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
}
