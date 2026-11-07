// Data and functions of other units that the engine's fight code reads or calls (symbols.txt; names guessed).
#ifndef ENGINE_FIGHT_FIGHTCOMMON_H
#define ENGINE_FIGHT_FIGHTCOMMON_H

#include "code/core/name.h"

namespace engine
{
	namespace driving
	{
		// 0x10D946E0: one, a pooled constant: a use of it is a load from memory, never a literal
		extern const float gOne;
	}
}

namespace fight
{
	// 0x1009E120: compares two floats with one of the compare operators (0 less, 1 less or equal, 2 equal, 3 not equal, 4
	// greater or equal, 5 greater): lhs op rhs
	bool CompareFloats(int op, const float* lhs, const float* rhs);
	// 0x100A1FB0: compares two names (0 equal, 1 not equal)
	// 0x100C2350 / 0x100C2430: the same for two flags (0 equal, 1 not equal)
	bool BoolsEqual(const bool* lhs, const bool* rhs);
	bool CompareBools(int op, const bool* lhs, const bool* rhs);
	bool CompareNames(int op, const core::Name<core::CaseSensitiveKey>* lhs, const core::Name<core::CaseSensitiveKey>* rhs);
}

#endif
