// proto::TimeSliceManager (RTTI class; one vftable slot, the deleting destructor): spreads work over the frames. Two
// fixed lists, eight and 512 entries, behind a flag and a counter; the entries' types are not recovered. Unit
// 0x103B2510 - 0x103B2560 (no assert path; the file name is a guess); member names are guesses.
#ifndef PROTO_TIMESLICEMANAGER_H
#define PROTO_TIMESLICEMANAGER_H

#include "code/container/arrayfixed.h"

namespace proto
{
	class TimeSliceManager
	{
	public:
		// 0x103B2510
		TimeSliceManager();
		// 0x103B2540 (deleting destructor 0x103B2560)
		virtual ~TimeSliceManager();

		bool unknown4;
		int unknown8;
		container::ArrayFixed<void*, 8> unknownC;  // +0xC
		container::ArrayFixed<int, 512> unknown30;  // +0x30
	};
}

#endif
