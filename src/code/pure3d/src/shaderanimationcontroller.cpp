// pure3d::ShaderAnimationController (unit around 0x1072E570 - 0x1072EA40; file name guessed from the class). Names are
// guesses.
#include "code/pure3d/primitive.h"
#include "code/pure3d/shader.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x1072E590
	bool ShaderAnimationController::Unknown25()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x1072E5E0
	Shader* ShaderAnimationController::GetShader()
	{
		return mShader;
	}

	// FUNCTION: ENGINE 0x1072E5A0
	bool ShaderAnimationController::IsSupported(Animation* animation)
	{
		if (animation != 0 && animation->mGroupCount > 0)
		{
			return animation->mType == 0x44414853 || animation->mType == 0x584554;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1072EA10
	void ShaderAnimationController::SetTarget(Entity* target)
	{
		SetBindingSource(dynamic_cast<Shader*>(target));
	}

	// FUNCTION: ENGINE 0x1072E9F0
	ShaderAnimationController* ShaderAnimationController::Clone()
	{
		return new ShaderAnimationController(*this);
	}
}
