// math::Capsule: a segment given by centre, unit direction and half length, with a radius. Layout from the
// transform and bounding functions; the class and member names are guesses.
#ifndef MATH_CAPSULE_H
#define MATH_CAPSULE_H

#include "code/math/vector.h"

namespace math
{
	class AABB;
	class Matrix;
	class Segment;

	class Capsule
	{
	public:
		Vector centre;
		float halfLength;
		Vector direction;
		float radius;

		// Moves the capsule through m: the centre as a point, the direction as a direction
		void Transform(const Matrix& m);
		// The same from src into this capsule
		void Transform(const Matrix& m, const Capsule& src);
		// The axis from centre - direction * halfLength to centre + direction * halfLength
		void GetSegment(Segment& out) const;
		// The axis' box grown by the radius
		void GetAABB(AABB& out) const;
		// True when p lies strictly within the radius of the axis segment (name guess)
		bool Contains(const Vector& p) const;
	};

	// A capped cylinder: centre, unit axis direction, half length along the axis and radius (layout from the
	// functions after Capsule's in capsule.cpp; class and member names are guesses)
	class Cylinder
	{
	public:
		Vector centre;
		Vector direction;
		float halfLength;
		float radius;

		// Moves the cylinder through m: the centre as a point, the direction as a direction
		void Transform(const Matrix& m);
		// The box around the cylinder (axis extent plus the end discs)
		void GetAABB(AABB& out) const;
		// True when p lies within the half length along the axis and strictly within the radius of it
		// Unit direction from the nearest point of the surface (side wall or cap) to p and the signed distance to it
		// (negative inside, direction then pointing out through the nearest face); name guessed after Sphere's
		void GetDirection(const Vector& p, Vector& out, float& distance) const;
		bool Contains(const Vector& p) const;
	};
}

#endif
