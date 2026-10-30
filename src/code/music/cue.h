// The cues and cells of the music library (RTTI: music::Cue, music::Part, music::Layer, music::Cell and
// music::MGraphCell). Only what the reflection templates need so far.
#ifndef MUSIC_CUE_H
#define MUSIC_CUE_H

#include "code/music/cell.h"
#include "code/om/entity.h"

namespace music
{
	// A cue: an entity that plays cells (0x68 bytes)
	class Cue : public om::Entity
	{
	public:
		// 0x105DD500
		explicit Cue(const om::ClassName& newName);
		virtual ~Cue();
		OM_ENTITY_ALLOCATION(Cue);

		char unknown20[0x48];
	};

}

#endif
