// choreo drivers (the driver type tables around 0x10956360 - 0x10956700; file name guessed). Names are guesses.
#include "code/choreo/puppet.h"

namespace choreo
{
	// FUNCTION: ENGINE 0x109560C0
	void UpdateDriver(Driver* driver, float dt)
	{
		gDriverUpdate[driver->mType](driver, dt);
	}
}
