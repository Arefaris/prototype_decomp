// Queries of a mesh volume's compressed tree: the ids of the items whose cell a box touches (unit around
// 0x106A7750; file and names are guesses).
#ifndef RAVENPHYSICS_COLLISION_NARROWPHASE_VERTEXQUERY_H
#define RAVENPHYSICS_COLLISION_NARROWPHASE_VERTEXQUERY_H

namespace ravenphysics
{
	// The ids found so far (16 bit each): room for 2048 from start, cursor is the next free slot
	struct IdList
	{
		int unknown0;
		int unknown4;
		unsigned short* start;
		unsigned short* cursor;
	};

	// What a tree query fills in: a bit per id already collected and the list of them
	struct TreeQuery
	{
		unsigned char unknown0[0x2080];
		unsigned char* seen;
		IdList* ids;
	};

	// Collects the ids of the cells of the tree at root that the box (lower corner in bounds[0 .. 2], upper corner
	// in bounds[3 .. 5], quantised coordinates) touches (0x106A7750). A node is a 16-bit header (bits 12 - 13: which
	// of the two children are lists of ids, bits 14 - 15: the split axis, 3 for a node that is only a list), the
	// split value and the children
	void QueryTree(const unsigned short* bounds, TreeQuery* query, const unsigned short* root);
}

#endif
