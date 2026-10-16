// pure3d::dxContext (RTTI name; base pure3d::pddiBaseContext, 69 slots): the Direct3D 9 implementation of the pddi
// device interface. Only the buffer and texture factories the neighbouring units call are reconstructed (unit around
// 0x1061B550; the file name is guessed, no assert path survives).
#ifndef PURE3D_PDDI_DX9_DXCONTEXT_H
#define PURE3D_PDDI_DX9_DXCONTEXT_H

#include "code/pure3d/pddi.h"
#include "code/pure3d/pddi/dx9/dxindexbuffer.h"
#include "code/pure3d/pddi/dx9/dxtexture.h"
#include "code/pure3d/pddi/dx9/dxvertexbuffer.h"

namespace pure3d
{
	class dxContext : public pddiBaseContext
	{
	public:
		// 0x1061B530 / 0x1061B540: the words the factories above use
		int GetUnknown8();
		IDirect3DDevice9* GetUnknownC();
		// 0x1061B550 / 0x1061B5A0: a texture from the pool, released again when the description cannot be built
		dxTexture* NewTexture(const TextureDescription* description);
		dxTexture* NewTexture(const TextureDescription* description, const dxTexture* image);
		// 0x1061B600 / 0x1061B660: a buffer from the pool (the creator's result is dropped)
		dxVertexBuffer* NewVertexBuffer(const VertexBufferDescription* description);
		dxIndexBuffer* NewIndexBuffer(const IndexBufferDescription* description);
	};

	// 0x11276D2C: the device the back end was built on (0x106202F0 installs it); the textures it made keep their
	// bytes of texture memory in its `textureMemory`
	extern dxContext* gContext;
}

#endif
