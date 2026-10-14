// container::TreeBase (names guessed): an intrusive red-black tree whose functions take the comparison as a callback.
// The class is declared in code/container/map.h; this unit (0x10610990 - 0x10610DD0) holds the out-of-line members.
#include "code/container/map.h"

namespace container
{
	// FUNCTION: ENGINE 0x106109C0
	TreeBase::Node* TreeBase::Find(KeyCompare compare, const void* key) const
	{
		Node* node = root;
		while (node != &nil)
		{
			int order = compare(key, node);
			if (order < 0)
			{
				node = node->left;
			}
			else if (order > 0)
			{
				node = node->right;
			}
			else
			{
				return node;
			}
		}
		return 0;
	}
}
