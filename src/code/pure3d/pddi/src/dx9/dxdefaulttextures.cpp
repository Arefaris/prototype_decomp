// The textures the Direct3D 9 back end keeps for materials without one (unit after dxtexture.cpp, around
// 0x1061D3A0; the file name is a guess). It is a unit of its own: compiled behind dxTexture::Lock in dxtexture.cpp,
// the compiler drops the zero stores into the lock record that Lock never reads (bits, slice, format, size, the
// word at +0x1C) and the function shrinks to 1408 bytes; the engine keeps all nine, so its compiler did not see Lock.
#include <math.h>
#include <new>

#include "code/math/mathconstants.h"
#include "code/math/mathutils.h"
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

	// 0x1061CBB0: holds a new texture in one of the slots above (dxtexture.cpp)
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
		unsigned int* __restrict row = (unsigned int*)lock.offset; \
		for (int y = lock.height - 1; y >= 0; y--) \
		{ \
			for (int x = 0; x < lock.width; x++) \
			{ \
				row[x] = (colour); \
			} \
			row = (unsigned int*)((char*)row + lock.pitch); \
		} \
		(target)->Unlock(); \
	}

	// One pixel of a ramp: the value clamped to a byte in all four channels
	inline unsigned int RampPixel(int value)
	{
		int clamped = math::Min(math::Max(value, 0), 0xFF);
		return (((clamped << 8) | clamped) << 8 | clamped) << 8 | clamped;
	}

	// FUNCTION: ENGINE 0x1061D3A0
	// NONMATCHING: 75 % (was 36 %), the same size; the clamp of the ramps comes out as another tree. The engine tests
	// `value < 0` first and then `value > 0xFF` on both paths (each leaf sets the value once; the cosine cases
	// cross-jump into the first two cases' trees), this compiler folds the negative path or turns the first test into
	// a cmov (two ifs on the value, ternaries, Min / Max in both orders, nested tests). What made the rest: the fills
	// write through a `__restrict` row and read the width and pitch of the lock in the loops (the engine's zero in edi
	// and one in ebx, set again after every fill), every description sets its levels, depth and format again, the ramp
	// computes `t` before the switch, each case packs its own pixel (an inline per case, which the cosine cases share
	// with the first two), the first ramp's pixel is built with multiplications (shifts of one value become the
	// nested form the clamped cases use) and the cosine ramps are a float `(cos + 1) * 0.5f` times `255.5f` in two
	// statements (in one expression the two constants fold into 127.75).
	// The engine's tree is what `int clamped = value; if (value < 0) clamped = 0; if (value > 0xFF) clamped = 0xFF;`
	// means when the first test is not if-converted: the second test is copied into both paths of the first (the
	// value's register compared again on the negative path) and the zero sinks into its leaf. This compiler turns
	// the first test into `cmovs` from the function's zero register (edi) whenever that register exists (in a unit
	// without one it branches, but does not copy the second test); the result as unsigned char / short / long, the
	// tests nested explicitly (setcc on the negative side), `else if` forms, /Os, /O1 and /Oy- keep the cmov or
	// setcc. 75.3 % as it is.
#ifdef NONMATCHING
	void CreateDefaultTextures(IDirect3DDevice9* device)
	{
		TextureLock lock;
		AssignTextureSlot(&gWhiteTexture, new dxTexture(device));
		AssignTextureSlot(&gBlackTexture, new dxTexture(device));
		AssignTextureSlot(&gTransparentTexture, new dxTexture(device));
		TextureDescription description;
		description.width = 8;
		description.height = 8;
		description.levels = 1;
		description.depth = 1;
		description.type = 1;
		description.format = 5;
		gWhiteTexture->Create(&description);
		gBlackTexture->Create(&description);
		gTransparentTexture->Create(&description);
		FILL_TEXTURE(gWhiteTexture, 0xFFFFFFFF)
		FILL_TEXTURE(gBlackTexture, 0xFF000000)
		FILL_TEXTURE(gTransparentTexture, 0)
		description.width = 2;
		description.height = 2;
		description.levels = 1;
		description.depth = 1;
		description.format = 5;
		AssignTextureSlot(&gFlatNormalTexture, new dxTexture(device));
		gFlatNormalTexture->Create(&description);
		FILL_TEXTURE(gFlatNormalTexture, 0xFF7F7FFF)
		description.width = 0x100;
		description.height = 8;
		description.levels = 1;
		description.depth = 1;
		description.format = 5;
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
				float t = (float)x * (1.0f / 255.0f);
				switch (y)
				{
				case 0:
					{
						int value = 0xFF - x;
						row[x] = (value * 0x1000000) | (value * 0x100) | (value * 0x10000) | value;
					}
					break;
				case 1:
					row[x] = RampPixel((((x + 1) * (x + 1)) >> 8) - 1);
					break;
				case 2:
					row[x] = RampPixel((((0x100 - x) * (0x100 - x)) >> 8) - 1);
					break;
				case 3:
					{
						static float frequency = math::PI;
						float ramp = (cos(t * frequency) + 1.0f) * 0.5f;
						row[x] = RampPixel((int)(ramp * 255.5f));
					}
					break;
				case 4:
					{
						static float frequencyA = math::PI;
						static float frequencyB = math::PI * 8.0f;
						float ramp = (((cos(t * frequencyA) + 1.0f) * 0.5f) * (cos(t * frequencyB) + 1.0f)) * 0.5f;
						row[x] = RampPixel((int)(ramp * 255.5f));
					}
					break;
				case 5:
					row[x] = 0xFFFFFFFF;
					if (x == 0xFF)
					{
						row[0xFF] = 0;
					}
					break;
				default:
					row[x] = 0;
					break;
				}
			}
			row = (unsigned int*)((char*)row + lock.pitch);
		}
		gRampTexture->Unlock();
	}
#endif
}
