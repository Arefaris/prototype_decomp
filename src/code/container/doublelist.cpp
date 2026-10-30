// container::DoubleListBase (see doublelist.h; unit 0x1060E6C0 - 0x1060E950).
#include "code/container/doublelist.h"

namespace container
{
	// FUNCTION: ENGINE 0x1060E6C0
	void DoubleListBase::Reset()
	{
		head = 0;
		tail = 0;
		count = 0;
	}

	// FUNCTION: ENGINE 0x1060E6D0
	void DoubleListBase::PushFront(Node* node)
	{
		node->next = head;
		if (head == 0)
		{
			tail = node;
			head = node;
			node->previous = 0;
			count++;
			return;
		}
		head->previous = node;
		head = node;
		node->previous = 0;
		count++;
	}

	// FUNCTION: ENGINE 0x1060E730
	void DoubleListBase::PushBack(Node* node)
	{
		node->previous = tail;
		if (head == 0)
		{
			head = node;
			tail = node;
			node->next = 0;
			count++;
			return;
		}
		tail->next = node;
		tail = node;
		node->next = 0;
		count++;
	}

	// FUNCTION: ENGINE 0x1060E770
	void DoubleListBase::Remove(Node* node)
	{
		if (node->previous == 0)
		{
			head = node->next;
		}
		else
		{
			node->previous->next = node->next;
		}
		if (node->next == 0)
		{
			tail = node->previous;
		}
		else
		{
			node->next->previous = node->previous;
		}
		count--;
		node->next = 0;
		node->previous = 0;
	}

	// FUNCTION: ENGINE 0x1060E7B0
	DoubleListBase::Node* DoubleListBase::Erase(Node* const* position)
	{
		Node* node = *position;
		if (node != 0)
		{
			Remove(node);
		}
		return node;
	}

	// FUNCTION: ENGINE 0x1060E7D0
	// EQUIVALENT: register allocation (the engine keeps the next node in edx, ours in eax), best 92.7%
	void DoubleListBase::PopFront()
	{
		if (head == tail)
		{
			count--;
			head = 0;
			tail = 0;
			return;
		}
		Node* next = head->next;
		head = next;
		next->previous = 0;
		count--;
	}

	// FUNCTION: ENGINE 0x1060E800
	// EQUIVALENT: the engine pops esi before the calls that empty the other list, ours after them, best 97.5%
	void DoubleListBase::Splice(DoubleListBase& other)
	{
		if (other.count != 0)
		{
			if (count != 0)
			{
				tail->next = other.head;
				other.head->previous = tail;
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

	// FUNCTION: ENGINE 0x1060E850
	// EQUIVALENT: the engine keeps the node in esi across the call that empties the list, ours in edx, best 53.1%
	void DoubleListBase::Reverse()
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

	// FUNCTION: ENGINE 0x1060E900
	// EQUIVALENT: register allocation (the engine keeps before in eax and the node in edx, ours the other way round)
	void DoubleListBase::Insert(Node* before, Node* node)
	{
		if (before == 0)
		{
			PushBack(node);
			return;
		}
		node->next = before;
		node->previous = before->previous;
		if (before->previous != 0)
		{
			before->previous->next = node;
			before->previous = node;
			count++;
			return;
		}
		head = node;
		before->previous = node;
		count++;
	}
}
