// The Lua scheduling natives of the game library (schedule, scheduleObject, schedulePersistent, unschedule) and the
// chunk name reader the script manager's error reports ask. Unit 0x108A6D90 - 0x108A7130 (no assert path names it; the
// file name is a guess).
#include "code/engine/luascriptmanager.h"

namespace engine
{
	// FUNCTION: ENGINE 0x108A6DA0
	// The reader of the file and line of a chunk name finds nothing in this build
	bool ParseChunkName(const char* name, unsigned int* first, unsigned int* second)
	{
		return false;
	}
}
