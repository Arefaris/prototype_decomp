#include "code/ravenphysics/collision/narrowphase/vertexquery.h"

namespace ravenphysics
{
	// By the node's two header bits: the mask and shift of the first field (the number of ids), of the second and of
	// the third (the numbers of ids of the two children)
	static const unsigned short kFields[5][4] =
	{
		{ 0x0fff, 0x003f, 0x003f, 0x000f },
		{ 0x0000, 0x0fc0, 0x0000, 0x0f00 },
		{ 0x0000, 0x0000, 0x0fc0, 0x00f0 },
		{ 0x0000, 0x0006, 0x0000, 0x0008 },
		{ 0x0000, 0x0000, 0x0006, 0x0004 }
	};

	// Adds an id to the list unless it has been seen
	static inline void AddId(TreeQuery* query, unsigned short id)
	{
		unsigned char bit = 1 << (id & 7);
		if ((query->seen[id >> 3] & bit) == 0)
		{
			query->seen[id >> 3] |= bit;
			IdList* list = query->ids;
			if (list->cursor < (unsigned short*)((char*)list->start + 0x1000))
			{
				*list->cursor = id;
				list->cursor++;
			}
		}
	}

	// FUNCTION: ENGINE 0x106A7750
	// NONMATCHING: the original keeps eight values in stack slots (header, kind, the id counts, the split and the
	// axis each have one) and the stack array starts four bytes later; ours allocates registers for most of them
#ifdef NONMATCHING
	// The nodes still to visit
	struct NodeStack
	{
		NodeStack()
			: count(0)
		{
		}

		void Push(const unsigned short* node)
		{
			items[count] = node;
			count++;
		}
		const unsigned short* Pop()
		{
			count--;
			return items[count];
		}

		const unsigned short* items[256];
		unsigned short count;
	};

	void QueryTree(const unsigned short* bounds, TreeQuery* query, const unsigned short* root)
	{
		NodeStack stack;
		const unsigned short* first = root;
		const unsigned short* second = 0;
		const unsigned short* node;
		while (true)
		{
			if (first != 0)
			{
				node = first;
				first = 0;
				if (second != 0)
				{
					stack.Push(second);
					second = 0;
				}
			}
			else if (second != 0)
			{
				node = second;
				second = 0;
			}
			else
			{
				if (stack.count == 0)
				{
					return;
				}
				node = stack.Pop();
			}
			unsigned int header = *node;
			unsigned int kind = header >> 12 & 3;
			unsigned short ids = kFields[0][kind] & header;
			unsigned short leftIds = (kFields[1][kind] & header) >> kFields[3][kind];
			unsigned short rightIds = (kFields[2][kind] & header) >> kFields[4][kind];
			const unsigned short* p = node + 1;
			while (ids != 0)
			{
				AddId(query, *p);
				p++;
				ids--;
			}
			unsigned int axis = (unsigned short)header >> 14;
			if (axis == 3)
			{
				continue;
			}
			unsigned short split = *p;
			p++;
			if (bounds[axis] > split)
			{
				if ((kind & 1) == 0)
				{
					p++;
				}
				else
				{
					p += leftIds;
				}
			}
			else if ((kind & 1) == 0)
			{
				first = node + *p;
				p++;
			}
			else
			{
				while (leftIds != 0)
				{
					AddId(query, *p);
					p++;
					leftIds--;
				}
			}
			if (bounds[3 + axis] >= split)
			{
				if ((kind & 2) == 0)
				{
					second = node + *p;
				}
				else
				{
					while (rightIds != 0)
					{
						AddId(query, *p);
						p++;
						rightIds--;
					}
				}
			}
		}
	}
#endif
}
