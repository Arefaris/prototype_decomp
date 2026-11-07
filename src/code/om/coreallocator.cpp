// The allocator of the om library that works on a heap of the core module (0x10AAAB10 - 0x10AAAC40).
#include "code/om/coreallocator.h"
#include "code/core/heap.h"
#include "code/core/memory/imemoryallocator.h"

namespace om
{
	// FUNCTION: ENGINE 0x10AAAC00
	CoreAllocator::CoreAllocator(int newHeap) :
		heap(newHeap)
	{
	}

	// FUNCTION: ENGINE 0x10AAAB10
	void* CoreAllocator::Allocate(const char* tag, unsigned int size, unsigned int alignment)
	{
		return core::HeapAllocAligned(heap, size, alignment);
	}

	// FUNCTION: ENGINE 0x10AAAB30
	void CoreAllocator::Release(void* memory, unsigned int size, unsigned int alignment)
	{
		core::HeapFreeAligned(heap, memory);
	}

	// FUNCTION: ENGINE 0x10AAAB50
	void* CoreAllocator::AllocateTracked(const char* tag, unsigned int size, unsigned int alignment)
	{
		return core::HeapAllocAligned(heap, size, alignment);
	}

	// FUNCTION: ENGINE 0x10AAAB70
	void CoreAllocator::ReleaseTracked(void* memory)
	{
		core::HeapFreeAligned(heap, memory);
	}

	// FUNCTION: ENGINE 0x10AAAB90
	int CoreAllocator::Slot5()
	{
		int value = 0;
		if (core::GetHeapAllocator(heap)->GetStat(3, &value))
		{
			return value;
		}
		return -1;
	}

	// FUNCTION: ENGINE 0x10AAABD0
	int CoreAllocator::Slot6()
	{
		int value = 0;
		core::GetHeapAllocator(heap)->GetStat(1, &value);
		return value;
	}
}
