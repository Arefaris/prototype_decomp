// core::AllocatorBaseSub_NoStubs (vftable 0x10EAEEC4) and core::MemoryExternalAllocator (vftable 0x10EAEE74; RTTI
// names): an allocator over a block of memory managed by an embedded heap object (ExternalHeap, name guessed; its
// methods live at 0x10B833E0 - 0x10B853A0, another unit). Unit 0x10B814E0 - 0x10B81A61 (no assert path; file name
// memory/externalallocator.cpp guessed). Layout: AllocatorBaseSub_NoStubs at 0 (AllocatorBase at 4), the heap at
// 0x44 (0x590 bytes), then five words. Member names guessed.
#ifndef CORE_MEMORY_EXTERNALALLOCATOR_H
#define CORE_MEMORY_EXTERNALALLOCATOR_H

#include "code/core/memory/allocatorbase.h"

namespace core
{
	// AllocatorBaseSub without the AllocFlags / FreeFlags stubs (only the name and safety slots are filled in)
	class AllocatorBaseSub_NoStubs : public IMemoryAllocator, public AllocatorBase
	{
	public:
		virtual const char* GetName();
		virtual void SetSafetyMode(int mode);
		virtual int GetSafetyMode();
		virtual void SetUnused(int value);
	};

	// The heap behind MemoryExternalAllocator; only what the allocator calls is declared
	class ExternalHeap
	{
	public:
		// 0x10B833E0: bookkeeping bytes for `count` blocks, (count + 3) * 16
		static unsigned int GetOverhead(unsigned int count);
		// 0x10B833F0 / 0x10B83430
		ExternalHeap();
		~ExternalHeap();
		// 0x10B84E00
		void Init(void* memory, unsigned int size, unsigned int param, unsigned int overhead, unsigned int limit, unsigned int align, unsigned int count, int flags);
		// 0x10B83450: the managed block, when there is one
		void GetMemory(void** memory, unsigned int* size);
		// 0x10B834A0 - 0x10B834F0
		unsigned int GetBlockLimit();
		unsigned int GetBlockCount();
		unsigned int GetUsedBytes();
		unsigned int GetFreeBytes();
		unsigned int GetPeakBytes();
		void ResetPeak();
		// 0x10B84F50 / 0x10B853A0
		void* Alloc(unsigned int size, unsigned int align, int flags);
		void Free(void* block);

		unsigned char storage[0x590];
	};

	class MemoryExternalAllocator : public AllocatorBaseSub_NoStubs
	{
	public:
		MemoryExternalAllocator();
		virtual ~MemoryExternalAllocator();
		// A plain (not interlocked) reference count; the last Release destroys the object in place and frees the
		// block it lives in
		virtual void AddRef();
		virtual void Release();
		virtual void* Alloc(unsigned int size);
		virtual void Free(void* block);
		virtual void* AllocAligned(unsigned int size, unsigned int align);
		virtual void FreeAligned(void* block);
		// Only for the allocator's own tag (flags must equal it)
		virtual void* AllocFlags(unsigned int size, unsigned int align, int flags, int unused);
		virtual void FreeFlags(void* block);
		virtual int GetType();
		virtual void GetRange(MemoryRange* range, int index);
		// 0 blocks, 1 used + free bytes, 2 used, 3 free, 7 peak, 8 block limit
		virtual bool GetStat(int id, int* value);
		virtual bool ResetStat(int id);
		virtual bool IsThreadSafe();

		static unsigned int GetOverhead(unsigned int count);
		void Init(void* memory, unsigned int size, unsigned int count, unsigned int param, const char* name, int heap, int selfHeap, void* self, int tag);

		ExternalHeap externalHeap;
		// The heap the managed memory came from (-1: none, the destructor frees nothing)
		int memoryHeap;
		// Where this object itself lives (freed by the last Release)
		int selfHeap;
		void* self;
		int tag;
		int refCount;
	};
}

#endif
