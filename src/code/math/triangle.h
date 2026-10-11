// math::Triangle: three corners (the layout the closest-point and containment tests read; the class name is the
// engine's, from the assert path of triangle.cpp; member and method names are guesses).
#ifndef MATH_TRIANGLE_H
#define MATH_TRIANGLE_H

#include "code/math/vector.h"

namespace math
{
	class Triangle
	{
	public:
		Vector a;
		Vector b;
		Vector c;

		// Closest point of the triangle to p (Ericson's region test); returns a region code: 1 / 2 / 4 for the edges
		// ab / bc / ca, 5 / 3 / 6 for the corners a / b / c (the union of their edges), 0 for the interior
		// (0x107D3420, not reconstructed yet)
		int ClosestPoint(const Vector& p, Vector& out) const;
		// Ray test (Moller-Trumbore, both windings): true and t (in units of direction) when origin + t direction
		// crosses the triangle; |det| <= EPSILON_SMALL counts as parallel (0x107D2ED0, NONMATCHING)
		bool IntersectRay(const Vector& origin, const Vector& direction, float& t) const;
		// True when p (assumed in the triangle's plane) lies inside the triangle (barycentric coordinates, sign bits)
		bool Contains(const Vector& p) const;
		// The smallest of the three corner angles (acos of the largest |cos| between the edges), 0 when degenerate
		float SmallestAngle() const;
		// True when p's (x, z) lies inside or on the triangle's projection onto the XZ plane (counter-clockwise order)
		bool ContainsXZ(const Vector& p) const;
	};

	// Area of the triangle a, b, c: half the length of (a - b) x (b - c) (name guess)
	float Area(const Vector& a, const Vector& b, const Vector& c);
}

#endif
