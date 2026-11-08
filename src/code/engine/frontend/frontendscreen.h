// engine::FrontendScreen: the front end's screen, a handle of the Flash movie it shows (the object at +0x2C of the front
// end's movie). Every call queues an event for the render thread. Unit 0x10886410 - 0x10886510 (names guessed).
#ifndef ENGINE_FRONTEND_FRONTENDSCREEN_H
#define ENGINE_FRONTEND_FRONTENDSCREEN_H

#include "code/engine/render/async/private/flash.h"

namespace engine
{
	class FrontendScreen
	{
	public:
		// 0x10886490 / 0x108864C0 / 0x108864E0
		void SetValue(int index, bool value, int a, int b);
		void SetCursor(int x, int y);
		void SetFloat(int index, int a, float value);
		// 0x10886430 / 0x10886470
		void SetFloatValue(float value);
		void SetFlag(bool value);

		render::FlashMovieHandler handle;
	};
}

#endif
