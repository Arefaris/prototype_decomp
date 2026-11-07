// The om library's allocators (0x105B7370 - 0x105B7610).
#include "code/om/allocator.h"
#include "code/om/allocation.h"
#include "code/core/heap.h"

namespace om
{
	Allocator* gAllocator = (Allocator*)&gDefaultAllocator;

	// FUNCTION: ENGINE 0x105B7600
	void* Allocator::AllocateTracked(const char* tag, unsigned int size, unsigned int alignment)
	{
		if (!(size > 0))
		{
			return 0;
		}
		unsigned int minimum = 8;
		unsigned int step = Max(minimum, alignment);
		char* block = (char*)Allocate(tag, size + step, step);
		block += step;
		((unsigned int*)block)[-1] = step;
		((unsigned int*)block)[-2] = size + step;
		return block;
	}

	// FUNCTION: ENGINE 0x105B7460
	void Allocator::ReleaseTracked(void* memory)
	{
		if (memory != 0)
		{
			unsigned int step = ((unsigned int*)memory)[-1];
			unsigned int total = ((unsigned int*)memory)[-2];
			Release((char*)memory - step, total, step);
		}
	}

	// FUNCTION: ENGINE 0x105B75D0
	DefaultAllocator::DefaultAllocator()
	{
	}

	// FUNCTION: ENGINE 0x105B73D0
	void* DefaultAllocator::Allocate(const char* tag, unsigned int size, unsigned int alignment)
	{
		return core::HeapAllocAligned(0, size, alignment);
	}

	// FUNCTION: ENGINE 0x105B73F0
	void DefaultAllocator::Release(void* memory, unsigned int size, unsigned int alignment)
	{
		core::HeapFreeAligned(0, memory);
	}

	// FUNCTION: ENGINE 0x105B7430
	Allocator* SetAllocator(Allocator* allocator)
	{
		Allocator* old = gAllocator;
		gAllocator = (Allocator*)&gDefaultAllocator;
		if (allocator != 0)
		{
			gAllocator = allocator;
		}
		return old;
	}

	// FUNCTION: ENGINE 0x105B7450
	Allocator* GetAllocator()
	{
		return gAllocator;
	}

	// FUNCTION: ENGINE 0x105B7490
	void* AllocateTrackedFrom(Allocator* allocator, const char* tag, unsigned int size, unsigned int alignment)
	{
		return allocator->AllocateTracked(tag, size, alignment);
	}

	// FUNCTION: ENGINE 0x105B74B0
	void ReleaseTrackedFrom(Allocator* allocator, void* memory)
	{
		allocator->ReleaseTracked(memory);
	}

	// FUNCTION: ENGINE 0x105B74D0
	void* AllocateFrom(Allocator* allocator, const char* tag, unsigned int size, unsigned int alignment)
	{
		if (size == 0)
		{
			return 0;
		}
		return allocator->Allocate(tag, size, alignment);
	}

	// FUNCTION: ENGINE 0x105B7500
	void ReleaseFrom(Allocator* allocator, void* memory, unsigned int size, unsigned int alignment)
	{
		if (size != 0)
		{
			allocator->Release(memory, size, alignment);
		}
	}

	// FUNCTION: ENGINE 0x105B7530
	void* AllocateTracked(const char* tag, unsigned int size, unsigned int alignment)
	{
		return AllocateTrackedFrom(GetAllocator(), tag, size, alignment);
	}

	// FUNCTION: ENGINE 0x105B7550
	void ReleaseTracked(void* memory)
	{
		ReleaseTrackedFrom(GetAllocator(), memory);
	}

	// FUNCTION: ENGINE 0x105B7570
	void* Allocate(const char* tag, unsigned int size, unsigned int alignment)
	{
		return AllocateFrom(GetAllocator(), tag, size, alignment);
	}

	// FUNCTION: ENGINE 0x105B7590
	void Release(void* memory, unsigned int size, unsigned int alignment)
	{
		ReleaseFrom(GetAllocator(), memory, size, alignment);
	}
}
