// pure3d::pddiObject, what the pddi layer hands out by reference count (unit around 0x10611F90 - 0x10612000; the file
// name is guessed, no assert path survives).
#include "code/core/interlocked.h"
#include "code/pure3d/pddi.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x10611F90
	pddiObject::pddiObject()
	{
		mRefCount = 0;
	}

	// FUNCTION: ENGINE 0x10611AF0
	pddiObject::~pddiObject()
	{
	}

	// FUNCTION: ENGINE 0x10611B00
	void pddiObject::Unknown3()
	{
		Release();
	}

	// FUNCTION: ENGINE 0x10611FC0
	void pddiObject::AddRef()
	{
		_InterlockedIncrement((long volatile*)&mRefCount);
	}

	// FUNCTION: ENGINE 0x10611FD0
	void pddiObject::Release()
	{
		long count = _InterlockedDecrement((volatile long*)&mRefCount);
		if (count < 1)
		{
			delete this;
		}
	}

	// FUNCTION: ENGINE 0x10611E10
	ConstantSlot::ConstantSlot()
	{
		index = -1;
	}

	// FUNCTION: ENGINE 0x10611E50
	ConstantSlot::ConstantSlot(const ConstantName* constant)
	{
		index = (unsigned short)constant->index;
	}

	// FUNCTION: ENGINE 0x10611E20
	ConstantSlot::ConstantSlot(int kind, const core::Name<core::CaseInsensitiveKey32>* name)
	{
		pddi->constants->Find(this, kind, name);
	}
}

// Kept copies (compiler-generated and inline functions of this unit):
// FUNCTION: ENGINE 0x10611FA0
