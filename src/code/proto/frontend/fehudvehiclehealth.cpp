#include "code/proto/frontend/fehudvehiclehealth.h"

#include "code/engine/controller/inputsystem.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/engine/gameobject/gameobjectmessages.h"

namespace engine
{
	namespace driving
	{
		// 0x10D94F78
		extern const float gZero;
	}
}

namespace proto
{
	// The handles of the players' game objects
	extern engine::GameObjectHandle gPlayerHandles[];
	// 0x103C01F0: asks an object for the object it is linked to and answers it when it is the given one (name guess)
	engine::GameObject* GetLinkedObject(engine::GameObject* object);
	// 0x104DBCA0: the index of the first local player, -1 when there is none (name guess)
	int GetLocalPlayerIndex();
	// 0x104D55F0: the object the first local player is linked to (name guess)
	engine::GameObject* GetLocalPlayerLinkedObject();

	// The handle of a player's game object, the empty handle when there is no such player
	inline engine::GameObjectHandle GetPlayerHandle(int index)
	{
		if (index >= engine::controller::InputSystem::Get()->GetPlayerCount())
		{
			return engine::GameObjectHandle();
		}
		return gPlayerHandles[index];
	}

	// FUNCTION: ENGINE 0x104D54C0
	FEHudVehicleHealth::FEHudVehicleHealth() : visible("_level0.mcAnchor.vehicleHealthHUD._visible"),
		healthMask("_level0.mcAnchor.vehicleHealthHUD.nodes.healthMask._x"),
		damageMask("_level0.mcAnchor.vehicleHealthHUD.damage.healthMask._x"), active(true)
	{
		visible.Set(FlashValue(false));
		healthMask.Set(FlashValue(-410.0));
		damageMask.Set(FlashValue(-410.0));
	}

	// FUNCTION: ENGINE 0x104D5420
	void FEHudVehicleHealth::Update(bool force)
	{
		visible.Flush(force);
		healthMask.Flush(force);
		damageMask.Flush(force);
	}

	// FUNCTION: ENGINE 0x104D54B0
	void FEHudVehicleHealth::OnShow(bool shown)
	{
		SetActive(shown);
	}

	// FUNCTION: ENGINE 0x104D5460
	void FEHudVehicleHealth::SetActive(bool newActive)
	{
		active = newActive;
		if (!newActive)
		{
			visible.Set(FlashValue(false));
			visible.Flush(true);
		}
	}

	// FUNCTION: ENGINE 0x104D5680
	// NONMATCHING: the health ratio is computed with x87 instead of SSE, 42 %
#ifdef NONMATCHING
	void FEHudVehicleHealth::UpdateHealth()
	{
		bool show = false;
		engine::GameObject* vehicle = GetLocalPlayerLinkedObject();
		if (vehicle != 0)
		{
			engine::GetHealthMessage message;
			vehicle->PostMessage(&message);
			float health = message.health;
			if (health > message.maxHealth)
			{
				health = message.maxHealth;
			}
			float offset = health / message.maxHealth * 410.0f - 410.0f;
			healthMask.Set(FlashValue((double)offset));
			double current = damageMask.value.value.number;
			float delta = offset - (float)current;
			double result;
			if (delta >= engine::driving::gZero)
			{
				result = offset;
			}
			else
			{
				result = current + delta * 0.2f;
			}
			damageMask.Set(FlashValue(result));
			show = active;
		}
		visible.Set(FlashValue(show));
	}
#endif

	// FUNCTION: ENGINE 0x104D55F0
	engine::GameObject* GetLocalPlayerLinkedObject()
	{
		int index = GetLocalPlayerIndex();
		if (index < 0)
		{
			return 0;
		}
		engine::GameObjectHandle handle = GetPlayerHandle(index);
		return GetLinkedObject(handle.Get());
	}
}
