// math::AABB members that other units use (kept copies of inlines of the math headers; this is not an original
// translation unit).
#include "code/math/aabb.h"
#include "code/math/sphere.h"

#include <math.h>

namespace math
{
	// FUNCTION: ENGINE 0x100D5AC0
	// EQUIVALENT: the engine reloads the box's far corner after the emptiness test, every form tried here keeps it in a
	// register from the test
	Sphere AABB::GetSphere() const
	{
		Sphere sphere;
		if (!(min.x > max.x || min.y > max.y || min.z > max.z))
		{
			float hz = (max.z - min.z) * 0.5f;
			float hx = (max.x - min.x) * 0.5f;
			float hy = (max.y - min.y) * 0.5f;
			sphere.centre.x = min.x + hx;
			sphere.centre.y = min.y + hy;
			sphere.centre.z = min.z + hz;
			float squared = hz * hz;
			squared += hx * hx;
			squared += hy * hy;
			sphere.radius = sqrtf(squared);
		}
		else
		{
			sphere.centre.x = 0.0f;
			sphere.centre.y = 0.0f;
			sphere.centre.z = 0.0f;
			sphere.radius = 0.0f;
		}
		return sphere;
	}
}
