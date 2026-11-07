// The two forms of proto::ShaderInputPatchFloat4 that the engine keeps in the first units of the image (0x1007F710 and
// 0x1007F770). They are a source of their own: the palette's reflection unit calls AddShaderInput on its colours
// directly and must see it as an external function.
#include "code/engine/render/async/drawable.h"
#include "code/proto/shaders/shaderpalette.h"
#include "code/pure3d/primitive.h"

namespace proto
{
	// FUNCTION: ENGINE 0x1007F710
	void ShaderInputPatchFloat4::AddShaderInput(pure3d::pddiShaderInputInitData* data)
	{
		float colour[4];
		colour[0] = value.r;
		colour[1] = value.g;
		colour[2] = value.b;
		colour[3] = value.a;
		data->SetVector4Named(4, name.name, colour);
	}

	// FUNCTION: ENGINE 0x1007F770
	// NONMATCHING: the engine copies the four floats in order into one block of stack words and passes it on; ours stores
	// the arguments last to first (26 %)
#ifdef NONMATCHING
	void ShaderInputPatchFloat4::AddBinding(engine::render::Drawable drawable)
	{
		drawable.SetBindingVector4(name.name, value.r, value.g, value.b, value.a);
	}
#endif
}
