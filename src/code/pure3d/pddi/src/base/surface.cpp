// pure3d::pddiSurface (a render target or texture of the device; unit around 0x1061C000, file name guessed). Names
// are guesses.
#include "code/pure3d/pddi.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x1061C480
	int pddiSurface::GetHandle()
	{
		return handle;
	}
}
