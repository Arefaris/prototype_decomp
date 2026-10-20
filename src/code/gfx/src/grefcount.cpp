// The reference counting of the Scaleform GFx library inside the engine DLL (the unit starting at 0x10959230; file name
// guessed).
#include "code/gfx/grefcount.h"

// FUNCTION: ENGINE 0x10959230
void* GNewOverrideBaseNew(unsigned int size)
{
	return GMemory::Alloc(size);
}

// FUNCTION: ENGINE 0x10959240
void GNewOverrideBaseDelete(void* block)
{
	GMemory::Free(block);
}

// The functions of the header that the engine also has on their own
// FUNCTION: ENGINE 0x10959260 ; GWeakProxy::Detach
// FUNCTION: ENGINE 0x10959270 ; GWeakProxy::AddRef
// FUNCTION: ENGINE 0x10959280 ; GWeakProxy::Release
void (GWeakProxy::*gKeepWeakProxy[])() = {&GWeakProxy::Detach, &GWeakProxy::AddRef, &GWeakProxy::Release};

// FUNCTION: ENGINE 0x10959250 ; GWeakProxy::GWeakProxy
#pragma inline_depth(0)
void GKeepWeakProxyConstructor()
{
	new GWeakProxy;
}
#pragma inline_depth()

GRefCountImpl gRefCountNone = {GRefCountNoneAddRef, GRefCountNoneRelease};
GRefCountImpl gRefCountOwners = {GRefCountOwnersAddRef, (void (__fastcall*)(GRefCountBaseImpl*))GRefCountOwnersRelease};

// FUNCTION: ENGINE 0x10959290
void __fastcall GRefCountNoneAddRef(GRefCountBaseImpl* object)
{
}

// FUNCTION: ENGINE 0x109592A0
void __fastcall GRefCountNoneRelease(GRefCountBaseImpl* object)
{
}

// FUNCTION: ENGINE 0x109592B0
void __fastcall GRefCountOwnersAddRef(GRefCountBaseImpl* object)
{
	object->mRefCount++;
}

// FUNCTION: ENGINE 0x109592C0
// EQUIVALENT: the virtual call of the deleting destructor loads the table pointer into the other one of eax and edx (100 % otherwise)
int __fastcall GRefCountOwnersRelease(GRefCountBaseImpl* object)
{
	int count = --object->mRefCount;
	if (count != 0)
	{
		return count;
	}
	delete object;
}

// FUNCTION: ENGINE 0x109592E0
GRefCountBaseImpl::GRefCountBaseImpl()
{
	mWeakProxy = 0;
	if (mRefCount == 0x56471E89 && mImpl == (GRefCountImpl*)0x9FE1234A)
	{
		mRefCount = 1;
		mImpl = &gRefCountOwners;
		return;
	}
	mRefCount = 0;
	mImpl = &gRefCountNone;
}

// FUNCTION: ENGINE 0x10959320
GRefCountBaseImpl::GRefCountBaseImpl(GRefCountImpl* owners, GRefCountImpl* none)
{
	mWeakProxy = 0;
	if (mRefCount == 0x56471E89 && mImpl == (GRefCountImpl*)0x9FE1234A)
	{
		mRefCount = 1;
		mImpl = owners;
		return;
	}
	mRefCount = 0;
	if (none == 0)
	{
		none = &gRefCountNone;
	}
	mImpl = none;
}

// FUNCTION: ENGINE 0x10959370
GRefCountBaseImpl::~GRefCountBaseImpl()
{
	if (mWeakProxy)
	{
		mWeakProxy->Detach();
		mWeakProxy->Release();
	}
}

// FUNCTION: ENGINE 0x10959390
bool GRefCountBaseImpl::SetRefCountMode(unsigned int mode)
{
	if (mImpl != &gRefCountNone)
	{
		switch (mode)
		{
		case 0:
			mImpl = &gRefCountOwners;
			return true;
		case 1:
			return false;
		}
	}
	return false;
}

// FUNCTION: ENGINE 0x109593C0
GWeakProxy* GRefCountBaseImpl::GetWeakProxy()
{
	if (mWeakProxy == 0)
	{
		mWeakProxy = new GWeakProxy;
		if (mWeakProxy == 0)
		{
			return 0;
		}
	}
	mWeakProxy->AddRef();
	return mWeakProxy;
}

// FUNCTION: ENGINE 0x109595F0 ; GRefCountBaseImpl::AddRef
void (GRefCountBaseImpl::*gKeepRefCountBase[])() = {&GRefCountBaseImpl::AddRef};
