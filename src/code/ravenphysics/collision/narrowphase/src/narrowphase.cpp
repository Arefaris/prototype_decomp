#include "code/ravenphysics/collision/narrowphase/narrowphase.h"

namespace ravenphysics
{
	// FUNCTION: ENGINE 0x106B2110
	void CollideVolumes(CollisionVolume* a, CollisionVolume* b, ContactBuffer* contacts, CollideInfo* info)
	{
		gCollideTable[a->type * 7 + b->type](a, b, contacts, info);
	}

	// FUNCTION: ENGINE 0x106B2150
	// EQUIVALENT: the original loads both type bytes into al / dl first and keeps the index in edi; ours widens them
	// as it goes
	void CollideVolumesSwapped(CollisionVolume* a, CollisionVolume* b, ContactBuffer* contacts, CollideInfo* info)
	{
		unsigned char typeA = a->type;
		unsigned char typeB = b->type;
		gCollideTableSwapped[typeA * 7 + typeB](a, b, contacts, info);
	}
}
