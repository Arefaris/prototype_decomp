#include <string.h>

#include "code/core/heap.h"
#include "code/core/memory/memoryspace.h"

namespace core
{
	// FUNCTION: ENGINE 0x10645D50
	void InitMemorySpace()
	{
	}

	// FUNCTION: ENGINE 0x10645D60
	void ShutdownMemorySpace()
	{
	}

	// FUNCTION: ENGINE 0x10645D70
	void* MemorySpaceCopy(void* destination, int destinationSpace, const void* source, int sourceSpace, unsigned int size)
	{
		memcpy(destination, source, size);
		return destination;
	}

	// FUNCTION: ENGINE 0x10645D90
	IMemorySpaceCopyRequest* MemorySpaceCopyAsync(void* destination, int destinationSpace, const void* source, int sourceSpace, unsigned int size)
	{
		memcpy(destination, source, size);
		return &gMemorySpaceCopyRequest;
	}

	// FUNCTION: ENGINE 0x10645DB0
	MemorySpaceAsyncRequest_Copy::~MemorySpaceAsyncRequest_Copy()
	{
	}

	// FUNCTION: ENGINE 0x10645DC0
	void MemorySpaceAsyncRequest_Copy::AddRef()
	{
		count++;
	}

	// FUNCTION: ENGINE 0x10645DD0
	void MemorySpaceAsyncRequest_Copy::Release()
	{
		count--;
	}

	// FUNCTION: ENGINE 0x10645DE0
	bool MemorySpaceAsyncRequest_Copy::IsComplete()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x10645DF0
	void* MemorySpaceAlloc(int space, int heap, unsigned int size)
	{
		return HeapAlloc(heap, size);
	}

	// FUNCTION: ENGINE 0x10645E10
	void* MemorySpaceAllocAligned(int space, int heap, unsigned int size, unsigned int align)
	{
		return HeapAllocAligned(heap, size, align);
	}

	// FUNCTION: ENGINE 0x10645E30
	IMemoryAllocator* MemorySpaceGetAllocator(int space, int heap)
	{
		return GetHeapAllocator(heap);
	}

	// FUNCTION: ENGINE 0x10645E40
	void MemorySpaceFree(int space, int heap, void* block)
	{
		HeapFree(heap, block);
	}

	// FUNCTION: ENGINE 0x10645E60
	void MemorySpaceFreeAligned(int space, int heap, void* block)
	{
		HeapFreeAligned(heap, block);
	}

	// FUNCTION: ENGINE 0x10645E80
	bool MemorySpaceIsAccessible()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x10645EA0
	MemorySpaceAsyncRequest_Copy::MemorySpaceAsyncRequest_Copy()
	{
		count = 0;
		CoreName();
	}
}
