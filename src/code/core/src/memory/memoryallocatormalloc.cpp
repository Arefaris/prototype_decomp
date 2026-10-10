#include <new>
#include <stdlib.h>

#include "code/core/memory/memoryallocatormalloc.h"

// The interlocked intrinsics, declared here instead of pulling in windows.h (the toolchain has no SDK headers)
extern "C"
{
	long _InterlockedIncrement(long volatile*);
	long _InterlockedDecrement(long volatile*);
	long _InterlockedAnd(long volatile*, long);
}
#pragma intrinsic(_InterlockedIncrement, _InterlockedDecrement, _InterlockedAnd)

namespace core
{
	// Read through GetStat(1); what writes it is not in this unit
	// GLOBAL: ENGINE 0x1127A898
	static int sPeakStat;
	// Raw storage for the static "system" allocator (constructed by InitSystemAllocator, not at start-up: the
	// original has no dynamic initialiser for it) and the pointer the rest of the memory system reads
	// GLOBAL: ENGINE 0x1127A884
	static int sSystemAllocatorStorage[sizeof(MemoryAllocatorMalloc) / sizeof(int)];
	// GLOBAL: ENGINE 0x1127A894
	static MemoryAllocatorMalloc* sSystemAllocator;

	// 0x106465D0 - 0x10646600 and 0x106467D0: four interlocked helpers with register arguments (atomic read
	// through _InterlockedAnd(p, -1), increment, decrement) that nothing in this unit calls; not reconstructed

	// FUNCTION: ENGINE 0x10646630
	void MemoryAllocatorMalloc::AddRef()
	{
	}

	// FUNCTION: ENGINE 0x10646640
	void MemoryAllocatorMalloc::Release()
	{
	}

	// FUNCTION: ENGINE 0x10646650
	void* MemoryAllocatorMalloc::AllocFlags(unsigned int size, unsigned int align, int flags, int unused)
	{
		if (flags != 0)
		{
			return 0;
		}
		return AllocAligned(size, align);
	}

	// FUNCTION: ENGINE 0x10646670
	void MemoryAllocatorMalloc::FreeFlags(void* block)
	{
		FreeAligned(block);
	}

	// FUNCTION: ENGINE 0x10646680
	int MemoryAllocatorMalloc::GetType()
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x10646690
	void MemoryAllocatorMalloc::GetRange(MemoryRange* range, int index)
	{
		range->start = 0;
		range->end = 0xFFFFFFFF;
	}

	// FUNCTION: ENGINE 0x106466B0
	bool MemoryAllocatorMalloc::ResetStat(int id)
	{
		if (id != 10)
		{
			return false;
		}
		bytesAllocated = 0;
		return true;
	}

	// FUNCTION: ENGINE 0x106466D0
	const char* MemoryAllocatorMalloc::GetName()
	{
		return "system";
	}

	// FUNCTION: ENGINE 0x106466E0
	void MemoryAllocatorMalloc::SetName(const char* name)
	{
	}

	// FUNCTION: ENGINE 0x106466F0
	int MemoryAllocatorMalloc::GetFlags()
	{
		return 2;
	}

	// FUNCTION: ENGINE 0x10646700
	void MemoryAllocatorMalloc::SetFlags(int flags)
	{
	}

	// FUNCTION: ENGINE 0x10646710
	bool MemoryAllocatorMalloc::IsThreadSafe()
	{
		return true;
	}

	// The static helpers take their arguments in registers (size in eax, align in ecx)

	// FUNCTION: ENGINE 0x10646750
	static void* SystemMalloc(unsigned int size)
	{
		if (size == 0)
		{
			size = 1;
		}
		return malloc(size);
	}

	// FUNCTION: ENGINE 0x10646770
	static void SystemFree(void* block)
	{
		free(block);
	}

	// FUNCTION: ENGINE 0x10646780
	// Over-allocates by align, aligns the result and keeps the raw pointer in the word before it
	static void* AlignedMalloc(unsigned int size, unsigned int align)
	{
		if (align < 4)
		{
			align = 4;
		}
		unsigned int raw = (unsigned int)SystemMalloc(size + align);
		unsigned int aligned = raw - raw % align + align;
		((unsigned int*)aligned)[-1] = raw;
		return (void*)aligned;
	}

	// FUNCTION: ENGINE 0x106467B0
	static void AlignedFree(void* block)
	{
		if (block != 0)
		{
			SystemFree((void*)((unsigned int*)block)[-1]);
		}
	}

	// FUNCTION: ENGINE 0x106467C0
	static int GetPeakStat()
	{
		return sPeakStat;
	}

	// FUNCTION: ENGINE 0x106467F0
	void* MemoryAllocatorMalloc::AllocAligned(unsigned int size, unsigned int align)
	{
		void* block = AlignedMalloc(size, align);
		if (block != 0)
		{
			_InterlockedIncrement(&allocationCount);
		}
		bytesAllocated += (size != 0) ? RoundUp(size, align) : align;
		return block;
	}

	// FUNCTION: ENGINE 0x10646850
	void MemoryAllocatorMalloc::FreeAligned(void* block)
	{
		if (block != 0)
		{
			_InterlockedDecrement(&allocationCount);
			AlignedFree(block);
		}
	}

	// FUNCTION: ENGINE 0x10646870
	bool MemoryAllocatorMalloc::GetStat(int id, int* value)
	{
		switch (id)
		{
		case 0:
			*value = _InterlockedAnd(&allocationCount, -1);
			return true;
		case 1:
			*value = GetPeakStat();
			return true;
		case 10:
			*value = bytesAllocated;
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x106468D0
	static void* DefaultMalloc(unsigned int size)
	{
		return AlignedMalloc(size, 16);
	}

	// FUNCTION: ENGINE 0x106468E0
	static void DefaultFree(void* block)
	{
		AlignedFree(block);
	}

	// FUNCTION: ENGINE 0x106468F0
	void* MemoryAllocatorMalloc::Alloc(unsigned int size)
	{
		void* block = DefaultMalloc(size);
		if (block != 0)
		{
			_InterlockedIncrement(&allocationCount);
		}
		bytesAllocated += (size != 0) ? RoundUp(size, 16) : 16;
		return block;
	}

	// FUNCTION: ENGINE 0x10646940
	void MemoryAllocatorMalloc::Free(void* block)
	{
		if (block != 0)
		{
			_InterlockedDecrement(&allocationCount);
			DefaultFree(block);
		}
	}

	// FUNCTION: ENGINE 0x10646960
	MemoryAllocatorMalloc* InitSystemAllocator()
	{
		sSystemAllocator = new (sSystemAllocatorStorage) MemoryAllocatorMalloc();
		return sSystemAllocator;
	}

	// FUNCTION: ENGINE 0x10646990
	MemoryAllocatorMalloc* GetSystemAllocatorInit()
	{
		return InitSystemAllocator();
	}
}
