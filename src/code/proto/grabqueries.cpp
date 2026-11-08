#include "code/proto/fightitems/motion/motion_grabcondition.h"
#include "code/proto/fightitems/motion/motionactionmessages.h"
#include "code/proto/fightitems/motion/motionmessages4.h"
#include "code/proto/fightitems/ai/aimessages.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/gameobject/gameobject.h"

namespace engine
{
	// 0x112649E0: the name "Holding"
	extern core::Name<core::CaseSensitiveKey> gHolding3;
}

namespace proto
{
	// RTTI: proto::SetGrabbedObjectMessage: gives the object an object to hold in a named grab slot (the same declaration as
	// the other units')
	class SetGrabbedObjectMessage : public GrabMessage
	{
	public:
		SetGrabbedObjectMessage(const core::Name<core::CaseSensitiveKey>* newSlot, engine::GameObjectHandle newObject, int v14) : GrabMessage(1), slot(newSlot), object(newObject), unknown14(v14)
		{
		}
		virtual ~SetGrabbedObjectMessage()
		{
		}

		const core::Name<core::CaseSensitiveKey>* slot;  // +0xC
		engine::GameObjectHandle object;  // +0x10
		int unknown14;
	};

	// RTTI: proto::GetSlotNameForGrabbedObjectMessage: the holder answers the name of the slot that holds an object (id 5)
	class GetSlotNameForGrabbedObjectMessage : public GrabMessage
	{
	public:
		explicit GetSlotNameForGrabbedObjectMessage(engine::GameObjectHandle newObject) : GrabMessage(5), object(newObject), slot()
		{
		}
		virtual ~GetSlotNameForGrabbedObjectMessage()
		{
		}

		engine::GameObjectHandle object;  // +0xC
		core::Name<core::CaseSensitiveKey> slot;  // +0x10
	};
}

namespace proto
{
	// RTTI: proto::GetGrabbableClassMessage: the object answers the class of its grabs (the same declaration as
	// motionmessages5.h, which cannot be included next to motionactionmessages.h)
	class GetGrabbableClassMessage : public GrabbableMessage
	{
	public:
		GetGrabbableClassMessage() : GrabbableMessage(1), className(), unknown18(false)
		{
		}
		virtual ~GetGrabbableClassMessage()
		{
		}

		int unknownC;
		core::Name<core::CaseSensitiveKey> className;  // +0x10
		bool unknown18;  // +0x18
		int unknown1C;
	};
}

namespace engine
{
	// 0x11264A10: the name "firearm"
	extern core::Name<core::CaseSensitiveKey> gFirearm2;
}

namespace proto
{
	// The helpers that ask an object about the objects it is attached to (unit 0x103BE3A0 - 0x103BEA90, no assert path;
	// the file name is a guess)

	// FUNCTION: ENGINE 0x103BE4C0
	bool IsGrabbedObject(engine::GameObject* object)
	{
		engine::AttachmentGetAttachmentStateMessage message;
		object->PostMessage(&message);
		if (message.parent == 0)
		{
			return false;
		}
		return message.parent->Get() != 0;
	}

	// FUNCTION: ENGINE 0x103BE560
	engine::GameObject* GetGrabbingObject(engine::GameObject* object)
	{
		engine::GameObject* result = 0;
		engine::AttachmentGetAttachmentStateMessage message;
		object->PostMessage(&message);
		if (message.parent != 0)
		{
			result = message.parent->Get();
		}
		return result;
	}

	// FUNCTION: ENGINE 0x103BEA10
	engine::GameObject* Unknown103BEA10(engine::GameObject* object)
	{
		GetCommanderSquadMessage message;
		object->SendMessage(&message);
		return message.commander.Get();
	}

	// FUNCTION: ENGINE 0x103BE5F0
	engine::GameObject* Unknown103BE5F0(engine::GameObject* object)
	{
		engine::AttachmentGetAttachmentStateMessage message;
		object->PostMessage(&message);
		engine::GameObject* result = 0;
		if (message.parent != 0)
		{
			engine::GameObject* holder = message.parent->Get();
			if (holder != 0)
			{
				GetGrabbedObjectMessage query(&engine::gHolding3);
				holder->SendMessage(&query);
				if (query.grabbed.Get() == object)
				{
					result = holder;
				}
			}
		}
		return result;
	}

	// FUNCTION: ENGINE 0x103BE720
	// NONMATCHING: the engine keeps the zero in ebp, caches the end of the list and loads the master table once (34.8 %)
#ifdef NONMATCHING
	engine::GameObject* Unknown103BE720(engine::GameObject* object)
	{
		GetGrabSlotsMessage message;
		object->SendMessage(&message);
		if (message.slots == 0)
		{
			return 0;
		}
		for (GrabSlot* slot = message.slots->begin; slot != message.slots->end; slot++)
		{
			if (static_cast<engine::GameObjectHandle&>(slot->held).Get() != 0 && slot->name == engine::gHolding3)
			{
				return static_cast<engine::GameObjectHandle&>(slot->held).Get();
			}
		}
		return 0;
	}
#endif

	// FUNCTION: ENGINE 0x103BE830
	engine::GameObject* Unknown103BE830(engine::GameObject* object)
	{
		GetGrabbedObjectMessage query(&engine::gHolding3);
		object->SendMessage(&query);
		engine::GameObject* held = query.grabbed.Get();
		if (held != 0)
		{
			GetGrabbableClassMessage classQuery;
			held->SendMessage(&classQuery);
			if (classQuery.className == engine::gFirearm2)
			{
				return held;
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x103BE920
	void DetachGrabbedObject(engine::GameObject* object)
	{
		engine::GameObject* holder = GetGrabbingObject(object);
		if (holder != 0)
		{
			GetSlotNameForGrabbedObjectMessage query(engine::GetHandle(object));
			holder->SendMessage(&query);
			if (!query.slot.IsEmpty())
			{
				SetGrabbedObjectMessage release(&query.slot, engine::GameObjectHandle(), 0);
				holder->SendMessage(&release);
			}
		}
	}
}
