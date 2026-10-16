// pure3d::dxSurface (RTTI name; base pure3d::pddiObject): the surface the default pool manager keeps for a texture.
// The layout follows the constructor (0x1061EF70) and 0x1061F0C0, which takes the size out of the Direct3D surface's
// description. Member names are guesses.
#ifndef PURE3D_PDDI_DX9_DXSURFACE_H
#define PURE3D_PDDI_DX9_DXSURFACE_H

#include "code/pure3d/pddi.h"
#include "code/pure3d/pddi/dx9/d3d9.h"

namespace pure3d
{
	class dxSurface : public pddiObject
	{
	public:
		// 0x1061EF70
		dxSurface();
		// 0x1061F0C0: keeps the surface and takes format, sample count and size from its description
		void SetSurface(IDirect3DSurface9* surface);

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
