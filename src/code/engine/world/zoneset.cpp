// The zones the world is streamed in (see zoneset.h).
#include "code/engine/world/zoneset.h"

namespace engine
{
	ZoneSet* gZoneSet;  // 0x11317800
	const void* gDefaultZoneTable;  // 0x113177EC

	// FUNCTION: ENGINE 0x10894830
	ZoneSet* GetZoneSet()
	{
		return gZoneSet;
	}

	// FUNCTION: ENGINE 0x10894850
	void ZoneSet::SetDefaults(const void* table)
	{
		gDefaultZoneTable = table;
	}

	// FUNCTION: ENGINE 0x10894860
	void ZoneSet::AddZone(const char* newName, const char* newFile, unsigned int newCount, const ZoneEntry* newEntries)
	{
		name = newName;
		file = newFile;
		entryCount = newCount;
		entries = newEntries;
		total = 0;
		const ZoneEntry* entry = newEntries;
		for (unsigned int index = 0; index < entryCount; index++)
		{
			total += entry->count;
			if (entry->size > largest)
			{
				largest = entry->size;
			}
			entry++;
		}
	}
}
