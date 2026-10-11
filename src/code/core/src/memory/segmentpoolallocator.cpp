#include "code/core/heap.h"
#include "code/core/memory/segmentpoolallocator.h"
#include "code/core/report.h"

// __FILE__ as the original build spelled it
#define SEGMENTPOOL_FILE "..\\..\\..\\code\\core\\src\\memory\\segmentpoolallocator.cpp"

// Placement new, inline as in <new> (the toolchain has no SDK headers; memoryallocatormalloc.cpp has the same one)
inline void* operator new(unsigned int size, void* block)
{
	return block;
}

namespace core
{
	// FUNCTION: ENGINE 0x1063DBA0
	inline SegmentPoolAllocator::Segment::Segment()
	{
		cursor = 0;
		mark = 0;
		count = 0;
	}

	// 0x1063DBB0 in the original; nothing here calls it, so our object has no copy to annotate
	inline SegmentPoolAllocator::Segment::~Segment()
	{
	}

	// FUNCTION: ENGINE 0x1063DBC0
	void* SegmentPoolAllocator::Segment::Alloc(unsigned int size, unsigned int base, int limit, unsigned int align)
	{
		if (cursor == 0)
		{
			if (count != 0)
			{
				return 0;
			}
			cursor = base;
		}
		unsigned int block = RoundUp(cursor, align);
		unsigned int end = block + size;
		if ((int)(end - base) > limit)
		{
			return 0;
		}
		count++;
		cursor = end;
		return (void*)block;
	}

	// FUNCTION: ENGINE 0x1063DC10
	void SegmentPoolAllocator::Segment::Free(void* block)
	{
		count--;
		if ((unsigned int)block >= mark)
		{
			cursor = mark;
		}
		else
		{
			cursor = 0;
			mark = 0;
		}
	}

