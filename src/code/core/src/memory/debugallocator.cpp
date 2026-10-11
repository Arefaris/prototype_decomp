#include "code/core/crc32.h"
#include "code/core/criticalsection.h"
#include "code/core/memory/allocatorbase.h"
#include "code/core/memory/debugallocator.h"

namespace core
{
	// GLOBAL: ENGINE 0x11330284
	int MemoryDebugAllocator::sLock[6];
	// GLOBAL: ENGINE 0x1133029C
	MemoryDebugAllocator* MemoryDebugAllocator::sFirst;
	// GLOBAL: ENGINE 0x113302A0
	MemoryDebugAllocator* MemoryDebugAllocator::sLast;
	// GLOBAL: ENGINE 0x113302A4
	int MemoryDebugAllocator::sCount;

	// FUNCTION: ENGINE 0x10B80B30
	// Whether one of the allocator's ranges holds the block (the compiler passes the allocator in edi); the same as
	// spilloverallocator.cpp's Contains, renamed here because symbols.txt needs distinct names
	static bool OwnsBlock(IMemoryAllocator* allocator, void* block)
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

	// FUNCTION: ENGINE 0x10B80B90
	MemoryDebugAllocator::~MemoryDebugAllocator()
	{
		CriticalSectionEnter(sLock);
		if (prev == 0)
		{
			sFirst = next;
		}
		else
		{
			prev->next = next;
		}
		if (next == 0)
		{
			sLast = prev;
		}
		else
		{
			next->prev = prev;
		}
		sCount--;
		CriticalSectionLeave(sLock);
		inner->Release();
		inner = 0;
		if (sFirst == 0)
		{
			CriticalSectionDelete(sLock);
		}
	}

	// FUNCTION: ENGINE 0x10B80C60
	void MemoryDebugAllocator::Init(IMemoryAllocator* allocator, int value)
	{
		BuildCrc32Table();
		inner = allocator;
		allocator->AddRef();
		mode = value;
		first = 0;
		last = 0;
		blockCount = 0;
		if (sFirst == 0)
		{
			CriticalSectionInit(sLock);
		}
		CriticalSectionEnter(sLock);
		prev = sLast;
		next = 0;
		if (sFirst == 0)
		{
			sFirst = this;
		}
		else
		{
			sLast->next = this;
		}
		sCount++;
		sLast = this;
		CriticalSectionLeave(sLock);
	}

