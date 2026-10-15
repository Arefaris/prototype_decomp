// ravenphysics collision objects and volumes (assert path code/ravenphysics/collision/src/collisionobject.cpp). Only the
// members the reconstructed code touches are named; the layout is partial and every name is a guess.
#ifndef RAVENPHYSICS_COLLISION_COLLISIONOBJECT_H
#define RAVENPHYSICS_COLLISION_COLLISIONOBJECT_H

#include "code/math/vector.h"

namespace ravenphysics
{
	// The head shared by all collision volume types; type indexes the narrow phase's dispatch tables
	struct CollisionVolume
	{
		unsigned char type;
		unsigned char swapped;
		unsigned char material;
		unsigned char unknown3;
		math::Vector boundsMin;
		math::Vector boundsMax;
	};

	class CollisionObject
	{
	public:
		// Clears the changed flag and tells whether it was set
		bool TestAndClearChanged()
		{
			bool wasChanged = changed;
			changed = false;
			return wasChanged;
		}

		// Bit 1 of the surface flags behind +0x64 (0x106555F0; name guess)
		bool IsSurfaceActive() const;
		// Hands the object to the world it now belongs to (0x10655600; name guess)
		void SetWorld(void* world);

		unsigned char unknown0[0x48];
		int id;
		int unknown4C;
		CollisionVolume** volumes;
		unsigned short volumeCount;
		unsigned char changed : 1;
		unsigned char unknown56 : 7;
		unsigned char unknown57;
		unsigned int state;
	};
}

#endif
