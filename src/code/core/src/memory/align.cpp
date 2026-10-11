#include "code/core/memory/align.h"

namespace core
{
	// FUNCTION: ENGINE 0x10645300
	unsigned int RoundUp(unsigned int size, unsigned int align)
	{
		if (align != 0)
		{
			unsigned int rest = size % align;
			if (rest != 0)
			{
				return size - rest + align;
			}
		}
		return size;
	}

	// FUNCTION: ENGINE 0x10645330
	unsigned int RoundDown(unsigned int size, unsigned int align)
	{
		if (align == 0)
		{
			return size;
		}
		return size / align * align;
	}

	// FUNCTION: ENGINE 0x10645350
	bool IsRoundedUp(unsigned int size, unsigned int align)
	{
		return size == RoundUp(size, align);
	}
}
