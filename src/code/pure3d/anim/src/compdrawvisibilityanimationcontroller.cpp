// pure3d::CompDrawVisibilityAnimationController (unit around 0x107347B0 - 0x10734C60; file name guessed from the
// class). Names are guesses.
#include "code/pure3d/channel.h"
#include "code/pure3d/drawable.h"
#include "code/pure3d/primitive.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x10734A50
	// NONMATCHING: the engine stores the vftable and the drawable before it loads the two arrays (75.0 %)
#ifdef NONMATCHING
	CompDrawVisibilityAnimationController::~CompDrawVisibilityAnimationController()
	{
		mDrawable = 0;
		if (mSegments != 0)
		{
			delete[] mSegments;
		}
		if (mChannels != 0)
		{
			delete[] mChannels;
		}
	}
#endif

	// FUNCTION: ENGINE 0x107347F0
	Drawable* CompDrawVisibilityAnimationController::GetDrawable()
	{
		return mDrawable;
	}

	// FUNCTION: ENGINE 0x10734BF0
	// NONMATCHING: the engine loads the other controller's pointer for the GetDrawable call between the stores of the
	// two arrays (78.0 %)
#ifdef NONMATCHING
	CompDrawVisibilityAnimationController::CompDrawVisibilityAnimationController(const CompDrawVisibilityAnimationController& other) : SimpleFrameController(other), mDrawable(0), mChannels(0), mChannelsEnd(0), mSegments(0), mSegmentsEnd(0)
	{
		SetDrawable(const_cast<CompDrawVisibilityAnimationController&>(other).GetDrawable());
	}
#endif

	// FUNCTION: ENGINE 0x10734BE0
	void CompDrawVisibilityAnimationController::SetDrawable(Drawable* drawable)
	{
		mDrawable = drawable;
		FindChannels();
	}

	// FUNCTION: ENGINE 0x10734BB0
	void CompDrawVisibilityAnimationController::SetAnimation(Animation* animation, float a, float b)
	{
		SimpleFrameController::SetAnimation(animation, a, b);
		FindChannels();
	}

	// FUNCTION: ENGINE 0x10734C50
	void CompDrawVisibilityAnimationController::SetTarget(Entity* target)
	{
		SetDrawable(dynamic_cast<Drawable*>(target));
	}

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
