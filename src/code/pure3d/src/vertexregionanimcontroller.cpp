// pure3d::VertexRegionAnimController (unit around 0x1072EBD0 - 0x10730570; file name guessed from the class). Names are
// guesses.
#include "code/engine/driving/carattributes.h"
#include <new>

#include "code/core/refptr.h"
#include "code/pure3d/loaders/drawableloaders.h"
#include "code/pure3d/primitive.h"

namespace pure3d
{
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
}
