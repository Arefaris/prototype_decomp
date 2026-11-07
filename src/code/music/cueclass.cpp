// The music library's cue (0x105DC6A0 - 0x105DD580): the entity that holds the grid of cells of its parts and
// layers.
#include "code/music/cue.h"

namespace music
{
	// FUNCTION: ENGINE 0x105DC6A0
	Cell* Cue::GetCell(unsigned int layer, unsigned int part)
	{
		return grid.cells[grid.layerCount * part + layer];
	}

	// FUNCTION: ENGINE 0x105DD500
	Cue::Cue(const om::ClassName& newName) :
		Entity(newName),
		bpm(120.0f),
		timeSignature(4, 4)
	{
	}

	// FUNCTION: ENGINE 0x105DBFF0
	bool Cue::Slot8(void* argument)
	{
		return true;
	}

	// FUNCTION: ENGINE 0x105DD580
	om::EntityTypeBase* Cue::GetEntityType()
	{
		return om::FindEntityType(typeid(Cue));
	}
}
