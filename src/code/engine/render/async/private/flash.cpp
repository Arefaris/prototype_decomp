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
