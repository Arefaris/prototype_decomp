// The watch list an object keeps of the things that point at it: the object holds the head of the list at a fixed
// offset of itself, every watcher one 12-byte node (the object, then the two links; the node whose prev is null is
// the head). Only Remove is out of line (0x10095300, the one copy every unit that unlinks reaches); a node inserts
// itself with the constructor.
#ifndef CORE_LINKLIST_H
#define CORE_LINKLIST_H

namespace core
{
	template<class T> struct Link;

	// The head of a watch list, embedded in the object the nodes point at
	template<class T> class LinkList
	{
	public:
		// 0x10095300: unlinks a node and clears it
		void Remove(Link<T>* node);

		Link<T>* head;
	};

	template<class T> struct Link
	{
		Link(T* newObject)
		{
			object = newObject;
			next = 0;
			prev = 0;
			if (newObject != 0)
			{
				next = newObject->watchList.head;
				if (newObject->watchList.head != 0)
				{
					newObject->watchList.head->prev = this;
				}
				prev = 0;
				newObject->watchList.head = this;
			}
		}
		~Link()
		{
			if (object != 0)
			{
				object->watchList.Remove(this);
			}
		}

		// The object this node is linked on
		T* object;
		Link<T>* next;
		Link<T>* prev;
	};
}

#endif
