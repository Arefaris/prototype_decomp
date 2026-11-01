// The list of the holders a reflected call made for its arguments (0x105CBDE0 - 0x105CF447, the unit of the reflection
// library's method classes).
#include "code/om/delegate.h"

namespace om
{
	// FUNCTION: ENGINE 0x105CBDE0
	void GarbageList::Add(GarbageLink* link)
	{
		link->next = head;
		head = link;
		if (link->next == 0)
		{
			tail = link;
		}
	}

	// FUNCTION: ENGINE 0x105CD920
	GarbageBase* GarbageList::GetFirst()
	{
		if (head != 0)
		{
			return static_cast<GarbageBase*>(head);
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x105CBE50
	void GarbageList::Remove(GarbageLink* link)
	{
		GarbageLink* current = head;
		GarbageLink* previous = 0;
		while (current != link)
		{
			previous = current;
			current = current->next;
		}
		if (previous == 0)
		{
			head = link->next;
		}
		else
		{
			previous->next = link->next;
		}
		if (link->next == 0)
		{
			tail = previous;
		}
	}

	// FUNCTION: ENGINE 0x105CF410
	void GarbageList::DeleteAll()
	{
		GarbageBase* holder = GetFirst();
		while (holder != 0)
		{
			Remove(holder);
			if (holder != 0)
			{
				delete holder;
			}
			holder = GetFirst();
		}
	}
}
