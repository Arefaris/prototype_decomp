// pure3d's default pool (the file name is the assert path of 0x106238B0 and 0x10623FB0,
// code/pure3d/pddi/src/dx9/dxdefaultpoolmanager.cpp). Direct3D's default pool loses every resource when the device
// is reset, so each resource the back end makes there is recorded here with what it was made from: 0x10623DB0
// releases them all before the reset and 0x10623FB0 makes them again after it (engine::Display 0x10616BB0 and
// 0x106182C0 call the two around their swaps). The class name and every member name are guesses; the entry layouts
// are what 0x10624990 - 0x10624C60 write.
#ifndef PURE3D_PDDI_DX9_DXDEFAULTPOOLMANAGER_H
#define PURE3D_PDDI_DX9_DXDEFAULTPOOLMANAGER_H

#include "code/container/arraydynamicnew.h"
#include "code/pure3d/pddi/dx9/d3d9.h"

namespace pure3d
{
	// A texture the device made in the default pool (0x20 bytes)
	struct DefaultPoolTexture
	{
		int width;
		int height;
		int levels;
		// The fraction of the display's width and height it is made with again (1.0 for the size it was asked for)
		float scale;
		int usage;
		unsigned int format;
		// The caller's handle, so that the recreated texture lands in the same place
		IDirect3DTexture9** texture;
		IDirect3DSurface9** surface;
	};

	// A vertex buffer the device made in the default pool (0x14 bytes)
	struct DefaultPoolVertexBuffer
	{
		unsigned int length;
		unsigned int usage;
		unsigned int fvf;
		IDirect3DVertexBuffer9** buffer;
		// The bytes to copy back into the recreated buffer (null when there are none)
		void* data;
	};

	// An index buffer the device made in the default pool (0x10 bytes)
	struct DefaultPoolIndexBuffer
	{
		unsigned int length;
		unsigned int usage;
		unsigned int format;
		IDirect3DIndexBuffer9** buffer;
	};

	// A render target the device made in the default pool (0x1C bytes)
	struct DefaultPoolRenderTarget
	{
		int width;
		int height;
		float scale;
		bool lockable;
		unsigned int format;
		unsigned int multiSample;
		IDirect3DSurface9** surface;
	};

	// A depth/stencil surface the device made in the default pool (0x18 bytes)
	struct DefaultPoolDepthStencil
	{
		int width;
		int height;
		float scale;
		unsigned int format;
		unsigned int multiSample;
		IDirect3DSurface9** surface;
	};

	// 0x11276DA4: the one manager, installed by the back end's creation. Its five arrays sit 0x10 bytes apart (the
	// device is at +0x50), so the array object the engine instantiates here is a word wider than the shared
	// container::ArrayDynamicNew; that fourth word is never read or written (the same padding the Lua script
	// manager's own arrays carry).
	class dxDefaultPoolManager
	{
	public:
		container::ArrayDynamicNew<DefaultPoolTexture*> textures;              // +0x00
		int unknownC;                                                          // +0x0C
		container::ArrayDynamicNew<DefaultPoolVertexBuffer*> vertexBuffers;    // +0x10
		int unknown1C;                                                         // +0x1C
		container::ArrayDynamicNew<DefaultPoolIndexBuffer*> indexBuffers;      // +0x20
		int unknown2C;                                                         // +0x2C
		container::ArrayDynamicNew<DefaultPoolRenderTarget*> renderTargets;    // +0x30
		int unknown3C;                                                         // +0x3C
		container::ArrayDynamicNew<DefaultPoolDepthStencil*> depthStencils;    // +0x40
		int unknown4C;                                                         // +0x4C
		IDirect3DDevice9* device;                                              // +0x50
		// Set while the default pool has been emptied and the resources are not made again yet
		bool released;                                                         // +0x54
	};

	extern dxDefaultPoolManager* gDefaultPoolManager;

	// 0x11276D8C: the lock every default pool operation holds
	extern unsigned char gDefaultPoolLock[0x18];

	// 0x10624990 / 0x10624A70 / 0x10624B10 / 0x10624BA0 / 0x10624C60: make one resource in the default pool and
	// record it. The handle the caller asked for lands in the texture/vertex buffer/index buffer/surface the pool
	// was handed a pointer to.
	bool PoolAllocateTexture(int width, int height, int levels, int usage, unsigned int format,
		IDirect3DTexture9** texture, IDirect3DSurface9** surface, float scale);
	bool PoolAllocateVertexBuffer(int length, unsigned int usage, unsigned int fvf,
		IDirect3DVertexBuffer9** buffer, void* data);
	bool PoolAllocateIndexBuffer(int length, unsigned int usage, unsigned int format,
		IDirect3DIndexBuffer9** buffer);
	bool PoolAllocateRenderTarget(int width, int height, unsigned int format, unsigned int multiSample, bool lockable,
		IDirect3DSurface9** surface, float scale);
	bool PoolAllocateDepthStencil(int width, int height, unsigned int format, unsigned int multiSample,
		IDirect3DSurface9** surface, float scale);
	// 0x10624D10: takes the texture that was made into a handle back out of the pool
	void FreePooledTexture(IDirect3DTexture9** texture);
	// 0x10623FB0: makes every resource the pool recorded again after the device came back (engine::Display's reset
	// calls it; 0x10623DB0, the release on the way in, is the other half)
	void RestoreDefaultPool();

	// 0x1061B140: the Direct3D multisample mode of a sample count (a table at 0x10E33DA0; name guess)
	int GetMultiSampleType(int samples);
}

#endif
