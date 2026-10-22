// engine::DrawableRegistry (symbol names only; the class is in the unit 0x10849090 - 0x1084CBAF): the global registry
// of the drawables the renderer works on. Only what the render scripts call is declared. Names are guesses.
#ifndef ENGINE_DRAWABLEREGISTRY_H
#define ENGINE_DRAWABLEREGISTRY_H

namespace engine
{
	class DrawableRegistry
	{
	public:
		// 0x108490B0: whether the renderer's drawables are updated apart from the main thread (the byte at +0x84)
		void SetDetachMainThread(bool value);
	};

	// 0x108490A0: the registry (a global at 0x1130EFE0)
	DrawableRegistry* GetDrawableRegistry();
}

#endif
