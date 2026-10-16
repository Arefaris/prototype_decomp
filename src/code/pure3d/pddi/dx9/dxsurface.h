// pure3d::dxSurface (RTTI name; base pure3d::pddiObject): the surface the default pool manager keeps for a texture.
// The layout follows the constructor (0x1061EF70) and 0x1061F0C0, which takes the size out of the Direct3D surface's
// description. Member names are guesses.
#ifndef PURE3D_PDDI_DX9_DXSURFACE_H
#define PURE3D_PDDI_DX9_DXSURFACE_H

#include "code/pure3d/pddi.h"
#include "code/pure3d/pddi/dx9/d3d9.h"

namespace pure3d
{
	// What a surface is made from: the size, the format and the sample count of the level (0x1061BF80 constructs
	// one, in the device unit, so its constructor is only declared here)
	class dxSurfaceLevel
	{
	public:
		// 0x1061BF80
		dxSurfaceLevel();

		int width;              // +0
		int height;             // +4
		unsigned int format;    // +8
		int multiSampleType;    // +0xC
		int unknown10;          // +0x10
		int unknown14;          // +0x14
		int unknown18;          // +0x18
		bool unknown1C;         // +0x1C
	};

	class dxSurface : public pddiObject
	{
	public:
		// 0x1061EF70
		dxSurface();
		// 0x1061F0C0: keeps the surface and takes format, sample count and size from its description
		void SetSurface(IDirect3DSurface9* surface);
		// 0x1061F000: takes the size, the format and the sample count of the level and makes the surface for it
		void SetLevel(const dxSurfaceLevel* level);

		IDirect3DSurface9* surface;   // +8
		unsigned int format;          // +0xC
		int multiSampleType;          // +0x10
		int width;                    // +0x14
		int height;                   // +0x18
		// Cleared once the surface is bound
		bool unknown1C;               // +0x1C
	};
}

#endif
