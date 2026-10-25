// What the physics content loader (RTTI: ravenphysics::PhysicsObjectLoader) keeps between the objects it reads: three
// lists of the objects it loaded or looked up by name, so a name read twice finds the same object. Unit 0x1067C400 -
// 0x1067F800 (no assert path, so the file name is a guess); names are guesses.
#ifndef RAVENPHYSICS_PHYSICSOBJECTLOADER_H
#define RAVENPHYSICS_PHYSICSOBJECTLOADER_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/core/name.h"

namespace ravenphysics
{
	// One object of a list under its name (0x10 bytes; copying it leaves the fourth word alone)
	struct LoaderEntry
	{
		LoaderEntry()
		{
		}
		LoaderEntry(const LoaderEntry& other) :
			name(other.name)
		{
			object = other.object;
		}

		core::Name<core::CaseSensitiveKey> name;   // 0x00
		void* object;                              // 0x08
		int unknownC;                              // 0x0C
	};

	typedef container::ArrayDynamic<LoaderEntry, container::AllocatorNew> LoaderList;

	// The material loaders, the intersection properties and the mass properties read so far (0x1127E468, 0x1127E458
	// and 0x1127E448)
	extern LoaderList gStatArrayA;
	extern LoaderList gStatArrayB;
	extern LoaderList gStatArrayC;
}

#endif
