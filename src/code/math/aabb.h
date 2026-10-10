// math::AABB: an axis-aligned box, the engine's own name ("math::AABB" is a reflected type). Layout from the Plane
// tests: minimum corner, then maximum corner (member names guessed).
#ifndef MATH_AABB_H
#define MATH_AABB_H

#include "code/math/vector.h"

namespace math
{
	class AABB
	{
	public:
		Vector min;
		Vector max;
	};
}

#endif