	// FUNCTION: ENGINE 0x10B80CF0
	void* MemoryDebugAllocator::AllocFlags(unsigned int size, unsigned int align, int flags, int unused)
	{
		if (flags == 0)
		{
			return AllocAligned(size, align);
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10B80D10
	void MemoryDebugAllocator::FreeFlags(void* block)
	{
		FreeAligned(block);
	}

	// FUNCTION: ENGINE 0x10B80D20
	bool MemoryDebugAllocator::GetStat(int id, int* value)
	{
		return inner->GetStat(id, value);
	}

	// FUNCTION: ENGINE 0x10B80D30
	bool MemoryDebugAllocator::ResetStat(int id)
	{
		return inner->ResetStat(id);
	}

	// FUNCTION: ENGINE 0x10B80D40
	const char* MemoryDebugAllocator::GetName()
	{
		return inner->GetName();
	}

	// FUNCTION: ENGINE 0x10B80D50
	void MemoryDebugAllocator::SetSafetyMode(int value)
	{
		inner->SetSafetyMode(value);
	}

	// FUNCTION: ENGINE 0x10B80D60
	int MemoryDebugAllocator::GetSafetyMode()
	{
		return inner->GetSafetyMode();
	}

	// FUNCTION: ENGINE 0x10B80D70
	void MemoryDebugAllocator::SetUnused(int value)
	{
		inner->SetUnused(value);
	}

	// FUNCTION: ENGINE 0x10B80D80
	int MemoryDebugAllocator::GetType()
	{
		return inner->GetType();
	}

	// FUNCTION: ENGINE 0x10B80D90
	void MemoryDebugAllocator::GetRange(MemoryRange* range, int index)
	{
		inner->GetRange(range, index);
	}

	// FUNCTION: ENGINE 0x10B80DA0
	void MemoryDebugAllocator::SetAllocCallback(DebugAllocCallback callback, void* userData)
	{
		CriticalSectionEnter(sLock);
		allocCallback = callback;
		allocUserData = userData;
		CriticalSectionLeave(sLock);
	}

	// FUNCTION: ENGINE 0x10B80DD0
	void MemoryDebugAllocator::SetFreeCallback(DebugFreeCallback callback, void* userData)
	{
		CriticalSectionEnter(sLock);
		freeCallback = callback;
		freeUserData = userData;
		CriticalSectionLeave(sLock);
	}

	// FUNCTION: ENGINE 0x10B80E00
	unsigned int MemoryDebugAllocator::GetHeaderSize()
	{
		return mode != 0 ? 32 : 0;
	}

	// FUNCTION: ENGINE 0x10B80E10
	// Header, block rounded to four bytes, footer; over-allocated by the alignment above 16
	void* MemoryDebugAllocator::AllocFramed(unsigned int size, unsigned int align)
	{
		unsigned int rounded = RoundUp(size, 4);
		unsigned int total = rounded + 32;
		if (align > 16)
		{
			total += align;
		}
		unsigned int raw = (unsigned int)inner->Alloc(total);
		unsigned int block = AlignUp(raw + 16, align);
		CriticalSectionEnter(sLock);
		Header* header = (Header*)(block - 16);
		header->size = rounded;
		header->prev = last;
		header->next = 0;
		if (first == 0)
		{
			first = header;
		}
		else
		{
			last->next = header;
		}
		last = header;
		header->crc = Crc32(&header->size, 12, 0xFFFFFFFF);
		Footer* footer = (Footer*)(block + rounded);
		footer->raw = raw;
		footer->total = total;
		footer->owner = this;
		footer->crc = Crc32(&footer->raw, 12, 0xFFFFFFFF);
		if (header->prev != 0)
		{
			header->prev->crc = Crc32(&header->prev->size, 12, 0xFFFFFFFF);
		}
		blockCount++;
		CriticalSectionLeave(sLock);
		return (void*)block;
	}

	// FUNCTION: ENGINE 0x10B80F00
	void MemoryDebugAllocator::FreeFramed(void* block)
	{
		if (block == 0)
		{
			return;
		}
		CriticalSectionEnter(sLock);
		Header* header = (Header*)block - 1;
		unsigned int raw = ((Footer*)((unsigned int)block + header->size))->raw;
		Header* after = header->next;
		Header* before = header->prev;
		if (header->prev == 0)
		{
			first = header->next;
		}
		else
		{
			header->prev->next = header->next;
		}
		if (header->next == 0)
		{
			last = header->prev;
		}
		else
		{
			header->next->prev = header->prev;
		}
		blockCount--;
		if (after != 0)
		{
			after->crc = Crc32(&after->size, 12, 0xFFFFFFFF);
		}
		if (before != 0)
		{
			before->crc = Crc32(&before->size, 12, 0xFFFFFFFF);
		}
		CriticalSectionLeave(sLock);
		inner->Free((void*)raw);
	}

	// FUNCTION: ENGINE 0x10B80FB0
	bool MemoryDebugAllocator::CheckHeader(Header* header)
	{
		if (header == 0)
		{
			return true;
		}
		if (!OwnsBlock(inner, header))
		{
			return false;
		}
		Footer* footer = (Footer*)((unsigned int)header + header->size + 16);
		if (header->crc != Crc32(&header->size, 12, 0xFFFFFFFF))
		{
			return false;
		}
		if (footer->crc != Crc32(&footer->raw, 12, 0xFFFFFFFF))
		{
			return false;
		}
		if (footer->owner != this)
		{
			return false;
		}
		if (footer->total < header->size)
		{
			return false;
		}
		if (footer->raw > (unsigned int)header)
		{
			return false;
		}
		if (header->next != 0 && !OwnsBlock(inner, header->next))
		{
			return false;
		}
		if (header->prev != 0 && !OwnsBlock(inner, header->prev))
		{
			return false;
		}
		if (header->next != 0 && header->next->prev != header)
		{
			return false;
		}
		if (header->prev != 0 && header->prev->next != header)
		{
			return false;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x10B81090
	// Every frame of one allocator, and the count must agree with the list
	bool CheckHeaders(MemoryDebugAllocator* allocator)
	{
		int count = 0;
		for (MemoryDebugAllocator::Header* header = allocator->first; header != 0; header = header->next)
		{
			count++;
			if (!allocator->CheckHeader(header))
			{
				return false;
			}
		}
		return allocator->blockCount == count;
	}

	// FUNCTION: ENGINE 0x10B810D0
	bool CheckAllocators()
	{
		int count = 0;
		for (MemoryDebugAllocator* allocator = MemoryDebugAllocator::sFirst; allocator != 0; allocator = allocator->next)
		{
			count++;
			if (!CheckHeaders(allocator))
			{
				return false;
			}
		}
		return MemoryDebugAllocator::sCount == count;
	}

	// FUNCTION: ENGINE 0x10B81110
	void MemoryDebugAllocator::Synchronise()
	{
		// Two cases with the same body (the original's switch compares 2 and 3 one after the other)
		switch (mode)
		{
		case 2:
			CriticalSectionEnter(sLock);
			CriticalSectionLeave(sLock);
			break;
		case 3:
			CriticalSectionEnter(sLock);
			CriticalSectionLeave(sLock);
			break;
		}
	}

	// FUNCTION: ENGINE 0x10B81150
	void MemoryDebugAllocator::AddRef()
	{
		RefCount::AddRef();
	}

	// FUNCTION: ENGINE 0x10B81160
	void MemoryDebugAllocator::Release()
	{
		RefCount::Release();
	}

	// FUNCTION: ENGINE 0x10B811D0
	void* MemoryDebugAllocator::Alloc(unsigned int size)
	{
		void* block;
		if (mode == 0)
		{
			block = inner->Alloc(size);
		}
		else
		{
			block = AllocFramed(size, 1);
		}
		Synchronise();
		CriticalSectionEnter(sLock);
		void* userData = allocUserData;
		DebugAllocCallback callback = allocCallback;
		CriticalSectionLeave(sLock);
		if (callback != 0)
		{
			callback(userData, size, 1, block == 0);
		}
		return block;
	}

	// FUNCTION: ENGINE 0x10B81240
	void MemoryDebugAllocator::Free(void* block)
	{
		if (mode == 0)
		{
			inner->Free(block);
		}
		else
		{
			FreeFramed(block);
		}
		Synchronise();
		CriticalSectionEnter(sLock);
		void* userData = freeUserData;
		DebugFreeCallback callback = freeCallback;
		CriticalSectionLeave(sLock);
		if (callback != 0)
		{
			callback(userData, block, false);
		}
	}

	// FUNCTION: ENGINE 0x10B812A0
	// The pass-through result is dropped (the original returns null in mode 0)
	void* MemoryDebugAllocator::AllocAligned(unsigned int size, unsigned int align)
	{
		void* block = 0;
		if (mode == 0)
		{
			inner->AllocAligned(size, align);
		}
		else
		{
			block = AllocFramed(size, align);
		}
		Synchronise();
		CriticalSectionEnter(sLock);
		void* userData = allocUserData;
		DebugAllocCallback callback = allocCallback;
		CriticalSectionLeave(sLock);
		if (callback != 0)
		{
			callback(userData, size, align, block == 0);
		}
		return block;
	}

	// FUNCTION: ENGINE 0x10B81320
	void MemoryDebugAllocator::FreeAligned(void* block)
	{
		if (mode == 0)
		{
			inner->FreeAligned(block);
		}
		else
		{
			FreeFramed(block);
		}
		Synchronise();
		CriticalSectionEnter(sLock);
		void* userData = freeUserData;
		DebugFreeCallback callback = freeCallback;
		CriticalSectionLeave(sLock);
		if (callback != 0)
		{
			callback(userData, block, true);
		}
	}

	// FUNCTION: ENGINE 0x10B81380
	bool MemoryDebugAllocator::IsThreadSafe()
	{
		CriticalSectionEnter(sLock);
		bool valid = CheckHeaders(this);
		CriticalSectionLeave(sLock);
		if (!valid)
		{
			return false;
		}
		return inner->IsThreadSafe();
	}

	// FUNCTION: ENGINE 0x10B813C0
	bool CheckAllocatorsLocked()
	{
		CriticalSectionEnter(MemoryDebugAllocator::sLock);
		bool valid = CheckAllocators();
		CriticalSectionLeave(MemoryDebugAllocator::sLock);
		return valid;
	}

	// FUNCTION: ENGINE 0x10B813F0
	bool CheckDebugAllocators()
	{
		return CheckAllocatorsLocked();
	}

	// FUNCTION: ENGINE 0x10B81430
	MemoryDebugAllocator::MemoryDebugAllocator()
	{
		inner = 0;
		mode = 1;
		next = 0;
		prev = 0;
		first = 0;
		last = 0;
		blockCount = 0;
		allocCallback = 0;
		allocUserData = 0;
		freeCallback = 0;
		freeUserData = 0;
	}

	// FUNCTION: ENGINE 0x10B814A0
	MemoryDebugAllocator* CreateDebugAllocator(IMemoryAllocator* allocator, int mode, int heap)
	{
		MemoryDebugAllocator* debug = new (heap) MemoryDebugAllocator();
		CoreName();
		debug->Init(allocator, mode);
		return debug;
	}
}
