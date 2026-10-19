// pure3d's default pool: what the back end makes in Direct3D's default pool (the pool a device reset empties) is
// recorded here and made again after the reset. The file name is the assert path of 0x106238B0 and 0x10623FB0.
#include <string.h>

#include "code/core/criticalsection.h"
#include "code/core/report.h"
#include "code/engine/display.h"
#include "code/pure3d/pddi/dx9/dxdefaultpoolmanager.h"
#include "code/pure3d/primitive.h"
#include "code/pure3d/shadows/shadowrendermanager.h"

// The one kernel32 call the pool's failure report makes (declared here as thread.cpp declares its imports)
extern "C"
{
	struct MEMORYSTATUS
	{
		unsigned long dwLength;
		unsigned long dwMemoryLoad;
		unsigned long dwTotalPhys;
		unsigned long dwAvailPhys;
		unsigned long dwTotalPageFile;
		unsigned long dwAvailPageFile;
		unsigned long dwTotalVirtual;
		unsigned long dwAvailVirtual;
	};

	__declspec(dllimport) void __stdcall GlobalMemoryStatus(MEMORYSTATUS* status);
}
#pragma comment(linker, "/alternatename:__imp__GlobalMemoryStatus@4=__imp__GlobalMemoryStatus")

namespace pure3d
{
	// GLOBAL: ENGINE 0x110BB75C
	// Switched off for good once the report has been answered with 3
	static bool sReportAllocationFailure = true;

	// The factor the report shows the byte counts in: one megabyte (the engine keeps it at 0x10E34590)
	static const float kMegabyte = 9.5367431640625e-07f;

	// FUNCTION: ENGINE 0x10623860
	static const char* GetErrorText(HRESULT result)
	{
		switch (result)
		{
		case D3DERR_NOTAVAILABLE:
			return "D3DERR_NOTAVAILABLE";
		case E_OUTOFMEMORY:
			return "E_OUTOFMEMORY";
		case D3DERR_OUTOFVIDEOMEMORY:
			return "D3DERR_OUTOFVIDEOMEMORY";
		case D3DERR_INVALIDCALL:
			return "D3DERR_INVALIDCALL";
		case D3DXERR_INVALIDDATA:
			return "D3DXERR_INVALIDDATA";
		}
		return "Unknown";
	}

	// FUNCTION: ENGINE 0x106238B0
	static void ReportAllocationFailure(HRESULT result, const char* name)
	{
		MEMORYSTATUS status;
		if (result != 0)
		{
			UINT available = gD3DDevice->lpVtbl->GetAvailableTextureMem(gD3DDevice);
			GlobalMemoryStatus(&status);
			if (sReportAllocationFailure)
			{
				if (core::Report(1, " oldassert ",
						"..\\..\\..\\code\\pure3d\\pddi\\src\\dx9\\dxdefaultpoolmanager.cpp", 0x36,
						"res == ((HRESULT)0x00000000L)",
						"Could not allocate %s\nD3D Error : %s\nAvalible video memory : %.2f\nWindows memory status - load:%d phys:%.2f availphys:%.2f\n    page:%.2f availpage:%.2f virt:%.2f availvirt:%.2f\nIf this assert occurs during an Alt-Tab it may be spurious\nQA, please try to continue and report if a crash occurs after\ncontinuing (ideally with a callstack), rather than just reporting\nthis assert",
						name, GetErrorText(result), (float)available * kMegabyte, status.dwMemoryLoad,
						(float)status.dwTotalPhys * kMegabyte, (float)status.dwAvailPhys * kMegabyte,
						(float)status.dwTotalPageFile * kMegabyte, (float)status.dwAvailPageFile * kMegabyte,
						(float)status.dwTotalVirtual * kMegabyte, (float)status.dwAvailVirtual * kMegabyte, 0) == 3)
				{
					sReportAllocationFailure = false;
				}
			}
		}
	}

	// Room for count elements: the array comes back empty when the allocation fails (the order of the stores is the
	// constructor's, not Create's)
	template<class T> static inline void AllocateArray(container::ArrayDynamicNew<T>& array, unsigned int count)
	{
		array.begin = (T*)operator new[](count * sizeof(T));
		if (array.begin != 0)
		{
			array.end = array.begin;
			array.capacity = array.begin + count;
		}
		else
		{
			array.end = 0;
			array.capacity = 0;
		}
	}

