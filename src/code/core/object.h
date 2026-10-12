// core::Object and core::RefCount (RTTI names; vftables 0x10E2C040 / 0x10E2C048, one slot each: the virtual
// destructor). Layout and behaviour as the allocators show them (class and member names of the data guessed):
// an Object remembers the heap it was created from; the heap travels through gObjectHeap (0x110BCCBC) from the
// placement operator new into the constructor, and back out of the destructor into operator delete. RefCount adds
// an interlocked count whose Release deletes the object through its virtual destructor.
#ifndef CORE_OBJECT_H
#define CORE_OBJECT_H

#include "code/core/heap.h"

extern "C"
{
	long _InterlockedIncrement(long volatile*);
	long _InterlockedDecrement(long volatile*);
	long _InterlockedExchange(long volatile*, long);
	long _InterlockedAnd(long volatile*, long);
}
#pragma intrinsic(_InterlockedIncrement, _InterlockedDecrement, _InterlockedExchange, _InterlockedAnd)

namespace core
{
	// The heap handed from operator new to the constructor and from the destructor to operator delete; -1 = none
	extern int gObjectHeap;

	class Object
	{
	public:
		Object()
		{
			heap = gObjectHeap;
			gObjectHeap = -1;
		}
		virtual ~Object()
		{
			gObjectHeap = heap;
		}
		void* operator new(unsigned int size, int heap)
		{
			gObjectHeap = heap;
			return HeapAlloc(heap, size);
		}
		void operator delete(void* block)
		{
			if (gObjectHeap != -1)
			{
				HeapFree(gObjectHeap, block);
			}
			gObjectHeap = -1;
		}
		// The XInput controllers' point arrays (their vector deleting destructors inline operator delete[])
		void* operator new[](unsigned int size, int heap)
		{
			gObjectHeap = heap;
			return HeapAlloc(heap, size);
		}
		void operator delete[](void* block)
		{
			if (gObjectHeap != -1)
			{
				HeapFree(gObjectHeap, block);
			}
			gObjectHeap = -1;
		}

		int heap;
	};

	class RefCount : public Object
	{
	public:
		RefCount()
		{
			count = 0;
		}
		// SegmentPoolAllocator starts at one (its factories do not AddRef)
		RefCount(long initial)
		{
			count = initial;
		}
		virtual ~RefCount()
		{
		}
		void AddRef()
		{
			_InterlockedIncrement(&count);
		}
		// The count is parked at a million while the object destroys itself
		void Release()
		{
			long remaining = _InterlockedDecrement(&count);
			if (remaining == 0)
			{
				_InterlockedExchange(&count, 1000000);
				delete this;
			}
		}

		// An atomic read of the count (0x106425D0 is the DirectInput unit's copy)
		long GetCount()
		{
			return _InterlockedAnd(&count, -1);
		}

		// volatile: the stores around the constructor's count = 0 stay (the RefCount vftable store, eax clearing)
		volatile long count;
	};
}

#endif
