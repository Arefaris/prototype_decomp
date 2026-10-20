// The library's start-up and shut-down (unit 0x10661510 - 0x10661BB0, no assert path; file name guessed). All names
// are guesses.
#ifndef RAVENPHYSICS_PHYSICS_H
#define RAVENPHYSICS_PHYSICS_H

namespace ravenphysics
{
	// What the library is started with (0x106619B0 sets the defaults)
	struct InitSettings
	{
		InitSettings();

		int materialCapacity;               // 0x00 (room for the registry of materials)
		int intersectionPropertyCapacity;   // 0x04
		int unknown8;                       // 0x08 (kept in 0x1127E42C)
		unsigned int scratchStackSize;      // 0x0C
		unsigned int collisionObjectCapacity;  // 0x10 (slots of the handle table)
		float unknown14;                    // 0x14
		float unknown18;                    // 0x18
		int unknown1C;                      // 0x1C
		int unknown20;                      // 0x20
		int unknown24;                      // 0x24
	};

	// How much of everything the library has in use (0x3C bytes; 0x10661BB0)
	struct Statistics
	{
		int materialCount;                  // 0x00
		int materialCapacity;               // 0x04
		unsigned int intersectionPropertyCount;  // 0x08
		int intersectionPropertyCapacity;   // 0x0C
		unsigned int collisionObjectCount;  // 0x10
		unsigned int collisionObjectCapacity;  // 0x14
		unsigned int scratchStackSize;      // 0x18
		unsigned int scratchStackUsed;      // 0x1C
		unsigned int scratchStackPeak;      // 0x20
		int arrayASize;                     // 0x24
		int arrayACapacity;                 // 0x28
		int arrayBSize;                     // 0x2C
		int arrayBCapacity;                 // 0x30
		int arrayCSize;                     // 0x34
		int arrayCCapacity;                 // 0x38
	};

	// Sets the library up: the tables, the registries, the scratch stack and the tasks (0x10661B10)
	void Init(const InitSettings* settings);
	// Takes it all down again (0x10661A40)
	void Shutdown();
	// Fills the statistics, folding the scratch stack's high water mark into its peak (0x10661BB0)
	void GetStatistics(Statistics* statistics);

	// The settings the library was started with (0x1127D3DC)
	extern InitSettings gSettings;
}

#endif
