// The mid phase's pair batches (assert path code/ravenphysics/batch/src/midphasebatcher.cpp). Names and layout are
// guesses.
#ifndef RAVENPHYSICS_BATCH_MIDPHASEBATCHER_H
#define RAVENPHYSICS_BATCH_MIDPHASEBATCHER_H

namespace ravenphysics
{
	class CollisionObject;
	class NarrowPhaseBatcher;

	// Two objects whose bounds overlap
	struct ObjectPair
	{
		CollisionObject* first;
		CollisionObject* second;
	};

	// Collects pairs into a window of a larger array and hands full windows on
	class PairBatch
	{
	public:
		// Starts a window of 20 pairs at the current offset (0x10691BD0)
		void Begin();
		// Queues the window when it holds pairs (0x10691C20)
		void Flush();

		ObjectPair* entries;
		int count;
		int capacity;
		ObjectPair* buffer;
		int offset;
		int total;
	};

	// One counter of the library's statistics: two values under a name (0x10658200 adds it to the log)
	struct StatEntry
	{
		int first;
		int second;
		int unknown8;
		const char* name;
	};

	// A fixed-size log of statistics, filled from several threads
	class StatLog
	{
	public:
		unsigned int Add(const StatEntry& entry);

		StatEntry* entries;
		int capacity;
		long* count;
	};

	// Collects the object pairs of the mid phase in batches and hands them to the narrow phase batcher
	class MidPhaseBatcher
	{
	public:
		// Queues what is left and, for the last of the callers sharing the batcher, flushes the narrow phase's
		// batches and reports the statistics (0x10691C30)
		void Finish();

		PairBatch pairs;
		unsigned char unknown18[0x28 - 0x18];
		int batchCount;
		int batchTotal;
		unsigned char unknown30[0x50 - 0x30];
		int pendingTasks;
		void* event;
		NarrowPhaseBatcher* narrowPhase;
		int unknown5C;
		long* users;
		unsigned char unknown64[0x70 - 0x64];
		StatLog log;
	};
}

#endif
