// The GJK distance / intersection code (assert path code/ravenphysics/collision/narrowphase/src/gjk.cpp). Names and
// layout are guesses.
#ifndef RAVENPHYSICS_COLLISION_NARROWPHASE_GJK_H
#define RAVENPHYSICS_COLLISION_NARROWPHASE_GJK_H

#include "code/math/vector.h"

namespace ravenphysics
{
	// The ids of the support points of up to four simplex vertices
	struct GjkSimplex
	{
		// Appends a vertex of the given id and position to points unless the id is already in the simplex; returns
		// 1 when it was added (0x106736F0)
		int AddVertex(int id, math::Vector* points, math::Vector point);

		int ids[4];
		int count;
	};

	struct GjkVolume;

	// Finds the point of a volume farthest along a direction: the point and its id are the results; hint is the id
	// of a good start (0 for none)
	typedef void (*GjkSupportFunction)(GjkVolume* volume, const math::Vector* direction, int hint, int* id,
		math::Vector* point);

	// A convex volume as the GJK sees it: its support functions and a function that prints it
	struct GjkVolume
	{
		unsigned char unknown0[0x44];
		GjkSupportFunction support;
		GjkSupportFunction supportFrom;
		int unknown4C;
		void (*dump)(GjkVolume* volume);
	};

	// The state of one GJK run (0xB0 bytes): the simplex of each volume with the support points, the closest
	// points found and the separating direction
	struct GjkState
	{
		// Copies (0x10673490 / 0x10673590)
		GjkState(const GjkState& other);
		void operator=(const GjkState& other);
		// Moves the simplexes towards the closest point to the origin of their difference, lands the direction to
		// it in direction and returns the squared distance, 0 when they touch (0x10673750)
		float Solve(math::Vector* direction);
		// Prints the simplexes and their points (0x10673310)
		void Dump();

		math::Vector pointsA[4];
		math::Vector pointsB[4];
		math::Vector closestA;
		math::Vector closestB;
		math::Vector normal;
		GjkSimplex simplexA;
		GjkSimplex simplexB;
		int unknownAC;
	};

	// The distance between two convex volumes along the search direction start (0x10677180)
	float GjkDistance(GjkState* state, GjkVolume* volumeA, GjkVolume* volumeB, const math::Vector* start);
}

#endif
