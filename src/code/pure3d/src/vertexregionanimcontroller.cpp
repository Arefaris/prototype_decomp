// pure3d::VertexRegionAnimController (unit around 0x1072EBD0 - 0x10730570; file name guessed from the class). Names are
// guesses.
#include "code/engine/driving/carattributes.h"
#include <new>

#include "code/core/refptr.h"
#include "code/pure3d/channel.h"
#include "code/pure3d/loaders/drawableloaders.h"
#include "code/pure3d/primitive.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x107303F0
	// NONMATCHING: the engine releases the regions through a counted loop over a copy of the first pointer and clears
	// the list behind the loop (about 40 %)
#ifdef NONMATCHING
	VertexRegionAnimController::~VertexRegionAnimController()
	{
		core::SafeRelease(mKeyFrames);
		VertexDeformRegion** first = mRegions.items;
		int regionCount = mRegions.end - first;
		for (VertexDeformRegion** region = first; regionCount != 0; regionCount--, region++)
		{
			core::SafeRelease(*region);
		}
		mRegions.end = first;
		delete mOffsets;
		mOffsets = 0;
		mRegions.end = first;
	}
#endif

	// FUNCTION: ENGINE 0x107302C0
	// NONMATCHING: the engine reloads the expression into ecx right after the allocation (96.0 %)
#ifdef NONMATCHING
	VertexRegionAnimController::VertexRegionAnimController(const VertexRegionAnimController& other) : SimpleFrameController(other), mRegions()
	{
		mKeyFrames = 0;
		mPrimitive = 0;
		mMeshState = 0;
		mExpression = 0;
		mOffsets = 0;
		mChanged = true;
		core::RefAssign(mKeyFrames, other.mKeyFrames);
		mPrimitive = other.mPrimitive;
		mMeshState = other.mMeshState;
		mExpression = other.mExpression;
		if (mExpression != 0)
		{
			delete mOffsets;
			float* offsets = new float[mExpression->count];
			VertexOffsetList* expression = mExpression;
			mOffsets = offsets;
			unsigned int count = expression->count;
			for (unsigned int i = 0; i < count; i++)
			{
				mOffsets[i] = 0.0f;
			}
		}
	}
#endif

	// FUNCTION: ENGINE 0x1072EBD0
	bool VertexRegionAnimController::Unknown25()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x1072EBE0
	bool VertexRegionAnimController::IsSupported(Animation* animation)
	{
		if (animation != 0 && animation->mGroupCount > 0)
		{
			if (animation->numFrames == engine::driving::gTwo)
			{
				return animation->mType == 0x58545256;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1072EC20
	void VertexRegionAnimController::SetTarget(Entity* target)
	{
	}

	// FUNCTION: ENGINE 0x10730460
	VertexRegionAnimController* VertexRegionAnimController::Clone()
	{
		return new VertexRegionAnimController(*this);
	}

	// FUNCTION: ENGINE 0x1072ED30
	bool VertexRegionAnimController::GetUnknownD8()
	{
		return mChanged;
	}

	// FUNCTION: ENGINE 0x1072F130
	void VertexRegionAnimController::SetKeyFrames(VertexAnimKeyFrameList* keyFrames)
	{
		core::RefAssign(mKeyFrames, keyFrames);
	}

	// FUNCTION: ENGINE 0x1072F8C0
	void VertexRegionAnimController::SetRegion(VertexDeformRegion* region)
	{
		if (region != 0 && !mRegions.IsFull())
		{
			region->AddRef();
			mRegions.PushBack(region);
			mChanged = true;
		}
	}

	// FUNCTION: ENGINE 0x1072EC30
	// EQUIVALENT: the same calls and stores in the same order; the engine keeps the overflow test of the array size in ecx
	// and the expression pointer in ecx, ours uses ebx and eax (72.6 %)
	void VertexRegionAnimController::SetMeshState(MeshState* state)
	{
		mPrimitive = state->GetPrimitive();
		mMeshState = state;
		mExpression = state->GetExpression();
		if (mExpression != 0)
		{
			delete mOffsets;
			mOffsets = new float[mExpression->count];
			unsigned int count = mExpression->count;
			for (unsigned int i = 0; i < count; i++)
			{
				mOffsets[i] = 0.0f;
			}
		}
	}

	// FUNCTION: ENGINE 0x10730490
	void VertexRegionAnimController::Unknown5()
	{
		if (UpdateWeights() == true)
		{
			IntChannel* channel = (IntChannel*)mAnimation->GetGroup(0)->FindChannel(0x58545256, 0x544E49);
			if (channel != 0)
			{
				unsigned int index0;
				unsigned int index1;
				int key0;
				int key1;
				float frame0;
				float frame1;
				channel->FindKeys(mFrame, &index0, &index1);
				channel->GetKey(index0, &frame0, &key0);
				SetFromKey(key0, true);
				channel->GetKey(index1, &frame1, &key1);
				SetToKey(key1, channel->mode);
				ApplyKeys();
				mChanged = false;
			}
		}
	}
}
