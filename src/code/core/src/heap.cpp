#include <string.h>

#include "code/core/heap.h"
#include "code/core/memory/imemoryallocator.h"
#include "code/core/memory/memoryallocatormalloc.h"
#include "code/core/memory/memoryspace.h"
#include "code/core/memory/rangemap.h"
#include "code/core/thread.h"

namespace core
{
	// One heap: its allocator and its place in the tree of heaps
	struct HeapEntry
	{
		IMemoryAllocator* allocator;
		HeapEntry* children;
		HeapEntry* next;
		HeapEntry* parent;
	};

	// The address map (0x11277F98): a RangeMap over a fixed buffer of 0x100 ranges. The buffer starts at the
	// RangeMap's heap member (a fixed map never uses it). Its dynamic initializer is 0x10D66890.
	class HeapMap : public RangeMap
	{
	public:
		HeapMap();
		~HeapMap();
		void Init(int defaultValue);

		Pair buffer[0x201];
	};

	HeapMap gHeapMap;

	// GLOBAL: ENGINE 0x11276F50
	static int sHeapSlot;
	// GLOBAL: ENGINE 0x11276F54
	static IMemoryAllocator* sMallocAllocator;
	// GLOBAL: ENGINE 0x11276F58
	static HeapEntry sSystemHeap;
	// GLOBAL: ENGINE 0x11276F78
	static HeapEntry sHeapTable[0x101];
	// GLOBAL: ENGINE 0x11277F88
	static bool sMemoryReady;
	// GLOBAL: ENGINE 0x11277F8C
	static AllocFailHook sAllocFailHook;
	// GLOBAL: ENGINE 0x11277F90
	static void* sAllocFailUser;
	// GLOBAL: ENGINE 0x110BC5A4
	HeapEntry* gHeaps = sHeapTable;

	// Every heap back to one allocator, the tree flat
	static __forceinline void ResetHeaps(IMemoryAllocator* allocator)
	{
		sSystemHeap.allocator = allocator;
		sSystemHeap.children = 0;
		sSystemHeap.next = 0;
		sSystemHeap.parent = 0;
		HeapEntry* heaps = gHeaps;
		for (int i = 0; i < 0x101; i++)
		{
			heaps[i].children = 0;
			heaps[i].parent = 0;
			heaps[i].next = 0;
			heaps[i].allocator = allocator;
		}
	}

	// FUNCTION: ENGINE 0x1063A6A0
	void MemoryNop1()
	{
	}

	// FUNCTION: ENGINE 0x1063A6B0
	void MemoryNop2()
	{
	}

	// FUNCTION: ENGINE 0x1063A6C0
	void ShutdownMemoryStage2()
	{
		FreeThreadDataSlot(sHeapSlot);
		ShutdownMemorySpace();
		sMemoryReady = false;
		GetSystemAllocatorDestroy();
		gHeapMap.Reset();
	}

	// FUNCTION: ENGINE 0x1063A6F0
	int GetCurrentHeap()
	{
		int heap;
		return GetThreadDataValue(sHeapSlot, &heap) ? heap : 0;
	}

	// FUNCTION: ENGINE 0x1063A710
	int SetCurrentHeap(int heap)
	{
		int previous;
		return ExchangeThreadDataValue(sHeapSlot, &previous, heap) ? previous : 0;
	}

	// FUNCTION: ENGINE 0x1063A740
	void SetSystemAllocator(IMemoryAllocator* allocator)
	{
		allocator->AddRef();
		ResetHeaps(allocator);
	}

	// FUNCTION: ENGINE 0x1063A790
	void ResetSystemAllocator()
	{
		IMemoryAllocator* installed = sSystemHeap.allocator;
		ResetHeaps(sMallocAllocator);
		installed->Release();
	}

	// FUNCTION: ENGINE 0x1063A7F0
	void SetAllocFailHook(AllocFailHook hook, void* user)
	{
		sAllocFailHook = hook;
		sAllocFailUser = user;
	}

	// FUNCTION: ENGINE 0x1063A810
	inline void CheckAlloc(void* block, unsigned int size, unsigned int align, int flags, int heap)
	{
		if (block == 0 && sAllocFailHook != 0)
		{
			sAllocFailHook(sAllocFailUser, heap, size, align, flags);
		}
	}

	// FUNCTION: ENGINE 0x1063A850
	void* HeapAlloc(int heap, unsigned int size)
	{
		IMemoryAllocator* allocator = gHeaps[heap].allocator;
		void* block = allocator->Alloc(size);
		CheckAlloc(block, size, 1, 0, heap);
		return block;
	}

	// FUNCTION: ENGINE 0x1063A8A0
	void* HeapAllocZero(int heap, unsigned int size)
	{
		void* block = HeapAlloc(heap, size);
		if (block != 0)
		{
			memset(block, 0, size);
		}
		return block;
	}

	// FUNCTION: ENGINE 0x1063A8D0
	void* HeapAllocAligned(int heap, unsigned int size, unsigned int align)
	{
		if (align < 4)
		{
			align = 4;
		}
		IMemoryAllocator* allocator = gHeaps[heap].allocator;
		void* block = allocator->AllocAligned(size, align);
		CheckAlloc(block, size, align, 0, heap);
		return block;
	}