	// FUNCTION: ENGINE 0x10625310
	dxDefaultPoolManager::dxDefaultPoolManager(IDirect3DDevice9* newDevice)
	{
		device = newDevice;
		device->lpVtbl->AddRef(device);
		released = false;
		AllocateArray(textures, 0x40);
		AllocateArray(vertexBuffers, 50000);
		AllocateArray(indexBuffers, 50000);
		AllocateArray(renderTargets, 0x40);
		AllocateArray(depthStencils, 8);
	}

	// Deletes every entry of an array and the array itself
	template<class T> static __forceinline void DeleteEntries(container::ArrayDynamicNew<T*>& array)
	{
		for (unsigned int i = 0; i < array.Size(); i++)
		{
			if (array[i] != 0)
			{
				delete array[i];
				array[i] = 0;
			}
		}
		array.Free();
	}

	// FUNCTION: ENGINE 0x10625420
	dxDefaultPoolManager::~dxDefaultPoolManager()
	{
		ReleaseDefaultPool();
		DeleteEntries(indexBuffers);
		DeleteEntries(vertexBuffers);
		DeleteEntries(textures);
		DeleteEntries(renderTargets);
		DeleteEntries(depthStencils);
		device->lpVtbl->Release(device);
	}

	// FUNCTION: ENGINE 0x10625640 is the compiler's scalar deleting destructor of the manager (ShutdownDefaultPool's
	// delete makes it)

	// FUNCTION: ENGINE 0x10625660
	void ShutdownDefaultPool()
	{
		if (gDefaultPoolManager != 0)
		{
			ReleaseDefaultPool();
			delete gDefaultPoolManager;
			gDefaultPoolManager = 0;
		}
		core::CriticalSectionDelete(gDefaultPoolLock);
	}

	// FUNCTION: ENGINE 0x106256A0
	void Unknown106256A0(IDirect3DDevice9* device)
	{
		core::CriticalSectionInit(gDefaultPoolLock);
		if (gDefaultPoolManager == 0)
		{
			gDefaultPoolManager = new dxDefaultPoolManager(device);
		}
		else
		{
			ShutdownDefaultPool();
			gDefaultPoolManager = new dxDefaultPoolManager(device);
		}
	}

	// FUNCTION: ENGINE 0x10624990
	bool PoolAllocateTexture(int width, int height, int levels, int usage, unsigned int format,
		IDirect3DTexture9** texture, IDirect3DSurface9** surface, float scale)
	{
		core::CriticalSectionEnter(gDefaultPoolLock);
		HRESULT result = gDefaultPoolManager->device->lpVtbl->CreateTexture(gDefaultPoolManager->device, width,
			height, levels, usage, format, D3DPOOL_DEFAULT, texture, 0);
		ReportAllocationFailure(result, "texture");
		DefaultPoolTexture* entry = new DefaultPoolTexture;
		entry->width = width;
		entry->height = height;
		entry->levels = levels;
		entry->usage = usage;
		entry->format = format;
		entry->texture = texture;
		entry->scale = scale;
		entry->surface = surface;
		if (surface != 0 && texture != 0)
		{
			(*texture)->lpVtbl->GetSurfaceLevel(*texture, 0, surface);
		}
		gDefaultPoolManager->textures.PushBack(entry);
		core::CriticalSectionLeave(gDefaultPoolLock);
		return true;
	}

	// FUNCTION: ENGINE 0x10624A70
	bool PoolAllocateVertexBuffer(int length, unsigned int usage, unsigned int fvf,
		IDirect3DVertexBuffer9** buffer, void* data)
	{
		core::CriticalSectionEnter(gDefaultPoolLock);
		HRESULT result = gDefaultPoolManager->device->lpVtbl->CreateVertexBuffer(gDefaultPoolManager->device,
			length, usage, fvf, D3DPOOL_DEFAULT, buffer, 0);
		ReportAllocationFailure(result, "vertex buffer");
		DefaultPoolVertexBuffer* entry = new DefaultPoolVertexBuffer;
		entry->length = length;
		entry->usage = usage;
		entry->fvf = fvf;
		entry->buffer = buffer;
		entry->data = data;
		gDefaultPoolManager->vertexBuffers.PushBack(entry);
		core::CriticalSectionLeave(gDefaultPoolLock);
		return true;
	}

