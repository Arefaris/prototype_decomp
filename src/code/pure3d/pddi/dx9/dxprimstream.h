// pure3d::dxPrimStream (RTTI name; base pure3d::pddiPrimStream): the Direct3D 9 primitive stream: a pool of vertex
// buffers the stream hands out a slice of at a time. The layout follows the constructor (0x1062AA90); every member
// name is a guess.
#ifndef PURE3D_PDDI_DX9_DXPRIMSTREAM_H
#define PURE3D_PDDI_DX9_DXPRIMSTREAM_H

#include "code/pure3d/pddi.h"
#include "code/pure3d/pddi/dx9/d3d9.h"

namespace pure3d
{
	class dxPrimStream : public pddiPrimStream
	{
	public:
		// 0x1062AA90: takes the vertex format length the stream's buffers are made with
		dxPrimStream(unsigned int length);

		int unknown4;
		int unknown8;
		int unknownC;
		int unknown10;
		int unknown14;
		int unknown18;
		int unknown1C;
		int unknown20;
		unsigned char unknown24[0x104];
		// The format length the constructor was given
		int length;
		// One vertex buffer per stream slot (the count is the file's gStreamBufferCount)
		IDirect3DVertexBuffer9** buffers;
		// The buffer of the current slot
		IDirect3DVertexBuffer9* current;
		int unknown134;
		bool unknown138;
		unsigned char unknown139[7];
		int unknown140;
		// The slot whose buffer is current
		int slot;
	};
}

#endif
