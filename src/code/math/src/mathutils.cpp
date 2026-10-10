#include <math.h>

#include "code/math/mathconstants.h"
#include "code/math/mathutils.h"

namespace math
{
	// FUNCTION: ENGINE 0x107CD360
	float InvSqrt(float value)
	{
		return 1.0f / sqrtf(value);
	}

	// FUNCTION: ENGINE 0x107CD370
	float AtanRatio(float a, float b)
	{
		float t = (a - b >= 0.0f) ? -(b / a) : a / b;
		float offset = (a - b >= 0.0f) ? HALF_PI : 0.0f;
		float t2 = t * t;
		return ((((((0.0429096147f * t2 - 0.0752896369f) * t2 + 0.106562637f) * t2 - 0.142088994f) * t2
			+ 0.199935511f) * t2 - 0.333331466f) * t2 + 1.0f) * t + offset;
	}

	// FUNCTION: ENGINE 0x107CD410
	// NONMATCHING: the original loads the leading coefficient as -2.39e-8 and adds; VS 2005 always folds the sign
	// into fsubr with +2.39e-8 for every form tried (98.2 %)
#ifdef NONMATCHING
	float SinPolynomial(float x)
	{
		float x2 = x * x;
		return (((((-2.39e-8f * x2 + 2.7526e-6f) * x2 - 0.000198409f) * x2 + 0.00833333191f) * x2 - 0.166666672f) * x2
			+ 1.0f) * x;
	}
#endif
}
