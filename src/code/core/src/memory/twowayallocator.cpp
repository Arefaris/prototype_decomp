#include "code/core/heap.h"
#include "code/core/memory/twowayallocator.h"
#include "code/core/report.h"
#include "code/core/utility.h"

// __FILE__ as the original build spelled it (it compiled from a directory three levels below the tree root)
#define TWOWAY_FILE "..\\..\\..\\code\\core\\src\\memory\\twowayallocator.cpp"

namespace core
{
	// FUNCTION: ENGINE 0x10645370
	// The rounding helpers (declared in allocatorbase.h; 0x10645300 - 0x10645350 are another unit's copies)
	template<class T> T AlignUp(T value, T align)
	{
		if (align != 0)
		{
			T rest = value % align;
			if (rest != 0)
			{
				return value - rest + align;
			}
		}
		return value;
	}

	// FUNCTION: ENGINE 0x106453A0
	template<class T> T AlignDown(T value, T align)
	{
		if (align == 0)
		{
			return value;
		}
		return value / align * align;
	}

	// FUNCTION: ENGINE 0x106453C0
	bool IsAligned(unsigned int value, unsigned int align)
	{
		return value == AlignUp(value, align);
	}

	// FUNCTION: ENGINE 0x106454B0
	void MemoryTwoWayAllocator::SetDirection(int value)
	{
		AllocatorLock lock(this);
		direction = value;
	}

	// FUNCTION: ENGINE 0x106454E0
	int MemoryTwoWayAllocator::GetDirection()
	{
		AllocatorLock lock(this);
		return direction;
	}

	// FUNCTION: ENGINE 0x10645510
	void MemoryTwoWayAllocator::ResetSide(int side)
	{
		AllocatorLock lock(this);
		if (side == 0)
		{
			low = base;
			lowCount = 0;
		}
		else
		{
			high = end;
			highCount = 0;
		}
	}

