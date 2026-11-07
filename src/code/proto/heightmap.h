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
		int originX;  // +0
		int originY;  // +4
		float values[36];  // +8
	};

	class Heightmap : public content::MetaLoadObject
	{
	public:
		typedef container::ArrayDynamic<unsigned short, container::AllocatorNew> HeightArray;

		Heightmap();
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

		// Vftable slot 3 (0x103951D0): ignores the name
		virtual void SetName(const content::ObjectName& name);
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
		unsigned char unknownFC[0x190 - 0xFC];
	};
}

#endif
