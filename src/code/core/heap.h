// Heap allocation entry points of the core module (names guessed). Not reconstructed yet: HeapAlloc (0x1063A850)
// looks the heap up in a table of allocator objects (0x110BC5A4, 16 bytes per heap), calls its virtual Alloc (slot 3)
// and reports a failed allocation to a hook (0x11277F8C / 0x11277F90) before returning null.
#ifndef CORE_HEAP_H
#define CORE_HEAP_H

namespace core
{
	void* HeapAlloc(int heap, unsigned int size);
	// 0x1063A9A0: returns a block to its heap
	void HeapFree(int heap, void* block);
	// 0x1063A8D0 / 0x1063A9C0: the aligned pair (allocator slots 5 and 6); sizes below 4 bytes are rounded up to 4
	void* HeapAllocAligned(int heap, unsigned int size, unsigned int align);
	void HeapFreeAligned(int heap, void* block);
	// 0x1063A6F0: the heap the current thread allocates from (a thread-local slot), 0 when it has none
	int GetCurrentHeap();
	// 0x1063AC00: returns a block to whichever heap owns it
	void Free(void* block);
}

#endif
