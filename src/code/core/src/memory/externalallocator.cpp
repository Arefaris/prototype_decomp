#include <new>

#include "code/core/heap.h"
#include "code/core/memory/externalallocator.h"

namespace core
{
	// FUNCTION: ENGINE 0x10B814E0
	unsigned int MemoryExternalAllocator::GetOverhead(unsigned int count)
	{
		return ExternalHeap::GetOverhead(count);
	}

	// FUNCTION: ENGINE 0x10B814F0
	void MemoryExternalAllocator::AddRef()
	{
		refCount++;
	}

	// FUNCTION: ENGINE 0x10B81500
	void MemoryExternalAllocator::Release()
	{
		if (refCount == 1)
		{
			int heap = selfHeap;
			void* block = self;
			this->~MemoryExternalAllocator();
			if (block != 0)
			{
				HeapFree(heap, block);
			}
		}
		else
		{
			refCount--;
		}
	}

	// FUNCTION: ENGINE 0x10B81540
	void* MemoryExternalAllocator::Alloc(unsigned int size)
	{
		return AllocFlags(size, 16, 0, 0);
	}

	// FUNCTION: ENGINE 0x10B81560
	void MemoryExternalAllocator::Free(void* block)
	{
		FreeFlags(block);
	}

	// FUNCTION: ENGINE 0x10B81570
	void* MemoryExternalAllocator::AllocAligned(unsigned int size, unsigned int align)
	{
		return AllocFlags(size, align, 0, 0);
	}

	// FUNCTION: ENGINE 0x10B81590
	void MemoryExternalAllocator::FreeAligned(void* block)
	{
		FreeFlags(block);
	}

	// FUNCTION: ENGINE 0x10B815A0
	void* MemoryExternalAllocator::AllocFlags(unsigned int size, unsigned int align, int flags, int unused)
	{
		AllocatorLock lock(this);
		if (flags != tag)
		{
			return 0;
		}
		return externalHeap.Alloc(size, align, 0);
	}

	// FUNCTION: ENGINE 0x10B81600
	void MemoryExternalAllocator::FreeFlags(void* block)
	{
		AllocatorLock lock(this);
		externalHeap.Free(block);
	}

	// FUNCTION: ENGINE 0x10B81630
	bool MemoryExternalAllocator::GetStat(int id, int* value)
	{
		AllocatorLock lock(this);
		switch (id)
		{
		case 0:
			*value = externalHeap.GetBlockCount();
			return true;
		case 1:
			*value = externalHeap.GetUsedBytes() + externalHeap.GetFreeBytes();
			return true;
		case 2:
			*value = externalHeap.GetUsedBytes();
			return true;
		case 3:
			*value = externalHeap.GetFreeBytes();
			return true;
		case 7:
			*value = externalHeap.GetPeakBytes();
			return true;
		case 8:
			*value = externalHeap.GetBlockLimit();
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10B81750
	bool MemoryExternalAllocator::ResetStat(int id)
	{
		AllocatorLock lock(this);
		if (id != 7)
		{
			return false;
		}
		externalHeap.ResetPeak();
		return true;
	}

	// FUNCTION: ENGINE 0x10B817A0
	int MemoryExternalAllocator::GetType()
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x10B817B0
	void MemoryExternalAllocator::GetRange(MemoryRange* range, int index)
	{
		unsigned int size = 0;
		externalHeap.GetMemory((void**)&range->start, &size);
		range->end = range->start + size;
	}

	// FUNCTION: ENGINE 0x10B81810
	MemoryExternalAllocator::~MemoryExternalAllocator()
	{
		void* memory = 0;
		unsigned int size = 0;
		externalHeap.GetMemory(&memory, &size);
		if (memoryHeap != -1)
		{
			HeapFree(memoryHeap, memory);
		}
	}

	// FUNCTION: ENGINE 0x10B81890
	const char* AllocatorBaseSub_NoStubs::GetName()
	{
		return AllocatorBase_Name::GetName();
	}

	// FUNCTION: ENGINE 0x10B818A0
	int AllocatorBaseSub_NoStubs::GetSafetyMode()
	{
		return GetMode();
	}

	// FUNCTION: ENGINE 0x10B818B0
	void AllocatorBaseSub_NoStubs::SetSafetyMode(int mode)
	{
		SetMode(mode, this);
	}

	// FUNCTION: ENGINE 0x10B818D0
	void AllocatorBaseSub_NoStubs::SetUnused(int value)
	{
		AllocatorBase_Safety::SetUnused(value);
	}

	// FUNCTION: ENGINE 0x10B818E0
	bool MemoryExternalAllocator::IsThreadSafe()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x10B818F0
	// The name is read back through the virtual GetName and dropped
	void MemoryExternalAllocator::Init(void* memory, unsigned int size, unsigned int count, unsigned int param, const char* name, int heap, int ownerHeap, void* block, int value)
	{
		SetName(name);
		unsigned int overhead = GetOverhead(count);
		memoryHeap = heap;
		selfHeap = ownerHeap;
		self = block;
		tag = value;
		GetName();
		externalHeap.Init(memory, size, (void*)param, overhead, (unsigned int)memory - 16, 16, count, 0);
	}

	// FUNCTION: ENGINE 0x10B81A10
	MemoryExternalAllocator::MemoryExternalAllocator()
	{
		memoryHeap = -1;
		selfHeap = -1;
		self = 0;
		tag = 0;
		refCount = 0;
	}

	// FUNCTION: ENGINE 0x10B81A70
	// The allocator and its block bookkeeping in one block of `heap`, the managed memory from `memoryHeap`
	IMemoryAllocator* NewPoolAllocator(int heap, int memoryHeap, unsigned int size, unsigned int count, int tag,
		const char* name)
	{
		void* self = HeapAlloc(heap, MemoryExternalAllocator::GetOverhead(count) + 0x5F0);
		void* bookkeeping = (char*)self + 0x5F0;
		void* memory = HeapAlloc(memoryHeap, size);
		MemoryExternalAllocator* allocator = new (self) MemoryExternalAllocator;
		allocator->Init(memory, size, count, (unsigned int)bookkeeping, name, memoryHeap, heap, self, tag);
		return allocator;
	}

	// FUNCTION: ENGINE 0x10B81B00
	// The same over memory the caller provides
	IMemoryAllocator* NewPoolAllocatorAt(int heap, void* memory, unsigned int size, unsigned int count, int tag,
		const char* name)
	{
		void* self = HeapAlloc(heap, MemoryExternalAllocator::GetOverhead(count) + 0x5F0);
		void* bookkeeping = (char*)self + 0x5F0;
		MemoryExternalAllocator* allocator = new (self) MemoryExternalAllocator;
		allocator->Init(memory, size, count, (unsigned int)bookkeeping, name, -1, heap, self, tag);
		return allocator;
	}
}
