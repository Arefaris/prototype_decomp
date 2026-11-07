#include "code/engine/render/async/private/flash.h"

namespace engine
{
	namespace render
	{
		// The event classes the movie calls queue
		template class RenderEvent1<FlashMovieHandler>;
		template class RenderEvent2<FlashMovieHandler, float>;
		template class RenderEvent2<FlashMovieHandler, bool>;
		template class RenderEvent5<FlashMovieHandler, unsigned int, bool, int, int>;
		template class RenderEvent3<FlashMovieHandler, int, int>;
		template class RenderEvent4<FlashMovieHandler, int, int, float>;
		template class RenderEvent7<FlashMovieHandler, container::StringC<128>, int, int, int, int, bool>;

		// The queueing functions of the calls (0x10886140, 0x10886180, 0x108861C0, 0x10886200, 0x10886250, 0x108862A0)
		template void QueueRenderEvent<FlashMovieHandler>(void (*)(FlashMovieHandler), FlashMovieHandler);
		template void QueueRenderEvent<FlashMovieHandler, float>(void (*)(FlashMovieHandler, float), FlashMovieHandler,
			float);
		template void QueueRenderEvent<FlashMovieHandler, bool>(void (*)(FlashMovieHandler, bool), FlashMovieHandler,
			bool);
		template void QueueRenderEvent<FlashMovieHandler, unsigned int, bool, int, int>(
			void (*)(FlashMovieHandler, unsigned int, bool, int, int), FlashMovieHandler, unsigned int, bool, int, int);
		template void QueueRenderEvent<FlashMovieHandler, int, int>(void (*)(FlashMovieHandler, int, int),
			FlashMovieHandler, int, int);
		template void QueueRenderEvent<FlashMovieHandler, int, int, float>(
			void (*)(FlashMovieHandler, int, int, float), FlashMovieHandler, int, int, float);
		// 0x10886090
		template void QueueRenderEvent<FlashMovieHandler, container::StringC<128>, int, int, int, int, bool>(
			void (*)(FlashMovieHandler, container::StringC<128>, int, int, int, int, bool), FlashMovieHandler,
			container::StringC<128>, int, int, int, int, bool);

		FlashMovieTable* gFlashMovieTable;

		// FUNCTION: ENGINE 0x108854E0
		void DestroyMovie(FlashMovieHandler movie)
		{
			FlashMovie** slot = gFlashMovieTable->Find(movie);
			if (slot != 0 && *slot != 0)
			{
				FlashMovie* object = *slot;
				FlashRenderer::Get()->Unknown10960E60(object);
				FlashMovieTable* table = gFlashMovieTable;
				*slot = 0;
				table->Free(&movie);
			}
		}

		// FUNCTION: ENGINE 0x10885540
		void SetMovieFloat(FlashMovieHandler movie, float value)
		{
			FlashMovie** slot = gFlashMovieTable->Find(movie);
			if (slot != 0 && *slot != 0)
			{
				(*slot)->Unknown10964000(value);
			}
		}

		// FUNCTION: ENGINE 0x10885590
		void SetMovieFlagB(FlashMovieHandler movie, bool value)
		{
			FlashMovie** slot = gFlashMovieTable->Find(movie);
			if (slot != 0 && *slot != 0)
			{
				(*slot)->unknown9D = value;
			}
		}

		// FUNCTION: ENGINE 0x108855D0
		void SetMovieFlag(FlashMovieHandler movie, bool value)
		{
			FlashMovie** slot = gFlashMovieTable->Find(movie);
			if (slot != 0 && *slot != 0)
			{
				(*slot)->unknown9E = value;
			}
		}

		// FUNCTION: ENGINE 0x10886410
		void ReleaseMovie(FlashMovieHandler movie)
		{
			QueueRenderEvent(DestroyMovie, movie);
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10884E70
// FUNCTION: ENGINE 0x108851A0
// FUNCTION: ENGINE 0x10885230
// FUNCTION: ENGINE 0x10885240
// FUNCTION: ENGINE 0x10885260
// FUNCTION: ENGINE 0x10885280
// FUNCTION: ENGINE 0x108852B0
// FUNCTION: ENGINE 0x108852D0
// FUNCTION: ENGINE 0x108852F0
// FUNCTION: ENGINE 0x10885310
// FUNCTION: ENGINE 0x10885350
// FUNCTION: ENGINE 0x10885380
// FUNCTION: ENGINE 0x108853B0
// FUNCTION: ENGINE 0x108853D0
// FUNCTION: ENGINE 0x10885410
// FUNCTION: ENGINE 0x10885440
// FUNCTION: ENGINE 0x108862F0
// FUNCTION: ENGINE 0x10886090
// FUNCTION: ENGINE 0x10886140
// FUNCTION: ENGINE 0x10886180
// FUNCTION: ENGINE 0x108861C0
// FUNCTION: ENGINE 0x10886200
// FUNCTION: ENGINE 0x10886250
// FUNCTION: ENGINE 0x108862A0
