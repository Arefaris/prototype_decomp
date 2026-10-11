#include "code/core/heap.h"
#include "code/core/memory/imemoryallocator.h"
#include "code/core/strings.h"
#include "code/engine/system/enginememory.h"

// FUNCTION: ENGINE 0x107DEF50
void* operator new(unsigned int size)
{
	if (!engine::gHeapReady)
	{
		return 0;
	}
	return core::HeapAlloc(core::GetCurrentHeap(), size);
}

// FUNCTION: ENGINE 0x107DEF70
void* operator new[](unsigned int size)
{
	if (!engine::gHeapReady)
	{
		return 0;
	}
	return core::HeapAlloc(core::GetCurrentHeap(), size);
}

// FUNCTION: ENGINE 0x107DEF90
void* operator new(unsigned int size, int heap)
{
	return core::HeapAlloc(heap, size);
}

// FUNCTION: ENGINE 0x107DEFB0
void* operator new[](unsigned int size, int heap)
{
	return core::HeapAlloc(heap, size);
}

// FUNCTION: ENGINE 0x107DEFD0
void operator delete(void* block)
{
	if (engine::gHeapReady)
	{
		core::Free(block);
	}
}

// FUNCTION: ENGINE 0x107DEFE0
void operator delete[](void* block)
{
	if (engine::gHeapReady)
	{
		core::Free(block);
	}
}

namespace engine
{
	// FUNCTION: ENGINE 0x107DEAE0
	core::IMemoryAllocator* CreateHeap(const HeapConfig2& config)
	{
		core::IMemoryAllocator* allocator = core::NewHeapAllocator(config.extraSize + config.size, config.heap,
			config.name, config.alignment, 0, config.flag);
		if (config.guard)
		{
			allocator = core::WrapAllocatorGuard(allocator, 2, config.heap);
		}
		if (config.track != -1)
		{
			allocator = core::WrapAllocatorTrack(allocator, config.track, config.heap, 0, 0);
		}
		allocator->SetSafetyMode(config.safetyMode);
		core::RegisterHeap(config.index, config.heap, allocator);
		return allocator;
	}

	// FUNCTION: ENGINE 0x107DEB60
	core::IMemoryAllocator* CreateTwoWayHeap(int index, unsigned int size, unsigned int extraSize, const char* name,
		int heap, int safetyMode, bool guard, int track)
	{
		core::IMemoryAllocator* allocator = core::NewTwoWayAllocator(size + extraSize, heap, name, 16);
		if (guard)
		{
			allocator = core::WrapAllocatorGuard(allocator, 2, heap);
		}
		if (track != -1)
		{
			allocator = core::WrapAllocatorTrack(allocator, track, heap, 0, 0);
		}
		allocator->SetSafetyMode(safetyMode);
		core::RegisterHeap(index, heap, allocator);
		return allocator;
	}

	// FUNCTION: ENGINE 0x107DEBE0
	core::IMemoryAllocator* CreatePoolHeap(int index, unsigned int a, unsigned int b, const char* name, int heap, int c,
		int safetyMode)
	{
		core::IMemoryAllocator* allocator = core::NewPoolAllocator(c, heap, a, b, 0, name);
		allocator->SetSafetyMode(safetyMode);
		core::RegisterHeap(index, allocator);
		return allocator;
	}

	// FUNCTION: ENGINE 0x107DEC30
	void GetHeapStats(int heap, int* capacity, int* betweenCursors, int* bytesFree, int* liveBlocks, const char** name)
	{
		core::IMemoryAllocator* allocator = core::GetHeapAllocator(heap);
		if (capacity != 0 && !allocator->GetStat(1, capacity))
		{
			*capacity = 0;
		}
		if (betweenCursors != 0 && !allocator->GetStat(3, betweenCursors))
		{
			*betweenCursors = 0;
		}
		if (liveBlocks != 0 && !allocator->GetStat(0, liveBlocks))
		{
			*liveBlocks = 0;
		}
		if (bytesFree != 0 && !allocator->GetStat(7, bytesFree))
		{
			*bytesFree = 0;
		}
		if (name != 0)
		{
			*name = allocator->GetName();
		}
	}

	// FUNCTION: ENGINE 0x107DF020
	void InitMemory(const HeapConfig& config)
	{
		core::InitMemoryStage1();
		core::InitMemoryStage2();
		gHeapReady = true;
		core::InitMemoryStage3(30);
		core::SetAllocFailHook(OnAllocFail, 0);
		// The system heap's capacity is queried and then replaced by a fixed 256 MB
		int available = 0;
		core::GetHeapAllocator(0x100)->GetStat(1, &available);
		available = 0x10000000;
		if (config.reserveSize != 0)
		{
			gReserveBlock = core::HeapAlloc(0x100, config.reserveSize);
			available -= config.reserveSize;
		}
		if (config.createSystemHeap)
		{
			available -= 0x32000;
			gSystemHeapMemory = core::HeapAlloc(0x100, available);
			core::IMemoryAllocator* allocator = core::NewHeapAllocatorAt(gSystemHeapMemory, available, "System Heap", 1,
				0x10, 0, 0);
			allocator->SetSafetyMode(2);
			core::SetSystemAllocator(allocator);
		}
		core::SetStringHeap(0x6F);
	}

	// FUNCTION: ENGINE 0x107DEF00
	HeapConfig::HeapConfig()
	{
		createSystemHeap = false;
		reserveSize = 0;
		size = 0x40000;
		unknownC = 0;
		smallBlock = 0x1000;
		largeBlock = 0x10000;
		count = 0x20;
	}

	// FUNCTION: ENGINE 0x107DEFF0
	HeapConfig2::HeapConfig2()
	{
		index = -1;
		size = 0;
		extraSize = 0;
		name = 0;
		heap = -1;
		safetyMode = 2;
		alignment = 0x10;
		guard = false;
		track = -1;
		flag = false;
	}
}
