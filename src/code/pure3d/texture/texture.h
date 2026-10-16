// pure3d's texture loading: the parsers that turn a file stream into a pure3d::Texture (RTTI: pure3d::TextureParser
// and its implementation pure3d::DDSParser) and the loader that keeps them. The module's directory is
// code/pure3d/texture/src/ (docs/original_tree.md has bmp.cpp there); this unit runs from 0x10729180 (the texture
// object and its upload helpers) to 0x1072B7F0 (the DDS parser). Slot and member names are guesses.
#ifndef PURE3D_TEXTURE_TEXTURE_H
#define PURE3D_TEXTURE_TEXTURE_H

#include "code/core/memory/imemoryallocator.h"
#include "code/core/name.h"
#include "code/pure3d/primitive.h"

namespace pure3d
{
	// Reads an image file into the texture it was made for (RTTI: pure3d::TextureParser, 4 slots: the deleting
	// destructor and the three below). Only the DDS parser implements it so far.
	class TextureParser
	{
	public:
		virtual ~TextureParser() = 0;
		// True when the parser can turn the texture's pixel format into one it writes
		virtual bool IsSupportedFormat(unsigned int format) = 0;
		// Reads the image of a stream into the texture
		virtual void Load(core::IRefCount* stream, const char* name, int unknown, bool flag, int zero) = 0;
		// Checks the block's own header and loads it (the arguments are the loader's)
		virtual unsigned int Parse(core::IRefCount* reader, unsigned int a, unsigned int b, unsigned int c,
			unsigned int d, unsigned int e, unsigned int f, unsigned int g) = 0;
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
		virtual void Load(core::IRefCount* stream, const char* name, int unknown, bool flag, int zero);
		virtual unsigned int Parse(core::IRefCount* reader, unsigned int a, unsigned int b, unsigned int c,
			unsigned int d, unsigned int e, unsigned int f, unsigned int g);

		Texture* texture;
		unsigned int width;
		unsigned int height;
	};
}

#endif
