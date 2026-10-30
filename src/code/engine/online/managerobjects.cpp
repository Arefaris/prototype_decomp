// The allocation of the online unit's manager classes (0x108EC840 - 0x108EC860; no assert path, file name guessed).
#include "code/core/heap.h"
#include "code/engine/online/onlinemanager.h"

namespace engine
{
	// The heap a manager class picks with the selector 1 (0x111E2060; name guessed)
	extern int gManagerHeap;

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
