// core::MemorySpillOverAllocator (RTTI name; vftables 0x10EAEDB0 for the RefCount base at 0 and 0x10EAED64 for the
// interface at 0xC): allocates from a primary allocator and, when that fails, from a fallback (a second allocator
// or a heap), counting what spilled over and telling an optional callback. Unit 0x10B803A0 - 0x10B80B12 (no assert
// path; file name memory/spilloverallocator.cpp guessed). Member names guessed.
#ifndef CORE_MEMORY_SPILLOVERALLOCATOR_H
#define CORE_MEMORY_SPILLOVERALLOCATOR_H

#include "code/core/memory/imemoryallocator.h"
#include "code/core/object.h"

namespace core
{
	const char* CoreName();
	unsigned int RoundUp(unsigned int size, unsigned int align);

	// Called before the first spill (and again while it keeps answering 1): (user data, the spill-over allocator,
	// primary, fallback, size, 16, 0, spill count); the answer replaces the notify state
	typedef int (*SpillOverCallback)(void* userData, IMemoryAllocator* allocator, IMemoryAllocator* primary,
		IMemoryAllocator* fallback, unsigned int size, unsigned int align, int flags, int count);

	class MemorySpillOverAllocator : public RefCount, public IMemoryAllocator
	{
	public:
		MemorySpillOverAllocator();
		virtual ~MemorySpillOverAllocator();
		virtual void AddRef();
		virtual void Release();
		virtual void* Alloc(unsigned int size);
		virtual void Free(void* block);
		virtual void* AllocAligned(unsigned int size, unsigned int align);
		virtual void FreeAligned(void* block);
		virtual void* AllocFlags(unsigned int size, unsigned int align, int flags, int unused);
		virtual void FreeFlags(void* block);
		virtual int GetType();
		virtual void GetRange(MemoryRange* range, int index);
		// 15 bytes spilled, 16 blocks spilled; anything else is the primary's
		virtual bool GetStat(int id, int* value);
		virtual bool ResetStat(int id);
		virtual const char* GetName();
		virtual void SetSafetyMode(int mode);
		virtual int GetSafetyMode();
		virtual void SetUnused(int value);
		virtual bool IsThreadSafe();

		// Spill into a second allocator, or into a heap (both AddRef the allocators they keep)
		void Init(IMemoryAllocator* primary, IMemoryAllocator* secondary, SpillOverCallback callback, void* userData);
		void InitHeap(IMemoryAllocator* primary, int heap, SpillOverCallback callback, void* userData);

		IMemoryAllocator* primary;
		IMemoryAllocator* secondary;
		int fallbackHeap;
		bool useHeap;
		SpillOverCallback callback;
		int notify;
		void* userData;
		long spilledBytes;
		long spilledCount;
	};

	// The allocator object comes from `heap`; both hand out the interface
	IMemoryAllocator* CreateSpillOverAllocator(IMemoryAllocator* primary, IMemoryAllocator* secondary, int heap, SpillOverCallback callback, void* userData);
	IMemoryAllocator* CreateSpillOverHeapAllocator(IMemoryAllocator* primary, int fallbackHeap, int heap, SpillOverCallback callback, void* userData);
}

#endif
