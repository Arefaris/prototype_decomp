// om::CoreAllocator (RTTI: derived from om::Allocator): an allocator of the om library that hands out the blocks of one
// heap of the core module.
#ifndef OM_COREALLOCATOR_H
#define OM_COREALLOCATOR_H

#include "code/om/allocation.h"
#include "code/om/allocator.h"

namespace om
{
	class CoreAllocator : public Allocator
	{
	public:
		// 0x10AAAC00: an allocator of the heap
		explicit CoreAllocator(int newHeap);
		// Slots 1 to 4 (0x10AAAB10 / 0x10AAAB30 / 0x10AAAB50 / 0x10AAAB70)
		virtual void* Allocate(const char* tag, unsigned int size, unsigned int alignment);
		virtual void Release(void* memory, unsigned int size, unsigned int alignment);
		virtual void* AllocateTracked(const char* tag, unsigned int size, unsigned int alignment);
		virtual void ReleaseTracked(void* memory);
		// Slots 5 and 6 (0x10AAAB90 / 0x10AAABD0): ask the heap's allocator for a statistic (names guessed)
		virtual int Slot5();
		virtual int Slot6();
		OM_ALLOCATION(CoreAllocator);

		int heap;  // 4
	};
}

#endif
