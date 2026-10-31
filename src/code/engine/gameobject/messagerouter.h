// engine::MessageRouter (0x2FE8 bytes; the global at 0x11318090): which game objects listen for which named message.
// The class lives in another unit (0x108A4xxx - 0x108A5xxx, no assert path; the file name and every name here are
// guesses); its destructor and the lookup cache are inline and used by the game object system.
#ifndef ENGINE_GAMEOBJECT_MESSAGEROUTER_H
#define ENGINE_GAMEOBJECT_MESSAGEROUTER_H

#include "code/container/arraydynamic.h"
#include "code/core/name.h"
#include "code/engine/gameobject/details/mastertable.h"
#include "code/engine/gameobject/gameobjecthandle.h"

namespace engine
{
	// A message channel: the name its subscribers are registered under
	class MessageListeners : public core::Name<core::CaseSensitiveKey>
	{
	public:
		// The static lists are built from the channel's text
		MessageListeners(const char* text, int unknown)
			: core::Name<core::CaseSensitiveKey>(text, unknown)
		{
		}
	};

	// The valid handles of a list, in order (skips the handles whose objects are gone)
	class HandleIterator
	{
	public:
		HandleIterator()
		{
			handle = 0;
			array = 0;
		}
		HandleIterator(GameObjectHandle* newHandle, container::ArrayDynamicHeap<GameObjectHandle>* newArray)
		{
			handle = newHandle;
			array = newArray;
			SkipInvalid();
		}
		HandleIterator(const HandleIterator& other)
		{
			handle = other.handle;
			array = other.array;
		}
		// 0x1020A2E0 (the copy the engine's calls reach)
		void SkipInvalid();
		HandleIterator& operator++()
		{
			handle++;
			SkipInvalid();
			return *this;
		}
		GameObjectHandle* operator->() const
		{
			return handle;
		}
		bool operator!=(HandleIterator other)
		{
			HandleIterator self = *this;
			return self.handle != other.handle;
		}

		GameObjectHandle* handle;
		container::ArrayDynamicHeap<GameObjectHandle>* array;
	};

	// The subscribers of one channel: its name and the handles (32 bytes)
	struct MessageListenerList
	{
		// 0x108327B0 (the router's unit)
		HandleIterator Begin();
		HandleIterator End()
		{
			return HandleIterator(handles.end, &handles);
		}

		core::Name<core::CaseSensitiveKey> name;
		container::ArrayDynamicHeap<GameObjectHandle> handles;
		int unknown18;
		int unknown1C;
	};

	// The list of a channel as GetListeners answers it
	class MessageListenerRef
	{
	public:
		MessageListenerRef(MessageListenerList* newList)
		{
			list = newList;
		}
		MessageListenerRef(const MessageListenerRef& other)
		{
			list = other.list;
		}

		MessageListenerList* list;
	};

	// The 16-byte entries of the router's second table (meaning unknown)
	struct MessageRouterEntry
	{
		int unknown[4];
	};

	class MessageRouter
	{
	public:
		// 0x108A5510
		explicit MessageRouter(const container::AllocatorCoreAligned<16>& allocator);

		// 0x108A5370
		void InitListeners(MessageListeners* listeners, int count);
		// 0x108A5170 / 0x108A54C0 / 0x108A51B0: the handle's registrations on a channel (Query's meaning unknown)
		bool Add(GameObjectHandle handle, const MessageListeners& listeners);
		void Remove(GameObjectHandle handle, const MessageListeners& listeners);
		void Query(GameObjectHandle handle, const MessageListeners& listeners);
		// 0x108A4BE0 / 0x108A4C10: forget a handle's registrations, exchange two handles' registrations
		void Invalidate(GameObjectHandle handle);
		void SwapHandles(GameObjectHandle first, GameObjectHandle second);

		// 0x108A5020: the list of a channel, null when it has none
		MessageListenerList* FindListSlow(const MessageListeners& listeners);
		MessageListenerList* FindList(const MessageListeners& listeners)
		{
			if (listeners == cachedName)
			{
				return cachedList;
			}
			return FindListSlow(listeners);
		}

		void Clear()
		{
			lists.Clear();
		}

		// The last list looked up and its name
		core::Name<core::CaseSensitiveKey> cachedName;
		MessageListenerList* cachedList;
		container::ArrayFixed<MessageListenerList, 255> lists;
		container::ArrayFixed<MessageRouterEntry, 255> entries;
		int heap;
	};

	extern MessageRouter* gMessageRouter;
}

#endif
