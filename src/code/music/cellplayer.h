// The cell players of the music library (RTTI: music::CellPlayer and music::MGraphCellPlayer): play one cell of a cue.
// Only the layout and the state enumeration are described so far; the state names come from the strings the
// reflection registers them under.
#ifndef MUSIC_CELLPLAYER_H
#define MUSIC_CELLPLAYER_H

#include "code/om/allocation.h"

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

		// Slot 0 (0x105E2AA0 is the deleting destructor)
		virtual ~CellPlayer()
		{
		}

		int state;  // 4
		int unknown8;
		int unknownC;
		int unknown10;
		int unknown14;
	};

	// The player of a cell that plays a graph of the music graph library (0x88 bytes)
	class MGraphCellPlayer : public CellPlayer
	{
	public:
		// 0x105E3120
		MGraphCellPlayer();
		OM_ALLOCATION(MGraphCellPlayer);

		char unknown18[0x70];
	};
}

#endif
