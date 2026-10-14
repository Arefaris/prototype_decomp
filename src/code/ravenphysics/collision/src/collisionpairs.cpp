// The pair tests between collision objects (unit around 0x106A3B40 - 0x106A5400; file name and function names are
// guesses).
#include "code/ravenphysics/batch/narrowphasebatcher.h"
#include "code/ravenphysics/collision/collisioninfo.h"
#include "code/ravenphysics/collision/narrowphase/narrowphase.h"
#include "code/ravenphysics/common/stackallocator.h"
#include "code/ravenphysics/physicsobject.h"

namespace ravenphysics
{
	// Collides the volumes of one pair of collision objects and records what they report, or hands the pair to the
	// batcher when there is one
	// FUNCTION: ENGINE 0x106A4BC0
	void CollidePair(PhysicsObject* bodyA, PhysicsObject* bodyB, CollisionObject* objectA, CollisionObject* objectB,
		unsigned short indexA, unsigned short indexB, CollisionVolume* volumeA, CollisionVolume* volumeB,
		CollisionInfoList* infos, CollideInfo* info, NarrowPhaseJob* job)
	{
		if (job != 0)
		{
			job->AddPair(bodyA, bodyB, objectA, objectB, volumeA, volumeB, indexA, indexB);
			return;
		}
		PairDetails details;
		BuildPairDetails(&details, bodyA, bodyB, objectA, objectB, volumeA, volumeB, indexA, indexB);
		ScratchStack stack;
		ScratchStackFrame frame;
		unsigned int capacity = infos->capacity;
		ContactBuffer contacts;
		contacts.contacts = 0;
		contacts.count = 0;
		contacts.capacity = 0;
		contacts.contacts = (Contact*)stack.Alloc(capacity * sizeof(Contact), 16);
		contacts.count = 0;
		contacts.capacity = capacity;
		bool normalPair = volumeA->swapped == 0 && volumeB->swapped == 0;
		if (!normalPair)
		{
			if (info->unknown1C != 0)
			{
				info->unknown24 = objectB;
			}
			CollideVolumesSwapped(volumeA, volumeB, &contacts, info);
		}
		else
		{
			if (info->unknown1C != 0)
			{
				info->unknown24 = objectA;
			}
			CollideVolumes(volumeA, volumeB, &contacts, info);
		}
		for (unsigned int i = 0; i < contacts.count; i++)
		{
			if (infos->count == infos->capacity)
			{
				break;
			}
			infos->count++;
			CollisionInfo* slot = infos->infos + (infos->count - 1);
			if (slot != 0)
			{
				slot->Init(contacts.contacts + i, &details);
			}
		}
	}

	// The unit's instances of StackAllocator::AllocArray
	// FUNCTION: ENGINE 0x106A3EE0
	template unsigned short* StackAllocator::AllocArray<unsigned short>(int, int);
}
