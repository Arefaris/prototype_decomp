#include "code/core/debug.h"
#include "code/engine/controller/inputsystem.h"
#include "code/engine/system/enginememory.h"
#include "code/engine/system/poimanager.hpp"
#include <new>

#define POI_FILE "..\\..\\..\\code\\engine\\system\\poimanager.cpp"

namespace engine
{
	// GLOBAL: ENGINE 0x1130D31C
	POIManager* POIManager::sManagers;
	// GLOBAL: ENGINE 0x1130D318
	int POIManager::sMaxPlayers;
	// GLOBAL: ENGINE 0x1130D328
	int POIManager::sRegisteredPlayers;
	// GLOBAL: ENGINE 0x1130D320
	int POIManager::sNextSerial;
	// GLOBAL: ENGINE 0x1130D310
	void (*POIManager::sPOIChanged)(int playerIndex);
	// GLOBAL: ENGINE 0x1130D314
	void (*POIManager::sPlayerRegistered)(int playerIndex);
	// GLOBAL: ENGINE 0x1130D324
	void (*POIManager::sControlChanged)(int playerIndex);

	// Kept copies of inline functions used in this unit: InputSystem::GetPlayerCount, POIManager::GetPlayerIndex
	// (poimanager.hpp), the empty POIManager destructor and POIManager's vector deleting destructor
	// FUNCTION: ENGINE 0x10825AF0
	// FUNCTION: ENGINE 0x10825B00
	// FUNCTION: ENGINE 0x10825C60
	// FUNCTION: ENGINE 0x10825F10

	// FUNCTION: ENGINE 0x10825B80
	inline PlayerControlChangedMessage::PlayerControlChangedMessage() : IntrusiveMessage(14, 0)
	{
	}

	// 0x10825EF0 is the compiler's scalar deleting destructor of this class
	// FUNCTION: ENGINE 0x10825EF0
	// FUNCTION: ENGINE 0x10825BB0
	inline PlayerControlChangedMessage::~PlayerControlChangedMessage()
	{
	}

	// FUNCTION: ENGINE 0x10825BC0
	POIManager::WorldStreamerPOI::WorldStreamerPOI()
	{
		position.x = math::kZeroVector.x;
		position.y = math::kZeroVector.y;
		position.z = math::kZeroVector.z;
		type = POI_NONE;
		serial = -1;
	}

	// FUNCTION: ENGINE 0x10825C10
	POIManager::WorldStreamerPOI::WorldStreamerPOI(math::Vector point)
	{
		position.x = point.x;
		position.y = point.y;
		position.z = point.z;
		type = POI_POSITION;
		serial = ++sNextSerial;
	}

	// FUNCTION: ENGINE 0x10825C70
	void POIManager::Reset()
	{
		mControlledObjectStackIndex = 0;
		mWorldStreamerPOIStackIndex = 0;
		mInactive = false;
	}

	// FUNCTION: ENGINE 0x10825C90
	int POIManager::PushPOI(float x, float y, float z)
	{
		OLD_ASSERT_AT(POI_FILE, 0xe3, mWorldStreamerPOIStackIndex < WORLD_STREAM_POI_STACK_SIZE,
			"mWorldStreamerPOIStackIndex < WORLD_STREAM_POI_STACK_SIZE", "");
		WorldStreamerPOI* poi = &mWorldStreamerPOIStack[mWorldStreamerPOIStackIndex++];
		new (poi) WorldStreamerPOI(math::Vector(x, y, z));
		if (sPOIChanged != 0)
		{
			sPOIChanged(this - sManagers);
		}
		return poi->serial;
	}

	// FUNCTION: ENGINE 0x10825D50
	void POIManager::PopPOI(GameObjectHandle object)
	{
		OLD_ASSERT_AT(POI_FILE, 0x109, mWorldStreamerPOIStackIndex, "mWorldStreamerPOIStackIndex", "");
		mWorldStreamerPOIStackIndex--;
		if (sPOIChanged != 0)
		{
			sPOIChanged(this - sManagers);
		}
	}

	// FUNCTION: ENGINE 0x10825DD0
	void POIManager::PopPOI(int serial)
	{
		OLD_ASSERT_AT(POI_FILE, 0x11a, mWorldStreamerPOIStackIndex, "mWorldStreamerPOIStackIndex", "");
		mWorldStreamerPOIStackIndex--;
		if (sPOIChanged != 0)
		{
			sPOIChanged(this - sManagers);
		}
	}

