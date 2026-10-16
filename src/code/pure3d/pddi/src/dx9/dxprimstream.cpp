// pure3d::dxPrimStream, the Direct3D 9 primitive stream of the pddi layer (unit around 0x1062AA90; the file name is
// guessed, no assert path survives).
#include <new>

#include "code/pure3d/pddi/dx9/dxprimstream.h"

namespace pure3d
{
	// 0x110BC3B8 / 0x110BC3B4: how many vertex buffers the stream keeps and how many bytes each holds
	extern int gStreamBufferCount;
	extern unsigned int gStreamBufferLength;

	// FUNCTION: ENGINE 0x1062AA90
	dxPrimStream::dxPrimStream(unsigned int bufferLength)
	{
		length = bufferLength;
		unknown138 = false;
		unknown20 = 0;
		unknown4 = 0;
		unknown8 = 0;
		unknownC = 0;
		unknown14 = 0;
		unknown18 = 0;
		unknown134 = 0;
		slot = 0;
		buffers = new IDirect3DVertexBuffer9*[gStreamBufferCount];
		IDirect3DDevice9* device = gD3DDevice;
		for (int i = 0; i < gStreamBufferCount; i++)
		{
			device->lpVtbl->CreateVertexBuffer(device, gStreamBufferLength, 8, 0, D3DPOOL_MANAGED, &buffers[i], 0);
		}
		current = buffers[slot];
		unknown140 = 0;
	}
}
