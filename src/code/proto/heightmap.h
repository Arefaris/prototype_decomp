// proto::Heightmap (RTTI and reflection names; a load object): a grid of 16-bit heights over an area of the world, with the
// margins around it, the lowest point and the factor that turns a stored height into a world height. Unit 0x10393100 -
// 0x10397700 (no assert path; the file name is a guess); the reflected names are original, the rest is guessed. The
// constructor (0x103954E0) and destructor (0x10395080) build and free a pool and a lookup table and are not
// reconstructed.
#ifndef PROTO_HEIGHTMAP_H
#define PROTO_HEIGHTMAP_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/core/heap.h"
#include "code/core/memory/memorypool.h"
#include "code/math/aabb.h"
#include "code/math/vector.h"

namespace container
{
	// The engine's Erase of the height array moves the elements with a loop that keeps the distance in a register
	template<> struct ArrayEraseInline<unsigned short>
	{
		enum
		{
			value = 3
		};
	};
}

namespace proto
{
	// The heights of a window of 6 by 6 cells around the cells being worked on (0x98 bytes; names guessed)
	struct HeightWindow
	{
		HeightWindow() : originX(0), originY(0)
		{
		}

		int originX;  // +0
		int originY;  // +4
		float values[36];  // +8
	};

	// The cache of the heights worked out for cells (a hash table of pointers keyed by cell, 0x28 bytes behind the
	// heights at +0xFC; the name and the member names are guesses). A removed slot holds the address of the table's own last word.
	struct HeightCache
	{
		HeightCache()
		{
			usedCount = 0;
			removedCount = 0;
			shrinks = false;
			maxRemoved = 100;
			maxLoadPercent = 60;
			slots = 0;
			keys = 0;
			removedMarker = 0;
			bucketCount = 0x2000;
			heap = core::GetCurrentHeap();
			Resize(bucketCount);
		}
		~HeightCache()
		{
			operator delete[](slots);
			operator delete[](keys);
		}
		// 0x103902C0: gives the table room for count buckets (the items move over)
		void Resize(unsigned int count);
		// 0x103901B0: files an item under a key
		void Insert(const int* key, void* item);
		// 0x103951F0: takes every slot holding the item out (answers how many); a table that shrinks packs itself when too many
		// removed slots pile up
		int Remove(void* item);
		// 0x10394E80: files every item again (drops the removed slots)
		void Rehash();

		// The probing of the table: the first slot is the key masked to the bucket count, the step comes from the next bits of
		// the key (always odd)
		class Probe
		{
		public:
			// 0x103949B0
			Probe(HeightCache* newTable) : table(newTable), key(0), start(0), current(0), step(0)
			{
			}
			// 0x1038CAA0: the position of a hash in the table
			unsigned int Mask(unsigned int hash)
			{
				return (table->bucketCount - 1) & hash;
			}
			// 0x1038CAC0: the step of a key (odd, from the bits behind the lowest nine)
			static unsigned int Step(unsigned __int64 hash)
			{
				return (unsigned int)((hash >> 9) & 0xfe) | 1;
			}
			// 0x1038DCA0: the first slot that is free, removed or filed under the key (null when the probing came round)
			void* StartInsert(const int* newKey);
			// 0x1038DC00: the first free slot or the slot filed under the key that is not a removed one
			void* Find(const int* newKey);
			// 0x1038CA20: the next slot to try for an insertion
			void* Next();
			// 0x10393340: the next slot to try for a search
			void* FindNext();

			HeightCache* table;  // +0
			int key;  // +4
			unsigned int start;  // +8
			unsigned int current;  // +0xC
			unsigned int step;  // +0x10
		};