	// FUNCTION: ENGINE 0x10624B10
	bool PoolAllocateIndexBuffer(int length, unsigned int usage, unsigned int format,
		IDirect3DIndexBuffer9** buffer)
	{
		core::CriticalSectionEnter(gDefaultPoolLock);
		HRESULT result = gDefaultPoolManager->device->lpVtbl->CreateIndexBuffer(gDefaultPoolManager->device,
			length, usage, format, D3DPOOL_DEFAULT, buffer, 0);
		ReportAllocationFailure(result, "index buffer");
		DefaultPoolIndexBuffer* entry = new DefaultPoolIndexBuffer;
		entry->length = length;
		entry->usage = usage;
		entry->format = format;
		entry->buffer = buffer;
		gDefaultPoolManager->indexBuffers.PushBack(entry);
		core::CriticalSectionLeave(gDefaultPoolLock);
		return true;
	}

	// FUNCTION: ENGINE 0x10624BA0
	bool PoolAllocateRenderTarget(int width, int height, unsigned int format, unsigned int multiSample,
		bool lockable, IDirect3DSurface9** surface, float scale)
	{
		core::CriticalSectionEnter(gDefaultPoolLock);
		HRESULT result = gDefaultPoolManager->device->lpVtbl->CreateRenderTarget(gDefaultPoolManager->device,
			width, height, format, multiSample, 0, lockable, surface, 0);
		ReportAllocationFailure(result, "render target");
		DefaultPoolRenderTarget* entry = new DefaultPoolRenderTarget;
		entry->width = width;
		entry->height = height;
		entry->scale = scale;
		entry->format = format;
		entry->lockable = lockable;
		entry->multiSample = multiSample;
		entry->surface = surface;
		gDefaultPoolManager->renderTargets.PushBack(entry);
		core::CriticalSectionLeave(gDefaultPoolLock);
		return true;
	}

	// FUNCTION: ENGINE 0x10624C60
	bool PoolAllocateDepthStencil(int width, int height, unsigned int format, unsigned int multiSample,
		IDirect3DSurface9** surface, float scale)
	{
		core::CriticalSectionEnter(gDefaultPoolLock);
		HRESULT result = gDefaultPoolManager->device->lpVtbl->CreateDepthStencilSurface(
			gDefaultPoolManager->device, width, height, format, multiSample, 0, 0, surface, 0);
		ReportAllocationFailure(result, "depth/stencil surface");
		DefaultPoolDepthStencil* entry = new DefaultPoolDepthStencil;
		entry->width = width;
		entry->height = height;
		entry->scale = scale;
		entry->format = format;
		entry->multiSample = multiSample;
		entry->surface = surface;
		gDefaultPoolManager->depthStencils.PushBack(entry);
		core::CriticalSectionLeave(gDefaultPoolLock);
		return true;
	}

	// FUNCTION: ENGINE 0x10624D10
	void FreePooledTexture(IDirect3DTexture9** texture)
	{
		core::CriticalSectionEnter(gDefaultPoolLock);
		unsigned int index = 0;
		unsigned int count = gDefaultPoolManager->textures.Size();
		while (index < count)
		{
			if (gDefaultPoolManager->textures[index]->texture == texture)
			{
				if (*gDefaultPoolManager->textures[index]->texture != 0)
				{
					(*gDefaultPoolManager->textures[index]->texture)->Release();
					if (gDefaultPoolManager->textures[index]->surface != 0)
					{
						(*gDefaultPoolManager->textures[index]->surface)->Release();
					}
				}
				delete gDefaultPoolManager->textures[index];
				gDefaultPoolManager->textures[index] = 0;
				gDefaultPoolManager->textures.Remove(&gDefaultPoolManager->textures[index]);
				break;
			}
			index++;
		}
		core::CriticalSectionLeave(gDefaultPoolLock);
	}

	// FUNCTION: ENGINE 0x10624DF0
	void FreePooledVertexBuffer(IDirect3DVertexBuffer9** buffer)
	{
		core::CriticalSectionEnter(gDefaultPoolLock);
		unsigned int index = 0;
		while (index < gDefaultPoolManager->vertexBuffers.Size())
		{
			if (gDefaultPoolManager->vertexBuffers[index]->buffer == buffer)
			{
				if (*gDefaultPoolManager->vertexBuffers[index]->buffer != 0)
				{
					(*gDefaultPoolManager->vertexBuffers[index]->buffer)->Release();
				}
				delete gDefaultPoolManager->vertexBuffers[index];
				gDefaultPoolManager->vertexBuffers[index] = 0;
				gDefaultPoolManager->vertexBuffers.Remove(&gDefaultPoolManager->vertexBuffers[index]);
				break;
			}
			index++;
		}
		core::CriticalSectionLeave(gDefaultPoolLock);
	}

