// pure3d::dxTechniques and pure3d::pddiBaseShaderTemplate: the accessors in the shader unit around 0x10618550.
#include "code/pure3d/pddi/dx9/dxcontext.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x10618550
	void* dxTechniques::Get(int technique)
	{
		return entries[technique];
	}

	// FUNCTION: ENGINE 0x10618580
	void pddiBaseShaderTemplate::InitConstants(pddiBaseContext::Constants* constants)
	{
		defaults->CopyTo(constants);
	}

	// FUNCTION: ENGINE 0x1061A2F0
	void pddiBaseShaderTemplate::AddPass(const char* name, const char* vertexProgram, const char* pixelProgram,
		const PrimStreamParameters* state, int unknown)
	{
	}
}
