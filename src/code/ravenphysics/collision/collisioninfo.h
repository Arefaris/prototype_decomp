// The record of one colliding pair (two collision objects, optionally with a triangle of a mesh on the second side).
// Names and layout are guesses; only the members the reconstructed code touches are named.
#ifndef RAVENPHYSICS_COLLISION_COLLISIONINFO_H
#define RAVENPHYSICS_COLLISION_COLLISIONINFO_H

#include "code/ravenphysics/collision/collisionobject.h"

namespace ravenphysics
{
	// A face of a mesh volume (8 bytes); the flags carry the material
	struct MeshFace
	{
		unsigned char unknown0[6];
		unsigned short flags;
	};

	struct CollisionMesh
	{
		unsigned char unknown0[200];
		MeshFace* faces;
	};

	struct Contact;
	struct PairDetails;

	class CollisionInfo
	{
	public:
		// Builds the record of one contact between the two sides of a pair (0x106A4030)
		void Init(const Contact* contact, const PairDetails* details);
		// The face of the mesh that the second side hit (0x10668C60)
		MeshFace* GetFace();
		// The material of the volume (or mesh face) of one side, 0 when that side has no object (0x10668D10)
		unsigned char GetMaterial(int side);

		unsigned char unknown0[0x18];
		CollisionObject* objects[2];
		int unknown20;
		CollisionMesh* mesh;
		unsigned short volumeIndices[2];
		unsigned char unknown2C[0x68 - 0x2C];
		unsigned short faceIndex;
		unsigned char unknown6A[0x70 - 0x6a];
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
