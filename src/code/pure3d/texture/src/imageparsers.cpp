// The PNG and Targa readers of the texture module (RTTI pure3d::PNGParser and pure3d::TGAParser; unit 0x1073CC70 -
// 0x1073DFF0 in the engine, file name guessed from the classes). Names are guesses.
#include <string.h>

#include "code/pure3d/pddi/dx9/dxtexture.h"
#include "code/pure3d/texture/texture.h"

namespace pure3d
{
	// 0x10E5DBF0: the bits a pixel of each texture format takes (this unit's copy of the table; name guess)
	static const int sImageFormatBits[37] =
	{
		0, 0x10, 0x18, 0x10, 0x10, 0x20, 0x20, 0x20, 0x40, 0x40, 0x80, 0x10, 0x20, 0x20, 0x40, 0x10, 0x20, 0x10,
		0x18, 0x20, 8, 0x10, 0x10, 0x20, 8, 0x10, 0x10, 0x20, 0x10, 0x20, 0x20, 0x40, 4, 8, 8, 8, 8
	};

	// The 18 bytes of a Targa file's header (and two bytes of padding)
	struct TGAHeader
	{
		unsigned char idLength;
		unsigned char colourMapType;
		unsigned char imageType;
		unsigned short colourMapStart;
		unsigned short colourMapLength;
		unsigned char colourMapDepth;
		unsigned short xOrigin;
		unsigned short yOrigin;
		unsigned short width;
		unsigned short height;
		unsigned char bits;
		unsigned char descriptor;
	};

	// The reads of the Targa header (inline in the engine: each one has a temporary of its own)
	__forceinline unsigned char ReadHeaderByte(content::ChunkStream* stream)
	{
		unsigned char value;
		stream->Read(&value, 1, 1, 1);
		return value;
	}

	__forceinline unsigned short ReadHeaderShort(content::ChunkStream* stream)
	{
		unsigned short value;
		stream->Read(&value, 1, 2, 1);
		return value;
	}

	// FUNCTION: ENGINE 0x1073D100
	PNGParser::~PNGParser()
	{
	}

	// FUNCTION: ENGINE 0x1073D110
	bool PNGParser::IsSupportedFormat(unsigned int format)
	{
		switch (format)
		{
		case 1:
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1073D130
	Texture* PNGParser::Load(core::IRefCount* stream, const char* name, int usage, bool flag, Texture* source)
	{
		return Parse(stream, 1, usage, 1, 1, 0, 0, 0);
	}

	// FUNCTION: ENGINE 0x1073D8A0
	TGAParser::~TGAParser()
	{
	}

	// FUNCTION: ENGINE 0x1073D8B0
	bool TGAParser::IsSupportedFormat(unsigned int format)
	{
		switch (format)
		{
		case 2:
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1073D8D0
	Texture* TGAParser::Load(core::IRefCount* stream, const char* name, int usage, bool flag, Texture* source)
	{
		return Parse(stream, 1, usage, 1, 1, 0, 0, 0);
	}

	// The engine calls the two helpers below (each has one caller) out of line
#pragma auto_inline(off)

	// FUNCTION: ENGINE 0x1073D280
	// NONMATCHING: the engine's static helper takes the stream in eax and the header in esi (this compiler picks ecx and eax),
	// the rest of the body is the engine's (best 17 %)
#ifdef NONMATCHING
	// Reads the header and makes the texture the image is read into (or checks the one given)
	static Texture* ReadTGAHeader(content::ChunkStream* stream, TGAHeader* header, int type, int usage, int levels,
		int depth, Texture* existing)
	{
		header->idLength = ReadHeaderByte(stream);
		header->colourMapType = ReadHeaderByte(stream);
		header->imageType = ReadHeaderByte(stream);
		header->colourMapStart = ReadHeaderShort(stream);
		header->colourMapLength = ReadHeaderShort(stream);
		header->colourMapDepth = ReadHeaderByte(stream);
		header->xOrigin = ReadHeaderShort(stream);
		header->yOrigin = ReadHeaderShort(stream);
		header->width = ReadHeaderShort(stream);
		header->height = ReadHeaderShort(stream);
		header->bits = ReadHeaderByte(stream);
		header->descriptor = ReadHeaderByte(stream);
		stream->Skip(header->idLength);
		if (header->imageType == 2 && (header->bits == 0x20 || header->bits == 0x18))
		{
			if (existing == 0)
			{
				TextureDescription description;
				description.type = type;
				description.levels = levels;
				description.depth = depth;
				description.width = header->width;
				description.height = header->height;
				description.format = 5;
				description.usage = usage;
				Texture* texture = new Texture();
				if (!texture->Create(&description, 0))
				{
					texture->Release();
					return 0;
				}
				return texture;
			}
			if (existing->info->description.format == 5)
			{
				return existing;
			}
		}
		return 0;
	}

#endif

	// FUNCTION: ENGINE 0x1073D610
	// NONMATCHING: same body, other registers for the header and the row pointers (best 32 %)
#ifdef NONMATCHING
	// Reads the rows of the image into a level of the texture, bottom up unless the header says otherwise; the 24 bit
	// rows get an opaque alpha byte
	static void ReadTGAPixels(int level, const TGAHeader* header, content::ChunkStream* stream, Texture* texture,
		int slice)
	{
		TextureLock lock;
		memset(&lock, 0, sizeof(lock));
		if (texture->info->Lock(&lock, 2, level, slice) && header->width == lock.width && header->height == lock.height)
		{
			unsigned int rowBytes = sImageFormatBits[lock.format] * (unsigned int)lock.width >> 3;
			unsigned char* row = (unsigned char*)lock.offset;
			int pitch = lock.pitch;
			if ((~header->descriptor & 0x20) != 0)
			{
				row = row + (lock.height - 1) * pitch;
				pitch = -pitch;
			}
			if (header->bits == 0x20)
			{
				for (unsigned int y = 0; y < (unsigned int)lock.height; y++)
				{
					stream->Read(row, rowBytes, 1, 1);
					row += pitch;
				}
				texture->info->Unlock();
				return;
			}
			if (header->bits == 0x18)
			{
				unsigned char* line = new unsigned char[lock.width * 3];
				for (unsigned int y = 0; y < (unsigned int)lock.height; y++)
				{
					stream->Read(line, lock.width * 3, 1, 1);
					unsigned char* source = line;
					unsigned char* target = row;
					for (unsigned int x = 0; x < (unsigned int)lock.width * 3; x += 3)
					{
						target[0] = source[0];
						target[1] = source[1];
						target[2] = source[2];
						target[3] = 0xFF;
						source += 3;
						target += 4;
					}
					row += pitch;
				}
				delete[] line;
			}
			texture->info->Unlock();
		}
	}

#endif

#pragma auto_inline(on)

	// FUNCTION: ENGINE 0x1073D8F0
	// NONMATCHING: calls the two helpers above with the engine's register arguments (best 94 %)
#ifdef NONMATCHING
	Texture* TGAParser::Parse(core::IRefCount* reader, int type, int usage, int levels, int depth, Texture* existing,
		int level, int slice)
	{
		content::ChunkStream* stream = static_cast<content::ChunkStream*>(reader);
		TGAHeader header;
		Texture* texture = ReadTGAHeader(stream, &header, type, usage, levels, depth, existing);
		if (texture == 0)
		{
			return 0;
		}
		ReadTGAPixels(level, &header, stream, texture, slice);
		return texture;
	}
#endif
}
