#include "code/core/criticalsection.h"
#include "code/core/debug.h"
#include "code/core/interlocked.h"
#include "code/ravenphysics/batch/midphasebatcher.h"
#include "code/ravenphysics/batch/narrowphasebatcher.h"

#define MIDPHASEBATCHER_FILE "..\\..\\..\\code\\ravenphysics\\batch\\src\\midphasebatcher.cpp"

namespace ravenphysics
{
	// FUNCTION: ENGINE 0x10691BD0
	void PairBatch::Begin()
	{
		entries = buffer + offset;
		count = 0;
		capacity = 20;
	}

	// FUNCTION: ENGINE 0x10691C30
	void MidPhaseBatcher::Finish()
	{
		pairs.Flush();
		OLD_ASSERT_TEXT_AT(MIDPHASEBATCHER_FILE, 109, pairs.count == 0, "0 == mPairList.GetPairList().Size()");
		long value = _InterlockedDecrement(users);
		OLD_ASSERT_TEXT_AT(MIDPHASEBATCHER_FILE, 111, value >= 0, "value >= 0");
		if (value == 0)
		{
			NarrowPhaseJob job;
			job.Init(narrowPhase, -1);
			job.FlushAll();
			job.Complete();
		}
		StatEntry entry;
		entry.first = batchCount;
		entry.second = batchTotal;
		entry.name = "MP Batches";
		entry.unknown8 = 0;
		log.Add(entry);
		entry.first = pairs.offset;
		entry.second = pairs.total;
		entry.name = "MP Pairs";
		entry.unknown8 = 0;
		log.Add(entry);
		core::EventSignal(event, 0x7ffe - pendingTasks);
	}
}
