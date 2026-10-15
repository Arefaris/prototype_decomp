// choreo::PartitionDriver and choreo::AnimationBlendDriver (the unit before deltatransform.cpp; file name guessed).
// The unit builds the drivers that partition the pose of a puppet and drive the clips of one animation: the blend
// driver keeps a table of fifteen clips (0x2C bytes each, from +0x3C) and the partition driver knows the range of
// joints of the pose its clip is blended into. Names are guesses.
#include "code/choreo/rootdriver.h"

namespace choreo
{
	// FUNCTION: ENGINE 0x1094D430
	PartitionDriver::~PartitionDriver()
	{
		mPose->Release();
	}

	// FUNCTION: ENGINE 0x1094D4B0
	bool PartitionDriver::CoversRoot() const
	{
		return mFirstJoint == 0;
	}

	// FUNCTION: ENGINE 0x1094D4C0
	bool PartitionDriver::Unknown1094D4C0(const AnimationBinding& binding) const
	{
		if (binding.mSource != 0 && mPose != 0)
		{
			if (!binding.mClip.Unknown10952390(mJointMask))
			{
				return false;
			}
		}
		return true;
	}
}
