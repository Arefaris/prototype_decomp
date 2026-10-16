// pure3d::dxIndexBuffer (RTTI name; base pure3d::pddiObject): an index buffer of the Direct3D 9 back end. The layout
// follows the constructor (0x106266D0) and the creation (0x10626770, which reads the D3D format out of the format
// tables at 0x10E3464C and 0x110BB934). The member names are guesses.
#ifndef PURE3D_PDDI_DX9_DXINDEXBUFFER_H
#define PURE3D_PDDI_DX9_DXINDEXBUFFER_H

#include "code/pure3d/pddi.h"
#include "code/pure3d/pddi/dx9/d3d9.h"

namespace pure3d
{
	// The description an index buffer is created from (0x10626770 reads +0, +4 and +8)
	struct IndexBufferDescription
	{
		// How many indices
		int count;             // +0
		// The size of one index, which is what the format tables are indexed by
		int indexSize;         // +4
		unsigned int usage;    // +8
	};

	// The six-word block an index buffer keeps at +0x1C: its constructor (0x10611BD0) clears all but the fourth
	// word. Name and members are guesses.
	class dxIndexBufferState
	{
	public:
		dxIndexBufferState();
		void Clear()
		{
			unknown0 = 0;
			unknown4 = 0;
			unknown8 = 0;
			unknownC = 0;
			unknown10 = 0;
			unknown14 = 0;
		}

		int unknown0;
		int unknown4;
		int unknown8;
		int unknownC;
		int unknown10;
		int unknown14;
	};

	// 0x10E3464C: the bytes one index of each size takes (0: the size is not one the device takes)
	extern int gIndexSizes[];
	// 0x110BB934: the Direct3D format each size is stored in
	extern int gIndexFormatIndices[];
	// 0x10E34670: the Direct3D format codes those indices name
	extern int gD3DIndexFormats[];

	// 0x10624B10: makes an index buffer in the default pool and records it (the unit it lives in is not
	// reconstructed yet)
	bool PoolAllocateIndexBuffer(int length, unsigned int usage, unsigned int format, IDirect3DIndexBuffer9** buffer);

	class dxIndexBuffer : public pddiObject
	{
	public:
		// 0x106266D0
		dxIndexBuffer();
		// 0x10626770
		void Create(const IndexBufferDescription* description);

		bool unknown8;
		// The buffer the device made
		IDirect3DIndexBuffer9* buffer;    // +0xC
		unsigned int unknown10;           // +0x10
		bool unknown14;
		// 1 while the device owns the buffer, 0 when it is the default pool's
		int unknown18;                    // +0x18
		dxIndexBufferState state;         // +0x1C
		int unknown34;                    // +0x34
	};
}

#endif
