// The device state the Direct3D 9 back end caches (unit around 0x10627FB0 - 0x10628B00; the file name is guessed, no
// assert path survives).
#include <string.h>

#include "code/pure3d/pddi/dx9/dxcontext.h"
#include "code/pure3d/pddi/dx9/dxdevicestate.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x10627FC0
	dxTexture* GetBlackTexture()
	{
		return gBlackTexture;
	}

	// FUNCTION: ENGINE 0x10627FD0
	dxTexture* GetWhiteTexture()
	{
		return gWhiteTexture;
	}

	// FUNCTION: ENGINE 0x10627FE0
	dxTexture* GetFlatNormalTexture()
	{
		return gFlatNormalTexture;
	}

	// FUNCTION: ENGINE 0x10627FF0
	dxTexture* GetRampTexture()
	{
		return gRampTexture;
	}

	// FUNCTION: ENGINE 0x10628000
	dxTexture* GetTransparentTexture()
	{
		return gTransparentTexture;
	}

	// FUNCTION: ENGINE 0x10628320
	void TakeDefaultTextureSnapshot()
	{
		gDefaultTextureSnapshot[0] = gBlackTexture;
		gDefaultTextureSnapshot[1] = gWhiteTexture;
		gDefaultTextureSnapshot[2] = gFlatNormalTexture;
		gDefaultTextureSnapshot[3] = gRampTexture;
		gDefaultTextureSnapshot[4] = gTransparentTexture;
	}

	// FUNCTION: ENGINE 0x10628360
	void ClearDefaultTextureSnapshot()
	{
		gDefaultTextureSnapshot[0] = 0;
		gDefaultTextureSnapshot[1] = 0;
		gDefaultTextureSnapshot[2] = 0;
		gDefaultTextureSnapshot[3] = 0;
		gDefaultTextureSnapshot[4] = 0;
	}

	// FUNCTION: ENGINE 0x10628010 is dxTexture::GetDeviceTexture, FUNCTION: ENGINE 0x10628030 its cube texture and
	// FUNCTION: ENGINE 0x10628050 its volume texture (inline in the header; the unit keeps a copy of each)

	// FUNCTION: ENGINE 0x10628090
	void SetVertexSamplerTexture(IDirect3DDevice9* device, int sampler, void* texture)
	{
		if (gTextureSlotCache->vertexTextures[sampler] != texture)
		{
			device->lpVtbl->SetTexture(device, sampler + 0x101, texture);
			gTextureSlotCache->vertexTextures[sampler] = texture;
			gTextureSlotCache->changes++;
		}
	}

	// FUNCTION: ENGINE 0x10628110
	void SetVertexSamplerTexture2D(IDirect3DDevice9* device, int sampler, dxTexture* texture)
	{
		IDirect3DTexture9* d3dTexture = texture->GetDeviceTexture();
		if (gTextureSlotCache->vertexTextures[sampler] != d3dTexture)
		{
			device->lpVtbl->SetTexture(device, sampler + 0x101, d3dTexture);
			gTextureSlotCache->vertexTextures[sampler] = d3dTexture;
			gTextureSlotCache->changes++;
		}
	}

	// FUNCTION: ENGINE 0x10628170
	void SetVertexSamplerTextureCube(IDirect3DDevice9* device, int sampler, dxTexture* texture)
	{
		IDirect3DCubeTexture9* d3dTexture = texture->GetDeviceCubeTexture();
		if (gTextureSlotCache->vertexTextures[sampler] != d3dTexture)
		{
			device->lpVtbl->SetTexture(device, sampler + 0x101, d3dTexture);
			gTextureSlotCache->vertexTextures[sampler] = d3dTexture;
			gTextureSlotCache->changes++;
		}
	}

	// FUNCTION: ENGINE 0x106281D0
	void SetVertexSamplerTextureVolume(IDirect3DDevice9* device, int sampler, dxTexture* texture)
	{
		IDirect3DVolumeTexture9* d3dTexture = texture->GetDeviceVolumeTexture();
		if (gTextureSlotCache->vertexTextures[sampler] != d3dTexture)
		{
			device->lpVtbl->SetTexture(device, sampler + 0x101, d3dTexture);
			gTextureSlotCache->vertexTextures[sampler] = d3dTexture;
			gTextureSlotCache->changes++;
		}
	}

	// FUNCTION: ENGINE 0x10628230
	void SetPixelSamplerTexture2D(IDirect3DDevice9* device, int sampler, dxTexture* texture)
	{
		IDirect3DTexture9* d3dTexture = texture->GetDeviceTexture();
		if (gTextureSlotCache->pixelTextures[sampler] != d3dTexture)
		{
			device->lpVtbl->SetTexture(device, sampler, d3dTexture);
			gTextureSlotCache->pixelTextures[sampler] = d3dTexture;
			gTextureSlotCache->changes++;
		}
	}

	// FUNCTION: ENGINE 0x10628280
	void SetPixelSamplerTextureCube(IDirect3DDevice9* device, int sampler, dxTexture* texture)
	{
		IDirect3DCubeTexture9* d3dTexture = texture->GetDeviceCubeTexture();
		if (gTextureSlotCache->pixelTextures[sampler] != d3dTexture)
		{
			device->lpVtbl->SetTexture(device, sampler, d3dTexture);
			gTextureSlotCache->pixelTextures[sampler] = d3dTexture;
			gTextureSlotCache->changes++;
		}
	}

	// FUNCTION: ENGINE 0x106282D0
	void SetPixelSamplerTextureVolume(IDirect3DDevice9* device, int sampler, dxTexture* texture)
	{
		IDirect3DVolumeTexture9* d3dTexture = texture->GetDeviceVolumeTexture();
		if (gTextureSlotCache->pixelTextures[sampler] != d3dTexture)
		{
			device->lpVtbl->SetTexture(device, sampler, d3dTexture);
			gTextureSlotCache->pixelTextures[sampler] = d3dTexture;
			gTextureSlotCache->changes++;
		}
	}

	// FUNCTION: ENGINE 0x10628440
	void SetVertexSamplerState(IDirect3DDevice9* device, int sampler, int type, int value)
	{
		int* state = &gRenderStateCache->samplerStates[sampler][type];
		if (value != *state)
		{
			*state = value;
			device->lpVtbl->SetSamplerState(device, sampler + 0x101, type, value);
		}
	}

	// FUNCTION: ENGINE 0x10628480
	void SetPixelSamplerState(IDirect3DDevice9* device, int sampler, int type, int value)
	{
		int* state = &gRenderStateCache->samplerStates[sampler + 4][type];
		if (value != *state)
		{
			*state = value;
			device->lpVtbl->SetSamplerState(device, sampler, type, value);
		}
	}

	// FUNCTION: ENGINE 0x106284C0
	void SetVertexConstant(IDirect3DDevice9* device, int count, unsigned int reg, const void* data)
	{
		if (gRenderStateCache->vertexPass == gRenderStateCache->vertexConstantPasses[reg]
			&& memcmp(data, gRenderStateCache->vertexConstants[reg], count * 4) == 0)
		{
			gRenderStateCache->constantsSkipped++;
			return;
		}
		gRenderStateCache->vertexDirtyFirst = gRenderStateCache->vertexDirtyFirst < reg
			? gRenderStateCache->vertexDirtyFirst : reg;
		gRenderStateCache->vertexDirtyLast = gRenderStateCache->vertexDirtyLast < reg
			? reg : gRenderStateCache->vertexDirtyLast;
		memcpy(gRenderStateCache->vertexConstants[reg], data, count * 4);
		gRenderStateCache->vertexConstantPasses[reg] = gRenderStateCache->vertexPass;
		gRenderStateCache->constantsWritten++;
	}

	// FUNCTION: ENGINE 0x10628600
	void SetPixelConstant(IDirect3DDevice9* device, int count, unsigned int reg, const void* data)
	{
		if (gRenderStateCache->pixelPass == gRenderStateCache->pixelConstantPasses[reg]
			&& memcmp(data, gRenderStateCache->pixelConstants[reg], count * 4) == 0)
		{
			gRenderStateCache->constantsSkipped++;
			return;
		}
		gRenderStateCache->pixelDirtyFirst = gRenderStateCache->pixelDirtyFirst < reg
			? gRenderStateCache->pixelDirtyFirst : reg;
		gRenderStateCache->pixelDirtyLast = gRenderStateCache->pixelDirtyLast < reg
			? reg : gRenderStateCache->pixelDirtyLast;
		memcpy(gRenderStateCache->pixelConstants[reg], data, count * 4);
		gRenderStateCache->pixelConstantPasses[reg] = gRenderStateCache->pixelPass;
		gRenderStateCache->constantsWritten++;
	}

	// FUNCTION: ENGINE 0x10628740
	// EQUIVALENT: the byte compare of the inlined comparison and the move of the data pointer behind it are scheduled
	// in another order (80.3 %); the loads, the stores and the calls are the same
	void SetVertexConstants(IDirect3DDevice9* device, unsigned int reg, const void* data, int vectors)
	{
		if (gRenderStateCache->vertexPass == gRenderStateCache->vertexConstantPasses[reg]
			&& memcmp(data, gRenderStateCache->vertexConstants[reg], vectors * 16) == 0)
		{
			gRenderStateCache->constantsSkipped++;
			return;
		}
		gRenderStateCache->vertexDirtyFirst = gRenderStateCache->vertexDirtyFirst < reg
			? gRenderStateCache->vertexDirtyFirst : reg;
		gRenderStateCache->vertexDirtyLast = gRenderStateCache->vertexDirtyLast < reg + vectors
			? reg + vectors : gRenderStateCache->vertexDirtyLast;
		memcpy(gRenderStateCache->vertexConstants[reg], data, vectors * 16);
		gRenderStateCache->vertexConstantPasses[reg] = gRenderStateCache->vertexPass;
		gRenderStateCache->constantsWritten++;
	}

	// FUNCTION: ENGINE 0x10628890
	// EQUIVALENT: the byte compare of the inlined comparison loads its two bytes in the other order (97.5 %); the
	// loads, the stores and the calls are the same
	void SetPixelConstants(IDirect3DDevice9* device, unsigned int reg, const void* data, int vectors)
	{
		if (gRenderStateCache->pixelPass == gRenderStateCache->pixelConstantPasses[reg]
			&& memcmp(data, gRenderStateCache->pixelConstants[reg], vectors * 16) == 0)
		{
			gRenderStateCache->constantsSkipped++;
			return;
		}
		gRenderStateCache->pixelDirtyFirst = gRenderStateCache->pixelDirtyFirst < reg
			? gRenderStateCache->pixelDirtyFirst : reg;
		gRenderStateCache->pixelDirtyLast = gRenderStateCache->pixelDirtyLast < reg + vectors
			? reg + vectors : gRenderStateCache->pixelDirtyLast;
		memcpy(gRenderStateCache->pixelConstants[reg], data, vectors * 16);
		gRenderStateCache->pixelConstantPasses[reg] = gRenderStateCache->pixelPass;
		gRenderStateCache->constantsWritten++;
	}

	// FUNCTION: ENGINE 0x106289E0
	void FlushVertexConstants(IDirect3DDevice9* device)
	{
		if (gRenderStateCache->vertexDirtyFirst <= gRenderStateCache->vertexDirtyLast)
		{
			device->lpVtbl->SetVertexShaderConstantF(device, gRenderStateCache->vertexDirtyFirst,
				gRenderStateCache->vertexConstants[gRenderStateCache->vertexDirtyFirst],
				gRenderStateCache->vertexDirtyLast - gRenderStateCache->vertexDirtyFirst + 1);
			gRenderStateCache->vertexDirtyFirst = 0x400;
			gRenderStateCache->vertexDirtyLast = 0;
		}
	}

	// FUNCTION: ENGINE 0x10628A50
	void FlushPixelConstants(IDirect3DDevice9* device)
	{
		if (gRenderStateCache->pixelDirtyFirst <= gRenderStateCache->pixelDirtyLast)
		{
			device->lpVtbl->SetPixelShaderConstantF(device, gRenderStateCache->pixelDirtyFirst,
				gRenderStateCache->pixelConstants[gRenderStateCache->pixelDirtyFirst],
				gRenderStateCache->pixelDirtyLast - gRenderStateCache->pixelDirtyFirst + 1);
			gRenderStateCache->pixelDirtyFirst = 0x400;
			gRenderStateCache->pixelDirtyLast = 0;
		}
	}
}