	// FUNCTION: ENGINE 0x10624EC0
	void FreePooledIndexBuffer(IDirect3DIndexBuffer9** buffer)
	{
		core::CriticalSectionEnter(gDefaultPoolLock);
		unsigned int index = 0;
		while (index < gDefaultPoolManager->indexBuffers.Size())
		{
			if (gDefaultPoolManager->indexBuffers[index]->buffer == buffer)
			{
				if (*gDefaultPoolManager->indexBuffers[index]->buffer != 0)
				{
					(*gDefaultPoolManager->indexBuffers[index]->buffer)->Release();
				}
				delete gDefaultPoolManager->indexBuffers[index];
				gDefaultPoolManager->indexBuffers[index] = 0;
				gDefaultPoolManager->indexBuffers.Remove(&gDefaultPoolManager->indexBuffers[index]);
				break;
			}
			index++;
		}
		core::CriticalSectionLeave(gDefaultPoolLock);
	}

	// FUNCTION: ENGINE 0x10624F90
	void FreePooledRenderTarget(IDirect3DSurface9** surface)
	{
		core::CriticalSectionEnter(gDefaultPoolLock);
		unsigned int index = 0;
		while (index < gDefaultPoolManager->renderTargets.Size())
		{
			if (gDefaultPoolManager->renderTargets[index]->surface == surface)
			{
				if (*gDefaultPoolManager->renderTargets[index]->surface != 0)
				{
					(*gDefaultPoolManager->renderTargets[index]->surface)->Release();
				}
				delete gDefaultPoolManager->renderTargets[index];
				gDefaultPoolManager->renderTargets[index] = 0;
				gDefaultPoolManager->renderTargets.Remove(&gDefaultPoolManager->renderTargets[index]);
				break;
			}
			index++;
		}
		core::CriticalSectionLeave(gDefaultPoolLock);
	}

	// FUNCTION: ENGINE 0x10625060
	void FreePooledDepthStencil(IDirect3DSurface9** surface)
	{
		core::CriticalSectionEnter(gDefaultPoolLock);
		unsigned int index = 0;
		while (index < gDefaultPoolManager->depthStencils.Size())
		{
			if (gDefaultPoolManager->depthStencils[index]->surface == surface)
			{
				if (*gDefaultPoolManager->depthStencils[index]->surface != 0)
				{
					(*gDefaultPoolManager->depthStencils[index]->surface)->Release();
				}
				delete gDefaultPoolManager->depthStencils[index];
				gDefaultPoolManager->depthStencils[index] = 0;
				gDefaultPoolManager->depthStencils.Remove(&gDefaultPoolManager->depthStencils[index]);
				break;
			}
			index++;
		}
		core::CriticalSectionLeave(gDefaultPoolLock);
	}

	// FUNCTION: ENGINE 0x10623DB0
	void ReleaseDefaultPool()
	{
		if (!gDefaultPoolManager->released)
		{
			core::CriticalSectionEnter(gDefaultPoolLock);
			if (GetParticleManager() != 0)
			{
				GetParticleManager()->Unknown106EDA30();
			}
			for (unsigned int i = 0; i < gDefaultPoolManager->textures.Size(); i++)
			{
				if (gDefaultPoolManager->textures[i]->surface != 0)
				{
					(*gDefaultPoolManager->textures[i]->surface)->Release();
				}
				if (gDefaultPoolManager->textures[i]->texture != 0)
				{
					(*gDefaultPoolManager->textures[i]->texture)->Release();
				}
				*gDefaultPoolManager->textures[i]->texture = 0;
			}
			for (unsigned int i = 0; i < gDefaultPoolManager->vertexBuffers.Size(); i++)
			{
				if (*gDefaultPoolManager->vertexBuffers[i]->buffer != 0)
				{
					ULONG references;
					do
					{
						references = (*gDefaultPoolManager->vertexBuffers[i]->buffer)->Release();
					}
					while (references > 0);
				}
				*gDefaultPoolManager->vertexBuffers[i]->buffer = 0;
			}
			for (unsigned int i = 0; i < gDefaultPoolManager->indexBuffers.Size(); i++)
			{
				if (*gDefaultPoolManager->indexBuffers[i]->buffer != 0)
				{
					(*gDefaultPoolManager->indexBuffers[i]->buffer)->Release();
				}
				*gDefaultPoolManager->indexBuffers[i]->buffer = 0;
			}
			for (unsigned int i = 0; i < gDefaultPoolManager->renderTargets.Size(); i++)
			{
				if (*gDefaultPoolManager->renderTargets[i]->surface != 0)
				{
					(*gDefaultPoolManager->renderTargets[i]->surface)->Release();
				}
				*gDefaultPoolManager->renderTargets[i]->surface = 0;
			}
			for (unsigned int i = 0; i < gDefaultPoolManager->depthStencils.Size(); i++)
			{
				(*gDefaultPoolManager->depthStencils[i]->surface)->Release();
				*gDefaultPoolManager->depthStencils[i]->surface = 0;
			}
			gDefaultPoolManager->released = true;
			core::CriticalSectionLeave(gDefaultPoolLock);
		}
	}

