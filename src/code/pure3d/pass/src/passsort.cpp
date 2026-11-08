// The sorting of the parts a pass draws by their distance from the eye (unit 0x10754780 - 0x10756300, the file name is
// a guess). Names are guesses.
#include <algorithm>
#include <math.h>

#include "code/math/aabb.h"
#include "code/math/matrix.h"
#include "code/math/sphere.h"
#include "code/math/vector.h"
#include "code/pure3d/drawable.h"
#include "code/pure3d/pass.h"
#include "code/pure3d/primitive.h"

namespace pure3d
{
	// 0x107547D0: orders the parts of the farthest first
	struct PartDistanceGreater
	{
		bool operator()(DrawablePart* a, DrawablePart* b) const
		{
			return a->distance > b->distance;
		}
	};

	// The order of the nearest first
	struct PartDistanceLess
	{
		bool operator()(DrawablePart* a, DrawablePart* b) const
		{
			return a->distance < b->distance;
		}
	};

	// FUNCTION: ENGINE 0x10754BD0
	// NONMATCHING: the engine keeps the box minimum in registers and its frame holds a temporary more (best 49.5 %)
#ifdef NONMATCHING
	void Pass::UpdateDistances(PartList* parts, const math::Vector* eye)
	{
		for (DrawablePart** it = parts->begin; it != parts->end; ++it)
		{
			DrawablePart* part = *it;
			math::AABB box;
			math::Sphere boxSphere;
			math::Sphere sphere;
			math::Vector centre;
			sphere.centre.x = 0.0f;
			sphere.centre.y = 0.0f;
			sphere.centre.z = 0.0f;
			if (part->state != 0)
			{
				part->state->GetBoundingBox(&box);
				if (!box.IsEmpty())
				{
					float hx = (box.max.x - box.min.x) * 0.5f;
					float hz = (box.max.z - box.min.z) * 0.5f;
					float hy = (box.max.y - box.min.y) * 0.5f;
					boxSphere.centre.x = hx + box.min.x;
					boxSphere.centre.y = hy + box.min.y;
					boxSphere.centre.z = hz + box.min.z;
					boxSphere.radius = sqrtf(hz * hz + hy * hy + hx * hx);
				}
				else
				{
					boxSphere.centre.x = 0.0f;
					boxSphere.centre.y = 0.0f;
					boxSphere.centre.z = 0.0f;
					boxSphere.radius = 0.0f;
				}
				sphere = boxSphere;
			}
			else
			{
				part->primitive->GetCentre(&sphere.centre);
			}
			part->batch.worldMatrix.Transform(sphere.centre, centre);
			float dx = centre.x - eye->x;
			float dy = centre.y - eye->y;
			float dz = centre.z - eye->z;
			part->distance = sqrtf(dx * dx + dy * dy + dz * dz) - sphere.radius;
		}
	}

#endif

	// FUNCTION: ENGINE 0x107561F0
#pragma inline_depth(0)
	void Pass::SortBackToFront(PartList* parts, const math::Vector* eye)
	{
		UpdateDistances(parts, eye);
		std::sort(parts->begin, parts->end, PartDistanceGreater());
	}
#pragma inline_depth()

	// The unit's other order (nearest first): the instance is kept
	template void std::sort<DrawablePart**, PartDistanceLess>(DrawablePart**, DrawablePart**, PartDistanceLess);
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x107547D0
// FUNCTION: ENGINE 0x10754860
// FUNCTION: ENGINE 0x10754880
// FUNCTION: ENGINE 0x10754890
// FUNCTION: ENGINE 0x107548A0
// FUNCTION: ENGINE 0x107548C0
// FUNCTION: ENGINE 0x107548D0
// FUNCTION: ENGINE 0x10754930
// FUNCTION: ENGINE 0x107549D0
// FUNCTION: ENGINE 0x10754ED0
// FUNCTION: ENGINE 0x10754EE0
// FUNCTION: ENGINE 0x10754F00
// FUNCTION: ENGINE 0x10754F50
// FUNCTION: ENGINE 0x10754FC0
// FUNCTION: ENGINE 0x10754FE0
// FUNCTION: ENGINE 0x10755030
// FUNCTION: ENGINE 0x107550A0
// FUNCTION: ENGINE 0x107550D0
// FUNCTION: ENGINE 0x107551F0
// FUNCTION: ENGINE 0x10755380
// FUNCTION: ENGINE 0x107553C0
// FUNCTION: ENGINE 0x107553F0
// FUNCTION: ENGINE 0x10755580
// FUNCTION: ENGINE 0x107555C0
// FUNCTION: ENGINE 0x107555F0
// FUNCTION: ENGINE 0x10755910
// FUNCTION: ENGINE 0x10755CC0
// FUNCTION: ENGINE 0x10755CF0
// FUNCTION: ENGINE 0x10755D70
// FUNCTION: ENGINE 0x10755DB0
// FUNCTION: ENGINE 0x10755E20
// FUNCTION: ENGINE 0x10755E70
// FUNCTION: ENGINE 0x10755F60
// FUNCTION: ENGINE 0x10756050
// FUNCTION: ENGINE 0x10756140
// FUNCTION: ENGINE 0x107561A0
// FUNCTION: ENGINE 0x10755F40
// FUNCTION: ENGINE 0x10755F50
// FUNCTION: ENGINE 0x10755940
// FUNCTION: ENGINE 0x10755620
// FUNCTION: ENGINE 0x107559D0
