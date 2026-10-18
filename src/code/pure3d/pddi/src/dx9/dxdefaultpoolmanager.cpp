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
