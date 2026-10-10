// Constants of the math module. "math::EPSILON_FLOAT" is the engine's own name (it survives in an assert text);
// its value here is the threshold Vector::Normalize compares against (0x2EDBE6FE at 0x10DA404C: one step below 1e-10f,
// as the constant check of tools/objcmp.py showed).
#ifndef MATH_MATHCONSTANTS_H
#define MATH_MATHCONSTANTS_H

namespace math
{
	const float EPSILON_FLOAT = 9.9999994e-11f;
	// Tolerance of Vector::IsZero and Vector::Perpendicular (1e-5f at 0x10E67C30); name guessed
	const float EPSILON_SMALL = 1e-5f;
	// pi / 2 (0x3FC90FDB)
	const float HALF_PI = 1.57079637f;
}

#endif
