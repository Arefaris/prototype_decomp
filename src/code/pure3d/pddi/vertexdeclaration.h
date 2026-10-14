// The description of a vertex declaration: up to 16 elements (the Direct3D 9 limit), each named like a shader
// parameter. The class name is a guess from the unit that holds its constructor (pddi/src/dx9/dxvertexdeclaration.cpp);
// the layout follows the constructor, the meanings of the fields are unknown.
#ifndef PURE3D_PDDI_VERTEXDECLARATION_H
#define PURE3D_PDDI_VERTEXDECLARATION_H

#include "code/pure3d/shaderparameters.h"

namespace pure3d
{
	// 0x114 bytes; a member of dxVertexBuffer
	class dxVertexDeclaration
	{
	public:
		// 0x10625AC0
		dxVertexDeclaration();

		int unknown0;
		int unknown4;
		ShaderParameter elements[16];
		int unknown108;
		int unknown10C;
		int unknown110;
	};
}

#endif
