// container::DoubleListBase (a name guess: the code shared by the engine's container::DoubleList<T> lists, whose
// instances for engine::FmvRequest are mapped under their template names): an intrusive doubly linked list with head,
// tail and count (0x1060E6C0 - 0x1060E950).
#ifndef CONTAINER_DOUBLELIST_H
#define CONTAINER_DOUBLELIST_H

namespace container
{
	class DoubleListBase
	{
	public:
		struct Node
		{
			Node* next;
			Node* previous;
		};

		// 0x1060E6C0: empties the list without freeing anything
		void Reset();
		// 0x1060E6D0 / 0x1060E730: links the node in front of the first / behind the last
		void PushFront(Node* node);
		void PushBack(Node* node);
		// 0x1060E770: unlinks the node
		void Remove(Node* node);
		// 0x1060E7B0: unlinks the node the position points at and answers it (null: none)
		Node* Erase(Node* const* position);
		// 0x1060E7D0: unlinks the first node
		void PopFront();
		// 0x1060E800: appends the nodes of the other list and empties it
		void Splice(DoubleListBase& other);
		// 0x1060E850: reverses the order of the nodes
		void Reverse();
		// 0x1060E900: links the node in front of before (at the end when before is null)
		void Insert(Node* before, Node* node);

		Node* head;
		Node* tail;
		int count;
	};
}

#endif
