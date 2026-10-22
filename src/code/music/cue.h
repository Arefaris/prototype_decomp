// The cues and cells of the music library (RTTI: music::Cue, music::Part, music::Layer, music::Cell and
// music::MGraphCell). Only what the reflection templates need so far.
#ifndef MUSIC_CUE_H
#define MUSIC_CUE_H

namespace music
{
	class Cue
	{
	public:
		virtual ~Cue();
	};

	class Cell
	{
	public:
		virtual ~Cell();
	};

	class MGraphCell : public Cell
	{
	public:
		virtual ~MGraphCell();
	};
}

#endif
