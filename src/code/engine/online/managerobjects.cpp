// The allocation of the online unit's manager classes (0x108EC840 - 0x108EC860; no assert path, file name guessed).
#include "code/core/heap.h"
#include "code/engine/online/onlinemanager.h"
#include "code/engine/system/desynchunter.h"
#include "code/engine/system/enginememory.h"

namespace engine
{
	// The heap a manager class picks with the selector 1 (0x111E2060; name guessed)
	extern int gManagerHeap;

	// The allocator of the heap the desync checker uses (0x1131B0A0; null while there is none; name guessed)
	extern core::IMemoryAllocator* gDesyncAllocator;

	// FUNCTION: ENGINE 0x108EC7C0
	void CreateDesyncHeap(DesyncSettings* settings)
	{
		if (gDesyncAllocator == 0)
		{
			gDesyncAllocator = core::GetHeapAllocator(0x81);
			CreateHeap(0x82, 0x800, 0, "Desync", 0x6f, 2, false, -1, false);
			gManagerHeap = settings->heap;
		}
	}

	// FUNCTION: ENGINE 0x108EC810
	void DestroyDesyncHeap()
	{
		if (gDesyncAllocator != 0)
		{
			gManagerHeap = 1;
			DestroyHeap(0x82);
			gDesyncAllocator = 0;
		}
	}

	// FUNCTION: ENGINE 0x108EC840
	void FreeManagerObject(void* object)
	{
		core::Free(object);
	}

	// FUNCTION: ENGINE 0x108EC860
	void* AllocateManagerObject(unsigned int size, int heap, const char* name)
	{
		void* block = 0;
		switch (heap)
		{
		case 0:
			block = core::HeapAlloc(0x81, size);
			break;
		case 1:
			block = core::HeapAlloc(gManagerHeap, size);
			break;
		case 2:
			block = core::HeapAlloc(0x82, size);
			break;
		}
		return block;
	}
}
