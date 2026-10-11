#include "code/core/heap.h"
#include "code/core/memory/memorypool.h"
#include "code/core/utility.h"

namespace core
{
	// FUNCTION: ENGINE 0x1063D510
	void* MemoryPool::Alloc(unsigned int size)
	{
		return AllocBlock();
	}

	// FUNCTION: ENGINE 0x1063D520
	void* MemoryPool::AllocAligned(unsigned int size, unsigned int align)
	{
		return AllocBlock();
	}

	// FUNCTION: ENGINE 0x1063D530
	void MemoryPool::FreeAligned(void* block)
	{
		Free(block);
	}

	// FUNCTION: ENGINE 0x1063D540
	bool MemoryPool::GetStat(int id, int* value)
	{
		AllocatorLock lock(this);
		switch (id)
		{
		case 0:
			*value = usedCount;
			return true;
		case 1:
			*value = blockCount * blockSize;
			return true;
		case 2:
			*value = usedCount * blockSize;
			return true;
		case 3:
			*value = (blockCount - usedCount) * blockSize;
			return true;
		case 7:
			*value = peakCount * blockSize;
			return true;
		case 8:
			*value = blockCount;
			return true;
		case 9:
			*value = blockSize;
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1063D640
	bool MemoryPool::ResetStat(int id)
	{
		AllocatorLock lock(this);
		if (id != 7)
		{
			return false;
		}
		peakCount = 0;
		return true;
	}

	// FUNCTION: ENGINE 0x1063D680
	int MemoryPool::GetType()
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x1063D690
	void MemoryPool::GetRange(MemoryRange* range, int index)
	{
		range->start = memory;
		range->end = memory + blockCount * blockSize;
	}

	// FUNCTION: ENGINE 0x1063D6B0
	unsigned int MemoryPool::GetIndex(void* block)
	{
		return ((unsigned int)block - memory) / blockSize;
	}

	// FUNCTION: ENGINE 0x1063D6C0
	void* MemoryPool::GetBlock(unsigned int index)
	{
		return (void*)(memory + index * blockSize);
	}

	// FUNCTION: ENGINE 0x1063D6D0
	bool MemoryPool::Contains(void* block)
	{
		return (unsigned int)block >= memory && (unsigned int)block < memory + blockCount * blockSize;
	}

	// FUNCTION: ENGINE 0x1063D770
	MemoryPool::~MemoryPool()
	{
		if (memoryHeap >= 0)
		{
			HeapFreeAligned(memoryHeap, (void*)memory);
		}
		memory = 0;
	}

	// FUNCTION: ENGINE 0x1063D800
	const char* MemoryPool::GetName()
	{
		return AllocatorBase_Name::GetName();
	}

	// FUNCTION: ENGINE 0x1063D810
	int MemoryPool::GetSafetyMode()
	{
		return GetMode();
	}

	// FUNCTION: ENGINE 0x1063D820
	void MemoryPool::SetSafetyMode(int mode)
	{
		SetMode(mode, this);
	}

	// FUNCTION: ENGINE 0x1063D840
	void MemoryPool::SetUnused(int value)
	{
		AllocatorBase_Safety::SetUnused(value);
	}

	// FUNCTION: ENGINE 0x1063D850
	void* MemoryPool::AllocFlags(unsigned int size, unsigned int align, int flags, int unused)
	{
		if (flags != 0)
		{
			return 0;
		}
		return AllocAligned(size, align);
	}

	// FUNCTION: ENGINE 0x1063D870
	void MemoryPool::FreeFlags(void* block)
	{
		FreeAligned(block);
	}

	// FUNCTION: ENGINE 0x1063D880
	bool MemoryPool::IsThreadSafe()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x1063D8A0
	void MemoryPool::AddRef()
	{
		RefCount::AddRef();
	}

	// FUNCTION: ENGINE 0x1063D8B0
	void MemoryPool::Release()
	{
		RefCount::Release();
	}

	// FUNCTION: ENGINE 0x1063D8E0
	void MemoryPool::Init(void* where, unsigned int size, unsigned int count, int heap, const char* name, unsigned int align)
	{
		blockSize = RoundUp(size, align);
		if (blockSize < 4)
		{
			blockSize = 4;
		}
		unsigned int total = blockSize * count;
		usedCount = 0;
		peakCount = 0;
		memoryHeap = heap;
		blockCount = count;
		if (where == 0)
		{
			memory = (unsigned int)HeapAllocAligned(heap, total, align);
		}
		else
		{
			memory = AlignUp((unsigned int)where, align);
		}
		SetName(name);
		unsigned int block = memory;
		freeList = 0;
		for (unsigned int i = 0; i < blockCount; i++)
		{
			*(void**)block = freeList;
			freeList = (void*)block;
			block += blockSize;
		}
	}

	// FUNCTION: ENGINE 0x1063D980
	void* MemoryPool::AllocBlock()
	{
		AllocatorLock lock(this);
		void* block = freeList;
		if (block == 0)
		{
			return 0;
		}
		freeList = *(void**)block;
		usedCount++;
		peakCount = Max(usedCount, peakCount);
		return block;
	}

	// FUNCTION: ENGINE 0x1063D9D0
	void MemoryPool::Free(void* block)
	{
		AllocatorLock lock(this);
		if (Contains(block))
		{
			*(void**)block = freeList;
			usedCount--;
			freeList = block;
		}
	}

	// FUNCTION: ENGINE 0x1063DA80
	MemoryPool::MemoryPool()
	{
		memory = 0;
		CoreName();
	}

	// FUNCTION: ENGINE 0x1063DAE0
	void CreateMemoryPool(MemoryPool** out, unsigned int size, unsigned int count, int heap, const char* name, unsigned int align)
	{
		MemoryPool* pool = new (heap) MemoryPool();
		pool->Init(0, size, count, heap, name, align);
		pool->AddRef();
		*out = pool;
	}

	// FUNCTION: ENGINE 0x1063DB40
	void CreateMemoryPoolAt(MemoryPool** out, void* memory, unsigned int size, unsigned int count, int heap, const char* name, unsigned int align)
	{
		MemoryPool* pool = new (heap) MemoryPool();
		pool->Init(memory, size, count, -1, name, align);
		pool->AddRef();
		*out = pool;
	}
}
