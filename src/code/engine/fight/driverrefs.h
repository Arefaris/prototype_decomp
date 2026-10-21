// The reference helpers the actions of the choreo driver tracks use for the driver they hold (names guessed): the
// engine keeps one out-of-line copy of each per driver type.
#ifndef ENGINE_FIGHT_DRIVERREFS_H
#define ENGINE_FIGHT_DRIVERREFS_H

#include "code/choreo/puppet.h"

namespace engine
{
	// Drops the reference and clears the pointer
	template<class T> void ReleaseDriverRef(T*& driver)
	{
		if (driver != 0)
		{
			driver->Release();
			driver = 0;
		}
	}

	// Takes a reference on the new driver and gives up the one on the old
	template<class T> void AssignDriverRef(T*& driver, T* newDriver)
	{
		if (newDriver != 0)
		{
			newDriver->AddRef();
		}
		if (driver != 0)
		{
			driver->Release();
		}
		driver = newDriver;
	}
}

#endif
