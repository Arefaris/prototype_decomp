// pure3d::VertexOffsetExpressionMixer (unit around 0x107315F0 - 0x10731900, with its loader; file name guessed from
// the class). Names are guesses.
#include <math.h>
#include <new>

#include "code/engine/driving/carattributes.h"
#include "code/pure3d/expressiongroup.h"
#include "code/pure3d/primitive.h"

namespace pure3d
{
	// 0x10730E00: adds the target of the key, scaled by weight, to the offsets
	void MixExpressionTarget(unsigned int key, float weight, VertexOffsetList* offsets, VertexAnimKeyFrameList* state);

	// FUNCTION: ENGINE 0x10730C80
	// NONMATCHING: the engine keeps the offset of the entry in a local and reloads the entry array every iteration, and keeps both constants in registers (the loop is the same, 6.0 %)
#ifdef NONMATCHING
	void VertexOffsetExpressionMixer::UpdateMixEntries()
	{
		for (unsigned int i = 0; i < (unsigned int)(mMixEntries.end - mMixEntries.begin); i++)
		{
			Expression* expression = mExpressions->mExpressions[i];
			MixEntry* entry = &mMixEntries.begin[i];
			float weight = mWeights.begin[i];
			int last = expression->mKeyCount - 1;
			if (last == 0)
			{
				entry->blended = false;
				entry->first = last;
				entry->scale = fabsf(weight / expression->mTimes[0]);
			}
			else
			{
				const float* time = expression->mTimes;
				int at = -1;
				if (weight > *time)
				{
					do
					{
						at++;
						time++;
						if (at == last)
						{
							break;
						}
					} while (weight > *time);
				}
				if (at == -1)
				{
					entry->blended = false;
					entry->first = 0;
					entry->scale = fabsf(weight / expression->mTimes[0]);
				}
				else if (at == last)
				{
					entry->blended = false;
					entry->first = last;
					entry->scale = fabsf(weight / expression->mTimes[last]);
				}
				else
				{
					float after = expression->mTimes[at + 1];
					float before = expression->mTimes[at];
					if (after * before < 0.0f)
					{
						int nearest = (at + (weight < 0.0f ? 1 : 0)) == 0;
						entry->blended = false;
						entry->first = nearest;
						entry->scale = fabsf(weight / expression->mTimes[nearest]);
					}
					else
					{
						float share = (weight - before) / (after - before);
						entry->first = at;
						entry->blended = true;
						entry->second = at + 1;
						entry->firstShare = engine::driving::gOne - share;
						entry->secondShare = share;
						entry->scale = engine::driving::gOne;
					}
				}
			}
		}
	}
#endif

	// FUNCTION: ENGINE 0x107315F0
	void VertexOffsetExpressionMixer::MixTarget(Expression* expression, int index, float weight, VertexOffsetList* offsets, VertexAnimKeyFrameList* state)
	{
		if (!(fabsf(weight) < 0.01f))
		{
			MixExpressionTarget(expression->mTargets[index], weight, offsets, state);
		}
	}

	// FUNCTION: ENGINE 0x10731630
	// NONMATCHING: the engine reloads the entry array every iteration and keeps the offset of the entry in a local (15.0 %)
#ifdef NONMATCHING
	void VertexOffsetExpressionMixer::Mix(VertexOffsetList* expression, VertexAnimKeyFrameList* state)
	{
		for (unsigned int i = 0; i < (unsigned int)(mMixEntries.end - mMixEntries.begin); i++)
		{
			MixEntry* entry = &mMixEntries.begin[i];
			Expression* source = mExpressions->mExpressions[i];
			if (entry->blended)
			{
				MixTarget(source, entry->first, entry->firstShare, expression, state);
				MixTarget(source, entry->second, entry->secondShare, expression, state);
			}
			else
			{
				MixTarget(source, entry->first, entry->scale, expression, state);
			}
		}
	}
#endif

	// FUNCTION: ENGINE 0x107316F0
	// NONMATCHING: the engine's call leaves ecx alone because its callee (0x10730C80) is not compiled here
#ifdef NONMATCHING
	void VertexOffsetExpressionMixer::Update()
	{
		if (mChanged)
		{
			UpdateMixEntries();
			mChanged = false;
		}
	}
#endif

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
