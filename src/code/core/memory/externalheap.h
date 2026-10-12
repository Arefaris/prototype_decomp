// The heap behind core::MemoryExternalAllocator (class and all names guessed; unit 0x10B82F80 - 0x10B85690, file name
// memory/externalheap.cpp guessed): a TLSF allocator (two-level segregated free lists with bitmaps) whose bookkeeping
// lives outside the managed memory, so that the memory itself is never touched. Every block of the memory (free or
// allocated) has a 16-byte descriptor in an array of `limit + 3` descriptors; descriptors are found by 15-bit indices
// (0x7FFF: none). Allocated and free blocks are kept in a red-black tree by address (to find the block of a pointer
// and the neighbours of a block); free blocks also sit in the TLSF lists (next / prev). Two sentinel blocks mark the
// two ends of the memory.
#ifndef CORE_MEMORY_EXTERNALHEAP_H
#define CORE_MEMORY_EXTERNALHEAP_H

namespace core
{
	// A block descriptor (memory/externalheap.cpp): offset and size in 16-byte units, the TLSF list links (the previous
	// index split in two), the colour and the tree links. A class template explicitly instantiated in the unit: its
	// accessors are inlined and also emitted out of line.
	template<int Unused> struct ExternalBlockT;
	typedef ExternalBlockT<0> ExternalBlock;

	class ExternalHeap
	{
	public:
		// 0x10B833E0: bookkeeping bytes for `count` blocks, (count + 3) * 16
		static unsigned int GetOverhead(unsigned int count);
		ExternalHeap();
		~ExternalHeap();
		void Shutdown();
		// The managed block, when there is one
		void GetMemory(void** memory, unsigned int* size);
		// The span between the first and the last allocation
		void GetUsedRange(unsigned int* start, unsigned int* used);
		unsigned int GetBlockLimit();
		unsigned int GetBlockCount();
		unsigned int GetUsedBytes();
		unsigned int GetFreeBytes();
		unsigned int GetPeakBytes();
		void ResetPeak();

		// The descriptors: a free list through `next`
		void ClearBlocks();
		void InitFreeBlocks();
		unsigned short NewBlock();
		void DeleteBlock(unsigned short index);
		// The tree by offset
		void ClearTree();
		unsigned short FindBlock(unsigned int offset);
		// In-order neighbours
		unsigned short GetSuccessor(unsigned short index);
		unsigned short GetPredecessor(unsigned short index);
		void Rotate(unsigned short index, int side);
		void DoubleRotate(unsigned short index, int side);
		// The TLSF lists
		void ClearLists();
		void MappingInsert(unsigned int size, int* fl, int* sl);
		bool FindSuitable(unsigned int size, int* fl, int* sl);
		unsigned int ToAddress(unsigned int offset);
		unsigned int ToOffset(unsigned int address);
		void TreeInsert(unsigned short index);
		void TreeRemove(unsigned int offset);
		// A free list entry is the block in front of a gap, keyed by the gap's size
		void InsertFree(unsigned int size, unsigned short index);
		unsigned short FindFree(unsigned int size, unsigned short* following, int mode);
		bool RemoveFree(unsigned int size, unsigned short index);

		void Init(void* memory, unsigned int size, void* blocks, unsigned int overhead, unsigned int base, unsigned int align, unsigned int limit, int strategy);
		void* Alloc(unsigned int size, unsigned int align, int mode);
		// Allocates at the very end the strategy fills from (the far end of the free space)
		void* AllocEnd(unsigned int size, unsigned int align);
		void Free(void* block);
		// Moves the managed memory (all allocations must stay inside)
		bool Resize(unsigned int memory, unsigned int size);
		bool Grow(unsigned int amount);
		bool Shrink(unsigned int amount);

		unsigned int memory;
		unsigned int size;
		unsigned int base;
		unsigned int limit;
		unsigned int align;
		bool ready;
		// 0: allocate from the low end, 1: from the high end
		int strategy;
		unsigned int count;
		unsigned int used;
		unsigned int freeFront;
		unsigned int freeBack;
		unsigned int peak;
		ExternalBlock* blocks;
		unsigned short first;
		unsigned short last;
		unsigned short freeBlocks;
		unsigned short root;
		unsigned int flBitmap;
		unsigned int slBitmap[20];
		unsigned short heads[20][32];
	};
}

#endif
