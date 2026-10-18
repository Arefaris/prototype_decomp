// The textures the Direct3D 9 back end keeps for materials without one (unit after dxtexture.cpp, around
// 0x1061D3A0; the file name is a guess).
#include <math.h>
#include <new>

#include "code/math/mathconstants.h"
#include "code/pure3d/pddi/dx9/dxtexture.h"

namespace pure3d
{
	// 0x11276D4C - 0x11276D5C: the textures every material can fall back on (names are guesses): white, black,
	// transparent, a flat normal map (2x2) and the 256x8 table of ramps
	dxTexture* gWhiteTexture = 0;
	dxTexture* gBlackTexture = 0;
	dxTexture* gTransparentTexture = 0;
	dxTexture* gFlatNormalTexture = 0;
	dxTexture* gRampTexture = 0;

	// 0x1061CBB0: holds a new texture in one of the slots above (another copy of AssignRef; name guess)
	void AssignTextureSlot(dxTexture** slot, dxTexture* value);

	// Locks the first level of a texture and writes one colour into all of it (the engine repeats the block)
#define FILL_TEXTURE(target, colour) \
	{ \
		lock.bits = 0; \
		lock.slice = 0; \
		lock.width = 0; \
		lock.height = 0; \
		lock.format = 0; \
		lock.pitch = 0; \
		lock.size = 0; \
		lock.unknown1C = 0; \
		lock.offset = 0; \
		(target)->Lock(&lock, 2, 0, 0); \
		unsigned int* row = (unsigned int*)lock.offset; \
		int fillWidth = lock.width; \
		int fillPitch = lock.pitch; \
		for (int y = lock.height - 1; y >= 0; y--) \
		{ \
			for (int x = 0; x < fillWidth; x++) \
			{ \
				row[x] = (colour); \
			} \
			row = (unsigned int*)((char*)row + fillPitch); \
		} \
		(target)->Unlock(); \
	}

	// FUNCTION: ENGINE 0x1061D3A0
	// NONMATCHING: the fills compile to the engine's rep stosd, but the register allocation (the zero in ebp
	// against edi,
	// the pitch spilled) and the order of the description's stores differ (best 36 %)
#ifdef NONMATCHING
	void CreateDefaultTextures(IDirect3DDevice9* device)
	{
		TextureLock lock;
		AssignTextureSlot(&gWhiteTexture, new dxTexture(device));
		AssignTextureSlot(&gBlackTexture, new dxTexture(device));
		AssignTextureSlot(&gTransparentTexture, new dxTexture(device));
		TextureDescription description;
		description.type = 1;
		description.levels = 1;
		description.depth = 1;
		description.width = 8;
		description.height = 8;
		description.format = 5;
		gWhiteTexture->Create(&description);
		gBlackTexture->Create(&description);
		gTransparentTexture->Create(&description);
		FILL_TEXTURE(gWhiteTexture, 0xFFFFFFFF)
		FILL_TEXTURE(gBlackTexture, 0xFF000000)
		FILL_TEXTURE(gTransparentTexture, 0)
		description.width = 2;
		description.height = 2;
		AssignTextureSlot(&gFlatNormalTexture, new dxTexture(device));
		gFlatNormalTexture->Create(&description);
		FILL_TEXTURE(gFlatNormalTexture, 0xFF7F7FFF)
		description.width = 0x100;
		description.height = 8;
		AssignTextureSlot(&gRampTexture, new dxTexture(device));
		gRampTexture->Create(&description);
		lock.bits = 0;
		lock.slice = 0;
		lock.width = 0;
		lock.height = 0;
		lock.format = 0;
		lock.pitch = 0;
		lock.size = 0;
		lock.unknown1C = 0;
		lock.offset = 0;
		gRampTexture->Lock(&lock, 2, 0, 0);
		unsigned int* row = (unsigned int*)lock.offset;
		for (int y = lock.height - 1; y >= 0; y--)
		{
			for (int x = 0; x < lock.width; x++)
			{
				int value;
				switch (y)
				{
				case 0:
					value = 0xFF - x;
					row[x] = (value << 24) | (value << 8) | (value << 16) | value;
					continue;
				case 1:
					value = (((x + 1) * (x + 1)) >> 8) - 1;
					break;
				case 2:
					value = (((0x100 - x) * (0x100 - x)) >> 8) - 1;
					break;
				case 3:
					{
						static float frequency = math::PI;
						value = (int)((cos((float)x * (1.0f / 255.0f) * frequency) + 1.0) * 0.5 * 255.5);
					}
					break;
				case 4:
					{
						static float frequencyA = math::PI;
						static float frequencyB = math::PI * 8.0f;
						float t = (float)x * (1.0f / 255.0f);
						value = (int)((((cos(t * frequencyA) + 1.0) * 0.5) * (cos(t * frequencyB) + 1.0)) * 0.5 * 255.5);
					}
					break;
				case 5:
					row[x] = 0xFFFFFFFF;
					if (x == 0xFF)
					{
						row[0xFF] = 0;
					}
					continue;
				default:
					row[x] = 0;
					continue;
				}
				if (value < 0)
				{
					value = 0;
				}
				else if (value > 0xFF)
				{
					value = 0xFF;
				}
				row[x] = (((value << 8) | value) << 8 | value) << 8 | value;
			}
			row = (unsigned int*)((char*)row + lock.pitch);
		}
		gRampTexture->Unlock();
	}
#endif
}
