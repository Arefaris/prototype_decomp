// The narrow phase of the physics library: the pair dispatch over the seven collision volume types
// (code/ravenphysics, unit around 0x106A2630 - 0x106B2900; file and names are guesses).
#ifndef RAVENPHYSICS_COLLISION_NARROWPHASE_NARROWPHASE_H
#define RAVENPHYSICS_COLLISION_NARROWPHASE_NARROWPHASE_H

#include "code/math/vector.h"
#include "code/ravenphysics/collision/collisionobject.h"

namespace ravenphysics
{
	// One contact of a collision test (48 bytes)
	struct Contact
	{
		math::Vector points[2];
		float unknown18;
		float unknown1C;
		float unknown20;
		float unknown24;
		int unknown28;
		unsigned short unknown2C;
		unsigned char unknown2E;
	};

	// The contacts a pair function reports; its room is allocated by the caller
	struct ContactBuffer
	{
		// The next free contact
		Contact* Next()
		{
			count++;
			return contacts + count - 1;
		}
		// Records a hit that has no contact data, naming the triangle of a mesh (-1 for none); false when the
		// buffer is full (0x106A8450; name guess)
		bool AddFace(int face);

		Contact* contacts;
		unsigned int count;
		unsigned int capacity;
	};

	// What a pair function needs besides the volumes
	struct CollideInfo
	{
		unsigned char unknown0[0x1c];
		int unknown1C;
		int unknown20;
		void* unknown24;
	};

	typedef void (*CollideFunction)(CollisionVolume* a, CollisionVolume* b, ContactBuffer* contacts, CollideInfo* info);

	// The pair functions by type of a and b (7 x 7, only a <= b is filled), 0x110C48D8 / 0x110C49A0
	extern CollideFunction gCollideTable[7 * 7];
	extern CollideFunction gCollideTableSwapped[7 * 7];

	// Calls the pair function of the two volumes' types (0x106B2110 / 0x106B2150)
	void CollideVolumes(CollisionVolume* a, CollisionVolume* b, ContactBuffer* contacts, CollideInfo* info);
	void CollideVolumesSwapped(CollisionVolume* a, CollisionVolume* b, ContactBuffer* contacts, CollideInfo* info);
}

#endif
