// math::Segment: two end points. The distance and closest-point functions of segment.cpp (0x107D6F90-0x107D7650)
// are not reconstructed yet (docs/math_worklist.md); the name is a guess.
#ifndef MATH_SEGMENT_H
#define MATH_SEGMENT_H

#include "code/math/vector.h"

namespace math
{
	class AABB;
	class Sphere;

	class Segment
	{
	public:
		Vector start;
		Vector end;

		Segment()
		{
		}
		// Kept out of line by the compiler in large callers (0x100F6A60)
		Segment(const Vector& a, const Vector& b) : start(a), end(b)
		{
		}

		// Component-wise min and max of the two end points
		void GetAABB(AABB& out) const;
		// Sphere around the midpoint with radius |start - end| (name guess)
		void GetSphere(Sphere& out) const;
		// Projection parameter of p: (p - start) . (end - start) / |end - start|^2 (name guess)
		float Parameter(const Vector& p) const;
		// Squared distance from a point / between two segments
		float DistanceSquared(const Vector& point) const;
		float DistanceSquared(const Segment& other) const;
		// The closest points p (on this segment) and q (on other); returns their squared distance (name guess)
		float ClosestPoints(const Segment& other, Vector& p, Vector& q) const;
		// Squared distance from p to the infinite line through the segment (name guess)
		float DistanceSquaredToLine(const Vector& p) const;
		// The point of the infinite line closest to p into out; returns the squared distance (name guess)
		float ClosestPointOnLine(const Vector& p, Vector& out) const;
		// Squared distance between the infinite lines through this segment and other (parallel lines: the distance
		// of other.start to this line) (name guess)
		float LineDistanceSquared(const Segment& other) const;
		// Squared distance from p given t = (p - start) . (end - start) and lengthSquared = |end - start|^2: to start
		// when t <= 1e-10, to end when t >= lengthSquared, else to the line (name guess)
		float DistanceSquared(const Vector& p, float t, float lengthSquared) const;
		// The point of the segment closest to p into out; returns the squared distance (name guess)
		float ClosestPoint(const Vector& p, Vector& out) const;
		// The same with t and lengthSquared precomputed as for DistanceSquared(p, t, lengthSquared) (name guess)
		float ClosestPoint(const Vector& p, float t, float lengthSquared, Vector& out) const;
	};
}

#endif
