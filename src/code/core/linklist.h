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
		// 0x105AA070 (the fight tracks' copy): points every node at another object and hands the list over to it; the
		// first argument is not read
		void Retarget(T* unused, T* newObject);

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
				// The head sits in the class that declares the list, which may be a base of T: every node has the
				// same 12-byte layout, so the list is the same list seen as this node's type
				LinkList<T>& list = reinterpret_cast<LinkList<T>&>(newObject->watchList);
				next = list.head;
				if (list.head != 0)
				{
					list.head->prev = this;
				}
				prev = 0;
				list.head = this;
			}
		}
		// The copy lists itself on the same object (0x10805B90 is the engine's copy of this)
		Link(const Link<T>& other)
		{
			T* newObject = other.object;
			object = newObject;
			next = 0;
			prev = 0;
			if (newObject != 0)
			{
				LinkList<T>& list = reinterpret_cast<LinkList<T>&>(newObject->watchList);
				next = list.head;
				if (list.head != 0)
				{
					list.head->prev = this;
				}
				prev = 0;
				list.head = this;
			}
		}
		~Link()
		{
			if (object != 0)
			{
				reinterpret_cast<LinkList<T>&>(object->watchList).Remove(this);
			}
		}

		// The object this node is linked on
		T* object;
		Link<T>* next;
		Link<T>* prev;
	};
}

#endif
