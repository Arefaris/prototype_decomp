// The description of a vertex declaration: up to 16 elements (the Direct3D 9 limit), each named like a shader
// parameter. The class name is a guess from the unit that holds its constructor (pddi/src/dx9/dxvertexdeclaration.cpp);
// the layout follows the constructor, the meanings of the fields are unknown.
#ifndef PURE3D_PDDI_VERTEXDECLARATION_H
#define PURE3D_PDDI_VERTEXDECLARATION_H

#include "code/container/arraydynamicstatic.h"
#include "code/pure3d/pddi/dx9/d3d9.h"
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

	// One entry of the declaration manager's table (0x10 bytes): the device's declaration, how many elements it has
	// (the end marker included), how many users it has and the number it is known by
	struct dxVertexDeclarationEntry
	{
		IDirect3DVertexDeclaration9* declaration;
		int elementCount;
		int users;
		int id;
	};

	// The declarations the device holds (the global at 0x11276F48; layout and names are guesses; the heap and the
	// alignment of the array's allocator are guesses too)
	class dxVertexDeclarationManager
	{
	public:
		container::ArrayDynamic<dxVertexDeclarationEntry, container::AllocatorCoreStatic<12, 16> > entries;
		// How many declarations have been made in all
		int count;
		int unknown14;
		int unknown18;
		// The number of the declaration the device has set (the draws set it when theirs is another)
		int current;
	};
	extern dxVertexDeclarationManager* gVertexDeclarationManager;

	// 0x1062B5C0: the number of the device declaration that has the elements (the list ends with an element of type
	// 0x11), made when the device has none yet (name guess)
	int FindVertexDeclaration(const D3DVERTEXELEMENT9* elements);
}

#endif
