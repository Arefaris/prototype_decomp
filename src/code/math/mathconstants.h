// Constants of the math module. "math::EPSILON_FLOAT" is the engine's own name (it survives in an assert text);
// its value here is the threshold Vector::Normalize compares against (1e-10f at 0x10DA404C).
#ifndef MATH_MATHCONSTANTS_H
#define MATH_MATHCONSTANTS_H

namespace math
{
	const float EPSILON_FLOAT = 1e-10f;
}

#endif
