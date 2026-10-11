#include <math.h>

#include "code/math/mathconstants.h"
#include "code/math/mathutils.h"
#include "code/math/sincos.h"

namespace math
{
	// GLOBAL: ENGINE 0x111BBD60
	// 0! .. 31! as floats, defined by the engine's data (name guessed)
	extern const float FACTORIAL_TABLE[32];

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
	// EQUIVALENT: the original loads the leading coefficient as -2.39e-8 and adds; VS 2005 folds the sign into fsubr
	// with +2.39e-8 for every form tried (98.2 %; also a named constant, a Horner chain on a variable and constant
	// expressions); the result is bit-identical
	float SinPolynomial(float x)
	{
		float x2 = x * x;
		return (((((-2.39e-8f * x2 + 2.7526e-6f) * x2 - 0.000198409f) * x2 + 0.00833333191f) * x2 - 0.166666672f) * x2
			+ 1.0f) * x;
	}

	// FUNCTION: ENGINE 0x107D8740
	void PolarToCartesian(float r, float angle, float* x, float* z)
	{
		SinCos(angle, x, z);
		*x *= r;
		*z *= r;
	}

	// FUNCTION: ENGINE 0x107D8780
	void CartesianToSpherical(float x, float y, float z, float* r, float* theta, float* phi)
	{
		float length = sqrtf(x * x + y * y + z * z);
		*r = length;
		*phi = acosf(z / length);
		*theta = atan2f(y, x);
	}

	// FUNCTION: ENGINE 0x107D87C0
	void SphericalToCartesian(float r, float theta, float phi, float* x, float* y, float* z)
	{
		float sinPhi;
		float cosTheta;
		float sinTheta;
		float cosPhi;
		SinCos(phi, &sinPhi, &cosPhi);
		SinCos(theta, &sinTheta, &cosTheta);
		float rs = sinPhi * r;
		*x = rs * cosTheta;
		*y = rs * sinTheta;
		*z = cosPhi * r;
	}

	// FUNCTION: ENGINE 0x107D8850
	float Factorial(int n)
	{
		if (n < 32)
		{
			return FACTORIAL_TABLE[n];
		}
		float result = 1.0f;
		while (n >= 32)
		{
			result *= (float)n;
			n--;
		}
		return FACTORIAL_TABLE[31] * result;
	}

	// FUNCTION: ENGINE 0x107D8920
	float Sinc(float x)
	{
		if (x != 0.0f)
		{
			return sinf(x) / x;
		}
		return 1.0f;
	}

	// FUNCTION: ENGINE 0x107D8950
	int Log2(unsigned int v)
	{
		int shift;
		if (v & 0xFFFF0000)
		{
			v >>= 16;
			shift = 16;
		}
		else
		{
			shift = 0;
		}
		if (v & 0xFF00)
		{
			v >>= 8;
			shift |= 8;
		}
		if (v & 0xF0)
		{
			v >>= 4;
			shift |= 4;
		}
		// Highest set bit of a nibble; the engine builds the table on the stack
		char table[16] = { 0, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3 };
		return table[v] | shift;
	}
}
