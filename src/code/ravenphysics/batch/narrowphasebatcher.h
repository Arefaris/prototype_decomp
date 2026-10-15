// The narrow phase batcher's pairs and queues (assert path code/ravenphysics/batch/src/narrowphasebatcher.cpp). Names
// and layout are guesses.
#ifndef RAVENPHYSICS_BATCH_NARROWPHASEBATCHER_H
#define RAVENPHYSICS_BATCH_NARROWPHASEBATCHER_H

#include "code/core/asynctask.h"

#include "code/ravenphysics/collision/collisionobject.h"

namespace ravenphysics
{
	class PhysicsObject;
	struct PairDetails;

	// The batcher the narrow phase's pairs are queued in and worked off from (assert path
	// code/ravenphysics/batch/src/narrowphasebatcher.cpp; the class name is the unit's, the layout is not recovered
	// yet and the context unit only holds a pointer to it)
	class NarrowPhaseBatcher
	{
	public:
		// Waits for every queued batch and reports what was left over (0x106911D0; name guess)
		void Complete();

		unsigned char unknown0[0x400];
	};

	// The pairs of one collision-type queue, filled until the capacity is reached
	struct Batch
	{
		PairDetails* storage;
		int count;
		int capacity;
		int type;
	};

	// What the batches are cut from: a block of 64-byte pair records and how many are taken
	struct BatchPool
	{
		PairDetails* records;
		int used;
	};

	// The 0x60-byte record a queued batch is handed on in (0x10690190 fills it in)
	class BatchTask
	{
	public:
		void Set(int type, const Batch* batch, void* queue, const int* ids, long* counter);

		Batch batch;
		void* queue;
		int ids[2];
		unsigned char unknown1C[0x50 - 0x1c];
		int type;
		long* counter;
		unsigned char unknown58[0x60 - 0x58];
	};

	// A timing record the task system fills in: the first 16 bytes are core::AsyncTaskTiming
	struct ProfileEvent
	{
		core::AsyncTaskTiming timing;
		bool unknown10;
		bool unknown11;
		const char* name;
		short code;
		short unknown1A;
		int unknown1C;
	};

	// Both sides of a colliding pair: for each a body, its object and the object's volume with its type
	__declspec(align(16)) struct PairDetails
	{
		PairDetails()
			: unknown0(-1), unknown8(-1), unknown14(-1), unknown1C(-1)
		{
		}

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

	// The size of a batch by collision type (6 ints at 0x10E4C9E4)
	extern const int gBatchSizes[6];

	// A snapshot of the narrow phase batcher's queues that a thread works with: a pointer to each type's batch, the
	// pool and the counters the batches share, and a copy of each type's task (0x10690A50 submits a batch)
	class NarrowPhaseJob
	{
	public:
		NarrowPhaseJob()
			: unknown24(0), unknown28(0), profileEvents(0), profileCapacity(0), profileCounter(0), unknown11C(0),
			  unknown120(0), unknown124(0)
		{
		}

		// Takes the batcher's pointers and values; pairIndex is the running index of the pairs added (0x106901E0)
		void Init(NarrowPhaseBatcher* batcher, int pairIndex);
		// Submits every non-empty batch and starts a new one (0x10690CC0)
		unsigned int FlushAll();
		// Queues a batch as a task; with no room left for another batch it only reports that (0x10690A50)
		void Submit(Batch* batch);
		// Adds the pair of two volumes to the batch of its collision type; a full batch is queued and replaced
		// (0x10690F70)
		bool AddPair(PhysicsObject* bodyA, PhysicsObject* bodyB, CollisionObject* objectA, CollisionObject* objectB,
			CollisionVolume* volumeA, CollisionVolume* volumeB, unsigned short indexA, unsigned short indexB);
		// Waits for nothing: signals that the batches are queued (0x106909A0)
		void Complete();

		Batch* batches[6];
		BatchPool* pool;
		long* lock;
		int pairIndex;
		int unknown24;
		int unknown28;
		long* batchCounter;
		core::AsyncTask tasks[6];
		int unknownF0[6];
		void* profileQueue;
		void* event;
		ProfileEvent* profileEvents;
		int profileCapacity;
		long* profileCounter;
		int unknown11C;
		int unknown120;
		int unknown124;
		long* queuedCounter;
		long* typeCounts;
		long* pairCounter;
	};

	// Works out the pair's collision type like NarrowPhaseJob::AddPair and fills in details (0x106904E0)
	void BuildPairDetails(PairDetails* details, PhysicsObject* bodyA, PhysicsObject* bodyB, CollisionObject* objectA,
		CollisionObject* objectB, CollisionVolume* volumeA, CollisionVolume* volumeB, unsigned short indexA,
		unsigned short indexB);
}

#endif
