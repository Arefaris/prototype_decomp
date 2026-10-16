// The Direct3D 9 interfaces the dx9 back end calls. The toolchain has no platform SDK headers, so they are declared
// here in the form the engine's code uses them: a COM vtable pointer, and __stdcall entries that take the interface
// as their first argument (the original calls `device->lpVtbl->Method(device, ...)`, so the interface is pushed, not
// passed in ecx). Only the slots the reconstructed units reach carry a name; a method's index is the one d3d9.h
// gives it, which is what fixes the offsets.
#ifndef PURE3D_PDDI_DX9_D3D9_H
#define PURE3D_PDDI_DX9_D3D9_H

typedef long HRESULT;
typedef unsigned int UINT;
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned long ULONG;
typedef int BOOL;
typedef void* HANDLE;
typedef unsigned int D3DFORMAT;
typedef unsigned int D3DPOOL;
typedef unsigned int D3DRESOURCETYPE;
typedef unsigned int D3DTEXTUREFILTERTYPE;
typedef unsigned int D3DMULTISAMPLE_TYPE;
typedef unsigned int D3DBACKBUFFER_TYPE;

// 0x8876086C and friends (the errors the default pool manager names)
#define D3DERR_INVALIDCALL 0x8876086C
#define D3DERR_NOTAVAILABLE 0x8876086A
#define D3DERR_OUTOFVIDEOMEMORY 0x8876017C
#define E_OUTOFMEMORY 0x8007000E
#define D3DXERR_INVALIDDATA 0x88760B59

enum
{
	D3DPOOL_DEFAULT = 0,
	D3DPOOL_MANAGED = 1,
	D3DPOOL_SYSTEMMEM = 2,
	D3DPOOL_SCRATCH = 3
};

enum
{
	D3DMULTISAMPLE_NONE = 0
};

enum
{
	D3DTEXF_NONE = 0,
	D3DTEXF_POINT = 1,
	D3DTEXF_LINEAR = 2,
	D3DTEXF_ANISOTROPIC = 3
};

// 0x10: the lock is only read
#define D3DLOCK_READONLY 0x10
// 0x2000: the buffer's old contents are dropped (what the pool locks a recreated vertex buffer with)
#define D3DLOCK_DISCARD 0x2000

struct D3DLOCKED_RECT
{
	int Pitch;
	void* pBits;
};

struct D3DLOCKED_BOX
{
	int RowPitch;
	int SlicePitch;
	void* pBits;
};

struct IDirect3DDevice9;
struct IDirect3DBaseTexture9;
struct IDirect3DTexture9;
struct IDirect3DVolumeTexture9;
struct IDirect3DCubeTexture9;
struct IDirect3DVertexBuffer9;
struct IDirect3DIndexBuffer9;
struct IDirect3DSurface9;

// One element of a vertex declaration (D3DVERTEXELEMENT9, 8 bytes)
struct D3DVERTEXELEMENT9
{
	unsigned short Stream;
	unsigned short Offset;
	unsigned char Type;
	unsigned char Method;
	unsigned char Usage;
	unsigned char UsageIndex;
};

struct IDirect3DVertexDeclaration9;

// 0x10 GetDeclaration (index 4)
struct IDirect3DVertexDeclaration9Vtbl
{
	void* queryInterface;
	void* addRef;
	void* release;
	void* getDevice;
	HRESULT (__stdcall* GetDeclaration)(IDirect3DVertexDeclaration9* declaration, D3DVERTEXELEMENT9* elements,
		UINT* count);
};

struct IDirect3DVertexDeclaration9
{
	IDirect3DVertexDeclaration9Vtbl* lpVtbl;
};

