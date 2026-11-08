// pure3d::VertexAnimController (unit around 0x1073E340 - 0x1073F220; file name guessed from the class). Names are
// guesses.
#include "code/core/refptr.h"
#include "code/pure3d/loaders/drawableloaders.h"
#include "code/pure3d/channel.h"
#include "code/pure3d/primitive.h"

namespace choreo
{
	extern const float gMinusOne;
}

namespace pure3d
{
	// FUNCTION: ENGINE 0x1073E3F0
	// NONMATCHING: the engine loads the constant -1 before the first member store (87.9 %)
#ifdef NONMATCHING
	VertexAnimController::VertexAnimController(const VertexAnimController& other) : SimpleFrameController(other)
	, mKeyFrames(0), mPrimitive(0), mMeshState(0), mExpression(0), mChanged(true), mLastFrame(choreo::gMinusOne)
	{
		core::RefAssign(mKeyFrames, other.mKeyFrames);
		mPrimitive = other.mPrimitive;
		mMeshState = other.mMeshState;
		mExpression = other.mExpression;
	}
#endif

	// FUNCTION: ENGINE 0x1073E450
	VertexAnimController::~VertexAnimController()
	{
		core::SafeRelease(mKeyFrames);
	}

	// FUNCTION: ENGINE 0x1073E340
	bool VertexAnimController::Unknown25()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x1073E350
	bool VertexAnimController::IsSupported(Animation* animation)
	{
		if (animation != 0 && animation->mGroupCount > 0)
		{
			return animation->mType == 0x58545256;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1073E380
	void VertexAnimController::SetTarget(Entity* target)
	{
	}

	// FUNCTION: ENGINE 0x1073E3D0
	void VertexAnimController::Unknown27()
	{
		mFrame = mStartFrame;
	}

	// FUNCTION: ENGINE 0x1073E3E0
	void VertexAnimController::Unknown28()
	{
		mFrame = mEndFrame;
	}

	// FUNCTION: ENGINE 0x1073E470
	VertexAnimController* VertexAnimController::Clone()
	{
		return new VertexAnimController(*this);
	}

	// FUNCTION: ENGINE 0x1073E390
	void VertexAnimController::SetMeshState(MeshState* state)
	{
		mPrimitive = state->GetPrimitive();
		mMeshState = state;
		mExpression = state->GetExpression();
		mChanged = true;
	}

	// FUNCTION: ENGINE 0x1073E3C0
	bool VertexAnimController::GetUnknown50()
	{
		return mChanged;
	}

	// FUNCTION: ENGINE 0x1073E490
	void VertexAnimController::SetKeyFrames(VertexAnimKeyFrameList* keyFrames)
	{
		core::RefAssign(mKeyFrames, keyFrames);
	}

	// FUNCTION: ENGINE 0x1073EC70
	void VertexAnimController::Unknown5()
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
			mChanged = false;
			if (mFrame != mLastFrame)
			{
				mLastFrame = mFrame;
				mChanged = true;
				SetFromKey(key0, true);
				if (index0 != index1)
				{
					channel->GetKey(index1, &frame1, &key1);
					SetToKey(key1, (mFrame - frame0) / (frame1 - frame0), channel->mode);
				}
				mExpression->ApplyTo((Mesh*)mPrimitive, mMeshState->buffers[mMeshState->unknown38]);
			}
		}
	}
}
