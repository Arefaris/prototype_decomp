// container::SListBase (names guessed): the out-of-line members of the intrusive singly linked list declared in
// code/container/slist.h (0x106103C0 - 0x10610630).
#include "code/container/slist.h"

namespace container
{
	// FUNCTION: ENGINE 0x106103D0
	void SListBase::PushFront(Node* node)
	{
		node->next = head;
		head = node;
		if (node->next == 0)
		{
			tail = node;
		}
		count++;
	}

	// FUNCTION: ENGINE 0x106103F0
	SListBase::Node* SListBase::Previous(const Node* node) const
	{
		if (node == 0)
		{
			return tail;
		}
		Node* previous = 0;
		Node* item = head;
		while (item != node)
		{
			previous = item;
			item = item->next;
		}
		return previous;
	}

	// FUNCTION: ENGINE 0x10610420
	void SListBase::InsertAfter(Node* previous, Node* node)
	{
		if (previous == 0)
		{
			PushFront(node);
			return;
		}
		node->next = previous->next;
		previous->next = node;
		if (node->next == 0)
		{
			tail = node;
		}
		count++;
	}

	// FUNCTION: ENGINE 0x10610450
	void SListBase::PushBack(Node* node)
	{
		node->next = 0;
		if (tail == 0)
		{
			count++;
			head = node;
			tail = node;
			return;
		}
		tail->next = node;
		count++;
		tail = node;
	}

	// FUNCTION: ENGINE 0x10610480
	SListBase::Node* SListBase::PopFront()
	{
		Node* node = head;
		if (node == tail)
		{
			count--;
			head = 0;
			tail = 0;
			return node;
		}
		Node* next = node->next;
		count--;
		head = next;
		return node;
	}

	// FUNCTION: ENGINE 0x106104B0
	SListBase::Node* SListBase::RemoveAfter(Node* previous)
	{
		if (previous == 0)
		{
			Node* first = head;
			PopFront();
			return first;
		}
		Node* node = previous->next;
		if (tail == node)
		{
			tail = previous;
		}
		previous->next = node->next;
		count--;
		return node;
	}

	// FUNCTION: ENGINE 0x106104E0
	void SListBase::Remove(Node* node)
	{
		Node* previous = Previous(node);
		RemoveAfter(previous);
	}

	// FUNCTION: ENGINE 0x10610500
	// EQUIVALENT: the engine pops esi before the calls that empty the other list, ours after them, best 97.2%
	void SListBase::Splice(SListBase& other)
	{
		if (other.count != 0)
		{
			if (count != 0)
			{
				tail->next = other.head;
				tail = other.tail;
				count += other.count;
				other.Reset();
				return;
			}
			head = other.head;
			tail = other.tail;
			count = other.count;
			other.Reset();
		}
	}

	// FUNCTION: ENGINE 0x10610550
	// EQUIVALENT: the engine keeps the node in esi across the call that empties the list, ours in edx, best 53.1%
	void SListBase::Reverse()
	{
		Node* node = head;
		Reset();
		while (node != 0)
		{
			Node* next = node->next;
			PushFront(node);
			node = next;
		}
	}

	// FUNCTION: ENGINE 0x106105F0
	void SListBase::InsertBefore(const Node* before, Node* node)
	{
		InsertAfter(Previous(before), node);
	}

	// FUNCTION: ENGINE 0x106103C0
	// (the constructor calls this function: it returns nothing)
	void SListBase::Reset()
	{
		head = 0;
		tail = 0;
		count = 0;
	}
}
