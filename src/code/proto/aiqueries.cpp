#include "code/proto/fightitems/ai/aimessages.h"
#include "code/proto/fightitems/ai/aicodemessages.h"
#include "code/proto/fightitems/motion/motionattachmentmessage.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/gameobject/gameobject.h"

namespace engine
{
	// 0x11264A08 / 0x112649E8 / 0x112649F0: the names "Driver", "Gunner" and "Driver_AI" (charactertypenames.cpp)
	extern core::Name<core::CaseSensitiveKey> gDriver;
	extern core::Name<core::CaseSensitiveKey> gGunner;
	extern core::Name<core::CaseSensitiveKey> gDriverAI2;
}

namespace proto
{
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
}
