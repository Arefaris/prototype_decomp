// The renderer's task (the unit 0x10849090 - 0x1084CBAF; no assert path, the file name is a guess): the registry of
// the drawables the renderer works on and the switches around it.
#include "code/engine/drawableregistry.h"

namespace engine
{
	// The registry (0x1130EFE0) and the sub-frame interpolation switch in front of it (0x1130EFD8; names guessed)
	extern DrawableRegistry gDrawableRegistry;
	extern bool gSubframeInterpolation;

	// FUNCTION: ENGINE 0x108490A0
	DrawableRegistry* GetDrawableRegistry()
	{
		return &gDrawableRegistry;
	}

	// FUNCTION: ENGINE 0x108490D0
	void SetSubframeInterpolation(bool value)
	{
		gSubframeInterpolation = value;
	}
}
