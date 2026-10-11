// The allocator interface of the core module: core::IRefCount (vftable 0x10D96DB8, 3 slots, all pure) and
// core::IMemoryAllocator (vftable 0x10E46AC4, 18 slots; names from the RTTI, member names guessed from
// core::MemoryAllocatorMalloc's implementation). Every allocator class in classes.tsv derives from these.
#ifndef CORE_MEMORY_IMEMORYALLOCATOR_H
#define CORE_MEMORY_IMEMORYALLOCATOR_H

namespace core
{
	struct IRefCount
	{
		virtual void AddRef() = 0;
		virtual void Release() = 0;
		virtual ~IRefCount() {}
	};

	struct MemoryRange
	{
		unsigned int start;
		unsigned int end;
	};

	struct IMemoryAllocator : IRefCount
	{
		virtual void* Alloc(unsigned int size) = 0;
		virtual void Free(void* block) = 0;
		virtual void* AllocAligned(unsigned int size, unsigned int align) = 0;
		virtual void FreeAligned(void* block) = 0;
		// Returns null when flags are given (the malloc allocator knows none)
		virtual void* AllocFlags(unsigned int size, unsigned int align, int flags, int unused) = 0;
		virtual void FreeFlags(void* block) = 0;
		virtual int GetType() = 0;
		virtual void GetRange(MemoryRange* range, int index) = 0;
		// Statistics by id: 0 live allocations, 1 a global peak counter, 10 bytes allocated
		virtual bool GetStat(int id, int* value) = 0;
		virtual bool ResetStat(int id) = 0;
		virtual const char* GetName() = 0;
		// Slots 14 - 16 go to AllocatorBase_Safety in the real allocators (mode 2 = locked with a critical section);
		// MemoryAllocatorMalloc answers 2 and ignores the setters
		virtual void SetSafetyMode(int mode) = 0;
		virtual int GetSafetyMode() = 0;
		virtual void SetUnused(int value) = 0;
		virtual bool IsThreadSafe() = 0;
	};
}

#endif
