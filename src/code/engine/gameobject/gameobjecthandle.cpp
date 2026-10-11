#include "code/engine/gameobject/details/mastertable.h"
#include "code/engine/gameobject/gameobjecthandle.h"

namespace engine
{
	// 0x107EF710 (another unit): delivers a message to the object behind a handle
	void SendMessage(GameObjectHandle handle, Message* message);

	// The message router (0x11318090, another unit); its methods take the handle by value
	class MessageRouter
	{
	public:
		// 0x108A5170 / 0x108A54C0 / 0x108A51B0
		void Add(GameObjectHandle handle, int value);
		void Remove(GameObjectHandle handle, int value);
		void Query(GameObjectHandle handle, int value);
	};
	extern MessageRouter* gMessageRouter;

	// FUNCTION: ENGINE 0x107EE330
	HandleBase::HandleBase()
	{
		index = 0xffff;
		serial = 0;
	}

	// FUNCTION: ENGINE 0x107EE340
	HandleBase::HandleBase(unsigned short newIndex, unsigned short newSerial)
	{
		index = newIndex;
		serial = newSerial;
	}

	// FUNCTION: ENGINE 0x107EE360
	void GameObjectHandle::Send(Message* message) const
	{
		SendMessage(*this, message);
	}

	// FUNCTION: ENGINE 0x107EE380
	void GameObjectHandle::RouterAdd(int value) const
	{
		gMessageRouter->Add(*this, value);
	}

	// FUNCTION: ENGINE 0x107EE3A0
	void GameObjectHandle::ClearFlags(int mask) const
	{
		gMasterTable->ClearFlags(*this, mask);
	}

	// FUNCTION: ENGINE 0x107EE3C0
	void GameObjectHandle::SetFlags(unsigned short mask) const
	{
		gMasterTable->SetFlags(*this, mask);
	}

	// FUNCTION: ENGINE 0x107EE3E0
	void GameObjectHandle::RouterRemove(int value) const
	{
		gMessageRouter->Remove(*this, value);
	}

	// FUNCTION: ENGINE 0x107EE400
	void GameObjectHandle::RouterQuery(int value) const
	{
		gMessageRouter->Query(*this, value);
	}

	// MasterTable::GetSerial is inline (mastertable.h); this is its kept copy
	// FUNCTION: ENGINE 0x107EE420

	// FUNCTION: ENGINE 0x107EE430
	HandleBase::HandleBase(unsigned short newIndex)
	{
		index = newIndex;
		serial = gMasterTable->GetSerial(newIndex);
	}
}
