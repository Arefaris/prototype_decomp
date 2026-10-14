#include <string.h>

#include "code/ravenphysics/common/stackallocator.h"

namespace ravenphysics
{
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