	// FUNCTION: ENGINE 0x10645560
	bool MemoryTwoWayAllocator::GetStat(int id, int* value)
	{
		AllocatorLock lock(this);
		switch (id)
		{
		case 0:
			*value = highCount + lowCount;
			return true;
		case 1:
			*value = end - base;
			return true;
		case 2:
		case 7:
			*value = (low - high) - base + end;
			return true;
		case 3:
			*value = high - low;
			return true;
		case 10:
			*value = bytesAllocated;
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10645650
	bool MemoryTwoWayAllocator::ResetStat(int id)
	{
		AllocatorLock lock(this);
		if (id != 10)
		{
			return false;
		}
		bytesAllocated = 0;
		return true;
	}

	// FUNCTION: ENGINE 0x10645690
	int MemoryTwoWayAllocator::GetType()
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x106456A0
	void MemoryTwoWayAllocator::GetRange(MemoryRange* range, int index)
	{
		range->start = base;
		range->end = end;
	}

	// FUNCTION: ENGINE 0x106456E0
	void MemoryTwoWayAllocator::Init(void* memory, unsigned int size, const char* name, unsigned int align)
	{
		defaultAlign = align;
		SetName(name);
		base = (unsigned int)memory;
		end = (unsigned int)memory + size;
		low = (unsigned int)memory;
		high = (unsigned int)memory + size;
	}

	// FUNCTION: ENGINE 0x10645730
	void* MemoryTwoWayAllocator::AllocImpl(unsigned int size, unsigned int align)
	{
		AllocatorLock lock(this);
		if (size == 0)
		{
			size = 1;
		}
		unsigned int block;
		if (direction == 0)
		{
			block = AlignUp(low, align);
			if (block + size < high)
			{
				lowCount++;
				low = block + size;
			}
			else
			{
				static bool sReportLow = true;
				if (sReportLow && Report(0, 0, TWOWAY_FILE, 333, 0, "MemoryTwoWayAllocator: Out of memory.\n", 0) == 3)
				{
					sReportLow = false;
				}
				block = 0;
			}
		}
		else
		{
			block = AlignDown(high - size, align);
			if (block > low)
			{
				highCount++;
				high = block;
			}
			else
			{
				static bool sReportHigh = true;
				if (sReportHigh && Report(0, 0, TWOWAY_FILE, 348, 0, "MemoryTwoWayAllocator: Out of memory.\n", 0) == 3)
				{
					sReportHigh = false;
				}
				block = 0;
			}
		}
		if (block != 0)
		{
			bytesAllocated += (size != 0) ? RoundUp(size, align) : align;
		}
		return (void*)block;
	}

	// FUNCTION: ENGINE 0x10645880
	void MemoryTwoWayAllocator::FreeImpl(void* block)
	{
		AllocatorLock lock(this);
		if (block != 0)
		{
			if ((unsigned int)block < high)
			{
				if (--lowCount == 0)
				{
					low = base;
				}
			}
			else
			{
				if (--highCount == 0)
				{
					high = end;
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x10645910
	MemoryTwoWayAllocator::~MemoryTwoWayAllocator()
	{
		core::Free((void*)base);
		base = 0;
		end = 0;
		low = 0;
		high = 0;
	}

	// FUNCTION: ENGINE 0x106459A0
	const char* MemoryTwoWayAllocator::GetName()
	{
		return AllocatorBase_Name::GetName();
	}

	// FUNCTION: ENGINE 0x106459B0
	int MemoryTwoWayAllocator::GetSafetyMode()
	{
		return GetMode();
	}

	// FUNCTION: ENGINE 0x106459C0
	void MemoryTwoWayAllocator::SetSafetyMode(int mode)
	{
		SetMode(mode, this);
	}

	// FUNCTION: ENGINE 0x106459E0
	void MemoryTwoWayAllocator::SetUnused(int value)
	{
		AllocatorBase_Safety::SetUnused(value);
	}

	// FUNCTION: ENGINE 0x106459F0
	void* MemoryTwoWayAllocator::AllocFlags(unsigned int size, unsigned int align, int flags, int unused)
	{
		if (flags != 0)
		{
			return 0;
		}
		return AllocAligned(size, align);
	}

	// FUNCTION: ENGINE 0x10645A10
	void MemoryTwoWayAllocator::FreeFlags(void* block)
	{
		FreeAligned(block);
	}

	// FUNCTION: ENGINE 0x10645A20
	bool MemoryTwoWayAllocator::IsThreadSafe()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x10645A40
	void MemoryTwoWayAllocator::AddRef()
	{
		RefCount::AddRef();
	}

	// FUNCTION: ENGINE 0x10645A50
	void MemoryTwoWayAllocator::Release()
	{
		RefCount::Release();
	}

	// FUNCTION: ENGINE 0x10645A80
	void MemoryTwoWayAllocator::Create(unsigned int size, const char* name, unsigned int align)
	{
		void* memory = HeapAlloc(heap, size);
		Init(memory, size, name, align);
	}

	// FUNCTION: ENGINE 0x10645AB0
	void* MemoryTwoWayAllocator::Alloc(unsigned int size)
	{
		return AllocImpl(size, defaultAlign);
	}

	// FUNCTION: ENGINE 0x10645AD0
	void MemoryTwoWayAllocator::Free(void* block)
	{
		FreeImpl(block);
	}

	// FUNCTION: ENGINE 0x10645AE0
	void* MemoryTwoWayAllocator::AllocAligned(unsigned int size, unsigned int align)
	{
		return AllocImpl(size, Max(align, defaultAlign));
	}

	// FUNCTION: ENGINE 0x10645B00
	void MemoryTwoWayAllocator::FreeAligned(void* block)
	{
		FreeImpl(block);
	}

	// FUNCTION: ENGINE 0x10645B10
	void MemoryTwoWayAllocator::Reset()
	{
		AllocatorLock lock(this);
		low = base;
		high = end;
		lowCount = 0;
		highCount = 0;
	}

	// FUNCTION: ENGINE 0x10645BC0
	MemoryTwoWayAllocator::MemoryTwoWayAllocator()
	{
		base = 0;
		end = 0;
		low = 0;
		high = 0;
		lowCount = 0;
		highCount = 0;
		bytesAllocated = 0;
		direction = 0;
		defaultAlign = 16;
		CoreName();
	}

	// FUNCTION: ENGINE 0x10645C40
	void CreateTwoWayAllocator(MemoryTwoWayAllocator** out, unsigned int size, int heap, const char* name, unsigned int align)
	{
		MemoryTwoWayAllocator* allocator = new (heap) MemoryTwoWayAllocator();
		CoreName();
		allocator->AddRef();
		allocator->Create(size, name, align);
		*out = allocator;
	}

	// FUNCTION: ENGINE 0x10645CA0
	MemoryTwoWayAllocator* NewTwoWayAllocator(unsigned int size, int heap, const char* name, unsigned int align)
	{
		MemoryTwoWayAllocator* allocator = new (heap) MemoryTwoWayAllocator();
		CoreName();
		allocator->Create(size, name, align);
		return allocator;
	}

	// FUNCTION: ENGINE 0x10645CF0
	MemoryTwoWayAllocator* NewTwoWayAllocatorAt(void* unused, int heap, void* memory, unsigned int size, const char* name, unsigned int align)
	{
		MemoryTwoWayAllocator* allocator = new (heap) MemoryTwoWayAllocator();
		CoreName();
		allocator->Init(memory, size, name, align);
		return allocator;
	}
}
