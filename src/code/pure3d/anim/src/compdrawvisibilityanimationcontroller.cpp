// pure3d::CompDrawVisibilityAnimationController (unit around 0x107347B0 - 0x10734C60; file name guessed from the
// class). Names are guesses.
#include "code/pure3d/channel.h"
#include "code/pure3d/drawable.h"
#include "code/pure3d/primitive.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x107347B0
	bool CompDrawVisibilityAnimationController::Unknown25()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x107347C0
	bool CompDrawVisibilityAnimationController::IsSupported(Animation* animation)
	{
		if (animation != 0 && animation->mGroupCount > 0)
		{
			return animation->mType == 0x53495650;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x107348B0
	void CompDrawVisibilityAnimationController::Unknown5()
	{
		int groupCount = mAnimation->mGroupCount;
		for (int i = 0; i < groupCount; i++)
		{
			if (mSegments[i] != 0xFFFF && mChannels[i] != 0)
			{
				bool visible;
				mChannels[i]->GetValue(mFrame, &visible);
				mDrawable->SetSegmentVisible(mSegments[i], visible);
			}
		}
	}

	// FUNCTION: ENGINE 0x10734C30
	CompDrawVisibilityAnimationController* CompDrawVisibilityAnimationController::Clone()
	{
		return new CompDrawVisibilityAnimationController(*this);
	}
}
