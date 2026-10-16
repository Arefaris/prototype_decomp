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

	// One entry of the declaration manager's table (0x10 bytes; the meanings of the last three words are unknown)
	struct dxVertexDeclarationEntry
	{
		dxVertexDeclaration* declaration;
		int unknown4;
		int unknown8;
		int unknownC;
	};

	// The declarations the device holds (the global at 0x11276F48; layout and names are guesses)
	class dxVertexDeclarationManager
	{
	public:
		dxVertexDeclarationEntry* begin;
		dxVertexDeclarationEntry* end;
		dxVertexDeclarationEntry* capacity;
		int unknownC;
		// How many declarations have been made in all
		int count;
	};
	extern dxVertexDeclarationManager* gVertexDeclarationManager;
}

#endif
