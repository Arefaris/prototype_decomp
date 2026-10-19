// The increments of the block TEA's sum (the unit around 0x1093FE70; split from tea.cpp so that the compiler does not
// know these functions leave the registers alone).
#include "code/crypto/tea.h"

namespace crypto
{
	// FUNCTION: ENGINE 0x1093FE70
	template <> unsigned int GetDelta<unsigned int>()
	{
		return 0x9E3779B9;
	}

	// FUNCTION: ENGINE 0x1093FE80
	template <> unsigned char GetDelta<unsigned char>()
	{
		return 0x9E;
	}
}
