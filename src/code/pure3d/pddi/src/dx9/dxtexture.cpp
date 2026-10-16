// pure3d::dxTexture, the Direct3D 9 texture of the pddi layer (unit around 0x1061C400 - 0x1061D3A0; the file name is
// guessed, no assert path survives).
#include "code/pure3d/pddi/dx9/dxtexture.h"

namespace pure3d
{
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

#ifdef NONMATCHING
	// FUNCTION: ENGINE 0x1061C400
	// NONMATCHING: scheduling, 31.0 %: every store is there with the engine's value and the engine's order, but our
	// compiler sinks the -1 / 1 group (0x28 - 0x3C) behind the whole run of zero stores and moves the vftable store
	// with it; reordering the source statements (document order, the engine's order) does not change the schedule.
	dxTexture::dxTexture(IDirect3DDevice9* device)
	{
		unknown8 = 0;
		unknownC = 0;
		unknown10 = 0;
		unknown14 = 0;
		unknown18 = 0;
		unknown1C = 0;
		unknown20 = 0;
		unknown24 = 0;
		unknown28 = -1;
		unknown2C = -1;
		unknown30 = 1;
		unknown34 = 0;
		unknown38 = 0;
		unknown3C = true;
		unknown40.pointer = 0;
		unknown44 = 0;
		texture = 0;
		unknown4C.pointer = 0;
		unknown50.pointer = 0;
		unknown54.pointer = 0;
		unknown58 = 0;
		unknown60 = -1;
		unknown64 = -1;
		unknown7C = false;
		unknown80 = 0;
		unknown84 = false;
		unknown88.pointer = 0;
		unknown8C = 0;
	}
#endif
}