	// The texture made again gets its first level's surface back
	static inline void RemakeTextureSurface(unsigned int i)
	{
		if (*gDefaultPoolManager->textures[i]->texture != 0
			&& gDefaultPoolManager->textures[i]->surface != 0)
		{
			(*gDefaultPoolManager->textures[i]->texture)->lpVtbl->GetSurfaceLevel(
				*gDefaultPoolManager->textures[i]->texture, 0, gDefaultPoolManager->textures[i]->surface);
		}
	}

	// FUNCTION: ENGINE 0x10623FB0
	// The surface fix-up behind a texture's creation is expanded in both branches, as the engine has it, and the
	// vertex buffer's output pointer is read through the array's first element: with the plain element access
	// this compiler turns the operands of a later address (the depth/stencil loop's) around.
	void RestoreDefaultPool()
	{
		if (gDefaultPoolManager->released)
		{
			core::CriticalSectionEnter(gDefaultPoolLock);
			for (unsigned int i = 0; i < gDefaultPoolManager->textures.Size(); i++)
			{
				if (gDefaultPoolManager->textures[i]->scale == 0.0f)
				{
					HRESULT result = gDefaultPoolManager->device->lpVtbl->CreateTexture(
						gDefaultPoolManager->device, gDefaultPoolManager->textures[i]->width,
						gDefaultPoolManager->textures[i]->height, gDefaultPoolManager->textures[i]->levels,
						gDefaultPoolManager->textures[i]->usage, gDefaultPoolManager->textures[i]->format,
						D3DPOOL_DEFAULT, gDefaultPoolManager->textures[i]->texture, 0);
					ReportAllocationFailure(result, "texture");
					RemakeTextureSurface(i);
				}
				else
				{
					HRESULT result = gDefaultPoolManager->device->lpVtbl->CreateTexture(
						gDefaultPoolManager->device,
						(unsigned int)((double)engine::gDisplay->GetWidth()
							* gDefaultPoolManager->textures[i]->scale),
						(unsigned int)((double)engine::gDisplay->GetUnknown8()
							* gDefaultPoolManager->textures[i]->scale),
						gDefaultPoolManager->textures[i]->levels, gDefaultPoolManager->textures[i]->usage,
						gDefaultPoolManager->textures[i]->format, D3DPOOL_DEFAULT,
						gDefaultPoolManager->textures[i]->texture, 0);
					ReportAllocationFailure(result, "texture");
					RemakeTextureSurface(i);
				}
			}
			for (unsigned int i = 0; i < gDefaultPoolManager->vertexBuffers.Size(); i++)
			{
				HRESULT result = gDefaultPoolManager->device->lpVtbl->CreateVertexBuffer(
					gDefaultPoolManager->device, gDefaultPoolManager->vertexBuffers[i]->length,
					gDefaultPoolManager->vertexBuffers[i]->usage, gDefaultPoolManager->vertexBuffers[i]->fvf,
					D3DPOOL_DEFAULT, gDefaultPoolManager->vertexBuffers.Begin()[i]->buffer, 0);
				ReportAllocationFailure(result, "vertex buffer");
				if (gDefaultPoolManager->vertexBuffers[i]->data != 0)
				{
					void* data = 0;
					IDirect3DVertexBuffer9* vertexBuffer = *gDefaultPoolManager->vertexBuffers[i]->buffer;
					HRESULT lockResult = vertexBuffer->lpVtbl->Lock(vertexBuffer, 0, 0, &data, D3DLOCK_DISCARD);
					ReportAllocationFailure(lockResult, "vertex buffer");
					memcpy(data, gDefaultPoolManager->vertexBuffers[i]->data,
						gDefaultPoolManager->vertexBuffers[i]->length);
					(*gDefaultPoolManager->vertexBuffers[i]->buffer)->lpVtbl->Unlock(
						*gDefaultPoolManager->vertexBuffers[i]->buffer);
				}
			}
			for (unsigned int i = 0; i < gDefaultPoolManager->indexBuffers.Size(); i++)
			{
				HRESULT result = gDefaultPoolManager->device->lpVtbl->CreateIndexBuffer(
					gDefaultPoolManager->device, gDefaultPoolManager->indexBuffers[i]->length,
					gDefaultPoolManager->indexBuffers[i]->usage, gDefaultPoolManager->indexBuffers[i]->format,
					D3DPOOL_DEFAULT, gDefaultPoolManager->indexBuffers[i]->buffer, 0);
				ReportAllocationFailure(result, "index buffer");
			}
			for (unsigned int i = 0; i < gDefaultPoolManager->renderTargets.Size(); i++)
			{
				gDefaultPoolManager->renderTargets[i]->multiSample =
					GetMultiSampleType(engine::gRenderDisplay->GetUnknown28());
				if (gDefaultPoolManager->renderTargets[i]->scale == 0.0f)
				{
					HRESULT result = gDefaultPoolManager->device->lpVtbl->CreateRenderTarget(
						gDefaultPoolManager->device, gDefaultPoolManager->renderTargets[i]->width,
						gDefaultPoolManager->renderTargets[i]->height, gDefaultPoolManager->renderTargets[i]->format,
						gDefaultPoolManager->renderTargets[i]->multiSample, 0,
						gDefaultPoolManager->renderTargets[i]->lockable,
						gDefaultPoolManager->renderTargets[i]->surface, 0);
					ReportAllocationFailure(result, "render target");
				}
				else
				{
					HRESULT result = gDefaultPoolManager->device->lpVtbl->CreateRenderTarget(
						gDefaultPoolManager->device,
						(unsigned int)((double)engine::gDisplay->GetWidth()
							* gDefaultPoolManager->renderTargets[i]->scale),
						(unsigned int)((double)engine::gDisplay->GetUnknown8()
							* gDefaultPoolManager->renderTargets[i]->scale),
						gDefaultPoolManager->renderTargets[i]->format,
						gDefaultPoolManager->renderTargets[i]->multiSample, 0,
						gDefaultPoolManager->renderTargets[i]->lockable,
						gDefaultPoolManager->renderTargets[i]->surface, 0);
					ReportAllocationFailure(result, "render target");
				}
			}
			for (unsigned int i = 0; i < gDefaultPoolManager->depthStencils.Size(); i++)
			{
				gDefaultPoolManager->depthStencils[i]->multiSample =
					GetMultiSampleType(engine::gRenderDisplay->GetUnknown28());
				if (gDefaultPoolManager->depthStencils[i]->scale == 0.0f)
				{
					HRESULT result = gDefaultPoolManager->device->lpVtbl->CreateDepthStencilSurface(
						gDefaultPoolManager->device, gDefaultPoolManager->depthStencils[i]->width,
						gDefaultPoolManager->depthStencils[i]->height, gDefaultPoolManager->depthStencils[i]->format,
						gDefaultPoolManager->depthStencils[i]->multiSample, 0, 0,
						gDefaultPoolManager->depthStencils[i]->surface, 0);
					ReportAllocationFailure(result, "depth/stencil surface");
				}
				else
				{
					HRESULT result = gDefaultPoolManager->device->lpVtbl->CreateDepthStencilSurface(
						gDefaultPoolManager->device,
						(unsigned int)((double)engine::gDisplay->GetWidth()
							* gDefaultPoolManager->depthStencils[i]->scale),
						(unsigned int)((double)engine::gDisplay->GetUnknown8()
							* gDefaultPoolManager->depthStencils[i]->scale),
						gDefaultPoolManager->depthStencils[i]->format,
						gDefaultPoolManager->depthStencils[i]->multiSample, 0, 0,
						gDefaultPoolManager->depthStencils[i]->surface, 0);
					ReportAllocationFailure(result, "depth/stencil surface");
				}
			}
			core::CriticalSectionLeave(gDefaultPoolLock);
			if (GetParticleManager() != 0)
			{
				GetParticleManager()->Unknown106EE500();
				GetParticleManager()->Unknown106EEC50(engine::gRenderDisplay->GetUnknown28());
			}
			ShadowRenderManager::Get()->Unknown10715F30();
			gDefaultPoolManager->released = false;
		}
	}
}

