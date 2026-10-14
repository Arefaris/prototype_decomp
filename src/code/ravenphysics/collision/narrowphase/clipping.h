// Clipping of the edges of a convex polyhedron against a set of planes (unit around 0x106C0140 - 0x106C3150, the
// collide functions of the volume pairs; file and names are guesses).
#ifndef RAVENPHYSICS_COLLISION_NARROWPHASE_CLIPPING_H
#define RAVENPHYSICS_COLLISION_NARROWPHASE_CLIPPING_H

#include "code/math/matrix.h"

namespace ravenphysics
{
	// A corner of the polyhedron: its signed distance to the plane being clipped against and how many live edges
	// end in it
	struct ClipVertex
	{
		float x;
		float y;
		float z;
		float distance;
		int refCount;
	};

	// A clipping plane (the normal and offset, one more word)
	struct ClipPlane
	{
		float x;
		float y;
		float z;
		float d;
		unsigned char unknown10;
		unsigned char unknown11[3];
	};

	// An edge between two corners and the part of it still inside [tMin, tMax]
	struct ClipEdge
	{
		float tMin;
		float tMax;
		unsigned char first;
		unsigned char second;
		unsigned short unknown0A;
		float payload[6];
	};

	template<class T>
	struct ClipList
	{
		T* data;
		unsigned int count;
	};

	// The corners, edge pairs and planes of a convex volume's mesh (counts, then arrays: 3 floats per corner, 2 bytes
	// per edge, 4 floats per plane)
	struct ConvexMesh
	{
		unsigned char unknown0[0x26];
		unsigned short vertexCount;
		unsigned short edgeCount;
		unsigned short planeCount;
		const float* vertices;
		const unsigned char* edges;
		const float* planes;
	};

	// A convex mesh volume: the mesh and the transform of the volume
	struct ConvexVolume
	{
		unsigned char unknown0[0x24];
		ConvexMesh* mesh;
		math::Matrix transform;
	};

	// Puts the volume's corners and planes through its transform into clip lists and starts every edge on its whole
	// length (0x106C1320)
	void BuildClipLists(ConvexVolume* volume, ClipList<ClipVertex>* vertices, ClipList<ClipEdge>* edges,
		ClipList<ClipPlane>* planes);

	// Clips every edge against every plane: corners' distances are recomputed per plane, an edge keeps the part
	// inside and is removed (replaced by the last edge) when nothing is left (0x106C0140)
	void ClipEdges(ClipList<ClipEdge>* edges, ClipList<ClipVertex>* vertices, ClipList<ClipPlane>* planes);
}

#endif
