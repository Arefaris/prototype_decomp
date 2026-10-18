// ravenphysics::PhysicsObject and the lock the library sets while it simulates (assert path
// code/ravenphysics/src/physicsobject.cpp). Only the members the reconstructed code touches are named; the layout is
// partial and every name is a guess except the class names the RTTI gives.
#ifndef RAVENPHYSICS_PHYSICSOBJECT_H
#define RAVENPHYSICS_PHYSICSOBJECT_H

#include "code/content/loadinventory.h"
#include "code/math/vector.h"
#include "code/ravenphysics/broadphase/broadphasedetector.h"

namespace math
{
	class Matrix;
	class OBB;
}

namespace ravenphysics
{
	class CollisionObject;
	struct IntersectionFilter;

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
		// 0x106561E0
		unsigned short GetDetectorIndex() const;
		unsigned char unknown3A[2];
		// How the body's collision objects collide (0x1065F6D0 sets the low two bits; 0x3C)
		unsigned short collisionMode;
		// 0x3E: the broad phase's state bits (the engine tests them as a byte)
		unsigned char collisionFlags;
		unsigned char unknown3F;
		unsigned char unknown40[0x50 - 0x40];
		unsigned int unknown50;

		// The broad phase's state in collisionFlags: bit 0 - the object is asleep, bit 3 - the object is left out
		// of the queries and of the solver (name guess)
		bool IsAsleep() const
		{
			return (collisionFlags & 1) != 0;
		}

		bool IsSkipped() const
		{
			return (collisionFlags & 8) != 0;
		}

		// Whether the low two bits of collisionMode are clear (name guess; the wake path passes this on to
		// RefreshBounds)
		bool IsUnflagged() const
		{
			return (collisionMode & 3) == 0;
		}

		// Sets or clears the low three bits of collisionMode (0x1065F540; name guess)
		void SetState(unsigned char mask, bool set);
	};

	// What a body is linked to (name and layout are guesses)
	struct PhysicsLink
	{
		unsigned char unknown0[0xC];
		int member;
	};

	// ravenphysics::PhysicsObject (RTTI): a body made of collision objects
	class PhysicsObject : public BroadPhaseObject
	{
	public:
		// Recomputes boundsMin / boundsMax from the bounds of the volumes of the active collision objects and
		// writes them into the detector's box (0x106608A0)
		void UpdateBounds();
		// Clears the collision objects' changed flags and recomputes the bounds when one of them was set
		// (0x106612C0). The parameter is one byte, not a word: the wake path calls it with the result of a
		// comparison, which the engine passes on without widening (`sete al` then a bare `push eax`).
		void RefreshBounds(bool unused);
		// Sets the low two bits of collisionMode and tells the detector (0x1065F6D0, another unit)
		void SetCollisionMode(unsigned short mode);
		// 0x10678250: sets what the object is tested against (the three words go to +0x28)
		void SetFilter(const IntersectionFilter* filter);
		// 0x106780A0: gives the object's first volume the box (placed by the matrix), copies the volume's bounds into
		// the object and its detector box and sets the collision mode to 2 (name guess)
		void SetBox(const math::OBB& box, const math::Matrix& transform);
		// 0x10677F90: the same for the volume it has (placed by the matrix; name guess)
		void SetTransform(const math::Matrix& transform);

		CollisionObject** objects;
		int unknown58;
		unsigned short objectCount;
		unsigned char unknown5E[2];
		PhysicsLink* link;     // 0x60

		// Whether the body takes part in the self collisions (0x10656320)
		bool IsLinked() const
		{
			return link != 0 && link->member != 0 && !(unknown50 & 1);
		}
	};
}

#endif
