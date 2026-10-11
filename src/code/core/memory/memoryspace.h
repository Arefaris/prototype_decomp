// The main-memory "memory space" (names guessed): copies and heap calls that take a space id first and ignore it,
// and core::IMemorySpaceCopyRequest / core::MemorySpaceAsyncRequest_Copy (RTTI names; vftables 0x10E473E0,
// 0x10E473F4), the request an asynchronous copy hands back. In main memory every copy finishes at once, so one
// static request (0x1127A474, constructed by a dynamic initializer at 0x10D66930) serves them all. Unit
// 0x10645D40 - 0x10645EDB (no assert path; file name memory/memoryspace.cpp guessed).
#ifndef CORE_MEMORY_MEMORYSPACE_H
#define CORE_MEMORY_MEMORYSPACE_H

#include "code/core/memory/imemoryallocator.h"

namespace core
{
	const char* CoreName();

	struct IMemorySpaceCopyRequest : IRefCount
	{
		virtual bool IsComplete() = 0;
	};

	class MemorySpaceAsyncRequest_Copy : public IMemorySpaceCopyRequest
	{
	public:
		MemorySpaceAsyncRequest_Copy();
		virtual ~MemorySpaceAsyncRequest_Copy();
		// A plain counter (the static instance is never freed)
		virtual void AddRef();
		virtual void Release();
		virtual bool IsComplete();

		int count;
	};

	// The static request; defined (and constructed) with the dynamic initializers, outside our units
	extern MemorySpaceAsyncRequest_Copy gMemorySpaceCopyRequest;

	void* MemorySpaceCopy(void* destination, int destinationSpace, const void* source, int sourceSpace, unsigned int size);
	IMemorySpaceCopyRequest* MemorySpaceCopyAsync(void* destination, int destinationSpace, const void* source, int sourceSpace, unsigned int size);
	void* MemorySpaceAlloc(int space, int heap, unsigned int size);
	void* MemorySpaceAllocAligned(int space, int heap, unsigned int size, unsigned int align);
	IMemoryAllocator* MemorySpaceGetAllocator(int space, int heap);
	void MemorySpaceFree(int space, int heap, void* block);
	void MemorySpaceFreeAligned(int space, int heap, void* block);
	bool MemorySpaceIsAccessible();
}

#endif
