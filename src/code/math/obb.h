// math::OBB: an oriented box, the engine's own name ("math::OBB" is a reflected type). Layout from the transform
// functions: centre, three axes, then extents (member names guessed).
#ifndef MATH_OBB_H
#define MATH_OBB_H

#include "code/math/vector.h"

namespace math
{
	class Matrix;

	class OBB
	{
	public:
		Vector centre;
		Vector axis[3];
		Vector extents;

		// Moves the box through m: the centre as a point, the axes as directions; extents unchanged
		void Transform(const Matrix& m);
		// The same from src into this box
		void Transform(const Matrix& m, const OBB& src);
	};
}

#endif
