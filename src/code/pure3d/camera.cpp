// pure3d::Camera: the view-volume test. See camera.h for the model; names are guesses.
#include "code/math/worldbounds.h"
#include "code/pure3d/camera.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x106DCC20
	// EQUIVALENT: same operations in the same order; the engine merges both branches' failing exits into one block
	// and cross-jumps their last test, ours keeps a second exit at the end of the second branch
	bool Camera::Contains(const math::Vector& point, float radius) const
	{
		if (unknown10 == 0)
		{
			if (point.z + radius < minZ)
			{
				return false;
			}
			if (point.z - radius > maxZ)
			{
				return false;
			}
			if (plane0x * point.x + plane0z * point.z > radius)
			{
				return false;
			}
			if (plane1x * point.x + plane1z * point.z > radius)
			{
				return false;
			}
			if (plane2y * point.y + plane2z * point.z > radius)
			{
				return false;
			}
			if (plane3y * point.y + plane3z * point.z > radius)
			{
				return false;
			}
		}
		else
		{
			if (point.z + radius < minZ)
			{
				return false;
			}
			if (point.z - radius > maxZ)
			{
				return false;
			}
			if (point.x + radius < math::WORLD_MIN - halfX)
			{
				return false;
			}
			if (point.x - radius > halfX)
			{
				return false;
			}
			if (point.y + radius < math::WORLD_MIN - halfY)
			{
				return false;
			}
			if (point.y - radius > halfY)
			{
				return false;
			}
		}
		return true;
	}
}
