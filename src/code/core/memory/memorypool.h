// core::IMemoryPool (vftable 0x10E46B74, 21 slots) and core::MemoryPool (RTTI names; vftables 0x10E46B1C and, for
// the RefCount base, 0x10E46B10): fixed-size blocks threaded on a free list. Unit 0x1063D430 - 0x1063DB97 (no
// assert path; file name memory/memorypool.cpp guessed). Layout as in MemoryTwoWayAllocator: interface at 0,
// RefCount at 4, AllocatorBase at 0x10, the pool from 0x50, 0x6C bytes in all. Member names guessed.
#ifndef CORE_MEMORY_MEMORYPOOL_H
#define CORE_MEMORY_MEMORYPOOL_H

#include "code/core/memory/allocatorbase.h"
#include "code/core/memory/imemoryallocator.h"
#include "code/core/object.h"

namespace core
{
	const char* CoreName();
	unsigned int RoundUp(unsigned int size, unsigned int align);

	struct IMemoryPool : IMemoryAllocator
	{
		// One block off the free list (null when the pool is exhausted)
		virtual void* AllocBlock() = 0;
		// Block index of an address and the address of a block index
		virtual unsigned int GetIndex(void* block) = 0;
		virtual void* GetBlock(unsigned int index) = 0;
	};

	class MemoryPool : public IMemoryPool, public AllocatorBase, public RefCount
	{
	public:
		MemoryPool();
		virtual ~MemoryPool();
		virtual void AddRef();
		virtual void Release();
		// Size and alignment are ignored: every block has the pool's size
		virtual void* Alloc(unsigned int size);
		virtual void Free(void* block);
		virtual void* AllocAligned(unsigned int size, unsigned int align);
		virtual void FreeAligned(void* block);
		virtual void* AllocFlags(unsigned int size, unsigned int align, int flags, int unused);
		virtual void FreeFlags(void* block);
		virtual int GetType();
		virtual void GetRange(MemoryRange* range, int index);
		// 0 blocks in use, 1 capacity in bytes, 2 bytes in use, 3 bytes free, 7 peak bytes, 8 block count,
		// 9 block size
		virtual bool GetStat(int id, int* value);
		// 7 clears the peak
		virtual bool ResetStat(int id);
		virtual const char* GetName();
		virtual void SetSafetyMode(int mode);
		virtual int GetSafetyMode();
		virtual void SetUnused(int value);
		virtual bool IsThreadSafe();
		virtual void* AllocBlock();
		virtual unsigned int GetIndex(void* block);
		virtual void* GetBlock(unsigned int index);

		// Whether the address lies inside the pool's blocks
		bool Contains(void* block);
		// Lays the blocks out in `memory` (aligned up) or, when it is null, in memory from `heap`
		void Init(void* memory, unsigned int size, unsigned int count, int heap, const char* name, unsigned int align);

		void* freeList;
		// The heap the blocks came from, -1 when the caller provided the memory
		int memoryHeap;
		unsigned int memory;
		unsigned int blockSize;
		unsigned int blockCount;
		unsigned int usedCount;
		unsigned int peakCount;
	};

	// The allocator object comes from `heap`; the blocks from the same heap or from memory the caller provides
	void CreateMemoryPool(MemoryPool** out, unsigned int size, unsigned int count, int heap, const char* name, unsigned int align);
	void CreateMemoryPoolAt(MemoryPool** out, void* memory, unsigned int size, unsigned int count, int heap, const char* name, unsigned int align);
}

#endif