namespace container
{
	// The arrays' members the unit keeps (one copy per array): the default constructor, destructor, Size, the element
	// access, PushBack, Remove, Free, Clear, Create and Allocate, and the ConstructAt of the elements
	// FUNCTION: ENGINE 0x106239F0
	// FUNCTION: ENGINE 0x10623A00
	// FUNCTION: ENGINE 0x10623A10
	// FUNCTION: ENGINE 0x10623A20
	// FUNCTION: ENGINE 0x10623A30
	// FUNCTION: ENGINE 0x10623A40
	// FUNCTION: ENGINE 0x10623A50
	// FUNCTION: ENGINE 0x10623A60
	// FUNCTION: ENGINE 0x10623A70
	// FUNCTION: ENGINE 0x10623A80
	// FUNCTION: ENGINE 0x10623A90
	// FUNCTION: ENGINE 0x10623B00
	// FUNCTION: ENGINE 0x10623B70
	// FUNCTION: ENGINE 0x10623BE0
	// FUNCTION: ENGINE 0x10623C50
	// FUNCTION: ENGINE 0x10623CC0
	// FUNCTION: ENGINE 0x10623CF0
	// FUNCTION: ENGINE 0x10623D20
	// FUNCTION: ENGINE 0x10623D50
	// FUNCTION: ENGINE 0x10623D80
	// FUNCTION: ENGINE 0x106245D0
	// FUNCTION: ENGINE 0x106245E0
	// FUNCTION: ENGINE 0x10624630
	// FUNCTION: ENGINE 0x10624660
	// FUNCTION: ENGINE 0x10624680
	// FUNCTION: ENGINE 0x10624690
	// FUNCTION: ENGINE 0x106246E0
	// FUNCTION: ENGINE 0x10624710
	// FUNCTION: ENGINE 0x10624730
	// FUNCTION: ENGINE 0x10624740
	// FUNCTION: ENGINE 0x10624790
	// FUNCTION: ENGINE 0x106247C0
	// FUNCTION: ENGINE 0x106247E0
	// FUNCTION: ENGINE 0x106247F0
	// FUNCTION: ENGINE 0x10624840
	// FUNCTION: ENGINE 0x10624870
	// FUNCTION: ENGINE 0x10624890
	// FUNCTION: ENGINE 0x106248A0
	// FUNCTION: ENGINE 0x106248F0
	// FUNCTION: ENGINE 0x10624920
	// FUNCTION: ENGINE 0x10625130
	// FUNCTION: ENGINE 0x10625160
	// FUNCTION: ENGINE 0x10625190
	// FUNCTION: ENGINE 0x106251C0
	// FUNCTION: ENGINE 0x106251F0
	// FUNCTION: ENGINE 0x10625220
	// FUNCTION: ENGINE 0x10625230
	// FUNCTION: ENGINE 0x10625240
	// FUNCTION: ENGINE 0x10625250
	// FUNCTION: ENGINE 0x10625260
	// FUNCTION: ENGINE 0x10625270
	// FUNCTION: ENGINE 0x10625290
	// FUNCTION: ENGINE 0x106252B0
	// FUNCTION: ENGINE 0x106252D0
	// FUNCTION: ENGINE 0x106252F0
	template class ArrayDynamicNew<pure3d::DefaultPoolTexture*>;
	template class ArrayDynamicNew<pure3d::DefaultPoolVertexBuffer*>;
	template class ArrayDynamicNew<pure3d::DefaultPoolIndexBuffer*>;
	template class ArrayDynamicNew<pure3d::DefaultPoolRenderTarget*>;
	template class ArrayDynamicNew<pure3d::DefaultPoolDepthStencil*>;
}
