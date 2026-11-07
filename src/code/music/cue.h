// The cues and cells of the music library (RTTI: music::Cue, music::Part, music::Layer, music::Cell and
// music::MGraphCell). Only what the reflection templates need so far.
#ifndef MUSIC_CUE_H
#define MUSIC_CUE_H

#include "code/music/cell.h"
#include "code/music/time.h"
#include "code/om/delegate.h"
#include "code/om/entity.h"

namespace music
{
	// The cells of a cue: a grid with a row for every part and a cell for every layer in it
	struct CellGrid
	{
		CellGrid() :
			partCount(0),
			layerCount(0),
			cells(0)
		{
		}

		unsigned int partCount;
		unsigned int layerCount;
		Cell** cells;  // partCount * layerCount cells
	};

	class Cue;

	// A part of a cue (RTTI: music::Part, 0x30 bytes): known by its index in the cue's tree of parts
	class Part
	{
	public:
		// Slot 0 (0x105DCAE0 is the body, the deleting destructor 0x105DD440): takes the part out of its cue
		virtual ~Part();
		// 0x105DC100 (the allocation's tag, an empty string)
		static const char* AllocationTag();
		static void* operator new(size_t)
		{
			return om::Allocate(AllocationTag(), sizeof(Part), __alignof(Part));
		}
		static void operator delete(void* memory)
		{
			om::Release(memory, sizeof(Part), __alignof(Part));
		}

		om::ClassName name;  // 8
		int index;  // 0x10
		Cue* cue;  // 0x14
		int unknown18;
		om::TreeNode node;  // 0x1C
	};

	// A layer of a cue (RTTI: music::Layer, 0x30 bytes): known by its index in the cue's tree of layers
	class Layer
	{
	public:
		// Slot 0 (0x105DCB20 is the body, the deleting destructor 0x105DD4D0)
		virtual ~Layer();
		// 0x105DC110
		static const char* AllocationTag();
		static void* operator new(size_t)
		{
			return om::Allocate(AllocationTag(), sizeof(Layer), __alignof(Layer));
		}
		static void operator delete(void* memory)
		{
			om::Release(memory, sizeof(Layer), __alignof(Layer));
		}

		om::ClassName name;  // 8
		int index;  // 0x10
		Cue* cue;  // 0x14
		int unknown18;
		om::TreeNode node;  // 0x1C
	};

	// A cue: an entity that plays cells (0x68 bytes)
	class Cue : public om::Entity
	{
	public:
		// 0x105DD500
		explicit Cue(const om::ClassName& newName);
		// Slot 0 (0x105DF800 is the body, the deleting destructor 0x105DF8B0)
		virtual ~Cue();
		// Slots 3, 4, 6, 7, 8 and 9 (0x105DE000, 0x105DE930, 0x105DF1C0, 0x105DF4F0, 0x105DBFF0, 0x105DD580)
		virtual bool Slot3(void* argument);
		virtual void Slot4(void* argument);
		virtual bool Slot6(void* argument);
		virtual bool Slot7(void* argument);
		virtual bool Slot8(void* argument);
		virtual om::EntityTypeBase* GetEntityType();
		OM_ENTITY_ALLOCATION(Cue);

		// 0x105DC6A0: the cell of a layer in a part (the engine has a second copy at 0x105DC680)
		Cell* GetCell(unsigned int layer, unsigned int part);
		Cell* GetCellAt(unsigned int layer, unsigned int part);

		CellGrid grid;  // 0x20
		om::TreeHead layers;  // 0x2C: the layers by their index
		om::TreeHead parts;  // 0x40: the parts by their index
		om::GarbageList unknown54;
		float bpm;  // 0x5C
		TimeSignature timeSignature;  // 0x60
	};

}

#endif
