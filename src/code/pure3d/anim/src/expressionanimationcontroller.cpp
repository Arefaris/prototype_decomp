// pure3d::ExpressionAnimationController (unit around 0x10734510 - 0x10734800; file name guessed from the class). Names
// are guesses.
#include <new>

#include "code/core/refptr.h"
#include "code/pure3d/channel.h"
#include "code/pure3d/expressiongroup.h"
#include "code/pure3d/primitive.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x10734510
	bool ExpressionAnimationController::Unknown25()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x10734520
	void ExpressionAnimationController::SetTarget(Entity* target)
	{
	}

	// FUNCTION: ENGINE 0x10734530
	VertexOffsetExpressionMixer* ExpressionAnimationController::GetMixer()
	{
		return mMixer;
	}

	// FUNCTION: ENGINE 0x10734620
	void ExpressionAnimationController::SetMixer(VertexOffsetExpressionMixer* mixer)
	{
		if (mixer != 0)
		{
			mWeightCount = 0;
			delete[] mWeights;
			mWeights = 0;
			core::RefAssign(mMixer, mixer);
			mWeightCount = mMixer->mWeights.Size();
			mWeights = new float[mWeightCount];
			ClearWeights();
		}
	}

	// FUNCTION: ENGINE 0x10734540
	void ExpressionAnimationController::ClearWeights()
	{
		for (int i = 0; i < mWeightCount; i++)
		{
			mWeights[i] = 0.0f;
		}
	}

	// FUNCTION: ENGINE 0x107345B0
	bool ExpressionAnimationController::IsSupported(Animation* animation)
	{
		if (animation != 0 && animation->mGroupCount > 0 && animation->mType == 0x505845)
		{
			if (mMixer != 0)
			{
				ExpressionGroup* expressions = mMixer->mExpressions;
				for (int i = 0; i < animation->mGroupCount; i++)
				{
					if (expressions->FindExpression(animation->GetGroup(i)->mName) == -1)
					{
						return false;
					}
				}
			}
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10734690
	void ExpressionAnimationController::Unknown5()
	{
		if (mAnimation != 0)
		{
			ClearWeights();
			int groupCount = mAnimation->mGroupCount;
			for (int i = 0; i < groupCount; i++)
			{
				AnimationGroup* group = mAnimation->GetGroup(i);
				Float1Channel* channel = (Float1Channel*)group->FindChannel(0x455453, 0x31544C46);
				if (channel != 0)
				{
					int index = mMixer->mExpressions->FindExpression(group->mName);
					if (index >= 0)
					{
						float value;
						channel->GetValue(mFrame, &value);
						VertexOffsetExpressionMixer* mixer = mMixer;
						mixer->mWeights.begin[index] = value;
						mixer->mChanged = true;
					}
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x10734790
	ExpressionAnimationController* ExpressionAnimationController::Clone()
	{
		return new ExpressionAnimationController(*this);
	}
}
