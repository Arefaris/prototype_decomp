// math::Sphere: centre and radius (the engine names "math::Sphere" among its reflected types; member names guessed).
#ifndef MATH_SPHERE_H
#define MATH_SPHERE_H

#include "code/math/vector.h"

namespace math
{
	class AABB;

	class Sphere
	{
	public:
		Vector centre;
		float radius;

		void GetAABB(AABB& out) const;
		// direction = unit vector from the centre to p (up when p is the centre), distance = |p - centre| - radius
		void GetDirection(const Vector& p, Vector& direction, float& distance) const;
	};
}

#endif
