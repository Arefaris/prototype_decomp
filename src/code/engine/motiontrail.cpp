// code/engine/motiontrail.cpp (file name is a guess): engine::MotionTrail and the classes that make one.
#include "code/engine/motiontrail.h"

namespace engine
{
	// FUNCTION: ENGINE 0x108BD8A0
	void MotionTrail::GetUnknown1C(float* values) const
	{
		// The original writes the second three-float vector before the first
		float* second = values + 3;
		second[0] = unknown1C[3];
		second[1] = unknown1C[4];
		second[2] = unknown1C[5];
		values[0] = unknown1C[0];
		values[1] = unknown1C[1];
		values[2] = unknown1C[2];
	}

	// FUNCTION: ENGINE 0x108BD920
	void MotionTrail::GetUnknown34(float* values) const
	{
		values[0] = unknown34[0];
		values[1] = unknown34[1];
		values[2] = unknown34[2];
		values[3] = unknown34[3];
	}

	// FUNCTION: ENGINE 0x108BD940
	void MotionTrail::SetUnknown34(const float* values)
	{
		unknown34[0] = values[0];
		unknown34[1] = values[1];
		unknown34[2] = values[2];
		unknown34[3] = values[3];
	}

	// FUNCTION: ENGINE 0x108BD960
	MotionTrailCreator::MotionTrailCreator()
		: unknown4(-1)
	{
	}
}
