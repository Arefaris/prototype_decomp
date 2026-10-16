// pure3d::dxTexture (RTTI name; base pure3d::pddiObject): a texture of the Direct3D 9 back end: a copy of the
// description it was asked for, its Direct3D textures for the device and the default pool, the level data it laid
// out for them and the texture it was copied from. The layout follows the constructor (0x1061C400), the destructor
// (0x1061CBE0) and the creations (0x1061CD70 / 0x1061D010); every member name is a guess.
#ifndef PURE3D_PDDI_DX9_DXTEXTURE_H
#define PURE3D_PDDI_DX9_DXTEXTURE_H

#include "code/pure3d/pddi.h"
#include "code/pure3d/pddi/dx9/d3d9.h"
#include "code/pure3d/pddi/dx9/dxsurface.h"

namespace pure3d
{
	// The description a texture is created from (0x38 bytes; 0x1061C8F0 validates it and copies it into the texture
	// at +8, where the texture reads it at every later step)
	struct TextureDescription
	{
		// 1: a 2D texture, 2: a cube texture, 3: a volume texture
		int type;              // +0
		// How many mip levels
		int levels;            // +4
		// How many slices a volume texture has
		int depth;             // +8
		int width;             // +0xC
		int height;            // +0x10
		unsigned int format;   // +0x14
		unsigned int usage;    // +0x18
		unsigned int flags;    // +0x1C
		int unknown20;         // +0x20
		int unknown24;         // +0x24
		int unknown28;         // +0x28
		int unknown2C;         // +0x2C
		int unknown30;         // +0x30
		// True when the device may hold the texture in its own pool
		bool unknown34;        // +0x34
	};

	// One slice of a level: the size the texture's data has at that level (0x1061C490 lays the rows out)
	struct TextureLevelData
	{
		int width;    // +0
		int height;   // +4
		// Bytes of one row
		int pitch;    // +8
		// Bytes of the whole slice
		int size;     // +0xC
	};

	// One level: how many slice records it has and where they are (8 bytes; the array is at dxTexture +0x44)
	struct TextureLevel
	{
		int count;
		TextureLevelData* data;
	};

	// Whatever a slot holds is released and the slot cleared; the engine emits one copy of this per type of slot
	// (0x1061CA90 - 0x1061CB10 are the four-byte holders of dxTexture, the pddi types through their virtual
	// Release, the Direct3D interfaces through their own)
	template <class T> void ReleaseRef(T** ref)
	{
		if (*ref != 0)
		{
			(*ref)->Release();
			*ref = 0;
		}
	}

	class dxTexture : public pddiObject
	{
	public:
		// 0x1061C400: the device argument is not read (the pool manager owns the device)
		dxTexture(IDirect3DDevice9* device);
		// 0x1061CBE0
		virtual ~dxTexture();
		// 0x1061CD70
		bool Create(const TextureDescription* description);
		// 0x1061D010: a copy of a texture that is already on the device, level by level
		bool Create(const TextureDescription* description, const dxTexture* image);

		// What the texture was asked for, copied in by 0x1061C8F0
		TextureDescription description;   // +8
		// The pool manager's record of the surface the device made for it (0x1061EF70, 0x20 bytes)
		dxSurface* surface;               // +0x40
		// The level records (one per mip level, `description.levels` of them)
		TextureLevel* levelData;          // +0x44
		IDirect3DTexture9* texture;       // +0x48
		// The copy of a device-pool texture the device owns (0x1061C600 binds it while the texture is locked)
		IDirect3DTexture9* defaultTexture;      // +0x4C
		IDirect3DVolumeTexture9* volumeTexture; // +0x50
		IDirect3DCubeTexture9* cubeTexture;     // +0x54
		// The Direct3D format the description's format was resolved to (0x1061C020)
		unsigned int d3dFormat;           // +0x58
		// The Direct3D pool the texture was made in (0: the default pool)
		unsigned int pool;                // +0x5C
		// The level and slice a locked level points at
		int lockLevel;                    // +0x60
		int lockSlice;                    // +0x64
		int unknown68;                    // +0x68
		int unknown6C;                    // +0x6C
		int unknown70;                    // +0x70
		int unknown74;                    // +0x74
		int unknown78;                    // +0x78
		// True while a level of this texture is locked
		bool locked;                      // +0x7C
		// The bytes of texture memory this texture counts for
		int memory;                       // +0x80
		// True when the texture was copied from another one (0x1061CD70)
		bool unknown84;                   // +0x84
		// The texture this one was copied from, and the texture that was copied from this one
		dxTexture* unknown88;             // +0x88
		dxTexture* unknown8C;             // +0x8C
	};
}

#endif
