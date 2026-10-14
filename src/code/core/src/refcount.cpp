// core::SafeReleaseRef (name guessed; the address sits next to the other per-type copies of core's release helper,
// 0x10098F60 / 0x10098FB0 / 0x10098FD0, so it is one instantiation of the SafeRelease template of
// code/core/refptr.h, kept out of line in this unit): releases a reference through core::IRefCount and clears the
// pointer. The sequencer's unit calls it, which is why its callers treat it as clobbering every register.
#include "code/core/refptr.h"

namespace core
{
	// FUNCTION: ENGINE 0x10098F90
	void SafeReleaseRef(core::IRefCount*& object)
	{
		if (object != 0)
		{
			object->Release();
			object = 0;
		}
	}
}
