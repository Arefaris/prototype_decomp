// CFLAGS: /arch:SSE2
// The texture unit: pure3d::Texture, the upload helpers that push its levels into the device and the loaders that
// read the image files (pure3d::TextureLoader and the parsers behind it). See texture.h.
//
// The upload half is a set of file-local functions that call each other with the register conventions the compiler
// picks for them (stream in eax, the description in esi, a stack word for the rest), so they are written in the order
// the original has them and each is declared `static`.
#include <string.h>

#include "code/pure3d/texture/texture.h"
#include "code/core/refptr.h"
#include "code/pure3d/pddi/dx9/dxcontext.h"
#include "code/pure3d/pddi/dx9/dxtexture.h"

namespace pure3d
{
	// 0x1127F358: the Direct3D 9 view of the pddi device (name guess)
	extern dxContext* gPddiDx;

	// A DDS file's pixel format block (32 bytes)
	struct DDSPixelFormat
	{
		unsigned int size;
		unsigned int flags;
		unsigned int fourCC;
		unsigned int bitCount;
		unsigned int redMask;
		unsigned int greenMask;
		unsigned int blueMask;
		unsigned int alphaMask;
	};

	// A DDS file's header, the 124 bytes after the "DDS " magic
	struct DDSHeader
	{
		unsigned int size;
		unsigned int flags;
		unsigned int height;
		unsigned int width;
		unsigned int linearSize;
		unsigned int depth;
		unsigned int mipMapCount;
		unsigned int reserved1[11];
		DDSPixelFormat format;
		unsigned int caps;
		unsigned int caps2;
		unsigned int caps3;
		unsigned int caps4;
		unsigned int reserved2;
	};

	// The part of a level an upload fills: its size and where it starts (16 bytes, halved for every level)
	struct UploadRect
	{
		unsigned int height;
		unsigned int width;
		unsigned int x;
		unsigned int y;
	};

	// 0x10E5C210: the bits a pixel of each texture format takes (name guess)
	static const int sFormatBits[37] =
	{
		0, 0x10, 0x18, 0x10, 0x10, 0x20, 0x20, 0x20, 0x40, 0x40, 0x80, 0x10, 0x20, 0x20, 0x40, 0x10, 0x20, 0x10,
		0x18, 0x20, 8, 0x10, 0x10, 0x20, 8, 0x10, 0x10, 0x20, 0x10, 0x20, 0x20, 0x40, 4, 8, 8, 8, 8
	};

	// FUNCTION: ENGINE 0x10729AE0
	Texture::Texture()
	{
		info = 0;
	}

	// FUNCTION: ENGINE 0x1072A0E0
	Texture::~Texture()
	{
		ReleaseRef(&info);
	}

	// FUNCTION: ENGINE 0x10729B00
	bool Texture::Create(const TextureDescription* description, const Texture* source)
	{
		if (source != 0)
		{
			dxTexture* image = source->info;
			info = gPddiDx->NewTexture(description, image);
		}
		else
		{
			info = gPddiDx->NewTexture(description);
		}
		if (info == 0)
		{
			return false;
		}
		info->AddRef();
		return true;
	}

	// FUNCTION: ENGINE 0x1072A470
	void TextureLoader::LoadObject(core::IRefCount** object, content::ObjectName* name,
		content::ChunkReader* reader, content::LoadInventory* inventory)
	{
		Texture* texture = FindTexture(reader, engine::render::gTextureLoadFlag, (int)inventory);
		if (texture != 0)
		{
			texture->AddRef();
			*object = texture;
			*name = texture->mName;
		}
	}

