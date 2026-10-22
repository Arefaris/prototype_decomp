// math::Sphere: centre and radius (the engine names "math::Sphere" among its reflected types; member names guessed).
#ifndef MATH_SPHERE_H
#define MATH_SPHERE_H

#include "code/math/vector.h"

namespace content
{
	struct ClassInfo;
	struct MemberList;
}

namespace math
{
	class AABB;

	class Sphere
	{
	public:
		// The reflection of the type (another unit, 0x10847660 / 0x10847DD0)
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		Vector centre;
		float radius;

		void GetAABB(AABB& out) const;
		// Grows the sphere to contain p: the centre moves halfway along the excess toward p
		void AddPoint(const Vector& p);
		// Grows the sphere to contain other (or becomes other when that contains this one)
		void AddSphere(const Sphere& other);
		// direction = unit vector from the centre to p (up when p is the centre), distance = |p - centre| - radius
		void GetDirection(const Vector& p, Vector& direction, float& distance) const;
		// Ray from origin along the unit direction: t of the entry point (0 when origin is inside); false when the ray
		// misses or starts beyond the sphere
		bool IntersectRay(const Vector& origin, const Vector& direction, float& t) const;
		// The same, but t is the first hit at or after the origin (the exit point when origin is inside)
		bool IntersectRayFirst(const Vector& origin, const Vector& direction, float& t) const;
	};
}

#endif
