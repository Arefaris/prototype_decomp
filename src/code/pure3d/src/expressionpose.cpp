// pure3d::ExpressionPose (unit around 0x10730B00 - 0x10730C50; file name guessed from the class). Names are guesses.
#include <new>

#include "code/pure3d/primitive.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x10731BE0
	ExpressionPose::~ExpressionPose()
	{
	}

	// FUNCTION: ENGINE 0x10730BA0
	void ExpressionPose::Clear()
	{
		Weight* end = mArray.end;
		for (Weight* at = mArray.begin; at != end; at++)
		{
			at->weight = 0.0f;
			at->changed = false;
		}
	}

	// FUNCTION: ENGINE 0x10730BC0
	int ExpressionPose::GetWeightCount()
	{
		return mArray.end - mArray.begin;
	}

	// FUNCTION: ENGINE 0x10730BF0
	float ExpressionPose::GetWeight(int index)
	{
		return mArray.begin[index].weight;
	}

	// FUNCTION: ENGINE 0x10730BD0
	void ExpressionPose::SetWeight(int index, float newWeight)
	{
		Weight* at = &mArray.begin[index];
		at->weight = newWeight;
		at->changed = true;
	}

	// FUNCTION: ENGINE 0x10730C00
	bool ExpressionPose::GetChanged(int index)
	{
		return mArray.begin[index].changed;
	}

	// FUNCTION: ENGINE 0x10730C10
	void ExpressionPose::Unknown10730C10(void* target)
	{
		VertexOffsetExpressionMixer* mixer = (VertexOffsetExpressionMixer*)target;
		Weight* at = mArray.begin;
		Weight* end = mArray.end;
		if (at != end)
		{
			int offset = 0;
			do
			{
				if (at->changed)
				{
					*(float*)(offset + (char*)mixer->mWeights.begin) = at->weight;
					mixer->mChanged = true;
					at->changed = false;
				}
				at++;
				offset += 4;
			} while (at != end);
		}
	}
}