	// FUNCTION: ENGINE 0x10825E50
	bool POIManager::IsFirstPlayerActive()
	{
		if (sRegisteredPlayers > 0)
		{
			return !sManagers[0].mInactive;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10825E70
	int POIManager::GetRegisteredPlayers()
	{
		return sRegisteredPlayers;
	}

	// FUNCTION: ENGINE 0x10825E80
	GameObjectHandle POIManager::GetPlayerObject(int playerIndex)
	{
		OLD_ASSERT_AT(POI_FILE, 0x198, playerIndex < sRegisteredPlayers, "playerIndex < sRegisteredPlayers", "");
		return sManagers[playerIndex].mPlayer;
	}

	// FUNCTION: ENGINE 0x10825F50
	void POIManager::DestroyAll()
	{
		if (sManagers != 0)
		{
			delete[] sManagers;
			sManagers = 0;
		}
	}

	// FUNCTION: ENGINE 0x10825F70
	void POIManager::ResetAll()
	{
		for (int i = 0; i < sMaxPlayers; i++)
		{
			Get(i).Reset();
		}
		sRegisteredPlayers = 0;
	}

	// FUNCTION: ENGINE 0x10825FF0
	POIManager::POIManager()
	{
		Reset();
	}

	// FUNCTION: ENGINE 0x10826040
	// EQUIVALENT: the engine keeps the handle serial in memory for the table check; our build loads it into a
	// register first
	POIManager::WorldStreamerPOI::WorldStreamerPOI(GameObjectHandle object) : handle(object)
	{
		type = POI_OBJECT;
		serial = ++sNextSerial;
		if (handle.IsValid())
		{
			position.x = math::kZeroVector.x;
			position.y = math::kZeroVector.y;
			position.z = math::kZeroVector.z;
		}
		else
		{
			const math::Matrix& matrix = handle.Get()->transform->value;
			position.Set(matrix.m[3][0], matrix.m[3][1], matrix.m[3][2]);
		}
	}

	// FUNCTION: ENGINE 0x10826180
	// EQUIVALENT: the engine checks the handle twice (IsValid, then Get); our build folds the second check away
	math::Vector POIManager::WorldStreamerPOI::GetPosition() const
	{
		if (type == POI_OBJECT && handle.IsValid())
		{
			return *(const math::Vector*)handle.Get()->transform->value.m[3];
		}
		return position;
	}

	// FUNCTION: ENGINE 0x10826210
	void POIManager::CreateAll()
	{
		if (sManagers == 0)
		{
			sMaxPlayers = controller::InputSystem::Get()->GetPlayerCount() + 1;
			sManagers = new (0xc) POIManager[sMaxPlayers];
		}
	}

	// FUNCTION: ENGINE 0x10826290
	int POIManager::PushPOI(GameObjectHandle object)
	{
		OLD_ASSERT_AT(POI_FILE, 0xd4, mWorldStreamerPOIStackIndex < WORLD_STREAM_POI_STACK_SIZE,
			"mWorldStreamerPOIStackIndex < WORLD_STREAM_POI_STACK_SIZE", "");
		WorldStreamerPOI* poi = &mWorldStreamerPOIStack[mWorldStreamerPOIStackIndex++];
		new (poi) WorldStreamerPOI(object);
		if (sPOIChanged != 0)
		{
			sPOIChanged(this - sManagers);
		}
		return poi->serial;
	}

	// FUNCTION: ENGINE 0x10826330
	void POIManager::ChangeControl(GameObjectHandle previous, GameObjectHandle next)
	{
		if (previous.IsValid())
		{
			GameObject* inst = previous.Get();
			OLD_ASSERT_AT(POI_FILE, 0x152, inst, "inst", "");
			PlayerControlChangedMessage message;
			message.info.Reset();
			inst->SendMessage(&message);
		}
		if (next.IsValid())
		{
			GameObject* inst = next.Get();
			OLD_ASSERT_AT(POI_FILE, 0x15b, inst, "inst", "");
			PlayerControlChangedMessage message;
			message.info.playerIndex = GetPlayerIndex();
			inst->SendMessage(&message);
		}
	}

	// FUNCTION: ENGINE 0x108264A0
	void POIManager::RegisterPlayer(int playerIndex, GameObjectHandle playerPositionHandle, bool active)
	{
		OLD_ASSERT_AT(POI_FILE, 0x168, playerIndex < sMaxPlayers, "playerIndex < sMaxPlayers", "");
		sManagers[playerIndex].mPlayer = playerPositionHandle;
		if (active)
		{
			sManagers[playerIndex].mInactive = false;
			sRegisteredPlayers++;
			sPlayerRegistered(playerIndex);
		}
		else
		{
			OLD_ASSERT_AT(POI_FILE, 0x174, playerPositionHandle.IsValid(), "playerPositionHandle.IsValid()", "");
			sManagers[playerIndex].mInactive = true;
			sPlayerRegistered(playerIndex);
		}
	}

	// FUNCTION: ENGINE 0x108265B0
	void POIManager::PushControlled(GameObjectHandle object)
	{
		OLD_ASSERT_AT(POI_FILE, 0xbf, mControlledObjectStackIndex < CONTROLLED_OBJECT_STACK_SIZE,
			"mControlledObjectStackIndex < CONTROLLED_OBJECT_STACK_SIZE", "");
		ChangeControl(GetControlled(), object);
		mControlledObjectStack[mControlledObjectStackIndex] = object;
		mControlledObjectStackIndex++;
		if (sControlChanged != 0)
		{
			sControlChanged(this - sManagers);
		}
	}

	// FUNCTION: ENGINE 0x10826660
	void POIManager::PopControlled(GameObjectHandle object)
	{
		OLD_ASSERT_AT(POI_FILE, 0xf4, mControlledObjectStackIndex, "mControlledObjectStackIndex", "");
		mControlledObjectStackIndex--;
		ChangeControl(object, GetControlled());
		if (sControlChanged != 0)
		{
			sControlChanged(this - sManagers);
		}
	}

	// FUNCTION: ENGINE 0x10826700
	void POIManager::Push(GameObjectHandle object)
	{
		PushControlled(object);
		PushPOI(object);
	}

	// FUNCTION: ENGINE 0x10826720
	void POIManager::Pop(GameObjectHandle object)
	{
		PopControlled(object);
		PopPOI(object);
	}

	// FUNCTION: ENGINE 0x10826740
	void POIManager::Replace(GameObjectHandle object)
	{
		Pop(GetControlled());
		Push(object);
	}
}
