// The om library's comparisons of numbers (names guessed).
#include "code/om/allocator.h"

namespace om
{
	// FUNCTION: ENGINE 0x105B75B0
	unsigned int Max(const unsigned int& first, const unsigned int& second)
	{
		unsigned int result = first;
		if (first <= second)
		{
			result = second;
		}
		return result;
	}
}
