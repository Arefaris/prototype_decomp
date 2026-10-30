#include "code/proto/freeroamevents/frobjects.h"

#include "code/engine/controller/inputsystem.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectsystem.h"

namespace proto
{
	// The game object a handle stands for, null when it is gone
	static inline engine::GameObject* ObjectOf(const engine::GameObjectHandle& handle)
	{
		return handle.Get();
	}

	// The handles of the players' game objects
	extern engine::GameObjectHandle gPlayerHandles[];

	// The first player's handle, the empty handle without players
	static inline engine::GameObjectHandle GetFirstPlayer()
	{
		if (engine::controller::InputSystem::Get()->GetPlayerCount() <= 0)
		{
			return engine::GameObjectHandle();
		}
		return gPlayerHandles[0];
	}

	// The position of the game object of an object (its transform's translation)
	static inline math::Vector PositionOfObject(const engine::GameObjectHandle& handle)
	{
		const math::Matrix& matrix = handle.Get()->transform->value;
		math::Vector position;
		position.x = matrix.m[3][0];
		position.y = matrix.m[3][1];
		position.z = matrix.m[3][2];
		return position;
	}

	// FUNCTION: ENGINE 0x105854C0
	FREventLocatorDef::FREventLocatorDef(ObjectName newName, float newX, float newY, float newZ, float new24,
		float new28, float new2C) : FREventObjectBase(newName)
	{
		x = newX;
		y = newY;
		z = newZ;
		unknown24 = new24;
		unknown28 = new28;
		unknown2C = new2C;
	}

	// FUNCTION: ENGINE 0x10586060
	bool FREventLocatorDef::IsReady()
	{
		return handle.Get() != 0;
	}

	// FUNCTION: ENGINE 0x105860B0
	void FREventLocatorDef::Release()
	{
		if (handle.Get() != 0)
		{
			handle.DeferUpdate(false);
		}
	}

	// FUNCTION: ENGINE 0x10585560
	math::Vector FREventLocatorDef::GetPosition()
	{
		math::Vector position;
		position.x = x;
		position.y = y;
		position.z = z;
		return position;
	}

	// FUNCTION: ENGINE 0x10585580
	int FREventLocatorDef::GetKind()
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x10586900
	FREventLocatorDef::~FREventLocatorDef()
	{
		if (handle.Get() != 0)
		{
			handle.DeferUpdate(false);
		}
	}

	// FUNCTION: ENGINE 0x105907A0
	FREventObjectDef::FREventObjectDef(ObjectName newName, ObjectName newTemplateName, float newX, float newY,
		float newZ, float newDirectionX, float newDirectionY, float newDirectionZ) : FREventObjectBase(newName),
		templateName(newTemplateName)
	{
		x = newX;
		y = newY;
		z = newZ;
		directionX = newDirectionX;
		directionY = newDirectionY;
		directionZ = newDirectionZ;
	}

	// FUNCTION: ENGINE 0x105913C0
	bool FREventObjectDef::IsReady()
	{
		return handle.Get() != 0;
	}

	// FUNCTION: ENGINE 0x10591410
	void FREventObjectDef::Release()
	{
		if (handle.Get() != 0)
		{
			handle.DeferUpdate(false);
		}
	}

	// FUNCTION: ENGINE 0x10591890
	math::Vector FREventObjectDef::GetPosition()
	{
		return PositionOfObject(handle);
	}

	// FUNCTION: ENGINE 0x10590850
	int FREventObjectDef::GetKind()
	{
		return 2;
	}

	// FUNCTION: ENGINE 0x10591F90
	FREventObjectDef::~FREventObjectDef()
	{
		if (handle.Get() != 0)
		{
			handle.DeferUpdate(false);
		}
	}

	// FUNCTION: ENGINE 0x105908B0
	int FREventTriggerBase::GetKind()
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x105908D0
	// NONMATCHING: the engine builds the by-value name of the inlined base constructor in its own argument slot
	// (one local copy, 8 bytes of locals); ours keeps two local copies, 93 %
#ifdef NONMATCHING
	FREventTriggerDef::FREventTriggerDef(ObjectName newName) : FREventTriggerBase(newName)
	{
	}
#endif

	// FUNCTION: ENGINE 0x10591480
	bool FREventTriggerDef::IsReady()
	{
		return handle.Get() != 0;
	}

	// FUNCTION: ENGINE 0x105914D0
	void FREventTriggerDef::Release()
	{
		if (handle.Get() != 0)
		{
			handle.DeferUpdate(false);
		}
	}

	// FUNCTION: ENGINE 0x10592050
	FREventTriggerDef::~FREventTriggerDef()
	{
		if (handle.Get() != 0)
		{
			handle.DeferUpdate(false);
		}
	}

	// FUNCTION: ENGINE 0x10590FC0
	bool FREventLocator::IsReady()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x10590560
	void FREventLocator::Spawn()
	{
	}

	// FUNCTION: ENGINE 0x10590570
	void FREventLocator::Release()
	{
	}

	// FUNCTION: ENGINE 0x10591920
	math::Vector FREventLocator::GetPosition()
	{
		return PositionOfObject(handle);
	}

	// FUNCTION: ENGINE 0x10590FD0
	int FREventLocator::GetKind()
	{
		return 0;
	}


	// FUNCTION: ENGINE 0x105905A0
	math::Vector FREventTriggerDefSphere::GetPosition()
	{
		math::Vector position;
		position.x = x;
		position.y = y;
		position.z = z;
		return position;
	}

	// FUNCTION: ENGINE 0x105905C0
	math::Vector FREventTriggerDefCuboid::GetPosition()
	{
		math::Vector position;
		position.x = box.centre.x;
		position.y = box.centre.y;
		position.z = box.centre.z;
		return position;
	}

	// FUNCTION: ENGINE 0x10591C40
	// NONMATCHING: the engine tests the player's handle twice (valid, then looked up again) and computes the squared
	// radius after the sum of the squared offsets; ours merges the tests and computes the radius first
#ifdef NONMATCHING
	bool FREventTriggerDefSphere::IsPlayerInside()
	{
		engine::GameObjectHandle player = GetFirstPlayer();
		if (player.IsValid())
		{
			const math::Matrix& matrix = player.Get()->transform->value;
			math::Vector position(matrix.m[3][0], matrix.m[3][1], matrix.m[3][2]);
			float dx = x - position.x;
			float dy = y - position.y;
			float dz = z - position.z;
			float distanceSquared = dx * dx + dz * dz + dy * dy;
			return radius * radius >= distanceSquared;
		}
		return false;
	}
#endif

	// FUNCTION: ENGINE 0x10591D40
	bool FREventTriggerDefCuboid::IsPlayerInside()
	{
		engine::GameObjectHandle player = GetFirstPlayer();
		if (player.IsValid())
		{
			const math::Matrix& matrix = player.Get()->transform->value;
			math::Vector position(matrix.m[3][0], matrix.m[3][1], matrix.m[3][2]);
			return box.Contains(position);
		}
		return false;
	}
}
