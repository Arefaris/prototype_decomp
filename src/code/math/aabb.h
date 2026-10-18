// math::AABB: an axis-aligned box, the engine's own name ("math::AABB" is a reflected type). Layout from the Plane
// tests: minimum corner, then maximum corner (member names guessed).
#ifndef MATH_AABB_H
#define MATH_AABB_H

#include "code/math/vector.h"

namespace content
{
	struct ClassInfo;
	struct MemberList;
}

namespace math
{
	class Matrix;
	class Sphere;

	class AABB
	{
	public:
		// The reflection of the type (another unit, 0x10847620 / 0x10847970)
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// A box whose minimum lies above its maximum on some axis is empty
		bool IsEmpty() const
		{
			return min.x > max.x || min.y > max.y || min.z > max.z;
		}
		// The middle of the box: the corners added and halved (inline in the engine's callers; the sums keep the order
		// Vector::Add gives them, which a hand-written (min + max) * 0.5 does not)
		void GetCentre(Vector* centre) const
		{
			centre->Add(min, max);
			centre->Scale(0.5f);
		}
		// The empty box that any point enlarges (+-1e12)
		void Reset()
		{
			min.x = 1e12f;
			min.y = 1e12f;
			min.z = 1e12f;
			max.x = -1e12f;
			max.y = -1e12f;
			max.z = -1e12f;
		}
		// 0x100D5AC0 (another unit's copy): the sphere through the corners, zero for an invalid box
		Sphere GetSphere() const;
		// 0x100A2660 (another unit's copy): the box around box transformed by m
		void SetTransformed(const Matrix& m, const AABB& box);
		// 0x102CBD60: widens every axis on which the box is (nearly) flat
		void Inflate();

		Vector min;
		Vector max;
	};
}

#endif
