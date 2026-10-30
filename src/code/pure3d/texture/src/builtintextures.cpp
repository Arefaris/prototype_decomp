// The textures the texture module builds itself (unit around 0x1073DA10 - 0x1073E200; file name guessed, the builders
// are not reconstructed yet). Names are guesses.
#include "code/core/refptr.h"
#include "code/pure3d/texture/texture.h"

namespace pure3d
{
	// 0x112818C4 - 0x112818E0: the textures the module made (name guesses)
	extern Texture* gBuiltinTexture112818C4;
	extern Texture* gBuiltinTexture112818C8;
	extern Texture* gBuiltinTexture112818CC;
	extern Texture* gBuiltinTexture112818D0;
	extern Texture* gBuiltinTexture112818D4;
	extern Texture* gBuiltinTexture112818D8;
	extern Texture* gBuiltinTexture112818DC;
	extern Texture* gBuiltinTexture112818E0;
	// 0x112818E4: whether they were made
	extern bool gBuiltinTexturesMade;

	// FUNCTION: ENGINE 0x1073E1F0
	void Unknown1073E1F0()
	{
		core::SafeRelease(gBuiltinTexture112818DC);
		core::SafeRelease(gBuiltinTexture112818D8);
		core::SafeRelease(gBuiltinTexture112818D4);
		core::SafeRelease(gBuiltinTexture112818D0);
		core::SafeRelease(gBuiltinTexture112818CC);
		core::SafeRelease(gBuiltinTexture112818C8);
		core::SafeRelease(gBuiltinTexture112818C4);
		core::SafeRelease(gBuiltinTexture112818E0);
		gBuiltinTexturesMade = false;
	}
}
