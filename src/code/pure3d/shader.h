// pure3d::Shader (RTTI name): a shader as the primitives use it. Only the draw parameters the primitives pass to the
// stream (at +0x14); names are guesses.
#ifndef PURE3D_SHADER_H
#define PURE3D_SHADER_H

#include "code/pure3d/primstream.h"

namespace pure3d
{
	class Shader
	{
	public:
		unsigned char unknown0[0x14];
		PrimStreamParameters parameters;
	};
}

#endif
