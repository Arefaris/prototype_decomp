// ravenphysics::PhysicsObject and the lock the library sets while it simulates (assert path
// code/ravenphysics/src/physicsobject.cpp). Only the members the reconstructed code touches are named; the layout is
// partial and every name is a guess except the class names the RTTI gives.
#ifndef RAVENPHYSICS_PHYSICSOBJECT_H
#define RAVENPHYSICS_PHYSICSOBJECT_H

#include "code/content/loadinventory.h"
#include "code/math/vector.h"
#include "code/ravenphysics/broadphase/broadphasedetector.h"

namespace ravenphysics
{
	class CollisionObject;

	// The library's lock: set while a simulation step runs, when the objects must not be touched (0x1127D3D8)
	class PhysicsLock
	{
	public:
		bool IsLocked() const
		{
			return locked;
		}

		bool locked;
	};

	extern PhysicsLock gLock;

	// ravenphysics::BroadPhaseObject (RTTI): an object with bounds in a detector
	class BroadPhaseObject : public content::LoadObject
	{
	public:
		math::Vector boundsMin;
		math::Vector boundsMax;
		int id;
		unsigned char unknown24[0x34 - 0x24];
		BroadPhaseDetector* detector;
		unsigned short detectorIndex;
		unsigned char unknown3A[0x54 - 0x3A];

		// The state the broad phase keeps in the head (at +0x3E): bit 0 - the object is asleep, bit 3 - the
		// object is left out of the queries and of the solver (name guess)
		bool IsAsleep() const
		{
			return (unknown3A[0x3E - 0x3A] & 1) != 0;
		}

		bool IsSkipped() const
		{
			return (unknown3A[0x3E - 0x3A] & 8) != 0;
		}
	};

	// ravenphysics::PhysicsObject (RTTI): a body made of collision objects
	class PhysicsObject : public BroadPhaseObject
	{
	public:
		// Recomputes boundsMin / boundsMax from the bounds of the volumes of the active collision objects and
		// writes them into the detector's box (0x106608A0)
		void UpdateBounds();
		// Clears the collision objects' changed flags and recomputes the bounds when one of them was set
		// (0x106612C0)
		void RefreshBounds(int unused);

		CollisionObject** objects;
		int unknown58;
		unsigned short objectCount;
	};
}

#endif
