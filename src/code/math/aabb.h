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
	class AABB
	{
	public:
		// The reflection of the type (another unit, 0x10847620 / 0x10847970)
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		Vector min;
		Vector max;
	};
}

#endif
