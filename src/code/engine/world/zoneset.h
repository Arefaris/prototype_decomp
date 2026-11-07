// The zones the world is streamed in (engine::ZoneSet and its entries; code/engine/world/zoneset.cpp, the unit starts at
// 0x10894830; no assert path, the file name and every name are guesses).
#ifndef ENGINE_WORLD_ZONESET_H
#define ENGINE_WORLD_ZONESET_H

namespace engine
{
	// One zone of a package (0x18 bytes)
	struct ZoneEntry
	{
		unsigned char unknown0[8];
		unsigned int size;  // +8
		unsigned char unknownC[4];
		unsigned int count;  // +0x10
		unsigned char unknown14[4];
	};

	class ZoneSet
	{
	public:
		// 0x10894850: remembers the table of zones every world starts with (a global, not a member)
		void SetDefaults(const void* table);
		// 0x10894860: adds a zone and its package file with that many entries
		void AddZone(const char* name, const char* file, unsigned int entryCount, const ZoneEntry* newEntries);

		// 0x108948D0: told when the window gains or loses the focus
		void Unknown108948D0(bool focused);
		// 0x108951B0: reloads the zones when the level changes (name unknown)
		void Unknown108951B0();

		int unknown0;
		const char* name;  // +4
		const char* file;  // +8
		const ZoneEntry* entries;  // +0xC
		unsigned int entryCount;  // +0x10
		int unknown14;
		int unknown18;
		unsigned int total;  // +0x1C
		unsigned int largest;  // +0x20
	};

	// 0x10894830
	ZoneSet* GetZoneSet();
}

#endif
