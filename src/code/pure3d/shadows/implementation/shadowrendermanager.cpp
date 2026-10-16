// pure3d::ShadowRenderManager (code/pure3d/shadows/implementation/shadowrendermanager.cpp; 0x10714560 - 0x10717900).
// Only the pieces the passes use are reconstructed. Names are guesses.
#include "code/core/heap.h"
#include "code/core/memory/imemoryallocator.h"
#include "code/pure3d/shadows/shadowrendermanager.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x10716830
	void ShadowRenderManager::Create(int mode)
	{
		gShadowMapHeap = core::NewHeapAllocator(0x500000, core::GetCurrentHeap(), "shadowMapHeap", 0x10, false, false);
		core::RegisterHeap(4, core::GetCurrentHeap(), gShadowMapHeap);
		gShadowMapHeap->AddRef();
		gShadowMapHeap->SetSafetyMode(2);
		gShadowRenderManager = new ShadowRenderManager(mode);
	}

	// FUNCTION: ENGINE 0x10715910
	ShadowRenderManager* ShadowRenderManager::Get()
	{
		return gShadowRenderManager;
	}

	// FUNCTION: ENGINE 0x10715AC0
	void ShadowRenderManager::Unknown10715AC0(const void* viewState)
	{
	}
}
