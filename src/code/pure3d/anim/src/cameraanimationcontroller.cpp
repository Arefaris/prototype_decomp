// pure3d::CameraAnimationController (unit around 0x107B4110 - 0x107B5340; file name guessed from the class). Names are
// guesses.
#include "code/core/refptr.h"
#include "code/pure3d/cameraanimationcontroller.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x107B43C0
	CameraAnimationController::CameraAnimationController() : camera(0), unknown118(false), cameraKind(-1),
		unknown119(true)
	{
	}

	// FUNCTION: ENGINE 0x107B4400
	bool CameraAnimationController::Unknown29()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x107B4410
	bool CameraAnimationController::IsSupported(Animation* animation)
	{
		if (animation != 0 && animation->mGroupCount > 0)
		{
			return animation->mType == 0x4D4143;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x107B4440
	Camera* CameraAnimationController::GetCamera()
	{
		return camera;
	}

	// FUNCTION: ENGINE 0x107B5150
	CameraAnimationController::~CameraAnimationController()
	{
		core::SafeRelease(camera);
	}

	// FUNCTION: ENGINE 0x107B5170
	void CameraAnimationController::SetCamera(Camera* newCamera)
	{
		core::SafeRelease(camera);
		cameraKind = -1;
		if (newCamera != 0)
		{
			if (dynamic_cast<VectorCamera*>(newCamera) != 0)
			{
				core::RefAssign(camera, newCamera);
				cameraKind = 1;
				return;
			}
			if (dynamic_cast<PointCamera*>(newCamera) != 0)
			{
				core::RefAssign(camera, newCamera);
				cameraKind = 2;
				return;
			}
			if (dynamic_cast<OrbitCamera*>(newCamera) == 0)
			{
				core::RefAssign(camera, newCamera);
				cameraKind = 0;
			}
		}
	}

	// FUNCTION: ENGINE 0x107B5260
	CameraAnimationController::CameraAnimationController(const CameraAnimationController& other) :
		BlendFrameController(other), cameraKind(-1), camera(0), unknown118(false), unknown119(true)
	{
		SetCamera(((CameraAnimationController&)other).GetCamera());
	}

	// FUNCTION: ENGINE 0x107B52B0
	CameraAnimationController* CameraAnimationController::Clone()
	{
		return new CameraAnimationController(*this);
	}

	// FUNCTION: ENGINE 0x107B52E0
	void CameraAnimationController::SetTarget(Entity* target)
	{
		SetCamera(dynamic_cast<Camera*>(target));
	}
}
