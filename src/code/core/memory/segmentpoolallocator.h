// core::SegmentPoolAllocator (RTTI name; vftables 0x10E46C7C and, for the RefCount base at 0x44, 0x10E46C70): one
// heap block cut into equal segments, each a small bump allocator, with one segment open for allocation at a time.
// Unit 0x1063DBA0 - 0x1063E72B, assert path code/core/src/memory/segmentpoolallocator.cpp. Layout: AllocatorBaseSub
// at 0 (AllocatorBase at 4), RefCount at 0x44, the pool from 0x50, 0x16C bytes in all. Member names guessed.
#ifndef CORE_MEMORY_SEGMENTPOOLALLOCATOR_H
#define CORE_MEMORY_SEGMENTPOOLALLOCATOR_H

#include "code/core/memory/allocatorbase.h"
#include "code/core/object.h"

namespace core
{
	const char* CoreName();
	unsigned int RoundUp(unsigned int size, unsigned int align);

	class SegmentPoolAllocator : public AllocatorBaseSub, public RefCount
	{
	public:
		// The 12-byte header of one segment, at the start of the heap block
		struct Segment
		{
			Segment();
			~Segment();
			// Bumps the cursor; null when the segment cannot hold `size` more bytes
			void* Alloc(unsigned int size, unsigned int base, int limit, unsigned int align);
			void Free(void* block);
			bool IsEmpty();
			unsigned int GetUsed(unsigned int base);
			void SetMark();

			unsigned int cursor;
			unsigned int mark;
			int count;
		};

		SegmentPoolAllocator();
		virtual ~SegmentPoolAllocator();
		virtual void AddRef();
		virtual void Release();
		virtual void* Alloc(unsigned int size);
		virtual void Free(void* block);
		virtual void* AllocAligned(unsigned int size, unsigned int align);
		virtual void FreeAligned(void* block);
		virtual int GetType();
		virtual void GetRange(MemoryRange* range, int index);
		// 0 segments in use, 1 capacity, 2 bytes in used segments, 3 bytes in empty segments, 11 segment count
		virtual bool GetStat(int id, int* value);
		virtual bool ResetStat(int id);
		virtual bool IsThreadSafe();

		unsigned int GetSegmentCount();
		// Opens the allocator; returns the current segment
		int Open();
		bool HasSegment();
		// Lock bits (only while bit 31 is set, which Init does for fewer than 32 segments)
		void LockSegment(int index);
		void UnlockSegment(int index);
		bool IsLocked(int index);
		unsigned int GetSegmentSize();
		// Bytes before the first segment: the headers, rounded up to 16
		unsigned int GetHeaderSize();
		unsigned int GetSegmentBase(unsigned int index);
		unsigned int GetSegmentIndex(unsigned int address);
		unsigned int GetEnd();
		Segment* GetSegment(unsigned int index);
		// A stack of byte counters (statistics per scope)
		void PushCounter();
		void PopCounter();
		int GetCounter();
		void Init(const char* name, unsigned int count, unsigned int size, int heap);
		void Shutdown();
		unsigned int CountEmptySegments();
		// Makes the segment holding `address` current and marks its cursor
		void Select(unsigned int address);
		// Moves on to the next empty segment; returns the previous one
		int Next();
		unsigned int GetBegin();
		unsigned int GetLimit();
		unsigned int GetUsed(unsigned int index);

		Segment* segments;
		unsigned int segmentCount;
		unsigned int segmentSize;
		int lockMask;
		int currentSegment;
		bool open;
		int counters[64];
		int counterTop;
	};

	void CreateSegmentPoolAllocator(SegmentPoolAllocator** out, unsigned int count, unsigned int size, int unused, int heap, const char* name);
	SegmentPoolAllocator* NewSegmentPoolAllocator(unsigned int count, unsigned int size, int unused, int heap, const char* name);
}

#endif
