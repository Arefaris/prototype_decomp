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
			unsigned int index : 16;  // the position in the table of movies
			unsigned int generation : 16;  // the serial the entry must still carry
		};

		// The movie the Flash player runs (another unit; names guessed)
		class FlashMovie
		{
		public:
			// 0x10964000
			void Unknown10964000(float value);

			unsigned char unknown0[0x9C];
			bool unknown9C;
			bool unknown9D;
			bool unknown9E;
		};

		// The player (0x109602F0 answers it, another unit)
		class FlashRenderer
		{
		public:
			static FlashRenderer* Get();
			// 0x10960E60: lets the movie go
			void Unknown10960E60(FlashMovie* movie);
		};

		// The movies by handle: a table of pointers with the serial each entry must still carry (0x2C bytes, made by
		// 0x108865F0, global 0x11316E3C; names guessed)
		class FlashMovieTable
		{
		public:
			// The slot of the handle's movie, null when the handle is out of date
			FlashMovie** Find(FlashMovieHandler handle)
			{
				if (handle.index < capacity && handle.generation == serials[handle.index])
				{
					return objects + handle.index;
				}
				return 0;
			}
			// 0x10884FD0: gives the handle's entry back
			void Free(const FlashMovieHandler* handle);

			FlashMovie** objects;  // +0
			FlashMovie** objectsEnd;  // +4
			int unknown8;
			int freeHead;  // +0xC
			void* nodes;  // +0x10
			void* nodesEnd;  // +0x14
			int unknown18;
			unsigned int* serials;  // +0x1C
			unsigned int* serialsEnd;  // +0x20
			int unknown24;
			unsigned int capacity;  // +0x28
		};
		extern FlashMovieTable* gFlashMovieTable;  // 0x11316E3C

		// What the movie's events run on the render thread (flash.cpp's neighbours, another unit; names guessed)
		// 0x108854E0 / 0x10885540 / 0x108855D0 / 0x10885610 / 0x108856A0 / 0x10885720
		void DestroyMovie(FlashMovieHandler movie);
		void SetMovieFloat(FlashMovieHandler movie, float value);
		void SetMovieFlag(FlashMovieHandler movie, bool value);
		// 0x10885590
		void SetMovieFlagB(FlashMovieHandler movie, bool value);
		void SetMovieValue(FlashMovieHandler movie, unsigned int index, bool value, int a, int b);
		void SetMovieCursor(FlashMovieHandler movie, int x, int y);
		void SetMovieNumber(FlashMovieHandler movie, int index, int a, float value);

		// 0x10886410: has the render thread let the movie go
		void ReleaseMovie(FlashMovieHandler movie);
	}
}

#endif
