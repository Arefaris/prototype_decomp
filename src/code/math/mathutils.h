// Scalar helpers of the math module (names guessed).
#ifndef MATH_MATHUTILS_H
#define MATH_MATHUTILS_H

namespace math
{
	// 1 / sqrt(value), on the x87 unit
	float InvSqrt(float value);
	// Polynomial arctangent of a / b for 0 <= a, b: atan(a / b) when a < b, else pi/2 - atan(b / a)
	float AtanRatio(float a, float b);
	// Odd polynomial (degree 13) approximation of sin(x) for small x
	float SinPolynomial(float x);
}

#endif