	// FUNCTION: ENGINE 0x1072A530
	// Whether the format is one of the block-compressed ones
	static bool IsBlockFormat(int format)
	{
		switch (format)
		{
		case 0x20:
		case 0x21:
		case 0x22:
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1072A540
	// The texture format of a DDS file's pixel format, 0 when there is none
	static int GetFormat(const DDSPixelFormat* format)
	{
		unsigned int flags = format->flags;
		unsigned int bits = format->bitCount;
		if ((flags & 0x40) != 0)
		{
			unsigned int red = format->redMask;
			unsigned int green = format->greenMask;
			unsigned int blue = format->blueMask;
			unsigned int alpha = format->alphaMask;
			if (bits == 0x10 && blue == 0x1F && green == 0x3E0 && red == 0x7C00 && alpha == 0x8000)
			{
				return 3;
			}
			if (bits == 0x10 && blue == 0xF && green == 0xF0 && red == 0xF00 && alpha == 0xF000)
			{
				return 4;
			}
			if (bits == 0x20 && blue == 0xFF && green == 0xFF00 && red == 0xFF0000 && alpha == 0xFF000000)
			{
				return 5;
			}
			if (bits == 0x20 && blue == 0x3FF && green == 0xFFC00 && red == 0x3FF00000 && alpha == 0xC0000000)
			{
				return 6;
			}
			if (bits == 0x20 && red == 0xFF && green == 0xFF00 && blue == 0xFF0000 && alpha == 0xFF000000)
			{
				return 7;
			}
			if (bits == 0x10 && blue == 0x1F && green == 0x7E0 && red == 0xF800)
			{
				return 1;
			}
			if (bits == 0x18 && blue == 0xFF && green == 0xFF00 && red == 0xFF0000)
			{
				return 2;
			}
		}
		else if ((flags & 0x20000) != 0 && (flags & 1) != 0)
		{
			if (bits == 0x10 && format->redMask == 0xFF && format->alphaMask == 0xFF00)
			{
				return 0x1C;
			}
		}
		else if ((flags & 0x20000) != 0)
		{
			unsigned int red = format->redMask;
			if (bits == 8 && red == 0xFF)
			{
				return 0x18;
			}
			if (bits == 0x10 && red == 0xFFFF)
			{
				return 0x19;
			}
		}
		else if ((flags & 2) != 0)
		{
			unsigned int alpha = format->alphaMask;
			if (bits == 8 && alpha == 0xFF)
			{
				return 0x14;
			}
			if (bits == 0x10 && alpha == 0xFFFF)
			{
				return 0x15;
			}
		}
		else if ((flags & 0x80000) != 0)
		{
			unsigned int red = format->redMask;
			unsigned int green = format->greenMask;
			if (bits == 0x10 && red == 0xFF && green == 0xFF00)
			{
				return 0xF;
			}
			if (bits == 0x20 && red == 0xFFFF && green == 0xFFFF0000)
			{
				return 0x10;
			}
		}
		else if ((flags & 4) != 0)
		{
			switch (format->fourCC)
			{
			case 0x6F:
				return 0xB;
			case 0x24:
				return 8;
			case 0x31545844:
				return 0x20;
			case 0x70:
				return 0xD;
			case 0x71:
				return 9;
			case 0x72:
				return 0xC;
			case 0x73:
				return 0xE;
			case 0x74:
				return 10;
			case 0x33545844:
				return 0x21;
			case 0x35545844:
				return 0x22;
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x1072A850
	// Fills in the pixel format block of a DDS file for the texture's format; false when the format has none
	static bool FillPixelFormat(DDSPixelFormat* format, Texture* texture)
	{
		format->size = 0x20;
		bool result = true;
		switch (texture->info->description.format)
		{
		case 3:
			format->flags |= 0x41;
			format->bitCount = 0x10;
			format->redMask = 0x7C00;
			format->greenMask = 0x3E0;
			format->blueMask = 0x1F;
			format->alphaMask = 0x8000;
			break;
		case 4:
			format->flags |= 0x41;
			format->bitCount = 0x10;
			format->redMask = 0xF00;
			format->greenMask = 0xF0;
			format->blueMask = 0xF;
			format->alphaMask = 0xF000;
			break;
		case 5:
			format->flags |= 0x41;
			format->bitCount = 0x20;
			format->redMask = 0xFF0000;
			format->greenMask = 0xFF00;
			format->blueMask = 0xFF;
			format->alphaMask = 0xFF000000;
			break;
		case 6:
			format->flags |= 0x41;
			format->bitCount = 0x20;
			format->redMask = 0x3FF00000;
			format->greenMask = 0xFFC00;
			format->blueMask = 0x3FF;
			format->alphaMask = 0xC0000000;
			break;
		case 7:
			format->flags |= 0x41;
			format->bitCount = 0x20;
			format->redMask = 0xFF;
			format->greenMask = 0xFF00;
			format->blueMask = 0xFF0000;
			format->alphaMask = 0xFF000000;
			break;
		case 1:
			format->flags |= 0x40;
			format->bitCount = 0x10;
			format->redMask = 0xF800;
			format->greenMask = 0x7E0;
			format->blueMask = 0x1F;
			break;
		case 2:
			format->flags |= 0x40;
			format->bitCount = 0x18;
			format->redMask = 0xFF0000;
			format->greenMask = 0xFF00;
			format->blueMask = 0xFF;
			break;
		case 0x1C:
			format->flags |= 0x20001;
			format->bitCount = 0x10;
			format->redMask = 0xFF;
			format->alphaMask = 0xFF00;
			break;
		case 0x18:
			format->flags |= 0x20000;
			format->bitCount = 8;
			format->redMask = 0xFF;
			break;
		case 0x11:
		case 0x19:
			format->flags |= 0x20000;
			format->bitCount = 0x10;
			format->redMask = 0xFFFF;
			break;
		case 0x14:
			format->flags |= 1;
			format->bitCount = 8;
			format->alphaMask = 0xFF;
			break;
		case 0x15:
			format->flags |= 1;
			format->bitCount = 0x10;
			format->alphaMask = 0xFFFF;
			break;
		case 0xF:
			format->flags |= 0x80000;
			format->bitCount = 0x10;
			format->redMask = 0xFF;
			format->greenMask = 0xFF00;
			break;
		case 0x10:
			format->flags |= 0x80000;
			format->bitCount = 0x20;
			format->redMask = 0xFFFF;
			format->greenMask = 0xFFFF0000;
			break;
		case 8:
			format->flags |= 4;
			format->fourCC = 0x24;
			break;
		case 0xB:
			format->flags |= 4;
			format->fourCC = 0x6F;
			break;
		case 0xD:
			format->flags |= 4;
			format->fourCC = 0x70;
			break;
		case 9:
			format->flags |= 4;
			format->fourCC = 0x71;
			break;
		case 0xC:
			format->flags |= 4;
			format->fourCC = 0x72;
			break;
		case 0xE:
			format->flags |= 4;
			format->fourCC = 0x73;
			break;
		case 10:
			format->flags |= 4;
			format->fourCC = 0x74;
			break;
		case 0x20:
			format->flags |= 4;
			format->fourCC = 0x31545844;
			break;
		case 0x21:
			format->flags |= 4;
			format->fourCC = 0x33545844;
			break;
		case 0x22:
			format->flags |= 4;
			format->fourCC = 0x35545844;
			break;
		default:
			return false;
		}
		return result;
	}

	// FUNCTION: ENGINE 0x1072AB40
	// Reads a DDS file's header and describes the texture it makes; `dropTop` is cleared when the file cannot give
	// up its first level
	static bool ReadHeader(content::ChunkStream* stream, TextureDescription* description, bool* dropTop)
	{
		char magic[4];
		stream->Read(magic, 4, 1, 1);
		if (strncmp(magic, "DDS ", 4) != 0)
		{
			return false;
		}
		DDSHeader header;
		stream->Read(&header, 0x1F, 4, 1);
		if (header.size != 0x7C || (~header.flags & 1) != 0 || (~header.flags & 0x1000) != 0 ||
			header.format.size != 0x20)
		{
			return false;
		}
		if ((header.caps2 & 0x200000) != 0)
		{
			if ((~header.flags & 0x800000) != 0)
			{
				return false;
			}
			description->type = 3;
			description->depth = header.depth;
		}
		else if ((header.caps2 & 0x200) != 0)
		{
			if ((~header.caps2 & 0xFC00) != 0)
			{
				return false;
			}
			description->type = 2;
			description->depth = 6;
		}
		else
		{
			description->type = 1;
			description->depth = 1;
		}
		description->width = header.width;
		description->height = header.height;
		unsigned int levels = header.mipMapCount > 0 ? header.mipMapCount : 1;
		description->levels = levels;
		if (*dropTop)
		{
			if (levels > 1 && (int)(header.width >> 1) % 4 == 0 && (int)(header.height >> 1) % 4 == 0)
			{
				description->levels = levels - 1;
				description->width = header.width >> 1;
				description->height = header.height >> 1;
			}
			else
			{
				*dropTop = false;
			}
		}
		int format = GetFormat(&header.format);
		bool ok = format != 0;
		description->format = format;
		return ok;
	}

	// FUNCTION: ENGINE 0x1072AD80
	// Rounds the sizes of a block-compressed level up to whole blocks
	static void RoundToBlock(unsigned int* width, unsigned int* height, int format)
	{
		switch (format)
		{
		case 0x20:
		case 0x21:
		case 0x22:
			{
				unsigned int value = *width;
				if ((value & 3) != 0)
				{
					value = (value & ~3u) + 4;
				}
				*width = value;
				value = *height;
				if ((value & 3) != 0)
				{
					value = (value & ~3u) + 4;
				}
				*height = value;
			}
		}
	}

	// FUNCTION: ENGINE 0x1072ADB0
	// EQUIVALENT: the same reads, locks and stream reads in the same order (84.7 %); the engine keeps the rect in esi
	// and the bits per pixel in ebx where this compiler swaps them, which also turns the operands of the destination's
	// sum and of one multiplication around. The dword-wide test of the rect's x is the constant-first comparison.
	// Reads one level (or the part of it `rect` names) of a slice of the texture from the stream
	static bool UploadLevel(content::ChunkStream* stream, Texture* texture, const UploadRect* rect, int level, int slice)
	{
		TextureLock lock;
		lock.bits = 0;
		lock.slice = 0;
		lock.width = 0;
		lock.height = 0;
		lock.format = 0;
		lock.pitch = 0;
		lock.size = 0;
		lock.unknown1C = 0;
		lock.offset = 0;
		if (!texture->info->Lock(&lock, 2, level, slice))
		{
			return false;
		}
		unsigned int width = lock.width;
		unsigned int height = lock.height;
		RoundToBlock(&width, &height, lock.format);
		unsigned int bits = sFormatBits[lock.format];
		unsigned int rowBytes = bits * width / 8;
		unsigned int xBytes = 0;
		unsigned int y = 0;
		if (rect != 0)
		{
			if (IsBlockFormat(lock.format) && 0 != (rect->x & 3))
			{
				texture->info->Unlock();
				return false;
			}
			width = rect->width;
			height = rect->height;
			RoundToBlock(&width, &height, lock.format);
			xBytes = rect->x * bits / 8;
			y = rect->y;
			rowBytes = bits * width / 8;
		}
		if (IsBlockFormat(lock.format))
		{
			height >>= 2;
			rowBytes *= 4;
			xBytes *= 4;
			y >>= 2;
		}
		char* destination = (char*)lock.offset + xBytes;
		unsigned int count = rowBytes / lock.unknown1C;
		if (y > 0)
		{
			destination += lock.pitch * y;
		}
		for (unsigned int row = y; row < y + height; ++row)
		{
			stream->Read(destination, count, lock.unknown1C, 1);
			destination += lock.pitch;
		}
		texture->info->Unlock();
		return true;
	}

	// FUNCTION: ENGINE 0x1072AF20
	// Steps over the first level of the file, which the texture does not keep
	static void SkipLevel(content::ChunkStream* stream, const TextureDescription* description)
	{
		unsigned int width = description->width * 2;
		unsigned int height = description->height * 2;
		RoundToBlock(&width, &height, description->format);
		// the engine reads the format again after the call instead of keeping it in a register
		int format = *(volatile const int*)&description->format;
		unsigned int rowBytes = sFormatBits[format] * width / 8;
		if (IsBlockFormat(format))
		{
			height >>= 2;
			rowBytes *= 4;
		}
		stream->Skip(rowBytes * height);
	}

	// FUNCTION: ENGINE 0x1072AF80
	// Writes one level of a slice of the texture to the stream
	static void SaveLevel(int level, int slice, OutputStream* stream, Texture* texture)
	{
		TextureLock lock;
		lock.bits = 0;
		lock.slice = 0;
		lock.width = 0;
		lock.height = 0;
		lock.format = 0;
		lock.pitch = 0;
		lock.size = 0;
		lock.unknown1C = 0;
		lock.offset = 0;
		if (texture->info->Lock(&lock, 1, level, slice))
		{
			unsigned int width = lock.width;
			unsigned int height = lock.height;
			RoundToBlock(&width, &height, lock.format);
			unsigned int rowBytes = sFormatBits[lock.format] * width / 8;
			if (IsBlockFormat(lock.format))
			{
				height >>= 2;
				rowBytes *= 4;
			}
			char* source = (char*)lock.offset;
			for (unsigned int row = 0; row < height; ++row)
			{
				stream->Write(source, rowBytes, 1);
				source += lock.pitch;
			}
			texture->info->Unlock();
		}
	}

	// FUNCTION: ENGINE 0x1072B050
	// Reads the levels of a 2D texture; every level of the part is half the size of the one before
	static void UploadLevels(content::ChunkStream* stream, Texture* texture, const TextureDescription* description, bool dropTop, UploadRect* rect)
	{
		if (dropTop == true)
		{
			unsigned int count = texture->info->description.levels + 1;
			for (unsigned int level = 0; level < count; ++level)
			{
				bool done = true;
				if (level == 0)
				{
					SkipLevel(stream, description);
				}
				else
				{
					done = UploadLevel(stream, texture, rect, level - 1, 0);
				}
				if (rect != 0)
				{
					rect->height >>= 1;
					rect->width >>= 1;
					rect->x >>= 1;
					rect->y >>= 1;
				}
				if (!done)
				{
					break;
				}
			}
		}
		else
		{
			unsigned int count = description->levels;
			for (unsigned int level = 0; level < count; ++level)
			{
				bool done = UploadLevel(stream, texture, rect, level, 0);
				if (rect != 0)
				{
					rect->height >>= 1;
					rect->width >>= 1;
					rect->x >>= 1;
					rect->y >>= 1;
				}
				if (!done)
				{
					break;
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x1072B110
	static void SaveLevels(OutputStream* stream, Texture* texture)
	{
		unsigned int count = texture->info->description.levels;
		for (unsigned int level = 0; level < count; ++level)
		{
			SaveLevel(level, 0, stream, texture);
		}
	}

	// FUNCTION: ENGINE 0x1072B150
	// Reads the levels of the six faces of a cube texture
	static void UploadCubeLevels(content::ChunkStream* stream, Texture* texture, const TextureDescription* description, bool dropTop)
	{
		if (dropTop == true)
		{
			unsigned int count = texture->info->description.levels + 1;
			for (unsigned int face = 0; face < 6; ++face)
			{
				for (unsigned int level = 0; level < count; ++level)
				{
					if (level == 0)
					{
						SkipLevel(stream, description);
					}
					else
					{
						UploadLevel(stream, texture, 0, level - 1, face);
					}
				}
			}
			return;
		}
		unsigned int count = texture->info->description.levels;
		for (unsigned int face = 0; face < 6; ++face)
		{
			for (unsigned int level = 0; level < count; ++level)
			{
				UploadLevel(stream, texture, 0, level, face);
			}
		}
	}

	// FUNCTION: ENGINE 0x1072B1F0
	static void SaveCubeLevels(OutputStream* stream, Texture* texture)
	{
		unsigned int count = texture->info->description.levels;
		for (unsigned int face = 0; face < 6; ++face)
		{
			for (unsigned int level = 0; level < count; ++level)
			{
				SaveLevel(level, face, stream, texture);
			}
		}
	}

	// FUNCTION: ENGINE 0x1072B230
	// EQUIVALENT: the same loops and calls in the same order; the engine passes the texture in edi, ours on the
	// stack (7.4 %)
	// Reads the slices of every level of a volume texture
	static void UploadVolumeLevels(content::ChunkStream* stream, bool dropTop, Texture* texture, const TextureDescription* description)
	{
		unsigned int count = texture->info->description.levels;
		if (dropTop == true)
		{
			for (unsigned int level = 0; level < count + 1; ++level)
			{
				unsigned int slices = texture->info->levelData[level].count;
				for (unsigned int slice = 0; slice < slices; ++slice)
				{
					if (level == 0)
					{
						SkipLevel(stream, description);
					}
					else
					{
						UploadLevel(stream, texture, 0, level - 1, slice);
					}
				}
			}
			return;
		}
		for (unsigned int level = 0; level < count; ++level)
		{
			unsigned int slices = texture->info->levelData[level].count;
			for (unsigned int slice = 0; slice < slices; ++slice)
			{
				UploadLevel(stream, texture, 0, level, slice);
			}
		}
	}

	// FUNCTION: ENGINE 0x1072B300
	static void SaveVolumeLevels(OutputStream* stream, Texture* texture)
	{
		unsigned int count = texture->info->description.levels;
		for (unsigned int level = 0; level < count; ++level)
		{
			unsigned int slices = texture->info->levelData[level].count;
			for (unsigned int slice = 0; slice < slices; ++slice)
			{
				SaveLevel(level, slice, stream, texture);
			}
		}
	}

	// FUNCTION: ENGINE 0x1072ACA0
	// Writes the DDS header of the texture
	static bool WriteHeader(OutputStream* stream, Texture* texture)
	{
		DDSHeader header;
		memset(&header, 0, sizeof(header));
		header.flags |= 0x1007;
		header.size = 0x7C;
		header.height = texture->info->levelData[0].data->height;
		header.width = texture->info->levelData[0].data->width;
		if ((unsigned int)texture->info->description.levels > 1)
		{
			header.flags |= 0x20000;
			header.caps |= 0x400008;
			header.mipMapCount = texture->info->description.levels;
		}
		int type = texture->info->description.type;
		if (type == 2)
		{
			header.caps |= 8;
			header.caps2 |= 0xFE00;
		}
		else if (type == 3)
		{
			header.flags |= 0x800000;
			header.caps |= 8;
			header.caps2 |= 0x200000;
			header.depth = texture->info->levelData[0].count;
		}
		if (!FillPixelFormat(&header.format, texture))
		{
			return false;
		}
		stream->Write("DDS ", 4, 1);
		stream->Write(&header, 0x7C, 1);
		return true;
	}

	// FUNCTION: ENGINE 0x1072B360
	bool SaveTexture(OutputStream* stream, Texture* texture)
	{
		if (!WriteHeader(stream, texture))
		{
			return false;
		}
		switch (texture->info->description.type)
		{
		case 1:
			SaveLevels(stream, texture);
			return true;
		case 2:
			SaveCubeLevels(stream, texture);
			return true;
		case 3:
			SaveVolumeLevels(stream, texture);
			return true;
		}
		return false;
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

	// FUNCTION: ENGINE 0x1072B470
	// EQUIVALENT: the same header read, texture creation, type switch and calls in the same order and the same
	// block layout; the engine keeps the stream in ebx and passes the texture to the volume upload in edi (13.8 %)
	Texture* DDSParser::Load(core::IRefCount* stream, const char* name, int usage, bool flag, Texture* source)
	{
		content::ChunkStream* chunks = static_cast<content::ChunkStream*>(stream);
		TextureDescription description;
		if (!ReadHeader(chunks, &description, &flag))
		{
			return 0;
		}
		description.usage = usage;
		Texture* target = texture;
		if (target != 0)
		{
			if (target->info->description.format != description.format)
			{
				return target;
			}
		}
		else
		{
			target = new Texture();
			if (!target->Create(&description, source))
			{
				target->Release();
				return 0;
			}
		}
		switch (target->info->description.type)
		{
		case 1:
			{
				UploadRect rect;
				UploadRect* part = 0;
				if (texture != 0)
				{
					rect.height = description.height;
					rect.width = description.width;
					rect.x = width;
					rect.y = height;
					part = &rect;
					unsigned int full = target->info->levelData[0].data->width;
					if (width + description.width > full)
					{
						break;
					}
					if (width + description.width > full)
					{
						break;
					}
				}
				UploadLevels(chunks, target, &description, flag, part);
			}
			break;
		case 2:
			UploadCubeLevels(chunks, target, &description, flag);
			break;
		case 3:
			UploadVolumeLevels(chunks, flag, target, &description);
			break;
		}
		return target;
	}

	// FUNCTION: ENGINE 0x1072B600
	// Makes the texture a header describes (or checks the one given) and reads one level into it
	static Texture* MakeTexture(Texture* texture, const DDSHeader* header, content::ChunkStream* stream, int type,
		int usage, int levels, int depth, int level, int slice)
	{
		Texture* target = texture;
		int format = GetFormat(&header->format);
		if (target == 0)
		{
			TextureDescription description;
			description.type = type;
			description.levels = levels;
			description.depth = depth;
			description.width = header->width;
			description.height = header->height;
			description.format = format;
			description.usage = usage;
			target = new Texture();
			if (!target->Create(&description, 0))
			{
				target->Release();
				return 0;
			}
		}
		else if (format != target->info->description.format)
		{
			return 0;
		}
		UploadLevel(stream, target, 0, level, slice);
		return target;
	}

	// FUNCTION: ENGINE 0x1072B6D0
	Texture* DDSParser::Parse(core::IRefCount* reader, int type, int usage, int levels, int depth, Texture* existing,
		int level, int slice)
	{
		content::ChunkStream* stream = static_cast<content::ChunkStream*>(reader);
		char magic[4];
		stream->Read(magic, 4, 1, 1);
		if (strncmp(magic, "DDS ", 4) != 0)
		{
			return 0;
		}
		DDSHeader header;
		stream->Read(&header, 0x1F, 4, 1);
		if (header.size != 0x7C || (~header.flags & 1) != 0 || (~header.flags & 0x1000) != 0 ||
			header.format.size != 0x20 || (header.caps2 & 0x200200) != 0 || header.mipMapCount > 0)
		{
			return 0;
		}
		return MakeTexture(existing, &header, stream, type, usage, levels, depth, level, slice);
	}
}
