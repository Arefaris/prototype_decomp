// core::MemoryAllocatorMalloc (RTTI name; vftable 0x10E4740C): the "system" allocator on top of the CRT malloc,
// with a size header for alignment and two counters. Unit 0x106465B0 - 0x10646995 (memory/memoryallocatormalloc.cpp,
// file and member names guessed).
#ifndef CORE_MEMORY_MEMORYALLOCATORMALLOC_H
#define CORE_MEMORY_MEMORYALLOCATORMALLOC_H

#include "code/core/memory/imemoryallocator.h"

// kernel32's IsDebuggerPresent, declared here instead of pulling in windows.h (the toolchain has no SDK headers).
// Declared without __stdcall: the call is the same for a function without arguments, and the import library the
// relinker generates names the slot __imp__IsDebuggerPresent (no @0).
extern "C" __declspec(dllimport) int IsDebuggerPresent(void);

namespace core
{
	// 0x106447F0: returns "core" (what the constructor does with it is not visible; the call is kept)
	const char* CoreName();
	// 0x10645300: size rounded up to a multiple of align (align 0 leaves it)
	unsigned int RoundUp(unsigned int size, unsigned int align);

	struct MemoryAllocatorMalloc : IMemoryAllocator
	{
		// Both are inlined into the deleting destructor and the system-allocator initialiser below, which is
		// why they are defined here; the compiler still emits the out-of-line copies (0x106465B0, 0x10646610)
		MemoryAllocatorMalloc()
		{
			bytesAllocated = 0;
			allocationCount = 0;
			CoreName();
		}
		virtual ~MemoryAllocatorMalloc()
		{
			// The result is ignored (a debug hook whose break was compiled out)
			IsDebuggerPresent();
		}
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
		virtual bool GetStat(int id, int* value);
		virtual bool ResetStat(int id);
		virtual const char* GetName();
		virtual void SetSafetyMode(int mode);
		virtual int GetSafetyMode();
		virtual void SetUnused(int value);
		virtual bool IsThreadSafe();

		int bytesAllocated;
		long allocationCount;
	};

	// Constructs the static system allocator in place and returns it (0x10646990 forwards to it)
	MemoryAllocatorMalloc* InitSystemAllocator();
	MemoryAllocatorMalloc* GetSystemAllocatorInit();
	// Invokes the virtual destructor without freeing the static storage (names guessed; the second is a forwarding entry)
	void DestroySystemAllocator();
	void GetSystemAllocatorDestroy();
}

#endif
