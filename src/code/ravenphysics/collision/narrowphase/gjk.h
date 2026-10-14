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
		// Appends a vertex of the given id and position to points unless the id is already in the simplex
		// (0x106736F0)
		int AddVertex(int id, math::Vector* points, float x, float y, float z);

		int ids[4];
		int count;
	};
}

#endif
