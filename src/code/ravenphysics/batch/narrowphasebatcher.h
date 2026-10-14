// The narrow phase's pair records (assert path code/ravenphysics/batch/src/narrowphasebatcher.cpp). Names and layout
// are guesses; the first half of a record (0x20 bytes) holds the two bodies, the second half is the PairDetails
// built here.
#ifndef RAVENPHYSICS_BATCH_NARROWPHASEBATCHER_H
#define RAVENPHYSICS_BATCH_NARROWPHASEBATCHER_H

namespace ravenphysics
{
	// Both sides of a colliding pair: for each a body, its object and the object's volume with its type
	struct PairDetails
	{
		// Fills in all members (0x10690100)
		void Set(const int& idA, void* pointerA, const int& idB, void* objectA, unsigned char typeA, void* volumeA,
			const int& idC, void* bodyB, const int& idD, void* objectB, unsigned char typeB, void* volumeB,
			unsigned short unknown28, unsigned short unknown2A, int unknown30);

		int unknown0;
		void* unknown4;
		int unknown8;
		void* unknownC;
		void* unknown10;
		int unknown14;
		void* unknown18;
		int unknown1C;
		void* unknown20;
		void* unknown24;
		unsigned short unknown28;
		unsigned short unknown2A;
		unsigned char typeA;
		unsigned char typeB;
		int unknown30;
	};
}

#endif
