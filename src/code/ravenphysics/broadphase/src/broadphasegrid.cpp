#include "code/ravenphysics/broadphase/broadphasedetector.h"

namespace ravenphysics
{
	// FUNCTION: ENGINE 0x10662F50
	void BroadPhaseGrid::Quantize(unsigned short* cell, const math::Vector& point)
	{
		for (int i = 3; i--; )
		{
			float v = ((&point.x)[i] - (&origin.x)[i]) * (&scale.x)[i];
			if (!(v >= 0.0f))
			{
				v = 0.0f;
			}
			if (v - 65535.0f >= 0.0f)
			{
				v = 65535.0f;
			}
			cell[i] = (unsigned short)(int)v;
		}
	}
}
