// The om library's atomic counters (0x105B3950, 0x105B3970; names guessed).
#include "code/om/stringdata.h"

namespace om
{
	// FUNCTION: ENGINE 0x105B3950
	int AtomicIncrement(int* value)
	{
		int result;
		__asm
		{
			mov eax, value
			mov ecx, 1
			lock xadd [eax], ecx
			inc ecx
			mov result, ecx
		}
		return result;
	}

	// FUNCTION: ENGINE 0x105B3970
	int AtomicDecrement(int* value)
	{
		int result;
		__asm
		{
			mov eax, value
			or ecx, 0xffffffff
			lock xadd [eax], ecx
			dec ecx
			mov result, ecx
		}
		return result;
	}
}
