#include "code/proto/fightitems/ai/aicodemessages.h"
#include "code/proto/fightitems/motion/motionattachmentmessage.h"
#include "code/proto/fightitems/ai/aihelpers.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/math/matrix.h"
#include "code/engine/driving/carattributes.h"
#include "code/proto/faction.h"
#include "code/proto/messages/disguisemessages.h"
#include "code/core/name.h"

namespace engine
{
	// The names the object classes are compared with (charactertypenames.cpp)
	extern core::Name<core::CaseSensitiveKey> gSoldier;  // 0x11263B30
	extern core::Name<core::CaseSensitiveKey> gCommander;  // 0x11263B58
	extern core::Name<core::CaseSensitiveKey> gPedestrian;  // 0x11263B80
	extern core::Name<core::CaseSensitiveKey> gBlackwatch;  // 0x11263B68
	extern core::Name<core::CaseSensitiveKey> gCop;  // 0x11263BB0
	extern core::Name<core::CaseSensitiveKey> gTankGunner;  // 0x11263C98
	// 0x11264A08 / 0x112649E8 / 0x112649F0: the names "Driver", "Gunner" and "Driver_AI" (charactertypenames.cpp)
	extern core::Name<core::CaseSensitiveKey> gDriver;
	extern core::Name<core::CaseSensitiveKey> gGunner;
	extern core::Name<core::CaseSensitiveKey> gDriverAI2;
}

namespace proto
{
	namespace HitEffectManager
	{
		extern core::Name<core::CaseSensitiveKey> gClassNameAttributeName;  // 0x112562B8
	}

	engine::GameObject* GetPlayerObject(int index);  // 0x10099560
	// 0x103BE3E0: the faction attribute of an object (name guess)
	Faction GetObjectFaction(engine::GameObject* object);

	// RTTI: proto::GetHelicopterSolverParamsMessage: the vehicle answers the parameters of its helicopter solver
	struct GetHelicopterSolverParamsMessage : public VehicleMessage
	{
		GetHelicopterSolverParamsMessage() : VehicleMessage(0), unknownC(0), params(0)
		{
		}
		virtual ~GetHelicopterSolverParamsMessage()
		{
		}

		int unknownC;
		void* params;  // +0x10
	};

	// RTTI: proto::GetTankSolverPropertiesVehicleMessage: the vehicle answers the properties of its tank solver
	struct GetTankSolverPropertiesVehicleMessage : public VehicleMessage
	{
		GetTankSolverPropertiesVehicleMessage() : VehicleMessage(2), properties(0)
		{
		}
		virtual ~GetTankSolverPropertiesVehicleMessage()
		{
		}

		void* properties;  // +0xC
	};

	// Helpers that ask an object about the objects it holds or is linked with (unit 0x103C0040 - 0x103C5D60, no assert
	// path; the file name is a guess)

	// FUNCTION: ENGINE 0x103C0040
	engine::GameObject* GetDriverObject(engine::GameObject* object)
	{
		GetGrabbedObjectMessage query(&engine::gDriver);
		object->SendMessage(&query);
		return query.grabbed.Get();
	}

	// FUNCTION: ENGINE 0x103C00D0
	engine::GameObject* GetGunnerObject(engine::GameObject* object)
	{
		GetGrabbedObjectMessage query(&engine::gGunner);
		object->SendMessage(&query);
		return query.grabbed.Get();
	}

	// FUNCTION: ENGINE 0x103C0160
	engine::GameObject* GetAIDriverObject(engine::GameObject* object)
	{
		GetGrabbedObjectMessage query(&engine::gDriverAI2);
		object->SendMessage(&query);
		return query.grabbed.Get();
	}

