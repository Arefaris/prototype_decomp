// Handles to game objects: a 16-bit index into the engine's game object table (0x1128348C, 8 bytes per entry) and
// the 16-bit serial the entry must still carry. The class and member names are guesses except IsValid (an assert
// in poimanager.cpp reads "playerPositionHandle.IsValid()"). Only what the engine's users need so far is declared;
// GameObject itself is in gameobject.h.
#ifndef ENGINE_GAMEOBJECT_GAMEOBJECTHANDLE_H
#define ENGINE_GAMEOBJECT_GAMEOBJECTHANDLE_H


namespace engine
{
	class MessageListeners;

	class GameObject;
	struct Message;

	struct GameObjectEntry
	{
		GameObject* object;
		unsigned short serial;
		unsigned short flags;
	};

	// The master table (0x1128348C, mastertable.h); its entries come first, which is all the handles need
	class MasterTable;
	extern MasterTable* gMasterTable;

	inline GameObjectEntry* GetGameObjectEntries()
	{
		return (GameObjectEntry*)gMasterTable;
	}

	// The handle data with the out-of-line constructors (gameobjecthandle.cpp). GameObjectHandle's own
	// constructor is inline, which is why callers take the address of a constructed temporary again instead of using
	// the base constructor's return value.
	class HandleBase
	{
	public:
		HandleBase();
		HandleBase(unsigned short newIndex, unsigned short newSerial);
		// The current serial of the table entry
		explicit HandleBase(unsigned short newIndex);

		unsigned short index;
		unsigned short serial;
	};

	class GameObjectHandle : public HandleBase
	{
	public:
		GameObjectHandle()
		{
		}
		GameObjectHandle(unsigned short newIndex, unsigned short newSerial) : HandleBase(newIndex, newSerial)
		{
		}
		explicit GameObjectHandle(unsigned short newIndex) : HandleBase(newIndex)
		{
		}
		unsigned short GetSerial() const
		{
			return serial;
		}
		// Puts the object on the deferred list (engine::DeferUpdate, 0x107EF710)
		void DeferUpdate(bool force) const;
		// The message router's registrations of the object on a channel (0x11318090; Query's meaning unknown)
		void RouterAdd(const MessageListeners& listeners) const;
		void RouterRemove(const MessageListeners& listeners) const;
		void RouterQuery(const MessageListeners& listeners) const;
		// The master table flags of the entry
		void ClearFlags(int mask) const;
		void SetFlags(unsigned short mask) const;

		GameObject* Get() const
		{
			if (index != 0xffff && GetGameObjectEntries()[index].serial == serial)
			{
				return GetGameObjectEntries()[index].object;
			}
			return 0;
		}
		bool IsValid() const
		{
			return index != 0xffff && GetGameObjectEntries()[index].serial == serial && GetGameObjectEntries()[index].object != 0;
		}
	};
}

#endif
