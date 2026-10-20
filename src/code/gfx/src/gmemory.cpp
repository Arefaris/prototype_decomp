// The Scaleform GFx allocators inside the engine DLL (the unit starting at 0x10959470; file name guessed).
#include "code/gfx/gmemory.h"

// FUNCTION: ENGINE 0x10959470
int GAllocator::Unknown10()
{
	return 0;
}

// FUNCTION: ENGINE 0x10959500
GDebugAllocator::GDebugAllocator()
{
}

// FUNCTION: ENGINE 0x10959510
void GMemory::SetGlobalAllocator(GAllocator* allocator)
{
	sGlobalAllocator = allocator;
	if (allocator == 0)
	{
		sGlobalAllocator = &gStandardAllocator;
	}
}

// FUNCTION: ENGINE 0x10959530
GAllocator* GMemory::GetGlobalAllocator()
{
	return sGlobalAllocator;
}

// FUNCTION: ENGINE 0x10959540
void GMemory::SetDebugAllocator(GDebugAllocator* allocator)
{
	sDebugAllocator = allocator;
	if (allocator == 0)
	{
		sDebugAllocator = &gDefaultDebugAllocator;
	}
}

// FUNCTION: ENGINE 0x10959560
GDebugAllocator* GMemory::GetDebugAllocator()
{
	return sDebugAllocator;
}

// FUNCTION: ENGINE 0x10959570
void GMemory::SetBlockAllocator(GAllocator* allocator)
{
	sBlockAllocator = allocator;
	if (allocator == 0)
	{
		sBlockAllocator = &gStandardBlockAllocator;
	}
}

// FUNCTION: ENGINE 0x10959590
GAllocator* GMemory::GetBlockAllocator()
{
	return sBlockAllocator;
}

// FUNCTION: ENGINE 0x109595A0
void* GMemory::Alloc(unsigned int size)
{
	return sGlobalAllocator->Alloc(size);
}

// FUNCTION: ENGINE 0x109595B0
void* GMemory::Realloc(void* block, unsigned int size)
{
	return sGlobalAllocator->Realloc(block, size);
}

// FUNCTION: ENGINE 0x109595C0
void GMemory::Free(void* block)
{
	sGlobalAllocator->Free(block);
}

// FUNCTION: ENGINE 0x109595D0
void* GMemory::AllocAligned(unsigned int size, unsigned int alignment, unsigned int extra)
{
	return sGlobalAllocator->AllocAligned(size, alignment, extra);
}

// FUNCTION: ENGINE 0x109595E0
void GMemory::FreeAligned(void* block)
{
	sGlobalAllocator->FreeAligned(block);
}
