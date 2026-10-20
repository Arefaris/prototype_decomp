// The reference counted base of the Scaleform GFx library inside the engine DLL (class names from the RTTI and the
// exports; members are guesses). The count is kept by one of two tables of functions the object points at.
#ifndef GFX_GREFCOUNT_H
#define GFX_GREFCOUNT_H

#include "code/gfx/gmemory.h"

class GRefCountBaseImpl;

// A table of the two functions that keep an object's count: add one and take one away
class GRefCountImpl
{
public:
	void (__fastcall* mAddRef)(GRefCountBaseImpl* object);
	void (__fastcall* mRelease)(GRefCountBaseImpl* object, int unknown);
};

// 0x111ECB90: the count is not kept (an object owned elsewhere), 0x111ECB98: the object counts its owners
extern GRefCountImpl gRefCountNone;
extern GRefCountImpl gRefCountOwners;

// 0x10959290 / 0x109592A0 / 0x109592B0 / 0x109592C0: the functions of the two tables
void __fastcall GRefCountNoneAddRef(GRefCountBaseImpl* object);
void __fastcall GRefCountNoneRelease(GRefCountBaseImpl* object, int unknown);
void __fastcall GRefCountOwnersAddRef(GRefCountBaseImpl* object);
int __fastcall GRefCountOwnersRelease(GRefCountBaseImpl* object, int unknown);

// 0x10959230 / 0x10959240: the operator new and operator delete of the base below
void* GNewOverrideBaseNew(unsigned int size);
void GNewOverrideBaseDelete(void* block);

// The base of the library's objects that are allocated through the global allocator
class GNewOverrideBase
{
public:
	static void* operator new(unsigned int size)
	{
		return GMemory::Alloc(size);
	}
	static void operator delete(void* block)
	{
		GMemory::Free(block);
	}
};

// What a weak pointer keeps to know the object it points at is gone (8 bytes)
class GWeakProxy : public GNewOverrideBase
{
public:
	// 0x10959250 / 0x10959260 / 0x10959270 / 0x10959280
	GWeakProxy()
	{
		mRefCount = 1;
		mAlive = true;
	}
	void Detach()
	{
		mAlive = false;
	}
	void AddRef()
	{
		mRefCount++;
	}
	void Release()
	{
		if (--mRefCount == 0)
		{
			delete this;
		}
	}

	int mRefCount;     // 0x00
	bool mAlive;       // 0x04
};

// Objects the library keeps count of (vftable 0x10E8D374, one slot: the deleting destructor)
class GRefCountBaseImpl
{
public:
	// 0x109592E0 / 0x10959320 (exported)
	GRefCountBaseImpl();
	GRefCountBaseImpl(GRefCountImpl* owners, GRefCountImpl* none);
	// 0x10959370 (exported)
	virtual ~GRefCountBaseImpl();
	// 0x10959390 (exported): only mode 0 is known; an object that is not counted refuses
	bool SetRefCountMode(unsigned int mode);
	// 0x109593C0: the weak proxy of the object, made when asked for the first time (one more owner of it)
	GWeakProxy* GetWeakProxy();
	// 0x109595F0: the object's own count functions
	void AddRef()
	{
		mImpl->mAddRef(this);
	}
	void Release()
	{
		mImpl->mRelease(this, 0);
	}

	// A block of an object made by new is marked, so that the constructor knows the object is not on the stack
	static void* operator new(unsigned int size)
	{
		void* block = GMemory::Alloc(size);
		if (block)
		{
			((unsigned int*)block)[1] = 0x56471E89;
			((unsigned int*)block)[2] = 0x9FE1234A;
		}
		return block;
	}
	static void operator delete(void* block)
	{
		GMemory::Free(block);
	}

	volatile int mRefCount;        // 0x04
	GRefCountImpl* mImpl;          // 0x08
	GWeakProxy* mWeakProxy;        // 0x0C
};

// The class a library object derives from to be counted (RTTI: GRefCountBase<class GFile>, ...)
template<class C>
class GRefCountBase : public GRefCountBaseImpl
{
public:
	GRefCountBase()
	{
	}
};

// A pointer to a counted object (names guessed; the engine has an instance of each function per class)
template<class T>
class GPtr
{
public:
	// 0x1095BD50: takes the object (one more owner of it)
	GPtr(T* object)
	{
		if (object)
		{
			object->AddRef();
		}
		mObject = object;
	}
	// 0x1095BD70: takes another object, gives the one it had back
	GPtr& operator=(T* object)
	{
		if (object)
		{
			object->AddRef();
		}
		if (mObject)
		{
			mObject->Release();
		}
		mObject = object;
		return *this;
	}
	// 0x1095BDA0: gives the object back and takes another that is already counted
	GPtr& SetCounted(T* object)
	{
		if (mObject)
		{
			mObject->Release();
		}
		mObject = object;
		return *this;
	}
	// 0x1095A560 / 0x1095A590: gives the object back
	void ReleaseObject()
	{
		if (mObject)
		{
			mObject->Release();
		}
	}
	// 0x1095A580: the object without counting it
	GPtr& SetRaw(T* object)
	{
		mObject = object;
		return *this;
	}
	// 0x1095A5B0 / 0x1095A5C0 / 0x1095BDD0 / 0x1095BDE0
	T* GetPtr() const
	{
		return mObject;
	}

	T* mObject;
};

#endif
