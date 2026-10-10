#include "code/math/aabb.h"
#include "code/math/sphere.h"

namespace math
{
	// FUNCTION: ENGINE 0x107DCED0
	void Sphere::GetDirection(const Vector& p, Vector& direction, float& distance) const
	{
		direction.x = p.x - centre.x;
		direction.y = p.y - centre.y;
		direction.z = p.z - centre.z;
		float length = direction.Normalize();
		distance = length - radius;
		if (length == 0.0f)
		{
			direction.x = 0.0f;
			direction.y = 1.0f;
			direction.z = 0.0f;
		}
	}
}
