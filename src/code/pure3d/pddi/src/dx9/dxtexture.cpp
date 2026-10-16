// pure3d::dxTexture, the Direct3D 9 texture of the pddi layer (unit around 0x1061C400 - 0x1061F200; the file name is
// guessed, no assert path survives).
#include <new>

#include "code/pure3d/pddi/dx9/dxtexture.h"

#include "code/pure3d/pddi/dx9/dxcontext.h"

namespace pure3d
{
	// 0x11276D48: the bytes of texture memory all the textures hold (name guess)
	extern int gTextureMemory;

	// The level records of the texture leave the level array through the pool manager (0x10624D10)
	void FreePooledTexture(IDirect3DTexture9** slot);

	// FUNCTION: ENGINE 0x1061C360
	// The formats a texture may be created with (the two four-character ones are "DF16" and "DF24", the depth
	// formats; the single bytes are the back end's own format codes). The result is a 32-bit 0 or 1: the engine's
	// callers read the low byte of it, but its own code sets the whole register.
	int IsTextureFormatSupported(unsigned int format)
	{
		if (format == 0x49 || format == 0x50 || format == 0x46 || format == 0x4F || format == 0x53 ||
			format == 0x4D || format == 0x4B || format == 0x52 || format == 0x47 || format == 0x34324644 ||
			format == 0x36314644)
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1061CBE0
	dxTexture::~dxTexture()
	{
		if (unknown88 != 0)
		{
			ReleaseRef(&unknown88->unknown8C);
			ReleaseRef(&unknown88);
		}
		for (unsigned int i = 0; i < (unsigned int)description.levels; i++)
		{
			operator delete[](levelData[i].data);
			levelData[i].data = 0;
		}
		operator delete[](levelData);
		levelData = 0;
		if (texture != 0)
		{
			if (pool == 0)
			{
				FreePooledTexture(&texture);
			}
			else
			{
				texture->Release();
			}
			texture = 0;
		}
		ReleaseRef(&surface);
		ReleaseRef(&volumeTexture);
		ReleaseRef(&cubeTexture);
		ReleaseRef(&defaultTexture);
		gTextureMemory -= memory;
		if (gContext != 0)
		{
			gContext->textureMemory = (float)(-memory) + gContext->textureMemory;
		}
	}
}
