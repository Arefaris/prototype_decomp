// pure3d::BillboardQuadGroupAnimationController (unit around 0x107B3B00 - 0x107B3FD0; file name guessed from the class).
// Names are guesses.
#include "code/core/refptr.h"
#include "code/pure3d/billboardquadgroupanimationcontroller.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x107B3B00
	BillboardQuadGroupAnimationController::BillboardQuadGroupAnimationController() : group(0)
	{
	}

	// FUNCTION: ENGINE 0x107B3B20
	bool BillboardQuadGroupAnimationController::Unknown25()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x107B3B30
	bool BillboardQuadGroupAnimationController::IsSupported(Animation* animation)
	{
		if (animation != 0)
		{
			return animation->mType == 0x475142;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x107B3B50
	void BillboardQuadGroupAnimationController::SetTarget(Entity* target)
	{
	}

	// FUNCTION: ENGINE 0x107B3B60
	BillboardQuadGroup* BillboardQuadGroupAnimationController::GetGroup()
	{
		return group;
	}

	// FUNCTION: ENGINE 0x107B3C30
	BillboardQuadGroupAnimationController::~BillboardQuadGroupAnimationController()
	{
		core::SafeRelease(group);
	}

	// FUNCTION: ENGINE 0x107B3C50
	void BillboardQuadGroupAnimationController::SetGroup(BillboardQuadGroup* newGroup)
	{
		core::RefAssign(group, newGroup);
	}

	// FUNCTION: ENGINE 0x107B3F80
	BillboardQuadGroupAnimationController::BillboardQuadGroupAnimationController(
		const BillboardQuadGroupAnimationController& other) : SimpleFrameController(other), group(0)
	{
		SetGroup(other.group);
	}

	// FUNCTION: ENGINE 0x107B3FB0
	BillboardQuadGroupAnimationController* BillboardQuadGroupAnimationController::Clone()
	{
		return new BillboardQuadGroupAnimationController(*this);
	}
}
