#include "code/math/aabb.h"
#include "code/math/segment.h"

namespace math
{
	// FUNCTION: ENGINE 0x107D6F40
	void Segment::GetAABB(AABB& out) const
	{
		for (int i = 3; i--; )
		{
			if ((&end.x)[i] > (&start.x)[i])
			{
				(&out.min.x)[i] = (&start.x)[i];
				(&out.max.x)[i] = (&end.x)[i];
			}
			else
			{
				(&out.max.x)[i] = (&start.x)[i];
				(&out.min.x)[i] = (&end.x)[i];
			}
		}
	}
}
