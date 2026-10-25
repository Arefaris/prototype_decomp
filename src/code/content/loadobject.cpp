// content::LoadObject: the allocation and the reference count of the content library's objects (unit starting at
// 0x105FE690; the file name is guessed).
#include "code/content/loadinventory.h"
#include "code/core/heap.h"
#include "code/core/interlocked.h"
#include <new>

namespace content
{
	// FUNCTION: ENGINE 0x105FE690
	void* LoadObject::operator new(unsigned int size)
	{
		return operator new[](size);
	}

	// FUNCTION: ENGINE 0x105FE6C0
	void* LoadObject::operator new(unsigned int size, int heap)
	{
		int previous = core::SetCurrentHeap(heap);
		void* block = operator new[](size);
		core::SetCurrentHeap(previous);
		return block;
	}

	// FUNCTION: ENGINE 0x105FE720
	void LoadObject::operator delete(void* block)
	{
		::operator delete(block);
	}

	// FUNCTION: ENGINE 0x105FE740
	void LoadObject::AddRef()
	{
		_InterlockedIncrement((long volatile*)&refCount);
	}

	// FUNCTION: ENGINE 0x105FE750
	void LoadObject::Release()
	{
		long remaining = _InterlockedDecrement((long volatile*)&refCount);
		if (remaining == 0)
		{
			_InterlockedExchange((long volatile*)&refCount, 0x8000000);
			delete this;
		}
	}
}
