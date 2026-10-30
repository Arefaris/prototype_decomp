// The first pair table's entries that hand the volumes and the contact buffer on to the pair function proper, and
// Names are guesses.
#include "code/ravenphysics/collision/narrowphase/narrowphase.h"

namespace ravenphysics
{
	// The pair functions proper (another unit, 0x106C4150 - 0x106CACF0)
	void CollideCapsulesPair(CollisionCapsule* a, CollisionCapsule* b, ContactBuffer* contacts);
	void CollideCapsuleBoxPair(CollisionCapsule* a, CollisionOBB* b, ContactBuffer* contacts);
	void CollideCapsulePlanePair(CollisionCapsule* a, CollisionPlane* b, ContactBuffer* contacts);
	void CollideCapsuleSpherePair(CollisionCapsule* a, CollisionSphere* b, ContactBuffer* contacts);
	void CollideBoxesPair(CollisionOBB* a, CollisionOBB* b, ContactBuffer* contacts);
	void CollideBoxPlanePair(CollisionOBB* a, CollisionPlane* b, ContactBuffer* contacts);
	void CollideBoxSpherePair(CollisionOBB* a, CollisionSphere* b, ContactBuffer* contacts);
	void CollideSpherePlanePair(CollisionSphere* a, CollisionPlane* b, ContactBuffer* contacts);
	void CollideSpheresPair(CollisionSphere* a, CollisionSphere* b, ContactBuffer* contacts);

	// FUNCTION: ENGINE 0x106B2190
	void CollideCapsules(CollisionCapsule* a, CollisionCapsule* b, ContactBuffer* contacts, CollideInfo* info)
	{
		CollideCapsulesPair(a, b, contacts);
	}

	// FUNCTION: ENGINE 0x106B21B0
	void CollideCapsuleBox(CollisionCapsule* a, CollisionOBB* b, ContactBuffer* contacts, CollideInfo* info)
	{
		CollideCapsuleBoxPair(a, b, contacts);
	}

	// FUNCTION: ENGINE 0x106B21D0
	void CollideCapsulePlane(CollisionCapsule* a, CollisionPlane* b, ContactBuffer* contacts, CollideInfo* info)
	{
		CollideCapsulePlanePair(a, b, contacts);
	}

	// FUNCTION: ENGINE 0x106B21F0
	void CollideCapsuleSphere(CollisionCapsule* a, CollisionSphere* b, ContactBuffer* contacts, CollideInfo* info)
	{
		CollideCapsuleSpherePair(a, b, contacts);
	}

	// FUNCTION: ENGINE 0x106B2210
	void CollideBoxes(CollisionOBB* a, CollisionOBB* b, ContactBuffer* contacts, CollideInfo* info)
	{
		CollideBoxesPair(a, b, contacts);
	}

	// FUNCTION: ENGINE 0x106B2230
	void CollideBoxPlane(CollisionOBB* a, CollisionPlane* b, ContactBuffer* contacts, CollideInfo* info)
	{
		CollideBoxPlanePair(a, b, contacts);
	}

	// FUNCTION: ENGINE 0x106B2250
	void CollideBoxSphere(CollisionOBB* a, CollisionSphere* b, ContactBuffer* contacts, CollideInfo* info)
	{
		CollideBoxSpherePair(a, b, contacts);
	}

	// FUNCTION: ENGINE 0x106B2270
	void CollideSpherePlane(CollisionSphere* a, CollisionPlane* b, ContactBuffer* contacts, CollideInfo* info)
	{
		CollideSpherePlanePair(a, b, contacts);
	}

	// FUNCTION: ENGINE 0x106B2290
	void CollideSpheres(CollisionSphere* a, CollisionSphere* b, ContactBuffer* contacts, CollideInfo* info)
	{
		CollideSpheresPair(a, b, contacts);
	}
}
