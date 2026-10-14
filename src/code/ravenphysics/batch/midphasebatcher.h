// The mid phase's pair batches (assert path code/ravenphysics/batch/src/midphasebatcher.cpp). Names and layout are
// guesses.
#ifndef RAVENPHYSICS_BATCH_MIDPHASEBATCHER_H
#define RAVENPHYSICS_BATCH_MIDPHASEBATCHER_H

namespace ravenphysics
{
	class CollisionObject;

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

		ObjectPair* entries;
		int count;
		int capacity;
		ObjectPair* buffer;
		int offset;
	};
}

#endif
