// Functions and data of other units that the code half of the motion fight items calls or reads.
#ifndef PROTO_FIGHTITEMS_MOTION_MOTIONCOMMON2_H
#define PROTO_FIGHTITEMS_MOTION_MOTIONCOMMON2_H

#include "code/core/name.h"
#include "code/math/vector.h"

namespace choreo
{
	// 0x10D94FF8: minus one
	extern const float gMinusOne;
}

namespace fight
{
	// 0x1009E120 (another unit): compares two floats with one of the compare operators (0 less, 1 less or equal, 2 equal, 3
	// not equal, 4 greater or equal, 5 greater): lhs op rhs
	bool CompareFloats(int op, const float* lhs, const float* rhs);
	// 0x107F1BB0 (another unit, cdecl): compares a value with one measure of a vector (name guess): selector 0 - 2 a component, 3 its
	// length in the xz plane, 4 its length, 5 - 7 the absolute value of a component
	bool CompareVectorMeasure(int op, const math::Vector* vector, int selector, float value);
}

#endif
