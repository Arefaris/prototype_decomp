// The record of one colliding pair (two collision objects, optionally with a triangle of a mesh on the second side).
// Names and layout are guesses; only the members the reconstructed code touches are named.
#ifndef RAVENPHYSICS_COLLISION_COLLISIONINFO_H
#define RAVENPHYSICS_COLLISION_COLLISIONINFO_H

#include "code/ravenphysics/collision/collisionobject.h"
#include "code/ravenphysics/context.h"

namespace ravenphysics
{
	class BroadPhaseObject;
	struct Contact;
	struct IntersectionProperties;
	struct MeshFaceRef;
	struct PairDetails;

	// What a collision test found out about one contact (0x30 bytes): the point on each side, the normal, the depth
	// and the triangle of the mesh the second side hit (0xFFFF for none)
	struct ContactRecord
	{
		// Moves the points through the matrix and turns the normal (0x106A8090, another unit)
		void Transform(const math::Matrix& matrix);

		math::Vector points[2];       // 0x00
		math::Vector normal;          // 0x18
		float depth;                  // 0x24
		unsigned short faceIndex;     // 0x28
		unsigned char unknown2A[6];
	};

	class CollisionInfo
	{
	public:
		// Builds the record of one contact between the two sides of a pair (0x106A4030)
		void Init(const Contact* contact, const PairDetails* details);
		// The triangle of the mesh that the second side hit (0x10668C60)
		GridFace* GetFace();
		// The material of the volume (or mesh face) of one side, 0 when that side has no object (0x10668D10)
		unsigned char GetMaterial(int side);
		// The volume of one side (0x10668A70)
		CollisionVolume* GetVolume(int side);
		// Whether the other record is the deeper one (0x10668A80)
		bool IsDeeperThan(const CollisionInfo* other) const;
		// Which side a body is: 0 when it is the first, 1 when it is the second, -1 when it is neither (0x10668AA0);
		// 1, 0 and -1 the other way round (0x10668AE0); both at once, -1 and -1 for neither (0x10668B20)
		int GetSide(int bodyId);
		int GetOtherSide(int bodyId);
		void GetSides(int bodyId, int* side, int* other);
		// Moves the contact through the matrix (0x10668B90)
		void Transform(const math::Matrix& matrix);
		// Sets the body (0x10668BA0) and the collision object (0x10668BD0) of one side
		void SetBody(int side, BroadPhaseObject* body);
		void SetObject(int side, CollisionObject* object);
		// The filter words of the volume (or mesh material, or body) of one side (0x10668C00)
		IntersectionProperties* GetFilter(int side);
		// The triangle of the mesh that the second side hit, as a reference (0x10668C80)
		void GetFaceRef(MeshFaceRef* ref);
		// The velocity of the contact point on one side, zero when the body does not simulate (0x10668CA0)
		void GetVelocity(int side, math::Vector* velocity);

		ObjectHandle bodyHandles[2];        // 0x00
		unsigned int objectHandles[2];      // 0x08
		BroadPhaseObject* bodies[2];        // 0x10
		CollisionObject* objects[2];        // 0x18
		CollisionVolume* volumes[2];        // 0x20 (the second is a mesh when the contact has a triangle)
		unsigned short volumeIndices[2];    // 0x28
		unsigned char unknown2C[0x40 - 0x2C];
		ContactRecord contact;              // 0x40
	};

	// The collision records of a pair test (records of 0x70 bytes, count taken so far)
	struct CollisionInfoList
	{
		CollisionInfo* infos;
		unsigned int count;
		unsigned int capacity;
	};
}

#endif