	// FUNCTION: ENGINE 0x103C01F0
	engine::GameObject* GetLinkedObject(engine::GameObject* object)
	{
		if (object == 0)
		{
			return 0;
		}
		engine::AttachmentGetAttachmentStateMessage message;
		object->PostMessage(&message);
		if (message.parent != 0)
		{
			engine::GameObject* holder = message.parent->Get();
			if (holder != 0)
			{
				engine::GameObject* driver = GetDriverObject(holder);
				engine::GameObject* gunner = GetGunnerObject(holder);
				engine::GameObject* aiDriver = GetAIDriverObject(holder);
				if (object == driver || object == gunner || object == aiDriver)
				{
					return holder;
				}
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x103C02D0
	bool Unknown103C02D0(engine::GameObject* object)
	{
		GetHelicopterSolverParamsMessage message;
		object->SendMessage(&message);
		if (message.params != 0)
		{
			return true;
		}
		engine::GameObject* linked = GetLinkedObject(object);
		if (linked != 0)
		{
			linked->SendMessage(&message);
			if (message.params != 0)
			{
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x103C0360
	bool Unknown103C0360(engine::GameObject* object)
	{
		GetTankSolverPropertiesVehicleMessage message;
		object->SendMessage(&message);
		if (message.properties != 0)
		{
			return true;
		}
		engine::GameObject* linked = GetLinkedObject(object);
		if (linked != 0)
		{
			linked->SendMessage(&message);
			if (message.properties != 0)
			{
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x103C0E00
	// NONMATCHING: the engine puts the false return before the true block (91.9 %)
#ifdef NONMATCHING
	bool IsPersonClass(engine::GameObject* object)
	{
		engine::BaseAttribute* attribute = object->FindAttribute(HitEffectManager::gClassNameAttributeName);
		core::Name<core::CaseSensitiveKey>* className;
		if (attribute != 0)
		{
			className = &((engine::Attribute<core::Name<core::CaseSensitiveKey> >*)attribute)->value;
		}
		else
		{
			className = 0;
		}
		bool result = false;
		if (className != 0)
		{
			result = *className == engine::gSoldier;
			if (result)
			{
				goto matched;
			}
			result = *className == engine::gCommander;
			if (result)
			{
				goto matched;
			}
			result = *className == engine::gPedestrian;
			if (result)
			{
				goto matched;
			}
			result = *className == engine::gPedestrian;
			if (result)
			{
				goto matched;
			}
			result = *className == engine::gCop;
			if (result)
			{
				goto matched;
			}
			result = *className == engine::gBlackwatch;
			if (result)
			{
				goto matched;
			}
			result = *className == engine::gTankGunner;
			if (!result)
			{
				return result;
			}
matched:
			result = true;
		}
		return result;
	}
#endif

	// FUNCTION: ENGINE 0x103C0EC0
	bool IsPedestrianClass(engine::GameObject* object)
	{
		engine::BaseAttribute* attribute = object->FindAttribute(HitEffectManager::gClassNameAttributeName);
		core::Name<core::CaseSensitiveKey>* className;
		if (attribute != 0)
		{
			className = &((engine::Attribute<core::Name<core::CaseSensitiveKey> >*)attribute)->value;
		}
		else
		{
			className = 0;
		}
		bool result = false;
		if (className != 0)
		{
			result = *className == engine::gPedestrian;
		}
		return result;
	}

	// The squared distance from a position to the first player (the engine keeps the position and the player index in
	// registers)
	static float SquaredDistanceToPlayer(const math::Vector* position, int player)
	{
		engine::GameObject* object = GetPlayerObject(player);
		if (object == 0)
		{
			return 999999995904.0f;
		}
		math::Matrix& matrix = object->transform->value;
		float dx = position->x - matrix.m[3][0];
		float dy = position->y - matrix.m[3][1];
		float dz = position->z - matrix.m[3][2];
		return dx * dx + dy * dy + dz * dz;
	}

	// FUNCTION: ENGINE 0x103C0F80
	float Unknown103C0F80(const math::Vector* position)
	{
		float nearest = 999999995904.0f;
		float distance = SquaredDistanceToPlayer(position, 0);
		if (distance < 999999995904.0f)
		{
			nearest = distance;
		}
		return nearest;
	}

	// FUNCTION: ENGINE 0x103C22A0
	bool IsMilitaryDisguiseNotBlown(engine::GameObject* object)
	{
		bool result = false;
		Faction faction = GetObjectFaction(object);
		result = faction.IsMilitary();
		if (result)
		{
			GetBlownDisguiseMsg message;
			object->SendMessage(&message);
			result = message.time == choreo::gZero;
		}
		return result;
	}

	// FUNCTION: ENGINE 0x103C2360
	bool Unknown103C2360(engine::GameObject* object, engine::GameObject* other)
	{
		Faction faction = GetObjectFaction(object);
		if (faction.IsInfected())
		{
			return true;
		}
		if (faction.IsMilitary())
		{
			return !IsMilitaryDisguiseNotBlown(other);
		}
		Faction otherFaction = GetObjectFaction(other);
		return otherFaction.GetRelationTo(faction) == 0;
	}

	// FUNCTION: ENGINE 0x103C2420
	bool IsPlayerOrDrivenByPlayer(engine::GameObject* object)
	{
		if (object == 0)
		{
			return false;
		}
		bool result = IsPlayerObject(object);
		if (!result)
		{
			return IsPlayerObject(GetDriverObject(object));
		}
		return result;
	}
}
