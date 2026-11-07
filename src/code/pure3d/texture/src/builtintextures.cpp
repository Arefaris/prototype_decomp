// The textures the texture module builds itself (unit around 0x1073DA10 - 0x1073E200; file name guessed, the builders
// are not reconstructed yet). Names are guesses.
#include "code/core/refptr.h"
#include "code/pure3d/context.h"
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
	// 0x1073DA10, 0x1073DF90: make the textures
	void Unknown1073DA10();
	void Unknown1073DF90();
	void Unknown1073E1D0();

	// FUNCTION: ENGINE 0x1073E1D0
	void Unknown1073E1D0()
	{
		Unknown1073DA10();
		Unknown1073DF90();
		gBuiltinTexturesMade = true;
	}

	// FUNCTION: ENGINE 0x10704A00
	Texture* GetBuiltinTextureC4()
	{
		if (!gBuiltinTexturesMade)
		{
			Unknown1073E1D0();
		}
		return gBuiltinTexture112818C4;
	}

	// FUNCTION: ENGINE 0x10704A20
	Texture* GetBuiltinTextureC8()
	{
		return gBuiltinTexture112818C8;
	}

	// FUNCTION: ENGINE 0x10704A30
	Texture* GetBuiltinTextureCC()
	{
		if (!gBuiltinTexturesMade)
		{
			Unknown1073E1D0();
		}
		return gBuiltinTexture112818CC;
	}

	// FUNCTION: ENGINE 0x10704A50
	Texture* GetBuiltinTextureD0()
	{
		if (!gBuiltinTexturesMade)
		{
			Unknown1073E1D0();
		}
		return gBuiltinTexture112818D0;
	}

	// FUNCTION: ENGINE 0x10704A70
	Texture* GetBuiltinTextureD4()
	{
		if (!gBuiltinTexturesMade)
		{
			Unknown1073E1D0();
		}
		return gBuiltinTexture112818D4;
	}

	// FUNCTION: ENGINE 0x10704A90
	Texture* GetBuiltinTextureD8()
	{
		if (!gBuiltinTexturesMade)
		{
			Unknown1073E1D0();
		}
		return gBuiltinTexture112818D8;
	}

	// FUNCTION: ENGINE 0x10704AB0
	Texture* GetBuiltinTextureDC()
	{
		if (!gBuiltinTexturesMade)
		{
			Unknown1073E1D0();
		}
		return gBuiltinTexture112818DC;
	}

	// FUNCTION: ENGINE 0x10704AD0
	Texture* GetBuiltinTextureE0()
	{
		if (!gBuiltinTexturesMade)
		{
			Unknown1073E1D0();
		}
		return gBuiltinTexture112818E0;
	}

	// 0x1079C540, 0x1079C580, 0x1079C590 (other units)
	void Unknown1079C540(Context* context);
	void Unknown1079C580();
	void Unknown1079C590();

	// FUNCTION: ENGINE 0x1073E260
	void Unknown1073E260(Context* context)
	{
		Unknown1079C540(context);
	}

	// FUNCTION: ENGINE 0x1073E2C0
	void Unknown1073E2C0()
	{
		Unknown1079C580();
	}

	// FUNCTION: ENGINE 0x1073E2D0
	void Unknown1073E2D0()
	{
		Unknown1079C590();
	}

	// FUNCTION: ENGINE 0x1073E2E0
	void Unknown1073E2E0()
	{
	}

	// FUNCTION: ENGINE 0x1073E2F0
	void Unknown1073E2F0()
	{
	}

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
