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
	class MessageListeners;

	// The listeners of one message: its name and the handles (32 bytes)
	struct MessageListenerList
	{
		core::Name<core::CaseSensitiveKey> name;
		container::ArrayDynamicHeap<GameObjectHandle> handles;
		int unknown18;
		int unknown1C;
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
		// 0x108A5170 / 0x108A54C0 / 0x108A51B0: the handle's registrations (meaning of value unknown)
		void Add(GameObjectHandle handle, int value);
		void Remove(GameObjectHandle handle, int value);
		void Query(GameObjectHandle handle, int value);
		// 0x108A4BE0 / 0x108A4C10: forget a handle's registrations, exchange two handles' registrations
		void Invalidate(GameObjectHandle handle);
		void SwapHandles(GameObjectHandle first, GameObjectHandle second);

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