// 0x2C Lock, 0x30 Unlock (index 11 / 12 of the resource interfaces)
struct IDirect3DVertexBuffer9Vtbl
{
	void* queryInterface;
	void* addRef;
	void* release;
	void* getDevice;
	void* setPrivateData;
	void* getPrivateData;
	void* freePrivateData;
	void* setPriority;
	void* getPriority;
	void* preLoad;
	void* getType;
	// The engine hands Lock the address of a D3DLOCKED_RECT, so the fourth argument is declared as a plain pointer
	HRESULT (__stdcall* Lock)(IDirect3DVertexBuffer9* buffer, UINT offsetToLock, UINT sizeToLock, void* data,
		DWORD flags);
	HRESULT (__stdcall* Unlock)(IDirect3DVertexBuffer9* buffer);
	void* getDesc;
};

struct IDirect3DVertexBuffer9
{
	IDirect3DVertexBuffer9Vtbl* lpVtbl;
};

struct IDirect3DIndexBuffer9Vtbl
{
	void* queryInterface;
	void* addRef;
	void* release;
	void* getDevice;
	void* setPrivateData;
	void* getPrivateData;
	void* freePrivateData;
	void* setPriority;
	void* getPriority;
	void* preLoad;
	void* getType;
	HRESULT (__stdcall* Lock)(IDirect3DIndexBuffer9* buffer, UINT offsetToLock, UINT sizeToLock, void** data,
		DWORD flags);
	HRESULT (__stdcall* Unlock)(IDirect3DIndexBuffer9* buffer);
	void* getDesc;
};

struct IDirect3DIndexBuffer9
{
	IDirect3DIndexBuffer9Vtbl* lpVtbl;
};

// 0x08 Release, and the surface interface's own slots above it
struct IDirect3DSurface9Vtbl
{
	void* queryInterface;
	void* addRef;
	ULONG (__stdcall* Release)(IDirect3DSurface9* surface);
	void* getDevice;
	void* setPrivateData;
	void* getPrivateData;
	void* freePrivateData;
	void* setPriority;
	void* getPriority;
	void* preLoad;
	void* getType;
	void* getDesc;
	void* getContainer;
	void* getDC;
	void* releaseDC;
	void* lockRect;
	void* unlockRect;
};

struct IDirect3DSurface9
{
	IDirect3DSurface9Vtbl* lpVtbl;

	// Releases the interface (the engine drops the references it holds through the interface's own vtable slot)
	ULONG Release();
};

inline ULONG IDirect3DSurface9::Release()
{
	return lpVtbl->Release(this);
}

// 0x48 GetSurfaceLevel, 0x4C LockRect, 0x50 UnlockRect, 0x54 AddDirtyRect (indices 18 - 21)
struct IDirect3DTexture9Vtbl
{
	void* queryInterface;
	void* addRef;
	ULONG (__stdcall* Release)(IDirect3DTexture9* texture);
	void* getDevice;
	void* setPrivateData;
	void* getPrivateData;
	void* freePrivateData;
	void* setPriority;
	void* getPriority;
	void* preLoad;
	void* getType;
	void* setLOD;
	void* getLOD;
	void* getLevelCount;
	void* setAutoGenFilterType;
	void* getAutoGenFilterType;
	void* generateMipSubLevels;
	void* getLevelDesc;
	HRESULT (__stdcall* GetSurfaceLevel)(IDirect3DTexture9* texture, UINT level, IDirect3DSurface9** surfaceLevel);
	HRESULT (__stdcall* LockRect)(IDirect3DTexture9* texture, UINT level, void* lockedRect, const void* rect,
		DWORD flags);
	HRESULT (__stdcall* UnlockRect)(IDirect3DTexture9* texture, UINT level);
	HRESULT (__stdcall* AddDirtyRect)(IDirect3DTexture9* texture, const void* dirtyRect);
};

struct IDirect3DTexture9
{
	IDirect3DTexture9Vtbl* lpVtbl;

	// Releases the interface (the engine drops the references it holds through the interface's own vtable slot)
	ULONG Release();
};

inline ULONG IDirect3DTexture9::Release()
{
	return lpVtbl->Release(this);
}

