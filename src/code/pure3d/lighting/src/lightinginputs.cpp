// pure3d::LightingInputs (RTTI name; unit around 0x107A6600 - 0x107A7000, file name guessed from the class). Names
// are guesses.
#include "code/pure3d/lighting.h"
#include "code/pure3d/pddi.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x107A6B10
	void LightingInputs::SetShaderConstant()
	{
		float x = enabled ? 1.0f : 0.0f;
		float y;
		float z;
		if (unknown4)
		{
			y = unknown8;
			z = unknownC;
		}
		else
		{
			y = 0.0f;
			z = 1.0f;
		}
		pddiBaseContext* context = pddi;
		context->constantsDirty |= 0x10;
		pddiBaseContext::Constants* constants = context->constants;
		float* constant = &constants->values[gLightingInputsConstant];
		constant[0] = x;
		constant[1] = y;
		constant[2] = z;
		constant[3] = 0.0f;
	}
}
