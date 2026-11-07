// pure3d::RefCounted and pure3d::LockableRefCounted (code/pure3d/src/refcounted.cpp, file name guessed from the
// classes; the unit starts at 0x106E2900): the interlocked reference counts of the render objects. Names are guesses.
#include "code/core/interlocked.h"
#include "code/pure3d/context.h"
#include "code/pure3d/entity.h"
#include "code/pure3d/pose.h"

#include <new>


namespace core
{
	void StrFree(char* text);
}

namespace pure3d
{
	// FUNCTION: ENGINE 0x106E2900
	RefCounted::~RefCounted()
	{
	}

	// FUNCTION: ENGINE 0x106E2910
	void RefCounted::operator delete(void* block)
	{
		::operator delete(block);
	}

	// FUNCTION: ENGINE 0x106E2930
	void* RefCounted::operator new(unsigned int size)
	{
		return ::operator new[](size);
	}

	// FUNCTION: ENGINE 0x106E2A00
	void RefCounted::AddRef()
	{
		_InterlockedIncrement((long volatile*)&mRefCount);
	}

	// FUNCTION: ENGINE 0x106E2A10
	void RefCounted::Release()
	{
		long remaining = _InterlockedDecrement((long volatile*)&mRefCount);
		if (remaining < 1)
		{
			delete this;
		}
	}

	// FUNCTION: ENGINE 0x106E2A30
	void LockableRefCounted::Lock()
	{
		AddRef();
		_InterlockedIncrement((long volatile*)&mLock);
	}

	// FUNCTION: ENGINE 0x106E2A50
	void LockableRefCounted::Unlock()
	{
		_InterlockedDecrement((long volatile*)&mLock);
		Release();
	}

	// FUNCTION: ENGINE 0x106E2A70
	void LockableRefCounted::AddRef()
	{
		_InterlockedIncrement((long volatile*)&mRefCount);
	}

	// FUNCTION: ENGINE 0x106E2A80
	void LockableRefCounted::Release()
	{
		long remaining = _InterlockedDecrement((long volatile*)&mRefCount);
		if (remaining < 1)
		{
			delete this;
		}
	}

	// FUNCTION: ENGINE 0x106E2AA0
	ContextKey::~ContextKey()
	{
		if (ownsText)
		{
			core::StrFree((char*)text);
		}
	}
}