	// FUNCTION: ENGINE 0x1063A930
	void* HeapAllocFlags(int heap, unsigned int size, unsigned int align, int flags, int unused)
	{
		if (align < 4)
		{
			align = 4;
		}
		IMemoryAllocator* allocator = gHeaps[heap].allocator;
		void* block = allocator->AllocFlags(size, align, flags, unused);
		CheckAlloc(block, size, align, flags, heap);
		return block;
	}

	// FUNCTION: ENGINE 0x1063A9A0
	void HeapFree(int heap, void* block)
	{
		IMemoryAllocator* allocator = gHeaps[heap].allocator;
		allocator->Free(block);
	}

	// FUNCTION: ENGINE 0x1063A9C0
	void HeapFreeAligned(int heap, void* block)
	{
		IMemoryAllocator* allocator = gHeaps[heap].allocator;
		allocator->FreeAligned(block);
	}

	// FUNCTION: ENGINE 0x1063A9E0
	void HeapFreeFlags(int heap, void* block)
	{
		IMemoryAllocator* allocator = gHeaps[heap].allocator;
		allocator->FreeFlags(block);
	}

	// FUNCTION: ENGINE 0x1063AA00
	IMemoryAllocator* GetHeapAllocator(int heap)
	{
		return gHeaps[heap].allocator;
	}

	// FUNCTION: ENGINE 0x1063AA20
	static int GetHeapIndex(HeapEntry* entry)
	{
		if (entry == &sSystemHeap)
		{
			return 0x100;
		}
		return entry - gHeaps;
	}

	// FUNCTION: ENGINE 0x1063AA40
	static bool IsHeapAllocator(int heap, IMemoryAllocator* allocator)
	{
		return allocator == gHeaps[heap].allocator;
	}

