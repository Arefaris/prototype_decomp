// pure3d::ShadowRenderManager (code/pure3d/shadows/implementation/shadowrendermanager.cpp; 0x10714560 - 0x10717900).
// Only the pieces the passes use are reconstructed. Names are guesses.
#include "code/core/heap.h"
#include "code/core/memory/imemoryallocator.h"
#include "code/core/refptr.h"
#include "code/pure3d/texture/texture.h"
#include "code/pure3d/context.h"
#include "code/pure3d/shadows/shadowrendermanager.h"

namespace pure3d
{
	// The memory pools of the shadow code (the frees below return a block to its pool, or to the heap when it lies
	// outside the pool); the names are guesses
	extern core::IMemoryAllocator* gShadowPool112816EC;
	extern core::IMemoryAllocator* gShadowPool112816F0;
	extern core::IMemoryAllocator* gShadowPool112816F4;

	// FUNCTION: ENGINE 0x10715060
	// NONMATCHING: the engine keeps the pool in edi and the block in esi (52.6 %)
#ifdef NONMATCHING
	void FreePoolBlockEC(void* block)
	{
		core::IMemoryAllocator* pool = gShadowPool112816EC;
		if (pool != 0)
		{
			core::MemoryRange range;
			pool->GetRange(&range, 0);
			if (range.start <= (unsigned int)block && (unsigned int)block < range.end)
			{
				pool->Free(block);
				return;
			}
		}
		core::FreeAligned(block);
	}
#endif

	// FUNCTION: ENGINE 0x107150B0
	// NONMATCHING: the engine keeps the pool in edi and the block in esi (52.6 %)
#ifdef NONMATCHING
	void FreePoolBlockF0(void* block)
	{
		core::IMemoryAllocator* pool = gShadowPool112816F0;
		if (pool != 0)
		{
			core::MemoryRange range;
			pool->GetRange(&range, 0);
			if (range.start <= (unsigned int)block && (unsigned int)block < range.end)
			{
				pool->Free(block);
				return;
			}
		}
		core::Free(block);
	}
#endif

	// FUNCTION: ENGINE 0x10715100
	// NONMATCHING: the engine keeps the pool in edi and the block in esi (52.6 %)
#ifdef NONMATCHING
	void FreePoolBlockF4(void* block)
	{
		core::IMemoryAllocator* pool = gShadowPool112816F4;
		unsigned int address = (unsigned int)block;
		if (pool != 0)
		{
			core::MemoryRange range;
			pool->GetRange(&range, 0);
			if (range.start <= address && address < range.end)
			{
				pool->Free(block);
				return;
			}
		}
		core::FreeAligned(block);
	}
#endif

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

	// FUNCTION: ENGINE 0x10715F30
	void ShadowRenderManager::Unknown10715F30()
	{
		needsRemake = true;
		Setup(mode, unknown4);
	}

	// FUNCTION: ENGINE 0x10715D60
	void ShadowRenderManager::Unknown10715D60()
	{
		if (!lent)
		{
			Unknown10715CD0();
			pddi->Clear(6);
			Unknown10715940();
		}
	}

	// FUNCTION: ENGINE 0x10715C80
	int ShadowRenderManager::LendShadowMapHeap()
	{
		pddi->Unknown9();
		Unknown10715B00();
		core::SafeRelease(texture);
		int value;
		gShadowMapHeap->GetStat(0, &value);
		lent = true;
		return 4;
	}

	// FUNCTION: ENGINE 0x10716900
	void ShadowRenderManager::ReclaimShadowMapHeap()
	{
		int value;
		gShadowMapHeap->GetStat(0, &value);
		lent = false;
		Setup(mode, -1);
	}

	// FUNCTION: ENGINE 0x10714D60
	ContextSettings::Unknown148::Unknown148()
	{
		unknown0 = 0x100000;
		unknown4 = 0;
	}
}
