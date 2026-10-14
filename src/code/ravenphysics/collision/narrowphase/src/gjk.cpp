#include "code/ravenphysics/collision/narrowphase/gjk.h"

namespace ravenphysics
{
	// FUNCTION: ENGINE 0x106736F0
	int GjkSimplex::AddVertex(int id, math::Vector* points, float x, float y, float z)
	{
		for (int i = 0; i < count; i++)
		{
			if (ids[i] == id)
			{
				return 0;
			}
		}
		ids[count] = id;
		math::Vector* point = points + count;
		point->x = x;
		point->y = y;
		point->z = z;
		count++;
		return 1;
	}
}
