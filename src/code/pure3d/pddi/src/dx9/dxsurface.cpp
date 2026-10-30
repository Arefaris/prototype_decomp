// pure3d::dxSurface, the surface the default pool manager keeps for a texture (unit around 0x1061EF70 - 0x1061F140;
// the file name is guessed, no assert path survives).
#include "code/pure3d/pddi/dx9/dxsurface.h"
#include "code/pure3d/pddi/dx9/dxdefaultpoolmanager.h"
#include "code/pure3d/pddi/dx9/dxtexture.h"

namespace pure3d
{
	// 0x1061C360
	int IsTextureFormatSupported(unsigned int format);

	// FUNCTION: ENGINE 0x1061BF80
	dxSurfaceLevel::dxSurfaceLevel()
	{
		format = 0;
		width = -1;
		height = -1;
		unknown10 = 0;
		unknown14 = 0;
		unknown18 = 0;
		multiSampleType = 0;
		unknown1C = 1;
	}

	// FUNCTION: ENGINE 0x1061EF70
	dxSurface::dxSurface() : surface(0), format(0), multiSampleType(0), width(0), height(0)
	{
		unknown1C = true;
	}

	// FUNCTION: ENGINE 0x1061EFA0
	dxSurface::~dxSurface()
	{
		if (unknown1C)
		{
			if (surface != 0)
			{
				if ((char)IsTextureFormatSupported(format) != 0)
				{
					FreePooledDepthStencil(&surface);
				}
				else
				{
					FreePooledRenderTarget(&surface);
				}
				surface = 0;
			}
		}
	}

	// FUNCTION: ENGINE 0x1061F000
	void dxSurface::SetLevel(const dxSurfaceLevel* level)
	{
		unknown1C = true;
		ResolveTextureFormat(&format, level->format, true);
		width = level->width;
		height = level->height;
		multiSampleType = GetMultiSampleType(level->multiSampleType);
		bool depth = format == 0x49 || format == 0x50 || format == 0x46 || format == 0x4F || format == 0x53 || format == 0x4D || format == 0x4B || format == 0x52 || format == 0x47 || format == 0x34324644 || format == 0x36314644;
		if (depth)
		{
			PoolAllocateDepthStencil(level->width, level->height, format, multiSampleType, &surface, 0.0f);
		}
		else
		{
			PoolAllocateRenderTarget(level->width, level->height, format, multiSampleType, false, &surface, 0.0f);
		}
	}

	// FUNCTION: ENGINE 0x1061F0C0
	void dxSurface::SetSurface(IDirect3DSurface9* newSurface)
	{
		D3DSURFACE_DESC description;
		surface = newSurface;
		unknown1C = false;
		newSurface->lpVtbl->GetDesc(newSurface, &description);
		width = description.Width;
		height = description.Height;
		format = description.Format;
		multiSampleType = description.MultiSampleType;
	}
}

// Kept copies (compiler-generated and inline functions of this unit):
// FUNCTION: ENGINE 0x1061F120
