#include "code/engine/gameobject/details/mastertable.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/engine/gameobject/messagerouter.h"

namespace engine
{
	// 0x107EF710 (gameobjectsystem.cpp)
	void DeferUpdate(GameObjectHandle handle, bool force);

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
	void GameObjectHandle::DeferUpdate(bool force) const
	{
		engine::DeferUpdate(*this, force);
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
