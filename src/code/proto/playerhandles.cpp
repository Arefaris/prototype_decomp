// The players' game object handles and the local player (unit 0x104DBBB0 - 0x104DC4A0; no assert path, the file name is a
// guess).
#include "code/engine/camera/director.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/engine/system/poimanager.hpp"

namespace engine
{
	// 0x107F2850
	bool IsLocalSlot(int slot);
}

namespace proto
{
	// FUNCTION: ENGINE 0x104DBCA0
	int GetLocalPlayerIndex()
	{
		for (int i = 0; i < 1; i++)
		{
			if (engine::IsLocalSlot(i))
			{
				return i;
			}
		}
		return -1;
	}

	// The handles of the players' game objects (frobjects.cpp)
	extern engine::GameObjectHandle gPlayerHandles[];
	// 0x1126E404: the player whose camera is shown (name guess)
	int gCameraPlayer;

	// FUNCTION: ENGINE 0x104DBBB0
	void SetControlChangedCallback(void (*callback)(int))
	{
		engine::POIManager::sControlChanged = callback;
	}

	// FUNCTION: ENGINE 0x104DBBC0
	int Unknown104DBBC0()
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x104DBCD0
	void ToggleCameraPlayer()
	{
		gCameraPlayer ^= 1;
		engine::camera::Director::Get()->ActivateCamera(gCameraPlayer, 0);
	}

	// FUNCTION: ENGINE 0x104DBD00
	void ResetPlayerHandles()
	{
		for (unsigned int i = 0; i < 2; i++)
		{
			gPlayerHandles[i] = engine::GameObjectHandle();
		}
		gCameraPlayer = GetLocalPlayerIndex();
	}

	// FUNCTION: ENGINE 0x104DBF60
	int Unknown104DBF60(engine::GameObject* object)
	{
		return -1;
	}
}
