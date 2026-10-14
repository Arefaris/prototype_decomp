// proto::NavMeshHull: the two navigation-mesh tests. See navmesh.h for the model; names are guesses.
#include "code/math/worldbounds.h"
#include "code/proto/navmesh.h"

namespace proto
{
	NavMesh* gNavMesh;

	// FUNCTION: ENGINE 0x10568390
	float AreaHeight(void* record)
	{
		int index = *(int*)((char*)record + 0x20);
		return gAreaHeights[index];
	}

	// FUNCTION: ENGINE 0x105691D0
	// EQUIVALENT: same operations in the same order; the engine keeps the point in ebx, the index in ebp and the
	// cursor in edi, ours allocates the callee-saved registers the other way round
	bool NavMeshHull::Contains(const math::Vector& point, float below, float above)
	{
		NavEdge* edge = begin;
		int count = end - edge;
		float px = point.x;
		float pz = point.z;
		for (int i = 0; i < count; i++)
		{
			float ax = gNavMesh->vertices[edge[i].a * 3];
			float az = gNavMesh->vertices[edge[i].a * 3 + 2];
			float dx = gNavMesh->vertices[*edge[i].b * 3] - ax;
			float dz = az - gNavMesh->vertices[*edge[i].b * 3 + 2];
			if (dx * az + dz * ax < dx * pz + dz * px)
			{
				return false;
			}
		}
		if (above >= 0.0f && below >= 0.0f)
		{
			bool under = nz * point.z + ny * (point.y + above) + nx * point.x <= math::WORLD_MIN - offset;
			bool over = nz * point.z + ny * (point.y - below) + nx * point.x <= math::WORLD_MIN - offset;
			return under != over;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x10568F90
	// EQUIVALENT: same operations in the same order; the engine keeps the loop index in ebx and the cursor in edi,
	// ours has them the other way round
	bool NavMeshHull::HasOpenArea()
	{
		NavEdge* edge = begin;
		int count = end - edge;
		for (int i = 0; i < count; i++)
		{
			unsigned short area = edge[i].area;
			if (area != 0xffff)
			{
				char* record = gNavMesh->areas + area * 64;
				if (record != 0)
				{
					if (AreaHeight(record) > 0.0f)
					{
						if ((float)*(signed short*)(record + 0x36) > 0.0f)
						{
							return true;
						}
					}
				}
			}
		}
		return false;
	}
}
