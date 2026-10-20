// math::OBB: an oriented box, the engine's own name ("math::OBB" is a reflected type). Layout from the transform
// functions: centre, three axes, then extents (member names guessed).
#ifndef MATH_OBB_H
#define MATH_OBB_H

#include "code/math/vector.h"

namespace math
{
	class AABB;
	class Matrix;

	class OBB
	{
	public:
		Vector centre;
		Vector axis[3];
		Vector extents;

		// Component-wise copy (0x100F7120, a kept out-of-line copy)
		OBB& operator=(const OBB& other);

		// Moves the box through m: the centre as a point, the axes as directions; extents unchanged
		void Transform(const Matrix& m);
		// The same from src into this box
		void Transform(const Matrix& m, const OBB& src);
		// The box around the corners (0x107D4450)
		void GetAABB(AABB& out) const;
		// True when p is inside the box (|(p - centre) . axis[i]| <= extents[i] for all three axes)
		bool Contains(const Vector& p) const;
		// Unit direction from the nearest point of the box surface to p and the distance to it (negative inside,
		// direction pointing inwards then); names guessed after Sphere::GetDirection
		void GetDirection(const Vector& p, Vector& direction, float& distance) const;
		// The offset of a corner from the centre: bit 0 negates the extent along axis[2], bit 1 along axis[1],
		// bit 2 along axis[0] (names guessed)
		void GetCornerOffset(Vector& out, unsigned char bits) const;
		// centre + GetCornerOffset(bits)
		void GetCorner(Vector& out, unsigned char bits) const;
	};
}

#endif
