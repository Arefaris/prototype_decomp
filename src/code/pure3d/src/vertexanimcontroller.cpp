// pure3d::VertexAnimController (unit around 0x1073E340 - 0x1073F220; file name guessed from the class). Names are
// guesses.
#include "code/pure3d/primitive.h"

namespace pure3d
{
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
}
