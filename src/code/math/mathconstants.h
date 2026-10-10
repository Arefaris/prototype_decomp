// Constants of the math module. "math::EPSILON_FLOAT" is the engine's own name (it survives in an assert text);
// its value here is the threshold Vector::Normalize compares against (1e-10f at 0x10DA404C).
#ifndef MATH_MATHCONSTANTS_H
#define MATH_MATHCONSTANTS_H

namespace math
{
	const float EPSILON_FLOAT = 1e-10f;
	// Tolerance of Vector::IsZero and Vector::Perpendicular (1e-5f at 0x10E67C30); name guessed
	const float EPSILON_SMALL = 1e-5f;
}

#endif
