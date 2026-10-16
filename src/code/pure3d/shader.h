// pure3d::Shader (RTTI name: pure3d::Entity; pure3d::RefCounted; core::IRefCount): a shader as the primitives use it.
// Only the draw parameters the primitives pass to the stream (at +0x14) are named; names are guesses.
#ifndef PURE3D_SHADER_H
#define PURE3D_SHADER_H

#include "code/pure3d/entity.h"
#include "code/pure3d/primstream.h"

namespace pure3d
{
	class Shader : public Entity
	{
	public:
		unsigned char unknown10[4];
		PrimStreamParameters parameters;
	};
}

#endif
