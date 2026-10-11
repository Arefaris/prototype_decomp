#include "code/core/heap.h"
#include "code/core/memory/spilloverallocator.h"

extern "C"
{
	long _InterlockedExchangeAdd(long volatile*, long);
	long _InterlockedAnd(long volatile*, long);
}
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedAnd)

namespace core
{
	// FUNCTION: ENGINE 0x10B803A0
	// Whether one of the allocator's ranges holds the block (the compiler passes the allocator in edi)
	static bool Contains(IMemoryAllocator* allocator, void* block)
	{
		unsigned int count = allocator->GetType();
		for (unsigned int i = 0; i < count; i++)
		{
			MemoryRange range;
			allocator->GetRange(&range, i);
			if ((unsigned int)block >= range.start && (unsigned int)block < range.end)
			{
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10B80400
	MemorySpillOverAllocator::~MemorySpillOverAllocator()
	{
		if (primary != 0)
		{
			primary->Release();
			primary = 0;
		}
		if (secondary != 0)
		{
			secondary->Release();
			secondary = 0;
		}
	}

	// FUNCTION: ENGINE 0x10B80470
	void MemorySpillOverAllocator::Init(IMemoryAllocator* first, IMemoryAllocator* second, SpillOverCallback function, void* data)
	{
		primary = first;
		first->AddRef();
		secondary = second;
		second->AddRef();
		useHeap = false;
		callback = function;
		userData = data;
		notify = function != 0;
	}

	// FUNCTION: ENGINE 0x10B804B0
	void MemorySpillOverAllocator::InitHeap(IMemoryAllocator* first, int heap, SpillOverCallback function, void* data)
	{
		primary = first;
		first->AddRef();
		fallbackHeap = heap;
		useHeap = true;
		callback = function;
		userData = data;
		notify = function != 0;
	}

	// FUNCTION: ENGINE 0x10B804F0
	void MemorySpillOverAllocator::Free(void* block)
	{
		if (Contains(primary, block))
		{
			primary->Free(block);
		}
		else
		{
			IMemoryAllocator* fallback = useHeap ? GetHeapAllocator(fallbackHeap) : secondary;
			fallback->Free(block);
		}
	}

	// FUNCTION: ENGINE 0x10B80550
	void MemorySpillOverAllocator::FreeAligned(void* block)
	{
		if (Contains(primary, block))
		{
			primary->FreeAligned(block);
		}
		else
		{
			IMemoryAllocator* fallback = useHeap ? GetHeapAllocator(fallbackHeap) : secondary;
			fallback->FreeAligned(block);
		}
	}

	// FUNCTION: ENGINE 0x10B805B0
	void MemorySpillOverAllocator::FreeFlags(void* block)
	{
		if (Contains(primary, block))
		{
			primary->FreeFlags(block);
		}
		else
		{
			IMemoryAllocator* fallback = useHeap ? GetHeapAllocator(fallbackHeap) : secondary;
			fallback->FreeFlags(block);
		}
	}

	// FUNCTION: ENGINE 0x10B80610
	const char* MemorySpillOverAllocator::GetName()
	{
		return primary->GetName();
	}

	// FUNCTION: ENGINE 0x10B80620
	void MemorySpillOverAllocator::SetSafetyMode(int mode)
	{
		primary->SetSafetyMode(mode);
	}

	// FUNCTION: ENGINE 0x10B80630
	int MemorySpillOverAllocator::GetSafetyMode()
	{
		return primary->GetSafetyMode();
	}

	// FUNCTION: ENGINE 0x10B80640
	void MemorySpillOverAllocator::SetUnused(int value)
	{
		primary->SetUnused(value);
	}

	// FUNCTION: ENGINE 0x10B80650
	int MemorySpillOverAllocator::GetType()
	{
		return primary->GetType();
	}

	// FUNCTION: ENGINE 0x10B80660
	void MemorySpillOverAllocator::GetRange(MemoryRange* range, int index)
	{
		primary->GetRange(range, index);
	}

	// FUNCTION: ENGINE 0x10B80670
	bool MemorySpillOverAllocator::IsThreadSafe()
	{
		return primary->IsThreadSafe();
	}

	// FUNCTION: ENGINE 0x10B806A0
	void MemorySpillOverAllocator::AddRef()
	{
		RefCount::AddRef();
	}

	// FUNCTION: ENGINE 0x10B806B0
	void MemorySpillOverAllocator::Release()
	{
		RefCount::Release();
	}

	// FUNCTION: ENGINE 0x10B80720
	// EQUIVALENT: same blocks and calls; around the callback the registers rotate (94.8 %): the original loads the
	// callback into edx first and userData last, ours primary first and the callback last. A local copy of the
	// callback, (*callback), a separate count, a result temporary, volatile members and a notifier struct do not help.
	void* MemorySpillOverAllocator::Alloc(unsigned int size)
	{
		void* block = primary->Alloc(size);
		if (block == 0)
		{
			IMemoryAllocator* fallback = useHeap ? GetHeapAllocator(fallbackHeap) : secondary;
			if (notify == 1)
			{
				notify = callback(userData, this, primary, fallback, size, 16, 0, _InterlockedAnd(&spilledCount, -1));
			}
			block = fallback->Alloc(size);
			if (block != 0)
			{
				_InterlockedExchangeAdd(&spilledBytes, RoundUp(size, 16));
				_InterlockedIncrement(&spilledCount);
			}
		}
		return block;
	}

	// FUNCTION: ENGINE 0x10B807D0
	// EQUIVALENT: as Alloc (95.0 %)
	void* MemorySpillOverAllocator::AllocAligned(unsigned int size, unsigned int align)
	{
		void* block = primary->AllocAligned(size, align);
		if (block == 0)
		{
			IMemoryAllocator* fallback = useHeap ? GetHeapAllocator(fallbackHeap) : secondary;
			if (notify == 1)
			{
				notify = callback(userData, this, primary, fallback, size, 16, 0, _InterlockedAnd(&spilledCount, -1));
			}
			block = fallback->AllocAligned(size, align);
			if (block != 0)
			{
				_InterlockedExchangeAdd(&spilledBytes, RoundUp(size, align));
				_InterlockedIncrement(&spilledCount);
			}
		}
		return block;
	}

	// FUNCTION: ENGINE 0x10B80890
	// EQUIVALENT: as Alloc (93.5 %)
	void* MemorySpillOverAllocator::AllocFlags(unsigned int size, unsigned int align, int flags, int unused)
	{
		void* block = primary->AllocFlags(size, align, flags, unused);
		if (block == 0)
		{
			IMemoryAllocator* fallback = useHeap ? GetHeapAllocator(fallbackHeap) : secondary;
			if (notify == 1)
			{
				notify = callback(userData, this, primary, fallback, size, 16, 0, _InterlockedAnd(&spilledCount, -1));
			}
			block = fallback->AllocFlags(size, align, flags, unused);
			if (block != 0)
			{
				_InterlockedExchangeAdd(&spilledBytes, RoundUp(size, align));
				_InterlockedIncrement(&spilledCount);
			}
		}
		return block;
	}

	// FUNCTION: ENGINE 0x10B80960
	bool MemorySpillOverAllocator::GetStat(int id, int* value)
	{
		if (id == 15)
		{
			*value = _InterlockedAnd(&spilledBytes, -1);
			return true;
		}
		if (id == 16)
		{
			*value = _InterlockedAnd(&spilledCount, -1);
			return true;
		}
		return primary->GetStat(id, value);
	}

	// FUNCTION: ENGINE 0x10B809C0
	bool MemorySpillOverAllocator::ResetStat(int id)
	{
		if (id == 15)
		{
			_InterlockedExchange(&spilledBytes, 0);
			return true;
		}
		if (id == 16)
		{
			_InterlockedExchange(&spilledCount, 0);
			return true;
		}
		return primary->ResetStat(id);
	}

	// FUNCTION: ENGINE 0x10B80A00
	MemorySpillOverAllocator::MemorySpillOverAllocator()
	{
		primary = 0;
		secondary = 0;
		fallbackHeap = 0x100;
		useHeap = false;
		spilledBytes = 0;
		spilledCount = 0;
	}

	// FUNCTION: ENGINE 0x10B80A60
	IMemoryAllocator* CreateSpillOverAllocator(IMemoryAllocator* primary, IMemoryAllocator* secondary, int heap, SpillOverCallback callback, void* userData)
	{
		MemorySpillOverAllocator* allocator = new (heap) MemorySpillOverAllocator();
		CoreName();
		allocator->Init(primary, secondary, callback, userData);
		return allocator;
	}

	// FUNCTION: ENGINE 0x10B80AC0
	IMemoryAllocator* CreateSpillOverHeapAllocator(IMemoryAllocator* primary, int fallbackHeap, int heap, SpillOverCallback callback, void* userData)
	{
		MemorySpillOverAllocator* allocator = new (heap) MemorySpillOverAllocator();
		CoreName();
		allocator->InitHeap(primary, fallbackHeap, callback, userData);
		return allocator;
	}
}
