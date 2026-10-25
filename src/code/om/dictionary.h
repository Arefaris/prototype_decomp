// om::Dictionary<Key, Value, Comparer> (RTTI: om::Dictionary<om::Name<...>, om::Name<...>, om::Comparer<...> >): an
// ordered map kept in a red-black tree whose nodes (0x20 bytes: the key, the value and the tree's node) are made by the
// om allocator. Only what the engine's reflection instances use is described.
#ifndef OM_DICTIONARY_H
#define OM_DICTIONARY_H

#include "code/om/allocation.h"
#include "code/om/tree.h"

namespace om
{
	template<class Key> struct Comparer
	{
	};

	template<class Key, class Value, class Compare> class Dictionary
	{
	public:
		struct Node
		{
			Key key;  // 0
			Value value;  // 8
			TreeNode link;  // 0x10
		};

		Dictionary()
		{
		}
		~Dictionary()
		{
			Clear();
		}
		// 0x108CFE30: takes every node out
		void Clear()
		{
			TreeNode* first;
			while ((first = tree.First()) != 0)
			{
				Node* node = reinterpret_cast<Node*>(reinterpret_cast<char*>(first) - 0x10);
				tree.Erase(&node->link);
				om::Release(node, sizeof(Node), 8);
			}
		}
		OM_ALLOCATION(Dictionary);

		TreeHead tree;
	};

	template<class Key, class Value, class Compare> const char* Dictionary<Key, Value, Compare>::AllocationTag()
	{
		return "";
	}
}

#endif
