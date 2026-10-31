// pure3d's texture loading: the parsers that turn a file stream into a pure3d::Texture (RTTI: pure3d::TextureParser
// and its implementation pure3d::DDSParser) and the loader that keeps them. The module's directory is
// code/pure3d/texture/src/ (docs/original_tree.md has bmp.cpp there); this unit runs from 0x10729180 (the texture
// object and its upload helpers) to 0x1072B7F0 (the DDS parser). Slot and member names are guesses.
#ifndef PURE3D_TEXTURE_TEXTURE_H
#define PURE3D_TEXTURE_TEXTURE_H

#include "code/content/chunkhandler.h"
#include "code/core/memory/imemoryallocator.h"
#include "code/core/name.h"
#include "code/pure3d/primitive.h"

namespace engine
{
	namespace render
	{
		// 0x1128186A: whether the textures of this load may be uploaded (declared in the render unit)
		extern bool gTextureLoadFlag;
	}
}

namespace pure3d
{
	// The chunk handler that turns a texture chunk of a P3D stream into a pure3d::Texture (RTTI: pure3d::TextureLoader,
	// 8 vftable slots; slot 7 is LoadObject). The destructor is declared first and not defined here, so that the
	// class's key function stays in the engine's copy of the unit and this file emits no vftable of its own.
	class TextureLoader : public content::SimpleChunkHandler
	{
	public:
		virtual ~TextureLoader();

		// 0x1072A470: the texture the chunk's image makes, written into `object` under the name `name`. The reader
		// is the chunk the caller opened, `flags` is one of its words.
		virtual void LoadObject(core::IRefCount** object, content::ObjectName* name, content::ChunkReader* reader,
			content::LoadInventory* inventory);

	private:
		// 0x1072A1E0: the texture of the chunk's image, or null (name guess)
		Texture* FindTexture(content::ChunkReader* reader, bool flag, int unknown);
	};

	// Reads an image file into the texture it was made for (RTTI: pure3d::TextureParser, 4 slots: the deleting
	// destructor and the three below). Only the DDS parser implements it so far.
	class TextureParser
	{
	public:
		virtual ~TextureParser()
		{
		}
		// True when the parser can turn the texture's pixel format into one it writes
		virtual bool IsSupportedFormat(unsigned int format) = 0;
		// Reads the image of a stream into the texture (the parser's own, or a new one made like `source`); the
		// texture, or null when the file is not an image it can read. `flag` asks for the top level to be dropped
		// and is cleared when the image cannot do without it.
		virtual Texture* Load(core::IRefCount* stream, const char* name, int usage, bool flag, Texture* source) = 0;
		// Checks the block's own header and uploads one level of its image into `texture`, or into a new one when
		// there is none; the texture, or null
		virtual Texture* Parse(core::IRefCount* reader, int type, int usage, int levels, int depth, Texture* existing,
			int level, int slice) = 0;
	};

	// The DirectDraw surface reader (RTTI: pure3d::DDSParser, 16 bytes): the texture it uploads into and the width
	// and height it was asked for.
	class DDSParser : public TextureParser
	{
	public:
		DDSParser();
		DDSParser(Texture* newTexture, unsigned int newWidth, unsigned int newHeight);
		virtual ~DDSParser();

		virtual bool IsSupportedFormat(unsigned int format);
		virtual Texture* Load(core::IRefCount* stream, const char* name, int usage, bool flag, Texture* source);
		virtual Texture* Parse(core::IRefCount* reader, int type, int usage, int levels, int depth, Texture* existing,
			int level, int slice);

		Texture* texture;
		unsigned int width;
		unsigned int height;
	};

	// The PNG reader (RTTI: pure3d::PNGParser, 4 bytes): reads and writes the files through the zlib of the image
	class PNGParser : public TextureParser
	{
	public:
		// 0x1073D250
		PNGParser()
		{
		}
		// 0x1073D100; the scalar deleting destructor is 0x1073D260
		virtual ~PNGParser();
		// 0x1073D110
		virtual bool IsSupportedFormat(unsigned int format);
		// 0x1073D130
		virtual Texture* Load(core::IRefCount* stream, const char* name, int usage, bool flag, Texture* source);
		// 0x1073D150
		virtual Texture* Parse(core::IRefCount* reader, int type, int usage, int levels, int depth, Texture* existing,
			int level, int slice);
	};

	// The Targa reader (RTTI: pure3d::TGAParser, 4 bytes): uncompressed 24 and 32 bit true colour images
	class TGAParser : public TextureParser
	{
	public:
		// 0x1073D950
		TGAParser()
		{
		}
		// 0x1073D8A0; the scalar deleting destructor is 0x1073D960
		virtual ~TGAParser();
		// 0x1073D8B0: format 2
		virtual bool IsSupportedFormat(unsigned int format);
		// 0x1073D8D0
		virtual Texture* Load(core::IRefCount* stream, const char* name, int usage, bool flag, Texture* source);
		// 0x1073D8F0
		virtual Texture* Parse(core::IRefCount* reader, int type, int usage, int levels, int depth, Texture* existing,
			int level, int slice);
	};

	// The BMP reader (RTTI: pure3d::BMPParser, 4 bytes; the unit is code/pure3d/texture/src/bmp.cpp)
	class BMPParser : public TextureParser
	{
	public:
		virtual ~BMPParser()
		{
		}
		// 0x107B5310: format 3
		virtual bool IsSupportedFormat(unsigned int format);
		// 0x107B5320
		virtual Texture* Load(core::IRefCount* stream, const char* name, int usage, bool flag, Texture* source);
		// 0x107B5910
		virtual Texture* Parse(core::IRefCount* reader, int type, int usage, int levels, int depth, Texture* existing,
			int level, int slice);
	};

	// The reader of images the device itself reads from memory (RTTI: pure3d::TextureMemoryImageParser, 4 bytes)
	class TextureMemoryImageParser : public TextureParser
	{
	public:
		// 0x107B5C60; the scalar deleting destructor is 0x107B5C70
		TextureMemoryImageParser()
		{
		}
		virtual ~TextureMemoryImageParser()
		{
		}
		// 0x107B5B50: the formats 0x1B - 0x1D
		virtual bool IsSupportedFormat(unsigned int format);
		// 0x107B5B70
		virtual Texture* Load(core::IRefCount* stream, const char* name, int usage, bool flag, Texture* source);
		// 0x107B5BE0
		virtual Texture* Parse(core::IRefCount* reader, int type, int usage, int levels, int depth, Texture* existing,
			int level, int slice);
	};

	// The stream the texture writers put a DDS file into (a file or a memory block; the slots before Write are not
	// reconstructed, the class name is a guess)
	class OutputStream : public core::IRefCount
	{
	public:
		virtual void Slot3();
		virtual void Slot4();
		virtual void Slot5();
		virtual void Slot6();
		virtual void Slot7();
		virtual void Slot8();
		virtual void Slot9();
		// Slot 10: writes `count` blocks of `bytes` bytes
		virtual void Write(const void* data, unsigned int bytes, unsigned int count);
	};

	// 0x1072B360: writes the texture's levels to a stream as a DDS file; false when its format has no DDS form
	bool SaveTexture(OutputStream* stream, Texture* texture);
}

#endif
