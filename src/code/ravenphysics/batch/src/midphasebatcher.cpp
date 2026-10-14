#include "code/ravenphysics/batch/midphasebatcher.h"

namespace ravenphysics
{
	// FUNCTION: ENGINE 0x10691BD0
	void PairBatch::Begin()
	{
		entries = buffer + offset;
		count = 0;
		capacity = 20;
	}
}
