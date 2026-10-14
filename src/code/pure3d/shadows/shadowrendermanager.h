// pure3d::ShadowRenderManager (the unit is code/pure3d/shadows/implementation/shadowrendermanager.cpp from the
// assert paths; its functions run 0x10714560 - 0x10717900): the one object that renders the shadow maps and keeps the
// shadow map the lit passes sample (global 0x11281730, reached through 0x10715910). Only what the passes use; the
// class name is the unit's, member names are guesses.
#ifndef PURE3D_SHADOWRENDERMANAGER_H
#define PURE3D_SHADOWRENDERMANAGER_H

#include "code/pure3d/pddi.h"

namespace pure3d
{
	class ShadowRenderManager
	{
	public:
		// 0x10715910
		static ShadowRenderManager* Get();
		// 0x10715AC0: does nothing (the view state of the render parameters is the argument)
		void Unknown10715AC0(const void* viewState);

		unsigned char unknown0[0x20];
		// The shadow map the lit passes sample (null: none)
		pddiSurface* shadowMap;
	};

	// 0x11281730
	extern ShadowRenderManager* gShadowRenderManager;
}

#endif
