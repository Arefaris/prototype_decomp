// pure3d::ShadowRenderManager (code/pure3d/shadows/implementation/shadowrendermanager.cpp; 0x10714560 - 0x10717900).
// Only the pieces the passes use are reconstructed. Names are guesses.
#include <math.h>

#include "code/core/criticalsection.h"
#include "code/core/debug.h"
#include "code/core/heap.h"
#include "code/core/memory/imemoryallocator.h"
#include "code/core/memory/memorypool.h"
#include "code/core/refptr.h"
#include "code/pure3d/protopass.h"
#include "code/pure3d/shader.h"
#include "code/pure3d/shaderconstants.h"
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

namespace engine
{
	namespace driving
	{
		extern const float gHalf;
	}
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
	void* AllocateParticleAligned(unsigned int size)
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
	void* AllocateParticle(unsigned int size)
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
	void FreeParticleAligned(void* block)
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
	void FreeParticle(void* block)
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

	// This unit's copy of the release helper for the shadow map heap
	// FUNCTION: ENGINE 0x10715B50
	template void core::SafeRelease<core::IMemoryAllocator>(core::IMemoryAllocator*& object);

	// This unit's copy of the texture reference helper
	// FUNCTION: ENGINE 0x10715B70
	template void core::RefAssign<pure3d::Texture>(pure3d::Texture*& pointer, pure3d::Texture* object);

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

	// FUNCTION: ENGINE 0x10715430
	void SetParticleTransformFlag(bool value)
	{
		if (value)
		{
			gParticleTransform[8] = engine::driving::gOne;
			return;
		}
		gParticleTransform[8] = 0.0f;
	}

	// FUNCTION: ENGINE 0x107154E0
	void SetParticleTransformX(int row, float value)
	{
		gParticleTransform[row * 4] = value;
	}

	// FUNCTION: ENGINE 0x10715500
	void SetParticleTransformY(int row, float value)
	{
		gParticleTransform[row * 4 + 1] = value;
	}

	// FUNCTION: ENGINE 0x10715520
	void SetParticleTransformZ(int row, float value)
	{
		gParticleTransform[row * 4 + 2] = value;
	}

	// FUNCTION: ENGINE 0x10715540
	void SetParticleTransformW(int row, float value)
	{
		gParticleTransform[row * 4 + 3] = value;
	}

	// FUNCTION: ENGINE 0x10715560
	void SetParticleTransformRow(int row, float x, float y, float z, float w)
	{
		float* at = &gParticleTransform[row * 4];
		at[0] = x;
		at[1] = y;
		at[2] = z;
		at[3] = w;
	}

	// FUNCTION: ENGINE 0x107155A0
	void* AllocRenderHeap(unsigned int size)
	{
		return core::HeapAlloc(GetRenderHeap(), size);
	}

	// FUNCTION: ENGINE 0x10716770
	ShadowRenderManager::ShadowRenderManager(int newMode)
	{
		texture = 0;
		unknown4 = -1;
		unknown8 = 0;
		unknownC = 0;
		unknown10 = false;
		unknown14 = 0;
		unknown18 = 0;
		shadowMap = (pddiSurface*)1;
		lent = false;
		width = 0x400;
		height = 0x400;
		needsRemake = false;
		OLD_ASSERT_TEXT_AT("..\\..\\..\\code\\pure3d\\shadows\\implementation\\shadowrendermanager.cpp", 0x46,
			gShadowRenderManager == 0, "0 == sSingleton");
		mode = newMode;
		Setup(newMode, -1);
		unknown18 = new Shader("unlit");
		((Shader*)unknown18)->AddRef();
	}

	// The writes of the shader constants of the device (names guessed): a float, a pair, a triple, a quad
	// FUNCTION: ENGINE 0x10716930
	void SetConstantFloat(const ConstantSlot& slot, float value)
	{
		*pddi->GetConstant(slot.index, pddiBaseContext::CONSTANT_FLOAT) = value;
	}

	// FUNCTION: ENGINE 0x10716960
	void SetConstantFloat2(const ConstantSlot& slot, const float* value)
	{
		float* at = pddi->GetConstant(slot.index, pddiBaseContext::CONSTANT_FLOAT2);
		at[0] = value[0];
		at[1] = value[1];
	}