		// Walks the stored items in bucket order (removed slots and empty ones are skipped)
		class Iterator
		{
		public:
			Iterator(HeightCache* newTable) : table(newTable)
			{
			}
			// 0x103938C0
			void* First()
			{
				index = 0xffffffff;
				return Next();
			}
			// 0x103932F0: the item behind the current one (null at the end)
			void* Next()
			{
				HeightCache* cache = table;
				unsigned int next = index;
				void* item;
				do
				{
					next++;
					if (next >= cache->bucketCount)
					{
						break;
					}
					item = cache->slots[next];
				}
				while (item == 0 || item == &cache->removedMarker);
				index = next;
				return Current();
			}
			// The item at the current position (null behind the last bucket)
			void* Current()
			{
				if (index >= table->bucketCount)
				{
					return 0;
				}
				return table->slots[index];
			}

			HeightCache* table;
			unsigned int index;
		};

		// Takes every item out (the slots are cleared; the items are not freed)
		void Clear()
		{
			for (unsigned int i = 0; i < bucketCount; i++)
			{
				slots[i] = 0;
			}
			usedCount = 0;
			removedCount = 0;
		}

		unsigned int bucketCount;  // +0
		unsigned int usedCount;  // +4
		unsigned int removedCount;  // +8
		bool shrinks;  // +0xC
		unsigned int maxRemoved;  // +0x10
		unsigned int maxLoadPercent;  // +0x14
		int heap;  // +0x18
		void** slots;  // +0x1C
		int* keys;  // +0x20
		void* removedMarker;  // +0x24
	};

	class Heightmap : public content::MetaLoadObject
	{
	public:
		typedef container::ArrayDynamic<unsigned short, container::AllocatorNew> HeightArray;

		// 0x103954E0
		Heightmap();
		// 0x10395080: frees the heights and gives the cached heights back to the pool (the deleting form is 0x103952B0)
		virtual ~Heightmap();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// 0x103937F0: stores the height of a cell (cells outside the grid are ignored)
		void SetHeight(int x, int y, float height);
		// 0x10393D90: the height of a cell (stored values behind the range of the heights are answered as they are, a cell
		// outside the grid gives 20001)
		float GetHeight(int x, int y);

		// 0x10394640: fills the window with the heights of the cells around a cell (size cells wide and margin more
		// around them; cells outside the grid or behind the range of the heights count as the highest or as 0)
		void FillWindow(int x, int y, unsigned int size, int margin, bool outsideHigh);
		// 0x1038C160: the height the window holds for a cell
		float GetWindowHeight(int x, int y);
		// 0x1038C180: the corner of a cell in the world, at the height of the window
		void GetWindowPoint(math::Vector* out, int x, int y);
		// 0x1038C1F0: the same moved by half a cell
		void GetWindowCellCenter(math::Vector* out, int x, int y);

		// Vftable slot 3 (0x103951D0): does nothing
		virtual void Slot3(int unused);
		// Vftable slot 5 (0x10393160): works out the factor behind the grid size and the half of the rows
		virtual bool Slot5();

		// 0x101E0A80 (the ai fight items' unit): the height of the cell (x, z); outside the grid or past the largest stored height it
		// is zero, or the invalid height when invalidOutside is set
		float GetHeight(int x, int z, bool invalidOutside) const;

		// 0x10DFA880 / 0x10DFA774: the largest stored height that counts and the one that marks a cell without a height
		static const unsigned short sMaxRawHeight;
		static const unsigned short sInvalidHeight;

		float gridSize;  // +8
		float inverseGridSize;  // +0xC
		int sizeX;  // +0x10
		int sizeY;  // +0x14
		int marginX;  // +0x18
		int marginY;  // +0x1C
		math::Vector minVec;  // +0x20
		float minHeight;  // +0x2C
		float maxHeight;  // +0x30
		float quantum;  // +0x34
		math::AABB aabb;  // +0x38
		int halfRows;  // +0x50
		HeightArray data;  // +0x54
		unsigned char unknown60[4];
		HeightWindow window;  // +0x64
		HeightCache cache;  // +0xFC
		core::MemoryPool pool;  // +0x124
	};
}

#endif
