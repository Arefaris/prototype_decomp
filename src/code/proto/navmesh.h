// The navigation mesh of the traffic system (global 0x112730C0; the class proto::AmbientNavMesh is the RTTI name).
// The mesh keeps a vertex array (+8) and 64-byte runtime area records (+0x38); a hull is a list of 28-byte edges
// between those vertices plus the plane that bounds the area. The two tests here are proto::NavMeshHull (name guessed;
// no assert path names this unit, 0x10568F90 - 0x105691D0). Member names are guesses.
#ifndef PROTO_NAVMESH_H
#define PROTO_NAVMESH_H

#include "code/math/vector.h"

namespace proto
{
	class NavMeshHull;

	// The mesh itself; only the vertex and area arrays are known
	class NavMesh
	{
	public:
		unsigned char unknown0[8];
		float* vertices;
		unsigned char unknownC[0x38 - 0xc];
		char* areas;
	};

	extern NavMesh* gNavMesh;

	// One edge of a hull (28 bytes): a vertex index, an area index and a pointer to the other vertex index
	struct NavEdge
	{
		unsigned short a;
		unsigned short unknown2;
		unsigned short area;
		unsigned short unknown6;
		unsigned short* b;
		unsigned char unknownC[0x10];
	};

	// The ground heights the area records index (0x10E24714; name guessed)
	extern float gAreaHeights[];

	// The ground height of an area record (0x10568390; another function of this unit)
	float AreaHeight(void* record);

	// A convex hull of the mesh: its edges and the plane that bounds the area
	class NavMeshHull
	{
	public:
		// 0x105691D0: true when the point lies on the inner side of every edge (the hull is a polygon in the XZ
		// plane) and, when both margins are non-negative, the vertical segment around it lies under the plane
		bool Contains(const math::Vector& point, float below, float above);
		// 0x10568F90: true when one of the hull's areas has a positive ground height and a positive word at +0x36
		bool HasOpenArea();

		NavEdge* begin;
		NavEdge* end;
		int unknown8;
		int unknownC;
		float nx;
		float ny;
		float nz;
		float offset;
	};
}

#endif
