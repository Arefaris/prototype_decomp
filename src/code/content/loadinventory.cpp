// content::LoadInventory: the lock every inventory shares and the flag accessors (unit 0x10601BB0 - 0x10603820; the
// name table's functions are not reconstructed yet).
#include "code/content/loadinventory.h"

namespace content
{
	// FUNCTION: ENGINE 0x10601BB0
	void InitInventoryLock()
	{
		core::CriticalSectionInit(gInventoryLock);
	}

	// FUNCTION: ENGINE 0x10601BC0
	void DeleteInventoryLock()
	{
		core::CriticalSectionDelete(gInventoryLock);
	}

	// FUNCTION: ENGINE 0x10601C30
	bool LoadInventory::GetUnknown8()
	{
		return unknown8;
	}
}
