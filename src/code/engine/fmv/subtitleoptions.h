// engine::SubtitleOptions (the object at 0x11316A58, another unit): the text objects the subtitles of a movie are shown
// in. Only what the movie player and the subtitle manager use is declared; names are guesses.
#ifndef ENGINE_FMV_SUBTITLEOPTIONS_H
#define ENGINE_FMV_SUBTITLEOPTIONS_H

#include "code/core/name.h"
#include "code/engine/fmv/fmvsubtitlemanager.h"

namespace engine
{
	class SubtitleOptions
	{
	public:
		void Unknown10876EF0(bool value);
		// 0x10877110: makes the text object of a subtitle; the two names pick its style (meaning unknown)
		int Show(FmvSubtitleManager::SubTitleEnty* subtitle, const core::Name<core::CaseSensitiveKey>& first,
			const core::Name<core::CaseSensitiveKey>& second, int unknown);
		// 0x10876B70: takes a text object down
		void Hide(int handle);

		unsigned char unknown0[0x1E];
		bool unknown1E;
	};
	extern SubtitleOptions* gSubtitleOptions;

	// The names the manager passes to Show (0x11316A70 / 0x11316A78, made by another unit's initialiser)
	extern core::Name<core::CaseSensitiveKey> gSubtitleFirstName;
	extern core::Name<core::CaseSensitiveKey> gSubtitleSecondName;
}

#endif
