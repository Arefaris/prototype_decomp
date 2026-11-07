// pure3d::ShadowRenderManager (code/pure3d/shadows/implementation/shadowrendermanager.cpp; 0x10714560 - 0x10717900).
// Only the pieces the passes use are reconstructed. Names are guesses.
#include "code/core/criticalsection.h"
#include "code/core/heap.h"
#include "code/core/memory/imemoryallocator.h"
#include "code/core/memory/memorypool.h"
#include "code/core/refptr.h"
#include "code/pure3d/shader.h"
#include "code/pure3d/texture/texture.h"
#include "code/pure3d/context.h"
#include "code/pure3d/shadows/shadowrendermanager.h"

namespace engine
{
	namespace driving
	{
		extern const float gOne;
	}
}

namespace proto
{
	extern const float gTen;
}

namespace pure3d
{
	// The memory pools of the particle code (the allocation functions below take a block from the pool on the render
	// thread, the frees return it to its pool or to the heap when it lies outside the pool); the names are guesses
	// GLOBAL: ENGINE 0x112816EC
	static core::MemoryPool* gParticleControllerPool = 0;
	// GLOBAL: ENGINE 0x112816F0
	static core::MemoryPool* gParticleGeneratorPool = 0;
	// GLOBAL: ENGINE 0x112816F4
	static core::MemoryPool* gParticleSystemStatePool = 0;
	// GLOBAL: ENGINE 0x112816E4
	core::MemoryPool* gAsyncTaskPool = 0;
	// GLOBAL: ENGINE 0x112816E8
	core::MemoryPool* gFeaturePacketPool = 0;
	// GLOBAL: ENGINE 0x112816F8
	bool gParticlesStarted = false;
	// GLOBAL: ENGINE 0x112816FC
	Shader* gParticleDebugShader = 0;
	// The transform the particle code starts with (name guess)
	// GLOBAL: ENGINE 0x11281700
	float gParticleTransform[12];

	// The thread the render code allocates on (names guessed): the allocation functions below use their pool only on this
	// thread
	// GLOBAL: ENGINE 0x112816E0
	int gRenderThread = 0;
	// GLOBAL: ENGINE 0x1113764C
	int gRenderHeap = -1;

	// FUNCTION: ENGINE 0x10714D70
	void SetRenderThread()
	{
		gRenderThread = core::GetThreadData();
	}

	// FUNCTION: ENGINE 0x10714D80
	bool IsRenderThread()
	{
		return core::GetThreadData() == gRenderThread;
	}

	// FUNCTION: ENGINE 0x10714E20
	int GetRenderHeap()
	{
		if (IsRenderThread())
		{
			return gRenderHeap;
		}
		return core::GetCurrentHeap();
	}

	// FUNCTION: ENGINE 0x10714E40
	void* AllocFromPool(core::IMemoryAllocator* pool, unsigned int size, unsigned int alignment)
	{
		core::IMemoryAllocator* allocator;
		if (pool != 0 && IsRenderThread())
		{
			allocator = pool;
		}
		else
		{
			allocator = core::GetHeapAllocator(core::GetCurrentHeap());
		}
		if (alignment > 1)
		{
			return allocator->AllocAligned(size, alignment);
		}
		return allocator->Alloc(size);
	}

	// FUNCTION: ENGINE 0x10714F50
	void* AllocPoolBlockEC(unsigned int size)
	{
		core::IMemoryAllocator* pool = gParticleControllerPool;
		core::IMemoryAllocator* allocator;
		if (pool != 0 && IsRenderThread())
		{
			allocator = pool;
		}
		else
		{
			allocator = core::GetHeapAllocator(core::GetCurrentHeap());
		}
		return allocator->AllocAligned(size, 0x10);
	}

	// FUNCTION: ENGINE 0x10714FA0
	void* AllocPoolBlockF0(unsigned int size)
	{
		core::IMemoryAllocator* pool = gParticleGeneratorPool;
		core::IMemoryAllocator* allocator;
		if (pool != 0 && IsRenderThread())
		{
			allocator = pool;
		}
		else
		{
			allocator = core::GetHeapAllocator(core::GetCurrentHeap());
		}
		return allocator->Alloc(size);
	}

