// engine::render::FlashMovieHandler (RTTI name, as the first argument of the render events its calls queue): a
// handle to a Flash movie in the table of movies, a 16-bit index and a 16-bit generation. The unit is
// code/engine/render/async/private/flash.cpp (from an assert path); the member names are guesses.
#ifndef ENGINE_RENDER_ASYNC_PRIVATE_FLASH_H
#define ENGINE_RENDER_ASYNC_PRIVATE_FLASH_H

#include "code/container/string.h"
#include "code/engine/render/async/renderevent.h"

namespace engine
{
	namespace render
	{
		class FlashMovieHandler
		{
		public:
			unsigned short index;  // +0
			unsigned short generation;  // +2
		};
	}
}

#endif
