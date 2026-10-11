// Small helpers shared by the core units (names guessed). Max is inline: the allocators' code shows its
// compare-and-branch at every use, which the plain conditional statements do not give (they become cmov).
#ifndef CORE_UTILITY_H
#define CORE_UTILITY_H

namespace core
{
	template<class T> inline T Max(T a, T b)
	{
		return a > b ? a : b;
	}
}

#endif
