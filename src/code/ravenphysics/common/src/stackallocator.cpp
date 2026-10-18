#include <string.h>

#include "code/core/debug.h"
#include "code/core/heap.h"
#include "code/ravenphysics/common/stackallocator.h"

#define STACKALLOCATOR_FILE "..\\..\\..\\code\\ravenphysics\\common\\src\\stackallocator.cpp"

namespace ravenphysics
{
	// The scratch stack's state (0x1127D408 on)
	char* ScratchStack::sBegin;
	unsigned int ScratchStack::sHighWater;
	int ScratchStack::sDepth;
	bool ScratchStack::sFill;
	bool ScratchStack::sLock;
	char* ScratchStack::sEnd;
	char* ScratchStack::sCurrent;
	int ScratchStack::sUnknown;

	// FUNCTION: ENGINE 0x10666F00
	unsigned int ScratchStack::GetFree(int align)
	{
		return (~(align - 1) & (unsigned int)sEnd) - ((unsigned int)sCurrent + align - 1 & ~(align - 1));
	}

	// FUNCTION: ENGINE 0x10666F30
	void ScratchStack::Create(unsigned int size, int heap, bool fill)
	{
		char* buffer = (char*)core::HeapAllocAligned(heap, size, 4);
		sEnd = buffer + size;
		sBegin = buffer;
		sCurrent = buffer;
		sDepth = 0;
		sHighWater = (unsigned int)buffer;
		sUnknown = 0;
		sFill = fill;
		sLock = false;
		if (fill)
		{
			memset(sBegin, 0xCC, size);
		}
	}

	// FUNCTION: ENGINE 0x10666F90
	void ScratchStack::Free()
	{
		OLD_ASSERT_TEXT_AT(STACKALLOCATOR_FILE, 69, !sLock, "!sLock");
		core::FreeAligned(sBegin);
	}

	// FUNCTION: ENGINE 0x10666FE0
	// NONMATCHING: 85.4 %; on captured states the engine hands out the block and raises the static at 0x1127D41C,
	// ours answers 0 (the statics' roles or the comparison differ; not resolved)
#ifdef NONMATCHING
	void* ScratchStack::Alloc(unsigned int size, int align)
	{
		OLD_ASSERT_TEXT_AT(STACKALLOCATOR_FILE, 81, !sLock, "!sLock");
		char* block = (char*)((unsigned int)(sCurrent + align - 1) & ~(align - 1));
		sCurrent = (char*)((unsigned int)(block + size + align - 1) & ~(align - 1));
		if (sCurrent > sEnd)
		{
			return 0;
		}
		if (sFill)
		{
			memset(block, 0xDC, size);
		}
		if (sHighWater < (unsigned int)sCurrent)
		{
			sHighWater = (unsigned int)sCurrent;
		}
		return block;
	}
#endif

	// FUNCTION: ENGINE 0x10667090
	bool ScratchStack::IsReady(int unused)
	{
		return true;
	}

	// FUNCTION: ENGINE 0x106670A0
	void* ScratchStack::Mark()
	{
		OLD_ASSERT_TEXT_AT(STACKALLOCATOR_FILE, 139, !sLock, "!sLock");
		sDepth++;
		return sCurrent;
	}

	// FUNCTION: ENGINE 0x10667100
	void ScratchStack::Release(void* mark)
	{
		OLD_ASSERT_TEXT_AT(STACKALLOCATOR_FILE, 146, !sLock, "!sLock");
		if (sFill)
		{
			memset(mark, 0xCC, sCurrent - (char*)mark);
		}
		sDepth--;
		sCurrent = (char*)mark;
	}

	// FUNCTION: ENGINE 0x10667190
	int ScratchStack::GetDepth()
	{
		return sDepth;
	}

	// FUNCTION: ENGINE 0x106671A0
	ScratchStackFrame* ScratchStackFrame::Open()
	{
		mark = ScratchStack::Mark();
		depth = ScratchStack::GetDepth();
		return this;
	}

	// FUNCTION: ENGINE 0x106671C0
	ScratchStackFrame::~ScratchStackFrame()
	{
		ScratchStack::Release(mark);
	}

	// FUNCTION: ENGINE 0x106671D0
	void ScratchStack::HandOver(StackAllocator* allocator)
	{
		allocator->Init(sCurrent, ((unsigned int)sEnd & ~15U) - ((unsigned int)sCurrent + 15U & ~15U), false);
		sLock = true;
	}

	// FUNCTION: ENGINE 0x10667200
	void ScratchStack::Lock()
	{
		OLD_ASSERT_TEXT_AT(STACKALLOCATOR_FILE, 207, !sLock, "!sLock");
		sLock = true;
	}

	// FUNCTION: ENGINE 0x10667250
	void ScratchStack::Unlock()
	{
		OLD_ASSERT_TEXT_AT(STACKALLOCATOR_FILE, 213, sLock, "sLock");
		sLock = false;
	}

	// FUNCTION: ENGINE 0x10686040
	StackAllocator::StackAllocator(void* buffer, unsigned int size, bool fill)
		: begin((char*)buffer), end((char*)buffer + size), current((char*)buffer), depth(0), fill(fill),
		  highWater(0), unknown18(true)
	{
		if (fill)
		{
			memset(buffer, 0xcc, size);
		}
	}

	// FUNCTION: ENGINE 0x10686090
	void StackAllocator::Init(void* buffer, unsigned int size, bool fill)
	{
		end = (char*)buffer + size;
		begin = (char*)buffer;
		current = (char*)buffer;
		depth = 0;
		this->fill = fill;
		highWater = 0;
		unknown18 = true;
		if (fill)
		{
			memset(buffer, 0xcc, size);
		}
	}

	// FUNCTION: ENGINE 0x106860E0
	StackAllocator::~StackAllocator()
	{
	}

	// FUNCTION: ENGINE 0x106860F0
	void* StackAllocator::Mark()
	{
		depth++;
		return current;
	}

	// FUNCTION: ENGINE 0x10686100
	void StackAllocator::Release(void* mark)
	{
		if (fill)
		{
			memset(mark, 0xcc, current - (char*)mark);
		}
		depth--;
		current = (char*)mark;
	}

	// FUNCTION: ENGINE 0x10686130
	int StackAllocator::GetDepth() const
	{
		return depth;
	}

	// FUNCTION: ENGINE 0x10686140
	StackAllocatorScope::StackAllocatorScope(StackAllocator* allocator)
		: allocator(allocator), mark(allocator->Mark()), depth(allocator->GetDepth())
	{
	}

	// FUNCTION: ENGINE 0x10686160
	StackAllocatorScope::~StackAllocatorScope()
	{
		allocator->Release(mark);
	}
}
