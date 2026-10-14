// pure3d::Pose (unit around 0x106DD670 - 0x106DD890; file name guessed from the class). Names are guesses.
#include "code/pure3d/pose.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x106DD6E0
	void Pose::Update()
	{
		mData.Update();
		mUpdateCount++;
	}
}
