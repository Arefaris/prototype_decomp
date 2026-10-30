// pure3d::VertexRegionAnimController (unit around 0x1072EBD0 - 0x10730570; file name guessed from the class). Names are
// guesses.
#include "code/engine/driving/carattributes.h"
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
}
