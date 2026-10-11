// core::MemoryTwoWayAllocator (RTTI name; vftables 0x10E47324 and, for the RefCount base, 0x10E4731C): a linear
// arena that hands out blocks from either end. Unit 0x10645370 - 0x10645D3A, assert path
// code/core/src/memory/twowayallocator.cpp. Member names guessed; the layout is the compiler's (interface at 0,
// RefCount at 4, AllocatorBase at 0x10, the arena state from 0x50, 0x74 bytes in all).
#ifndef CORE_MEMORY_TWOWAYALLOCATOR_H
#define CORE_MEMORY_TWOWAYALLOCATOR_H

#include "code/core/memory/allocatorbase.h"
#include "code/core/memory/imemoryallocator.h"
#include "code/core/object.h"

namespace core
{
	// 0x106447F0: returns "core" (what the callers do with it is not visible; the calls are kept)
	const char* CoreName();
	// 0x10645300: size rounded up to a multiple of align (align 0 leaves it); another unit's copy of AlignUp
	unsigned int RoundUp(unsigned int size, unsigned int align);

	class MemoryTwoWayAllocator : public IMemoryTwoWayAllocator, public AllocatorBase, public RefCount
	{
	public:
		MemoryTwoWayAllocator();
		virtual ~MemoryTwoWayAllocator();
		virtual void AddRef();
		virtual void Release();
		virtual void* Alloc(unsigned int size);
		virtual void Free(void* block);
		virtual void* AllocAligned(unsigned int size, unsigned int align);
		virtual void FreeAligned(void* block);
		virtual void* AllocFlags(unsigned int size, unsigned int align, int flags, int unused);
		virtual void FreeFlags(void* block);
		virtual int GetType();
		virtual void GetRange(MemoryRange* range, int index);
		// 0 live blocks, 1 capacity, 2 / 7 bytes free, 3 bytes between the two cursors, 10 bytes allocated
		virtual bool GetStat(int id, int* value);
		virtual bool ResetStat(int id);
		virtual const char* GetName();
		virtual void SetSafetyMode(int mode);
		virtual int GetSafetyMode();
		virtual void SetUnused(int value);
		virtual bool IsThreadSafe();
		virtual void Reset();
		// 0 allocates upwards from the low end, anything else downwards from the high end
		virtual void SetDirection(int direction);
		virtual int GetDirection();
		virtual void ResetSide(int side);

		// Takes over [memory, memory + size) under the given name and default alignment
		void Init(void* memory, unsigned int size, const char* name, unsigned int align);
		// Allocates the arena from the object's own heap and calls Init
		void Create(unsigned int size, const char* name, unsigned int align);
		// The two workers behind the Alloc / Free entry points
		void* AllocImpl(unsigned int size, unsigned int align);
		void FreeImpl(void* block);

		unsigned int base;
		unsigned int end;
		unsigned int low;
		unsigned int high;
		int lowCount;
		int highCount;
		int bytesAllocated;
		int direction;
		unsigned int defaultAlign;
	};

	// The three factories: the allocator object comes from `heap` (operator new of Object) and the arena from
	// the same heap (Create) or from memory the caller provides (the last one, whose first argument is unused)
	void CreateTwoWayAllocator(MemoryTwoWayAllocator** out, unsigned int size, int heap, const char* name, unsigned int align);
	MemoryTwoWayAllocator* NewTwoWayAllocator(unsigned int size, int heap, const char* name, unsigned int align);
	MemoryTwoWayAllocator* NewTwoWayAllocatorAt(void* unused, int heap, void* memory, unsigned int size, const char* name, unsigned int align);
}

#endif
