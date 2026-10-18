// ravenphysics::PhysicsObject and the lock the library sets while it simulates (assert path
// code/ravenphysics/src/physicsobject.cpp). Only the members the reconstructed code touches are named; the layout is
// partial and every name is a guess except the class names the RTTI gives.
#ifndef RAVENPHYSICS_PHYSICSOBJECT_H
#define RAVENPHYSICS_PHYSICSOBJECT_H

#include "code/content/loadinventory.h"
#include "code/math/matrix.h"
#include "code/math/vector.h"
#include "code/pure3d/pose.h"
#include "code/ravenphysics/broadphase/broadphasedetector.h"
#include "code/ravenphysics/collision/collisionobject.h"
#include "code/ravenphysics/context.h"

namespace math
{
	class Matrix;
	class OBB;
}

namespace ravenphysics
{
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
		// Starts as an object in no detector (0x1065F5B0, another unit)
		BroadPhaseObject();
		// Puts the base's vftable back (0x1065F530, another unit)
		~BroadPhaseObject();

		// The two slots the bodies fill in (0x1065FF70 / 0x1065F9D0 in PhysicsObject)
		virtual int GetUnknown48() = 0;
		virtual bool HasVolumeType(unsigned short type) = 0;

		BroadPhaseBox bounds;            // 0x08
		int id;                          // 0x20 (the handle the body is registered under)
		unsigned char unknown24[4];
		// What the object collides with, kept in the detector next to its box (0x28)
		BroadPhaseMasks masks;
		BroadPhaseDetector* detector;
		unsigned short detectorIndex;
		// 0x106561E0
		unsigned short GetDetectorIndex() const;
		unsigned char unknown3A[2];
		// How the body's collision objects collide (0x1065F6D0 sets the low two bits; 0x3C)
		unsigned short collisionMode;
		// 0x3E: the broad phase's state bits
		unsigned char asleep : 1;
		unsigned char unknown3E1 : 1;
		unsigned char unknown3E2 : 1;
		unsigned char skipped : 1;
		unsigned char unknown3E4 : 4;
		unsigned char unknown3F;

		// The broad phase's state: asleep, and left out of the queries and of the solver (name guess)
		bool IsAsleep() const
		{
			return asleep;
		}

		bool IsSkipped() const
		{
			return skipped;
		}

		// Whether the low two bits of collisionMode are clear (name guess; the wake path passes this on to
		// RefreshBounds)
		bool IsUnflagged() const
		{
			return (collisionMode & 3) == 0;
		}

		// Sets or clears the low three bits of collisionMode (0x1065F540; name guess)
		void SetState(unsigned char mask, bool set);

		// Takes the filter and tells the detector (name guess)
		void SetMasks(const BroadPhaseMasks& newMasks)
		{
			masks.unknown0 = newMasks.unknown0;
			masks.unknown4 = newMasks.unknown4;
			masks.unknown8 = newMasks.unknown8;
			if (detector != 0)
			{
				detector->masks[detectorIndex] = newMasks;
			}
		}

