// The dramatic camera's copies of the smaller of two floats and of the vector comparison, which the engine keeps out of
// line in the unit (a source of their own here: the camera's callers must see them as external functions, as the
// engine's compiler did not know their bodies when it compiled the callers).
#include "code/math/vector.h"
#include <math.h>

namespace engine
{
	namespace camera
	{
		float MinOf(float a, float b);
	}
}

// FUNCTION: ENGINE 0x10071300
float engine::camera::MinOf(float a, float b)
{
	return b > a ? a : b;
}

// FUNCTION: ENGINE 0x10070B70
bool math::Vector::IsNearOther(const Vector& other, float tolerance) const
{
	return fabsf(x - other.x) <= tolerance && fabsf(y - other.y) <= tolerance && fabsf(z - other.z) <= tolerance;
}
