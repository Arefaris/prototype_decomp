// pure3d::RenderParams (RTTI name; unit around 0x1074E500 - 0x1074F800, file name guessed from the class). Names are
// guesses.
#include "code/pure3d/lighting.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x1074EE10
	int RenderParams::GetUnknown14()
	{
		return unknown14;
	}

	// FUNCTION: ENGINE 0x1074F3B0
	void* RenderParams::GetViewState(int view)
	{
		return &views[view];
	}

	// FUNCTION: ENGINE 0x1074F3C0
	void* RenderParams::GetCameraData(int view)
	{
		return &cameras[view];
	}
}
