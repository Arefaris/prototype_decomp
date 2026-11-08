// engine::MessageListenerList (the subscribers of one message channel; the router's list entries): the functions of the
// unit at 0x10832480 - 0x10832890 (no assert path; the file name is a guess). A list keeps the handles of the game
// objects that listen; handles of objects that are gone stay in it until a pass over the list drops them.
#include "code/engine/gameobject/messagerouter.h"

namespace engine
{
	// container::Find over the handles (the engine keeps two out-of-line copies; the list's methods expand it)
	inline GameObjectHandle* FindHandle(GameObjectHandle* first, GameObjectHandle* last, const GameObjectHandle& value)
	{
		while (first != last && *first != value)
		{
			first++;
		}
		return first;
	}

	// The channel's name and the heap the handles live in
	// FUNCTION: ENGINE 0x10832780
	// NONMATCHING: the engine stores the heap word before the three zero words (best 86.7 %)
#ifdef NONMATCHING
	MessageListenerList::MessageListenerList(const core::Name<core::CaseSensitiveKey>& newName,
		const container::AllocatorCoreAligned<16>& allocator)
		: name(newName), handles(allocator), unknown18(0), unknown1C(0)
	{
	}
#endif

	// Whether the handle is in the list
	// FUNCTION: ENGINE 0x10832500
	bool MessageListenerList::AddHandle(GameObjectHandle handle)
	{
		GameObjectHandle* end = handles.end;
		return FindHandle(handles.begin, end, handle) != end;
	}

	// Clears the handle's entry
	// FUNCTION: ENGINE 0x10832530
	// NONMATCHING: the loop exit is not threaded to the return in the engine (best 92 %)
#ifdef NONMATCHING
	void MessageListenerList::QueryHandle(GameObjectHandle handle)
	{
		GameObjectHandle* end = handles.end;
		GameObjectHandle* item = FindHandle(handles.begin, end, handle);
		if (item != end)
		{
			item->index = 0xffff;
			item->serial = 0;
			unknown18--;
		}
	}
#endif

	// Makes the handle's entry stale
	// FUNCTION: ENGINE 0x10832570
	// NONMATCHING: the loop exit is not threaded to the return in the engine (best 95 %)
#ifdef NONMATCHING
	void MessageListenerList::InvalidateHandle(GameObjectHandle handle)
	{
		GameObjectHandle* end = handles.end;
		GameObjectHandle* item = FindHandle(handles.begin, end, handle);
		if (item != end)
		{
			item->serial++;
		}
	}
#endif

	// Every entry of first becomes second and the other way round
	// FUNCTION: ENGINE 0x108325A0
	void MessageListenerList::SwapHandles(GameObjectHandle first, GameObjectHandle second)
	{
		GameObjectHandle* end = handles.end;
		for (GameObjectHandle* item = handles.begin; item != end; item++)
		{
			if (*item == first)
			{
				*item = second;
			}
			else if (*item == second)
			{
				*item = first;
			}
		}
	}

	// Drops the entries of objects that are gone
	// FUNCTION: ENGINE 0x10832660
	void MessageListenerList::DropInvalid()
	{
		if (unknown1C != 0)
		{
			return;
		}
		if (unknown18 == 0)
		{
			if (handles.begin != handles.end)
			{
				handles.Reset();
			}
			return;
		}
		GameObjectHandle* item = handles.begin;
		while (item != handles.end)
		{
			if (!item->IsValid())
			{
				handles.EraseFast(item);
			}
			else
			{
				item++;
			}
		}
		unknown18 = handles.Size();
	}

	// FUNCTION: ENGINE 0x108327B0
	HandleIterator MessageListenerList::Begin()
	{
		HandleIterator iterator(handles.begin, &handles);
		if (iterator.handle == handles.end)
		{
			unknown18 = 0;
		}
		return iterator;
	}

	// Puts the handle in (in the place of a stale one when there is one); answers true
	// FUNCTION: ENGINE 0x108327E0
	// NONMATCHING: register allocation of the stale-entry search (best 42 %)
#ifdef NONMATCHING
	bool MessageListenerList::RemoveHandle(GameObjectHandle handle)
	{
		container::ArrayDynamicHeap<GameObjectHandle>& array = handles;
		GameObjectHandle* stale = handles.end;
		for (GameObjectHandle* item = handles.begin; item != handles.end; item++)
		{
			if (*item == handle)
			{
				return true;
			}
			if (stale == handles.end && !item->IsValid())
			{
				stale = item;
			}
		}
		if (stale == handles.end)
		{
			if (array.end == array.capacity)
			{
				array.Reserve(array.Size() * 2);
			}
			array.PushBack(handle);
		}
		else
		{
			*stale = handle;
		}
		unknown18++;
		return true;
	}
#endif
}
