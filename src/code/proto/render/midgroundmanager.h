// proto::MidgroundManager (RTTI 0x110ACA90-ish, vftable 0x10DEAB90, constructor 0x102DE380): the streaming cells the
// midground pass draws. The unit has no assert path, so the file name, the class layout and every member name are
// guesses. The cell index (MidgroundMap) is the unit's own: its Find, Next, Insert and Grow are the four kept copies
// at 0x102DD6F0 / 0x102DD7B0, 0x102DD3B0, 0x102DDAD0 and 0x102DDBA0.
#ifndef PROTO_RENDER_MIDGROUNDMANAGER_H
#define PROTO_RENDER_MIDGROUNDMANAGER_H

#include "code/container/arraydynamic.h"
#include "code/core/name.h"
#include "code/engine/render/async/drawable.h"

namespace proto
{
	// The cell index: open addressing over the 64-bit hash of the cell's name, holding a pointer to the cell's
	// drawable. `sentinel` is the value of an empty slot and `buckets` holds its address. The probe step is
	// ((key >> 9) & 0xFE) | 1. (name guess)
	class MidgroundMap
	{
	public:
		// A search position: seven words built on the caller's stack, of which +4 is left uninitialised
		struct Iterator
		{
			Iterator(MidgroundMap* newMap)
			{
				map = newMap;
				key = 0;
				index = 0;
				current = 0;
				step = 0;
			}

			// 0x102DD6F0 / 0x102DD7B0: the value the key is stored under, null when the map has no such key
			engine::render::Drawable* Find(const unsigned __int64& newKey);

			MidgroundMap* map;
			int unknown4;
			unsigned __int64 key;
			int index;
			int current;
			int step;
		};

		// +0x00: the number of slots (a power of two; the mask is this minus one)
		unsigned int capacity;
		// +0x04: the number of live entries
		int count;
		int unknown8;
		int unknownC;
		int unknown10;
		int unknown14;
		// +0x18: the heap the two tables are allocated from
		int unknown18;
		engine::render::Drawable** buckets;
		unsigned __int64* keys;
		// +0x24: the value of an empty slot
		engine::render::Drawable sentinel;
	};

	// The object a cell describes (name guess): its +0x10 is the name the manager indexes the cell under
	struct MidgroundCellData
	{
		unsigned char unknown0[0x10];
		core::Name<core::CaseSensitiveKey> name;
	};

	// One streaming cell of the midground (name guess)
	struct MidgroundCell
	{
		unsigned char unknown0[0x54];
		MidgroundCellData* unknown54;
	};

	// One cell the manager has loaded: its name, the drawable it streams in and the manager's scale (name guess).
	// Its four members are 0x14 bytes, but the engine steps through the array 0x18 at a time and the copy into it
	// leaves the last four bytes alone: the record is eight-byte aligned there because the engine's core::Name is (a
	// 64-bit hash). Ours is two 32-bit words, so this record is 0x14 and the two walking functions are NONMATCHING
	// until core::Name's alignment is settled; the member layout is otherwise the engine's.
	struct MidgroundCellRecord
	{
		core::Name<core::CaseSensitiveKey> name;
		engine::render::Drawable* drawable;
		int unknownC;
		float unknown10;
	};

	class MidgroundManager
	{
	public:
		// The class is polymorphic in the engine (RTTI base engine::RenderTask::PresentationTask, vftable
		// 0x10DEAB90). That base is not recovered yet, so the vftable pointer and its own word at +0x04 are declared
		// here and no destructor is defined: the compiler then emits no vftable of ours for the class.
		virtual ~MidgroundManager();
		// +0x04: the base class's own word, a byte set to 1 by the constructor 0x102DE380
		unsigned char unknown4[4];

		// 0x102DDD30: the cell's drawable is shown and the cell is recorded
		void CellLoaded(MidgroundCell* cell);
		// 0x102DDE30: the cell's drawable is taken down and its record erased
		void CellUnloaded(MidgroundCell* cell);

		// +0x08: the scale the records are given
		float unknown8;
		// +0x0C: the drawables the cells were given, the cursor +0x10 and the end +0x14
		container::ArrayDynamicHeap<engine::render::Drawable> drawables;
		// +0x1C: the cell index
		MidgroundMap map;
		// +0x44: the loaded cells, the cursor +0x48 and the end +0x4C
		container::ArrayDynamicHeap<MidgroundCellRecord> records;
	};
}

#endif
