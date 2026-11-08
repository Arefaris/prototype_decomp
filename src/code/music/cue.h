// The cues and cells of the music library (RTTI: music::Cue, music::Part, music::Layer, music::Cell and
// music::MGraphCell). Only what the reflection templates need so far.
#ifndef MUSIC_CUE_H
#define MUSIC_CUE_H

#include "code/music/cell.h"
#include "code/music/time.h"
#include "code/om/delegate.h"
#include "code/om/entity.h"
#include "code/om/string.h"

namespace music
{
	// The cells of a cue: a grid with a row for every layer and a cell for every part in it (the cell of a part and a
	// layer is cells[partCount * layer + part])
	struct CellGrid
	{
		CellGrid() :
			layerCount(0),
			partCount(0),
			cells(0)
		{
		}
		// 0x105DD040 (the engine's own copy is not called): gives the cells back
		~CellGrid()
		{
			om::Release(cells, partCount * layerCount * 4, 4);
			cells = 0;
			layerCount = 0;
			partCount = 0;
		}
		// 0x105DC1E0 (the allocation's tag, an empty string)
		static const char* AllocationTag();
		// 0x105DCE50: gives the grid that many parts and layers, keeping the cells that are still there (a part or layer
		// count of zero empties it)
		void Resize(unsigned int newPartCount, unsigned int newLayerCount);
		// 0x105DD070 / 0x105DD250: a new empty part behind the part, and the part taken out
		void InsertPart(unsigned int part);
		void RemovePart(unsigned int part);
		// 0x105DD160: the layer taken out
		void RemoveLayer(unsigned int layer);

		unsigned int layerCount;
		unsigned int partCount;
		Cell** cells;  // partCount * layerCount cells
	};

	class Cue;

	// A part of a cue (RTTI: music::Part, 0x30 bytes): known by its index in the cue's tree of parts
	class Part
	{
	public:
		// 0x105DD3E0: a part of the cue under the name, at the index
		Part(Cue* owner, const om::ClassName* newName, unsigned int newIndex);
		// Slot 0 (0x105DCAE0 is the body, the deleting destructor 0x105DD440): takes the part out of its cue
		virtual ~Part();
		// 0x105DC640
		void SetName(const om::ClassName* newName);
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
		void* unknown18;
		om::TreeNode node;  // 0x1C
	};

	// A layer of a cue (RTTI: music::Layer, 0x30 bytes): known by its index in the cue's tree of layers
	class Layer
	{
	public:
		// 0x105DD470: a layer of the cue under the name, at the index
		Layer(Cue* owner, const om::ClassName* newName, unsigned int newIndex);
		// Slot 0 (0x105DCB20 is the body, the deleting destructor 0x105DD4D0)
		virtual ~Layer();
		// 0x105DBF60
		void SetCellType(om::MetaTypeBase* newCellType);
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
		om::MetaTypeBase* cellType;  // 0x18: the class of the players of the cells in the layer, none until a cell is set
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

		// 0x105DC6A0: the cell of a part in a layer (the engine has a second copy at 0x105DC680)
		Cell* GetCell(unsigned int part, unsigned int layer);
		Cell* GetCellAt(unsigned int part, unsigned int layer);
		// 0x105DCC90 / 0x105DCCB0: the part or layer of an index, null when there is none
		Part* GetPart(unsigned int index);
		Layer* GetLayer(unsigned int index);
		// 0x105DCBF0 / 0x105DCC40: the part or layer known by a name, null when there is none
		Part* FindPartByName(const om::ClassName* partName);
		Layer* FindLayerByName(const om::ClassName* layerName);
		// 0x105DCCD0 / 0x105DCD60: the name with a number behind it until no part or layer has it (names guessed)
		om::String MakeUniquePartName(om::String baseName);
		om::String MakeUniqueLayerName(om::String baseName);
		// 0x105DD770 / 0x105DD830: a new part or layer behind the last (names guessed)
		void AddPart();
		void AddLayer();
		// 0x105DD5B0: a new part behind the part of the index; the parts after it move up (name guessed)
		void InsertPart(unsigned int index);
		// 0x105DD710: puts the cell in the cell of the part and layer; false when the layer holds cells of another
		// kind of player (name guessed)
		bool SetCell(unsigned int part, unsigned int layer, Cell* cell);
		// 0x105DDCB0: deletes all cells, parts and layers (name guessed)
		void Clear();
		// 0x105DD6B0: stops the players of the cell (left to the engine; name guessed)
		void StopCellPlayers(unsigned int part, unsigned int layer);
		// 0x105DDF50: deletes the cell of a part and layer (name guessed)
		void RemoveCell(unsigned int part, unsigned int layer);
		// 0x105DDF00: puts a copy of the cell into the other part and layer when that one has no cell, 0x105DF880: does that
		// for every layer of a part (names guessed)
		void CopyCell(unsigned int fromPart, unsigned int fromLayer, unsigned int toPart, unsigned int toLayer);
		void CopyPart(unsigned int toPart, unsigned int fromPart);
		// 0x105DDF90: moves the cell to the other part and layer when that one has no cell (name guessed)
		void MoveCell(unsigned int fromPart, unsigned int fromLayer, unsigned int toPart, unsigned int toLayer);

		CellGrid grid;  // 0x20
		om::TreeHead layers;  // 0x2C: the layers by their index
		om::TreeHead parts;  // 0x40: the parts by their index
		om::GarbageList unknown54;
		float bpm;  // 0x5C
		TimeSignature timeSignature;  // 0x60
	};

}

#endif
