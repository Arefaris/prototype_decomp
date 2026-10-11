// Heap allocation entry points of the core module (names guessed). Not reconstructed yet: HeapAlloc (0x1063A850)
// looks the heap up in a table of allocator objects (0x110BC5A4, 16 bytes per heap), calls its virtual Alloc (slot 3)
// and reports a failed allocation to a hook (0x11277F8C / 0x11277F90) before returning null.
#ifndef CORE_HEAP_H
#define CORE_HEAP_H

namespace core
{
	struct IMemoryAllocator;

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

	struct IMemoryAllocator;

	// 0x1063AAD0 / 0x1063AAF0: makes heap the thread's current heap for the object's lifetime
	class HeapScope
	{
	public:
		explicit HeapScope(int heap);
		~HeapScope();

		int previous;
	};

	// 0x1063AA00: the allocator object behind a heap index
	IMemoryAllocator* GetHeapAllocator(int heap);
	// 0x1063AF60 / 0x1063AE10: install an allocator in the heap table (the first form also records the heap it was
	// carved from)
	void RegisterHeap(int index, int parent, IMemoryAllocator* allocator);
	void RegisterHeap(int index, IMemoryAllocator* allocator);
	// 0x1063A740: the allocator the system heap (0x100) hands out from
	void SetSystemAllocator(IMemoryAllocator* allocator);
	// 0x1063AD50: removes a heap from the table again
	void UnregisterHeap(int heap);
	// 0x1063A7F0: the hook a failed allocation reports to (0x11277F8C) and the value passed back to it (0x11277F90)
	void SetAllocFailHook(void (*hook)(int heap), void* user);
	// 0x1063C7D0, 0x1063AB80, 0x10645120: start-up of the core memory system, called before the first heap exists
	void InitMemoryStage1();
	void InitMemoryStage2();
	void InitMemoryStage3(int count);
	// 0x10645400 / 0x10645430: heap allocators carved from a parent heap or placed over memory the caller owns
	IMemoryAllocator* NewHeapAllocator(unsigned int size, int parent, const char* name, unsigned int align, int unknown,
		bool flag);
	IMemoryAllocator* NewHeapAllocatorAt(void* memory, unsigned int size, const char* name, int unknown1,
		unsigned int align, int unknown2, int unknown3);
	// 0x10B81A70: an allocator factory of another kind (arguments partly unknown)
	IMemoryAllocator* NewPoolAllocator(int a, int b, unsigned int c, unsigned int d, int e, const char* name);
}

#endif
