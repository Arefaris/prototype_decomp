// code/engine/system/enginememory.cpp (assert path at 0x10E6818C), 0x107DEAE0-0x107DF240: the global operator new /
// delete that route to the core heaps once gHeapReady is set, heap creation and the configuration structs it is
// driven by. Names and the meaning of the configuration fields are guesses.
#ifndef ENGINE_SYSTEM_ENGINEMEMORY_H
#define ENGINE_SYSTEM_ENGINEMEMORY_H

namespace core
{
	struct IMemoryAllocator;
}

namespace engine
{
	// Defaults: a 256 KB heap with 4 KB / 64 KB block sizes and 32 of something. InitMemory reads the first two fields.
	class HeapConfig
	{
	public:
		// Creates the "System Heap" over the memory left once the reserve is taken
		bool createSystemHeap;
		// Bytes kept back from the system heap in one block (gReserveBlock)
		int reserveSize;
		int size;
		int unknownC;
		int smallBlock;
		int largeBlock;
		int count;

		HeapConfig();
	};

	// One heap of the heap table, as CreateHeap builds it. Defaults: indices -1, safety mode 2, alignment 16
	class HeapConfig2
	{
	public:
		int index;
		unsigned int size;
		unsigned int extraSize;
		const char* name;
		// The heap the allocator's memory comes from
		int heap;
		int safetyMode;
		unsigned int alignment;
		bool guard;
		int track;
		bool flag;

		// Inline: CreateHeap's argument form builds one on the stack (0x107DEFF0 is the kept copy)
		HeapConfig2()
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
	};

	// Set by InitMemory; before it operator new returns null and delete does nothing
	extern bool gHeapReady;
	// 0x11283284: the block InitMemory reserves (HeapConfig::reserveSize bytes); 0x1128328C: the system heap's memory
	extern void* gReserveBlock;
	extern void* gSystemHeapMemory;

	// Creates the heap a configuration describes, stacks the guard / tracking wrappers it asks for, sets its safety
	// mode and installs it in the heap table
	core::IMemoryAllocator* CreateHeap(const HeapConfig2& config);
	// The same from the fields as arguments (the alignment stays 16)
	core::IMemoryAllocator* CreateHeap(int index, unsigned int size, unsigned int extraSize, const char* name, int heap,
		int safetyMode, bool guard, int track, bool flag);
	// A heap backed by a segment pool allocator (core::CreateSegmentPoolAllocator); the fourth argument is not used
	core::IMemoryAllocator* CreateBlockHeap(int index, unsigned int count, unsigned int size, int unknown, int unused,
		const char* name, int heap, int safetyMode, int unknown9);
	// Reports allocations still live in the heap, then removes it from the heap table
	void DestroyHeap(int heap);
	// The same for a two-way allocator taken from another heap
	core::IMemoryAllocator* CreateTwoWayHeap(int index, unsigned int size, unsigned int extraSize, const char* name,
		int heap, int safetyMode, bool guard, int track);
	// The same for the third allocator kind (arguments partly unknown); it is installed without a parent heap
	core::IMemoryAllocator* CreatePoolHeap(int index, unsigned int a, unsigned int b, const char* name, int heap, int c,
		int safetyMode);
	// Reads a heap's statistics into the non-null outputs (0 when the allocator does not know one) and its name
	void GetHeapStats(int heap, int* capacity, int* betweenCursors, int* bytesFree, int* liveBlocks, const char** name);
	// Starts the core memory system, reserves memory, creates the system heap and points strings at heap 0x6F
	void InitMemory(const HeapConfig& config);
	// 0x107DED20: the allocation failure hook InitMemory installs; it reports the heap's figures
	void OnAllocFail(void* user, int heap, unsigned int size, unsigned int align, int flags);
}

// The engine's global allocation operators (0x107DEF50-0x107DEFE0): the plain forms allocate from the current
// thread's heap, the (size, heap) forms from the given one
void* operator new(unsigned int size);
void* operator new[](unsigned int size);
void* operator new(unsigned int size, int heap);
void* operator new[](unsigned int size, int heap);
void operator delete(void* block);
void operator delete[](void* block);

#endif
