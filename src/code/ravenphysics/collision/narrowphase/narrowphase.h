// The narrow phase of the physics library: the pair dispatch over the seven collision volume types
// (code/ravenphysics, unit around 0x106A2630 - 0x106B2900; file and names are guesses).
#ifndef RAVENPHYSICS_COLLISION_NARROWPHASE_NARROWPHASE_H
#define RAVENPHYSICS_COLLISION_NARROWPHASE_NARROWPHASE_H

#include "code/ravenphysics/collision/collisionobject.h"

namespace ravenphysics
{
	struct ContactBuffer;
	struct CollideInfo;

	typedef void (*CollideFunction)(CollisionVolume* a, CollisionVolume* b, ContactBuffer* contacts, CollideInfo* info);

	// The pair functions by type of a and b (7 x 7, only a <= b is filled), 0x110C48D8 / 0x110C49A0
	extern CollideFunction gCollideTable[7 * 7];
	extern CollideFunction gCollideTableSwapped[7 * 7];

	// Calls the pair function of the two volumes' types (0x106B2110 / 0x106B2150)
	void CollideVolumes(CollisionVolume* a, CollisionVolume* b, ContactBuffer* contacts, CollideInfo* info);
	void CollideVolumesSwapped(CollisionVolume* a, CollisionVolume* b, ContactBuffer* contacts, CollideInfo* info);
}

#endif
