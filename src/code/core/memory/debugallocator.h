// core::IMemoryDebugAllocator (vftable 0x10EAEE1C, 21 slots) and core::MemoryDebugAllocator (RTTI names; vftables
// 0x10EAEDC4 and, for the RefCount base at 4, 0x10EAEDB8): wraps another allocator, optionally framing every block
// with CRC-checked headers and footers kept in a list, and reports allocations to callbacks. All debug allocators
// sit in one global list under one critical section. Unit 0x10B80B20 - 0x10B814DF (no assert path; file name
// memory/debugallocator.cpp guessed). Member names guessed.
#ifndef CORE_MEMORY_DEBUGALLOCATOR_H
#define CORE_MEMORY_DEBUGALLOCATOR_H

#include "code/core/memory/imemoryallocator.h"
#include "code/core/object.h"

namespace core
{
	const char* CoreName();
	unsigned int RoundUp(unsigned int size, unsigned int align);

	// (user data, size, alignment, failed) after every allocation; (user data, block, aligned) after every free
	typedef void (*DebugAllocCallback)(void* userData, unsigned int size, unsigned int align, bool failed);
	typedef void (*DebugFreeCallback)(void* userData, void* block, bool aligned);

	struct IMemoryDebugAllocator : IMemoryAllocator
	{
		virtual void SetAllocCallback(DebugAllocCallback callback, void* userData) = 0;
		virtual void SetFreeCallback(DebugFreeCallback callback, void* userData) = 0;
		// Bytes the debug frame adds in front of a block (0 when the frames are off)
		virtual unsigned int GetHeaderSize() = 0;
	};

	class MemoryDebugAllocator : public IMemoryDebugAllocator, public RefCount
	{
	public:
		// 16 bytes in front of every framed block; the CRC covers the three fields after it
		struct Header
		{
			unsigned int crc;
			unsigned int size;
			Header* next;
			Header* prev;
		};

		// 16 bytes after the block (at the rounded size)
		struct Footer
		{
			unsigned int crc;
			unsigned int raw;
			unsigned int total;
			MemoryDebugAllocator* owner;
		};

		MemoryDebugAllocator();
		virtual ~MemoryDebugAllocator();
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
		// Checks this allocator's frames first
		virtual bool IsThreadSafe();
		virtual void SetAllocCallback(DebugAllocCallback callback, void* userData);
		virtual void SetFreeCallback(DebugFreeCallback callback, void* userData);
		virtual unsigned int GetHeaderSize();

		// Wraps `allocator`; mode 0 passes everything through, anything else frames the blocks
		void Init(IMemoryAllocator* allocator, int mode);
		void* AllocFramed(unsigned int size, unsigned int align);
		void FreeFramed(void* block);
		bool CheckHeader(Header* header);
		// Modes 2 and 3 pass through the global lock after every call
		void Synchronise();

		IMemoryAllocator* inner;
		int mode;
		MemoryDebugAllocator* next;
		MemoryDebugAllocator* prev;
		Header* first;
		Header* last;
		int blockCount;
		DebugAllocCallback allocCallback;
		void* allocUserData;
		DebugFreeCallback freeCallback;
		void* freeUserData;

		// The list of all debug allocators and its lock (a CRITICAL_SECTION, created with the first allocator and
		// deleted with the last). Class members, not file statics: the original rereads them after every store
		// through a pointer, which internal linkage would let the compiler skip.
		static int sLock[6];
		static MemoryDebugAllocator* sFirst;
		static MemoryDebugAllocator* sLast;
		static int sCount;
	};

	// The frame checks (external functions: the original passes the allocator on the stack)
	bool CheckHeaders(MemoryDebugAllocator* allocator);
	bool CheckAllocators();
	bool CheckAllocatorsLocked();

	// Checks the frames of every debug allocator under the global lock
	bool CheckDebugAllocators();
	MemoryDebugAllocator* CreateDebugAllocator(IMemoryAllocator* allocator, int mode, int heap);
}

#endif
