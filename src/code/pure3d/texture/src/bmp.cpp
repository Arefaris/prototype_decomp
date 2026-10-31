// The BMP reader of the texture module (RTTI pure3d::BMPParser; the unit is code/pure3d/texture/src/bmp.cpp, 0x107B5310 -
// 0x107B5B40 in the engine). Names are guesses.
#include "code/pure3d/texture/texture.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x107B5310
	bool BMPParser::IsSupportedFormat(unsigned int format)
	{
		return format == 3;
	}

	// FUNCTION: ENGINE 0x107B5320
	Texture* BMPParser::Load(core::IRefCount* stream, const char* name, int usage, bool flag, Texture* source)
	{
		return Parse(stream, 1, usage, 1, 1, 0, 0, 0);
	}
}
