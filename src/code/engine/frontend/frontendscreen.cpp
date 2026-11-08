// engine::FrontendScreen: see frontendscreen.h.
#include "code/engine/frontend/frontendscreen.h"

namespace engine
{
	// FUNCTION: ENGINE 0x10886430
	void FrontendScreen::SetFloatValue(float value)
	{
		render::QueueRenderEvent(render::SetMovieFloat, handle, value);
	}

	// FUNCTION: ENGINE 0x10886470
	void FrontendScreen::SetFlag(bool value)
	{
		render::QueueRenderEvent(render::SetMovieFlag, handle, value);
	}

	// FUNCTION: ENGINE 0x10886490
	void FrontendScreen::SetValue(int index, bool value, int a, int b)
	{
		render::QueueRenderEvent(render::SetMovieValue, handle, (unsigned int)index, value, a, b);
	}

	// FUNCTION: ENGINE 0x108864C0
	void FrontendScreen::SetCursor(int x, int y)
	{
		render::QueueRenderEvent(render::SetMovieCursor, handle, x, y);
	}

	// FUNCTION: ENGINE 0x108864E0
	void FrontendScreen::SetFloat(int index, int a, float value)
	{
		render::QueueRenderEvent(render::SetMovieNumber, handle, index, a, value);
	}
}
