// pure3d::dxVertexBuffer (RTTI name; base pure3d::pddiObject): a vertex buffer of the Direct3D 9 back end. The layout
// follows the constructor (0x106262D0); the creation (0x10626350) fills the declaration at +0x14 from the descriptor
// it is given. The member names are guesses.
#ifndef PURE3D_PDDI_DX9_DXVERTEXBUFFER_H
#define PURE3D_PDDI_DX9_DXVERTEXBUFFER_H

#include "code/pure3d/pddi.h"
#include "code/pure3d/pddi/dx9/d3d9.h"
#include "code/pure3d/pddi/vertexdeclaration.h"
#include "code/pure3d/shaderparameters.h"

namespace pure3d
{
	// The description a vertex buffer is created from: the shader parameters the gpu skin was made with (0x10626350
	// reads +0 (how many vertices), +4 (how many elements), +8 (the usage flags: bit 0 write-only, bit 1 dynamic), the
	// elements from +0x10, +0x110 (whether the data's size is given) and +0x114 (the size of the data))
	struct VertexBufferDescription : ShaderParameters
	{
		// 0x106122B0: the streams of a vertex format (the format word of a prim group) for count vertices (the last
		// two arguments are the prim group's; names guessed)
		VertexBufferDescription(int count, unsigned int format, int unknown, bool unknown2);
	};

	class dxVertexBuffer : public pddiObject
	{
	public:
		// 0x106262D0
		dxVertexBuffer();
		// 0x10625E30: lets go of the device buffer (to the pool when it is the default pool's) and the elements
		virtual ~dxVertexBuffer();
		// 0x106258D0
		void Unlock();
		// 0x10625F00: locks the vertices; the description receives the buffer's own declaration, the locked block
		// (in its word at +0x108) and the flags the lock was asked with
		void Lock(dxVertexDeclaration* description, int count);
		// 0x10625FA0: fills the shader parameters with the descriptor of the buffer (its counts, its flags and its
		// elements)
		void Unknown10625FA0(ShaderParameters* parameters);
		// 0x10626350
		void Create(const VertexBufferDescription* description);
		// 0x10625900: the first word of the declaration (the draws take it for how many vertices there are)
		int GetUnknown14();

		bool unknown8;
		// The Direct3D vertex buffer
		IDirect3DVertexBuffer9* unknownC;
		// The description's usage flags (bit 0 write-only, bit 1 dynamic)
		unsigned int unknown10;
		dxVertexDeclaration declaration;
		int unknown128;
		int unknown12C;
		// 1 while the buffer is the default pool's, 0 when the device owns it (set from the descriptor's pool)
		int unknown130;
		// The elements the device's declaration is made from (a new[] block, the end marker included)
		D3DVERTEXELEMENT9* unknown134;
		int unknown138;
	};
}

#endif
