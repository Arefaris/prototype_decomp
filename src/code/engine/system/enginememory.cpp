#include "code/core/debug.h"
#include "code/core/heap.h"
#include "code/core/memory/debugallocator.h"
#include "code/core/memory/imemoryallocator.h"
#include "code/core/memory/segmentpoolallocator.h"
#include "code/core/memory/spilloverallocator.h"
#include "code/core/memory/twowayallocator.h"
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
			allocator = core::CreateDebugAllocator(allocator, 2, config.heap);
		}
		if (config.track != -1)
		{
			allocator = core::CreateSpillOverHeapAllocator(allocator, config.track, config.heap, 0, 0);
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
			allocator = core::CreateDebugAllocator(allocator, 2, heap);
		}
		if (track != -1)
		{
			allocator = core::CreateSpillOverHeapAllocator(allocator, track, heap, 0, 0);
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

	// HeapConfig2's constructor is inline in the header; this is its kept copy
	// FUNCTION: ENGINE 0x107DEFF0

	// FUNCTION: ENGINE 0x107DF270
	core::IMemoryAllocator* CreateHeap(int index, unsigned int size, unsigned int extraSize, const char* name, int heap,
		int safetyMode, bool guard, int track, bool flag)
	{
		HeapConfig2 config;
		config.index = index;
		config.size = size;
		config.extraSize = extraSize;
		config.name = name;
		config.heap = heap;
		config.safetyMode = safetyMode;
		config.guard = guard;
		config.track = track;
		config.flag = flag;
		return CreateHeap(config);
	}

	// FUNCTION: ENGINE 0x107DECD0
	// NONMATCHING: the kind arrives in eax, not on the stack, 0 %. The engine's OnAllocFail (0x107DED20) already has
	// the kind in eax when it reaches it, so the compiler gave this internal function a register parameter - a
	// convention MSVC 2005 only hands out under whole-program optimisation, so plain /O2 puts our argument on the
	// stack and the switch cannot reach the same code. The body is the engine's otherwise.
#ifdef NONMATCHING
	const char* GetHeapKindName(int kind)
	{
		switch (kind)
		{
		case 0:
			return "None";
		case 1:
			return "Uncached";
		case 2:
			return "WriteCombine";
		case 3:
			return "Vram";
		case 4:
			return "Vram Preferred";
		case 5:
			return "Vram (heap default)";
		default:
			return "Unknown";
		}
	}
#endif

	// FUNCTION: ENGINE 0x107DF2D0
	core::IMemoryAllocator* CreateBlockHeap(int index, unsigned int count, unsigned int size, int unknown, int unused,
		const char* name, int heap, int safetyMode)
	{
		core::SegmentPoolAllocator* pool;
		core::CreateSegmentPoolAllocator(&pool, count, size, unused, heap, name);
		pool->SetSafetyMode(safetyMode);
		core::RegisterHeap(index, heap, pool);
		pool->Release();
		return pool;
	}

	// GLOBAL: ENGINE 0x111BBF84
	static bool sReportLiveAllocations = true;

	// FUNCTION: ENGINE 0x107DF330
	void DestroyHeap(int heap)
	{
		int liveBlocks;
		const char* name;
		GetHeapStats(heap, 0, 0, 0, &liveBlocks, &name);
		if (liveBlocks != 0 && sReportLiveAllocations)
		{
			if (core::Report(0, 0, "..\\..\\..\\code\\engine\\system\\enginememory.cpp", 911, 0,
				"Error: Allocator \"%s\" is being destroyed with %d objects still allocated\n", name, liveBlocks, 0) == 3)
			{
				sReportLiveAllocations = false;
			}
		}
		core::UnregisterHeap(heap);
	}
}