		// Copies the filter into the detector's entry of the object
		void StoreMasks()
		{
			if (detector != 0)
			{
				BroadPhaseMasks* entry = detector->masks + detectorIndex;
				entry->unknown0 = masks.unknown0;
				entry->unknown4 = masks.unknown4;
				entry->unknown8 = masks.unknown8;
			}
		}
	};

	// One of the body's joints (class and slot names are guesses; the engine deletes them through slot 3 and
	// updates them through slot 6)
	class PhysicsJoint
	{
	public:
		virtual void Slot0() = 0;
		virtual void Slot1() = 0;
		virtual void Slot2() = 0;
		virtual ~PhysicsJoint() = 0;
		virtual void Slot4() = 0;
		virtual void Slot5() = 0;
		virtual void Update(const void* argument) = 0;

		// Hands a query on to the joint (0x1065CDE0, another unit; name guess)
		void SetQuery(const void* query);
	};

	class PhysicsObject;

	// The joints a link makes (12 bytes per joint; class and members are guesses)
	struct JointDefinition
	{
		int unknown0;
		int unknown4;
		int unknown8;
	};

	class JointSet
	{
	public:
		virtual void AddRef() = 0;
		virtual void Release() = 0;

		// How many joints the set holds (0x106A5F90, another unit)
		int Count();
		// A joint for each definition, in a new array (0x106A6910, another unit)
		PhysicsJoint** CreateJoints(PhysicsObject* body);

		int unknown4;
		JointDefinition* begin;    // 0x08
		JointDefinition* end;      // 0x0C
	};

	// What a body is linked to: the objects it is made of are tied to a skeleton (name and layout are guesses)
	struct PhysicsLink
	{
		// Frees the arrays and releases the joint set (0x10660FF0)
		~PhysicsLink();
		// Drops a reference and frees the link with the last one (0x106613F0)
		void Release();
		// Takes a reference (0x1065FCD0)
		void AddRef();
		// An empty link (0x1065FCB0)
		PhysicsLink();

		unsigned short refCount;          // 0x00
		unsigned short skeletonJointCount;  // 0x02 (the joints of the skeleton the objects follow)
		unsigned short* jointOfObject;    // 0x04 (the skeleton joint each object follows)
		unsigned short* objectOfJoint;    // 0x08 (the object that drives each joint, 0xFFFF for none)
		unsigned char* pairMask;          // 0x0C (one bit per pair of objects)
		JointSet* joints;                 // 0x10
	};

	// A function that does nothing (0x1065FCE0; name guess)
	void DoNothing();

	// A bit of a bit set (0x1065FB20) and the number of pairs of n objects (0x1065FB50)
	void SetBit(unsigned char* bits, unsigned int index, bool value);
	unsigned int CountPairs(int n);
	// The bit of the pair of two objects, among count objects (0x1065FC30)
	int GetPairIndex(int count, unsigned int first, unsigned int second);
	// Does the work for one pair of a body's collision objects, whose bit in the body's pair mask is set
	// (0x106A5590, another unit; name guess)
	void ProcessObjectPair(PhysicsObject* body, CollisionObject* first, CollisionObject* second, int a, int b, int c,
		int d);

	// ravenphysics::PhysicsObject (RTTI): a body made of collision objects
	class PhysicsObject : public BroadPhaseObject
	{
	public:
		// Builds a body of its own around one collision object (0x10661040; name guess)
		static PhysicsObject* Create(CollisionObject* object);
		// Builds a body around the collision objects of an array and a link (0x10661170; name guess)
		static PhysicsObject* Create(CollisionObject** objects, unsigned int count, PhysicsLink* link);

		// Registers the body in the handle table (0x1065FF00)
		PhysicsObject();
		// Takes the body out of the handle table and frees its joints and collision objects (0x10661420)
		~PhysicsObject();

		// The slots 5 and 6 of the vftable
		virtual int GetUnknown48();
		virtual bool HasVolumeType(unsigned short type);

		// Prints the bounds and the collision objects (0x1065F880, another unit; name guess)
		void Print();
		// Prints the body when a volume sticks out of its bounds (0x1065F8C0; name guess)
		void CheckBounds();
		// Sets the word the first virtual function returns (0x1065F9B0)
		void SetUnknown48(int value);
		// Takes the bytes as the link's pair mask (0x1065FA10; name guess)
		void SetPairMask(const unsigned char* mask, unsigned int size);
		// Hands a query on to every joint (0x1065FA50; name guess)
		void NotifyJoints(const void* argument);
		// Sets the collision mode to 1 (0x1065F9C0; name guess)
		void SetCollisionModeOne();
		// Gives every collision object a material (0x1065FAA0)
		void SetMaterial(unsigned char material);
		// Calls the pair callback for every pair of objects whose bit is set (0x1065FB60; name guess)
		void ForEachPair(int a, int b, int c, int d);
		// How many of the collision objects are active (0x1065FC80; name guess)
		int GetActiveCount();
		// Sets the box of the body in its detector (0x1065FDF0; name guess)
		void SetBounds(const BroadPhaseBox* box);
		// Sets the first two words of the filter (0x1065FE90; name guess)
		void SetFilterWords(const int* words);
		// The name the body is kept under (0x1065FF80)
		void SetName(core::Name<core::CaseSensitiveKey> newName);
		// Adds the objects' two filters up again and stores them in the detector (0x1065FF90; name guess)
		void UpdateFilters();
		// Sets the filter of every volume and of the body to the values (0x10660050; name guess)
		void SetFilter(const BroadPhaseMasks* masks);
		// The same for the volumes of one collision object (0x10660150; name guess)
		void SetObjectFilter(int object, const CollisionFilter* filter);
		// The same for one volume (0x106601E0; name guess)
		void SetVolumeFilter(int object, int volume, const CollisionFilter* filter);
		// Sets or clears the bits of the first filter word on every volume (0x10660260; name guess)
		void SetFilterBits(unsigned int mask, bool set);
		// The same for the volumes of one collision object (0x10660360; name guess)
		void SetObjectFilterBits(int object, unsigned int mask, bool set);
		// The same for one volume (0x10660410; name guess)
		void SetVolumeFilterBits(int object, int volume, unsigned int mask, bool set);
		// The same for the second filter word (0x106604A0 / 0x106605A0 / 0x10660650; name guesses)
		void SetFilterBits2(unsigned int mask, bool set);
		void SetObjectFilterBits2(int object, unsigned int mask, bool set);
		void SetVolumeFilterBits2(int object, int volume, unsigned int mask, bool set);
		// A copy of the body with copies of its objects (0x106606E0)
		PhysicsObject* Clone();
		// Turns the bit of one pair of objects in the link's pair mask on or off (0x10660F50; name guess)
		void SetPairEnabled(unsigned int pair, bool enabled);
		// Hands a query to every collision object and every joint and refreshes the bounds (0x10661350; name
		// guess)
		void SetVolumeQuery(const void* query);
		// Takes a reference to a joint set for the link, if one is given (0x10660880; name guess)
		void SetJointSet(JointSet* set);
		// The pair of values the joint set holds for one joint (0x10660FC0; name guess)
		void GetJointPair(int index, int* first, int* second);
		// Recomputes boundsMin / boundsMax from the bounds of the volumes of the active collision objects and
		// writes them into the detector's box (0x106608A0)
		void UpdateBounds();
		// Moves every collision object by a matrix and then the body's bounds (0x106609F0; name guess)
		void TransformBy(const math::Matrix& matrix);
		// Updates the transform of one collision object, or of all with -1, and the bounds (0x10660A90; name guess)
		void UpdateTransform(const math::Matrix& matrix, int index);
		// Switches one collision object on or off and tells the detector (0x10660B30; name guess)
		void SetObjectActive(int index, bool active);
		// Sets the transforms of the collision objects to the world matrices of the joints they follow, optionally
		// moved by a matrix (0x10660BB0; name guess)
		void ReadPose(const pure3d::Pose* pose, const math::Matrix* offset);
		// Writes the transforms of the collision objects into the world matrices of the pose, the joints without an
		// object from their local matrices (0x10660D70; name guess)
		void WritePose(pure3d::Pose* pose, const math::Matrix* offset);
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

		core::Name<core::CaseSensitiveKey> name;   // 0x40
		int unknown48;
		float unknown4C;
		unsigned int unknown50;
		CollisionObject** objects;       // 0x54
		PhysicsJoint** joints;           // 0x58
		unsigned short objectCount;      // 0x5C
		unsigned short jointCount;       // 0x5E
		PhysicsLink* link;               // 0x60
		int unknown64;

		// Whether the body takes part in the self collisions (0x10656320)
		bool IsLinked() const
		{
			return link != 0 && link->pairMask != 0 && !(unknown50 & 1);
		}
	};

	// The physics object of a collision volume (0x10661140)
	PhysicsObject* CreatePhysicsObject(CollisionVolume* volume, bool flag, float size);
}

#endif
