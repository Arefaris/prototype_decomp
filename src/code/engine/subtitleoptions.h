// The subtitle object at 0x11316A58 is an engine::FESubtitle (frontend/fesubtitle.h); the units that only show or stop
// subtitles keep using the earlier name.
#ifndef ENGINE_SUBTITLEOPTIONS_H
#define ENGINE_SUBTITLEOPTIONS_H

#include "code/engine/frontend/fesubtitle.h"

namespace engine
{
	typedef FESubtitle SubtitleOptions;
}

#endif
