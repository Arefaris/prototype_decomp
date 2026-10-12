// The heaps of the core module (unit 0x1063A6A0 - 0x1063AF72, file name heap.cpp and all names guessed): a table of
// 0x101 heap entries (0x110BC5A4 points at it), each an allocator object plus links that make the heaps a tree (a heap
// registered over memory of another heap is its child). Index 0x100 and every unregistered index stand for the system
// heap, whose allocator is the malloc allocator until SetSystemAllocator installs another. A range map (0x11277F98)
// records which heap owns which address range, so that a block can be freed without knowing its heap. The current
// heap of a thread lives in a thread data slot (0x11276F50).
#ifndef CORE_HEAP_H
#define CORE_HEAP_H

namespace core
{
	struct IMemoryAllocator;

	// Told about every allocation that fails (align 1 for HeapAlloc, flags 0 unless given)
	typedef void (*AllocFailHook)(void* user, int heap, unsigned int size, unsigned int align, int flags);

	void MemoryNop1();
	void MemoryNop2();
	// The counterpart of InitMemoryStage2
	void ShutdownMemoryStage2();
	// The heap the current thread allocates from (a thread data slot), 0 when it has none
	int GetCurrentHeap();
	// Returns the previous one (0 when the thread has no slot)
	int SetCurrentHeap(int heap);
	// The allocator every heap without one of its own uses (the system heap)
	void SetSystemAllocator(IMemoryAllocator* allocator);
	// Back to the malloc allocator; releases the one installed
	void ResetSystemAllocator();
	void SetAllocFailHook(AllocFailHook hook, void* user);
	void* HeapAlloc(int heap, unsigned int size);
	// HeapAlloc, the block cleared
	void* HeapAllocZero(int heap, unsigned int size);
	// Alignments below 4 bytes are rounded up to 4
	void* HeapAllocAligned(int heap, unsigned int size, unsigned int align);
	void* HeapAllocFlags(int heap, unsigned int size, unsigned int align, int flags, int unused);
	void HeapFree(int heap, void* block);
	void HeapFreeAligned(int heap, void* block);
	void HeapFreeFlags(int heap, void* block);
	// The allocator object behind a heap index
	IMemoryAllocator* GetHeapAllocator(int heap);

	// Makes heap the thread's current heap for the object's lifetime
	class HeapScope
	{
	public:
		explicit HeapScope(int heap);
		~HeapScope();

		int previous;
	};

	void MemoryNop3();
	void MemoryNop4();
	void AddRefAllocator(IMemoryAllocator* allocator);
	void ReleaseAllocator(IMemoryAllocator* allocator);
	// 0x1063C7D0, 0x1063AB80, 0x10645120: start-up of the core memory system, called before the first heap exists
	void InitMemoryStage1();
	void InitMemoryStage2();
	void InitMemoryStage3(int count);
	// Return a block to whichever heap owns it
	void Free(void* block);
	void FreeAligned(void* block);
	void FreeFlags(void* block);
	IMemoryAllocator* GetBlockAllocator(void* block);
	// True when the block lies in the heap and in none of the heaps registered inside it (true for null, false for
	// heap -1)
	bool IsBlockInHeap(void* block, int heap);
	// Removes a heap from the table again: the heaps inside it move to a sibling with the same allocator (or to its
	// parent), its address ranges go with them
	void UnregisterHeap(int heap);
	// Installs an allocator in the heap table (AddRef) and files its address ranges; the parent is found from them
	void RegisterHeap(int index, IMemoryAllocator* allocator);
	// The same; parent is not used
	void RegisterHeap(int index, int parent, IMemoryAllocator* allocator);

	// 0x10645400 - 0x10645460 (memory/twowayallocator.cpp): dlmalloc heap allocators (CreateDlAllocator) in a block of
	// the parent heap, placed at the start of memory the caller owns, or over the caller's memory (the allocator
	// object itself from `heap`)
	IMemoryAllocator* NewHeapAllocator(unsigned int size, int parent, const char* name, unsigned int align,
		bool noFastbins, bool manual);
	IMemoryAllocator* NewHeapAllocatorAt(void* memory, unsigned int size, const char* name, int unused,
		unsigned int align, bool noFastbins, bool manual);
	IMemoryAllocator* NewHeapAllocatorOver(void* memory, unsigned int size, int heap, const char* name, int unused,
		unsigned int align, bool noFastbins, bool manual);
	// 0x10B81A70 / 0x10B81B00 (memory/externalallocator.cpp): a MemoryExternalAllocator (block heap) in a block of
	// `heap`, over memory from `memoryHeap` / over the caller's memory
	IMemoryAllocator* NewPoolAllocator(int heap, int memoryHeap, unsigned int size, unsigned int count, int tag,
		const char* name);
	IMemoryAllocator* NewPoolAllocatorAt(int heap, void* memory, unsigned int size, unsigned int count, int tag,
		const char* name);
}

#endif
