// The engine's memory setup unit (0x107DEAE0-0x107DF240): the global operator new / delete that route to the core
// heaps once gHeapReady is set, heap creation and the configuration structs it is driven by. Only the small parts
// are reconstructed; names and the meaning of the configuration fields are guesses.
#ifndef ENGINE_MEMORY_MEMORY_H
#define ENGINE_MEMORY_MEMORY_H

namespace engine
{
	// Set by the memory initialisation (0x107DF020); before it operator new returns null and delete does nothing
	extern bool gHeapReady;

	// Defaults: a 256 KB heap with 4 KB / 64 KB block sizes and 32 of something
	class HeapConfig
	{
	public:
		bool flag;
		int unknown4;
		int size;
		int unknownC;
		int smallBlock;
		int largeBlock;
		int count;

		HeapConfig();
	};

	// Defaults: indices -1, type 2, alignment 16
	class HeapConfig2
	{
	public:
		int index;
		int unknown4;
		int unknown8;
		int unknownC;
		int parent;
		int type;
		int alignment;
		bool flag1C;
		int unknown20;
		bool flag24;

		HeapConfig2();
	};
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