	// FUNCTION: ENGINE 0x10714FF0
	void* AllocPoolBlockF4(unsigned int size)
	{
		core::IMemoryAllocator* pool = gParticleSystemStatePool;
		core::IMemoryAllocator* allocator;
		if (pool != 0 && IsRenderThread())
		{
			allocator = pool;
		}
		else
		{
			allocator = core::GetHeapAllocator(core::GetCurrentHeap());
		}
		return allocator->AllocAligned(size, 0x10);
	}

	// FUNCTION: ENGINE 0x10715060
	void FreePoolBlockEC(void* block)
	{
		core::IMemoryAllocator* pool = gParticleControllerPool;
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

	// FUNCTION: ENGINE 0x107150B0
	void FreePoolBlockF0(void* block)
	{
		core::IMemoryAllocator* pool = gParticleGeneratorPool;
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

	// FUNCTION: ENGINE 0x10715100
	void FreePoolBlockF4(void* block)
	{
		core::IMemoryAllocator* pool = gParticleSystemStatePool;
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

	void Unknown1075CCF0();
	void Unknown106F2D00();
	void Unknown106EC370();
	void Unknown106EC3E0();
	void Unknown106F2DB0();
	void Unknown1075CD00();

	// This unit's copy of the pool release
	// FUNCTION: ENGINE 0x10715180
	template void core::SafeRelease<core::MemoryPool>(core::MemoryPool*& object);

	// FUNCTION: ENGINE 0x10715380
	void Unknown10715380()
	{
		Unknown106EC3E0();
		core::SafeRelease(gParticleSystemStatePool);
		core::SafeRelease(gParticleGeneratorPool);
		core::SafeRelease(gParticleControllerPool);
		core::SafeRelease(gFeaturePacketPool);
		core::SafeRelease(gAsyncTaskPool);
		core::SafeRelease(gParticleDebugShader);
		Unknown106F2DB0();
		Unknown1075CD00();
		gRenderThread = 0;
		gRenderHeap = -1;
		gParticlesStarted = false;
	}

	// FUNCTION: ENGINE 0x107151B0
	void Unknown107151B0(const ContextRenderSettings* settings)
	{
		gRenderHeap = settings->unknown4;
		gParticlesStarted = true;
		gRenderThread = core::GetThreadData();
		Unknown1075CCF0();
		Unknown106F2D00();
		if (gPddiDx != 0)
		{
			gParticleDebugShader = new Shader("particleDebug");
			gParticleDebugShader->AddRef();
		}
		gParticleTransform[0] = engine::driving::gOne;
		gParticleTransform[1] = 0.0f;
		gParticleTransform[2] = 0.0f;
		gParticleTransform[3] = proto::gTen;
		gParticleTransform[4] = 0.0f;
		gParticleTransform[5] = engine::driving::gOne;
		gParticleTransform[6] = 0.0f;
		gParticleTransform[7] = 0.0f;
		gParticleTransform[8] = 0.0f;
		gParticleTransform[9] = engine::driving::gOne;
		gParticleTransform[10] = 0.0f;
		gParticleTransform[11] = 0.0f;
		core::CreateMemoryPool(&gAsyncTaskPool, 0x50, 0x32, GetRenderHeap(), "particles::AsyncTask Pool", 0x10);
		core::CreateMemoryPool(&gFeaturePacketPool, 0x5C, 0xDAC, GetRenderHeap(), "particles::FeaturePacket Pool", 0x10);
		core::CreateMemoryPool(&gParticleControllerPool, 0x58, 500, GetRenderHeap(), "particles::ParticleController Pool",
			0x10);
		core::CreateMemoryPool(&gParticleGeneratorPool, 0x450, 500, GetRenderHeap(), "particles::ParticleGenerator Pool",
			0x10);
		core::CreateMemoryPool(&gParticleSystemStatePool, 0x4E0, 500, GetRenderHeap(),
			"particles::ParticleSystemState Pool", 0x10);
		gAsyncTaskPool->SetSafetyMode(2);
		gFeaturePacketPool->SetSafetyMode(2);
		gParticleControllerPool->SetSafetyMode(2);
		gParticleGeneratorPool->SetSafetyMode(2);
		gParticleSystemStatePool->SetSafetyMode(2);
		Unknown106EC370();
	}

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