struct IDirect3DCubeTexture9Vtbl
{
	void* queryInterface;
	void* addRef;
	ULONG (__stdcall* Release)(IDirect3DCubeTexture9* texture);
	void* getDevice;
	void* setPrivateData;
	void* getPrivateData;
	void* freePrivateData;
	void* setPriority;
	void* getPriority;
	void* preLoad;
	void* getType;
	void* setLOD;
	void* getLOD;
	void* getLevelCount;
	void* setAutoGenFilterType;
	void* getAutoGenFilterType;
	void* generateMipSubLevels;
	void* getLevelDesc;
	void* getCubeMapSurface;
	HRESULT (__stdcall* LockRect)(IDirect3DCubeTexture9* texture, unsigned int faceType, UINT level,
		void* lockedRect, const void* rect, DWORD flags);
	HRESULT (__stdcall* UnlockRect)(IDirect3DCubeTexture9* texture, unsigned int faceType, UINT level);
	HRESULT (__stdcall* AddDirtyRect)(IDirect3DCubeTexture9* texture, unsigned int faceType, const void* dirtyRect);
};

struct IDirect3DCubeTexture9
{
	IDirect3DCubeTexture9Vtbl* lpVtbl;

	// Releases the interface (the engine drops the references it holds through the interface's own vtable slot)
	ULONG Release();
};

inline ULONG IDirect3DCubeTexture9::Release()
{
	return lpVtbl->Release(this);
}

struct IDirect3DVolumeTexture9Vtbl
{
	void* queryInterface;
	void* addRef;
	ULONG (__stdcall* Release)(IDirect3DVolumeTexture9* texture);
	void* getDevice;
	void* setPrivateData;
	void* getPrivateData;
	void* freePrivateData;
	void* setPriority;
	void* getPriority;
	void* preLoad;
	void* getType;
	void* setLOD;
	void* getLOD;
	void* getLevelCount;
	void* setAutoGenFilterType;
	void* getAutoGenFilterType;
	void* generateMipSubLevels;
	void* getLevelDesc;
	void* getVolumeLevel;
	HRESULT (__stdcall* LockBox)(IDirect3DVolumeTexture9* texture, UINT level, void* lockedVolume, const void* box,
		DWORD flags);
	HRESULT (__stdcall* UnlockBox)(IDirect3DVolumeTexture9* texture, UINT level);
	HRESULT (__stdcall* AddDirtyBox)(IDirect3DVolumeTexture9* texture, const void* dirtyBox);
};

struct IDirect3DVolumeTexture9
{
	IDirect3DVolumeTexture9Vtbl* lpVtbl;

	// Releases the interface (the engine drops the references it holds through the interface's own vtable slot)
	ULONG Release();
};

inline ULONG IDirect3DVolumeTexture9::Release()
{
	return lpVtbl->Release(this);
}

// The parameters a device is made or reset with (0x38 bytes)
struct D3DPRESENT_PARAMETERS
{
	UINT BackBufferWidth;
	UINT BackBufferHeight;
	D3DFORMAT BackBufferFormat;
	UINT BackBufferCount;
	D3DMULTISAMPLE_TYPE MultiSampleType;
	DWORD MultiSampleQuality;
	unsigned int SwapEffect;
	void* hDeviceWindow;
	BOOL Windowed;
	BOOL EnableAutoDepthStencil;
	D3DFORMAT AutoDepthStencilFormat;
	DWORD Flags;
	UINT FullScreen_RefreshRateInHz;
	UINT PresentationInterval;
};

struct D3DDISPLAYMODE
{
	UINT Width;
	UINT Height;
	UINT RefreshRate;
	D3DFORMAT Format;
};

// The device's capabilities (0x130 bytes; only the fields the back end reads are named)
struct D3DCAPS9
{
	unsigned int unknown0[0x16];
	UINT MaxTextureWidth;
	UINT MaxTextureHeight;
	unsigned int unknown60[0x1D];
	DWORD DevCaps2;
	unsigned int unknownD8[7];
	DWORD StretchRectFilterCaps;
	unsigned int unknownF8[14];
};

