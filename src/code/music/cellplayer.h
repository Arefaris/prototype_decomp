// The cell player of the music library (RTTI: music::CellPlayer): plays the cells of a cue. Only its state enumeration
// is described so far; the state names come from the strings the reflection registers them under.
#ifndef MUSIC_CELLPLAYER_H
#define MUSIC_CELLPLAYER_H

namespace music
{
	class CellPlayer
	{
	public:
		enum State
		{
			StateFree = 0,
			StateWaitingToFadeIn = 3,
			StatePlaying = 5,
			StateWaitingToFadeOut = 6
		};
	};
}

#endif
