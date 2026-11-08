// pure3d::VertexOffsetExpressionMixer (unit around 0x107315F0 - 0x10731900, with its loader; file name guessed from
// the class). Names are guesses.
#include <new>

#include "code/pure3d/expressiongroup.h"
#include "code/pure3d/primitive.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x10731AA0
	VertexOffsetExpressionMixer::~VertexOffsetExpressionMixer()
	{
	}

	// FUNCTION: ENGINE 0x10731700
	void VertexOffsetExpressionMixer::Apply(VertexOffsetList* expression, VertexAnimKeyFrameList* state)
	{
		expression->Prepare();
		Mix(expression, state);
	}

	// FUNCTION: ENGINE 0x10730AF0
	int VertexOffsetExpressionMixer::GetWeightCount()
	{
		return mWeights.Size();
	}

	// FUNCTION: ENGINE 0x10730B00
	void VertexOffsetExpressionMixer::SetWeight(int index, float weight)
	{
		mWeights.begin[index] = weight;
		mChanged = true;
	}

	// FUNCTION: ENGINE 0x10730B20
	float VertexOffsetExpressionMixer::GetWeight(int index)
	{
		return mWeights.begin[index];
	}

	// FUNCTION: ENGINE 0x10730C50
	void VertexOffsetExpressionMixer::ClearWeights()
	{
		for (unsigned int i = 0; i < (unsigned int)mWeights.Size(); i++)
		{
			mWeights.begin[i] = 0.0f;
		}
	}
}