	// FUNCTION: ENGINE 0x1063DC40
	bool SegmentPoolAllocator::Segment::IsEmpty()
	{
		if (cursor == 0 && count == 0)
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1063DC60
	unsigned int SegmentPoolAllocator::Segment::GetUsed(unsigned int base)
	{
		unsigned int used = 0;
		if (cursor != 0)
		{
			used = cursor - base;
		}
		return used;
	}

	// FUNCTION: ENGINE 0x1063DC80
	void SegmentPoolAllocator::Segment::SetMark()
	{
		mark = cursor;
	}

	// FUNCTION: ENGINE 0x1063DC90
	unsigned int SegmentPoolAllocator::GetSegmentCount()
	{
		return segmentCount;
	}

	// FUNCTION: ENGINE 0x1063DCA0
	int SegmentPoolAllocator::Open()
	{
		open = true;
		return currentSegment;
	}

	// FUNCTION: ENGINE 0x1063DCB0
	bool SegmentPoolAllocator::HasSegment()
	{
		return currentSegment > -1;
	}

	// FUNCTION: ENGINE 0x1063DCC0
	void SegmentPoolAllocator::LockSegment(int index)
	{
		if (lockMask & 0x80000000)
		{
			lockMask |= 1 << index;
		}
	}

	// FUNCTION: ENGINE 0x1063DCE0
	void SegmentPoolAllocator::UnlockSegment(int index)
	{
		if (lockMask & 0x80000000)
		{
			lockMask &= ~(1 << index);
		}
	}

	// FUNCTION: ENGINE 0x1063DD00
	bool SegmentPoolAllocator::IsLocked(int index)
	{
		if ((lockMask & 0x80000000) && (lockMask & (1 << index)))
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1063DD20
	void* SegmentPoolAllocator::Alloc(unsigned int size)
	{
		return AllocAligned(size, 16);
	}

	// FUNCTION: ENGINE 0x1063DD40
	void SegmentPoolAllocator::FreeAligned(void* block)
	{
		Free(block);
	}

	// FUNCTION: ENGINE 0x1063DD50
	int SegmentPoolAllocator::GetType()
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x1063DD60
	bool SegmentPoolAllocator::ResetStat(int id)
	{
		return false;
	}

	// FUNCTION: ENGINE 0x1063DD70
	unsigned int SegmentPoolAllocator::GetSegmentSize()
	{
		return segmentSize;
	}

	// FUNCTION: ENGINE 0x1063DD80
	unsigned int SegmentPoolAllocator::GetHeaderSize()
	{
		return RoundUp(segmentCount * sizeof(Segment), 16);
	}

	// FUNCTION: ENGINE 0x1063DDA0
	unsigned int SegmentPoolAllocator::GetSegmentBase(unsigned int index)
	{
		unsigned int start = (unsigned int)segments;
		unsigned int header = GetHeaderSize();
		return segmentSize * index + header + start;
	}

	// FUNCTION: ENGINE 0x1063DDC0
	unsigned int SegmentPoolAllocator::GetSegmentIndex(unsigned int address)
	{
		unsigned int start = (unsigned int)segments;
		unsigned int header = GetHeaderSize();
		return (address - header - start) / segmentSize;
	}

	// FUNCTION: ENGINE 0x1063DDE0
	unsigned int SegmentPoolAllocator::GetEnd()
	{
		unsigned int start = (unsigned int)segments;
		unsigned int first = GetHeaderSize() + start;
		return first + segmentSize * segmentCount;
	}

	// FUNCTION: ENGINE 0x1063DE00
	SegmentPoolAllocator::Segment* SegmentPoolAllocator::GetSegment(unsigned int index)
	{
		return &segments[index];
	}

	// FUNCTION: ENGINE 0x1063DE10
	void SegmentPoolAllocator::PushCounter()
	{
		AllocatorLock lock(this);
		counters[++counterTop] = 0;
	}

	// FUNCTION: ENGINE 0x1063DE50
	void SegmentPoolAllocator::PopCounter()
	{
		AllocatorLock lock(this);
		counterTop--;
	}

	// FUNCTION: ENGINE 0x1063DE80
	int SegmentPoolAllocator::GetCounter()
	{
		AllocatorLock lock(this);
		return counters[counterTop];
	}

	// FUNCTION: ENGINE 0x1063DEE0
	void SegmentPoolAllocator::Init(const char* name, unsigned int count, unsigned int size, int heap)
	{
		SetName(name);
		if (segments == 0 && size > 0 && (size & 15) == 0)
		{
			segmentCount = count;
			segmentSize = size;
			lockMask = 0;
			if (count < 32)
			{
				lockMask = 0x80000000;
			}
			segments = (Segment*)HeapAlloc(heap, GetHeaderSize() + count * size);
			for (unsigned int i = 0; i < count; i++)
			{
				new (GetSegment(i)) Segment();
			}
			currentSegment = 0;
			open = false;
		}
	}

	// FUNCTION: ENGINE 0x1063DF70
	void SegmentPoolAllocator::Shutdown()
	{
		if (segments != 0)
		{
			core::Free(segments);
			segments = 0;
			segmentCount = 0;
			segmentSize = 8;
			currentSegment = -1;
			open = false;
		}
	}

	// FUNCTION: ENGINE 0x1063DFB0
	unsigned int SegmentPoolAllocator::CountEmptySegments()
	{
		unsigned int count = segmentCount;
		unsigned int empty = 0;
		for (unsigned int i = 0; i < count; i++)
		{
			if (GetSegment(i)->IsEmpty())
			{
				empty++;
			}
		}
		return empty;
	}

	// FUNCTION: ENGINE 0x1063DFF0
	void SegmentPoolAllocator::Select(unsigned int address)
	{
		open = true;
		unsigned int index = GetSegmentIndex(address);
		GetSegment(index)->SetMark();
		currentSegment = index;
	}

	// FUNCTION: ENGINE 0x1063E020
	int SegmentPoolAllocator::Next()
	{
		int previous = currentSegment;
		unsigned int count = segmentCount;
		open = false;
		int found = -1;
		unsigned int index = (previous + 1) % count;
		for (unsigned int i = 0; i < count; i++)
		{
			if (GetSegment(index)->IsEmpty())
			{
				found = index;
				break;
			}
			index = (index + 1) % count;
		}
		currentSegment = found;
		return previous;
	}

	// FUNCTION: ENGINE 0x1063E090
	void SegmentPoolAllocator::Free(void* block)
	{
		AllocatorLock lock(this);
		if (segments == 0)
		{
			return;
		}
		unsigned int base = GetSegmentBase(0);
		if ((unsigned int)block < base)
		{
			return;
		}
		unsigned int segmentIndex = ((unsigned int)block - base) / segmentSize;
		if (segmentIndex < segmentCount)
		{
			static bool sAssertLocked = true;
			if (sAssertLocked && IsLocked(segmentIndex)
				&& Report(1, " oldassert ", SEGMENTPOOL_FILE, 438, "!IsLocked( segmentIndex )", 0) == 3)
			{
				sAssertLocked = false;
			}
			Segment* segment = GetSegment(segmentIndex);
			segment->Free(block);
			if (currentSegment < 0 && segment->IsEmpty())
			{
				currentSegment = segmentIndex;
			}
		}
	}

	// FUNCTION: ENGINE 0x1063E160
	void* SegmentPoolAllocator::AllocAligned(unsigned int size, unsigned int align)
	{
		AllocatorLock lock(this);
		counters[counterTop] += (size != 0) ? RoundUp(size, align) : align;
		counters[counterTop] += align - 16;
		if (segments == 0)
		{
			return 0;
		}
		if (!open)
		{
			return 0;
		}
		Segment* segment = GetSegment(currentSegment);
		unsigned int base = GetSegmentBase(currentSegment);
		return segment->Alloc(size, base, segmentSize, align);
	}

	// FUNCTION: ENGINE 0x1063E210
	bool SegmentPoolAllocator::GetStat(int id, int* value)
	{
		AllocatorLock lock(this);
		if (segments == 0)
		{
			return false;
		}
		switch (id)
		{
		case 0:
		{
			unsigned int count = segmentCount;
			int used = 0;
			for (unsigned int i = 0; i < count; i++)
			{
				if (!GetSegment(i)->IsEmpty())
				{
					used++;
				}
			}
			*value = used;
			return true;
		}
		case 1:
			*value = segmentSize * segmentCount;
			return true;
		case 2:
		{
			unsigned int count = segmentCount;
			int bytes = 0;
			for (unsigned int i = 0; i < count; i++)
			{
				if (!GetSegment(i)->IsEmpty())
				{
					bytes += segmentSize;
				}
			}
			*value = bytes;
			return true;
		}
		case 3:
		{
			unsigned int count = segmentCount;
			int bytes = 0;
			for (unsigned int i = 0; i < count; i++)
			{
				if (GetSegment(i)->IsEmpty())
				{
					bytes += segmentSize;
				}
			}
			*value = bytes;
			return true;
		}
		case 11:
			*value = segmentCount;
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1063E380
	unsigned int SegmentPoolAllocator::GetBegin()
	{
		return GetSegmentBase(0);
	}

	// FUNCTION: ENGINE 0x1063E390
	unsigned int SegmentPoolAllocator::GetLimit()
	{
		return GetEnd();
	}

	// FUNCTION: ENGINE 0x1063E3A0
	unsigned int SegmentPoolAllocator::GetUsed(unsigned int index)
	{
		return GetSegment(index)->GetUsed(GetSegmentBase(index));
	}

	// FUNCTION: ENGINE 0x1063E400
	const char* AllocatorBaseSub::GetName()
	{
		return AllocatorBase_Name::GetName();
	}

	// FUNCTION: ENGINE 0x1063E410
	int AllocatorBaseSub::GetSafetyMode()
	{
		return GetMode();
	}

	// FUNCTION: ENGINE 0x1063E420
	void AllocatorBaseSub::SetSafetyMode(int mode)
	{
		SetMode(mode, this);
	}

	// FUNCTION: ENGINE 0x1063E440
	void AllocatorBaseSub::SetUnused(int value)
	{
		AllocatorBase_Safety::SetUnused(value);
	}

	// FUNCTION: ENGINE 0x1063E450
	void* AllocatorBaseSub::AllocFlags(unsigned int size, unsigned int align, int flags, int unused)
	{
		if (flags != 0)
		{
			return 0;
		}
		return AllocAligned(size, align);
	}

	// FUNCTION: ENGINE 0x1063E470
	void AllocatorBaseSub::FreeFlags(void* block)
	{
		FreeAligned(block);
	}

	// FUNCTION: ENGINE 0x1063E4D0
	SegmentPoolAllocator::~SegmentPoolAllocator()
	{
		if (segments != 0)
		{
			Shutdown();
		}
	}

	// FUNCTION: ENGINE 0x1063E550
	bool SegmentPoolAllocator::IsThreadSafe()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x1063E570
	void SegmentPoolAllocator::AddRef()
	{
		RefCount::AddRef();
	}

	// FUNCTION: ENGINE 0x1063E580
	void SegmentPoolAllocator::Release()
	{
		RefCount::Release();
	}

	// FUNCTION: ENGINE 0x1063E5B0
	void SegmentPoolAllocator::GetRange(MemoryRange* range, int index)
	{
		range->start = GetBegin();
		range->end = GetLimit();
	}

	// FUNCTION: ENGINE 0x1063E5D0
	// EQUIVALENT: as in the MemoryPool constructor, the original clears eax after the RefCount vftable store and
	// ours right after the heap is copied (86.3 %); everything else is identical.
	// The reference count starts at one: the factories hand the allocator out without an AddRef
	SegmentPoolAllocator::SegmentPoolAllocator()
		: RefCount(1)
	{
		segments = 0;
		segmentCount = 0;
		open = false;
		counterTop = 0;
		segmentSize = 8;
		currentSegment = -1;
	}

	// FUNCTION: ENGINE 0x1063E690
	void CreateSegmentPoolAllocator(SegmentPoolAllocator** out, unsigned int count, unsigned int size, int unused, int heap, const char* name)
	{
		SegmentPoolAllocator* allocator = new (heap) SegmentPoolAllocator();
		CoreName();
		allocator->Init(name, count, size, heap);
		*out = allocator;
	}

	// FUNCTION: ENGINE 0x1063E6E0
	SegmentPoolAllocator* NewSegmentPoolAllocator(unsigned int count, unsigned int size, int unused, int heap, const char* name)
	{
		SegmentPoolAllocator* allocator = new (heap) SegmentPoolAllocator();
		CoreName();
		allocator->Init(name, count, size, heap);
		return allocator;
	}
}
