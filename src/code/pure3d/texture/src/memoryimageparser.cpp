// The reader of images in memory (RTTI pure3d::TextureMemoryImageParser; unit 0x107B5B40 - 0x107B5C90, file name guessed
// from the class). Names are guesses.
#include "code/content/chunkhandler.h"
#include "code/pure3d/pddi.h"
#include "code/pure3d/texture/texture.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x107B5B50
	bool TextureMemoryImageParser::IsSupportedFormat(unsigned int format)
	{
		switch ((int)format)
		{
		case 0x1B:
		case 0x1C:
		case 0x1D:
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x107B5B70
	Texture* TextureMemoryImageParser::Load(core::IRefCount* stream, const char* name, int usage, bool flag,
		Texture* source)
	{
		pddiQuery* query = pddi->Unknown24(0x102);
		if (query != 0)
		{
			Texture* texture = new Texture();
			texture->SetInfo(query->CreateTexture(1, stream, ((content::LoadStream*)stream)->GetSize()));
			return texture;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x107B5BE0
	Texture* TextureMemoryImageParser::Parse(core::IRefCount* reader, int type, int usage, int levels, int depth,
		Texture* existing, int level, int slice)
	{
		pddiQuery* query = pddi->Unknown24(0x102);
		if (query != 0)
		{
			Texture* texture = new Texture();
			dxTexture* info;
			if (depth != 0)
			{
				info = query->CreateCubeTexture(type, reader, levels);
			}
			else
			{
				info = query->CreateTexture(type, reader, levels);
			}
			texture->SetInfo(info);
			return texture;
		}
		return 0;
	}
}
