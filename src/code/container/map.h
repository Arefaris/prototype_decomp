// container::TreeBase and container::Map<Key, Value, Allocator> (names guessed): an intrusive red-black tree whose
// functions take the comparison as a callback, and the keyed map over it. TreeBase is out of line in another unit
// (0x10610990 - 0x10610DD0); Map is a header template, so each unit that uses one has copies of the members it uses.
#ifndef CONTAINER_MAP_H
#define CONTAINER_MAP_H

#include "code/container/arraydynamicstatic.h"
#include "code/core/heap.h"
#include <new>

namespace container
{
	class TreeBase
	{
	public:
		struct Node
		{
			Node* left;
			Node* right;
			Node* parent;
			bool red;
		};

		// Orders a key (first argument) / a node against a node
		typedef int (*KeyCompare)(const void* key, const Node* node);
		typedef int (*NodeCompare)(const Node* a, const Node* b);
		// Called for every node by Clear (with the context Clear was given); true when the node may go
		typedef bool (*Deleter)(Node* node, void* context);

		TreeBase();
		bool IsEmpty() const;
		Node* Find(KeyCompare compare, const void* key) const;
		// The node a new node with key goes below, or null when key is in the tree
		Node* FindParent(KeyCompare compare, const void* key) const;
		void Insert(Node* node, NodeCompare compare, Node* parent);
		void Remove(Node* node);
		Node* First() const;
		Node* Next(Node* node) const;
		void Clear(Deleter deleter, void* context);

		Node* root;
		Node nil;
		int count;
	};

	template<class Key, class Value, class Allocator> class Map : public TreeBase
	{
	public:
		struct Pair
		{
			Pair(const Key& newKey, const Value& newValue)
			{
				key = newKey;
				value = newValue;
			}

			Key key;
			Value value;
		};

		struct MapNode : public TreeBase::Node
		{
			MapNode(const Pair& newPair) : pair(newPair)
			{
			}

			Pair pair;
		};

		class Iterator
		{
		public:
			Iterator(MapNode* newNode, Map* newMap)
			{
				node = newNode;
				map = newMap;
			}

			Pair* operator->() const
			{
				return &node->pair;
			}
			Pair& operator*() const
			{
				return node->pair;
			}
			Iterator& operator++()
			{
				node = (MapNode*)map->Next(node);
				return *this;
			}
			bool operator==(const Iterator& other) const
			{
				return node == other.node;
			}
			bool operator!=(const Iterator& other) const
			{
				return node != other.node;
			}

			MapNode* node;
			Map* map;
		};

		static int Compare(const Key& a, const Key& b)
		{
			if (a < b)
			{
				return -1;
			}
			if (b < a)
			{
				return 1;
			}
			return 0;
		}
		static int CompareNodes(const Node* a, const Node* b)
		{
			return Compare(((const MapNode*)a)->pair.key, ((const MapNode*)b)->pair.key);
		}
		static int CompareKey(const void* key, const Node* node)
		{
			return Compare(*(const Key*)key, ((const MapNode*)node)->pair.key);
		}
		static bool DeleteNode(Node* node, void* context)
		{
			Allocator::Free(node);
			return true;
		}

		explicit Map(Allocator newAllocator = Allocator()) : allocator(newAllocator)
		{
		}
		~Map()
		{
			Clear();
		}

		Iterator Begin()
		{
			return Iterator((MapNode*)First(), this);
		}
		Iterator End()
		{
			return Iterator(0, 0);
		}
		Iterator Find(const Key& key)
		{
			return Iterator((MapNode*)TreeBase::Find(CompareKey, &key), this);
		}
		Iterator Insert(const Pair& pair)
		{
			Node* parent = FindParent(CompareKey, &pair.key);
			if (parent == 0)
			{
				return Iterator(0, 0);
			}
			MapNode* node = new (Allocator::Alloc(sizeof(MapNode))) MapNode(pair);
			TreeBase::Insert(node, CompareNodes, parent);
			return Iterator(node, this);
		}
		Iterator Erase(Iterator position)
		{
			Iterator next = position;
			++next;
			Remove(position.node);
			Allocator::Free(position.node);
			return next;
		}
		bool Erase(const Key& key)
		{
			Iterator it = Find(key);
			if (it.node != 0)
			{
				Erase(it);
				return true;
			}
			return false;
		}
		void Clear()
		{
			TreeBase::Clear(DeleteNode, this);
		}

		Allocator allocator;
	};
}

#endif
