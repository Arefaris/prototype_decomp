// math::Plane: a unit normal and the distance term d, so that normal . p + d = 0 on the plane. The engine names
// "math::Plane" (reflected type); member and method names are guesses until the binary confirms them.
#ifndef MATH_PLANE_H
#define MATH_PLANE_H

#include "code/math/vector.h"

namespace math
{
	class AABB;
	class Matrix;

	class Plane
	{
	public:
		Vector normal;
		float d;

		// The plane through a, b and c: normal = (b - a) x (c - a) normalised, d = -(normal . a)
		void Set(const Vector& a, const Vector& b, const Vector& c);
		// Nonzero when the box corner nearest to the plane's back side is on or behind the plane (the box is not
		// entirely in front)
		int IsBoxPartlyBehind(const AABB& box) const;
		// Nonzero when the box corner farthest to the front is on or behind the plane (the box is entirely behind)
		int IsBoxBehind(const AABB& box) const;
		// True when the segment a-b crosses the plane; t is the fraction from a to the crossing. False when both
		// ends are on the same side or the signed distances differ by at most EPSILON_SMALL
		bool IntersectSegment(const Vector& a, const Vector& b, float* t) const;
		// True when the ray from origin along direction (not necessarily unit) hits the plane in front of the
		// origin; hit is the point. False for a ray (nearly) parallel to the plane
		bool IntersectRay(const Vector& origin, const Vector& direction, Vector* hit) const;
		// This plane = p moved through m: the normal rotated, d from the point -p.d * normal + m's translation
		void Transform(const Matrix& m, const Plane& p);
	};
}

#endif
