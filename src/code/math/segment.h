// math::Segment: two end points. The distance and closest-point functions of segment.cpp (0x107D6F90-0x107D7650)
// are not reconstructed yet (docs/math_worklist.md); the name is a guess.
#ifndef MATH_SEGMENT_H
#define MATH_SEGMENT_H

#include "code/math/vector.h"

namespace math
{
	class AABB;

	class Segment
	{
	public:
		Vector start;
		Vector end;

		// Component-wise min and max of the two end points
		void GetAABB(AABB& out) const;
	};
}

#endif
