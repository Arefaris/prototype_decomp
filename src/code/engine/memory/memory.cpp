#include "code/core/heap.h"
#include "code/engine/memory/memory.h"

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
	// FUNCTION: ENGINE 0x107DEF00
	HeapConfig::HeapConfig()
	{
		flag = false;
		unknown4 = 0;
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
		unknown4 = 0;
		unknown8 = 0;
		unknownC = 0;
		parent = -1;
		type = 2;
		alignment = 0x10;
		flag1C = false;
		unknown20 = -1;
		flag24 = false;
	}
}
