// The counted chained slot table's function that clears a bucket (0x10683230; a unit of its own: the engine does not know
// which registers FreeBucket keeps); see chaintable.h.
#include "code/ravenphysics/chaintable.h"

namespace ravenphysics
{
	// FUNCTION: ENGINE 0x10683230
	void CountedWordChainTable::ClearBucket(unsigned short bucket)
	{
		FreeBucket(bucket);
		counts[bucket] = 0;
	}
}
