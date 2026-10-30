// container::SListBase and container::SListLite<T> (names from the RTTI: SListLite<...>::Node derives from
// SListBase::Node): an intrusive singly linked list with head, tail and count. The list functions are out of line
// in another unit (0x106103C0 constructor, 0x10610450 PushBack, 0x106104E0 Remove); member names are guesses.
#ifndef CONTAINER_SLIST_H
#define CONTAINER_SLIST_H

#include <new>

namespace container
{
	class SListBase
	{
	public:
		class Node
		{
		public:
			Node* next;
		};

		// 0x106103C0 (the constructor is this function, mapped under both names)
		SListBase();
		// 0x106103C0: empties the list without freeing anything
		void Reset();
		void PushBack(Node* node);
		// 0x106103D0 (names of the members below guessed): links the node in front of the first
		void PushFront(Node* node);
		// 0x106103F0: the node in front of the given one, null for the first node (the last one for a null node)
		Node* Previous(const Node* node) const;
		// 0x10610420: links the node behind previous (in front of the first one when previous is null)
		void InsertAfter(Node* previous, Node* node);
		// 0x106105F0: links the node in front of before
		void InsertBefore(const Node* before, Node* node);
		// 0x10610500: appends the nodes of the other list and empties it
		void Splice(SListBase& other);
		// 0x10610550: reverses the order of the nodes
		void Reverse();
		// 0x10610480 (another unit; names guessed): unlinks the first node and answers it
		Node* PopFront();
		// 0x106104B0: unlinks the node after previous (the first one when previous is null) and answers it
		Node* RemoveAfter(Node* previous);
		void Remove(Node* node);
		bool Contains(const Node* node) const
		{
			for (Node* item = head; item != 0; item = item->next)
			{
				if (item == node)
				{
					return true;
				}
			}
			return false;
		}

		Node* head;
		Node* tail;
		int count;
	};

	// A list of T, where T derives from SListLite<T>::Node (possibly after a vftable, so the node can sit inside T)
	template<class T> class SListLite : public SListBase
	{
	public:
		class Node : public SListBase::Node
		{
		};

		T* First() const
		{
			return static_cast<T*>(static_cast<Node*>(head));
		}
		void PushBack(T* item)
		{
			SListBase::PushBack(static_cast<Node*>(item));
		}
		void Remove(T* item)
		{
			SListBase::Remove(static_cast<Node*>(item));
		}
		static T* Next(T* item)
		{
			return static_cast<T*>(static_cast<Node*>(static_cast<Node*>(item)->next));
		}
	};
}

namespace container
{
	// A list of values of T in nodes from Allocator (name guessed)
	template<class T, class Allocator> class SList : public SListBase
	{
	public:
		struct ValueNode : public SListBase::Node
		{
			T value;
		};

		class Iterator
		{
		public:
			explicit Iterator(ValueNode* newNode)
			{
				node = newNode;
			}

			T& operator*() const
			{
				return node->value;
			}
			Iterator& operator++()
			{
				node = (ValueNode*)node->next;
				return *this;
			}
			Iterator operator++(int)
			{
				Iterator old = *this;
				node = (ValueNode*)node->next;
				return old;
			}
			bool operator!=(const Iterator& other) const
			{
				return node != other.node;
			}

			ValueNode* node;
		};

		SList()
		{
		}
		~SList()
		{
			Clear();
		}

		unsigned int Size() const
		{
			return count;
		}
		Iterator Begin() const
		{
			return Iterator((ValueNode*)head);
		}
		Iterator End() const
		{
			return Iterator(0);
		}
		void PushBack(const T& value)
		{
			ValueNode* node = (ValueNode*)Allocator::Alloc(sizeof(ValueNode));
			if (node != 0)
			{
				node->value = value;
				SListBase::PushBack(node);
			}
		}
		void Clear()
		{
			ValueNode* node = (ValueNode*)head;
			while (node != 0)
			{
				ValueNode* current = node;
				node = (ValueNode*)node->next;
				Allocator::Free(current);
			}
			new (this) SListBase;
		}

		Allocator allocator;
	};
}

#endif
