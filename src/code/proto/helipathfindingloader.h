// proto::HeliPathfindingLoader (RTTI and reflection names; a load object): the pathfinding grid of the helicopters - its
// size in cells, a height per cell and a table of nodes the path search fills. Unit 0x10397700 - 0x10397B00 (no assert
// path; the file name is a guess); the reflected names are original, the rest is guessed.
#ifndef PROTO_HELIPATHFINDINGLOADER_H
#define PROTO_HELIPATHFINDINGLOADER_H

#include "code/container/arrayc.h"
#include "code/content/arraycmetatype.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"

namespace proto
{
	class HeliPathfindingLoader : public content::MetaLoadObject
	{
	public:
		enum
		{
			CELL_COUNT = 10000
		};

		// One node of the search (12 bytes; the engine initialises only the parent)
		struct Node
		{
			int unknown0;  // +0
			int unknown4;  // +4
			unsigned short unknown8;  // +8
			unsigned short parent;  // +0xA
		};

		// 0x103978E0
		HeliPathfindingLoader();
		// 0x10397930 (the deleting destructor is 0x10397940, which expands it)
		virtual ~HeliPathfindingLoader()
		{
		}
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// 0x10397750
		bool HasData();
		// 0x10397760: the next number of a node
		short TakeNodeNumber();

		int sizeX;  // +8
		int sizeZ;  // +0xC
		container::ArrayC<float, CELL_COUNT> data;  // +0x10
		Node nodes[CELL_COUNT];  // +0x9C50
		unsigned short nextNodeNumber;  // +0x27110
	};
}

#endif
