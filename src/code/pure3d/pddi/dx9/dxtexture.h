// pure3d::dxTexture (RTTI name; base pure3d::pddiObject): a texture of the Direct3D 9 back end: the description it
// was asked for, the D3D texture and its default-pool bookkeeping. The layout follows the constructor (0x1061C400)
// and the destructor (0x1061CBE0); every member name is a guess.
#ifndef PURE3D_PDDI_DX9_DXTEXTURE_H
#define PURE3D_PDDI_DX9_DXTEXTURE_H

#include "code/pure3d/pddi.h"
#include "code/pure3d/pddi/dx9/d3d9.h"

namespace pure3d
{
	// A four-byte reference-counted holder: the constructor does nothing (the owner clears it), the destructor
	// releases what it holds (0x1061CA90 - 0x1061CBB0 are the copies the texture's members use)
	class dxTextureRef
	{
	public:
		~dxTextureRef();

		void* pointer;
	};

	// The description a texture is created from (0x1061CD70 reads +0xC, +0x10, +0x14, +0x1C and +0x34); only what
	// those reads need is named, the type itself belongs to the pddi base unit
	struct TextureDescription;
	// What the second creation form (0x1061D010) adds to the description
	struct TextureLevels;

	class dxTexture : public pddiObject
	{
	public:
		// 0x1061C400: the device argument is not read (the pool manager owns the device)
		dxTexture(IDirect3DDevice9* device);
		// 0x1061CBE0
		virtual ~dxTexture();
		// 0x1061CD70 / 0x1061D010
		bool Create(const TextureDescription* description);
		bool Create(const TextureDescription* description, const TextureLevels* levels);

		// 1: a 2D texture, 2: a cube texture, 3: a volume texture (the CreateTexture / CreateCubeTexture /
		// CreateVolumeTexture branches of 0x1061CD70)
		int unknown8;
		// The levels the texture was asked for
		int unknownC;
		int unknown10;
		int unknown14;
		int unknown18;
		int unknown1C;
		// Bit 1 selects the "scaled" creation path (0x1061CD70)
		unsigned int unknown20;
		int unknown24;
		int unknown28;
		int unknown2C;
		int unknown30;
		int unknown34;
		int unknown38;
		bool unknown3C;
		dxTextureRef unknown40;
		// The per-level data: 8 bytes each, a count and a pointer
		int unknown44;
		IDirect3DTexture9* texture;
		dxTextureRef unknown4C;
		dxTextureRef unknown50;
		dxTextureRef unknown54;
		int unknown58;
		int unknown5C;
		int unknown60;
		int unknown64;
		int unknown68;
		int unknown6C;
		int unknown70;
		int unknown74;
		int unknown78;
		bool unknown7C;
		// Bytes of texture memory this texture counts for
		int unknown80;
		bool unknown84;
		dxTextureRef unknown88;
		int unknown8C;
	};
}

#endif