	// FUNCTION: ENGINE 0x10716990
	void SetConstantFloat3(const ConstantSlot& slot, const float* value)
	{
		float* at = pddi->GetConstant(slot.index, pddiBaseContext::CONSTANT_FLOAT3);
		at[0] = value[0];
		at[1] = value[1];
		at[2] = value[2];
	}

	// FUNCTION: ENGINE 0x107169C0
	void SetConstantFloat4(const ConstantSlot& slot, const float* value)
	{
		float* at = pddi->GetConstant(slot.index, pddiBaseContext::CONSTANT_FLOAT4);
		at[0] = value[0];
		at[1] = value[1];
		at[2] = value[2];
		at[3] = value[3];
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

	// FUNCTION: ENGINE 0x107168B0
	void Unknown107168B0()
	{
		delete gShadowRenderManager;
		gShadowRenderManager = 0;
		core::UnregisterHeap(4);
		core::SafeRelease(gShadowMapHeap);
		if (gShadowMapBlock != 0)
		{
			core::FreeAligned(gShadowMapBlock);
		}
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

	// FUNCTION: ENGINE 0x10715900
	int ShadowRenderManager::GetUnknown20()
	{
		return (int)shadowMap;
	}

	// FUNCTION: ENGINE 0x10715920
	void ShadowRenderManager::SetUnknown20(int value)
	{
		shadowMap = (pddiSurface*)value;
		context->UpdateRenderParams();
	}

	// FUNCTION: ENGINE 0x10715980
	void GetShadowMapSize(int mode, int* width, int* height, int unused, int cascades)
	{
		if (cascades == -1)
		{
			cascades = 4;
		}
		unsigned int rows = (unsigned int)ceil((double)((float)cascades * engine::driving::gHalf));
		switch (mode)
		{
		case 0:
			*width = 0x800;
			*height = rows << 10;
			break;
		case 1:
			*width = 0x400;
			*height = rows << 9;
			break;
		case 2:
			*width = 0x200;
			*height = rows << 8;
			break;
		case 3:
			*width = 0x400;
			*height = 0x400;
			break;
		}
		*width = 0x800;
		*height = 0x800;
	}

	// FUNCTION: ENGINE 0x10715A70
	int GetShadowMapMemory(int mode)
	{
		int width = 0;
		int height = 0;
		GetShadowMapSize(mode, &width, &height, 2, -1);
		return (width * height * 4 + 0xFFFE & 0xFFFF0000) + 0x10000;
	}

	// FUNCTION: ENGINE 0x10715B00
	void ShadowRenderManager::Unknown10715B00()
	{
		BindTextureConstant(gConstantShadowMap.index, 0);
	}

	// FUNCTION: ENGINE 0x10715940
	void ShadowRenderManager::Unknown10715940()
	{
		pddi->SetColourWrite(true, true, true, true);
		pddi->SetRenderTargets(0);
		pddi->SetViewUnknown10(0);
	}

	// FUNCTION: ENGINE 0x10715CD0
	void ShadowRenderManager::Unknown10715CD0()
	{
		pddiRenderTargets targets = { 0, 0, 0, 0, 0 };
		Unknown10715B00();
		if (unknown10)
		{
			targets.colour = ((pddiSurface*)unknown8->info)->GetHandle();
		}
		else
		{
			targets.colour = unknownC;
		}
		targets.depth = ((pddiSurface*)texture->info)->GetHandle();
		pddi->SetRenderTargets(&targets);
		if (unknown10)
		{
			pddi->SetColourWrite(true, true, true, true);
		}
		else
		{
			pddi->SetColourWrite(false, false, false, false);
		}
	}

	// FUNCTION: ENGINE 0x10715B20
	void ShadowRenderManager::SetUnknown10(bool value)
	{
		unknown10 = value;
	}

	// FUNCTION: ENGINE 0x10715F50
	void ShadowRenderManager::Unknown10715F50(int unknown)
	{
		if (mode != 3)
		{
			Setup(mode, unknown);
		}
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
