// The router that tells which game objects listen for which named message (code/engine/gameobject/messagerouter.cpp; the
// file name is a guess, the unit starts at 0x108A4AA0). Names are guesses.
#include "code/engine/gameobject/messagerouter.h"

namespace engine
{
	// The first entry of the sorted table that is not less than the key (the engine keeps one copy of the search)
	// FUNCTION: ENGINE 0x108A4CC0
	MessageRouterEntry* LowerBoundEntry(MessageRouterEntry* first, MessageRouterEntry* last, const MessageListeners& key)
	{
		int count = last - first;
		while (0 < count)
		{
			int half = count / 2;
			MessageRouterEntry* middle = first + half;
			if (middle->key < key)
			{
				first = middle + 1;
				count = count + (-1 - half);
			}
			else
			{
				count = half;
			}
		}
		return first;
	}

	// FUNCTION: ENGINE 0x108A4BE0
	void MessageRouter::Invalidate(GameObjectHandle handle)
	{
		MessageListenerList* end = lists.End();
		for (MessageListenerList* list = lists.Begin(); list != end; list++)
		{
			list->InvalidateHandle(handle);
		}
	}

	// FUNCTION: ENGINE 0x108A4C10
	void MessageRouter::SwapHandles(GameObjectHandle first, GameObjectHandle second)
	{
		MessageListenerList* end = lists.End();
		for (MessageListenerList* list = lists.Begin(); list != end; list++)
		{
			list->SwapHandles(first, second);
		}
	}

	// FUNCTION: ENGINE 0x108A5020
	// EQUIVALENT: scheduling: the engine computes the table's address before it pushes the key for the search, ours after (94.3 %)
	MessageListenerList* MessageRouter::FindListSlow(const MessageListeners& listeners)
	{
		MessageRouterEntry* end = entries.End();
		MessageRouterEntry* first = entries.Begin();
		MessageRouterEntry* found = LowerBoundEntry(first, end, listeners);
		if (found != end)
		{
			if (!(listeners < found->key))
			{
				end = found;
			}
		}
		if (end != entries.End())
		{
			MessageListenerList* list = end->list;
			cachedName = listeners;
			cachedList = list;
			return end->list;
		}
		cachedName = listeners;
		cachedList = 0;
		return 0;
	}

	// FUNCTION: ENGINE 0x108A5170
	bool MessageRouter::Add(GameObjectHandle handle, const MessageListeners& listeners)
	{
		MessageListenerList* list = FindList(listeners);
		if (list != 0)
		{
			return list->AddHandle(handle);
		}
		return false;
	}

	// FUNCTION: ENGINE 0x108A51B0
	void MessageRouter::Query(GameObjectHandle handle, const MessageListeners& listeners)
	{
		MessageListenerList* list = FindList(listeners);
		if (list != 0)
		{
			list->QueryHandle(handle);
		}
	}

	// FUNCTION: ENGINE 0x108A54C0
	bool MessageRouter::Remove(GameObjectHandle handle, const MessageListeners& listeners)
	{
		MessageListenerList* list = FindList(listeners);
		if (list == 0)
		{
			list = InitListeners((MessageListeners*)&listeners, 0x10);
			if (list == 0)
			{
				return false;
			}
		}
		return list->RemoveHandle(handle);
	}
}