	// FUNCTION: ENGINE 0x1063AA60
	static bool HeapContains(IMemoryAllocator* allocator, void* block)
	{
		if (block == 0)
		{
			return true;
		}
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

	// FUNCTION: ENGINE 0x1063AAC0
	static int GetBlockHeap(void* block)
	{
		return gHeapMap.Get((unsigned int)block);
	}

	// FUNCTION: ENGINE 0x1063AAD0
	HeapScope::HeapScope(int heap)
	{
		previous = GetCurrentHeap();
		SetCurrentHeap(heap);
	}

	// FUNCTION: ENGINE 0x1063AAF0
	HeapScope::~HeapScope()
	{
		SetCurrentHeap(previous);
	}

	// FUNCTION: ENGINE 0x1063AB00
	HeapMap::HeapMap()
	{
	}

	// FUNCTION: ENGINE 0x1063AB10
	HeapMap::~HeapMap()
	{
	}

	// FUNCTION: ENGINE 0x1063AB20
	void HeapMap::Init(int defaultValue)
	{
		RangeMap::Init(defaultValue, 0x100, (Pair*)&heap);
	}

	// FUNCTION: ENGINE 0x1063AB40
	void MemoryNop3()
	{
	}

	// FUNCTION: ENGINE 0x1063AB50
	void MemoryNop4()
	{
	}

	// FUNCTION: ENGINE 0x1063AB60
	void AddRefAllocator(IMemoryAllocator* allocator)
	{
		allocator->AddRef();
	}

	// FUNCTION: ENGINE 0x1063AB70
	void ReleaseAllocator(IMemoryAllocator* allocator)
	{
		allocator->Release();
	}

	// FUNCTION: ENGINE 0x1063AB80
	void InitMemoryStage2()
	{
		if (!sMemoryReady)
		{
			sMemoryReady = true;
			IMemoryAllocator* allocator = GetSystemAllocatorInit();
			sMallocAllocator = allocator;
			ResetHeaps(allocator);
			gHeapMap.Init(0x100);
			InitMemorySpace();
			AllocThreadDataSlot(&sHeapSlot, 0);
		}
	}

	// FUNCTION: ENGINE 0x1063AC00
	// EQUIVALENT: the original loads the allocator straight into ecx (vtable in eax, slot in edx); ours loads it into
	// eax and copies it to ecx (index form, entry pointer, local, inline accessor tried)
	void Free(void* block)
	{
		HeapEntry* entry = &gHeaps[GetBlockHeap(block)];
		entry->allocator->Free(block);
	}

	// FUNCTION: ENGINE 0x1063AC30
	// EQUIVALENT: the original loads the allocator straight into ecx (vtable in eax, slot in edx); ours loads it into
	// eax and copies it to ecx (index form, entry pointer, local, inline accessor tried)
	void FreeAligned(void* block)
	{
		HeapEntry* entry = &gHeaps[GetBlockHeap(block)];
		entry->allocator->FreeAligned(block);
	}

	// FUNCTION: ENGINE 0x1063AC60
	// EQUIVALENT: the original loads the allocator straight into ecx (vtable in eax, slot in edx); ours loads it into
	// eax and copies it to ecx (index form, entry pointer, local, inline accessor tried)
	void FreeFlags(void* block)
	{
		HeapEntry* entry = &gHeaps[GetBlockHeap(block)];
		entry->allocator->FreeFlags(block);
	}

	// FUNCTION: ENGINE 0x1063AC90
	IMemoryAllocator* GetBlockAllocator(void* block)
	{
		return GetHeapAllocator(GetBlockHeap(block));
	}

	// FUNCTION: ENGINE 0x1063ACB0
	bool IsBlockInHeap(void* block, int heap)
	{
		if (heap == -1)
		{
			return false;
		}
		if (block == 0)
		{
			return true;
		}
		HeapEntry* entry = &gHeaps[heap];
		if (entry->allocator == sSystemHeap.allocator)
		{
			entry = &sSystemHeap;
		}
		if (!HeapContains(entry->allocator, block))
		{
			return false;
		}
		HeapEntry* sibling = entry;
		if (entry->parent != 0)
		{
			sibling = entry->parent->children;
		}
		for (; sibling != 0; sibling = sibling->next)
		{
			if (sibling->allocator == entry->allocator)
			{
				for (HeapEntry* child = sibling->children; child != 0; child = child->next)
				{
					if (HeapContains(child->allocator, block))
					{
						return false;
					}
				}
			}
		}
		return true;
	}

	// FUNCTION: ENGINE 0x1063AD50
	// EQUIVALENT: same blocks except one: the original places the `owner = parent` block after the `before` branch
	// (out of line, jumping back); with the reset loaded after the Release call the zero / parent registers swap
	void UnregisterHeap(int heap)
	{
		HeapEntry* entry = &gHeaps[heap];
		HeapEntry* parent = entry->parent;
		HeapEntry* twin = 0;
		HeapEntry* before = 0;
		HeapEntry* last = 0;
		for (HeapEntry* sibling = parent->children; sibling != 0; sibling = sibling->next)
		{
			if (sibling == entry)
			{
				before = last;
			}
			else if (twin == 0 && sibling->allocator == entry->allocator)
			{
				twin = sibling;
			}
			last = sibling;
		}
		HeapEntry* owner;
		if (twin != 0)
		{
			// The heaps inside move to the sibling over the same allocator
			HeapEntry* child = entry->children;
			if (child != 0)
			{
				while (child->next != 0)
				{
					child->parent = twin;
					child = child->next;
				}
				child->parent = twin;
				child->next = twin->children;
				twin->children = entry->children;
				entry->children = 0;
			}
			owner = twin;
		}
		else
		{
			owner = parent;
		}
		gHeapMap.ReplaceValue(heap, GetHeapIndex(owner));
		if (before != 0)
		{
			before->next = entry->next;
		}
		else
		{
			parent->children = entry->next;
		}
		entry->allocator->Release();
		entry->children = 0;
		entry->parent = 0;
		entry->next = 0;
		entry->allocator = sSystemHeap.allocator;
	}

	// FUNCTION: ENGINE 0x1063AE10
	// EQUIVALENT: the loop matches; the original keeps the entry in edi (spilled) and pushes ebx only on the loop path,
	// ours keeps the entry in ebx, and stores parent before children (if / else, ternary and a 0x100 start tried)
	void RegisterHeap(int index, IMemoryAllocator* allocator)
	{
		if (gHeaps[index].allocator != sSystemHeap.allocator)
		{
			UnregisterHeap(index);
		}
		allocator->AddRef();
		HeapEntry* entry = &gHeaps[index];
		unsigned int count = allocator->GetType();
		HeapEntry* parent;
		if (count == 0)
		{
			parent = &sSystemHeap;
		}
		else
		{
			int found = -1;
			for (unsigned int i = 0; i < count; i++)
			{
				MemoryRange range;
				allocator->GetRange(&range, i);
				int previous = 0;
				int result = gHeapMap.Set(range.start, range.end, index, &previous);
				found = previous;
				if (result == 2)
				{
					// The range crosses a heap boundary: the heap over this allocator that contains it
					HeapEntry* owner = &gHeaps[found];
					while (owner != 0 && owner->allocator != allocator)
					{
						owner = owner->parent;
					}
					found = GetHeapIndex(owner->parent);
				}
				else if (result == 1 && IsHeapAllocator(found, allocator))
				{
					HeapEntry* owner = gHeaps[found].parent;
					if (owner != 0)
					{
						found = GetHeapIndex(owner);
					}
					else
					{
						found = 0x100;
					}
				}
			}
			if (found == 0x100)
			{
				parent = &sSystemHeap;
			}
			else
			{
				parent = &gHeaps[found];
			}
		}
		entry->allocator = allocator;
		entry->children = 0;
		entry->parent = parent;
		entry->next = parent->children;
		parent->children = entry;
	}

	// FUNCTION: ENGINE 0x1063AF60
	void RegisterHeap(int index, int parent, IMemoryAllocator* allocator)
	{
		RegisterHeap(index, allocator);
	}
}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D66890
// FUNCTION: ENGINE 0x10D86820
