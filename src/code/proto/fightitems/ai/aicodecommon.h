// Functions and data of other units that the code half of the ai fight items calls or reads.
#ifndef PROTO_FIGHTITEMS_AI_AICODECOMMON_H
#define PROTO_FIGHTITEMS_AI_AICODECOMMON_H

#include "code/core/name.h"

namespace choreo
{
	// 0x10D94F78: zero
	extern const float gZero;
}

namespace fight
{
	// 0x1009E120 (another unit): compares two floats with one of the compare operators (0 less, 1 less or equal, 2 equal, 3
	// not equal, 4 greater or equal, 5 greater): lhs op rhs
	bool CompareFloats(int op, const float* lhs, const float* rhs);
	// 0x100A1FB0 (another unit): compares two names (0 equal, 1 not equal)
	bool CompareNames(int op, const core::Name<core::CaseSensitiveKey>* lhs, const core::Name<core::CaseSensitiveKey>* rhs);
}

#endif
