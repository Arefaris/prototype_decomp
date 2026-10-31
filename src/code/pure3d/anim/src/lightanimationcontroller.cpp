// pure3d::LightAnimationController (unit around 0x107B2D80 - 0x107B3A40; file name guessed from the class). Names are
// guesses.
#include "code/pure3d/lightanimationcontroller.h"
#include "code/pure3d/lightgroup.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x107B2ED0
	LightAnimationController::LightAnimationController() : lightType(0), light(0)
	{
	}

	// FUNCTION: ENGINE 0x107B2EF0
	bool LightAnimationController::Unknown29()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x107B2F00
	bool LightAnimationController::IsSupported(Animation* animation)
	{
		if (animation != 0 && animation->mGroupCount > 0)
		{
			return animation->mType == 0x4554494C;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x107B2F30
	Light* LightAnimationController::GetLight()
	{
		return light;
	}

	// FUNCTION: ENGINE 0x107B2F60
	LightAnimationController::~LightAnimationController()
	{
		engine::render::ReleaseControllerObject((void*&)light);
	}

	// FUNCTION: ENGINE 0x107B2F80
	void LightAnimationController::SetLight(Light* newLight)
	{
		engine::render::AssignControllerObject((void*&)light, newLight);
		lightType = 0;
		if (light != 0)
		{
			lightType = light->type;
			return;
		}
		lightType = 1;
	}

	// FUNCTION: ENGINE 0x107B39A0
	LightAnimationController::LightAnimationController(const LightAnimationController& other) :
		BlendFrameController(other), lightType(0), light(0)
	{
		SetLight(((LightAnimationController&)other).GetLight());
	}

	// FUNCTION: ENGINE 0x107B39E0
	LightAnimationController* LightAnimationController::Clone()
	{
		return new LightAnimationController(*this);
	}

	// FUNCTION: ENGINE 0x107B3A10
	void LightAnimationController::SetTarget(Entity* target)
	{
		SetLight(dynamic_cast<Light*>(target));
	}
}
