// pure3d::ExpressionPose (unit around 0x10730B00 - 0x10730C50; file name guessed from the class). Names are guesses.
#include "code/pure3d/primitive.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x10730BA0
	void ExpressionPose::Clear()
	{
		Weight* end = mWeightsEnd;
		for (Weight* at = mWeights; at != end; at++)
		{
			at->weight = 0.0f;
			at->changed = false;
		}
	}

	// FUNCTION: ENGINE 0x10730BD0
	void ExpressionPose::SetWeight(int index, float newWeight)
	{
		Weight* at = &mWeights[index];
		at->weight = newWeight;
		at->changed = true;
	}

	// FUNCTION: ENGINE 0x10730C00
	bool ExpressionPose::GetChanged(int index)
	{
		return mWeights[index].changed;
	}

	// FUNCTION: ENGINE 0x10730C10
	void ExpressionPose::Unknown10730C10(void* target)
	{
		VertexOffsetExpressionMixer* mixer = (VertexOffsetExpressionMixer*)target;
		Weight* at = mWeights;
		Weight* end = mWeightsEnd;
		if (at != end)
		{
			int offset = 0;
			do
			{
				if (at->changed)
				{
					*(float*)(offset + (char*)mixer->mWeights) = at->weight;
					mixer->mChanged = true;
					at->changed = false;
				}
				at++;
				offset += 4;
			} while (at != end);
		}
	}
}
