#include "code/core/criticalsection.h"
#include "code/core/memory/allocatorbase.h"
#include "code/core/strings.h"

namespace core
{
	// FUNCTION: ENGINE 0x10646D10
	AllocatorBase_Name::~AllocatorBase_Name()
	{
	}

	// FUNCTION: ENGINE 0x10646D20
	const char* AllocatorBase_Name::GetName()
	{
		return name;
	}

	// FUNCTION: ENGINE 0x10646D30
	void AllocatorBase_Name::SetName(const char* value)
	{
		StrNCpy(name, value, sizeof(name));
	}

	// FUNCTION: ENGINE 0x10646D50
	AllocatorBase_Safety::AllocatorBase_Safety()
	{
		flag = 0;
		mode = 1;
	}

	// FUNCTION: ENGINE 0x10646D70
	AllocatorBase_Safety::~AllocatorBase_Safety()
	{
		if (mode == 2)
		{
			CriticalSectionDelete(section);
		}
	}

	// FUNCTION: ENGINE 0x10646D80
	// Mode 2 guards the allocator with the critical section; the owner is not used
	void AllocatorBase_Safety::SetMode(int value, void* owner)
	{
		if (value != mode)
		{
			if (mode == 2)
			{
				CriticalSectionDelete(section);
			}
			mode = value;
			if (value == 2)
			{
				CriticalSectionInit(section);
			}
			flag = 0;
		}
	}

	// FUNCTION: ENGINE 0x10646DC0
	int AllocatorBase_Safety::GetMode()
	{
		return mode;
	}

	// FUNCTION: ENGINE 0x10646DD0
	void AllocatorBase_Safety::SetUnused(int value)
	{
	}

	// FUNCTION: ENGINE 0x10646DE0
	void AllocatorBase_Safety::Lock()
	{
		if (mode == 2)
		{
			CriticalSectionEnter(section);
		}
	}

	// FUNCTION: ENGINE 0x10646DF0
	void AllocatorBase_Safety::Unlock()
	{
		if (mode == 2)
		{
			CriticalSectionLeave(section);
		}
	}

	// FUNCTION: ENGINE 0x10646E00
	AllocatorBase_Name::AllocatorBase_Name()
	{
		SetName("unknown");
	}
}
