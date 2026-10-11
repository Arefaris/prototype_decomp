#include "code/core/criticalsection.h"
#include "code/core/debugger.h"

namespace core
{
	// GLOBAL: ENGINE 0x1127A444
	unsigned int gDebugPending;
	// GLOBAL: ENGINE 0x1127A44D
	bool gDebugLinkOpen;
	// GLOBAL: ENGINE 0x1127A450
	int gDebugValue;
	// GLOBAL: ENGINE 0x1127A454
	unsigned char gDebugLock[0x18];
	// GLOBAL: ENGINE 0x1127A46C
	int gDebugLockCount;

	// FUNCTION: ENGINE 0x10644760
	void DebugSignal(int value)
	{
	}

	// FUNCTION: ENGINE 0x10644770
	void DebugInit()
	{
	}

	// FUNCTION: ENGINE 0x10644780
	void DebugShutdown()
	{
	}

	// FUNCTION: ENGINE 0x10644790
	int DebugGetZero()
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x106447A0
	int DebugGetValue()
	{
		return gDebugValue;
	}

	// FUNCTION: ENGINE 0x106447B0
	bool DebugIsLinkOpen()
	{
		return gDebugLinkOpen;
	}

	// FUNCTION: ENGINE 0x106447C0
	bool IsDebugLinkClosed()
	{
		return !gDebugLinkOpen;
	}

	// FUNCTION: ENGINE 0x106447D0
	int DebugHasPending()
	{
		return 0 < gDebugPending;
	}

	// FUNCTION: ENGINE 0x106447E0
	void DebugWait(int value)
	{
	}

	// FUNCTION: ENGINE 0x106447F0
	const char* CoreName()
	{
		return "core";
	}

	// FUNCTION: ENGINE 0x10644800
	void DebugLockInit()
	{
		if (gDebugLockCount == 0)
		{
			CriticalSectionInit(gDebugLock);
		}
		gDebugLockCount++;
	}

	// FUNCTION: ENGINE 0x10644820
	void DebugLockShutdown()
	{
		if (gDebugLockCount == 1)
		{
			CriticalSectionDelete(gDebugLock);
		}
		gDebugLockCount--;
	}

	// FUNCTION: ENGINE 0x10644840
	void DebugLockEnter()
	{
		CriticalSectionEnter(gDebugLock);
	}

	// FUNCTION: ENGINE 0x10644850
	void DebugLockLeave()
	{
		CriticalSectionLeave(gDebugLock);
	}

	// FUNCTION: ENGINE 0x10644860
	void DebugGetRange(int* start, int* end)
	{
		*start = 0;
		*end = 0;
	}

	// FUNCTION: ENGINE 0x10644880
	void DebugNop()
	{
	}
}
