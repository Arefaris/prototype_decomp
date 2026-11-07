// The thread safe reference count of the om library (0x105B4C50, 0x105B4C70), the interlocked change of a counter.
#include "code/om/refcount.h"

namespace om
{
	// FUNCTION: ENGINE 0x105B4C50
	int ThreadSafeRefCount::AddRef(int* count)
	{
		int result;
		__asm
		{
			mov eax, count
			mov ecx, 1
			lock xadd [eax], ecx
			inc ecx
			mov result, ecx
		}
		return result;
	}

	// FUNCTION: ENGINE 0x105B4C70
	int ThreadSafeRefCount::Release(int* count)
	{
		int result;
		__asm
		{
			mov eax, count
			or ecx, 0xffffffff
			lock xadd [eax], ecx
			dec ecx
			mov result, ecx
		}
		return result;
	}
}
