// What the Direct3D 9 back end remembers of the device's state so that it only sets what changed: the textures on
// the samplers, the texture sampler states and the default textures. Names are guesses.
#ifndef PURE3D_PDDI_DX9_DXDEVICESTATE_H
#define PURE3D_PDDI_DX9_DXDEVICESTATE_H

#include "code/pure3d/pddi/dx9/d3d9.h"
#include "code/pure3d/pddi/dx9/dxtexture.h"

namespace pure3d
{
	// The textures set on the samplers of the device (the object at 0x11276F44): the four vertex samplers, then
	// the sixteen pixel samplers; `changes` counts every texture that was set
	struct dxTextureSlotCache
	{
		void* vertexTextures[4];
		void* pixelTextures[16];
		int unknown50;
		int changes;
	};

	extern dxTextureSlotCache* gTextureSlotCache;
	// 0x11276F30: the default textures the device was given for a frame (black, white, flat normal, ramp, transparent;
	// 0x10628320 takes them from the globals, 0x10628360 lets go of them)
	extern dxTexture* gDefaultTextureSnapshot[5];

	// 0x10627FC0 / 0x10627FD0 / 0x10627FE0 / 0x10627FF0 / 0x10628000: the default textures
	dxTexture* GetBlackTexture();
	dxTexture* GetWhiteTexture();
	dxTexture* GetFlatNormalTexture();
	dxTexture* GetRampTexture();
	dxTexture* GetTransparentTexture();
	// 0x10628320 / 0x10628360
	void TakeDefaultTextureSnapshot();
	void ClearDefaultTextureSnapshot();

	// Set a texture on a vertex sampler (0x10628090; 0x10628110, 0x10628170 and 0x106281D0 take the plain, the cube
	// and the volume texture of a dxTexture) or on a pixel sampler (0x10628230, 0x10628280 and 0x106282D0) when it
	// is not set already
	void SetVertexSamplerTexture(IDirect3DDevice9* device, int sampler, void* texture);
	void SetVertexSamplerTexture2D(IDirect3DDevice9* device, int sampler, dxTexture* texture);
	void SetVertexSamplerTextureCube(IDirect3DDevice9* device, int sampler, dxTexture* texture);
	void SetVertexSamplerTextureVolume(IDirect3DDevice9* device, int sampler, dxTexture* texture);
	void SetPixelSamplerTexture2D(IDirect3DDevice9* device, int sampler, dxTexture* texture);
	void SetPixelSamplerTextureCube(IDirect3DDevice9* device, int sampler, dxTexture* texture);
	void SetPixelSamplerTextureVolume(IDirect3DDevice9* device, int sampler, dxTexture* texture);
	// 0x10628440 / 0x10628480: set a sampler state of a vertex or a pixel sampler when it is not set already
	void SetVertexSamplerState(IDirect3DDevice9* device, int sampler, int type, int value);
	void SetPixelSamplerState(IDirect3DDevice9* device, int sampler, int type, int value);

	// Keep a shader constant in the cache when the register does not hold it already (the device is given the
	// registers in a block when the cache is flushed). A constant of up to four numbers takes one register
	// (0x106284C0 for the vertex shader, 0x10628600 for the pixel shader; the count is of numbers), an array
	// of vectors takes as many registers as it has vectors (0x10628740 and 0x10628890)
	void SetVertexConstant(IDirect3DDevice9* device, int count, unsigned int reg, const void* data);
	void SetPixelConstant(IDirect3DDevice9* device, int count, unsigned int reg, const void* data);
	void SetVertexConstants(IDirect3DDevice9* device, unsigned int reg, const void* data, int vectors);
	void SetPixelConstants(IDirect3DDevice9* device, unsigned int reg, const void* data, int vectors);
	// 0x106289E0 / 0x10628A50: give the device the registers written since the last flush
	void FlushVertexConstants(IDirect3DDevice9* device);
	void FlushPixelConstants(IDirect3DDevice9* device);
}

#endif
