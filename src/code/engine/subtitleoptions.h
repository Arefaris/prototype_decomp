// The object at 0x11316A58 (the subtitle settings and the subtitles on screen; another unit). Only what the fight
// tracks and the movie player use is declared; the names are guesses.
#ifndef ENGINE_SUBTITLEOPTIONS_H
#define ENGINE_SUBTITLEOPTIONS_H

#include "code/core/name.h"

namespace engine
{
	class SubtitleOptions
	{
	public:
		void Unknown10876EF0(bool value);
		// 0x10876B70: ends the subtitle that Show answered with the handle
		void Stop(int handle);
		// 0x10877110: puts a subtitle of the given type and speaker on the screen and answers its handle
		int Show(const char* text, const core::Name<core::CaseSensitiveKey>& typeName, const core::Name<core::CaseSensitiveKey>& speakerName, bool flag);

		unsigned char unknown0[0x1E];
		bool unknown1E;
	};
	extern SubtitleOptions* gSubtitleOptions;
}

#endif
