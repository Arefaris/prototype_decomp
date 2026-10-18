// pure3d::Shader (RTTI name: pure3d::Entity; pure3d::RefCounted; core::IRefCount; 0x30 bytes, vftable 0x10E587D8):
// a shader as the primitives use it. It keeps the device's shader at +0x10, the draw parameters at +0x14 and the
// flags the render passes sort by; names are guesses.
#ifndef PURE3D_SHADER_H
#define PURE3D_SHADER_H

#include "code/pure3d/entity.h"
#include "code/pure3d/primstream.h"

namespace pure3d
{
	class dxShader;

	class Shader : public Entity
	{
	public:
		// 0x107064A0: a shader of that name (the device's shader of the same name is looked up for it)
		explicit Shader(const char* shaderName);
		// 0x107062D0: takes the draw parameters and sets the flags that follow from them
		void SetParameters(const PrimStreamParameters& newParameters);

		dxShader* shader;
		PrimStreamParameters parameters;
		unsigned char unknown20[4];
		// The word at +0x24 whose low four bits the loaders set (0x10B953B0)
		unsigned int unknown24Bits : 4;
		unsigned int unknown24Rest : 28;
		unsigned char unknown28[8];
	};
}

#endif
