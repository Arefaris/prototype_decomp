// The sampling side of math::Noise. It sits far from the parameter class (0x1010xxxx vs 0x107D8xxx) and its
// callers go through the incremental-link thunks, so it is its own translation unit; "perlin" is a guess at its name.
#include "code/math/noise.h"

namespace math
{
	// FUNCTION: ENGINE 0x101040C0
	float Noise::Lattice(int x, int y, int z) const
	{
		int n = (seed | 1) + x + y * 15259 + z * 44533;
		n = n ^ (n << 13);
		n = (n * (n * n * 15731 + 789221) - 771171059) & 0x7FFFFFFF;
		return 1.0f - n / 1073741824.0;
	}
}
