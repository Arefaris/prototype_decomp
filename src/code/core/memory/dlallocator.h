// core::MemoryDlAllocator (RTTI name; vftables 0x10E47824 and, for the Object base at 0x44, 0x10E47818) and its base
// core::`anonymous namespace'::MemoryDlAllocator_Implementation (0x10E477CC / 0x10E477C0): an allocator over one block
// of memory managed by Doug Lea's malloc 2.7 (`anonymous namespace'::coreDlMalloc, a base at 0x4C: the malloc state,
// the fastbins and the chunks all live in the block; MORECORE moves a break through it). Unit 0x1064AE30 - 0x1064C41B
// (file name guessed). The classes are declared in core instead of the anonymous namespaces (their mangled names would
// carry a hash of the build path). Member and method names guessed; the dlmalloc parts keep dlmalloc's names.
#ifndef CORE_MEMORY_DLALLOCATOR_H
#define CORE_MEMORY_DLALLOCATOR_H

#include "code/core/memory/allocatorbase.h"
#include "code/core/object.h"

namespace core
{
	struct malloc_chunk
	{
		unsigned int prev_size;
		unsigned int size;
		malloc_chunk* fd;
		malloc_chunk* bk;
	};

	typedef malloc_chunk* mchunkptr;
	typedef malloc_chunk* mbinptr;
	typedef malloc_chunk* mfastbinptr;

	// dlmalloc 2.7's malloc_state, with the fastbins in an array of their own (null when fastbins are off)
	struct malloc_state
	{
		unsigned int max_fast;
		mfastbinptr* fastbins;
		mchunkptr top;
		mchunkptr last_remainder;
		mchunkptr bins[128 * 2];
		unsigned int binmap[4];
		unsigned long trim_threshold;
		unsigned int top_pad;
		unsigned int mmap_threshold;
		int n_mmaps;
		int n_mmaps_max;
		int max_n_mmaps;
		unsigned int pagesize;
		unsigned int mmapped_mem;
		unsigned int sbrked_mem;
		unsigned int max_sbrked_mem;
		unsigned int max_mmapped_mem;
		unsigned int max_total_mem;
	};

	typedef malloc_state* mstate;

	// The malloc itself: MORECORE hands out the block between the break and the end
	class coreDlMalloc
	{
	public:
		coreDlMalloc()
			: end(0), brk(0), alignment(0), fastbinCount(0), state(0)
		{
		}
		~coreDlMalloc()
		{
		}
		void malloc_init_state(mstate av);
		void malloc_consolidate(mstate av);
		int mALLOPt(int param_number, int value);
		char* MORECORE(long size);
		void fREe(void* mem);
		void* sYSMALLOc(unsigned int nb, mstate av);
		void* mALLOc(unsigned int bytes);
		void* mEMALIGn(unsigned int alignment, unsigned int bytes);
		void DisableFastbins();

		char* end;
		char* brk;
		unsigned int alignment;
		unsigned int fastbinCount;
		mstate state;
		char* base;
	};

	struct MemoryDlAllocator_Implementation : public AllocatorBaseSub, public Object, public coreDlMalloc
	{
	public:
		// The heap's own block (freed by the last Release), the block the malloc works in
		MemoryDlAllocator_Implementation(void* block, int heap, bool inPlace, void* memory, unsigned int size,
			const char* name, unsigned int align, bool noFastbins);
		virtual ~MemoryDlAllocator_Implementation();
		virtual void AddRef();
		virtual void Release();
		virtual void* Alloc(unsigned int size);
		virtual void Free(void* block);
		virtual void* AllocAligned(unsigned int size, unsigned int align);
		virtual void FreeAligned(void* block);
		virtual int GetType();
		virtual void GetRange(MemoryRange* range, int index);
		// 0 live allocations, 1 capacity, 2 bytes in use, 3 bytes free, 7 peak, 10 bytes requested, 17 allocations
		virtual bool GetStat(int id, int* value);
		virtual bool ResetStat(int id);
		virtual bool IsThreadSafe();

		void SetAutoRelease(bool on);
		bool GetStatUnlocked(int id, int* value);
		bool ResetStatUnlocked(int id);
		// Starts the malloc over (the last block was freed)
		void Reset();

		void* memory;
		unsigned int memorySize;
		unsigned int count;
		unsigned int total;
		unsigned int bytes;
		unsigned int requested;
		unsigned int peak;
		void* block;
		bool inPlace;
		int refs;
		int blockHeap;
		bool noFastbins;
		bool autoRelease;
	};

	class MemoryDlAllocator : public MemoryDlAllocator_Implementation
	{
	public:
		MemoryDlAllocator(void* block, int heap, bool inPlace, void* memory, unsigned int size, const char* name,
			unsigned int align, bool noFastbins);
		// Placed at the start of the caller's memory (CreateDlAllocator inlines it)
		MemoryDlAllocator(int heap, void* memory, unsigned int size, const char* name, unsigned int align,
			bool noFastbins)
			: MemoryDlAllocator_Implementation(0, heap, true, memory, size, name, align, noFastbins)
		{
		}
		virtual ~MemoryDlAllocator();

		void* operator new(unsigned int size, void* where);
		void* operator new(unsigned int size, int heap)
		{
			return Object::operator new(size, heap);
		}
	};

	// 0x1064C300: a dlmalloc allocator in memory of its own (allocate: from the heap, with the allocator in front),
	// or placed at the start of the caller's memory (inPlace), or over the caller's memory
	MemoryDlAllocator* CreateDlAllocator(bool allocate, int heap, bool inPlace, void* memory, unsigned int size,
		const char* name, unsigned int align, bool noFastbins, bool manual);
}

#endif
