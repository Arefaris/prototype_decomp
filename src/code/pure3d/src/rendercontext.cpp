// pure3d::RenderContext (unit around 0x1074D650 - 0x1074DB30; file name guessed from the class). Names are guesses.
#include "code/pure3d/context.h"
#include "code/pure3d/lighting.h"
#include "code/pure3d/pass.h"
#include "code/pure3d/pddi.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x1074D880
	void RenderContext::Run(const RenderParams* params)
	{
		if (pass != 0)
		{
			if (setsTargets && params->unknown10 != 0 && params->unknown14 != 0)
			{
				pddiRenderTargets targets = {0, 0, 0, 0, 0};
				targets.depth = ((pddiSurface*)params->unknown14)->GetHandle();
				targets.colour = ((pddiSurface*)params->unknown10)->GetHandle();
				pddi->SetRenderTargets(&targets);
			}
			pass->Visit((void*)params);
			pass->Run((PassContext*)params);
			if (setsTargets && params->unknown10 != 0 && params->unknown14 != 0)
			{
				pddi->SetRenderTargets(0);
			}
		}
	}
}
