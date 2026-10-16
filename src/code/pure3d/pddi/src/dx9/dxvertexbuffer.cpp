// pure3d::dxVertexBuffer, the Direct3D 9 vertex buffer of the pddi layer (unit around 0x106262D0 - 0x106266D0; the
// file name is guessed, no assert path survives).
#include <string.h>

#include "code/pure3d/pddi/dx9/dxvertexbuffer.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x106262D0
	dxVertexBuffer::dxVertexBuffer() : unknown8(0), unknownC(0), unknown10(0), unknown130(1), unknown134(0),
		unknown138(-1)
	{
		memset(&declaration, 0, sizeof(declaration));
	}

	// FUNCTION: ENGINE 0x10625900
	int dxVertexBuffer::GetUnknown14()
	{
		return declaration.unknown0;
	}
}
