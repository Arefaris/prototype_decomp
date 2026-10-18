// The small classes of the narrow phase's collision info list (assert path
// code/ravenphysics/batch/src/narrowphase/buildcollisioninfolist.cpp). Names and layout are guesses.
#ifndef RAVENPHYSICS_BATCH_BUILDCOLLISIONINFOLIST_H
#define RAVENPHYSICS_BATCH_BUILDCOLLISIONINFOLIST_H

#include <xmmintrin.h>

#include "code/ravenphysics/common/stackallocator.h"

namespace ravenphysics
{
	struct CollisionHandle;

	// What the narrow phase knows about a pair of volumes it reports on (0x30 bytes: ten floats, a word, the types
	// of the two volumes and a byte)
	struct PairInfo
	{
		// Copies the members one by one (0x106B29D0)
		PairInfo& operator=(const PairInfo& other);

		float values[10];
		int unknown28;
		unsigned char typeA;     // 0x2C
		unsigned char typeB;     // 0x2D
		unsigned char unknown2E;
	};

	// One record of the sorted lists the collision info is built from: the key it is ordered by and two words
	struct InfoRecord
	{
		unsigned int key;
		unsigned int first;
		unsigned int second;
	};

	// A run of records over the scratch stack and the unit's copies of its accessors (names are guesses)
	struct InfoRecordArray
	{
		// Takes the storage: count records aligned to align (0x106B2A90)
		void Create(unsigned int newCount, int align);
		void SetCount(int newCount);
		InfoRecord* At(int index);
		InfoRecord* GetItems();
		int GetCount();

		InfoRecord* items;
		int count;
		ScratchStack allocator;
	};

	// The same run for another record (0x106B2A40)
	struct InfoRecordArraySecond
	{
		void SetCount(int newCount);

		void* items;
		int count;
	};

	// Copies four floats on a 16 byte boundary in one piece (0x106B2BD0; name guess)
	void CopyQuad(float* destination, const float* source);
	// Reports the types of the volumes of a pair (0x106B2970)
	void ReportPair(const PairInfo* info);
	// Two functions that do nothing (0x106B29C0 / 0x106B2A80)
	void DoNothingFirst();
	void DoNothingSecond();
	// Merges two runs of records ordered by key into one, the first run first among equal keys (0x106B2AE0)
	void MergeRecords(InfoRecord* out, const InfoRecord* first, unsigned int firstCount, const InfoRecord* second,
		unsigned int secondCount);
	// Reports how many collisions two objects of the handle table have, with the volumes they collide with
	// (0x106B2BF0)
	void ReportCollisions(int unused, const CollisionHandle* handleA, const CollisionHandle* handleB,
		unsigned int volumeA, unsigned int volumeB, int count);
}

#endif
