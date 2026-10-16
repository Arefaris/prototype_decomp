// pure3d::dxVertexBuffer (RTTI name; base pure3d::pddiObject): a vertex buffer of the Direct3D 9 back end. The layout
// follows the constructor (0x106262D0); the creation (0x10626350) fills the declaration at +0x14 from the descriptor
// it is given. The member names are guesses.
#ifndef PURE3D_PDDI_DX9_DXVERTEXBUFFER_H
#define PURE3D_PDDI_DX9_DXVERTEXBUFFER_H

#include "code/pure3d/pddi.h"
#include "code/pure3d/pddi/dx9/d3d9.h"
#include "code/pure3d/pddi/vertexdeclaration.h"

namespace pure3d
{
	// The description a vertex buffer is created from (0x10626350 reads +0, +4, +0x18 and the elements from +0x18)
	struct VertexBufferDescription;

	class dxVertexBuffer : public pddiObject
	{
	public:
		// 0x106262D0
		dxVertexBuffer();
		// 0x10626350
		void Create(const VertexBufferDescription* description);

		bool unknown8;
		int unknownC;
		int unknown10;
		dxVertexDeclaration declaration;
		int unknown128;
		int unknown12C;
		// 1 while the buffer is the default pool's, 0 when the device owns it (set from the descriptor's pool)
		int unknown130;
		// The bytes the declaration's elements were laid out with (a new[] block)
		int unknown134;
		int unknown138;
	};
}

#endif
