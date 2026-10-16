// The texture unit: pure3d::Texture, the upload helpers that push its levels into the device and the loaders that
// read the image files (pure3d::TextureLoader and the parsers behind it). See texture.h.
//
// Open in this unit: its upload half is compiled with link-time code generation, so the helpers cannot be written in
// C++. The reader at 0x1072AB40 takes its stream in eax and the descriptor it fills in esi, the header decoder at
// 0x1072B600 takes the decoded header in esi and one of the loader's arguments in eax, and the predicates 0x1072A530
// (is the format a depth one), 0x1072AD80 (round both sizes up to four) and 0x1072A540 (the pixel format of a DDS
// header) take their argument in eax and answer in eax. Every caller has to set those registers itself, which is
// what blocks 0x1072B470, 0x1072B6D0, 0x1072ADB0 and 0x1072AF80 below.
#include "code/pure3d/texture/texture.h"
#include "code/core/refptr.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x10729AE0
	Texture::Texture()
	{
		info = 0;
	}

	// FUNCTION: ENGINE 0x1072A0E0
	Texture::~Texture()
	{
		core::SafeRelease(info);
	}

	// FUNCTION: ENGINE 0x1072B420
	bool DDSParser::IsSupportedFormat(unsigned int format)
	{
		switch (format)
		{
		case 5:
		case 6:
		case 8:
		case 10:
		case 0x1A:
		case 0x1C:
			return true;
		}
		return false;
	}
}

#ifdef NONMATCHING
namespace pure3d
{
	// The parts of this unit that are still external: the content library's reader (0x1060B260 is its Read) and the
	// helpers above, kept as declarations until their own units are reconstructed.
	class TextureReader : public core::IRefCount
	{
	public:
		void Read(void* destination, unsigned int size, unsigned int count, unsigned int unknown);
	};

	struct DDSParserImage;

	bool ReadDDSHeader(TextureReader* stream, DDSParserImage* image);
	bool TextureLoadInfo(Texture* texture, DDSParserImage* image, int unknown);
	void UploadLevels(TextureReader* stream, Texture* texture, DDSParserImage* image, bool flag);
	void UploadMipChain(TextureReader* stream, Texture* texture, DDSParserImage* image, bool flag);
	void UploadSurface(TextureReader* stream, DDSParserImage* image, bool flag);
	unsigned int DecodeDDSHeader(const unsigned int* header, unsigned int a, unsigned int b, unsigned int c,
		unsigned int d, unsigned int e, unsigned int f, unsigned int g);

	// What the readers fill in before the upload runs (0x38 bytes): the size of the image, the pixel format the
	// device wants and the four colour masks. The names are guesses.
	struct DDSParserImage
	{
		unsigned int unknown0;
		unsigned int unknown4;
		unsigned int unknown8;
		unsigned int unknownC;
		unsigned int unknown10;
		unsigned int unknown14;
		unsigned int unknown18;
		int format;
		int unknown20;
		unsigned int width;
		unsigned int height;
		unsigned int unknown2C;
		unsigned int unknown30;
		bool unknown34;
	};

	// FUNCTION: ENGINE 0x1072B470
	// NONMATCHING: the reader helper takes its stream in eax and its descriptor in esi.
	void DDSParser::Load(core::IRefCount* stream, const char* name, int unknown, bool flag, int zero)
	{
		DDSParserImage image;
		image.unknown0 = 0;
		image.unknown4 = 0;
		image.unknown8 = 0;
		image.unknownC = 0;
		image.unknown10 = 0;
		image.unknown14 = 0;
		image.unknown18 = 0;
		image.unknown34 = true;
		image.format = -1;
		image.unknown20 = -1;
		image.width = 1;
		image.height = 0;
		image.unknown2C = 0;
		image.unknown30 = 0;
		if (!ReadDDSHeader(static_cast<TextureReader*>(stream), &image))
		{
			return;
		}
		Texture* target = texture;
		if (target == 0)
		{
			target = new Texture();
			if (!TextureLoadInfo(target, &image, zero))
			{
				target->Release();
				return;
			}
		}
		else if (target->info->unknown20 != image.unknown18)
		{
			return;
		}
		// the three upload paths: the levels the file names (1), its mip chain (2) or one surface (3)
		switch (target->info->kind)
		{
		case 1:
			UploadLevels(static_cast<TextureReader*>(stream), target, &image, flag);
			break;
		case 2:
			UploadMipChain(static_cast<TextureReader*>(stream), target, &image, flag);
			break;
		case 3:
			UploadSurface(static_cast<TextureReader*>(stream), &image, flag);
			break;
		}
	}

	// FUNCTION: ENGINE 0x1072B6D0
	// NONMATCHING: the header decoder takes the header in esi and one of the loader's arguments in eax.
	unsigned int DDSParser::Parse(core::IRefCount* reader, unsigned int a, unsigned int b, unsigned int c,
		unsigned int d, unsigned int e, unsigned int f, unsigned int g)
	{
		TextureReader* stream = static_cast<TextureReader*>(reader);
		char magic[4];
		stream->Read(magic, 4, 1, 1);
		if (strncmp(magic, "DDS ", 4) != 0)
		{
			return 0;
		}
		unsigned int header[0x1F];
		stream->Read(header, 0x1F, 4, 1);
		if (header[0] != 0x7C || (~header[1] & 1) != 0 || (~header[1] & 0x1000) != 0)
		{
			return 0;
		}
		if (header[0x12] != 0x20 || (header[0x1E] & 0x200200) != 0 || header[7] != 0)
		{
			return 0;
		}
		return DecodeDDSHeader(header, a, b, c, d, e, f, g);
	}
}
#endif
