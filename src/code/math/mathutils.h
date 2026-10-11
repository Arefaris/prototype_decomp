// Scalar helpers of the math module (names guessed).
#ifndef MATH_MATHUTILS_H
#define MATH_MATHUTILS_H

namespace math
{
	// The smaller of two values (an inline template is what Spline::InvalidateLengths needs to match: it keeps the
	// min as a branch where a plain conditional becomes cmov)
	template<class T> inline T Min(T a, T b)
	{
		return a < b ? a : b;
	}

	// The larger of two values
	template<class T> inline T Max(T a, T b)
	{
		return a > b ? a : b;
	}

	// a when test >= 0, else b: the PowerPC fsel the console code was written around (compare against zero after a
	// subtraction; seen in Spline::GetParameter)
	inline float Select(float test, float a, float b)
	{
		return test >= 0.0f ? a : b;
	}

	// value clamped to [lo, hi] with two Selects (seen in the triangle angle function)
	inline float Clamp(float value, float lo, float hi)
	{
		float r = Select(value - lo, value, lo);
		r = Select(r - hi, hi, r);
		return r;
	}

	// 1 / sqrt(value), on the x87 unit
	float InvSqrt(float value);
	// Polynomial arctangent of a / b for 0 <= a, b: atan(a / b) when a < b, else pi/2 - atan(b / a)
	float AtanRatio(float a, float b);
	// Polynomial arctangent of any x (|error| about 0.0015 rad), capsule.cpp's unit (name guessed)
	float FastAtan(float x);
	// Odd polynomial (degree 13) approximation of sin(x) for small x
	float SinPolynomial(float x);
	// (r, angle) to x = r sin(angle), z = r cos(angle)
	void PolarToCartesian(float r, float angle, float* x, float* z);
	// (x, y, z) to r = |v|, theta = atan2(y, x), phi = acos(z / r)
	void CartesianToSpherical(float x, float y, float z, float* r, float* theta, float* phi);
	// (r, theta, phi) to x = r sin(phi) cos(theta), y = r sin(phi) sin(theta), z = r cos(phi)
	void SphericalToCartesian(float r, float theta, float phi, float* x, float* y, float* z);
	// n! as a float: from FACTORIAL_TABLE for n < 32, else 31! times the product 32 .. n
	float Factorial(int n);
	// sin(x) / x, 1 at 0
	float Sinc(float x);
	// Position of the highest set bit of v (0 for v = 0 and 1)
	int Log2(unsigned int v);
}

#endif
