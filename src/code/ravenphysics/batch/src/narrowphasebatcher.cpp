#include "code/core/debug.h"
#include "code/core/interlocked.h"
#include "code/ravenphysics/batch/narrowphasebatcher.h"
#include "code/ravenphysics/physicsobject.h"

#define NARROWPHASEBATCHER_FILE "..\\..\\..\\code\\ravenphysics\\batch\\src\\narrowphasebatcher.cpp"

namespace ravenphysics
{
	// FUNCTION: ENGINE 0x10690100
	void PairDetails::Set(const int& idA, void* pointerA, const int& idB, void* objectA, unsigned char typeA,
		void* volumeA, const int& idC, void* bodyB, const int& idD, void* objectB, unsigned char typeB, void* volumeB,
		unsigned short unknown28, unsigned short unknown2A, int unknown30)
	{
		unknown0 = idA;
		unknown4 = pointerA;
		unknown8 = idB;
		unknownC = objectA;
		this->typeA = typeA;
		unknown10 = volumeA;
		unknown14 = idC;
		unknown18 = bodyB;
		unknown1C = idD;
		unknown20 = objectB;
		this->typeB = typeB;
		unknown24 = volumeB;
		this->unknown28 = unknown28;
		this->unknown2A = unknown2A;
		this->unknown30 = unknown30;
	}

	// FUNCTION: ENGINE 0x10690A50
	void NarrowPhaseJob::Submit(Batch* batch)
	{
		BatchTask* slot;
		long* counter = batchCounter;
		long index = _InterlockedIncrement(counter) - 1;
		if (index < 0x400)
		{
			slot = (BatchTask*)((char*)counter + index * 0x60 + 0x10);
		}
		else
		{
			_InterlockedExchangeAdd(counter, -1);
			slot = 0;
		}
		if (slot == 0)
		{
			long queued;
			long* queuedPointer;
			static bool sQueued = true;
			if (sQueued && (queuedPointer = batchCounter, queued = _InterlockedAnd(queuedPointer, -1),
				core::Report(0, " Pre ", NARROWPHASEBATCHER_FILE, 109, 0, "%d batches queued", queued, 0)) == 3)
			{
				sQueued = false;
			}
			static bool sPerType = true;
			if (sPerType && core::Report(0, " Pre ", NARROWPHASEBATCHER_FILE, 110, 0, "Per type: ", 0) == 3)
			{
				sPerType = false;
			}
			for (unsigned int i = 0; i < 6; i++)
			{
				long* typeCount = typeCounts + i;
				unsigned int counts = _InterlockedAnd(typeCount, -1);
				static bool sType = true;
				if (sType && core::Report(0, " Pre ", NARROWPHASEBATCHER_FILE, 115, 0, "Type %d: %d Batches, %d Pairs", i,
					(short)(counts >> 16), (short)counts, 0) == 3)
				{
					sType = false;
				}
			}
			OLD_ASSERT_AT(NARROWPHASEBATCHER_FILE, 118, 0, "0", "");
		}
		int type = batch->type;
		slot->Set(type, batch, profileQueue, &unknown24, queuedCounter);
		core::AsyncTask task = tasks[type];
		task.data = slot;
		task.timing = 0;
		if (profileCounter != 0)
		{
			ProfileEvent* event = 0;
			long eventIndex = _InterlockedIncrement(profileCounter) - 1;
			if (eventIndex < profileCapacity)
			{
				event = profileEvents + eventIndex;
			}
			else
			{
				_InterlockedDecrement(profileCounter);
			}
			if (event != 0)
			{
					task.timing = &event->timing;
					event->name = 0;
					event->timing.processor = -1;
					event->code = type + 8;
					event->unknown10 = false;
					event->timing.start = 0;
					event->timing.end = 0;
					event->unknown11 = true;
			}
		}
		union
		{
			struct
			{
				short pairs;
				short batches;
			} parts;
			long all;
		} delta;
		delta.parts.pairs = (short)batch->count;
		delta.parts.batches = 1;
		_InterlockedExchangeAdd(typeCounts + type, delta.all);
		_InterlockedIncrement(queuedCounter);
		core::SubmitAsyncTasks(&task, 1, 2);
	}

	// FUNCTION: ENGINE 0x10690F70
	// NONMATCHING: the original saves registers late and keeps this on the stack, with the pointers to the bodies' ids
	// and the batch in registers; ours keeps this in edi and the type in ebp (about 40 % of the instructions line up)
#ifdef NONMATCHING
	bool NarrowPhaseJob::AddPair(PhysicsObject* bodyA, PhysicsObject* bodyB, CollisionObject* objectA,
		CollisionObject* objectB, CollisionVolume* volumeA, CollisionVolume* volumeB, unsigned short indexA,
		unsigned short indexB)
	{
		int kind;
		if (objectA == 0 || objectB == 0 || volumeA->swapped != 0 || volumeB->swapped != 0)
		{
			kind = 5;
		}
		else if (volumeB->type == 6)
		{
			switch (volumeA->type)
			{
			case 0:
			case 1:
				kind = 2;
				break;
			case 2:
			case 4:
				kind = 3;
				break;
			case 3:
				kind = 4;
				break;
			case 5:
				return true;
			case 6:
				return true;
			default:
				return true;
			}
		}
		else if (volumeB->type == 3 || volumeB->type == 4 || volumeA->type == 3 || volumeA->type == 4)
		{
			kind = 1;
		}
		else
		{
			kind = 0;
		}
		int index = pairIndex++;
		int size = gBatchSizes[kind];
		Batch* batch = batches[kind];
		bool full = false;
		long* lockPointer = lock;
		do
		{
		}
		while (_InterlockedCompareExchange(lockPointer, 1, 0) != 0);
		batch->count++;
		PairDetails* record = batch->storage + (batch->count - 1);
		const int& bodyAId = bodyA->id;
		const int& bodyBId = bodyB->id;
		if (kind == 5)
		{
			int idA = -1;
			int idB = -1;
			if (objectA != 0)
			{
				idA = objectA->id;
			}
			if (objectB != 0)
			{
				idB = objectB->id;
			}
			unsigned char typeA = 0xff;
			if (volumeA != 0)
			{
				typeA = volumeA->type;
			}
			unsigned char typeB = 0xff;
			if (volumeB != 0)
			{
				typeB = volumeB->type;
			}
			record->Set(bodyAId, bodyA, idA, objectA, typeA, volumeA, bodyBId, bodyB, idB, objectB, typeB, volumeB,
				indexA, indexB, index);
		}
		else
		{
			record->Set(bodyAId, bodyA, objectA->id, objectA, volumeA->type, volumeA, bodyBId, bodyB, objectB->id,
				objectB, volumeB->type, volumeB, indexA, indexB, index);
		}
		Batch full_;
		full_.storage = 0;
		full_.count = 0;
		full_.capacity = 0;
		full_.type = 6;
		if (batch->count == size)
		{
			full_.count = batch->count;
			full_.storage = batch->storage;
			full_.capacity = batch->capacity;
			full_.type = batch->type;
			int used = pool->used;
			pool->used = used + size;
			batch->storage = pool->records + used;
			full = true;
			batch->count = 0;
			batch->capacity = size;
			batch->type = kind;
		}
		_InterlockedExchange(lock, 0);
		if (full)
		{
			Submit(&full_);
		}
		_InterlockedIncrement(pairCounter);
		return true;
	}
#endif
}
