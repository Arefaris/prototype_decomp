#include <math.h>

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

	// FUNCTION: ENGINE 0x107DCD20
	// EQUIVALENT: same instructions, the registers of the three origin - centre differences are numbered differently
	bool Sphere::IntersectRay(const Vector& origin, const Vector& direction, float& t) const
	{
		float dx = origin.x - centre.x;
		float dy = origin.y - centre.y;
		float dz = origin.z - centre.z;
		float b = direction.x * dx + direction.y * dy + direction.z * dz;
		float c = dx * dx + dy * dy + dz * dz - radius * radius;
		if (c > 0.0f && b > 0.0f)
		{
			return false;
		}
		float discriminant = b * b - c;
		if (discriminant < 0.0f)
		{
			return false;
		}
		float hit = -b - sqrtf(discriminant);
		if (hit < 0.0f)
		{
			hit = 0.0f;
		}
		t = hit;
		return true;
	}

	// FUNCTION: ENGINE 0x107DCDF0
	// EQUIVALENT: as IntersectRay
	bool Sphere::IntersectRayFirst(const Vector& origin, const Vector& direction, float& t) const
	{
		float dx = origin.x - centre.x;
		float dy = origin.y - centre.y;
		float dz = origin.z - centre.z;
		float b = direction.x * dx + direction.y * dy + direction.z * dz;
		float c = dx * dx + dy * dy + dz * dz - radius * radius;
		if (c > 0.0f && b > 0.0f)
		{
			return false;
		}
		float discriminant = b * b - c;
		if (discriminant < 0.0f)
		{
			return false;
		}
		float root = sqrtf(discriminant);
		float hit = -b - root;
		if (hit < 0.0f)
		{
			hit = root - b;
		}
		t = hit;
		return true;
	}
}
