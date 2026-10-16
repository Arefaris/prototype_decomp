// pure3d::dxContext, the Direct3D 9 device of the pddi layer: only the buffer and texture factories the neighbouring
// dx9 units call (unit around 0x1061B550; the file name is guessed, no assert path survives).
#include "code/pure3d/pddi/dx9/dxcontext.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x1061B530
	int dxContext::GetUnknown8()
	{
		return unknown8;
	}

	// FUNCTION: ENGINE 0x1061B540
	IDirect3DDevice9* dxContext::GetUnknownC()
	{
		return unknownC;
	}

	// FUNCTION: ENGINE 0x1061B550
	dxTexture* dxContext::NewTexture(const TextureDescription* description)
	{
		dxTexture* texture = new dxTexture(unknownC);
		if (!texture->Create(description))
		{
			delete texture;
			return 0;
		}
		return texture;
	}

	// FUNCTION: ENGINE 0x1061B5A0
	dxTexture* dxContext::NewTexture(const TextureDescription* description, const TextureLevels* levels)
	{
		dxTexture* texture = new dxTexture(unknownC);
		if (!texture->Create(description, levels))
		{
			delete texture;
			return 0;
		}
		return texture;
	}

	// FUNCTION: ENGINE 0x1061B600
	dxVertexBuffer* dxContext::NewVertexBuffer(const VertexBufferDescription* description)
	{
		dxVertexBuffer* buffer = new dxVertexBuffer();
		buffer->Create(description);
		return buffer;
	}

	// FUNCTION: ENGINE 0x1061B660
	dxIndexBuffer* dxContext::NewIndexBuffer(const IndexBufferDescription* description)
	{
		dxIndexBuffer* buffer = new dxIndexBuffer();
		buffer->Create(description);
		return buffer;
	}
}
