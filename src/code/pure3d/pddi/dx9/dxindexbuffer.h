// pure3d::dxIndexBuffer (RTTI name; base pure3d::pddiObject): an index buffer of the Direct3D 9 back end. The layout
// follows the constructor (0x106266D0) and the creation (0x10626770, which reads the D3D format out of the format
// tables at 0x10E3464C and 0x110BB934). The member names are guesses.
#ifndef PURE3D_PDDI_DX9_DXINDEXBUFFER_H
#define PURE3D_PDDI_DX9_DXINDEXBUFFER_H

#include "code/pure3d/pddi.h"
#include "code/pure3d/pddi/dx9/d3d9.h"

namespace pure3d
{
	// The description an index buffer is created from (0x10626770 reads +0, +4, +8 and +0x10)
	struct IndexBufferDescription;

	// The six-word block an index buffer keeps at +0x1C: its constructor (0x10611BD0) clears all but the fourth
	// word. Name and members are guesses.
	class dxIndexBufferState
	{
	public:
		dxIndexBufferState();

		int unknown0;
		int unknown4;
		int unknown8;
		int unknownC;
		int unknown10;
		int unknown14;
	};

	class dxIndexBuffer : public pddiObject
	{
	public:
		// 0x106266D0
		dxIndexBuffer();
		// 0x10626770
		void Create(const IndexBufferDescription* description);

		bool unknown8;
		int unknownC;
		int unknown10;
		bool unknown14;
		int unknown18;
		dxIndexBufferState state;
		int unknown34;
	};
}

#endif
