// The music library's cue (0x105DC6A0 - 0x105DD580): the entity that holds the grid of cells of its parts and
// layers.
#include "code/music/cue.h"

namespace music
{
	// FUNCTION: ENGINE 0x105DC680
	Cell* Cue::GetCellAt(unsigned int layer, unsigned int part)
	{
		return grid.cells[grid.layerCount * part + layer];
	}

	// FUNCTION: ENGINE 0x105DC100
	const char* Part::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x105DC110
	const char* Layer::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x105DCAE0
	// NONMATCHING: the engine keeps this in eax and adds the offset of the node to it, ours takes the node's address with lea (36.4 %)
#ifdef NONMATCHING
	Part::~Part()
	{
		cue->parts.Erase(&node);
	}
#endif

	// FUNCTION: ENGINE 0x105DCB20
	// NONMATCHING: the engine keeps this in eax and adds the offset of the node to it, ours takes the node's address with lea (36.4 %)
#ifdef NONMATCHING
	Layer::~Layer()
	{
		cue->layers.Erase(&node);
	}
#endif

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