struct IDirect3D9;

// The slots of the Direct3D object the display uses (indices as in d3d9.h)
struct IDirect3D9Vtbl
{
	void* unknown0[8];
	// 0x20 GetAdapterDisplayMode
	HRESULT (__stdcall* GetAdapterDisplayMode)(IDirect3D9* d3d, UINT adapter, D3DDISPLAYMODE* mode);
	void* unknown24[5];
	// 0x38 GetDeviceCaps
	HRESULT (__stdcall* GetDeviceCaps)(IDirect3D9* d3d, UINT adapter, unsigned int deviceType, D3DCAPS9* caps);
	void* getAdapterMonitor;
	// 0x40 CreateDevice
	HRESULT (__stdcall* CreateDevice)(IDirect3D9* d3d, UINT adapter, unsigned int deviceType, void* focusWindow,
		DWORD behaviourFlags, D3DPRESENT_PARAMETERS* parameters, IDirect3DDevice9** device);
};

struct IDirect3D9
{
	IDirect3D9Vtbl* lpVtbl;
};

// The slots the dx9 back end uses, in d3d9.h's order (the index is the offset divided by four)
struct IDirect3DDevice9Vtbl
{
	void* queryInterface;
	void* addRef;
	void* release;
	HRESULT (__stdcall* TestCooperativeLevel)(IDirect3DDevice9* device);
	// 0x10
	UINT (__stdcall* GetAvailableTextureMem)(IDirect3DDevice9* device);
	void* evictManagedResources;
	void* getDirect3D;
	void* getDeviceCaps;
	void* getDisplayMode;
	// 0x24
	void* getCreationParameters;
	void* setCursorProperties;
	void* setCursorPosition;
	void* showCursor;
	void* createAdditionalSwapChain;
	// 0x38
	void* getSwapChain;
	void* getNumberOfSwapChains;
	HRESULT (__stdcall* Reset)(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* parameters);
	void* present;
	void* getBackBuffer;
	// 0x4C
	void* getRasterStatus;
	void* setDialogBoxMode;
	void* setGammaRamp;
	// 0x58 GetGammaRamp
	HRESULT (__stdcall* GetGammaRamp)(IDirect3DDevice9* device, UINT swapChain, void* ramp);
	// 0x5C CreateTexture
	HRESULT (__stdcall* CreateTexture)(IDirect3DDevice9* device, UINT width, UINT height, UINT levels, DWORD usage,
		D3DFORMAT format, D3DPOOL pool, IDirect3DTexture9** texture, HANDLE* sharedHandle);
	// 0x60 CreateVolumeTexture
	HRESULT (__stdcall* CreateVolumeTexture)(IDirect3DDevice9* device, UINT width, UINT height, UINT depth,
		UINT levels, DWORD usage, D3DFORMAT format, D3DPOOL pool, IDirect3DVolumeTexture9** texture,
		HANDLE* sharedHandle);
	// 0x64 CreateCubeTexture
	HRESULT (__stdcall* CreateCubeTexture)(IDirect3DDevice9* device, UINT edgeLength, UINT levels, DWORD usage,
		D3DFORMAT format, D3DPOOL pool, IDirect3DCubeTexture9** texture, HANDLE* sharedHandle);
	// 0x68 CreateVertexBuffer
	HRESULT (__stdcall* CreateVertexBuffer)(IDirect3DDevice9* device, UINT length, DWORD usage, DWORD fvf,
		D3DPOOL pool, IDirect3DVertexBuffer9** vertexBuffer, HANDLE* sharedHandle);
	// 0x6C CreateIndexBuffer
	HRESULT (__stdcall* CreateIndexBuffer)(IDirect3DDevice9* device, UINT length, DWORD usage, D3DFORMAT format,
		D3DPOOL pool, IDirect3DIndexBuffer9** indexBuffer, HANDLE* sharedHandle);
	// 0x70 CreateRenderTarget
	HRESULT (__stdcall* CreateRenderTarget)(IDirect3DDevice9* device, UINT width, UINT height, D3DFORMAT format,
		D3DMULTISAMPLE_TYPE multiSample, DWORD multisampleQuality, BOOL lockable, IDirect3DSurface9** surface,
		HANDLE* sharedHandle);
	// 0x74 CreateDepthStencilSurface
	HRESULT (__stdcall* CreateDepthStencilSurface)(IDirect3DDevice9* device, UINT width, UINT height,
		D3DFORMAT format, D3DMULTISAMPLE_TYPE multiSample, DWORD multisampleQuality, BOOL discard,
		IDirect3DSurface9** surface, HANDLE* sharedHandle);
	// 0x78 UpdateSurface, 0x7C UpdateTexture
	void* updateSurface;
	void* updateTexture;
	// 0x80 GetRenderTargetData
	HRESULT (__stdcall* GetRenderTargetData)(IDirect3DDevice9* device, IDirect3DSurface9* renderTarget,
		IDirect3DSurface9* destSurface);
	void* getFrontBufferData;
	// 0x88 StretchRect
	HRESULT (__stdcall* StretchRect)(IDirect3DDevice9* device, IDirect3DSurface9* sourceSurface,
		const void* sourceRect, IDirect3DSurface9* destSurface, const void* destRect, D3DTEXTUREFILTERTYPE filter);
	// 0x8C ColorFill
	void* colorFill;
	// 0x90 - 0x140: the offscreen surface, the render targets, the scene, the transforms and the states
	void* unknown94[45];
	// 0x144 DrawPrimitive
	HRESULT (__stdcall* DrawPrimitive)(IDirect3DDevice9* device, unsigned int primitiveType, UINT startVertex,
		UINT primitiveCount);
	// 0x148 DrawIndexedPrimitive
	HRESULT (__stdcall* DrawIndexedPrimitive)(IDirect3DDevice9* device, unsigned int primitiveType, INT baseVertex,
		UINT minIndex, UINT numVertices, UINT startIndex, UINT primitiveCount);
	// 0x14C - 0x154
	void* unknown14C[3];
	// 0x158 CreateVertexDeclaration
	HRESULT (__stdcall* CreateVertexDeclaration)(IDirect3DDevice9* device, const D3DVERTEXELEMENT9* elements,
		IDirect3DVertexDeclaration9** declaration);
	// 0x15C SetVertexDeclaration
	HRESULT (__stdcall* SetVertexDeclaration)(IDirect3DDevice9* device, void* declaration);
	// 0x160 - 0x19C: the vertex shaders and their constants and the stream sources
	void* unknown160[4];
	// 0x170 SetVertexShader
	HRESULT (__stdcall* SetVertexShader)(IDirect3DDevice9* device, void* shader);
	void* unknown174;
	// 0x178 SetVertexShaderConstantF
	HRESULT (__stdcall* SetVertexShaderConstantF)(IDirect3DDevice9* device, UINT startRegister,
		const float* constantData, UINT vector4fCount);
	void* unknown17C[5];
	// 0x190 SetStreamSource
	HRESULT (__stdcall* SetStreamSource)(IDirect3DDevice9* device, UINT streamNumber, void* streamData,
		UINT offsetInBytes, UINT stride);
	void* unknown194[3];
	// 0x1A0 SetIndices
	HRESULT (__stdcall* SetIndices)(IDirect3DDevice9* device, IDirect3DIndexBuffer9* indexBuffer);
	void* unknown1A4[2];
	// 0x1AC SetPixelShader
	HRESULT (__stdcall* SetPixelShader)(IDirect3DDevice9* device, void* shader);
};

struct IDirect3DDevice9
{
	IDirect3DDevice9Vtbl* lpVtbl;
};

// 0x11276D38: the device every dx9 unit draws through
extern IDirect3DDevice9* gD3DDevice;

#endif
