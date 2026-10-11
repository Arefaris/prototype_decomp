// container::SListBase and container::SListLite<T> (names from the RTTI: SListLite<...>::Node derives from
// SListBase::Node): an intrusive singly linked list with head, tail and count. The list functions are out of line
// in another unit (0x106103C0 constructor, 0x10610450 PushBack, 0x106104E0 Remove); member names are guesses.
#ifndef CONTAINER_SLIST_H
#define CONTAINER_SLIST_H

namespace container
{
	class SListBase
	{
	public:
		struct Node
		{
			Node* next;
		};

		SListBase();
		void PushBack(Node* node);
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
		struct Node : public SListBase::Node
		{
		};

		T* First() const
		{
			return static_cast<T*>(static_cast<Node*>(head));
		}
		static T* Next(T* item)
		{
			return static_cast<T*>(static_cast<Node*>(static_cast<Node*>(item)->next));
		}
	};
}

#endif
