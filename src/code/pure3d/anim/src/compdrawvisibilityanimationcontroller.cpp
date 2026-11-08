// pure3d::CompDrawVisibilityAnimationController (unit around 0x107347B0 - 0x10734C60; file name guessed from the
// class). Names are guesses.
#include <new>

#include "code/pure3d/channel.h"
#include "code/pure3d/context.h"
#include "code/pure3d/drawable.h"
#include "code/pure3d/primitive.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x10734A50
	CompDrawVisibilityAnimationController::~CompDrawVisibilityAnimationController()
	{
		mDrawable = 0;
	}

	// FUNCTION: ENGINE 0x107347F0
	Drawable* CompDrawVisibilityAnimationController::GetDrawable()
	{
		return mDrawable;
	}

	// FUNCTION: ENGINE 0x10734A20
	CompDrawVisibilityAnimationController::CompDrawVisibilityAnimationController() : mDrawable(0)
	{
	}

	// FUNCTION: ENGINE 0x10734BF0
	CompDrawVisibilityAnimationController::CompDrawVisibilityAnimationController(const CompDrawVisibilityAnimationController& other) : SimpleFrameController(other), mDrawable(0)
	{
		SetDrawable(const_cast<CompDrawVisibilityAnimationController&>(other).GetDrawable());
	}

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

	// FUNCTION: ENGINE 0x10734AD0
	// NONMATCHING: the engine loads the arguments of FindSegment before it computes the address of the segment slot,
	// and takes the name's address with lea (67.0 %)
#ifdef NONMATCHING
	void CompDrawVisibilityAnimationController::FindChannels()
	{
		mSegments.Clear();
		mChannels.Clear();
		if (mAnimation != 0 && mDrawable != 0)
		{
			int groupCount = mAnimation->mGroupCount;
			{
				unsigned int noSegment = 0;
				mSegments.Allocate(groupCount, (const unsigned short*)&noSegment);
			}
			{
				BoolChannel* noChannel = 0;
				mChannels.Allocate(groupCount, &noChannel);
			}
			for (int i = 0; i < groupCount; i++)
			{
				mSegments[i] = mDrawable->FindSegment(((ContextName*)&mAnimation->GetGroup(i)->mName)->GetHash());
				mChannels[i] = (BoolChannel*)mAnimation->GetGroup(i)->FindChannel(0x534956, 0x4C4F4F42);
			}
		}
	}
#endif

	// FUNCTION: ENGINE 0x10734C30
	CompDrawVisibilityAnimationController* CompDrawVisibilityAnimationController::Clone()
	{
		return new CompDrawVisibilityAnimationController(*this);
	}
}
