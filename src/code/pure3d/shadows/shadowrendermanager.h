// pure3d::ShadowRenderManager (the unit is code/pure3d/shadows/implementation/shadowrendermanager.cpp from the
// assert paths; its functions run 0x10714560 - 0x10717900): the one object that renders the shadow maps and keeps the
// shadow map the lit passes sample (global 0x11281730, reached through 0x10715910). Only what the passes use; the
// class name is the unit's, member names are guesses.
#ifndef PURE3D_SHADOWRENDERMANAGER_H
#define PURE3D_SHADOWRENDERMANAGER_H

#include "code/pure3d/pddi.h"

namespace core
{
	struct IMemoryAllocator;
}

namespace pure3d
{
	class ShadowRenderManager
	{
	public:
		// 0x10716770: builds the manager over the shadow quality mode its argument names (it must be the first one)
		ShadowRenderManager(int mode);
		// 0x10716830: creates the shadow map heap and the manager over it
		static void Create(int mode);

		// 0x10715910
		static ShadowRenderManager* Get();
		// 0x10715AC0: does nothing (the view state of the render parameters is the argument)
		void Unknown10715AC0(const void* viewState);
		// 0x10715F30: makes the shadow map again after the device came back (called by the default pool)
		void Unknown10715F30();
		// 0x10715C80: gives the shadow map memory up to a borrower (the pause state) and answers the heap it is in
		int LendShadowMapHeap();
		// 0x10716900: takes the shadow map memory back and makes the map again
		void ReclaimShadowMapHeap();

		unsigned char unknown0[0x18];
		// 0x107064A0 over the name "unlit"
		void* unknown18;
		// The mode Create was given (0 - 3, from the context settings' shadow setting)
		int mode;
		// The shadow map the lit passes sample (null: none)
		pddiSurface* shadowMap;
		// Set while the shadow map memory is lent out (0x10715C80, 0x10716900)
		bool lent;
		unsigned char unknown25[0xf];
	};

	// 0x11281730
	extern ShadowRenderManager* gShadowRenderManager;
	// 0x11281734: the heap the shadow maps and their surfaces are allocated from
	extern core::IMemoryAllocator* gShadowMapHeap;
}

#endif
