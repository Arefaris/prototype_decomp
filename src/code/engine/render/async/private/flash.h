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

		// What the movie's events run on the render thread (flash.cpp's neighbours, another unit; names guessed)
		// 0x108854E0 / 0x10885540 / 0x108855D0 / 0x10885610 / 0x108856A0 / 0x10885720
		void DestroyMovie(FlashMovieHandler movie);
		void SetMovieFloat(FlashMovieHandler movie, float value);
		void SetMovieFlag(FlashMovieHandler movie, bool value);
		void SetMovieValue(FlashMovieHandler movie, unsigned int index, bool value, int a, int b);
		void SetMovieCursor(FlashMovieHandler movie, int x, int y);
		void SetMovieNumber(FlashMovieHandler movie, int index, int a, float value);

		// 0x10886410: has the render thread let the movie go
		void ReleaseMovie(FlashMovieHandler movie);
	}
}

#endif
